#include "../include/Retro_MFA.h"

void set_flip_alignment(t_manual *alignment)
{
	alignment[0].byte0 = build_4_bytes_int((uint8_t[4]){0xD7, 0xB1, 0x00, 0x00});
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
