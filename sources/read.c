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

static uint32_t build_int(t_byte *buf, ssize_t bytes_read, ssize_t *offset)
{
	if (bytes_read < *offset + 4)
		exit(1); // FIXME
	uint32_t number = 
		buf[*offset + 3] << 24 |
		buf[*offset + 2] << 16 |
		buf[*offset + 1] << 8 |
		buf[*offset];
	printf("[int] raw bytes:  0x%.2X%.2X%.2X%.2X\n"
		   "      offset was: %zu (0x%.2X)\n"
		   "      converted number: %i\n",
		buf[*offset], buf[*offset + 1], buf[*offset + 2], buf[*offset + 3],
		*offset, (unsigned int) *offset, number);
	*offset += 4;
	return ((uint32_t) number);
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
		num = build_int(file_buf, bytes_read, offset);
		*offset += num;
	}
	// 4) skip the unknown data block 
	*offset += 9*4 + 1024; // TODO why does it need 9*4 and not 8*4?
	// 5) skipping more unknown data block (icons?)
	*offset += 15540; // first big noise range
	*offset += 47008; // second larger noise range
	*offset += 26434; // skipped until assets?? where in white 2 big chunks of data appear 54 times
	num = build_int(file_buf, bytes_read, offset);
	*offset += num;
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