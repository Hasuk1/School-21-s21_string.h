#include "s21_string.h"

int s21_atoi(const char *str) {
  int result = 0, i = 0;
  while (str[i] >= '0' && str[i] <= '9') {
    result = result * 10 + (str[i] - '0');
    i++;
  }
  return result;
}

static int parse_int(int length, const char **str) {
  int value = 0;
  while (**str >= '0' && **str <= '9') {
    value = value * 10 + (**str - '0');
    (*str)++;
  }
  if (length == 1) {
    s21_size_t value_size = sizeof(value);
    if (value_size <= CHAR_BIT || value >= SHRT_MAX) value = 0;
  } else if (length == 2) {
    s21_size_t value_size = sizeof(value);
    if (value_size <= CHAR_BIT || value >= CHAR_MAX) value = 0;
  } else if (length == 5) {
    if (value >= INT_MAX) value = 0;
  }
  return value;
}

void process_int_format(int length, int *width, const char **str, va_list args,
                        int *read_values) {
  int *pval, isNegative = 1;
  while (**str == ' ') (*str)++;
  if (**str == '-' || **str == '+') {
    if (**str == '-') isNegative = -1;
    (*str)++;
  }
  if (*width == -1) {
    while (**str >= '0' && **str <= '9') {
      (*str)++;
    }
  } else {
    while (!(**str >= '0' && **str <= '9')) (*str)++;
    if (length == 1) {
      short *psval = va_arg(args, short *);
      pval = (int *)psval;
    } else if (length == 2) {
      char *pcval = va_arg(args, char *);
      pval = (int *)pcval;
    } else if (length == 3) {
      long *plval = va_arg(args, long *);
      pval = (int *)plval;
    } else if (length == 4) {
      long long *pllval = va_arg(args, long long *);
      pval = (int *)pllval;
    } else if (length == 5) {
      double *pdval = va_arg(args, double *);
      pval = (int *)pdval;
    } else {
      pval = va_arg(args, int *);
    }
    if (*width > 0) {
      char buf[*width + 1];
      int i;
      for (i = 0; i < *width && (**str >= '0' && **str <= '9'); i++) {
        buf[i] = **str;
        (*str)++;
      }
      buf[i] = '\0';
      *pval = s21_atoi(buf) * isNegative;
      (*width) = 0;
    } else {
      *pval = parse_int(length, (const char **)str) * isNegative;
    }
    (*read_values)++;
  }
  (*width) = 0;
}

double s21_atod(const char *str) {
  double result = 0.0, fraction = 0.0, divisor = 10.0;
  while (*str >= '0' && *str <= '9') {
    result = result * 10.0 + (*str - '0');
    str++;
  }
  if (*str == '.') {
    str++;
  }
  while (*str >= '0' && *str <= '9') {
    fraction = fraction + (*str - '0') / divisor;
    divisor *= 10.0;
    str++;
  }
  result += fraction;
  return result;
}

static long double parse_double(const char **str) {
  long double integer_part = 0, fraction_part = 0, exponent_part = 0;
  int exponent_sign = 1, exponent_digits = 0;
  while (**str >= '0' && **str <= '9') {
    integer_part = integer_part * 10 + (**str - '0');
    (*str)++;
  }
  if (**str == '.' || **str == ',') {
    (*str)++;
    long double fraction_scale = 1;
    while (**str >= '0' && **str <= '9') {
      fraction_part = fraction_part * 10 + (**str - '0');
      fraction_scale *= 10;
      (*str)++;
    }
    fraction_part /= fraction_scale;
  }
  if (**str == 'e' || **str == 'E') {
    (*str)++;
    if (**str == '+' || **str == '-') {
      exponent_sign = (**str == '-') ? -1 : 1;
      (*str)++;
    }
    while (**str >= '0' && **str <= '9') {
      exponent_part = exponent_part * 10 + (**str - '0');
      exponent_digits++;
      (*str)++;
    }
    exponent_part *= exponent_sign;
  }
  long double test = powl(10, exponent_part);
  long double result = integer_part + fraction_part;
  result *= test;
  return result;
}

