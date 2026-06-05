#include "Retro_MFA.h"
#include "fenster.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024 * 1024

#define W 1920
#define H 1080

void read_file(int fd, char *file_buf) {
  read(fd, file_buf, BUFFER_SIZE);
}

void open_window(char *file_buf) {
  (void)file_buf;
  uint32_t win_buf[W * H];
  struct fenster f = { .title = "hello", .width = W, .height = H, .buf = win_buf };
  fenster_open(&f);
  while (fenster_loop(&f) == 0) {
    for (int i = 0; i < W; i++) {
      for (int j = 0; j < H; j++) {
        fenster_pixel(&f, i, j) = rand();
      }
    }
  }
  fenster_close(&f);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    dprintf(STDERR_FILENO, "usage: ./Retro_MFA \"FILE.mfa\"\n");
    return 1;
  }
  if (strlen(argv[1]) < 5 || strncmp(argv[1] + strlen(argv[1]) - 4, ".mfa", 4) != 0) {
    dprintf(STDERR_FILENO, "usage: ./Retro_MFA \"FILE.mfa\"\n");
    return 1;
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    dprintf(STDERR_FILENO, "couldn't open file %s\n", argv[1]);
    return 1;
  }
  char *file_buf = calloc(1, BUFFER_SIZE);
  if (!file_buf) {
    dprintf(STDERR_FILENO, "memory failure\n");
    return 1;
  }
  read_file(fd, file_buf);
  open_window(file_buf);
  free(file_buf);
  return 0;
}