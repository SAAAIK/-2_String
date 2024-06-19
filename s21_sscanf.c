#include "s21_string.h"

void s21_get_tokens(token *tokens, int *tokens_count, char **format_pos,
                    va_list *argptr) {
  while (**format_pos != '\0') {
    token cur_token = {NULL, 0, 0, 0, 0};
    if (s21_check_space(**format_pos)) {
      s21_skip_spaces(format_pos);
      tokens[(*tokens_count)++].specifier = ' ';
    } else if (**format_pos == '%') {
      (*format_pos)++;
      s21_get_width(format_pos, &cur_token);
      s21_get_length(format_pos, &cur_token);
      tokens[*tokens_count] = cur_token;
      tokens[*tokens_count].specifier = **format_pos;
      if (tokens[*tokens_count].width_type != 2)
        tokens[(*tokens_count)++].address = va_arg(*argptr, void *);
      else
        (*tokens_count)++;
      (*format_pos)++;
    } else {
      int i = 0;
      while (**format_pos && !s21_check_space(**format_pos) &&
             **format_pos != '%') {
        tokens[*tokens_count].buff[i++] = **format_pos;
        (*format_pos)++;
      }
      tokens[*tokens_count].buff[i] = '\0';
      tokens[(*tokens_count)++].specifier = 'b';
    }
  }
}

void s21_skip_chars_in_buff(char **str_pos, char *buff, int *error) {
  s21_skip_spaces(str_pos);

  if (s21_strspn(*str_pos, buff) != s21_strlen(buff))
    *error = 1;
  else
    (*str_pos) = (*str_pos) + s21_strlen(buff);
}

void s21_get_length(char **format_pos, token *token) {
  if (**format_pos == 'h') {
    token->length = 1;
    (*format_pos)++;
    if (**format_pos == 'h') {
      token->length = 5;
      (*format_pos)++;
    }
  } else if (**format_pos == 'l') {
    token->length = 2;
    (*format_pos)++;
    if (**format_pos == 'l') {
      token->length = 3;
      (*format_pos)++;
    }
  } else if (**format_pos == 'L') {
    token->length = 4;
    (*format_pos)++;
  }
}

void s21_get_width(char **format_pos, token *token) {
  char *buff = malloc(100 * sizeof(char));
  char *start_format = *format_pos;
  int count_digits = 0;
  if (**format_pos == '*') {
    token->width_type = 2;
    (*format_pos)++;
  } else if (s21_is_digit(**format_pos)) {
    token->width_type = 1;
    while (s21_is_digit(**format_pos)) {
      count_digits++;
      (*format_pos)++;
    }
    s21_memcpy(buff, start_format, count_digits);
    buff[count_digits] = '\0';
    token->width = atoi(buff);
  }
  free(buff);
}

void s21_write_tokens_to_vars(const token *tokens, int tokens_count,
                              char *str_pos, int *result) {
  int tok_pos = 0;
  char *start_pos = str_pos;
  int error = 0;
  while (tok_pos != tokens_count && !error) {
    token cur_token = tokens[tok_pos];
    if (cur_token.specifier == 'c')
      s21_write_char_to_var(cur_token, &str_pos, result);
    if (cur_token.specifier == 'd')
      s21_write_int_to_var(cur_token, &str_pos, result, &error);
    if (cur_token.specifier == 'i')
      s21_write_8_10_16_to_var(cur_token, &str_pos, result, &error);
    if (cur_token.specifier == 'f' || cur_token.specifier == 'g' ||
        cur_token.specifier == 'G' || cur_token.specifier == 'e' ||
        cur_token.specifier == 'E')
      s21_write_float_to_var(cur_token, &str_pos, result, &error);
    if (cur_token.specifier == 's')
      s21_write_str_to_var(cur_token, &str_pos, result);
    if (cur_token.specifier == 'o')
      s21_write_8_to_var(cur_token, &str_pos, result, &error);
    if (cur_token.specifier == 'x' || cur_token.specifier == 'X' ||
        cur_token.specifier == 'p')
      s21_write_16_to_var(cur_token, &str_pos, result, &error);
    if (cur_token.specifier == 'u')
      s21_write_unsigned_int_to_var(cur_token, &str_pos, result, &error);
    if (cur_token.specifier == 'n')
      s21_write_count_symbs_to_var(cur_token, str_pos, start_pos);
    if (cur_token.specifier == ' ') s21_skip_spaces(&str_pos);
    if (cur_token.specifier == 'b')
      s21_skip_chars_in_buff(&str_pos, cur_token.buff, &error);
    if (cur_token.specifier == '%') s21_skip_percent(&str_pos, &error);
    tok_pos++;
  }
}