void process_double_format(int length, int *width, const char **str,
                           va_list args, int *read_values) {
  double *pval;
  int isNegative = 1, r = 1;
  while (**str == ' ') (*str)++;
  if (**str == '-' || **str == '+') {
    if (**str == '-') isNegative = -1;
    (*str)++;
  }
  if (length == 5) {
    long double *pldval = va_arg(args, long double *);
    *pldval = parse_double(str) * isNegative;
    r = 0;
  } else {
    pval = va_arg(args, double *);
  }
  if (*width > 0) {
    char buf[*width + 1];
    int i;
    for (i = 0; i < *width; i++) {
      if ((**str == '.' || **str == ',') || (**str >= '0' && **str <= '9')) {
        buf[i] = **str;
        (*str)++;
      }
    }
    buf[i] = '\0';
    if (r) *pval = s21_atod(buf) * isNegative;
    (*width) = 0;
  } else {
    if (r) *pval = parse_double((const char **)str) * isNegative;
  }
  (*read_values)++;
}

static float s21_atof(const char *str) {
  float result = 0, fraction = 0, divisor = 10;
  while (*str >= '0' && *str <= '9') {
    result = result * 10.0 + (*str - '0');
    str++;
  }
  if (*str == '.') {
    str++;
  }
  while (*str >= '0' && *str <= '9') {
    fraction = fraction + (*str - '0') / divisor;
    divisor *= 10.0;
    str++;
  }
  result += fraction;
  return result;
}

static float parse_float(const char **str) {
  float integer_part = 0, fraction_part = 0, exponent_part = 0;
  int exponent_sign = 1, exponent_digits = 0;
  while (**str >= '0' && **str <= '9') {
    integer_part = integer_part * 10 + (**str - '0');
    (*str)++;
  }
  if (**str == '.' || **str == ',') {
    (*str)++;
    float fraction_scale = 1;
    while (**str >= '0' && **str <= '9') {
      fraction_part = fraction_part * 10 + (**str - '0');
      fraction_scale *= 10;
      (*str)++;
    }
    fraction_part /= fraction_scale;
  }
  if (**str == 'e' || **str == 'E') {
    (*str)++;
    if (**str == '+' || **str == '-') {
      exponent_sign = (**str == '-') ? -1 : 1;
      (*str)++;
    }
    while (**str >= '0' && **str <= '9') {
      exponent_part = exponent_part * 10 + (**str - '0');
      exponent_digits++;
      (*str)++;
    }
    exponent_part *= exponent_sign;
  }
  float test = powf(10, exponent_part);
  float result = integer_part + fraction_part;
  result *= test;
  return result;
}

void process_float_format(int *width, const char **str, va_list args,
                          int *read_values) {
  float *pval;
  int isNegative = 1, r = 1;
  while (**str == ' ') (*str)++;
  if (**str == '-' || **str == '+') {
    if (**str == '-') isNegative = -1;
    (*str)++;
  }
  pval = va_arg(args, float *);
  if (*width > 0) {
    char buf[*width + 1];
    int i;
    for (i = 0; i < *width; i++) {
      if ((**str == '.' || **str == ',') || (**str >= '0' && **str <= '9')) {
        buf[i] = **str;
        (*str)++;
      }
    }
    buf[i] = '\0';
    if (r) *pval = s21_atof(buf) * isNegative;
    (*width) = 0;
    (*read_values)++;
  } else if (*width == -1) {
    while ((**str == '.' || **str == ',') || (**str >= '0' && **str <= '9'))
      (*str)++;
  } else {
    if (r) *pval = parse_float((const char **)str) * isNegative;
    (*read_values)++;
  }
}

void process_char_format(int *width, const char **str, va_list args,
                         int *read_values) {
  if (*width == -1) {
    (*str)++;
    (*width) = 0;
  } else if (*width > 0) {
    char *pval = va_arg(args, char *);
    *pval = **str;
    (*str)++;
    (*read_values)++;
    (*width) = 0;
  } else {
    char *pval = va_arg(args, char *);
    *pval = **str;
    (*str)++;
    (*read_values)++;
  }
}

static int parse_string(const char **str, char *buffer, int buffer_size,
                        int *read_values) {
  int length = 0;
  while (**str != '\0' && **str != ' ' && length < buffer_size - 1) {
    while ((**str != ' ' && **str != '\0') && length < buffer_size - 1) {
      *buffer++ = **str;
      (*str)++;
      length++;
    }
    if (length > 0 && (**str == ' ' || **str == '\0')) {
      *buffer = '\0';
      continue;
    }
  }
  if (length > 0) (*read_values)++;
  (*str)++;
  if (length < buffer_size) {
    *buffer = '\0';
  } else {
    buffer[buffer_size - 1] = '\0';
  }
  return length;
}

void process_string_format(int *width, const char **str, va_list args,
                           int *read_values) {
  char *pval = va_arg(args, char *);
  parse_string((const char **)str, pval, *width > 0 ? *width + 1 : INT_MAX,
               read_values);
  (*width) = 0;
}

