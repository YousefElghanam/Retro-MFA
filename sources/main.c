#include "Retro_MFA.h"

bool validate_header(t_byte *file_buf, ssize_t bytes_read, ssize_t *offset)
{
	// 1) initial check for file id
	const uint8_t fileid[5] = {MFA_FILEID}; // FILE ID: |MMF2|
	if (bytes_read > 5 && memcmp(file_buf, &fileid, 5) == 0)
	{
		// 2) locate end of header
		const uint8_t headerend[12] = {MFA_ENDOFHEADER};
		for (int i = 5; i < bytes_read; i++)
		{
			if (file_buf[i] == headerend[0] && bytes_read - i >= 12)
			{
				if (memcmp(file_buf + i, &headerend, 12))
					continue;
				else
				{
					printf("HEADER END FOUND\n");
					*offset = i + 12;
					return (true);
				}
			}
		}
	}
	dprintf(STDERR_FILENO, "Error: MFA header broken\n");
	return (false);
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
		return (false);
	header_validated = true;
  }
  if (data->bytes_read == 0)
	return (false);
  return (true);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    dprintf(STDERR_FILENO, "usage: ./Retro_MFA \"FILE.mfa\"\n");
    return 1;
  }
  if (strlen(argv[1]) < 5 || strncmp(argv[1] + strlen(argv[1]) - 4, ".mfa", 4) != 0) {
    dprintf(STDERR_FILENO, "usage: ./Retro_MFA \"FILE.mfa\"\n");
    return 1;
  }
  t_data data;
  if (!init(&data, argv[1]))
  	return (cleanup(&data, 2, "Error setting everything up.\n"));
  while (read_file(&data)) // TODO state handling, bad file header etc. on parsing? the render call after loop
  	visual_test(&data);
  rnd_frame(&data);
  //   open_window(file_buf);
  return (cleanup(&data, 0, NULL));
}
