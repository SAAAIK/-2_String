#include "s21_string.h"

int s21_parser(const char *string, va_list args, char *result) {
  int index = 0;
  char temp[1024] = "";
  char c;
  int res_index = 0;
  char percent_index;
  while ((c = string[index]) !=
         '\0') {  //%[флаги][ширина][.точность][длина]спецификатор
    //проверка на первый символ - % и последний символ - спецификатор
    if (c == '%') {
      percent_index = index;
      format_sprintf format = {0};
      index++;
      s21_parser_flags(&format, string, &index);
      s21_parser_width(&format, string, &index);
      s21_parser_precision(&format, string, &index);
      s21_parser_length(&format, string, &index);
      if (s21_parser_specifier(&format, string, &index)) {
        s21_param_result(args, format, temp, &res_index);
      } else {
        for (int i = 0; i < index + 1 - percent_index; i++) {
          temp[res_index] = string[percent_index + i];
          res_index++;
        }
      }
    } else {
      temp[res_index] = string[index];
      res_index++;
    }
    index++;
  }
  temp[res_index] = '\0';
  for (int i = 0; i < res_index + 1; i++) {
    result[i] = temp[i];
  }
  return res_index;
}

void s21_parser_flags(format_sprintf *format, const char *string, int *index) {
  char *format_flags = "-+ #0";
  char flag;
  while (s21_strchr(format_flags, (flag = string[*index])) != NULL) {
    switch (flag) {
      case '-':
        format->flags.minus = true;
        break;
      case '+':
        format->flags.plus = true;
        break;
      case ' ':
        format->flags.space = true;
        break;
      case '#':
        format->flags.hash_sign = true;
        break;
      case '0':
        format->flags.null_sign = true;
        break;
    }
    *index = *index + 1;
  }
}

void s21_parser_width(format_sprintf *format, const char *string, int *index) {
  char str_number[1024] = {0};
  int str_index = 0;
  if (string[*index] == '*') {
    format->width.star_sign = true;
    *index = *index + 1;
  }
  while (string[*index] >= 48 && string[*index] <= 57) {  // ascii
    str_index++;
    *index = *index + 1;
  }
  s21_strncpy((char *)str_number, string + *index - str_index, str_index);
  if (str_index != 0) {
    format->width.number = s21_str_to_d(str_number);
  }
}

void s21_parser_length(format_sprintf *format, const char *string, int *index) {
  char *format_specifiers = "hLl";
  char spec = string[*index];
  if (s21_strchr(format_specifiers, spec) != NULL) {
    switch (string[*index]) {
      case 'h':
        format->length.h = true;
        break;
      case 'L':
        format->length.L = true;
        break;
      case 'l':
        format->length.l = true;
        break;
    }
    *index = *index + 1;
  }
}

void s21_parser_precision(format_sprintf *format, const char *string,
                          int *index) {
  char str_number[1024] = {0};
  int str_index = 0;
  if (string[*index] == '.') {
    format->precision.point = true;
    *index = *index + 1;
  }
  if (string[*index] == '*') {
    format->precision.star_sign = true;
    *index = *index + 1;
  }
  while (string[*index] >= 48 && string[*index] <= 57) {  // ascii
    str_index++;
    *index = *index + 1;
  }
  s21_strncpy((char *)str_number, string + *index - str_index, str_index);
  if (str_index != 0) {
    format->precision.number = s21_str_to_d(str_number);
  }
}

