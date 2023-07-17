#include "s21_string.h"

int s21_putchar(char *str, int ap) {
  *str = ap;
  return 1;
}

int isNumFormat(char format) {
  return (format == 'd' || format == 'f' || format == 'u' || format == 'x' ||
          format == 'X' || format == 'o' || format == 'e' || format == 'E' ||
          format == 'g' || format == 'G');
}

int s21_putstr(char *str, char *ap, flags_t flags) {
  s21_size_t size = s21_strlen(ap);
  if (flags.percision == -1) flags.percision = size;
  int i = 0;
  while (ap[i] && i < flags.percision) {
    s21_putchar(str, ap[i]);
    str++;
    i++;
  }
  return i;
}

int s21_putEFG(char *str, long double num, flags_t flags, int flagCase,
               int format) {
  char *numStr = S21_NULL;
  flags.percision = flags.percision == -1 ? 6 : flags.percision;
  if (flags.width) flags.width -= (flags.plus || flags.space);
  if (flags.minus) flags.minus -= (flags.plus || flags.space);
  if (format == 1) {
    numStr = ftoa(num, flags.percision);
  } else if (format == 2) {
    numStr = doubleToExp(num, flags.percision, flagCase);
  } else {
    numStr = doubleToFormat(num, flags.percision, flagCase);
  }
  flags.percision = -1;
  return numUtil(str, numStr, flags, num);
}

int s21_putnbr(char *str, long long int num, flags_t flags) {
  int i = 0;
  if (flags.width)
    flags.width -= ((flags.plus && num > 0) || (flags.space && num > 0));
  if (flags.minus) flags.minus -= (flags.plus != 0 || (flags.space));  //
  char *numStr = s21_itoa(num);
  if (flags.zero && flags.percision > 2 && flags.width) flags.zero = 0;
  int s = s21_strlen(numStr);
  if (s > flags.percision && flags.percision <= flags.width &&
      flags.percision != -1) {
    flags.percision = flags.width;
  }
  if (flags.percision < s && s > flags.width && num != 0) {
    flags.percision = s;
    flags.width = s;
  }
  return numUtil(str, numStr, flags, num) + i;
}

int s21_puthex(char *str, long long int num, int flagCase, flags_t flags,
               int flagBase) {
  flags_t tmp = {};
  tmp.percision = -1;
  flags.isHex = 1 + flagCase;
  int i = 0;
  flags.plus = 0;
  flags.space = 0;
  char *numStr = s21_intToHexOrOct(num, flagCase, flagBase);
  if (flags.tag && flags.width > 2) {
    if (flagBase)
      flags.width -= 2;
    else
      flags.width -= 1;
  }
  str += i;
  if ((flags.tag && !flags.width) || (flags.tag && flags.zero)) {
    if (flagCase) {
      i += s21_putstr(str, "0X", tmp);
    } else {
      if (flagBase)
        i += s21_putstr(str, "0x", tmp);
      else
        i += s21_putstr(str, "0", tmp);
    }
    str += i;
  }
  flags.isHex = flagBase ? flags.isHex : 3;
  if (!flagBase && flags.tag && flags.percision) flags.percision -= 1;
  return numUtil(str, numStr, flags, num) + i;
}

int s21_putunbr(char *str, unsigned long long int num, flags_t flags) {
  int i = 0;
  char *numStr = s21_utoa(num);
  i += putZeros(str, flags.percision, numStr);
  str += i;
  flags.percision = -1;
  return numUtil(str, numStr, flags, num);
}

int countNum(char *str) {
  int count = 0;
  while (isdigit(*(str++))) {
    count++;
  }
  return count;
}

int subAtoi(char *str, int count) {
  char substr[20];
  int num = 0;
  for (int i = 0; i < count && i < 20; i++) {
    substr[i] = *str;
    str++;
  }
  substr[count] = '\0';
  num = atoi(substr);
  return num;
}

int isNotSpec(char symbol) {
  int isSpec = 1;
  if (symbol == 'c' || symbol == '%' || symbol == 's' || symbol == 'i' ||
      symbol == 'd' || symbol == 'f' || symbol == 'u' || symbol == 'x' ||
      symbol == 'X' || symbol == 'p' || symbol == 'o' || symbol == 'E' ||
      symbol == 'e' || symbol == 'g' || symbol == 'G')
    isSpec = 0;
  return isSpec;
}

flags_t parseFlags(char *format, va_list *ap) {
  format++;
  flags_t flags = {0};
  flags.percision = -1;
  int numSize = 0;
  while (format && isNotSpec(*format)) {
    switch (*format) {
      case '+':
        flags.plus = 1;
        flags.flagSize++;
        break;
      case '-':
        if (*(format + 1) != '*') {
          if (*(format + 1) == '+') {
            flags.plus = 1;
            format += 1;
            flags.flagSize += 1;
          } else if (*(format + 1) == ' ') {
            flags.space = 1;
            format++;
            flags.flagSize++;
          }
          format += numFromFormat(&flags.minus, &flags.flagSize, format);
        } else {
          flags.minus = va_arg(*ap, int);
          format++;
          flags.flagSize += 2;
        }
        break;

      case '.':
        if (*(format + 1) != '*') {
          format += numFromFormat(&flags.percision, &flags.flagSize, format);
        } else {
          flags.percision = va_arg(*ap, int);
          format++;
          flags.flagSize += 2;
        }
        break;
      case ' ':
        flags.space = 1;
        flags.flagSize++;
        break;
      case '*':
        flags.width = va_arg(*ap, int);
        flags.flagSize += 1;
        break;
      case 'l':
        flags.l = 1;
        flags.flagSize += 1;
        break;
      case 'h':
        flags.h = 1;
        flags.flagSize += 1;
        break;
      case 'L':
        flags.L = 1;
        flags.flagSize += 1;
        break;
      case '#':
        flags.tag = 1;
        flags.flagSize += 1;
        break;
      case '0':
        flags.zero = 1;
        flags.flagSize += 1;
        break;
      default:
        if (isdigit(*format)) {
          numSize = countNum(format);
          flags.width = subAtoi(format, numSize);
          format += numSize;
          flags.flagSize += numSize;
          format--;
        }
        break;
    }
    format++;
  }
  return flags;
}

int checkFormat(char *str, char format, va_list *ap, flags_t flags) {
  int i = 0;
  char *arg;
  if (format == 'i') format = 'd';
  switch (format) {
    case 'c':
      i = s21_putchar(str, va_arg(*ap, int));
      break;
    case 's':
      arg = va_arg(*ap, char *);
      if (flags.width)
        str += widthFlags(str, arg, flags.width, &i, flags.percision);
      i += s21_putstr(str, arg, flags);
      if (flags.minus) {
        str += i;
        str += widthFlags(str, arg, flags.minus, &i, flags.percision);
      }
      break;
    case '%':
      i = s21_putchar(str, '%');
      break;
    case 'p':
      flags.tag = 1;
      i = s21_puthex(str, va_arg(*ap, unsigned long long), 0, flags, 1);
      break;
    default:
      if (isNumFormat(format)) {
        i = callPutsNumFunc(format, str, flags, ap);
      } else
        i = s21_putchar(str, format);
      break;
  }
  return i;
}