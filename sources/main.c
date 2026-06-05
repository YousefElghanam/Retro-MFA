#include "Retro_MFA.h"
#include "mlx_utils.h"


bool read_file(int fd, t_byte *file_buf) {
  ssize_t bytes = read(fd, file_buf, BUFFER_SIZE);
  printf("bytes: %zd\n", bytes);
  if (bytes == 0)
	return (false);
  return (true);
}

void visual_test(t_byte* file_buf, t_mlxu* visual, t_mlxu_2d* px)
{
	static int frame;
	static unsigned int pixels;
	int color = 0;
	for (int i = 0; i + 2 < BUFFER_SIZE;)
	{
		color = 0;
		// color = file_buf[i] << 24 | file_buf[i + 1] << 16 | file_buf[i + 2] << 8;
		// color = file_buf[i + 2] << 24 | file_buf[i + 1] << 16 | file_buf[i] << 8;
		// color = file_buf[i + 2] << 16 | file_buf[i + 1] << 8 | file_buf[i];
		color = file_buf[i + 2] | file_buf[i + 1] << 8 | file_buf[i] << 16;
		i += 4;
		// read from buffer UNTIL all pixels are filled
		// then render, wait a bit, start over
		mlxu_pixel_put_buffer(visual, px->x, px->y, color);
		if (px->x == visual->active.win->size.x)
		{
			// printf("row %i full\n", px->y);
			px->x = 0;
			px->y++;
		}
		else
			px->x++;
		if (px->y == visual->active.win->size.y && px->x == visual->active.win->size.x)
		{
			pixels += px->x * px->y;
			frame++;
			printf("frame #%i (pixels|bytes: %u|%u)\n", frame, pixels, pixels * 4);
			mlxu_flush_buffer(visual);
			usleep(3000000);
			px->x = 0;
			px->y = 0;
		}
	}
	
	
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
  mlxu_setup_new_win(&visual, "TESTING", (t_mlxu_2d){400,400,0});
  t_mlxu_2d px;
  memset(&px, 0, sizeof (px));
  while (read_file(fd, file_buf))
  {
  	visual_test(file_buf, &visual, &px);
  }
  mlxu_flush_buffer(&visual);
usleep(3000000);
  //   open_window(file_buf);
  mlxu_terminate(&visual, "bye");
  free(file_buf);
  return 0;
}