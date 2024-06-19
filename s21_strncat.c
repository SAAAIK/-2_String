#include "s21_string.h"
// Добавляет строку, на которую указывает src, в конец строки,
//  на которую указывает dest, длиной до n символов.
char *s21_strncat(char *dest, const char *src, size_t n) {
  char *new_str = NULL;
  if (n > 0) {
    int new_len = s21_strlen(dest) + n + 1;
    new_str = calloc(new_len, sizeof(char));
    s21_strcpy(new_str, dest);
    for (int i = s21_strlen(dest), j = 0; j < n; j++, i++) {
      new_str[i] = src[j];
    }
    new_str[s21_strlen(dest) + n] = '\0';
  } else {
    new_str = calloc(s21_strlen(dest) + 1, sizeof(char));
    s21_strcpy(new_str, dest);
    new_str[s21_strlen(dest)] = '\0';
  }
  return new_str;
}