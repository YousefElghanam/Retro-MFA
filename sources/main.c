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
//   while (read_file(&data)) // TODO state handling, bad file header etc. on parsing? the render call after loop
//   	visual_test(&data);
//   rnd_frame(&data);
  read_file(&data);
  single_sprite_test(&data, 0x178A7);
  single_sprite_test(&data, 0x1F29F);
  single_sprite_test(&data, 0x22923);
  single_sprite_test(&data, 0x25FA7);
  single_sprite_test(&data, 0x2962B);
  single_sprite_test(&data, 0x2CCAF);
  single_sprite_test(&data, 0x3DD43);
  single_sprite_test(&data, 0x3EE9F);
  single_sprite_test(&data, 0x44EF7);
  single_sprite_test(&data, 0x65DDD);
  single_sprite_test(&data, 0x68ACD);
  single_sprite_test(&data, 0xACEF7);
  single_sprite_test(&data, 0xD6507);
  single_sprite_test(&data, 0xE4D87);
  rnd_frame(&data);
  //   open_window(file_buf);
  return (cleanup(&data, 0, NULL));
}
