#include "s21_string.h"

void s21_errnum_tostring(char *str, int num) {
  int i, rem, len = 0, n;
  n = num;
  while (n != 0) {
    len++;
    n /= 10;
  }
  if (num >= 0) {
    for (i = 0; i < len; i++) {
      rem = num % 10;
      num = num / 10;
      str[len - (i + 1)] = rem + '0';
    }
  } else {
    len++;
    str[0] = '-';
    for (i = 0; i < len - 1; i++) {
      rem = num % 10;
      num = num / 10;
      str[len - (i + 1)] = rem + '0';
      if (i == len - 2) {
        str[len - (i + 1)] = (-1 * rem) + '0';
      }
    }
  }
  str[len] = '\0';
}