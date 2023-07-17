#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *arr1 = (unsigned char *)str1, *arr2 = (unsigned char *)str2;
  int count = 0;
  if (arr1 != S21_NULL && arr2 != S21_NULL) {
    for (size_t i = 0; i < n; i++) {
      if (arr1[i] < arr2[i] || arr1[i] > arr2[i]) {
        count = arr1[i] - arr2[i];
        break;
      }
    }
  }
  return count;
}