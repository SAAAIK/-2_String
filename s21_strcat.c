#include "s21_string.h"

/**
 * Concantinate source string into destination
 */
char *s21_strcat(char *destination, const char *source) {
  int last = s21_strlen(destination);
  int i = 0;
  while (source[i] != '\0') {
    destination[last] = source[i];
    i++;
    last++;
  }
  destination[last] = '\0';
  return destination;
}