void s21_skip_percent(char **str_pos, int *error) {
  if (**str_pos == '%')
    (*str_pos)++;
  else
    *error = 1;
}

void s21_write_count_symbs_to_var(token cur_token, const char *str_pos,
                                  const char *start_pos) {
  long long int res = (long long int)(str_pos - start_pos);
  s21_convert_int(res, cur_token);
}

void s21_write_8_10_16_to_var(token cur_token, char **str_pos, int *result,
                              int *error) {
  s21_skip_spaces(str_pos);
  if (s21_strspn(*str_pos, "0x") == 2 || s21_strspn(*str_pos, "0X") == 2 ||
      s21_strspn(*str_pos + 1, "0x") == 2 ||
      s21_strspn(*str_pos + 1, "0X") == 2)
    s21_write_16_to_var(cur_token, str_pos, result, error);
  else if (s21_strspn(*str_pos, "0") == 1 || s21_strspn(*str_pos + 1, "0") == 1)
    s21_write_8_to_var(cur_token, str_pos, result, error);
  else if (s21_strspn(*str_pos, "+-0123456789"))
    s21_write_int_to_var(cur_token, str_pos, result, error);
}

void s21_write_8_to_var(token cur_token, char **str_pos, int *result,
                        int *error) {
  s21_skip_spaces(str_pos);
  char *buff = malloc(100 * sizeof(char));
  char *start_str = *str_pos;
  int count_symbs = 0;
  int sign = 1;
  int sign_flag = 0;
  int sign_error = 0;
  *error = 1;
  if (**str_pos == '-' || **str_pos == '+') {
    if (**str_pos == '-') sign = -1;
    sign_flag = 1;
    (*str_pos)++;
    start_str++;
    if (cur_token.width_type == 1) cur_token.width--;
  }
  if (**str_pos == '-' || **str_pos == '+') sign_error = 1;
  while (s21_strchr("01234567", **str_pos) != NULL && **str_pos != '\0') {
    if (count_symbs >= cur_token.width && cur_token.width_type == 1) break;
    count_symbs++;
    (*str_pos)++;
  }
  if (!(sign_error ||
        (sign_flag && (cur_token.width < 1 && cur_token.width_type == 1)))) {
    s21_memcpy(buff, start_str, count_symbs);
    buff[count_symbs] = '\0';
    unsigned long int res = strtoull(buff, NULL, 8);
    if (count_symbs != 0 && cur_token.width_type != 2) {
      (*result)++;
      s21_convert_unsigned_int(res, cur_token, sign);
    }
    *error = 0;
  }
  free(buff);
}

void s21_write_unsigned_int_to_var(token cur_token, char **str_pos, int *result,
                                   int *error) {
  s21_skip_spaces(str_pos);
  char *buff = malloc(100 * sizeof(char));
  char *start_str = *str_pos;
  int count_symbs = 0;
  int sign = 0;
  int sign_error = 0;
  *error = 1;
  if (**str_pos == '-' || **str_pos == '+') {
    (*str_pos)++;
    sign = 1;
    count_symbs++;
  }
  if (**str_pos == '-' || **str_pos == '+') sign_error = 1;
  while (s21_strchr("0123456789", **str_pos) != NULL && **str_pos != '\0') {
    if (count_symbs >= cur_token.width && cur_token.width_type == 1) break;
    count_symbs++;
    (*str_pos)++;
  }
  if (!(sign_error ||
        sign && (cur_token.width <= 1 && cur_token.width_type == 1))) {
    s21_memcpy(buff, start_str, count_symbs);
    buff[count_symbs] = '\0';
    unsigned long long int res = strtoull(buff, NULL, 10);
    if (count_symbs != 0 && cur_token.width_type != 2) {
      s21_convert_unsigned_int(res, cur_token, 1);
      (*result)++;
    }
    *error = 0;
  }
  free(buff);
}