int s21_parser_specifier(format_sprintf *format, const char *string,
                         int const *index) {
  char *format_specifiers = "cdieEfgGosuxXpn%";
  char spec = string[*index];
  int res = 0;
  if (s21_strchr(format_specifiers, spec) != NULL) {
    switch (spec) {
      case 'c':
        format->specifiers.c = true;
        break;
      case 'd':
        format->specifiers.d = true;
        break;
      case 'e':
        format->specifiers.e = true;
        break;
      case 'E':
        format->specifiers.E = true;
        break;
      case 'f':
        format->specifiers.f = true;
        break;
      case 'g':
        format->specifiers.g = true;
        break;
      case 'G':
        format->specifiers.G = true;
        break;
      case 'o':
        format->specifiers.o = true;
        break;
      case 's':
        format->specifiers.s = true;
        break;
      case 'u':
        format->specifiers.u = true;
        break;
      case 'x':
        format->specifiers.x = true;
        break;
      case 'X':
        format->specifiers.X = true;
        break;
      case 'p':
        format->specifiers.p = true;
        break;
      case '%':
        format->specifiers.percent = true;
        break;
    }
    res = 1;
  }
  return res;
}

void s21_d_to_buff(va_list args, format_sprintf format, char *temp, int *flag) {
  length_sprintf_format_ length_temp = format.length;
  long long c = 0;
  if (length_temp.h) {
    c = (short)va_arg(args, int);
  } else if (length_temp.l) {
    c = va_arg(args, long long);
  } else {
    c = va_arg(args, int);
  }
  s21_d_to_str(c, temp);
  s21_precision(temp, format, 'd');
  s21_flags(temp, format);
  s21_width(temp, format);
  if (format.precision.number == 0 && format.precision.point && c == 0) {
    *flag = 1;
    if (format.width.number != 0)
      temp[s21_strlen(temp) - 1] = ' ';
    else
      temp[s21_strlen(temp) - 1] = '\0';
  }
}

void s21_f_to_buff(va_list args, format_sprintf format, char *temp) {
  length_sprintf_format_ length_temp = format.length;
  long double c = 0;
  if (length_temp.L)
    c = va_arg(args, long double);
  else
    c = va_arg(args, double);

  int round_index = 0;
  round_index = (!format.precision.point) ? 6 : format.precision.number;

  s21_f_to_str(c, temp, round_index, format);
  s21_precision(temp, format, 'f');
  s21_flags(temp, format);
  s21_width(temp, format);
}

void s21_s_to_buff(va_list args, format_sprintf format, char *temp, int *flag) {
  int len = 0;
  char *c = NULL;
  c = va_arg(args, char *);
  if (c == NULL) {
    len = 6;
    char buff[] = "(null)\0";
    s21_strcpy(temp, buff);
  } else {
    len = (int)s21_strlen(c);
    for (int i = 0; i < len; i++) {
      temp[i] = c[i];
    }
  }
  temp[len] = '\0';
  s21_precision(temp, format, 's');
  if (c == NULL && format.precision.number < 6 && format.precision.point) {
    temp[0] = '\0';
  }
  s21_width(temp, format);
  if (s21_strlen(temp) == 0) {
    *flag = 1;
  }
  if (format.precision.number == 0 && format.precision.point && c == 0) {
    *flag = 1;
    if (format.width.number != 0)
      temp[s21_strlen(temp) - 1] = ' ';
    else
      temp[s21_strlen(temp) - 1] = '\0';
  }
}

void s21_xXp_to_buff(va_list args, format_sprintf format, char *temp,
                     int *flag) {
  specifiers_sprintf_format specs_temp = format.specifiers;
  length_sprintf_format_ length_temp = format.length;
  unsigned long long c = 0;
  if (specs_temp.p) {
    c = va_arg(args, unsigned long long);
    format.flags.hash_sign = true;
  } else if (length_temp.h) {
    c = (unsigned short)va_arg(args, unsigned int);
  } else if (length_temp.l) {
    c = va_arg(args, unsigned long long);
  } else {
    c = va_arg(args, unsigned int);
  }

  if (specs_temp.p && c == 0) {
    char buff[] = "(nil)\0";
    s21_strcpy(temp, buff);
    s21_width(temp, format);
  } else {
    s21_oupx_to_str(c, temp, format, 16);
    s21_precision(temp, format, 'x');
    s21_flags(temp, format);
    s21_width(temp, format);
    if (format.precision.number == 0 && format.precision.point && c == 0) {
      *flag = 1;
      if (format.width.number != 0)
        temp[s21_strlen(temp) - 1] = ' ';
      else
        temp[s21_strlen(temp) - 1] = '\0';
    }
  }
}