void get_res_strtoul(const char *str, int base, unsigned long *result) {
  int digit = 0;
  while ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F') ||
         (*str >= 'a' && *str <= 'f')) {
    if (*str >= '0' && *str <= '9') {
      digit = *str - '0';
    } else if (*str >= 'A' && *str <= 'F') {
      digit = *str - 'A' + 10;
    } else if (*str >= 'a' && *str <= 'f')
      digit = *str - 'a' + 10;
    if (digit >= base) break;
    *result = *result * base + digit;
    (str)++;
  }
}

unsigned long s21_strtoul(int length, const char *str, int base) {
  unsigned long result = 0;
  int isNegative = 0;
  if (*str == '-' || *str == '+') {
    if (*str == '-') isNegative = 1;
    str++;
  }
  if (base == 16 && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
  } else if (base == 16 && *str == '0' && (*(str + 1) == '0'))
    while (*str == '0') str++;
  get_res_strtoul((const char *)str, base, &result);
  if (base == 10) {
    if (length == 1) {
      s21_size_t result_size = sizeof(result);
      if (result_size <= CHAR_BIT || result >= SHRT_MAX) result = 0;
    } else if (length == 2) {
      s21_size_t result_size = sizeof(result);
      if (result_size <= CHAR_BIT || result >= CHAR_MAX) result = 0;
    } else if (length == 5) {
      if (result >= INT_MAX) result = 0;
    }
  }
  if (isNegative) {
    if (base == 10) {
      result = UINT_MAX + 1 - result;
    } else
      result *= -1;
  }
  return result;
}

long s21_strtol(const char **str, int base) {
  long result = 0;
  int isNegative = 0;
  if (**str == '-' || **str == '+') {
    if (**str == '-') isNegative = 1;
    (*str)++;
  }
  if (base == 0) {
    if (**str == '0') {
      (*str)++;
      if (**str == 'x' || **str == 'X') {
        base = 16;
        (*str)++;
      } else {
        base = 8;
      }
    } else {
      base = 10;
    }
  }
  if (base == 16 && **str == '0') {
    (*str)++;
    if (**str == 'x' || **str == 'X') {
      (*str)++;
    } else
      (*str)--;
  }
  while ((**str >= '0' && **str <= '9') || (**str >= 'A' && **str <= 'F') ||
         (**str >= 'a' && **str <= 'f')) {
    int digit = 0;
    if (**str >= '0' && **str <= '9') {
      digit = **str - '0';
    } else if (**str >= 'A' && **str <= 'F') {
      digit = **str - 'A' + 10;
    } else if (**str >= 'a' && **str <= 'f') {
      digit = **str - 'a' + 10;
    }
    if (digit >= base) break;
    result = result * base + digit;
    (*str)++;
  }
  return isNegative ? -result : result;
}

static unsigned int parse_unsigned_int(const char **str) {
  unsigned int value = 0;
  int isNegative = 0;
  if (**str == '-' || **str == '+') {
    if (**str == '-') isNegative = 1;
    (*str)++;
  }
  while (**str >= '0' && **str <= '9') {
    value = value * 10 + (**str - '0');
    (*str)++;
  }
  if (isNegative) value = UINT_MAX + 1 - value;
  return value;
}

void process_x_format(int length, int *width, const char **str, va_list args,
                      const char **format, int *read_values) {
  unsigned int *pval, r = 1;
  while (**str == ' ') (*str)++;
  if (length == 1) {
    unsigned short *pusval = va_arg(args, unsigned short *);
    pval = (unsigned int *)pusval;
  } else if (length == 2) {
    unsigned char *pcuval = va_arg(args, unsigned char *);
    pval = (unsigned int *)pcuval;
  } else if (length == 3) {
    unsigned long *pulval = va_arg(args, unsigned long *);
    pval = (unsigned int *)pulval;
  } else if (length == 4) {
    unsigned long long *pullval = va_arg(args, unsigned long long *);
    *pullval = parse_unsigned_int((const char **)str);
    r = 0;
  } else
    pval = va_arg(args, unsigned int *);
  if (*width > 0) {
    char buf[*width + 1];
    int i = 0;
    for (i = 0; i < *width && ((**str >= '0' && **str <= '9') ||
                               (**str >= 'A' && **str <= 'F') ||
                               (**str >= 'a' && **str <= 'f'));
         i++) {
      buf[i] = **str;
      (*str)++;
    }
    (*read_values)++;
    buf[i] = '\0';
    if (**format == 'u') {
      int base = 10;
      if (r) *pval = s21_strtoul(length, buf, base);
    } else if (**format == 'o') {
      int base = 8;
      if (r) *pval = s21_strtoul(length, buf, base);
    } else if (r)
      *pval = s21_strtoul(length, buf, 16);
    (*width) = 0;
  } else {
    if (**format == 'u') {
      if (r) *pval = parse_unsigned_int((const char **)str);
    } else if (**format == 'o') {
      if (r) *pval = s21_strtol((const char **)str, 8);
    } else if (r)
      *pval = s21_strtol((const char **)str, 16);
    (*read_values)++;
  }
}

