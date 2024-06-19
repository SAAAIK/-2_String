#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *OLDS;
  char *token = S21_NULL;
  if (str == S21_NULL)
    str = OLDS;
  else
    OLDS = S21_NULL;

  str += s21_strspn(str, delim);
  if (*str == '\0') {
    OLDS = str;
    token = S21_NULL;
  } else {
    token = str;
    str += s21_strcspn(token, delim);
    if (*str == '\0') {
      // This token finishes the string
      OLDS = s21_strchr(token, '\0');
    } else {
      // Terminate the token and make OLDS point past it
      *str = '\0';
      OLDS = str + 1;
    }
  }
  return token;
}