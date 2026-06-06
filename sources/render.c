#include "Retro_MFA.h"

static void prt_frameinfo(t_debug* dinfo)
{
	if (!DEBUG)
		return ;
	static unsigned int last_pixels;
	// dinfo->pixels += last_px->x * last_px->y;
	dinfo->frame++;
	printf("frame #%i: %6u pixels (total: %u pixels, %u bytes)\n",
		dinfo->frame, dinfo->pixels - last_pixels,
		dinfo->pixels, dinfo->pixels * 4);
	last_pixels = dinfo->pixels;
}

void rnd_frame(t_data *data)
{
	prt_frameinfo(&data->dinfo);
	mlxu_flush_buffer(&data->visual);
	usleep(FRAME_SLEEPTIME);
}

int keyhooks(int key, void* param)
{
	t_data* data = param;
	if (key == K_Q || key == K_ESC)
		mlx_loop_end(data->visual.mlx_ptr);
	return (0);
}
