#ifndef S21_STRING_H
#define S21_STRING_H

typedef long unsigned s21_size_t;

#define S21_NULL (void *)0

#define BUFF_SIZE 4096

#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct token {
  void *address;
  int width;
  int width_type;
  int length;
  char specifier;
  char buff[1024];
} token;

typedef struct {
  bool minus;
  bool plus;
  bool space;
  bool hash_sign;
  bool null_sign;
} flags_sprintf_format;

typedef struct {
  bool c;
  bool d;
  bool i;
  bool e;
  bool E;
  bool f;
  bool g;
  bool G;
  bool o;
  bool s;
  bool u;
  bool x;
  bool X;
  bool p;
  bool n;
  bool percent;
} specifiers_sprintf_format;

typedef struct {
  int number;
  bool star_sign;
} width_sprintf_format;

typedef struct {
  int number;
  bool point;
  bool star_sign;
} precision_sprintf_format_;

typedef struct {
  bool h;
  bool l;
  bool L;
} length_sprintf_format_;

typedef struct {
  int size;
  flags_sprintf_format flags;
  specifiers_sprintf_format specifiers;
  width_sprintf_format width;
  precision_sprintf_format_ precision;
  length_sprintf_format_ length;
} format_sprintf;

#ifdef __APPLE__
#define E_FLAG 0
#define ERR_MAX 107
#define ERR_MIN -1
#define STRERR_MAX 70
#define ERROR "Unknown error: "
#define ERROR_ARRAY                                                           \
  char errlist[107][70] = {"Undefined error: 0",                              \
                           "Operation not permitted",                         \
                           "No such file or directory",                       \
                           "No such process",                                 \
                           "Interrupted system call",                         \
                           "Input/output error",                              \
                           "Device not configured",                           \
                           "Argument list too long",                          \
                           "Exec format error",                               \
                           "Bad file descriptor",                             \
                           "No child processes",                              \
                           "Resource deadlock avoided",                       \
                           "Cannot allocate memory",                          \
                           "Permission denied",                               \
                           "Bad address",                                     \
                           "Block device required",                           \
                           "Resource busy",                                   \
                           "File exists",                                     \
                           "Cross-device link",                               \
                           "Operation not supported by device",               \
                           "Not a directory",                                 \
                           "Is a directory",                                  \
                           "Invalid argument",                                \
                           "Too many open files in system",                   \
                           "Too many open files",                             \
                           "Inappropriate ioctl for device",                  \
                           "Text file busy",                                  \
                           "File too large",                                  \
                           "No space left on device",                         \
                           "Illegal seek",                                    \
                           "Read-only file system",                           \
                           "Too many links",                                  \
                           "Broken pipe",                                     \
                           "Numerical argument out of domain",                \
                           "Result too large",                                \
                           "Resource temporarily unavailable",                \
                           "Operation now in progress",                       \
                           "Operation already in progress",                   \
                           "Socket operation on non-socket",                  \
                           "Destination address required",                    \
                           "Message too long",                                \
                           "Protocol wrong type for socket",                  \
                           "Protocol not available",                          \
                           "Protocol not supported",                          \
                           "Socket type not supported",                       \
                           "Operation not supported",                         \
                           "Protocol family not supported",                   \
                           "Address family not supported by protocol family", \
                           "Address already in use",                          \
                           "Can't assign requested address",                  \
                           "Network is down",                                 \
                           "Network is unreachable",                          \
                           "Network dropped connection on reset",             \
                           "Software caused connection abort",                \
                           "Connection reset by peer",                        \
                           "No buffer space available",                       \
                           "Socket is already connected",                     \
                           "Socket is not connected",                         \
                           "Can't send after socket shutdown",                \
                           "Too many references: can't splice",               \
                           "Operation timed out",                             \
                           "Connection refused",                              \
                           "Too many levels of symbolic links",               \
                           "File name too long",                              \
                           "Host is down",                                    \
                           "No route to host",                                \
                           "Directory not empty",                             \
                           "Too many processes",                              \
                           "Too many users",                                  \
                           "Disc quota exceeded",                             \
                           "Stale NFS file handle",                           \
                           "Too many levels of remote in path",               \
                           "RPC struct is bad",                               \
                           "RPC version wrong",                               \
                           "RPC prog. not avail",                             \
                           "Program version wrong",                           \
                           "Bad procedure for program",                       \
                           "No locks available",                              \
                           "Function not implemented",                        \
                           "Inappropriate file type or format",               \
                           "Authentication error",                            \
                           "Need authenticator",                              \
                           "Device power is off",                             \
                           "Device error",                                    \
                           "Value too large to be stored in data type",       \
                           "Bad executable (or shared library)",              \
                           "Bad CPU type in executable",                      \
                           "Shared library version mismatch",                 \
                           "Malformed Mach-o file",                           \
                           "Operation canceled",                              \
                           "Identifier removed",                              \
                           "No message of desired type",                      \
                           "Illegal byte sequence",                           \
                           "Attribute not found",                             \
                           "Bad message",                                     \
                           "EMULTIHOP (Reserved)",                            \
                           "No message available on STREAM",                  \
                           "ENOLINK (Reserved)",                              \
                           "No STREAM resources",                             \
                           "Not a STREAM",                                    \
                           "Protocol error",                                  \
                           "STREAM ioctl timeout",                            \
                           "Operation not supported on socket",               \
                           "Policy not found",                                \
                           "State not recoverable",                           \
                           "Previous owner died",                             \
                           "Interface output queue is full"}
