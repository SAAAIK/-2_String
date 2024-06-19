#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *rez = NULL;
  unsigned char *char_str = (unsigned char *)str;
  while (n-- && !rez) {
    if (*char_str == (char)c) {
      rez = char_str;
    }
    char_str++;
  }
  return rez;
}