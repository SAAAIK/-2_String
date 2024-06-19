#include "../s21_string.h"

int main() {
  char s1[30] = "hello, world!";
  char s2[] = "hELLO, WORLD!";
  s21_size_t num = 7;
  char *s33243 = s21_insert(s1, s2, num);
  if (s33243) free(s33243);

  char s1_2[30] = "";
  char s3_2[] = "";
  char *s2_2 = s21_insert(s1_2, s3_2, num);
  if (s2_2) free(s2_2);

  char *s1_3 = S21_NULL;
  char s3_3[] = "";
  char *s2_3 = s21_insert(s1_3, s3_3, num);
  if (s2_3) free(s2_3);

  char s1_4[30] = "abc";
  char s3_4[] = "333";
  s21_size_t num_4 = 10;
  char *s2_4 = s21_insert(s1_4, s3_4, num_4);
  if (s2_4) free(s2_4);

  char s1_5[] = "wtf";
  char *s3_5 = S21_NULL;
  s21_size_t num_5 = 0;
  char *s2_5 = s21_insert(s1_5, s3_5, num_5);
  if (s2_5) free(s2_5);

  char str_1[] = "Hello, world!";
  int ch1_1 = ' ';
  s21_memchr(str_1, ch1_1, s21_strlen(str_1));

  char str_2[] = "Hello, world!";
  int ch_2 = 101;
  s21_memchr(str_2, ch_2, s21_strlen(str_2));

  char str_3[] = "Hello, world!";
  int ch_3 = '1';
  s21_memchr(str_3, ch_3, s21_strlen(str_3));

  char str_4[] = "Hello, world!";
  int ch_4 = 65;
  s21_memchr(str_4, ch_4, s21_strlen(str_4));

  char str_5[] = "69917020";
  int ch_5 = '\0';
  s21_memchr(str_5, ch_5, s21_strlen(str_5));

  char s3[] = "Hello, world!";
  char s4[] = "Hello, world!";
  s21_size_t n1 = 7;
  s21_memcmp(s3, s4, n1);

  char s5[] = "Hello, world!";
  char s6[] = "Good";
  s21_size_t n2 = 4;
  s21_memcpy(s5, s6, n2);

  char s7[] = "Hello, world!";
  int ch = 80;
  s21_size_t n3 = 7;
  s21_memset(s7, ch, n3);

  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 9;
  int b = 10;
  int c = 17;
  int d = 66;
  int e = 124;
  s21_sprintf(str2, str3, a, b, c, d, e);

  char str4[] = "\0testing_this";
  char str5[100] = "thi00s";
  s21_strcpy(str5, str4);

  char format[] = "%c %c \t%c";
  char str6[] = "\t\n\n  123 \n  \t";
  char c11, c12, c13;
  s21_sscanf(str6, format, &c11, &c12, &c13);

  char s8[100] = "Hell0000\0";
  char s9[] = "";
  s21_strcat(s8, s9);

  char s10[] = "Hello, world!";
  int ch2 = 33;
  s21_strchr(s10, ch2);

  char s11[] = "u";
  char s12[] = "\0";
  s21_strcmp(s11, s12);

  char s13[] = "69917020";
  char s14[] = "69917020";
  s21_strcspn(s13, s14);

  int n4 = -1;
  s21_strerror(n4);

  char str7[] =
      "213145346758697808-9704=3524-1309876289403-5=6576=432=-31044253=60931 "
      "21";
  s21_strlen(str7);

  char s15[30] = "Hello, world!";
  char s16[] = "\n\0\\d\f\\g\7";
  s21_size_t n5 = 3;
  char *new_result = s21_strncat(s15, s16, n5);
  if (new_result) free(new_result);

  char s17[] = "Hello, world!";
  char s18[] = "Hello, world!";
  s21_size_t n6 = 14;
  s21_strncmp(s17, s18, n6);

  char s19[20] = "Hello, world!";
  char s20[] = "Good";
  s21_size_t n7 = 5;
  s21_strncpy(s19, s20, n7);

  char s21[] = "Hello, world!";
  char s22[] = "!";
  s21_strpbrk(s21, s22);

  char s23[] = "Hello, world!";
  int ch3 = 'h';
  s21_strrchr(s23, ch3);

  char s24[] = "123456789";
  char s25[] = "123";
  s21_strspn(s24, s25);

  char s26[] = "Hello, world!";
  char s27[] = "Hello, world!";
  s21_strstr(s26, s27);

  char s28[] = "\0Hello, world!";
  char s29[] = "\0";
  s21_strtok(s28, s29);

  char s30[30] = "hello, world!";
  char *ns1 = s21_to_lower(s30);
  free(ns1);

  char s31[30] = "hello, world!";
  char *ns2 = s21_to_upper(s31);
  free(ns2);

  char s32[30] = "-?hello, world!";
  char s33[] = "!?-";
  char *ns3 = s21_trim(s32, s33);
  if (ns3) free(ns3);
  return 0;
}