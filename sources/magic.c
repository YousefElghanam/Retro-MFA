#include "Retro_MFA.h"

static t_sprite get_asset_data(t_byte* buf)
{
	t_sprite s;
	s.size = build_4_bytes_int(&buf[8]);
	s.width = build_2_bytes_int(&buf[12]);
	s.height = build_2_bytes_int(&buf[14]);
	return (s);
}

static ssize_t find_assets(t_byte *file_buf, ssize_t bytes_read, ssize_t *offset, t_sprite* sprite)
{
	uint8_t sequence[6] = {ASSET_HEADER_SEQUENCE};
	t_byte *buf;
	static int assets_found = 0;
	// FIXME this currently gets interrupted too soon, when buffer is fully read but file is not
	// FIXME could be fixed together with the list idea for the mlx imagebuffers
	// TODO also requires asset detection (size based) to be adjusted by filename or something
	//		or different header sequence - blue looks like i get all individual frames of an asset
	for (; *offset + ASSET_HEADER_SIZE < bytes_read;
		 (*offset)++)
	{
		buf = &file_buf[*offset];
		if (memcmp(&buf[2], sequence, 6))
			continue;
		// check MUST FILLED bytes for valid asset
		if (buf[0] && buf[1] && buf[8] && buf[9] && buf[12] && buf[14] && buf[16] && buf[17])
		{
			*sprite = get_asset_data(buf);
			// if (sprite->width > 25 && sprite->height > 25)
			if (sprite->size > 2000 && sprite->size < 200000)
			{
				printf("sprite data @0x%.2X (%zu): %ix%i (%i bytes)\n",
					(unsigned int) *offset, *offset,
					sprite->width, sprite->height, sprite->size);
				assets_found++;
				(*offset) += 32;
				return (*offset);
			}
		}
	}
	printf("%s located %i valid headers\n", __FUNCTION__, assets_found);
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
		*ymax = 0;
		// check if NEXT image doesn't fit in the WINDOW anymore
		if (offset->y + sprite->height >= data->visual.active.win->size.y)
		{
			printf("window buffer full, creating new buffer...\n");
			// FIXME error check
			mlxu_setup_new_buffer(&data->visual);
			offset->y = SPACING;
		}
	}
	
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

static void render_single_image(t_data* data, ssize_t adress, t_sprite* sprite)
{
	t_mlxu_2d px = {0,0,0};
	static t_mlxu_2d off = {SPACING, SPACING, 0}; // to put them next to each other
	ssize_t px_in_img;
	int color;
	static int ymax;
	px_in_img = sprite->width * sprite->height * 2; // TODO 2 is only for here
	update_img_offset(data, sprite, &off, &ymax);
	// ONE image
	for (ssize_t i = 0; i < px_in_img; i += 2)
	{
		color = 0;
		if (adress + i >= data->bytes_read)
		{
			data->offset += sprite->size;
			return ;
		}
		color = get_color(data->file_buf, adress + i);
		mlxu_pixel_put_buffer(&data->visual, px.x + off.x, px.y + off.y, color);
		advance_px(&px, sprite->width - 1);
		if (px.y == sprite->height - 1 && px.x == sprite->width - 1)
		{
			px.x = 0;
			px.y = 0;
			off.x += sprite->width;
		}
	}
	data->dinfo.images++;
	data->offset += sprite->size;
}

int get_me_some_pretty_images(t_data* data)
{
	ssize_t addr = 0;
	t_sprite sprite = {0,0,0};
	while (data->offset < data->bytes_read)
	{
		addr = find_assets(data->file_buf, data->bytes_read, &data->offset, &sprite);
		if (addr == 0)
			break ;
		// FIXME find_assets doesn't trigger "nothing found" for all files
		render_single_image(data, addr, &sprite);
	}
	printf("rendered %i images\n", data->dinfo.images);
	data->offset = 0;
	data->dinfo.images = 0;
	return (0);
}
