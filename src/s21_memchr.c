#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *res = S21_NULL;
  if (str != S21_NULL) {
    unsigned char *byte = (unsigned char *)str;
    for (s21_size_t i = 0; i < n; i++) {
      if (byte[i] == c) {
        res = &byte[i];
        break;
      }
    }
  }
  return res;
}
