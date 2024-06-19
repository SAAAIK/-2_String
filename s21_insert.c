#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_str = NULL;
  if (str && src) {
    if (start_index <= s21_strlen(src)) {
      s21_size_t len_src = s21_strlen(src);
      s21_size_t len_str = s21_strlen(str);
      s21_size_t len_new = len_src + len_str;
      new_str = calloc(len_src + len_str + 1, sizeof(char));

      for (s21_size_t i = 0; i < start_index; i++) {
        new_str[i] = src[i];
      }
      for (s21_size_t i = 0; i < len_str; i++) {
        new_str[start_index + i] = str[i];
      }
      for (s21_size_t i = 0; i < len_new - start_index - len_str; i++) {
        new_str[start_index + len_str + i] = src[start_index + i];
      }
      new_str[len_new] = '\0';
    }
  } else if (str) {
    if ((int)s21_strlen(str) > 0) {
      new_str = calloc(s21_strlen(str) + 1, sizeof(char));
      s21_strcpy(new_str, str);
      new_str[s21_strlen(str)] = '\0';
    }
  }
  return new_str;
}