#elif __linux__

#define E_FLAG 1
#define ERR_MAX 134
#define ERR_MIN -1
#define STRERR_MAX 70
#define ERROR "Unknown error "
#define ERROR_ARRAY                                        \
  char errlist[134][70] = {                                \
      "Success",                                           \
      "Operation not permitted",                           \
      "No such file or directory",                         \
      "No such process",                                   \
      "Interrupted system call",                           \
      "Input/output error",                                \
      "No such device or address",                         \
      "Argument list too long",                            \
      "Exec format error",                                 \
      "Bad file descriptor",                               \
      "No child processes",                                \
      "Resource temporarily unavailable",                  \
      "Cannot allocate memory",                            \
      "Permission denied",                                 \
      "Bad address",                                       \
      "Block device required",                             \
      "Device or resource busy",                           \
      "File exists",                                       \
      "Invalid cross-device link",                         \
      "No such device",                                    \
      "Not a directory",                                   \
      "Is a directory",                                    \
      "Invalid argument",                                  \
      "Too many open files in system",                     \
      "Too many open files",                               \
      "Inappropriate ioctl for device",                    \
      "Text file busy",                                    \
      "File too large",                                    \
      "No space left on device",                           \
      "Illegal seek",                                      \
      "Read-only file system",                             \
      "Too many links",                                    \
      "Broken pipe",                                       \
      "Numerical argument out of domain",                  \
      "Numerical result out of range",                     \
      "Resource deadlock avoided",                         \
      "File name too long",                                \
      "No locks available",                                \
      "Function not implemented",                          \
      "Directory not empty",                               \
      "Too many levels of symbolic links",                 \
      "Unknown error 41",                                  \
      "No message of desired type",                        \
      "Identifier removed",                                \
      "Channel number out of range",                       \
      "Level 2 not synchronized",                          \
      "Level 3 halted",                                    \
      "Level 3 reset",                                     \
      "Link number out of range",                          \
      "Protocol driver not attached",                      \
      "No CSI structure available",                        \
      "Level 2 halted",                                    \
      "Invalid exchange",                                  \
      "Invalid request descriptor",                        \
      "Exchange full",                                     \
      "No anode",                                          \
      "Invalid request code",                              \
      "Invalid slot",                                      \
      "Unknown error 58",                                  \
      "Bad font file format",                              \
      "Device not a stream",                               \
      "No data available",                                 \
      "Timer expired",                                     \
      "Out of streams resources",                          \
      "Machine is not on the network",                     \
      "Package not installed",                             \
      "Object is remote",                                  \
      "Link has been severed",                             \
      "Advertise error",                                   \
      "Srmount error",                                     \
      "Communication error on send",                       \
      "Protocol error",                                    \
      "Multihop attempted",                                \
      "RFS specific error",                                \
      "Bad message",                                       \
      "Value too large for defined data type",             \
      "Name not unique on network",                        \
      "File descriptor in bad state",                      \
      "Remote address changed",                            \
      "Can not access a needed shared library",            \
      "Accessing a corrupted shared library",              \
      ".lib section in a.out corrupted",                   \
      "Attempting to link in too many shared libraries",   \
      "Cannot exec a shared library directly",             \
      "Invalid or incomplete multibyte or wide character", \
      "Interrupted system call should be restarted",       \
      "Streams pipe error",                                \
      "Too many users",                                    \
      "Socket operation on non-socket",                    \
      "Destination address required",                      \
      "Message too long",                                  \
      "Protocol wrong type for socket",                    \
      "Protocol not available",                            \
      "Protocol not supported",                            \
      "Socket type not supported",                         \
      "Operation not supported",                           \
      "Protocol family not supported",                     \
      "Address family not supported by protocol",          \
      "Address already in use",                            \
      "Cannot assign requested address",                   \
      "Network is down",                                   \
      "Network is unreachable",                            \
      "Network dropped connection on reset",               \
      "Software caused connection abort",                  \
      "Connection reset by peer",                          \
      "No buffer space available",                         \
      "Transport endpoint is already connected",           \
      "Transport endpoint is not connected",               \
      "Cannot send after transport endpoint shutdown",     \
      "Too many references: cannot splice",                \
      "Connection timed out",                              \
      "Connection refused",                                \
      "Host is down",                                      \
      "No route to host",                                  \
      "Operation already in progress",                     \
      "Operation now in progress",                         \
      "Stale file handle",                                 \
      "Structure needs cleaning",                          \
      "Not a XENIX named type file",                       \
      "No XENIX semaphores available",                     \
      "Is a named type file",                              \
      "Remote I/O error",                                  \
      "Disk quota exceeded",                               \
      "No medium found",                                   \
      "Wrong medium type",                                 \
      "Operation canceled",                                \
      "Required key not available",                        \
      "Key has expired",                                   \
      "Key has been revoked",                              \
      "Key was rejected by service",                       \
      "Owner died",                                        \
      "State not recoverable",                             \
      "Operation not possible due to RF-kill",             \
      "Memory page has hardware error"}
