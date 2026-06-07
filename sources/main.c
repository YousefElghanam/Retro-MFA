#include "../include/Retro_MFA.h"

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
  	get_me_some_pretty_images(&data);
//   	visual_test(&data);
  if (data.dinfo.total)
  {
	  rnd_frame(&data);
	  printf("images: %i\n", data.dinfo.images);
	  printf("\nusage:\n"
			 "   press cursor keys to move between pages\n"
			 "   press 'q' or 'esc' to quit\n\n");
	  mlx_loop(data.visual.mlx_ptr);
  }
  return (cleanup(&data, 0, NULL));
}
