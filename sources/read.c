#include "Retro_MFA.h"

static bool validate_fourbytes(
	t_byte *buf,
	ssize_t bytes_read,
	ssize_t *offset,
	uint8_t four_bytes[4])
{
	static int nmagic;
	nmagic++;
	printf("::: read %zu || offset %zu ||\n"
		   "    four bytes 0x%.2X%.2X%.2X%.2X\n"
		   "    raw bytes  0x%.2X%.2X%.2X%.2X\n",
		bytes_read, *offset,
		four_bytes[0], four_bytes[1], four_bytes[2], four_bytes[3],
		buf[*offset], buf[*offset + 1], buf[*offset + 2], buf[*offset + 3]);
	if  (bytes_read > *offset + 4)
	{
		if (memcmp(buf + *offset, four_bytes, 4) == 0)
			// return (false);
			printf("Magic Byte #%i found.\n", nmagic);
		else
			printf("Magic Byte #%i NOT found.\n", nmagic);
		*offset += 4;
	}
	return (true);
}

static void find_assets(t_byte *file_buf, ssize_t bytes_read, ssize_t *og_off)
{
	uint8_t sequence[6] = {ASSET_HEADER_SEQUENCE};
	t_byte *buf;
	t_sprite sprite;
	int assets_found = 0;
	// printf("%s: offset %zu bytes read %zu\n", __FUNCTION__, *og_off, bytes_read);
	for (ssize_t offset = *og_off;
		 offset + ASSET_HEADER_SIZE < bytes_read;
		 offset++)
	{
		buf = &file_buf[offset];
		if (memcmp(&buf[2], sequence, 6))
			continue;
		// printf("%s got a sequence\n", __FUNCTION__);
		// check MUST FILLED bytes for valid asset
		if (buf[0] && buf[1] && buf[8] && buf[9] && buf[12] && buf[14] && buf[16] && buf[17])
		{
			// printf("\tfound an asset\n");
			sprite.width = build_2_bytes_int(&buf[12]);
			sprite.height = build_2_bytes_int(&buf[14]);
			sprite.size = build_4_bytes_int(&buf[8]);
			// if (sprite.width > 25 && sprite.height > 25)
			if (sprite.size > 2000 && sprite.size < 200000)
			{
				printf("sprite data @0x%.2X: %ix%i (%i bytes)\n",
					(unsigned int) offset, sprite.width, sprite.height, sprite.size);
				assets_found++;
			}
		}
	}
	printf("%s located %i valid headers\n", __FUNCTION__, assets_found);
}


static bool validate_header(t_byte *file_buf, ssize_t bytes_read, ssize_t *offset)
{
	// 1) initial check for file id
	// const uint8_t fileid[4] = {MFA_FILEID}; // FILE ID: |MMF2|
	// if (bytes_read > 4 && memcmp(file_buf, &fileid, 4))
	// 	return (false);
	validate_fourbytes(file_buf, bytes_read, offset, (uint8_t[4]){MFA_FILEID});
	// 2) some magic bytes
	validate_fourbytes(file_buf, bytes_read, offset, (uint8_t[4]){MAGIC_1});
	validate_fourbytes(file_buf, bytes_read, offset, (uint8_t[4]){MAGIC_2});
	validate_fourbytes(file_buf, bytes_read, offset, (uint8_t[4]){MAGIC_3});
	// 3) skip over tile, path, filler...
	uint32_t num;
	for (short i = 0; i < 4; i++)
	{
		num = build_4_bytes_int(&file_buf[*offset]);
		*offset += 4 + num;
	}
	// 4) skip the unknown data block 
	*offset += 9*4 + 1024; // TODO why does it need 9*4 and not 8*4?
	find_assets(file_buf, bytes_read, offset);
	// 5) skipping more unknown data block (icons?)
	// *offset += 15540; // first big noise range
	// *offset += 47008; // second larger noise range
	// *offset += 26434; // skipped until assets?? where in white 2 big chunks of data appear 54 times
	// num = build_4_bytes_int(&file_buf[*offset]); // TODO is this the 4 byte sequence BEFORE the 32 byte?
	// *offset += 4 + num;
	return (true);
}

bool read_file(t_data *data) {
  static bool header_validated;
  data->bytes_read = read(data->fd, data->file_buf, BUFFER_SIZE);
  if (DEBUG) {
	static ssize_t total;
	total += data->bytes_read;
	printf("read %zd bytes from file (total: %zd)\n",
		data->bytes_read, total);
  }
  if (!header_validated)
  {
	if (!validate_header(data->file_buf, data->bytes_read, &data->offset))
	{
		dprintf(STDERR_FILENO, "Error: MFA header broken\n");
		return (false);
	}
	header_validated = true;
  }
  if (data->bytes_read == 0)
	return (false);
  return (true);
}