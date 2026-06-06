#include "Retro_MFA.h"
#include "math.h"

static void prt_32byte(t_byte* buf, ssize_t adress)
{
	int bytes = 1;
	printf("bytes 0x%.6X (%zu): ", (unsigned int) adress, adress);
	for (int i = adress; i < adress + ASSET_HEADER_SIZE; i++)
	{
		printf("%.2x ", buf[i]);
		if (bytes % 8 == 0)
			printf("  ");
		bytes++;
	}
	printf("\n");
}


static void get_asset_data(t_data* data, ssize_t adress, t_sprite* sprite)
{
	if (adress + ASSET_HEADER_SIZE > data->bytes_read)
		return ;
	uint16_t b2;
	prt_32byte(data->file_buf, adress);
	// BASED ON white2.mfa !!
	// bytes 1 & 2 are unclear
	t_byte* buf = &data->file_buf[adress];
	b2 = build_2_bytes_int(buf);
	printf("\tbytes as integer | 1 | 2 | 21 | >>>> | %i | %i | %i |\n",
		*buf, *(buf + 1), b2);
	// bytes 3 to 8 are always same
	buf += 8;
	// bytes 9 to 12 4 bytes to get the num of bytes for color data
	sprite->size = build_4_bytes_int(buf);
	printf("\tsize: %i\n", sprite->size);
	// printf("\tbytes as integer | 9 | 10 | 11 | 12 | >>>> | %i | %i | %i | %i |\n",
	// 	*buf, *(buf + 1), *(buf + 2), *(buf + 3));
	buf += 4;
	// bytes 13 & 14: width
	sprite->width = build_2_bytes_int(buf);
	buf += 2;
	// bytes 15 & 16: height
	sprite->height = build_2_bytes_int(buf);
	buf += 2;
	printf("\tdimensions: %ix%i\n", sprite->width, sprite->height);
	// bytes 17 & 18: always same unclear... color coding?
	b2 = *buf | *(buf + 1) << 8;
	printf("\tbytes as integer | 17 | 18 | 1817 | >>>> | %i | %i | %i |\n",
		*buf, *(buf + 1), b2);
	buf += 2;
	// bytes remaining: all zeros.. filler?
}

void single_sprite_test(t_data* data, ssize_t adress)
{
	t_sprite sprite;
	t_mlxu_2d px = {0,0,0};
	static t_mlxu_2d off; // to put them next to each other
	uint16_t col_encoded;
	ssize_t frame;
	int color;
	static int ymax;
	get_asset_data(data, adress, &sprite);
	frame = sprite.width * sprite.height * 2; // 2 is only for here
	adress += 32;
	// put everything next to each other
	if (ymax < sprite.height - 1)
	 ymax = sprite.height;
	if (off.x + sprite.width >= data->visual.active.win->size.x)
	{
		off.x = 0;
		off.y += ymax;
		if (off.y + sprite.height >= data->visual.active.win->size.y)
			exit(1); // FIXME
	}
	// ONE image
	for (ssize_t i = 0; i < frame; i += 2)
	{
		color = 0;
		col_encoded = 0;
		col_encoded = build_2_bytes_int(&data->file_buf[adress + i]);
		color = col_encoded | data->file_buf[adress + i + frame] << 24;
		mlxu_pixel_put_buffer(&data->visual, px.x + off.x, px.y + off.y, color);
		advance_px(&px, sprite.width - 1);
		if (px.y == sprite.height - 1 && px.x == sprite.width - 1)
		{
			px.x = 0;
			px.y = 0;
			off.x += sprite.width;
		}
	}
}
