#include "../include/Retro_MFA.h"

static bool validate_fourbytes(
	t_byte *buf,
	ssize_t b_read,
	ssize_t *offset,
	uint8_t four_bytes[4])
{
	static int nmagic;
	nmagic++; 
	if (DEBUG && b_read)
		printf("::: read %zu || offset %zu ||\n", b_read, *offset);
	if (DEBUG && b_read > *offset + 4)
		printf("    four bytes 0x%.2X%.2X%.2X%.2X\n"
			   "    raw bytes  0x%.2X%.2X%.2X%.2X\n",
			   four_bytes[0], four_bytes[1], four_bytes[2], four_bytes[3],
			   buf[*offset], buf[*offset + 1], buf[*offset + 2], buf[*offset + 3]);
	if  (b_read > *offset + 4)
	{
		if (memcmp(buf + *offset, four_bytes, 4) != 0)
			return (false);
			// printf("Magic Byte #%i NOT found.\n", nmagic);
		else if (DEBUG)
			printf("Magic Byte #%i found.\n", nmagic);
		*offset += 4;
	}
	return (true);
}

static bool validate_header(t_byte *buf, ssize_t b_read, ssize_t *offset)
{
	if (// 1) initial check for file id
		!validate_fourbytes(buf, b_read, offset, (uint8_t[4]){MFA_FILEID}) ||
		// 2) some magic bytes
		!validate_fourbytes(buf, b_read, offset, (uint8_t[4]){MAGIC_1}) ||
		!validate_fourbytes(buf, b_read, offset, (uint8_t[4]){MAGIC_2}) ||
		!validate_fourbytes(buf, b_read, offset, (uint8_t[4]){MAGIC_3})
	)
		return (false);
	// 3) all the other data blocks are simply ignored by now
	return (true);
}

void read_file(t_data *data) {
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
		data->res = RES_ERR;
		return;
	}
	header_validated = true;
  }
  if (data->bytes_read == 0)
  	data->res = RES_DONE;
// 	return (false);
}