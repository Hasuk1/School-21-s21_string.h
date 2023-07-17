#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int n_ = n;
  if (n_ > 0) {
    for (s21_size_t i = 0; i < n; i++) {
      dest[i] = src[i];
    }
  }
  return dest;
}