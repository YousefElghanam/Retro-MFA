#include "Retro_MFA.h"

bool read_file(t_data *data) {
  static int call;
  data->bytes_read = read(data->fd, data->file_buf, BUFFER_SIZE);
  if (DEBUG) {
	static ssize_t total;
	total += data->bytes_read;
	printf("read %zd bytes from file (total: %zd)\n",
		data->bytes_read, total);
  }
  call++; // TODO or a bool for a ONETIME header check, if bytes_read is large enough
  if (call == 1)
  {
	const uint8_t head[5] = {MFA_FILEID}; // FILE ID: |MMF2|
	if (memcmp(data->file_buf, &head, 5))
	{
		dprintf(STDERR_FILENO, "Error: MFA header broken\n");
		return (false);
	}
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
