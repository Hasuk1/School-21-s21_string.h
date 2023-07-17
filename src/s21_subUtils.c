#include "s21_string.h"

int widthFlags(char *str, char *strNum, int countSpace, int *i, int percision) {
  int s = s21_strlen(strNum);
  int size = percision == -1 ? s : percision;
  if (countSpace && countSpace > size) {
    for (int f = 0; f < countSpace - size; f++) {
      str += s21_putchar(str, ' ');
      *i += 1;
    }
  } else {
    countSpace = size;
  }
  return countSpace - size;
}

int putZeros(char *str, int percision, char *numStr) {
  int i = 0;
  s21_size_t s = s21_strlen(numStr);
  if (percision != -1 && (int)s <= percision) {
    while (i < percision - (int)s) {
      i += s21_putchar(str, '0');
      str += 1;
    }
  }
  return i;
}

int numWorkWithFlags(char *str, long long int num, flags_t flags, int *i) {
  int flag = 0;
  flags.percision = -1;
  if (num > 0 && flags.space) {
    *i += s21_putstr(str, " ", flags);
    flag = 1;
  } else if (num > 0 && flags.plus) {
    *i += s21_putstr(str, "+", flags);
    flag = 1;
  }
  return flag;
}

int numUtil(char *str, char *numStr, flags_t flags, long long int num) {
  int i = 0;
  if (numStr != S21_NULL) {
    if (flags.space) str += numWorkWithFlags(str, num, flags, &i);
    if (flags.width && !flags.zero && !flags.isHex)
      str += widthFlags(str, numStr, flags.width, &i, flags.percision);
    else if (flags.width && !flags.zero && flags.isHex)
      str += widthFlags(str, numStr, flags.width, &i, flags.percision);
    if ((flags.zero && flags.width && !flags.isHex) ||
        (!flags.percision && flags.isHex) ||
        (flags.zero && flags.width && flags.isHex && flags.percision == -1)) {
      int a = putZeros(str, flags.width, numStr);
      i += a;
      str += a;
    }
    if (flags.isHex && flags.tag && flags.width && !flags.zero) {
      int a = 0;
      if (flags.isHex == 1)
        a = s21_putstr(str, "0x", flags);
      else if (flags.isHex == 2)
        a = s21_putstr(str, "0X", flags);
      else
        a = s21_putstr(str, "0", flags);
      i += a;
      str += a;
    }
    if (flags.plus) str += numWorkWithFlags(str, num, flags, &i);
    if (flags.percision > 0) {
      int a = putZeros(str, flags.percision, numStr);
      i += a;
      str += a;
    }
    int a = s21_putstr(str, numStr, flags);
    i += a;
    if (flags.minus) {
      str += a;
      if (flags.tag) {
        if (flags.isHex != 3)
          flags.minus -= 2;
        else
          flags.minus -= 1;
      }
      str += widthFlags(str, numStr, flags.minus, &i, flags.percision);
    }
    free(numStr);
  } else {
    i += s21_putstr(str, "(null)", flags);
  }
  return i;
}

void *parseVaArg(flags_t flags, char format, va_list *ap) {
  void *arg = S21_NULL;
  switch (format) {
    case 'd':
    case 'x':
    case 'X':
    case 'o': {
      long long int *i = malloc(sizeof(long long int));
      if (flags.h)
        *i = (long long int)(short int)va_arg(*ap, int);
      else if (flags.l)
        *i = va_arg(*ap, long long int);
      else if (!flags.L)
        *i = (long long int)va_arg(*ap, int);
      arg = i;
      break;
    }
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G': {
      long double *d = malloc(sizeof(long double));
      if (!flags.L)
        *d = (long double)va_arg(*ap, double);
      else
        *d = va_arg(*ap, long double);
      arg = d;
      break;
    }
    case 'u': {
      unsigned long long int *u = malloc(sizeof(unsigned long long int));
      *u = va_arg(*ap, unsigned long long int);
      arg = u;
      break;
    }
    default:
      arg = &format;
      break;
  }
  return arg;
}

int callPutsNumFunc(char format, char *str, flags_t flags, va_list *ap) {
  int i = 0;
  void *a = S21_NULL;
  a = parseVaArg(flags, format, ap);
  switch (format) {
    case 'd':
      if (flags.percision > 0 && flags.width <= flags.percision &&
          *(long long int *)a < 0) {
        flags.space = 0;
        i += 1;
        str += s21_putchar(str, '-');
        *(long long int *)a *= -1;
        flags.plus = 0;
      }
      i += s21_putnbr(str, *(long long int *)a, flags);
      break;
    case 'f':
      i = s21_putEFG(str, *(long double *)a, flags, 0, 1);
      break;
    case 'u':
      i = s21_putunbr(str, *(unsigned long long int *)a, flags);
      break;
    case 'x':
      i = s21_puthex(str, *(long long int *)a, 0, flags, 1);
      break;
    case 'X':
      i = s21_puthex(str, *(long long int *)a, 1, flags, 1);
      break;
    case 'o':
      i = s21_puthex(str, *(long long int *)a, 0, flags, 0);
      break;
    case 'e':
      i = s21_putEFG(str, *(long double *)a, flags, 0, 2);
      break;
    case 'E':
      i = s21_putEFG(str, *(long double *)a, flags, 1, 2);
      break;
    case 'g':
      i = s21_putEFG(str, *(long double *)a, flags, 0, 3);
      break;
    case 'G':
      i = s21_putEFG(str, *(long double *)a, flags, 1, 3);
      break;
    default:
      i = s21_putchar(str, *(char *)a);
      break;
  }
  if (format != 'c') free(a);
  return i;
}

int numFromFormat(int *changeValue, int *flagSize, char *format) {
  format++;
  int numSize = 0;
  if (*format != '*') {
    numSize = countNum(format);
    *changeValue = subAtoi(format, numSize);
    *flagSize += numSize + 1;
    format += numSize;
  }
  return numSize;
}