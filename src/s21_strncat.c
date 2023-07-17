#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (dest == S21_NULL || src == S21_NULL) return dest;

  char *p = dest + s21_strlen(dest);
  for (s21_size_t i = 0; *src != '\0' && i < n; i++) {
    *(p++) = *(src++);
  }

  *p = '\0';
  return dest;
}