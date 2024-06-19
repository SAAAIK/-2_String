#include "s21_string.h"

void *s21_memset(void *str, int c, size_t n) {
  unsigned char *pstr = (unsigned char *)str;
  for (size_t i = 0; i < n; i++) {
    pstr[i] = (char)c;
  }
  return (void *)pstr;
}