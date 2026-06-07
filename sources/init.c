#include "../include/Retro_MFA.h"

bool init(t_data *data, char *file) {
  memset(data, 0, sizeof (t_data));
  data->fd = open(file, O_RDONLY);
  if (data->fd == -1) {
    dprintf(STDERR_FILENO, "couldn't open file %s\n", file);
    return false;
  }
  if (mlxu_setup_new_display(&data->visual) != 0)
  	return (false);
  if (mlxu_setup_new_win(&data->visual, TITLE, (t_mlxu_2d){W,H,0}) != 0)
  	return (false);
  if (mlxu_setup_new_buffer(&data->visual) != 0)
    return (false);
  mlx_hook(data->visual.active.win->ptr,
		   DestroyNotify, NoEventMask, mlx_loop_end,
		   data->visual.mlx_ptr);
  mlx_key_hook(data->visual.active.win->ptr, keyhooks, data);
//   mlx_loop_hook(data.visual.mlx_ptr, get_me_some_pretty_images, &data);
  if (DEBUG)
  	printf("Display: %ix%i || Window: %ix%i (%ipx)\n",\
		data->visual.dsp_size.x, data->visual.dsp_size.y,
		data->visual.active.win->size.x, data->visual.active.win->size.y,
		data->visual.active.win->size.x * data->visual.active.win->size.y);
  return (true);
}
