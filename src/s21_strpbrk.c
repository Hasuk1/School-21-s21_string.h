#include "s21_string.h"
char *s21_strpbrk(const char *str1, const char *str2) {
  const char *STR1, *STR2;
  for (STR1 = str1; *STR1 != '\0'; ++STR1) {
    for (STR2 = str2; *STR2 != '\0'; ++STR2) {
      if (*STR1 == *STR2) {
        return (char *)STR1;
      }
    }
  }
  return S21_NULL;
}
