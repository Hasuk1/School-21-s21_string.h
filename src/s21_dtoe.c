#include "s21_string.h"

long double s21_rountlf(long double num, int precision) {
  if (precision == 0) num = llroundl(num);
  long long int intPart = (long long int)num;
  long double floatPart = (long double)num - intPart;
  if (floatPart < 0) floatPart *= -1.0;

  floatPart *= powl(10, precision);
  floatPart = llroundl(floatPart);
  if (floatPart >= powl(10, precision)) {
    floatPart = 0;
    intPart++;
  }
  if (floatPart >= __LDBL_MAX__) {
    floatPart = 0;
    precision = 0;
  }
  floatPart = floatPart / powl(10, precision);
  floatPart += 0.000000000001;
  return (long double)intPart + floatPart;
}

int intLength(long double number) {
  int size = 0;
  if (number == 0) {
    size = 1;
  } else if (number < 0) {
    number = -number;
  }
  if (number != 0) size = (int)log10(number) + 1;

  return size;
}

char *doubleToExp(long double number, int precision, int flagCase) {
  number = s21_rountlf(number, precision);
  int sign = (number < 0) ? -1 : 1;
  number *= sign;
  int exponent = 0;

  while (number >= 10) {
    number /= 10;
    exponent++;
  }

  int intDigits = intLength(number);
  int totalLength = intDigits + precision + 3;
  if (sign == -1) {
    totalLength++;
  }

  char *buffer = (char *)malloc((totalLength + 3) * sizeof(char));
  if (buffer != S21_NULL) {
    int index = 0;
    if (sign == -1) {
      buffer[index++] = '-';
    }
    buffer[index++] = '0' + (int)number;

    if (precision > 0) {
      buffer[index++] = '.';
      number -= (int)number;
      while (precision > 0) {
        number *= 10;
        int digit = (int)number;
        number -= digit;
        buffer[index++] = '0' + digit;
        precision--;
      }
    }

    if (flagCase) {
      buffer[index++] = 'E';
    } else {
      buffer[index++] = 'e';
    }
    if (exponent >= 0) {
      buffer[index++] = '+';
    } else {
      buffer[index++] = '-';
      exponent = -exponent;
    }
    buffer[index++] = '0' + (exponent / 10);
    buffer[index++] = '0' + (exponent % 10);

    buffer[index] = '\0';
  }
  return buffer;
}

int countNumInt(int num) {
  int count = 0;
  while (num > 0) {
    num /= 10;
    count++;
  }
  return count;
}

char *removeLastZeros(char *strNum) {
  char *newStr = S21_NULL;
  int len = s21_strlen(strNum);
  int countZero = 0;
  for (int i = len - 1; i != 0 && strNum[i] == '0'; i--) {
    if (strNum[i] == '0') {
      countZero++;
    }
  }
  newStr = (char *)malloc((sizeof(char)) * (len - countZero + 1));
  for (int i = 0; i < len - countZero; i++) {
    newStr[i] = strNum[i];
  }
  newStr[len - countZero] = '\0';
  free(strNum);
  return newStr;
}

char *gtoa(long double num, int precision) {
  long long int intPart = (long long int)num;
  long double floatPart = num - (long double)intPart;
  char *strNum = (char *)malloc((precision + 3) * sizeof(char));
  int countInt = countNumInt(intPart);
  char *intPartStr = s21_itoa(intPart);
  char *startNum = strNum;
  if (intPartStr != S21_NULL && strNum != S21_NULL) {
    for (int i = 0; i < precision && intPartStr[i] != '\0'; i++) {
      *strNum = intPartStr[i];
      strNum++;
    }
    free(intPartStr);
    if (precision - countInt > 0) {
      *strNum = '.';
      strNum++;
      int countFloatPart = precision - countInt;
      floatPart *= powl(10, countFloatPart);
      floatPart = lroundl(floatPart);
      char *floatPartStr = s21_itoa((long long int)floatPart);
      if (floatPartStr != S21_NULL) {
        for (int i = 0; i < countFloatPart; i++) {
          *strNum = floatPartStr[i];
          strNum++;
        }
        free(floatPartStr);
      }
    }
    *(strNum) = '\0';
  }
  startNum = removeLastZeros(startNum);
  return startNum;
}

char *doubleToFormat(long double number, int precision, int flagCase) {
  if (fabsl(number) < pow(10, -precision) ||
      fabsl(number) >= pow(10, precision)) {
    return doubleToExp(number, precision, flagCase);
  } else {
    return gtoa(number, precision);
  }
}
