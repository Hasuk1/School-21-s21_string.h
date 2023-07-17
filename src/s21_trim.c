#include "s21_string.h"
int s21_strspn(const char *str1, const char *str2) {
  int i = 0, j = 0;
  for (i = 0; str1[i] != '\0'; i++) {
    for (j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        break;
      }
    }
    if (!str2[j]) {
      return i;
    }
  }
  return i;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL) return S21_NULL;
  const char *trim = " ";
  char *result = (char *)malloc(s21_strlen(src) + 1);
  if (result == S21_NULL) {
    return S21_NULL;
  }
  char *back = (char *)malloc(s21_strlen(src) + 1);
  if (back == S21_NULL) {
    return S21_NULL;
  }
  s21_size_t i = 0;
  if (trim_chars != S21_NULL && trim_chars[0] != '\0') {
    trim = trim_chars;
  }
  if (src != S21_NULL) {
    for (i = 0; src[i] != '\0'; i++) {
      back[i] = src[s21_strlen(src) - 1 - i];
    }
    back[i] = '\0';
    s21_size_t ferst = s21_strspn(src, trim);
    s21_size_t last = s21_strspn(back, trim);
    s21_size_t lenght_result = 0;
    if (ferst == s21_strlen(src)) {
      lenght_result = 0;
    } else {
      lenght_result = s21_strlen(src) - ferst - last;
    }
    for (s21_size_t i = 0; i < lenght_result && src[ferst + i] != '\0'; i++) {
      result[i] = src[ferst + i];
    }
    result[lenght_result] = '\0';
    free(back);
  }
  return result;
}
