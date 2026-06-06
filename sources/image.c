#include "Retro_MFA.h"

static void prt_32byte(t_byte* buf, ssize_t adress)
{
	int bytes = 1;
	printf("bytes 0x%.6X (%zu): ", (unsigned int) adress, adress);
	for (int i = adress; i < adress + ASSET_HEADER_WHITE2; i++)
	{
		printf("%.2x ", buf[i]);
		if (bytes % 8 == 0)
			printf("  ");
		bytes++;
	}
	printf("\n");
}

static uint16_t build_short(t_byte* buf)
{
	uint16_t number = 
		buf[1] << 8 |
		buf[0];
	return (number);
}

void get_asset_data(t_data* data, ssize_t adress)
{
	if (adress + ASSET_HEADER_WHITE2 > data->bytes_read)
		return ;
	uint16_t width, height, b2;
	prt_32byte(data->file_buf, adress);
	// BASED ON white2.mfa !!
	// bytes 1 & 2 are unclear
	t_byte* buf = &data->file_buf[adress];
	b2 = build_short(buf);
	printf("\tbytes as integer | 1 | 2 | 21 | >>>> | %i | %i | %i |\n",
		*buf, *(buf + 1), b2);
	// bytes 3 to 8 are always same
	// bytes 9 to 12 sometimes different - unclear
	buf += 8;
	printf("\tbytes as integer | 9 | 10 | 11 | 12 | >>>> | %i | %i | %i | %i |\n",
		*buf, *(buf + 1), *(buf + 2), *(buf + 3));
	buf += 4;
	// bytes 13 & 14: width
	width = *buf | *(buf + 1) << 8 ;
	buf += 2;
	// bytes 15 & 16: height
	height = *buf | *(buf + 1) << 8 ;
	buf += 2;
	printf("\tdimensions: %ix%i\n", width, height);
	// bytes 17 & 18: always same unclear... color coding?
	b2 = *buf | *(buf + 1) << 8;
	printf("\tbytes as integer | 17 | 18 | 1817 | >>>> | %i | %i | %i |\n",
		*buf, *(buf + 1), b2);
	buf += 2;
	// bytes remaining: all zeros.. filler?
}
