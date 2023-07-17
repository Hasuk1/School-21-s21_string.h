#include "s21_string.h"

char *s21_utoa(unsigned long long int value) {
  char *str = NULL;
  if (value == 0) {
    str = (char *)malloc(2 * sizeof(char));
    if (str != NULL) {
      str[0] = '0';
      str[1] = '\0';
    }
  } else {
    int num_digits = 0;
    unsigned long long int temp = value;

    while (temp > 0) {
      temp /= 10;
      num_digits++;
    }

    str = (char *)malloc((num_digits + 1) * sizeof(char));
    if (str != NULL) {
      str += num_digits;
      *str = '\0';

      while (value > 0) {
        *(--str) = '0' + (value % 10);
        value /= 10;
      }
    }
  }
  return str;
}