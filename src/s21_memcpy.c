#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *s = (unsigned char *)src;
  unsigned char *new = (unsigned char *)dest;
  if (s != S21_NULL && new != S21_NULL) {
    for (s21_size_t i = 0; i < n; i++) {
      new[i] = s[i];
    }
  }
  return new;
}