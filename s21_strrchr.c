#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  s21_size_t res = -1;
  s21_size_t i = 0;
  for (; str[i] != '\0'; i++) {
    if (str[i] == c) res = i;
  }
  if (str[i] == c) res = i;
  return (res == -1ul) ? S21_NULL : (char *)(str + res);
}