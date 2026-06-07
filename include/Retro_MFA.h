#ifndef RETRO_MFA_H
#define RETRO_MFA_H

#include "lists.h"
#include "mlx_utils.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string.h> // memset
#include <unistd.h>

#define BUFFER_SIZE 1024 * 1024

#define W 900 // 320//1920
#define H 800 // 480//1080
#define TITLE ".mfa Inspector"

#define FRAME_SLEEPTIME 300

#define MFA_FILEID 0x4d, 0x4d, 0x46, 0x32
#define MAGIC_1 0x04, 0x00, 0x00, 0x00
#define MAGIC_2 0x03, 0x00, 0x00, 0x00
#define MAGIC_3 0xF8, 0x00, 0x00, 0x00
#define EMPTY_FOUR_BYTES 0x00, 0x00, 0x00, 0x00
#define MFA_ENDOFHEADER                                                        \
  0x00, 0xF8, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00

#define ASSET_HEADER_SEQUENCE 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
#define ASSET_HEADER_SIZE 32 // validated only with white2 & blue
#define ASSET_HEADER_POS_WIDTH 12
#define ASSET_HEADER_POS_HEIGHT 14
#define ASSET_FILLER 240
#define ASSET_COL_2BYTE 0x1006
#define ASSET_COL_3BYTE 0x1004

#define SPACING 8

#define DestroyNotify 17
#define NoEventMask 0L

#ifndef DEBUG
#define DEBUG 0
#endif

// -----------------------------------------------------------------------------
// data types
// -----------------------------------------------------------------------------

typedef uint8_t t_byte;

typedef enum e_state { RES_OK, RES_DONE, RES_ERR } t_state;

typedef struct s_debug {
  unsigned int frame;
  unsigned int pages;
  unsigned int images;
} t_debug;

typedef struct s_manual
{
	uint32_t byte0;
	ssize_t addr;
} t_manual;

typedef struct s_sprite {
  uint16_t width;
  uint16_t height;
  uint32_t size;
  uint16_t col_encoding; // 4100 for 3 byte per pixel // 4102 for 2 bytes per pixel
  uint16_t bytes_0_1;
  short	col_num_bytes;
} t_sprite;

typedef struct s_data {
  t_byte file_buf[BUFFER_SIZE];
  int fd;
  ssize_t bytes_read;
  ssize_t offset;
  t_mlxu visual;
  t_mlxu_2d px;
  t_debug dinfo;
  t_state res;
  t_manual manual[100];
} t_data;

// -----------------------------------------------------------------------------
// prototypes
// -----------------------------------------------------------------------------

bool init(t_data *data, char *file);
void read_file(t_data *data);
int keyhooks(int key, void *param);
void get_me_some_pretty_images(t_data *data);
int get_color(t_byte *buf, ssize_t offset, t_sprite *sprite);
uint16_t build_2_bytes_int(t_byte *buf);
uint32_t build_4_bytes_int(t_byte *buf);
void advance_px(t_mlxu_2d *px, int max_x);
void rnd_frame(t_data *data);
int cleanup(t_data *data, int res, char *err_msg);

#endif /* RETRO_MFA_H */
