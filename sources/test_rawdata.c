#include "Retro_MFA.h"

void prt_frameinfo(t_debug* dinfo, t_mlxu_2d* last_px)
{
	if (!DEBUG)
		return ;
	dinfo->pixels += last_px->x * last_px->y;
	dinfo->frame++;
	printf("frame #%i (pixels|bytes: %u|%u)\n", dinfo->frame, dinfo->pixels, dinfo->pixels * 4);
}

static void advance_px(t_mlxu_2d* px, int max_x)
{
	if (px->x == max_x)
	{
		px->x = 0;
		px->y++;
	}
	else
		px->x++;
}

void visual_test(t_byte* file_buf, t_mlxu* visual, t_mlxu_2d* px, t_debug* dinfo)
{
	int color;
	for (int i = 0; i + 2 < BUFFER_SIZE;)
	{
		color = 0;
		// -- COLLECTING COLOR INFORMATION
		// color = file_buf[i] << 24 | file_buf[i + 1] << 16 | file_buf[i + 2] << 8;
		// color = file_buf[i + 2] << 24 | file_buf[i + 1] << 16 | file_buf[i] << 8;
		// color = file_buf[i + 2] << 16 | file_buf[i + 1] << 8 | file_buf[i];
		color = file_buf[i + 2] | file_buf[i + 1] << 8 | file_buf[i] << 16;
		// -------------------------------
		i += 4;
		mlxu_pixel_put_buffer(visual, px->x, px->y, color);
		advance_px(px, visual->active.win->size.x);
		if (px->y == visual->active.win->size.y && px->x == visual->active.win->size.x)
		{
			prt_frameinfo(dinfo, px);
			mlxu_flush_buffer(visual);
			usleep(3000000);
			px->x = 0;
			px->y = 0;
		}
	}
}
