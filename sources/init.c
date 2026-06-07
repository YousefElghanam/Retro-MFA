#include "../include/Retro_MFA.h"

void set_flip_alignment(t_manual *alignment)
{
  //white4: 20, 34 - 51, 53, 54, 57, 58, 59
	alignment[0].byte0 = build_4_bytes_int((uint8_t[4]){0xD7, 0xB1, 0x00, 0x00}); // 5
	alignment[1].byte0 = build_4_bytes_int((uint8_t[4]){0x64, 0x86, 0x00, 0x00}); // 20
	alignment[2].byte0 = build_4_bytes_int((uint8_t[4]){0x13, 0x20, 0x00, 0x00}); // 34
	alignment[3].byte0 = build_4_bytes_int((uint8_t[4]){0x72, 0xC4, 0x00, 0x00}); // 35
	alignment[4].byte0 = build_4_bytes_int((uint8_t[4]){0x8A, 0x43, 0x00, 0x00}); // 36
	alignment[5].byte0 = build_4_bytes_int((uint8_t[4]){0x9A, 0x3B, 0x00, 0x00}); // 37
	alignment[6].byte0 = build_4_bytes_int((uint8_t[4]){0xF5, 0x5C, 0x00, 0x00}); // 38
	alignment[7].byte0 = build_4_bytes_int((uint8_t[4]){0x12, 0x5C, 0x00, 0x00}); // 39
	alignment[8].byte0 = build_4_bytes_int((uint8_t[4]){0x4A, 0x63, 0x00, 0x00}); // 40
	alignment[9].byte0 = build_4_bytes_int((uint8_t[4]){0x38, 0xD3, 0x00, 0x00}); // 41
	alignment[10].byte0 = build_4_bytes_int((uint8_t[4]){0x9F, 0x16, 0x00, 0x00}); // 42
	alignment[11].byte0 = build_4_bytes_int((uint8_t[4]){0xA6, 0x76, 0x00, 0x00}); // 43
	alignment[12].byte0 = build_4_bytes_int((uint8_t[4]){0xBC, 0x44, 0x00, 0x00}); // 44
	alignment[13].byte0 = build_4_bytes_int((uint8_t[4]){0x17, 0x8D, 0x00, 0x00}); // 45
	alignment[14].byte0 = build_4_bytes_int((uint8_t[4]){0x83, 0x29, 0x00, 0x00}); // 46
	alignment[15].byte0 = build_4_bytes_int((uint8_t[4]){0x24, 0xC5, 0x00, 0x00}); // 47
	alignment[16].byte0 = build_4_bytes_int((uint8_t[4]){0x2D, 0x0E, 0x00, 0x00}); // 48
	alignment[17].byte0 = build_4_bytes_int((uint8_t[4]){0x30, 0xD9, 0x00, 0x00}); // 49
	alignment[18].byte0 = build_4_bytes_int((uint8_t[4]){0xAA, 0xBC, 0x00, 0x00}); // 50
	alignment[19].byte0 = build_4_bytes_int((uint8_t[4]){0x90, 0xE2, 0x00, 0x00}); // 51
	alignment[20].byte0 = build_4_bytes_int((uint8_t[4]){0x92, 0xAB, 0x00, 0x00}); // 53
	alignment[21].byte0 = build_4_bytes_int((uint8_t[4]){0x30, 0x4C, 0x00, 0x00}); // 54
	alignment[22].byte0 = build_4_bytes_int((uint8_t[4]){0x9A, 0x08, 0x00, 0x00}); // 57
	alignment[23].byte0 = build_4_bytes_int((uint8_t[4]){0x3C, 0x84, 0x00, 0x00}); // 58
	alignment[24].byte0 = build_4_bytes_int((uint8_t[4]){0x34, 0x60, 0x00, 0x00}); // 59
	alignment[0].addr = 0x21581;
}

void set_skip(t_manual *skip)
{
	skip[0].byte0 = build_4_bytes_int((uint8_t[4]){0x42, 0x8B, 0x00, 0x00});
	skip[0].addr = 0x1D15;
}

bool init(t_data *data, char *file) {
  memset(data, 0, sizeof (t_data));
  data->fd = open(file, O_RDONLY);
  if (data->fd == -1) {
    dprintf(STDERR_FILENO, "couldn't open file %s\n", file);
    return false;
  }
  if (mlxu_setup_new_display(&data->visual) != 0)
  	return (false);
  if (mlxu_setup_new_win(&data->visual, file, (t_mlxu_2d){W,H,0}) != 0)
  	return (false);
  if (mlxu_setup_new_buffer(&data->visual) != 0)
    return (false);
  mlx_hook(data->visual.active.win->ptr,
		   DestroyNotify, NoEventMask, mlx_loop_end,
		   data->visual.mlx_ptr);
  mlx_key_hook(data->visual.active.win->ptr, keyhooks, data);
//   mlx_loop_hook(data.visual.mlx_ptr, get_me_some_pretty_images, &data);
  set_flip_alignment(data->manual_alignment);
  set_skip(data->manual_skip);
  if (DEBUG)
  	printf("Display: %ix%i || Window: %ix%i (%ipx)\n",\
		data->visual.dsp_size.x, data->visual.dsp_size.y,
		data->visual.active.win->size.x, data->visual.active.win->size.y,
		data->visual.active.win->size.x * data->visual.active.win->size.y);
  return (true);
}
