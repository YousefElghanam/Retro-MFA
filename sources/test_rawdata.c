#include "../include/Retro_MFA.h"

void advance_px(t_mlxu_2d* px, int max_x)
{
	if (px->x == max_x)
	{
		px->x = 0;
		px->y++;
	}
	else
		px->x++;
}

void visual_test(t_data *data)
// void visual_test(t_byte* file_buf, t_mlxu* visual, t_mlxu_2d* px, t_debug* dinfo)
{
	int color;
	t_byte *buf = data->file_buf;
	printf("rendering ... starting at offset %zu (0x%.2X)\n",
		data->offset, (unsigned int) data->offset);
	for (ssize_t i = data->offset; i + 2 < data->bytes_read;)
	{
		data->dinfo.pixels++;
		color = 0;
		// -- COLLECTING COLOR INFORMATION
		// color = buf[i] << 24 | buf[i + 1] << 16 | buf[i + 2] << 8;
		// color = buf[i + 2] << 24 | buf[i + 1] << 16 | buf[i] << 8;
		// color = buf[i + 2] << 16 | buf[i + 1] << 8 | buf[i];
		color = buf[i + 2] | buf[i + 1] << 8 | buf[i] << 16;
		// -------------------------------
		i += 4;
		mlxu_pixel_put_buffer(&data->visual, data->px.x, data->px.y, color);
		advance_px(&data->px, data->visual.active.win->size.x);
		if (data->px.y == data->visual.active.win->size.y &&
			data->px.x == data->visual.active.win->size.x)
		{
			rnd_frame(data);
			data->px.x = 0;
			data->px.y = 0;
		}
	}
}
