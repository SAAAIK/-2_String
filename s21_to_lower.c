#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *our_str2 = S21_NULL;
  if (str) {
    our_str2 = calloc((s21_strlen(str) + 1), sizeof(char));
  }
  if (our_str2) {
    s21_strncpy(our_str2, str, s21_strlen(str) + 1);
    for (char *i = our_str2; *i; i++) {
      if (*i >= 'A' && *i <= 'Z') {
        *i += 32;
      }
    }
  }
  return (void *)our_str2;
}