void s21_gG_to_buff(va_list args, format_sprintf format, char *temp) {
  length_sprintf_format_ length_temp = format.length;
  specifiers_sprintf_format specs_temp = format.specifiers;
  long double c = 0;
  if (length_temp.L)
    c = va_arg(args, long double);
  else
    c = va_arg(args, double);

  if (specs_temp.g || specs_temp.G)
    s21_g_to_str(c, temp, format);
  else {
    int round_index = (!format.precision.point) ? 6 : format.precision.number;
    s21_e_to_str(c, temp, round_index, format);
  }
  s21_flags(temp, format);
  s21_width(temp, format);
}

void s21_ou_to_buff(va_list args, format_sprintf format, char *temp,
                    int *flag) {
  specifiers_sprintf_format specs_temp = format.specifiers;
  length_sprintf_format_ length_temp = format.length;
  unsigned long long c = 0;
  int base = 10;
  if (specs_temp.o) base = 8;

  if (length_temp.h)
    c = (unsigned short)va_arg(args, unsigned int);
  else if (length_temp.l) {
    c = va_arg(args, unsigned long long);
  } else {
    c = va_arg(args, unsigned int);
  }
  s21_oupx_to_str(c, temp, format, base);
  s21_precision(temp, format, 'x');
  s21_flags(temp, format);
  s21_width(temp, format);
  if (format.precision.number == 0 && format.precision.point && c == 0) {
    *flag = 1;
    if (format.width.number != 0)
      temp[s21_strlen(temp) - 1] = ' ';
    else
      temp[s21_strlen(temp) - 1] = '\0';
  }
}

void s21_c_to_buff(va_list args, format_sprintf format, char *temp) {
  char c = va_arg(args, int);
  temp[0] = c;
  temp[1] = '\0';
  s21_width(temp, format);
}

int s21_str_to_d(char const *str) {
  int result = 0;
  int sign = 1;
  int i = 0;

  if (str[0] == '-') {
    sign = -1;
    i = 1;
  }
  for (; str[i] != '\0'; i++) {
    result = result * 10 + (str[i] - '0');
  }
  return result * sign;
}

int s21_is_digit(char c) {
  if (c >= 48 && c <= 57) return 1;
  return 0;
}

int s21_d_len(unsigned long long int num) {
  int length = 0;
  if (num == 0) return 1;
  while (num != 0) {
    num = num / 10;
    length++;
  }
  return length;
}

void s21_d_to_str(long long int num, char *res) {
  int sign_st = 0;
  int flag = 0;
  if (num < 0) {
    sign_st = 1;
    num = -num;
  }
  if (num == LONG_MIN) {
    num = 9223372036854775807;
    flag = 1;
  }
  int i = 0;
  char temp[1024] = "";
  if (num == 0) {
    res[0] = '0';
    res[1] = '\0';
    return;
  }
  while (num > 0) {
    int digit;
    digit = num % 10;
    temp[i] = digit + '0';
    num /= 10;
    i++;
  }
  temp[i + 1] = '\0';
  if (sign_st) res[0] = '-';
  for (int j = 0; j <= i; j++) {
    if (sign_st)
      res[j + 1] = temp[i - j - 1];
    else
      res[j] = temp[i - j - 1];
  }
  if (flag) {  // MAX_LONG_LONG
    res[i] = '8';
  }
}

void s21_oupx_to_str(unsigned long long num, char *res, format_sprintf format,
                     int base) {
  char temp[1024];
  int count = 0;

  if (base == 0) return;
  if (num == 0) {
    res[0] = '0';
    res[1] = '\0';
    return;
  }

  while (num != 0) {
    int remainder = 0;
    remainder = num % base;
    if (remainder < 10) {
      temp[count] = remainder + '0';
    } else {
      if (format.specifiers.x || format.specifiers.p)
        temp[count] = remainder + 87;                         // a-f
      if (format.specifiers.X) temp[count] = remainder + 55;  // A-F
    }
    num /= base;
    count++;
  }
  for (int i = 0; i < count; i++) {
    res[i] = temp[count - i - 1];
  }
  res[count] = '\0';
}

