#include "s21_string.h"

void *s21_to_upper(const char *str) {
  int i = 0;
  if (str == S21_NULL) return S21_NULL;
  char *STR = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
  if (STR == S21_NULL) return S21_NULL;
  if (str != S21_NULL) {
    for (i = 0; str[i] != '\0'; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        STR[i] = str[i] - 32;
      } else
        STR[i] = str[i];
    }
  }
  STR[i] = '\0';
  return (void *)STR;
}