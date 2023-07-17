#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *start = str;
  va_list ap;
  va_start(ap, format);
  int i = 0;
  while (*format) {
    if (*format != '%') {
      i += s21_putchar(start, *format);
      start++;
      format++;
    } else {
      flags_t flags = parseFlags((char *)format, &ap);
      if (flags.flagSize) format += flags.flagSize;
      format++;
      int b = checkFormat(start, *format, &ap, flags);
      i += b;
      start += b;
      format++;
    }
  }
  va_end(ap);
  str[i] = '\0';
  return i;
}