#ifndef RETRO_MFA_H
#define RETRO_MFA_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // memset
#include "mlx_utils.h"

#define BUFFER_SIZE 1024 * 1024

#define W 320//1920
#define H 480//1080

#ifndef DEBUG
# define DEBUG 0
#endif

// -----------------------------------------------------------------------------
// data types
// -----------------------------------------------------------------------------

typedef uint8_t t_byte;

typedef struct s_debug
{
	unsigned int frame;
	unsigned int pixels;
} t_debug;

// -----------------------------------------------------------------------------
// raw data experiment
// -----------------------------------------------------------------------------

void visual_test(t_byte* file_buf, t_mlxu* visual, t_mlxu_2d* px, t_debug* dinfo);
void prt_frameinfo(t_debug* dinfo, t_mlxu_2d* last_px);

#endif /* RETRO_MFA_H */
