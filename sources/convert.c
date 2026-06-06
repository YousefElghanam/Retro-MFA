#include "Retro_MFA.h"

uint32_t build_4_bytes_int(t_byte *buf)
{
	// if (bytes_read < *offset + 4)
	// 	exit(1); // FIXME this needs to be somehow done outside perhaps
	uint32_t number = 
		buf[3] << 24 |
		buf[2] << 16 |
		buf[1] << 8 |
		buf[0];
	printf("[int] raw bytes:  0x%.2X%.2X%.2X%.2X\n"
		   "      converted number: %i\n",
		buf[0], buf[1], buf[2], buf[3], number);
	return ((uint32_t) number);
}

uint16_t build_2_bytes_int(t_byte* buf)
{
	uint16_t number = 
		buf[1] << 8 |
		buf[0];
	return (number);
}
