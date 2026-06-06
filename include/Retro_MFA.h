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

#define W 300//320//1920
#define H 640//480//1080
#define TITLE ".mfa Inspector"

#define FRAME_SLEEPTIME 5000000

#define MFA_FILEID 0x4d, 0x4d, 0x46, 0x32
#define MAGIC_1 0x04, 0x00, 0x00, 0x00
#define MAGIC_2 0x03, 0x00, 0x00, 0x00
#define MAGIC_3 0xF8, 0x00, 0x00, 0x00
#define EMPTY_FOUR_BYTES 0x00, 0x00, 0x00, 0x00
#define MFA_ENDOFHEADER 0x00, 0xF8, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00

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

typedef struct s_data
{
	t_byte file_buf[BUFFER_SIZE];
	int fd;
	ssize_t bytes_read;
	ssize_t offset;
	t_mlxu visual;
	t_mlxu_2d px;
	t_debug dinfo;
} t_data;

// -----------------------------------------------------------------------------
// prototypes
// -----------------------------------------------------------------------------

bool init(t_data *data, char *file);
bool read_file(t_data *data);
int cleanup(t_data *data, int res, char *err_msg);

// -----------------------------------------------------------------------------
// raw data experiment
// -----------------------------------------------------------------------------

void visual_test(t_data *data);
void prt_frameinfo(t_debug* dinfo);
void rnd_frame(t_data *data);

#endif /* RETRO_MFA_H */
