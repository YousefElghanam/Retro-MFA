#include "../include/Retro_MFA.h"

// all the bytes read must be sure that they CAN read the buffer
// for writing the assets to mlx window, the loop ensures that enough data
//    can be read before anything begins
// for finding the assets, also the outer loop ensures that the full header
//    can be read before anything begins
// there are no other calls left

uint32_t build_4_bytes_int(t_byte *buf)
{
	uint32_t number = 
		buf[3] << 24 |
		buf[2] << 16 |
		buf[1] << 8 |
		buf[0];
	return ((uint32_t) number);
}

uint16_t build_2_bytes_int(t_byte* buf)
{
	uint16_t number = 
		buf[1] << 8 |
		buf[0];
	return (number);
}
