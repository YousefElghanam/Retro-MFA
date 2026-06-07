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
  while (data.res == RES_OK)
  {
	read_file(&data);
	get_me_some_pretty_images(&data);
  }
  if (data.res == RES_DONE)
  {
	if (data.dinfo.pages)
	{
		rnd_frame(&data);
		printf("total pages: %i\n", data.dinfo.pages);
		printf("\nusage:\n"
				"   press cursor keys to move between pages\n"
				"   press 'q' or 'esc' to quit\n\n");
		mlx_loop(data.visual.mlx_ptr);
	}
	else
		printf("No images found.\n");
  }
  return (cleanup(&data, 0, NULL));
}
