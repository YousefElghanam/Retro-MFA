#include "Retro_MFA.h"

bool read_file(t_data *data) {
  ssize_t bytes = read(data->fd, data->file_buf, BUFFER_SIZE);
  if (DEBUG)
  	printf("read %zd bytes from file\n", bytes);
  if (bytes == 0)
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
  	return (cleanup(&data, 2, "Error setting everything up."));
  while (read_file(&data))
  	visual_test(&data);
  rnd_frame(&data);
  //   open_window(file_buf);
  return (cleanup(&data, 0, NULL));
}
