#include "s21_string.h"
char *s21_strstr(const char *haystack, const char *needle) {
  int flag = 0;
  if (haystack == S21_NULL || needle == S21_NULL) flag = 1;
  if (flag == 0) {
    const char *STR1;
    for (STR1 = haystack; *STR1 != '\0'; STR1++) {
      int i = 0;
      while (needle[i] != '\0' && STR1[i] == needle[i]) i++;
      if (needle[i] == '\0') {
        return (char *)STR1;
      }
    }
    if (s21_strlen(needle) == 0) {
      STR1 = haystack;
      return (char *)STR1;
    }
  }
  return S21_NULL;
}