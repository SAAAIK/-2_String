#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
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