unsigned long s21_strtoulp(const char **str, int base) {
  unsigned long result = 0;
  if (**str == '-') {
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }
  if (base == 16) (*str) += 2;
  while ((**str >= '0' && **str <= '9') || (**str >= 'A' && **str <= 'F') ||
         (**str >= 'a' && **str <= 'f')) {
    int digit = 0;
    if (**str >= '0' && **str <= '9') {
      digit = **str - '0';
    } else if (**str >= 'A' && **str <= 'F') {
      digit = **str - 'A' + 10;
    } else if (**str >= 'a' && **str <= 'f') {
      digit = **str - 'a' + 10;
    }
    if (digit >= base) break;
    result = result * base + digit;
    (*str)++;
  }
  return result;
}

void process_pointer_format(int *width, const char **str, va_list args,
                            int *read_values) {
  void **ppval = va_arg(args, void **);
  while (**str == ' ') (*str)++;
  if (*width > 0) {
    char buf[*width + 1];
    int i = 0;
    if (**str == '-' || **str == '+') {
      (*str)++;
    }
    if (**str == '0') {
      (*str)++;
      if (**str == 'x' || **str == 'X') {
        (*str)++;
      } else
        (*str)--;
    }

    for (i = 0; i < *width && ((**str >= '0' && **str <= '9') ||
                               (**str >= 'A' && **str <= 'F') ||
                               (**str >= 'a' && **str <= 'f'));
         i++) {
      buf[i] = **str;
      (*str)++;
    }
    buf[i] = '\0';
    *ppval = (void *)s21_strtoul(0, buf, 16);
    (*width) = 0;
    (*read_values)++;
  } else if (*width == -1) {
    while ((**str >= '0' && **str <= '9') || (**str >= 'A' && **str <= 'F') ||
           (**str >= 'a' && **str <= 'f'))
      (*str)++;
  } else {
    *ppval = (void *)s21_strtoulp((const char **)str, 16);
    (*read_values)++;
  }
  (*width) = 0;
}

void int_x_width_pars(int length, va_list args, int *read_values,
                      const char **str, int isNegative, int base, int *width) {
  int r = 1;
  unsigned int *pval = 0;
  if (length == 1) {
    unsigned short *pusval = va_arg(args, unsigned short *);
    pval = (unsigned int *)pusval;
  } else if (length == 2) {
    unsigned char *pcuval = va_arg(args, unsigned char *);
    pval = (unsigned int *)pcuval;
  } else if (length == 3) {
    unsigned long *pulval = va_arg(args, unsigned long *);
    pval = (unsigned int *)pulval;
  } else if (length == 4) {
    unsigned long long *pullval = va_arg(args, unsigned long long *);
    *pullval = parse_unsigned_int((const char **)str);
    (*read_values)++;
    r = 0;
  } else {
    pval = va_arg(args, unsigned int *);
  }

  if (*width > 0) {
    char buf[*width + 1];
    int i = 0;
    for (i = 0; i < *width && ((**str >= '0' && **str <= '9') ||
                               (**str >= 'A' && **str <= 'F') ||
                               (**str >= 'a' && **str <= 'f'));
         i++) {
      buf[i] = **str;
      (*str)++;
    }
    buf[i] = '\0';
    if (base == 10) {
      if (r) *pval = s21_strtoul(length, buf, base) * isNegative;
    } else if (base == 8) {
      if (r) *pval = s21_strtoul(length, buf, base);
    } else if (base == 16) {
      if (r) *pval = s21_strtoul(length, buf, base);
    }
    if ((pval != 0) && (base == 10 || base == 8 || base == 16))
      (*read_values)++;
  } else if (*width == 0) {
    if (base == 10) {
      if (r) *pval = parse_int(length, (const char **)str) * isNegative;
    } else if (base == 8) {
      if (r) *pval = s21_strtol((const char **)str, base);
    } else if (base == 16) {
      if (r) *pval = s21_strtol((const char **)str, base);
    }
    if ((pval != 0) && (base == 10 || base == 8 || base == 16))
      (*read_values)++;
  }
}