#endif

int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *dest, const char *src);
char *s21_strcat(char *destination, const char *source);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
void s21_errnum_tostring(char *str, int num);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_memchr(const void *str, int c, s21_size_t n);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);  // hotbl
void *s21_to_lower(const char *str);  // hotbl
void *s21_insert(const char *src, const char *str,
                 s21_size_t start_index);                 // hotbl
void *s21_trim(const char *src, const char *trim_chars);  // hotbl

char *s21_strncat(char *dest, const char *src, size_t n);
char *s21_strchr(const char *str, int c);

void s21_write_tokens_to_vars(const token *tokens, int tokens_count,
                              char *str_pos, int *result);
void s21_write_char_to_var(token cur_token, char **str_pos, int *result);
void s21_get_tokens(token *tokens, int *tokens_count, char **format_pos,
                    va_list *argptr);
int s21_check_space(char ch);
void s21_skip_spaces(char **pos);
int s21_sscanf(const char *str, const char *format, ...);
void s21_write_int_to_var(token cur_token, char **str_pos, int *result,
                          int *error);
void s21_write_float_to_var(token cur_token, char **str_pos, int *result,
                            int *error);
void s21_write_str_to_var(token cur_token, char **str_pos, int *result);
void s21_write_8_10_16_to_var(token cur_token, char **str_pos, int *result,
                              int *error);
void s21_write_16_to_var(token cur_token, char **str_pos, int *result,
                         int *error);
void s21_write_8_to_var(token cur_token, char **str_pos, int *result,
                        int *error);
void s21_get_length(char **format_pos, token *token);
void s21_get_width(char **format_pos, token *token);
void s21_convert_int(long long int res, token cur_token);
void s21_convert_float(long double res, token cur_token);
void s21_convert_unsigned_int(unsigned long long int res, token cur_token,
                              int sign);
void s21_write_unsigned_int_to_var(token cur_token, char **str_pos, int *result,
                                   int *error);
int s21_check_EOS_string(const char *str);
void s21_skip_chars_in_buff(char **str_pos, char *buff, int *error);
void s21_write_count_symbs_to_var(token cur_token, const char *str_pos,
                                  const char *start_pos);
void s21_skip_percent(char **str_pos, int *error);

int s21_memcmp(const void *str1, const void *str2, size_t n);
void *s21_memcpy(void *dest, const void *src, size_t n);
void *s21_memset(void *str, int c, size_t n);

int s21_parser(const char *string, va_list args, char *result);
void s21_parser_flags(format_sprintf *format, const char *string, int *index);
void s21_parser_width(format_sprintf *format, const char *string, int *index);
void s21_parser_length(format_sprintf *format, const char *string, int *index);
void s21_parser_precision(format_sprintf *format, const char *string,
                          int *index);
int s21_parser_specifier(format_sprintf *format, const char *string,
                         int const *index);

void s21_d_to_buff(va_list args, format_sprintf format, char *temp, int *flag);
void s21_f_to_buff(va_list args, format_sprintf format, char *temp);
void s21_s_to_buff(va_list args, format_sprintf format, char *temp, int *flag);
void s21_xXp_to_buff(va_list args, format_sprintf format, char *temp,
                     int *flag);
void s21_gG_to_buff(va_list args, format_sprintf format, char *temp);
void s21_ou_to_buff(va_list args, format_sprintf format, char *temp, int *flag);
void s21_c_to_buff(va_list args, format_sprintf format, char *temp);

int s21_str_to_d(char const *str);
int s21_is_digit(char c);
int s21_d_len(unsigned long long int num);
void s21_d_to_str(long long int num, char *res);
void s21_oupx_to_str(unsigned long long num, char *res, format_sprintf format,
                     int base);
int s21_f_len(long double x);
void s21_f_to_str(long double num, char *res, int round_index,
                  format_sprintf format);
void s21_e_to_str(long double num, char *res, int round_index,
                  format_sprintf format);
void s21_g_to_str(long double num, char *res, format_sprintf format);

void s21_precision(char *res, format_sprintf format, char param);
void s21_width(char *res, format_sprintf format);
void s21_flags(char *res, format_sprintf format);
void s21_param_result(va_list args, format_sprintf format, char *res,
                      int *res_index);
int s21_sprintf(char *str, const char *string, ...);

#endif  // S21_STRING_H
