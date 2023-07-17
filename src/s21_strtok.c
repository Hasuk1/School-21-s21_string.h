#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last = S21_NULL;
  if (str != S21_NULL) {
    last = str;
  } else if (last == S21_NULL) {
    return S21_NULL;
  }
  while (*last && s21_strchr(delim, *last)) {
    ++last;
  }
  if (*last == '\0') {
    return S21_NULL;
  }
  char *token = last;
  while (*last && !s21_strchr(delim, *last)) {
    ++last;
  }
  if (*last) {
    *last++ = '\0';
  }
  return token;
}
