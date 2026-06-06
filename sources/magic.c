#include "Retro_MFA.h"

static ssize_t find_assets(t_byte *file_buf, ssize_t bytes_read, ssize_t *offset)
{
	uint8_t sequence[6] = {ASSET_HEADER_SEQUENCE};
	t_byte *buf;
	t_sprite sprite;
	static int assets_found = 0;
	// printf("%s: offset %zu bytes read %zu\n", __FUNCTION__, *og_off, bytes_read);
	for (; *offset + ASSET_HEADER_SIZE < bytes_read;
		 (*offset)++)
	{
		buf = &file_buf[*offset];
		if (memcmp(&buf[2], sequence, 6))
			continue;
		// printf("%s got a sequence\n", __FUNCTION__);
		// check MUST FILLED bytes for valid asset
		if (buf[0] && buf[1] && buf[8] && buf[9] && buf[12] && buf[14] && buf[16] && buf[17])
		{
			// printf("\tfound an asset\n");
			sprite.width = build_2_bytes_int(&buf[12]);
			sprite.height = build_2_bytes_int(&buf[14]);
			sprite.size = build_4_bytes_int(&buf[8]);
			// if (sprite.width > 25 && sprite.height > 25)
			if (sprite.size > 2000 && sprite.size < 200000)
			{
				printf("sprite data @0x%.2X: %ix%i (%i bytes)\n",
					(unsigned int) *offset, sprite.width, sprite.height, sprite.size);
				assets_found++;
				return (*offset);
			}
		}
	}
	printf("%s located %i valid headers\n", __FUNCTION__, assets_found);
	return (0);
}

int get_me_some_pretty_images(t_data* data)
{
	ssize_t addr = 0;
	// static ssize_t start;
	// if (start == 0)
	// 	start = data->offset;
	// data->offset = start;
	while (data->offset < data->bytes_read)
	{
		addr = find_assets(data->file_buf, data->bytes_read, &data->offset);
		if (addr == 0)
			break ;
		single_sprite_test(data, addr);
	}
	printf("rendered %i images\n", data->dinfo.images);
	rnd_frame(data);
	mlx_loop(data->visual.mlx_ptr);
	return (0);
}
