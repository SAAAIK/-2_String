#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, size_t n) {
  unsigned char *destp = (unsigned char *)dest;
  unsigned char *srcp = (unsigned char *)src;

  for (size_t i = 0; i < n; i++) destp[i] = srcp[i];
  return (void *)dest;
}