void process_int_x_format(int length, int *width, const char **str,
                          va_list args, int *read_values) {
  int isNegative = 1;
  int base = 0;
  while (**str == ' ') (*str)++;
  if (*width == -1) {
    while ((**str >= '0' && **str <= '9') || (**str >= 'A' && **str <= 'F') ||
           (**str >= 'a' && **str <= 'f') || (**str == '-') || (**str == '+'))
      (*str)++;
  }
  if (**str == '-' || **str == '+') {
    if (**str == '-') isNegative = -1;
    (*str)++;
  }
  if (**str >= '0' && **str <= '9') {
    base = 10;
    if (**str == '0') {
      base = 8;
      (*str)++;
      if (**str == 'x' || **str == 'X') {
        base = 16;
        (*str)--;
      }
    }
  }
  int_x_width_pars(length, args, read_values, (const char **)str, isNegative,
                   base, width);
  (*width) = 0;
}

static void width_parser(const char **format, int *width) {
  while (**format >= '0' && **format <= '9') {
    *width = *width * 10 + (**format - '0');
    (*format)++;
  }
}

static void length_parser(const char **format, int *length) {
  *length = 0;
  switch (**format) {
    case 'h':
      *length = 1;
      (*format)++;
      if (**format == 'h') {
        *length = 2;
        (*format)++;
      }
      break;
    case 'l':
      *length = 3;
      (*format)++;
      if (**format == 'l') {
        *length = 4;
        (*format)++;
      } else if (**format == 'u')
        *length = 4;
      break;
    case 'L':
      *length = 5;
      (*format)++;
      break;
    default:
      break;
  }
}

void switch_case_specifiers(va_list args, const char **str, int *read_values,
                            int *width, int length, const char **format) {
  if (args != S21_NULL) {
    if (**format == 'd') {
      process_int_format(length, width, (const char **)str, args, read_values);
    } else if (**format == 'i') {
      process_int_x_format(length, width, (const char **)str, args,
                           read_values);
    } else if (**format == 'f' || **format == 'e' || **format == 'E' ||
               **format == 'g' || **format == 'G') {
      if (length == 0) {
        process_float_format(width, (const char **)str, args, read_values);
      } else
        process_double_format(length, width, (const char **)str, args,
                              read_values);
    } else if (**format == 'c') {
      process_char_format(width, (const char **)str, args, read_values);
    } else if (**format == 's') {
      process_string_format(width, (const char **)str, args, read_values);
    } else if (**format == 'u' || **format == 'o' || **format == 'x' ||
               **format == 'X') {
      process_x_format(length, width, (const char **)str, args,
                       (const char **)format, read_values);
    } else if (**format == 'p') {
      process_pointer_format(width, (const char **)str, args, read_values);
    } else if (**format == 'n') {
      int *pval = va_arg(args, int *);
      *pval = *read_values;
    } else if (**format == '%') {
      if (**str == '%') {
        (*str)++;
      } else {
        (*read_values) = -1;
      }
    } else
      (*read_values) = -1;
  } else
    (*read_values) = -1;
}

int s21_sscanf(const char *str, const char *format, ...) {
  if (str == S21_NULL || format == S21_NULL) return -1;
  va_list args;
  va_start(args, format);
  int read_values = 0, width = 0, length = 0, width_astr = 0;
  while (*format != '\0' && *str != '\0') {
    while (*format != '%' && *format != '\0') format++;
    if (*format == '%') {
      format++;
      if (*format == '*') {
        format++;
        width_parser(&format, &width);
        if (width == 0) width = -1;
        if (width > 0) {
          width_astr = width;
          width = 0;
          while (*format != '%') format++;
          continue;
        } else
          width = -1;
      } else {
        width_parser(&format, &width);
      }
      length_parser(&format, &length);
      if (width_astr > 0) {
        if (*format == 'c' || *format == 's') {
          str += width_astr;
        } else {
          while (*str == ' ') str++;
          str += width_astr;
        }
        width_astr = 0;
      }
      switch_case_specifiers(args, &str, &read_values, &width, length, &format);
      if (*format != '\0' && *str != '\0') format++;
      if (*str == *format) {
        format++;
        str++;
      }
      while (*format != '%' && *format != '\0') format++;
    } else {
      read_values = -1;
      break;
    }
  }
  va_end(args);
  return read_values;
}