void s21_write_16_to_var(token cur_token, char **str_pos, int *result,
                         int *error) {
  s21_skip_spaces(str_pos);
  char *buff = malloc(100 * sizeof(char));
  char *start_str = *str_pos;
  int count_symbs = 0;
  int sign = 1;
  int sign_flag = 0;
  int sign_error = 0;
  *error = 1;
  if (**str_pos == '-' || **str_pos == '+') {
    if (**str_pos == '-') sign = -1;
    sign_flag = 1;
    (*str_pos)++;
    start_str++;
    if (cur_token.width_type == 1) cur_token.width--;
  }
  if (**str_pos == '-' || **str_pos == '+') sign_error = 1;
  while (s21_strchr("0xX0123456789abcdefABCDEF", **str_pos) != NULL &&
         **str_pos != '\0') {
    if (count_symbs >= cur_token.width && cur_token.width_type == 1) break;
    count_symbs++;
    (*str_pos)++;
  }
  if (!(sign_error ||
        (sign_flag && (cur_token.width < 1 && cur_token.width_type == 1)))) {
    s21_memcpy(buff, start_str, count_symbs);
    buff[count_symbs] = '\0';
    unsigned long int res = strtoull(buff, NULL, 16);
    if (count_symbs != 0 && cur_token.width_type != 2) {
      s21_convert_unsigned_int(res, cur_token, sign);
      (*result)++;
    }
    *error = 0;
  }
  free(buff);
}

void s21_write_float_to_var(token cur_token, char **str_pos, int *result,
                            int *error) {
  s21_skip_spaces(str_pos);

  char *buff = malloc(100 * sizeof(char));
  char *start_str = *str_pos;
  int count_symbs = 0;
  int dot = 0;
  int sign = 0;
  int sign_error = 0;
  *error = 1;
  if (**str_pos == '-' || **str_pos == '+') {
    sign = 1;
    count_symbs++;
    (*str_pos)++;
  }
  if (**str_pos == '-' || **str_pos == '+') sign_error = 1;
  while (s21_strchr(".0123456789eE+-NnaAifIF", **str_pos) != NULL &&
         **str_pos != '\0') {
    if ((**str_pos == '.' && dot) ||
        (count_symbs >= cur_token.width && cur_token.width_type == 1))
      break;
    if (**str_pos == '.') dot = 1;
    count_symbs++;
    (*str_pos)++;
  }
  if (!(sign_error ||
        sign && (cur_token.width <= 1 && cur_token.width_type == 1))) {
    s21_memcpy(buff, start_str, count_symbs);
    buff[count_symbs] = '\0';
    long double res = strtold(buff, NULL);
    if (cur_token.width_type != 2 && count_symbs != 0 &&
        !(isalpha(*buff) && res == 0)) {
      s21_convert_float(res, cur_token);
      (*result)++;
    }
    *error = 0;
  }
  free(buff);
}

void s21_write_str_to_var(token cur_token, char **str_pos, int *result) {
  s21_skip_spaces(str_pos);
  char *buff = malloc(100 * sizeof(char));
  char *start_str = *str_pos;
  int count_symbs = 0;
  while (!s21_check_space(**str_pos) && **str_pos != '\0') {
    if (count_symbs >= cur_token.width && cur_token.width_type == 1) break;
    count_symbs++;
    (*str_pos)++;
  }
  if (cur_token.width_type != 2 && count_symbs != 0) {
    s21_memcpy(buff, start_str, count_symbs);
    buff[count_symbs] = '\0';
    s21_strcpy((char *)cur_token.address, buff);
    (*result)++;
  }
  free(buff);
}