int s21_f_len(long double x) {
  int count = 0;
  if (x == 0 || x == 1) return 1;
  while (x >= 1) {
    count++;
    x /= 10.0L;
  }
  return count;
}

void s21_f_to_str(long double num, char *res, int round_index,
                  format_sprintf format) {
  int minus = 0;
  long double drob_, int_ = 0.0L;
  char temp[1024] = "";
  if (num < 0) {
    num = -num;
    minus = 1;
  }
  drob_ = modfl(num, &int_);
  int len_drob = round_index;
  for (int i = 0; i < len_drob; i++) {
    drob_ *= 10.0L;
  }
  if ((int)(fmodl(drob_ * 10.0L, 10.0L)) >= 5) {
    drob_ = drob_ + 1.0L;
  }
  if ((s21_f_len(drob_) > len_drob && len_drob != 0) ||
      (len_drob == 0 && (int)(fmodl(drob_ * 10.0L, 10.0L)) >= 5)) {
    int_ = int_ + 1.0L;
  }
  int len_int = s21_f_len(int_);
  for (int i = 0; i < len_drob; i++) {
    int digit = (int)(fmodl(drob_, 10.0L));
    temp[i] = digit + '0';
    drob_ /= 10.0L;
  }
  if (round_index != 0 || format.flags.hash_sign) {
    temp[len_drob] = '.';
  }
  for (int i = 0; i < len_int; i++) {
    int digit = (int)(fmodl(int_, 10.0L));
    temp[i + len_drob + 1] = digit + '0';
    int_ /= 10.0L;
  }
  if (minus) res[0] = '-';
  for (int i = 0; i < len_drob + len_int + 1; i++) {
    res[i + minus] = temp[len_drob + len_int - i];
  }
  res[minus + len_drob + len_int + 1] = '\0';
}

void s21_e_to_str(long double num, char *res, int round_index,
                  format_sprintf format) {
  bool e_minus = false, sign_minus = false;
  char temp[1024] = "";
  int len, count = 0;
  if (num < 0) {
    sign_minus = true;
    num = -num;
  }
  while (num < 1 && num != 0) {
    e_minus = true;
    num *= 10.0;
    count++;
  }
  while (num > 10) {
    num /= 10.0;
    count++;
  }
  s21_f_to_str(num, temp, round_index, format);
  len = s21_strlen(temp);
  if (temp[0] == '1' && temp[1] == '0') {
    for (int i = 1; i < (int)s21_strlen(temp); i++) {
      temp[i] = temp[i + 1];
    }
    temp[s21_strlen(temp)] = '\0';
    len = s21_strlen(temp);
    count++;
  }
  s21_strcpy(res, temp);
  res[len] = 'e';
  if (format.specifiers.E || format.specifiers.G) res[len] = 'E';
  if (e_minus)
    res[len + 1] = '-';
  else
    res[len + 1] = '+';
  if (count < 100) {
    res[len + 2] = (count / 10) + '0';
    res[len + 3] = (count % 10) + '0';
  } else {
    res[len + 2] = (count / 100) + '0';
    res[len + 3] = (count / 10 % 10) + '0';
    res[len + 4] = (count % 10) + '0';
  }
  res[s21_strlen(res)] = '\0';
  if (sign_minus) {
    for (int i = s21_strlen(res); i > 0; i--) {
      res[i] = res[i - 1];
    }
    res[0] = '-';
  }
}

