#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  if (str == S21_NULL) return S21_NULL;
  const char *last = S21_NULL;
  while (*str != '\0') {
    if (*str == c) last = str;
    str++;
  }
  return ((c == '\0') ? (char *)str : (char *)last);
}