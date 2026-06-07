#include "../include/Retro_MFA.h"
#include <stdint.h>

static t_sprite get_asset_data(t_byte* buf)
{
	t_sprite s;
	s.size = build_4_bytes_int(&buf[8]);
	s.width = build_2_bytes_int(&buf[12]);
	s.height = build_2_bytes_int(&buf[14]);
	s.col_encoding = build_2_bytes_int(&buf[16]);
	return (s);
}

static ssize_t find_assets(t_byte *file_buf, ssize_t bytes_read, ssize_t *offset, t_sprite* sprite)
{
	uint8_t sequence[6] = {ASSET_HEADER_SEQUENCE};
	t_byte *buf;
	static int assets_found;
	static bool new_cycle;
	if (new_cycle)
	{
		assets_found = 0;
		new_cycle = false;
	}
	while (*offset + ASSET_HEADER_SIZE < bytes_read)
	{
		buf = &file_buf[*offset];
		if (memcmp(&buf[2], sequence, 6) == 0)
		{
			// check MUST FILLED bytes for valid asset
			if (buf[0] && buf[1] && buf[8] && buf[9] &&
				buf[12] && buf[14] && buf[16] && buf[17])
			{
				*sprite = get_asset_data(buf);
				// if (sprite->width > 25 && sprite->height > 25)
				if (sprite->size > 2000 && sprite->size < 200000)
				{
					printf("  sprite @ 0x%.2X (%zu): %ix%i (%i bytes) color 0x%.2X\n",
						(unsigned int) *offset, *offset,
						sprite->width, sprite->height, sprite->size, sprite->col_encoding);
					assets_found++;
					(*offset) += 32;
					return (*offset);
				}
			}
		}
		(*offset)++;
	}
	printf("%s located %i valid headers\n", __FUNCTION__, assets_found);
	new_cycle = true;
	return (0);
}

static void update_img_offset(t_data* data, t_sprite* sprite, t_mlxu_2d* offset, int* ymax)
{
	// put everything next to each other
	if (*ymax < sprite->height - 1)
		*ymax = sprite->height;
	offset->x += SPACING;
	// check if NEXT image doesn't fit in the ROW anymore
	if (offset->x + sprite->width >= data->visual.active.win->size.x)
	{
		offset->x = SPACING;
		offset->y += *ymax + SPACING;
		*ymax = sprite->height;
	}
	// check if NEXT image doesn't fit in the WINDOW anymore
	if (offset->y + sprite->height >= data->visual.active.win->size.y)
	{
		printf("rendered %i images in %p\n",
			data->dinfo.images, data->visual.active.img_node);
		printf("  window buffer full, creating new buffer...\n");
		data->dinfo.images = 0;
		if (mlxu_setup_new_buffer(&data->visual) != 0)
			data->res = RES_ERR;
		offset->y = SPACING;
	}
	// printf("\tnew rendering offset: (%ix%i)\n", offset->x, offset->y);	
}

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

static void render_single_image(t_data* data, ssize_t adress, t_sprite* sprite)
{
	t_mlxu_2d px = {0,0,0};
	static t_mlxu_2d off = {SPACING, SPACING, 0}; // to put them next to each other
	ssize_t px_in_img;
	int color;
	static int ymax;
	px_in_img = sprite->width * sprite->height * (2 + (sprite->col_encoding == 4100));
	if (adress + px_in_img >= data->bytes_read)
		return ;
	update_img_offset(data, sprite, &off, &ymax);
	if (data->res != RES_OK)
    return ;
	for (ssize_t i = 0; i < px_in_img; i += (2 + (sprite->col_encoding == 4100)))
	{
		color = 0;
		color = get_color(data->file_buf, adress + i, sprite);
		mlxu_pixel_put_buffer(&data->visual, px.x + off.x, px.y + off.y, color);
		// for debugging, higlight last row in RED
		// if (px.y == sprite->height - 1)
		// 	mlxu_pixel_put_buffer(&data->visual, px.x + off.x, px.y + off.y, RED);
		advance_px(&px, sprite->width - 1);
	}
	// when rendering done for this image, adjust to the right by this image
	off.x += sprite->width;
	// adjust reading offset in buffer by this assets total read size
	data->offset += sprite->size;
	data->dinfo.images++;
}

void get_me_some_pretty_images(t_data* data)
{
	ssize_t addr = 0;
	t_sprite sprite = {0,0,0, 0};
	static t_mlxu_img *prev = NULL;
	if (data->res != RES_OK)
		return;
	while (data->res == RES_OK && data->offset < data->bytes_read)
	{
		addr = find_assets(data->file_buf, data->bytes_read, &data->offset, &sprite);
		if (addr == 0)
			break ;
		render_single_image(data, addr, &sprite);
	}
	// this counter can be lower, because find_assets doesn't care
	// if one full frame of the image can actually fit the window
	printf("rendered %i images in %p\n",
		data->dinfo.images, data->visual.active.img_node);
	// counting number of pages created
	if (prev != data->visual.active.img)
	{
		if (data->dinfo.images)
			data->dinfo.pages++;
		prev = data->visual.active.img;
	}
	// reset some stuff
	data->offset = 0;
	data->dinfo.images = 0;
}