/* Пусть P равно точности, если она не равна нулю, 6, если точность не указана,
или 1, если точность равна нулю. Затем, если преобразование со стилем E имеет
показатель X: Если P > X ≥ −4, то преобразование будет со стилем f и точностью P
− (X + 1). В противном случае преобразование будет со стилем e и точностью P
− 1. */
void s21_g_to_str(long double num, char *res, format_sprintf format) {
  int p, index = 0, x = 0;
  long double temp_int;
  char temp_str[1024] = {0};
  int prec_number = format.precision.number;
  int is_prec = format.precision.point;
  if (num == INFINITY) {
    char temp[] = "inf\0";
    s21_strcpy(res, temp);
    return;
  }
  if (isnan(num)) {
    char temp[] = "nan\0";
    s21_strcpy(res, temp);
    return;
  }
  if (num == 0) {
    char temp[] = "0\0";
    s21_strcpy(res, temp);
    return;
  }
  if (is_prec && prec_number != 0)
    p = prec_number;
  else if (is_prec)
    p = 1;
  else
    p = 6;
  temp_int = num;
  if (temp_int < 0) {
    temp_int = -temp_int;
  }
  while (temp_int < 1) {
    temp_int *= 10.0;
    x--;
  }
  while (temp_int > 10) {
    temp_int /= 10.0;
    x++;  // показатель X
  }
  if (p > x && x >= -4) {
    p = p - (x + 1);
    s21_f_to_str(num, temp_str, p, format);
    index = s21_strlen(temp_str) - 1;
    while (temp_str[index] == '0' && !format.flags.hash_sign && p != 0) {
      temp_str[index] = '\0';
      index--;
    }
    if (temp_str[index] == '.' && !format.flags.hash_sign)
      temp_str[index] = '\0';
    else
      temp_str[index + 1] = '\0';
  } else {
    int temp_len;
    p = p - 1;
    s21_e_to_str(num, temp_str, p, format);
    index =
        s21_strlen(temp_str) - 1 - 2 -
        (abs(x) < 100 ? 2 : s21_d_len(x));  // -2 (e- or e+) -x (010, 310, ...)
    temp_int = index;
    temp_len = s21_strlen(temp_str);
    while (temp_str[index] == '0' && !format.flags.hash_sign) {
      temp_str[index] = '\0';
      index--;
    }
    if (temp_str[index] == '.' && !format.flags.hash_sign) {
      temp_str[index] = '\0';
      index--;
    }
    for (int i = temp_int + 1; i < temp_len; i++) {
      temp_str[index + 1] = temp_str[i];
      index++;
    }
    temp_str[index + 1] = '\0';
  }
  s21_strcpy(res, temp_str);
}

void s21_precision(char *res, format_sprintf format, char param) {
  int prec = 0;
  int form_prec = format.precision.number;
  if (!format.precision.point) return;
  if (s21_strchr("diouxX", param) != NULL) {
    char temp[1024] = "";
    int minus = res[0] == '-' ? 1 : 0;
    int len = (int)s21_strlen(res) - minus;
    if (form_prec > len) prec = form_prec - (int)s21_strlen(res) + minus;
    for (int i = 0; i < len; i++) {
      temp[i] = res[i + minus];
    }
    if (minus) {
      res[0] = '-';
    }
    for (int i = 0; i < prec; i++) {
      res[i + minus] = '0';
    }
    for (int i = 0; i < len; i++) {
      res[prec + i + minus] = temp[i];
    }
    if (form_prec == 0 && param == '0') res[0] = '\0';
  }
  if (s21_strchr("eEf", param) != NULL) {
    prec = form_prec;
    if (form_prec != 0) {
      int index = 0;
      while (res[index] != '.') index++;
      res[index + prec + 1] = '\0';
    }
  }
  if (s21_strchr("s", param) != NULL) {
    res[form_prec] = '\0';
  }
  res[s21_strlen(res)] = '\0';
}

