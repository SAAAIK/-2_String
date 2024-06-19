#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t res = -1;
  if (needle[0] != '\0') {
    for (s21_size_t i = 0; haystack[i] != '\0'; i++) {
      for (s21_size_t j = 0; needle[j] != '\0' && res == -1ul; j++) {
        if (needle[j + 1] == '\0' && needle[j] == haystack[i + j])
          res = i;
        else if (needle[j] != haystack[i + j]) {
          break;
        }
      }
    }
  } else {
    res = 0;
  }

  return (res == -1ul) ? S21_NULL : (char *)(haystack + res);
}