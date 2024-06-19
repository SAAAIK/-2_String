#include "s21_string.h"

int s21_trim_finder(const char *src, const char *trim_chars, int spot) {
  spot -= 1;
  int res = 0;
  int chars_len = s21_strlen(trim_chars);
  for (int i = 0; i < chars_len; i++) {
    if (src[spot] == trim_chars[i]) {
      res++;
    }
  }
  return res > 0 ? 1 : 0;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *trim = NULL;
  if (src) {
    if (trim_chars) {
      int str_entry = 1, str_tail = (int)s21_strlen(src);
      while (s21_trim_finder(src, trim_chars, str_entry)) str_entry += 1;
      if (str_entry != str_tail) {
        while (s21_trim_finder(src, trim_chars, str_tail)) str_tail -= 1;
      }
      int len_new = str_tail - str_entry;
      trim = calloc(len_new + 2, sizeof(char));
      if (trim) {
        for (int i = str_entry - 1, j = 0; i <= str_tail; i++, j++) {
          trim[j] = src[i];
        }
        trim[len_new + 1] = '\0';
      } else {
        trim = "";
      }
    } else {
      trim = s21_trim(src, "\t\n");
    }
  }
  return (char *)trim;
}