void s21_width(char *res, format_sprintf format) {
  char temp[1024] = "";
  char first_char_res = res[0];
  int len = (int)s21_strlen(res);
  int ww = format.width.number;
  if (ww <= len) return;
  if (format.flags.minus) {
    for (int i = 0; i < ww - len; i++) {
      res[i + len] = ' ';
    }
    res[ww] = '\0';
  } else {
    for (int i = 0; i < len; i++) {
      temp[i] = res[i];
    }
    for (int i = 0; i < ww - len; i++) {
      if (format.flags.null_sign && !format.specifiers.c &&
          !format.specifiers.s)
        res[i] = '0';
      else
        res[i] = ' ';
    }
    for (int i = 0; i < len; i++) {
      res[i + (ww - len)] = temp[i];
    }
    res[ww] = '\0';

    if (format.flags.null_sign && !format.specifiers.c &&
        !format.specifiers.s && !s21_is_digit(first_char_res)) {
      char temp_char = res[ww - len];
      res[ww - len] = res[0];
      res[0] = temp_char;
    }
  }
  res[s21_strlen(res)] = '\0';
}

void s21_flags(char *res, format_sprintf format) {
  flags_sprintf_format flag_temp = format.flags;
  if (format.flags.hash_sign && !(res[0] == '0' && res[1] == '\0')) {
    char buff[1024] = "";
    int deploy = 0;
    if (format.specifiers.p || format.specifiers.x || format.specifiers.X) {
      buff[0] = '0';
      buff[1] = 'x';
      if (format.specifiers.X) buff[1] = 'X';
      deploy = 2;
    }
    if (format.specifiers.o &&
        (format.precision.number < (int)s21_strlen(res))) {
      buff[0] = '0';
      deploy = 1;
    }
    s21_strcpy(buff + deploy, res);
    s21_strcpy(res, buff);
    res[s21_strlen(res)] = '\0';
  }
  if (flag_temp.plus || flag_temp.space) {
    char temp[1024] = "";
    bool minus = (res[0] == '-') ? 1 : 0;
    bool d_spec = format.specifiers.x || format.specifiers.X ||
                  format.specifiers.u || format.specifiers.o;
    s21_strcpy(temp, res);
    if (!minus && flag_temp.plus && !d_spec)
      res[0] = '+';
    else if (!minus && flag_temp.space && !d_spec)
      res[0] = ' ';
    if (minus || d_spec) {
      s21_strcpy(res, temp);
    } else {
      s21_strcpy(res + 1, temp);
    }
    res[s21_strlen(res)] = '\0';
  }
  res[s21_strlen(res)] = '\0';
}

void s21_param_result(va_list args, format_sprintf format, char *res,
                      int *res_index) {
  specifiers_sprintf_format specs_temp = format.specifiers;
  int flag = 0;
  char temp[1024] = "";
  if (format.width.star_sign) {
    format.width.number = va_arg(args, int);
  }
  if (format.precision.star_sign) {
    format.precision.number = va_arg(args, int);
  }
  if (specs_temp.percent) {
    temp[0] = '%';
    temp[1] = '\0';
  }
  if (specs_temp.c) {
    s21_c_to_buff(args, format, temp);
  } else if (specs_temp.d) {
    s21_d_to_buff(args, format, temp, &flag);
  } else if (specs_temp.f) {
    s21_f_to_buff(args, format, temp);
  } else if (specs_temp.s) {
    s21_s_to_buff(args, format, temp, &flag);
  } else if (specs_temp.x || specs_temp.X || specs_temp.p) {
    s21_xXp_to_buff(args, format, temp, &flag);
  } else if (specs_temp.g || specs_temp.G || specs_temp.e || specs_temp.E) {
    s21_gG_to_buff(args, format, temp);
  } else if (specs_temp.o || specs_temp.u) {
    s21_ou_to_buff(args, format, temp, &flag);
  }
  for (size_t i = 0; i < s21_strlen(temp); i++) {
    res[*res_index] = temp[i];
    *res_index = *res_index + 1;
  }
  if (s21_strlen(temp) == 0 && !flag) {
    res[*res_index] = temp[0];
    *res_index = *res_index + 1;
  }
}

int s21_sprintf(char *str, const char *string, ...) {
  va_list args;
  va_start(args, string);
  int c = s21_parser(string, args, str);
  va_end(args);
  return c;
}
