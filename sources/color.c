#include "../include/Retro_MFA.h"

int get_color(t_byte* buf, ssize_t offset, t_sprite* sprite)
{
  uint32_t color = 0;
  if (sprite->col_encoding == 4100) {
    uint8_t b = buf[offset];
    uint8_t g = buf[offset + 1];
    uint8_t r = buf[offset + 2];
    color = (r << 16) | (g << 8) | b;
  }
  else {
    uint16_t col_encoded = build_2_bytes_int(&buf[offset]);
    uint8_t r = ((col_encoded >> 10) & 0x1F) * 255 / 31;
    uint8_t g = ((col_encoded >> 5)  & 0x1F) * 255 / 31;
    uint8_t b = ( col_encoded        & 0x1F) * 255 / 31;
    color = (0xFF << 24) | (r << 16) | (g << 8) | b;
  }
  return (color);
}
