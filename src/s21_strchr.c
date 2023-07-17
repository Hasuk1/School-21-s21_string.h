#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *first = S21_NULL;
  if (str != S21_NULL) {
    while (*str != '\0') {
      if (*str == c) {
        first = (char *)str;
      }
      ++str;
    }
    if (*str == c) {
      first = (char *)str;
    }
  }
  return first;
}