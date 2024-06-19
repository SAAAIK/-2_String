#include "s21_string.h"

/**
 * Copies up characters from the string pointed to, by src to dest
 */
char *s21_strcpy(char *dest, const char *src) {
  int i = 0;
  for (; src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}