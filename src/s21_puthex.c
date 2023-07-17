#include "s21_string.h"

char *s21_intToHexOrOct(long long int num, int flagFont, int flagBase) {
  int size = 0;
  long long int temp = num;
  int base = flagBase ? 16 : 8;  // Определяем основание: 16 (шестнадцатеричное)
                                 // или 8 (восьмеричное)

  if (temp < 0) {
    temp = (unsigned int)temp;
    num = (unsigned int)temp;
  }

  if (temp == 0) {
    size = 1;
  } else {
    while (temp != 0) {
      size++;
      temp = temp / base;
    }
  }

  char *str = (char *)malloc(size * sizeof(char) + 1);

  if (str != S21_NULL) {
    int index = size - 1;

    if (num == 0) {
      str[index] = '0';
    } else {
      while (num != 0) {
        int digit = num % base;

        if (digit < 10) {
          str[index] = '0' + digit;
        } else {
          if (flagFont == 1) {
            str[index] = 'A' + digit - 10;
          } else {
            str[index] = 'a' + digit - 10;
          }
        }

        index--;
        num = num / base;
      }
    }

    str[size] = '\0';
  }

  return str;
}