void s21_write_int_to_var(token cur_token, char **str_pos, int *result,
                          int *error) {
  s21_skip_spaces(str_pos);
  char *buff = malloc(100 * sizeof(char));
  char *start_str = *str_pos;
  int count_symbs = 0;
  int sign = 0;
  int sign_error = 0;
  *error = 1;
  if (**str_pos == '-' || **str_pos == '+') {
    sign = 1;
    count_symbs++;
    (*str_pos)++;
  }
  if (**str_pos == '-' || **str_pos == '+') sign_error = 1;
  while (s21_is_digit(**str_pos) && **str_pos != '\0') {
    if (count_symbs >= cur_token.width && cur_token.width_type == 1) break;
    count_symbs++;
    (*str_pos)++;
  }
  if (!(sign_error ||
        sign && (cur_token.width <= 1 && cur_token.width_type == 1))) {
    s21_memcpy(buff, start_str, count_symbs);
    buff[count_symbs] = '\0';
    long long int res = strtoll(buff, NULL, 10);
    if (count_symbs != 0 && cur_token.width_type != 2) {
      s21_convert_int(res, cur_token);
      (*result)++;
    }
    *error = 0;
  }
  free(buff);
}

void s21_convert_unsigned_int(unsigned long long int res, token cur_token,
                              int sign) {
  if (cur_token.length == 0)
    *(unsigned int *)cur_token.address = sign * (unsigned int)res;
  if (cur_token.length == 1)
    *(unsigned short int *)cur_token.address = sign * (unsigned short int)res;
  if (cur_token.length == 2)
    *(unsigned long int *)cur_token.address = sign * (unsigned long int)res;
  if (cur_token.length == 3)
    *(unsigned long long int *)cur_token.address =
        sign * (unsigned long long int)res;
  if (cur_token.length == 5)
    *(unsigned char *)cur_token.address = sign * (unsigned char)res;
}

void s21_convert_float(long double res, token cur_token) {
  if (cur_token.length == 0) *(float *)cur_token.address = (float)res;
  if (cur_token.length == 2) *(double *)cur_token.address = (double)res;
  if (cur_token.length == 4)
    *(long double *)cur_token.address = (long double)res;
}

void s21_convert_int(long long int res, token cur_token) {
  if (cur_token.length == 0) *(int *)cur_token.address = (int)res;
  if (cur_token.length == 1) *(short int *)cur_token.address = (short int)res;
  if (cur_token.length == 2) *(long int *)cur_token.address = (long int)res;
  if (cur_token.length == 3)
    *(long long int *)cur_token.address = (long long int)res;
  if (cur_token.length == 5) *(char *)cur_token.address = (char)res;
}

void s21_write_char_to_var(token cur_token, char **str_pos, int *result) {
  if (cur_token.width_type != 2) {
    *(char *)cur_token.address = **str_pos;
    (*result)++;
  }
  (*str_pos)++;
}

int s21_check_space(char ch) {
  int res = ch == ' ' || ch == '\n' || ch == '\t';
  return res;
}

void s21_skip_spaces(char **pos) {
  while (s21_check_space(**pos) && **pos) {
    (*pos)++;
  }
}

int s21_check_EOS_string(const char *str) {
  int EOS_string = -1;
  for (int i = 0; str[i]; i++) {
    if (!s21_check_space(str[i]) && str[i] != '\0') {
      EOS_string = 0;
      break;
    }
  }
  return EOS_string;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list argptr;
  va_start(argptr, format);
  int result = 0;
  int EOS_str = s21_check_EOS_string(str);
  int EOS_format = s21_check_EOS_string(format);

  if (!EOS_str && !EOS_format) {
    char *str_pos = (char *)str;
    char *format_pos = (char *)format;
    token tokens[1000];
    int tokens_count = 0;

    s21_get_tokens(tokens, &tokens_count, &format_pos, &argptr);
    s21_write_tokens_to_vars(tokens, tokens_count, str_pos, &result);

    va_end(argptr);
  } else if (EOS_format == -1) {
    result = 0;
  } else {
    result = -1;
  }

  return result;
}