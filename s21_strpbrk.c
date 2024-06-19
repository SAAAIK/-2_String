#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char str2_alphabet[128] = {0};
  for (s21_size_t i = 0; str2[i] != '\0'; i++) {
    str2_alphabet[(int)str2[i]] = 1;
  }
  s21_size_t res = 0;
  for (; str1[res] != '\0' && !str2_alphabet[(int)str1[res]]; res++)
    ;
  return (str1[res] == '\0') ? S21_NULL : (char *)(str1 + res);
}