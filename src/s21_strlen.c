#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t i = 0;
  if (str != S21_NULL) {
    while (str && str[i] != '\0') {
      i++;
    }
  }
  return i;
}