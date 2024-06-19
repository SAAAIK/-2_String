#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  unsigned char *p_str1 = (unsigned char *)str1;
  unsigned char *p_str2 = (unsigned char *)str2;
  int rez = 0;

  while (n--) {
    if (*p_str1 != *p_str2) {
      rez = (*p_str1 > *p_str2) ? 1 : -1;
      break;
    }
    p_str1++;
    p_str2++;
  }
  return rez;
}