#include "Retro_MFA.h"

bool read_file(int fd, t_byte *file_buf) {
  ssize_t bytes = read(fd, file_buf, BUFFER_SIZE);
  printf("bytes: %zd\n", bytes);
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
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    dprintf(STDERR_FILENO, "couldn't open file %s\n", argv[1]);
    return 1;
  }
  t_byte *file_buf = calloc(1, BUFFER_SIZE);
  if (!file_buf) {
    dprintf(STDERR_FILENO, "memory failure\n");
    return 1;
  }
  t_mlxu visual;
  memset(&visual, 0, sizeof (visual));
  mlxu_setup_new_display(&visual);
  mlxu_setup_new_win(&visual, "TESTING", (t_mlxu_2d){W,H,0});
  if (DEBUG)
  	printf("Display: %ix%i || Window: %ix%i\n", visual.dsp_size.x, visual.dsp_size.y, visual.active.win->size.x, visual.active.win->size.y);
  t_mlxu_2d px;
  t_debug dinfo;
  memset(&px, 0, sizeof (px));
  while (read_file(fd, file_buf))
  	visual_test(file_buf, &visual, &px, &dinfo);
  prt_frameinfo(&dinfo, &px);
  mlxu_flush_buffer(&visual);
  usleep(3000000);
  //   open_window(file_buf);
  mlxu_terminate(&visual, "bye");
  free(file_buf);
  return 0;
}