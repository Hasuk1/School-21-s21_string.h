#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int flag = 0;
  if (n > 0 && str1 != S21_NULL && str2 != S21_NULL) {
    for (s21_size_t i = 0; i < n; i++) {
      if (str1[i] != str2[i]) {
        flag = str1[i] - str2[i];
        break;
      }
    }
  }
  return flag;
}
