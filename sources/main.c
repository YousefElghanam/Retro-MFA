#include "Retro_MFA.h"
#include "mlx_utils.h"
#include "string.h"

void read_file(int fd, char *file_buf) {
  read(fd, file_buf, BUFFER_SIZE);
}

void visual_test()
{
	t_mlxu visual;
	memset(&visual, 0, sizeof (visual));
	mlxu_setup_new_display(&visual);
	mlxu_setup_new_win(&visual, "TESTING", (t_mlxu_2d){800,600,0});
	sleep(1);
	mlxu_terminate(&visual, "bye");
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
  char *file_buf = calloc(1, BUFFER_SIZE);
  if (!file_buf) {
    dprintf(STDERR_FILENO, "memory failure\n");
    return 1;
  }
  read_file(fd, file_buf);
  //   open_window(file_buf);
 visual_test();
  free(file_buf);
  return 0;
}