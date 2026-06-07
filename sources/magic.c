#include "../include/Retro_MFA.h"
#include <stdint.h>

static t_sprite get_asset_data(t_byte* buf)
{
	t_sprite s;
	s.bytes_0_1 = build_2_bytes_int(&buf[0]);
	s.size = build_4_bytes_int(&buf[8]);
	s.width = build_2_bytes_int(&buf[12]);
	s.height = build_2_bytes_int(&buf[14]);
	s.col_encoding = build_2_bytes_int(&buf[16]);
	if (s.col_encoding == ASSET_COL_2BYTE)
		s.col_num_bytes = 2;
	else if (s.col_encoding == ASSET_COL_3BYTE)
		s.col_num_bytes = 3;
	else
		s.col_num_bytes = 2;
	return (s);
}

static void prt_header(int assets_found, t_byte *buf)
{
	printf("header %d: ", assets_found);
	for (int i=0; i < 32;i++)
	{
		printf("%.2X ", (uint16_t) buf[i]);
		if (i!=0 && i % 8 == 0)
			printf(" ");

	}
	printf("\n");
}

bool search_skip(t_manual *skip, t_byte *buf, ssize_t adress)
{
	ssize_t off = adress - 32; // has to be changed, because header is already added
	for (int i = 0; i < 1; i++)
	{
		printf("%s: addr %zu|%zu ::: bytes %X|%.2X%.2X%.2X%.2X\n",
			__FUNCTION__, off, skip[i].addr,
			skip[i].byte0, buf[off + 0], buf[off + 1], buf[off + 2], buf[off + 3]);
		if (off == skip[i].addr && memcmp(&buf[off], &skip[i].byte0, 4) == 0)
			return (true);
	}
	return (false);
}

bool search_alignment_flip(t_manual *alignment, t_byte *buf, ssize_t adress)
{
	ssize_t off = adress - 32; // has to be changed, because header is already added
	for (int i = 0; i < 1; i++)
	{
		printf("%s: addr %zu|%zu ::: bytes %X|%X%X%X%X\n",
			__FUNCTION__, off, alignment[i].addr,
			alignment[i].byte0, buf[off + 0], buf[off + 1], buf[off + 2], buf[off + 3]);
		if (off == alignment[i].addr && memcmp(&buf[off], &alignment[i].byte0, 4) == 0)
			return (true);
	}
	return (false);
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
			// check MUST FILLED bytes for valid asset - w/o get ALL assets
			// if (buf[0] && buf[1] && buf[8] && buf[9] &&
			// 	buf[12] && buf[14] && buf[16] && buf[17])
			{
				*sprite = get_asset_data(buf);
				// this helps to get rid of unknown encodings - can stay or go
				if (sprite->size > 1700 && sprite->size < 200000)
				{
					prt_header(assets_found, buf);
					printf("  sprite @ 0x%.2X (%zu): %ix%i (%i bytes) color 0x%.4X | leading 0x%.4X\n",
						(unsigned int) *offset, *offset,
						sprite->width, sprite->height, sprite->size,
						sprite->col_encoding, sprite->bytes_0_1);
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
	px_in_img = sprite->width * sprite->height * sprite->col_num_bytes;
	if (adress + px_in_img >= data->bytes_read)
		return ;
	update_img_offset(data, sprite, &off, &ymax);
	if (data->res != RES_OK)
    	return ;
	short flip = -1;
	if (search_alignment_flip(data->manual_alignment, data->file_buf, adress))
		flip = 0;
	printf("offset: %zu | addr %zu\n",data->offset, adress);
	for (ssize_t i = 0; i < px_in_img; i += sprite->col_num_bytes)
	{
		color = 0;
		color = get_color(data->file_buf, adress + i, sprite);
		mlxu_pixel_put_buffer(&data->visual, px.x + off.x, px.y + off.y, color);
		advance_px(&px, sprite->width + flip);
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
	t_sprite sprite = {0,0,0,0,0,0};
	static t_mlxu_img *prev = NULL;
	if (data->res != RES_OK)
		return;
	while (data->res == RES_OK && data->offset < data->bytes_read)
	{
		addr = find_assets(data->file_buf, data->bytes_read, &data->offset, &sprite);
		if (addr == 0)
			break ;
		if (search_skip(data->manual_skip, data->file_buf, addr) == false)
			render_single_image(data, addr, &sprite);
		else
			data->offset += sprite.size;
		
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
