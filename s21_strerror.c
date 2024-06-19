#include "s21_string.h"

char *s21_strerror(int errnum) {
  char *ptr = S21_NULL;
  if (errnum > ERR_MIN && errnum < ERR_MAX) {
    ERROR_ARRAY;
    ptr = (char *)errlist[errnum];
  } else {
    static char part1[33] = {0};
    static char part2[33] = {0};
    part1[0] = '\0';
    part2[0] = '\0';
    s21_errnum_tostring(part2, errnum);
    s21_strcat(part1, ERROR);
    s21_strcat(part1, part2);
    ptr = part1;
  }
  return ptr;
}
