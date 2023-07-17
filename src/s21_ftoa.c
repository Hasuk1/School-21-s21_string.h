#include "s21_string.h"

int zeroCounter(double num, int percision) {
  int count = 0;
  if (num < 0) num = -num;
  num *= 10;
  while (num < 0.99999991 && count < percision) {
    num *= 10;
    count++;
  }
  return count;
}

char *ftoa(long double num, int percision) {
  flags_t flags = {};
  flags.percision = percision;
  if (percision == 0) num = llroundl(num);
  long long int intPart = (long long int)num;
  long double floatPart = (long double)num - intPart;
  char *startPos = S21_NULL;
  if (floatPart < 0) floatPart *= -1;

  floatPart *= powl(10, percision);
  floatPart = llroundl(floatPart);
  if (floatPart >= powl(10, percision)) {
    floatPart = 0;
    intPart++;
  }
  if (floatPart >= __LDBL_MAX__) {
    floatPart = 0;
    percision = 0;
  }

  if (num < 0 && intPart == 0) intPart = -1;

  char *strIntPart = s21_itoa(intPart);
  char *strFloatPart = s21_itoa(floatPart);
  if (strIntPart != S21_NULL && strFloatPart != S21_NULL) {
    s21_size_t size = s21_strlen(strIntPart);
    if (intPart == -1 && num < 0 && num > -1) {
      size += 1;
      percision -= 1;
      strIntPart[1] = '0';
    }
    char *strNum = (char *)malloc((size + percision + 2) * sizeof(char));
    if (strNum != S21_NULL) {
      int zeroCount = zeroCounter(num - (int)num, percision);
      flags.percision = -1;
      int i = s21_putstr(strNum, strIntPart, flags);
      startPos = strNum;
      if (floatPart == 0) zeroCount = percision - 1;
      if (percision != 0) {
        strNum += i;
        *strNum = '.';
        while (zeroCount >= 1) {
          strNum++;
          *strNum = '0';
          zeroCount--;
        }
        i = s21_putstr(++strNum, strFloatPart, flags);
      }
      strNum[i] = '\0';
      free(strIntPart);
      free(strFloatPart);
    } else if (strIntPart != S21_NULL) {
      free(strIntPart);
    } else if (strFloatPart != S21_NULL) {
      free(strFloatPart);
    }
  }
  return startPos;
}