#include "s21_string.h"

int s21_sizen(long long int n) {
  int size = 0;
  if (n == 0)
    return (1);
  else if (n == -__LONG_LONG_MAX__)
    return (20);
  else if (n < 0) {
    size++;
    n = n * -1;
  }
  while (n > 0) {
    n = n / 10;
    size++;
  }
  return size;
}

char *s21_nbrstr(char *res, int i, long long int n) {
  res[i--] = 0;
  if (n == 0)
    res[i] = '0';
  else if (n < 0) {
    res[0] = '-';
    if (n == -2147483648) {
      res[1] = '2';
      n = 147483648;
    } else
      n = n * -1;
  }
  while (n > 0) {
    res[i] = n % 10 + '0';
    n /= 10;
    i--;
  }
  return (res);
}

char *s21_itoa(long long int n) {
  int i = s21_sizen(n);
  char *res = {0};
  res = (char *)malloc(sizeof(char) * (i + 2));
  if (res) {
    res[i] = '\0';
    res = s21_nbrstr(res, i, n);
  }
  return (res);
}