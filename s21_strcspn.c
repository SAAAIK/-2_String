#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  char str2_alphabet[128];
  for (s21_size_t i = 0; i < 128; i++) {
    str2_alphabet[i] = 0;
  }
  for (s21_size_t i = 0; str2[i] != '\0'; i++) {
    str2_alphabet[(int)str2[i]] = 1;
  }
  s21_size_t res = 0;
  for (; str1[res] != '\0' && !str2_alphabet[(int)str1[res]]; res++)
    ;
  return res;
}