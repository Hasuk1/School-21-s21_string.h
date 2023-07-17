#include "../s21_string.h"

#include <check.h>
#include <stdio.h>
#include <string.h>

/*STRING.H*/

START_TEST(test_s21_memchr) {
  const char *first;
  const char *second;

  first = s21_memchr("Hello world\0", 'w', 5);
  second = memchr("Hello world\0", 'w', 5);
  ck_assert_ptr_eq(first, second);

  first = s21_memchr("Hello world\n\0", 'w', 10);
  second = memchr("Hello world\n\0", 'w', 10);
  ck_assert_ptr_eq(first, second);

  first = s21_memchr("a\n\0", '\n', 3);
  second = memchr("a\n\0", '\n', 3);
  ck_assert_ptr_eq(first, second);

  first = s21_memchr(" \n\0", '\0', 100);
  second = memchr(" \n\0", '\0', 100);
  ck_assert_ptr_eq(first, second);

  first = s21_memchr(" \0", ' ', 1);
  second = memchr(" \0", ' ', 1);
  ck_assert_ptr_eq(first, second);

  first = s21_memchr("\0", '\0', 1);
  second = memchr("\0", '\0', 1);
  ck_assert_ptr_eq(first, second);

  first = s21_memchr("test", 'x', 4);
  second = memchr("test", 'x', 4);
  ck_assert_ptr_eq(first, second);

  first = s21_memchr("", 'x', 0);
  second = memchr("", 'x', 0);
  ck_assert_ptr_eq(first, second);
}
END_TEST

START_TEST(test_s21_memcmp) {
  int first;
  int second;

  char *f1 = "Hello world\0";
  char *s1 = "Hello world\0";
  first = s21_memcmp(f1, s1, 5);
  second = memcmp(f1, s1, 5);
  ck_assert_int_eq(first, second);

  char *f2 = "Hello world\n\0";
  char *s2 = "Hello world\n\0";
  first = s21_memcmp(f2, s2, 13);
  second = memcmp(f2, s2, 13);
  ck_assert_int_eq(first, second);

  char *f3 = " \0";
  char *s3 = "\n\0";
  first = s21_memcmp(f3, s3, 2);
  second = memcmp(f3, s3, 2);
  ck_assert_int_gt(first, 0);
  ck_assert_int_gt(second, 0);

  char *f4 = "H\n\0";
  char *s4 = "a\n\0";
  first = s21_memcmp(f4, s4, 1);
  second = memcmp(f4, s4, 1);
  ck_assert_int_lt(first, 0);
  ck_assert_int_lt(second, 0);

  char *f5 = " \n\0";
  char *s5 = " \0";
  first = s21_memcmp(f5, s5, 2);
  second = memcmp(f5, s5, 2);
  ck_assert_int_eq(first, second);
}
END_TEST

START_TEST(test_s21_memcpy) {
  const char *first;
  const char *second;
  char buffer[100] = "Hello ";

  first = s21_memcpy(buffer, "Hello world\0", 12);
  second = memcpy(buffer, "Hello world\0", 12);
  ck_assert_ptr_eq(first, second);

  first = s21_memcpy(buffer + 6, "world", 5);
  second = memcpy(buffer + 6, "world", 5);
  ck_assert_ptr_eq(first, second);

  first = s21_memcpy(buffer + 11, "", 1);
  second = memcpy(buffer + 11, "", 1);
  ck_assert_ptr_eq(first, second);

  first = s21_memcpy(buffer, "This string is too long to copy", 30);
  second = memcpy(buffer, "This string is too long to copy", 30);
  ck_assert_ptr_eq(first, second);
}
END_TEST

START_TEST(test_s21_memset) {
  const char *first, *second;
  char buffer[100] = "Hello ";

  first = s21_memset(buffer, 'w', 12);
  second = memset(buffer, 'w', 12);
  ck_assert_ptr_eq(first, second);

  first = s21_memset(buffer + 6, '\n', 1);
  second = memset(buffer + 6, '\n', 1);
  ck_assert_ptr_eq(first, second);

  first = s21_memset(buffer, 'a', 5);
  second = memset(buffer, 'a', 5);
  ck_assert_ptr_eq(first, second);

  first = s21_memset(buffer, '\0', 1);
  second = memset(buffer, '\0', 1);
  ck_assert_ptr_eq(first, second);

  first = s21_memset(buffer, ' ', 100);
  second = memset(buffer, ' ', 100);
  ck_assert_ptr_eq(first, second);

  first = s21_memset(buffer, 'p', 2);
  second = memset(buffer, 'p', 2);
  ck_assert_ptr_eq(first, second);
}
END_TEST

START_TEST(test_s21_strncat) {
  const char *first;
  const char *second;
  char s1[100] = "Hello ";

  first = s21_strncat(s1, "world", 2);
  second = strncat(s1, "world", 2);
  ck_assert_str_eq(first, second);

  first = s21_strncat(s1, "", 0);
  second = strncat(s1, "", 0);
  ck_assert_str_eq(first, second);

  memset(s1, '\0', sizeof(s1));
  strcpy(s1, "Hello");
  first = s21_strncat(s1, " world", 10);
  second = strncat(s1, " world", 10);
  ck_assert_str_eq(first, second);

  ck_assert_str_eq(s21_strncat(s1, S21_NULL, 10), s1);
  ck_assert_ptr_eq(s21_strncat(S21_NULL, S21_NULL, 10), S21_NULL);
}
END_TEST

START_TEST(test_s21_strchr) {
  const char *first;
  const char *second;
  char s1[100] = "Hello ";

  first = s21_strchr(s1, ' ');
  second = strchr(s1, ' ');
  ck_assert_ptr_eq(first, second);

  first = s21_strchr(s1, '\0');
  second = strchr(s1, '\0');
  ck_assert_ptr_eq(first, second);

  first = s21_strchr(s1, 'w');
  second = strchr(s1, 'w');
  ck_assert_ptr_eq(first, second);

  s1[0] = '\0';
  first = s21_strchr(s1, 'h');
  second = strchr(s1, 'h');
  ck_assert_ptr_eq(first, second);

  first = s21_strchr(s1, '\0');
  second = strchr(s1, '\0');
  ck_assert_ptr_eq(first, second);
}
END_TEST

START_TEST(test_s21_strncmp) {
  int first;
  int second;

  char *f1 = "Hello world\0";
  char *s1 = "Hello world\0";
  first = s21_strncmp(f1, s1, 5);
  second = strncmp(f1, s1, 5);
  ck_assert_int_eq(first, second);

  char *f2 = "Hello world\n\0";
  char *s2 = "Hello world\n\0";
  first = s21_strncmp(f2, s2, 13);
  second = strncmp(f2, s2, 13);
  ck_assert_int_eq(first, second);

  char *f3 = "a\n\0";
  char *s3 = "Hello world\n\0";
  first = s21_strncmp(f3, s3, 3);
  second = strncmp(f3, s3, 3);
  ck_assert_int_eq(first > 0, second > 0);

  char *f4 = " \n\0";
  char *s4 = "a\n\0";
  first = s21_strncmp(f4, s4, 0);
  second = strncmp(f4, s4, 0);
  ck_assert_int_eq(first, second);

  char *f5 = " \n\0";
  char *s5 = " \0";
  first = s21_strncmp(f5, s5, 2);
  second = strncmp(f5, s5, 2);
  ck_assert_int_eq(first > 0, second > 0);

  char *f6 = " \0";
  char *s6 = "\n\0";
  first = s21_strncmp(f6, s6, 2);
  second = strncmp(f6, s6, 2);
  ck_assert_int_eq(first < 0, second < 0);

  char *f7 = "";
  char *s7 = "Hello world\0";
  first = s21_strncmp(f7, s7, 5);
  second = strncmp(f7, s7, 5);
  ck_assert_int_eq(first < 0, second < 0);

  char *f8 = "test";
  char *s8 = "testing";
  first = s21_strncmp(f8, s8, 4);
  second = strncmp(f8, s8, 4);
  ck_assert_int_eq(first == 0, second == 0);
}
END_TEST

START_TEST(test_s21_strncpy) {
  const char *first;
  const char *second;
  char buffer[100] = "Hello ";

  first = s21_strncpy(buffer, "Hello world\0", 12);
  second = strncpy(buffer, "Hello world\0", 12);
  ck_assert_ptr_eq(first, second);

  first = s21_strncpy(buffer, "world\0", 6);
  second = strncpy(buffer, "world\0", 6);
  ck_assert_ptr_eq(first, second);

  first = s21_strncpy(buffer, "a\n\0", 3);
  second = strncpy(buffer, "a\n\0", 3);
  ck_assert_ptr_eq(first, second);

  first = s21_strncpy(buffer, " \n\0", 4);
  second = strncpy(buffer, " \n\0", 4);
  ck_assert_ptr_eq(first, second);

  first = s21_strncpy(buffer, " \0", 5);
  second = strncpy(buffer, " \0", 5);
  ck_assert_ptr_eq(first, second);

  first = s21_strncpy(buffer, "\n\0", 6);
  second = strncpy(buffer, "\n\0", 6);
  ck_assert_ptr_eq(first, second);

  first = s21_strncpy(buffer, "", 7);
  second = strncpy(buffer, "", 7);
  ck_assert_ptr_eq(first, second);

  first = s21_strncpy(buffer, "Hello world\0", 50);
  second = strncpy(buffer, "Hello world\0", 50);
  ck_assert_ptr_eq(first, second);

  first = s21_strncpy(buffer, "Hello world\0", 12);
  second = strncpy(buffer, "Hello world\0", 12);
  ck_assert_ptr_eq(first, second);
}
END_TEST

START_TEST(test_s21_strcspn) {
  size_t first;
  size_t second;

  char str1[100] = "Hello world\0";
  first = s21_strcspn(str1, "z");
  second = strcspn(str1, "z");
  ck_assert_int_eq(first, second);

  char str2[100] = "Hello world\0";
  first = s21_strcspn(str2, "H");
  second = strcspn(str2, "H");
  ck_assert_int_eq(first, second);

  char str3[100] = "Hello world\0";
  first = s21_strcspn(str3, "\0");
  second = strcspn(str3, "\0");
  ck_assert_int_eq(first, second);

  char str4[100] = "Hello world\0";
  first = s21_strcspn(str4, "o");
  second = strcspn(str4, "o");
  ck_assert_int_eq(first, second);

  char str5[100] = "Hello world\0";
  first = s21_strcspn(str5, "\r\n");
  second = strcspn(str5, "\r\n");
  ck_assert_int_eq(first, second);

  char str6[100] = "Hello world\0";
  first = s21_strcspn(str6, "ow");
  second = strcspn(str6, "ow");
  ck_assert_int_eq(first, second);

  char str7[100] = "Hello world\0";
  first = s21_strcspn(str7, "He");
  second = strcspn(str7, "He");
  ck_assert_int_eq(first, second);

  char str8[100] = "";
  first = s21_strcspn(str8, "a");
  second = strcspn(str8, "a");
  ck_assert_int_eq(first, second);

  char str9[100] = "Hello world\0";
  first = s21_strcspn(str9, "");
  second = strcspn(str9, "");
  ck_assert_int_eq(first, second);
}
END_TEST

START_TEST(test_s21_strerror) {
  for (int i = -123; i < 0; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }

  for (int i = 0; i <= 106; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }

  for (int i = 107; i <= 234; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(test_s21_strlen) {
  const char *str;
  size_t expected_len, actual_len;

  str = "";
  expected_len = strlen(str);
  actual_len = s21_strlen(str);
  ck_assert_int_eq(expected_len, actual_len);

  str = "a";
  expected_len = strlen(str);
  actual_len = s21_strlen(str);
  ck_assert_int_eq(expected_len, actual_len);

  str = "Hello, world!";
  expected_len = strlen(str);
  actual_len = s21_strlen(str);
  ck_assert_int_eq(expected_len, actual_len);

  str = "    ";
  expected_len = strlen(str);
  actual_len = s21_strlen(str);
  ck_assert_int_eq(expected_len, actual_len);

  str = "S21_NULL\0characters";
  expected_len = strlen(str);
  actual_len = s21_strlen(str);
  ck_assert_int_eq(expected_len, actual_len);

  str = "1234567890";
  expected_len = strlen(str);
  actual_len = s21_strlen(str);
  ck_assert_int_eq(expected_len, actual_len);

  str = "This is a very long string that is longer than the buffer size.";
  expected_len = strlen(str);
  actual_len = s21_strlen(str);
  ck_assert_int_eq(expected_len, actual_len);
}
END_TEST

START_TEST(test_s21_strpbrk) {
  const char *str;
  const char *accept;
  char *expected_res, *actual_res;

  str = "Hello, world!";
  accept = "1234567890";
  expected_res = strpbrk(str, accept);
  actual_res = s21_strpbrk(str, accept);
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "Hello, world!";
  accept = ",";
  expected_res = strpbrk(str, accept);
  actual_res = s21_strpbrk(str, accept);
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "The quick brown fox jumps over the lazy dog.";
  accept = "aeiou";
  expected_res = strpbrk(str, accept);
  actual_res = s21_strpbrk(str, accept);
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "aaaaaaaaaa";
  accept = "a";
  expected_res = strpbrk(str, accept);
  actual_res = s21_strpbrk(str, accept);
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "S21_NULL\0characters";
  accept = "\0";
  expected_res = strpbrk(str, accept);
  actual_res = s21_strpbrk(str, accept);
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "abcdefghijklmnopqrstuvwxyz";
  accept = "";
  expected_res = strpbrk(str, accept);
  actual_res = s21_strpbrk(str, accept);
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "This is a very long string that is longer than the buffer size.";
  accept = "s";
  expected_res = strpbrk(str, accept);
  actual_res = s21_strpbrk(str, accept);
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "Hello, world!";
  accept = "1234567890";
  expected_res = strpbrk(str, accept);
  actual_res = s21_strpbrk(str, accept);
  ck_assert_ptr_eq(expected_res, actual_res);
}
END_TEST

START_TEST(test_s21_strrchr) {
  const char *str;
  const char ch = 'o';
  char *expected_res, *actual_res;

  str = "Hello, world!";
  expected_res = strrchr(str, ch);
  actual_res = s21_strrchr(str, ch);
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "Hello, world!";
  expected_res = strrchr(str, ',');
  actual_res = s21_strrchr(str, ',');
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "The quick brown fox jumps over the lazy dog.";
  expected_res = strrchr(str, 'o');
  actual_res = s21_strrchr(str, 'o');
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "oooooooooo";
  expected_res = strrchr(str, 'o');
  actual_res = s21_strrchr(str, 'o');
  ck_assert_ptr_eq(expected_res, actual_res);

  str = "abcdefghijklmnopqrstuvwxyz";
  expected_res = strrchr(str, '1');
  actual_res = s21_strrchr(str, '1');
  ck_assert_ptr_eq(expected_res, actual_res);

  char buffer[100] =
      "This is a very long string that is longer than the buffer size.";
  expected_res = strrchr(buffer, 's');
  actual_res = s21_strrchr(buffer, 's');
  ck_assert_ptr_eq(expected_res, actual_res);

  char str1[] = "Hello, Mel";
  int c1 = 'e';
  ck_assert_ptr_eq(s21_strrchr(str1, c1), strrchr(str1, c1));

  char str2[] = "Hello, Mel";
  int c2 = 'p';
  ck_assert_ptr_eq(s21_strrchr(str2, c2), strrchr(str2, c2));

  char str3[] = "";
  int c3 = 'l';
  ck_assert_ptr_eq(s21_strrchr(str3, c3), strrchr(str3, c3));

  char str4[] = "Hello";
  int c4 = 0;
  ck_assert_ptr_eq(s21_strrchr(str4, c4), strrchr(str4, c4));

  char str5[] = "Hello";
  int c5 = 'o';
  ck_assert_ptr_eq(s21_strrchr(str5, c5), strrchr(str5, c5));
}
END_TEST

START_TEST(s21_strrchr_edge_cases_test) {
  char str1[] = "";
  int c1 = 'e';
  ck_assert_ptr_eq(s21_strrchr(str1, c1), strrchr(str1, c1));

  char str2[] = "Hello, Mel";
  int c2 = 'z';
  ck_assert_ptr_eq(s21_strrchr(str2, c2), strrchr(str2, c2));

  char str3[] = "Hello, Mel";
  int c3 = 'H';
  ck_assert_ptr_eq(s21_strrchr(str3, c3), strrchr(str3, c3));

  char str4[] = "Hello, Mel";
  int c4 = 'M';
  ck_assert_ptr_eq(s21_strrchr(str4, c4), strrchr(str4, c4));

  char str5[] = "Hello, Mel";
  int c5 = 'l';
  ck_assert_ptr_eq(s21_strrchr(str5, c5), strrchr(str5, c5));

  ck_assert_ptr_eq(s21_strrchr(S21_NULL, c5), S21_NULL);
}
END_TEST

START_TEST(test_s21_strstr) {
  const char *str1;
  const char *str2;
  char *expected_res, *actual_res;

  str1 = "The quick brown fox jumps over the lazy dog.";
  str2 = "brown fox";
  expected_res = strstr(str1, str2);
  actual_res = s21_strstr(str1, str2);
  ck_assert_ptr_eq(expected_res, actual_res);

  str1 = "The quick brown fox jumps over the lazy dog.";
  str2 = "doggy";
  expected_res = strstr(str1, str2);
  actual_res = s21_strstr(str1, str2);
  ck_assert_ptr_eq(expected_res, actual_res);

  str1 = "The quick brown fox jumps over the lazy dog.";
  str2 = "The quick";
  expected_res = strstr(str1, str2);
  actual_res = s21_strstr(str1, str2);
  ck_assert_ptr_eq(expected_res, actual_res);

  str1 = "The quick brown fox jumps over the lazy dog.";
  str2 = "lazy dog.";
  expected_res = strstr(str1, str2);
  actual_res = s21_strstr(str1, str2);
  ck_assert_ptr_eq(expected_res, actual_res);

  str1 = "The quick brown fox jumps over the lazy dog.";
  str2 = "";
  expected_res = strstr(str1, str2);
  actual_res = s21_strstr(str1, str2);
  ck_assert_ptr_eq(expected_res, actual_res);

  str1 = "The quick brown fox jumps over the lazy dog.";
  str2 = "The quick brown fox jumps over the lazy dog.";
  expected_res = strstr(str1, str2);
  actual_res = s21_strstr(str1, str2);
  ck_assert_ptr_eq(expected_res, actual_res);

  str1 = "This is a very long string that is longer than the buffer size.";
  str2 = "missing";
  expected_res = strstr(str1, str2);
  actual_res = s21_strstr(str1, str2);
  ck_assert_ptr_eq(expected_res, actual_res);

  str1 = "short";
  str2 = "longer";
  expected_res = strstr(str1, str2);
  actual_res = s21_strstr(str1, str2);
  ck_assert_ptr_eq(expected_res, actual_res);

  str1 = "";
  str2 = "";
  expected_res = strstr(str1, str2);
  actual_res = s21_strstr(str1, str2);
  ck_assert_ptr_eq(expected_res, actual_res);

  actual_res = s21_strstr(S21_NULL, S21_NULL);
  ck_assert_ptr_eq(S21_NULL, actual_res);
}
END_TEST

START_TEST(test_s21_strtok) {
  char str[] = "The quick brown fox jumps over the lazy dog.";
  const char *delim = " ";
  char *expected_res, *actual_res;

  expected_res = strtok(str, delim);
  actual_res = s21_strtok(str, delim);
  ck_assert_ptr_eq(expected_res, actual_res);

  char str2[] = "The_quick_brown_fox_jumps_over_the_lazy_dog.";
  delim = "";
  expected_res = strtok(str2, delim);
  actual_res = s21_strtok(str2, delim);
  ck_assert_ptr_eq(expected_res, actual_res);

  char str3[] = "12345";
  delim = "12345";
  expected_res = strtok(str3, delim);
  actual_res = s21_strtok(str3, delim);
  ck_assert_ptr_eq(expected_res, actual_res);

  char str4[30] = "School-21";
  ck_assert_str_eq(s21_strtok(str4, "-"), strtok(str4, "-"));
  ck_assert_str_eq(s21_strtok(str4, ""), strtok(str4, ""));
  ck_assert_str_eq(s21_strtok(str4, "oo"), strtok(str4, "oo"));
  ck_assert_str_eq(s21_strtok(str4, "Sc"), strtok(str4, "Sc"));
  ck_assert_str_eq(s21_strtok(str4, "21"), strtok(str4, "21"));

  ck_assert_ptr_eq(s21_strtok(S21_NULL, "12"), S21_NULL);

  char str5[30] = "+++++";
  ck_assert_ptr_eq(s21_strtok(str5, "+"), strtok(str5, "+"));
  ck_assert_ptr_eq(s21_strtok(str5, "+"), strtok(str5, "+"));
  ck_assert_ptr_eq(s21_strtok(str5, "+"), strtok(str5, "+"));
  ck_assert_ptr_eq(s21_strtok(str5, "+"), strtok(str5, "+"));
  ck_assert_ptr_eq(s21_strtok(str5, "+"), strtok(str5, "+"));
}
END_TEST

/*SPECIAL*/

START_TEST(test_s21_to_upper) {
  char str1[] = "simple", compare1[] = "SIMPLE";
  char *got1 = s21_to_upper(str1);
  ck_assert_pstr_eq(got1, compare1);
  free(got1);

  char str2[] = "We aRe TrYiNG heRe TO GEt upper strIng",
       compare2[] = "WE ARE TRYING HERE TO GET UPPER STRING";
  char *got2 = s21_to_upper(str2);
  ck_assert_pstr_eq(got2, compare2);
  free(got2);

  char str3[] =
      "(LeTs Test, somE LinES***$ wiTh ADDITIONAL:: &12342 syMBOls 0 -+ )",
       compare3[] =
           "(LETS TEST, SOME LINES***$ WITH ADDITIONAL:: &12342 SYMBOLS 0 -+ )";
  char *got3 = s21_to_upper(str3);
  ck_assert_pstr_eq(got3, compare3);
  free(got3);

  char str4[] = "", compare4[] = "";
  char *got4 = s21_to_upper(str4);
  ck_assert_pstr_eq(got4, compare4);
  free(got4);

  char str5[1024] = {0};
  memset(str5, 'a', 1023);
  char *got5 = s21_to_upper(str5);
  ck_assert_ptr_nonnull(got5);
  ck_assert_uint_eq('A', got5[0]);
  free(got5);

  char str6[] = "a", compare6[] = "A";
  char *got6 = s21_to_upper(str6);
  ck_assert_str_eq(compare6, got6);
  free(got6);

  char str7[] = "Z", compare7[] = "Z";
  char *got7 = s21_to_upper(str7);
  ck_assert_str_eq(compare7, got7);
  free(got7);

  char *got8 = s21_to_upper(S21_NULL);
  ck_assert_ptr_eq(S21_NULL, got8);
}
END_TEST

START_TEST(test_s21_to_lower_h) {
  char str1[] = "SIMPLE";
  char compare1[] = "simple";
  char *got1 = s21_to_lower(str1);
  ck_assert_ptr_nonnull(got1);
  if (got1 != S21_NULL) {
    ck_assert_pstr_eq(got1, compare1);
    free(got1);
  }

  char str2[] = "We aRe TrYiNG heRe TO GEt LOWER strIng";
  char compare2[] = "we are trying here to get lower string";
  char *got2 = s21_to_lower(str2);
  ck_assert_ptr_nonnull(got2);
  if (got2 != S21_NULL) {
    ck_assert_pstr_eq(got2, compare2);
    free(got2);
  }

  char str3[] =
      "(LeTs Test, somE LinES***$ wiTh ADDITIONAL:: &12342 syMBOls 0 -+ )";
  char compare3[] =
      "(lets test, some lines***$ with additional:: &12342 symbols 0 -+ )";
  char *got3 = s21_to_lower(str3);
  ck_assert_ptr_nonnull(got3);
  if (got3 != S21_NULL) {
    ck_assert_pstr_eq(got3, compare3);
    free(got3);
  }

  char str4[] = "";
  char compare4[] = "";
  char *got4 = s21_to_lower(str4);
  ck_assert_ptr_nonnull(got4);
  if (got4 != S21_NULL) {
    ck_assert_pstr_eq(got4, compare4);
    free(got4);
  }

  char *got5 = s21_to_lower(S21_NULL);
  ck_assert_ptr_null(got5);
}
END_TEST

START_TEST(test_s21_insert) {
  char *str1 = "Aboba";
  char *in1 = "kek";
  char *result1 = S21_NULL;
  result1 = (char *)s21_insert(str1, in1, 2);
  ck_assert_str_eq(result1, "Abkekoba");
  free(result1);

  char *str2 = "Aboba";
  char *in2 = "kek";
  char *result2 = S21_NULL;
  result2 = (char *)s21_insert(str2, in2, 5);
  ck_assert_str_eq(result2, "Abobakek");
  free(result2);

  char *str3 = "";
  char *in3 = "k ek";
  char *result3 = (char *)s21_insert(str3, in3, 0);
  ck_assert_str_eq(result3, "k ek");
  free(result3);

  char *str4 = "Aboba   ";
  char *in4 = "k ek";
  char *result4 = (char *)s21_insert(str4, in4, 0);
  ck_assert_str_eq(result4, "k ekAboba   ");
  free(result4);

  char *str5 = "Aboba   ";
  char *in5 = S21_NULL;
  char *result5 = (char *)s21_insert(str5, in5, 6);
  ck_assert_ptr_eq(result5, S21_NULL);
  free(result5);

  char *str6 = S21_NULL;
  char *in6 = "k ek";
  char *result6 = (char *)s21_insert(str6, in6, 8);
  ck_assert_ptr_eq(result6, S21_NULL);
  free(result6);

  char *str7 = "Aboba   ";
  char *in7 = "k ek";
  char *result7 = (char *)s21_insert(str7, in7, -1);
  ck_assert_ptr_eq(result7, S21_NULL);
}
END_TEST

START_TEST(s21_insert_test_1) {
  char test_str[50] = {"Hello, World!"};
  char ins[50] = {"_hop-hey lalaley_"};
  s21_size_t index = 0;
  char out_expected[50] = {"_hop-hey lalaley_Hello, World!"};
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_str_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_2) {
  char test_str[50] = {"Hello, World!"};
  char ins[50] = {"_hop-hey lalaley_"};
  s21_size_t index = 6;
  char out_expected[50] = {"Hello,_hop-hey lalaley_ World!"};
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_str_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_3) {
  char test_str[50] = {"Hello, World!"};
  char ins[50] = {"_hop-hey lalaley_"};
  s21_size_t index = 50;
  char *out_expected = S21_NULL;
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_5) {
  char *test_str = S21_NULL;
  char *ins = S21_NULL;
  s21_size_t index = 10;
  char *out_expected = S21_NULL;
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_trim_test) {
  char *str1 = "WoW, I love it!";
  char *ptr1 = "W";
  char *res1 = (char *)s21_trim(str1, ptr1);
  ck_assert_str_eq(res1, "oW, I love it!");
  free(res1);

  char *str2 = "WoW\0, I love it!";
  char *ptr2 = "W";
  char *res2 = (char *)s21_trim(str2, ptr2);
  ck_assert_str_eq(res2, "o");
  free(res2);

  char *str3 = "WoW, I love it!";
  char *ptr3 = "Wo!";
  char *res3 = (char *)s21_trim(str3, ptr3);
  ck_assert_str_eq(res3, ", I love it");
  free(res3);

  char *str4 = "WoW, I love it!";
  char *ptr4 = "P";
  char *res4 = (char *)s21_trim(str4, ptr4);
  ck_assert_str_eq(res4, "WoW, I love it!");
  free(res4);

  char *str5 = "abc";
  char *ptr5 = "abc";
  char *res5 = (char *)s21_trim(str5, ptr5);
  ck_assert_str_eq(res5, "");
  free(res5);

  char *str6 = "     HELLO    ";
  char *ptr6 = " ";
  char *res6 = (char *)s21_trim(str6, ptr6);
  ck_assert_str_eq(res6, "HELLO");
  free(res6);
  char *str7 = "     HELLO    ";
  char *ptr7 = S21_NULL;
  char *res7 = (char *)s21_trim(str7, ptr7);
  ck_assert_str_eq(res7, "HELLO");
  free(res7);
}
END_TEST

START_TEST(s21_trim_test_1) {
  char test_str[50] = {""};
  char trims[50] = {""};
  char out_expected[50] = {""};
  char *out_s21 = s21_trim(test_str, trims);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_trim_test_2) {
  char test_str[50] = {""};
  char trims[50] = {"@#$<fuck up>$%^"};
  char out_expected[50] = {""};
  char *out_s21 = s21_trim(test_str, trims);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_trim_test_3) {
  char test_str[50] = {"  <^ u%p>   Hello, World!c $ #@ k  "};
  char trims[50] = {""};
  char out_expected[50] = {"<^ u%p>   Hello, World!c $ #@ k"};
  char *out_s21 = s21_trim(test_str, trims);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

/*SPRINTF*/

START_TEST(test_s21_sprintf_с) {
  char buff[70] = {0};
  char s21_buff[70] = {0};

  int x6 = 12345;
  char *format_string3 = "%+.*d\n";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string3, 8, 4, x6),
                   sprintf(buff, format_string3, 8, 4, x6));
  ck_assert_str_eq(buff, s21_buff);

  short x7 = -32768;
  char *format_string4 = "%hd\n";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string4, x7),
                   sprintf(buff, format_string4, x7));
  ck_assert_str_eq(buff, s21_buff);

  float x8 = 123.456;
  char *format_string5 = "% 010.2f\n";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string5, x8),
                   sprintf(buff, format_string5, x8));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_d_1) {
  char buff[70] = {0};
  char s21_buff[70] = {0};
  int x1 = 234;
  int x2 = -345;
  char *format_string1 = "love %+d % d love";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string1, x1, x2),
                   sprintf(buff, format_string1, x1, x2));
  ck_assert_str_eq(buff, s21_buff);

  int x5 = 2342;
  int x6 = -345;
  char *format_string3 = "love %+10d %-10d love";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string3, x5, x6),
                   sprintf(buff, format_string3, x5, x6));
  ck_assert_str_eq(buff, s21_buff);

  char *format_string4 = "precision test %.0d %.d %.*d";
  int x7 = 0;
  int x8 = 0;
  int x9 = 3;
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string4, x7, x8, x9, x1),
                   sprintf(buff, format_string4, x7, x8, x9, x1));
  ck_assert_str_eq(buff, s21_buff);
  int x10 = 123;
  char *format_string6 = "flag test %+d % d %#x %o %010d";
  unsigned int x12 = 42;
  int x13 = -42;
  ck_assert_int_eq(
      s21_sprintf(s21_buff, format_string6, x12, x13, x12, x12, x10),
      sprintf(buff, format_string6, x12, x13, x12, x12, x10));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_d_2) {
  char s21_buff[200] = {};
  char buff[200] = {};

  char *format_string1 = "%ld, %+-10.8d, % d, % -*.10d, %*d, %-20.10hd, %.0d";
  int res21 = s21_sprintf(s21_buff, format_string1, 12345, 321, 4444, 25, 55555,
                          10, 1, 22, 0);
  int res =
      sprintf(buff, format_string1, 12345, 321, 4444, 25, 55555, 10, 1, 22, 0);
  ck_assert_int_eq(res21, res);
  ck_assert_str_eq(s21_buff, buff);

  char *format_string2 = "%10ld, %-10ld, %+5hd, %20Lf, %-5hu";
  res21 =
      s21_sprintf(s21_buff, format_string2, __INT_MAX__, INT_MIN, SHRT_MAX - 1,
                  (long double)99999999999999999 - 10, (unsigned short int)225);
  res = sprintf(buff, format_string2, __INT_MAX__, INT_MIN, SHRT_MAX - 1,
                (long double)99999999999999999 - 10, (unsigned short int)225);
  ck_assert_int_eq(res21, res);
  ck_assert_str_eq(s21_buff, buff);
}
END_TEST

START_TEST(test_s21_sprintf_i) {
  char buff[70] = {0};
  char s21_buff[70] = {0};
  long int x3 = 2323454;
  short int x4 = 3;
  char *format_string2 = "love %-3li %+03hi love";
  ck_assert_int_eq(s21_sprintf(buff, format_string2, x3, x4),
                   sprintf(s21_buff, format_string2, x3, x4));

  int x1 = 0x234;
  int x2 = 0x345;
  int input = 10;
  char *format_string1 = "love %*i %i love";
  ck_assert_int_eq(s21_sprintf(buff, format_string1, input, x1, x2),
                   sprintf(s21_buff, format_string1, input, x1, x2));
}
END_TEST

START_TEST(test_s21_sprintf_e_1) {
  char buff[100];
  char s21_buff[100];

  double x1 = 12345.2345;
  int input_width = 8;
  int input_precision = 2;
  char *format_string1 = "love %*.*e % E love";
  ck_assert_int_eq(
      s21_sprintf(s21_buff, format_string1, input_width, input_precision, x1,
                  x1),
      sprintf(buff, format_string1, input_width, input_precision, x1, x1));
  ck_assert_str_eq(buff, s21_buff);

  char *format_string5 = "love %*e love";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string5, 10, x1),
                   sprintf(buff, format_string5, 10, x1));
  ck_assert_str_eq(buff, s21_buff);

  char *format_string6 = "love %.*e love";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string6, 4, x1),
                   sprintf(buff, format_string6, 4, x1));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_e_2) {
  char s21_buff[200] = {};
  char buff[200] = {};

  char *format_string = "love %*.*e % E love";
  int res21 = s21_sprintf(s21_buff, format_string, 312.1121, 444.1231,
                          (long double)444.1, 55.142241, 10, 1.1, 555.123123, 1,
                          88.111, 4321.12);
  int res = sprintf(buff, format_string, 312.1121, 444.1231, (long double)444.1,
                    55.142241, 10, 1.1, 555.123123, 1, 88.111, 4321.12);
  ck_assert_int_eq(res21, res);
  ck_assert_str_eq(s21_buff, buff);
}
END_TEST

START_TEST(test_s21_sprintf_f_1) {
  char buff[70] = {0};
  char s21_buff[70] = {0};
  float x11 = 234.123;
  float x21 = -345.678;
  char *format_string11 = "love %.f %+f love";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string11, x11, x21),
                   sprintf(buff, format_string11, x11, x21));
  ck_assert_str_eq(s21_buff, buff);
  long double x31 = 21234.23434;
  long double x41 = -3234.56788;
  char *format_string21 = "love %10.2Lf %+.4Lf love";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string21, x31, x41),
                   sprintf(buff, format_string21, x31, x41));
  ck_assert_str_eq(s21_buff, buff);
  double x51 = 0.2341;
  double x61 = -12345;
  char *format_string31 = "love %#f %010f love";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string31, x51, x61),
                   sprintf(buff, format_string31, x51, x61));
  ck_assert_str_eq(s21_buff, buff);
  float x1 = 234.123;
  float width1 = -1.55;
  char *format_string1 = "%f";
  s21_sprintf(s21_buff, format_string1, width1, x1);
  sprintf(buff, format_string1, width1, x1);
  ck_assert_str_eq(s21_buff, buff);

  float x2 = -345.678;
  int width2 = 10;
  int precision2 = -0.5;
  char *format_string2 = "%*.*f";
  ck_assert_int_eq(
      s21_sprintf(s21_buff, format_string2, width2, precision2, x2),
      sprintf(buff, format_string2, width2, precision2, x2));
  ck_assert_str_eq(s21_buff, buff);
  long double x3 = 21234.23434;
  int precision3 = 4;
  char *format_string3 = "%.*Lf";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string3, precision3, x3),
                   sprintf(buff, format_string3, precision3, x3));
  ck_assert_str_eq(s21_buff, buff);
  long double x4 = -3234.56788;
  int precision4 = 4;
  char *format_string4 = "%.*Lf";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string4, precision4, x4),
                   sprintf(buff, format_string4, precision4, x4));
  ck_assert_str_eq(s21_buff, buff);
  long double x7 = 12345.6789;
  char *format_string7 = "%Lf";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string7, x7),
                   sprintf(buff, format_string7, x7));
  ck_assert_str_eq(s21_buff, buff);
}
END_TEST

START_TEST(test_s21_sprintf_f_2) {
  char s21_buff[200] = {};
  char buff[200] = {};
  const char *format_string =
      "%f, % -025.10f, % Lf, % 020.2f, %*f, %.3f, %.*f, %-10f";
  int res21 = s21_sprintf(s21_buff, format_string, 312.1121, 444.1231,
                          (long double)444.1, 555555.1, 10, 1.1, 555.123123, 1,
                          55555.111, 4321.1);
  int res = sprintf(buff, format_string, 312.1121, 444.1231, (long double)444.1,
                    555555.1, 10, 1.1, 555.123123, 1, 55555.111, 4321.1);
  ck_assert_int_eq(res21, res);
  ck_assert_str_eq(s21_buff, buff);
}
END_TEST

START_TEST(test_s21_sprintf_g_G) {
  int res = 0;
  int resBI = 0;
  char result[200] = {};
  char resultBI[200] = {};
  const char *test11 = "%g, % -025.10g, % g, % 020.2g, %6g, %.3G, %.10G, %-10G";
  res = s21_sprintf(result, test11, 312.1121, 444.1231, 444.1, 56.199241, 1.1,
                    (double)123.456, (double)55555.111, 4321.1);
  resBI = sprintf(resultBI, test11, 312.1121, 444.1231, 444.1, 56.199241, 1.1,
                  (double)123.456, (double)55555.111, 4321.1);
  ck_assert_str_eq(result, resultBI);
  ck_assert_int_eq(res, resBI);
}
END_TEST

START_TEST(test_s21_sprintf_o_1) {
  char buff[70] = {0};
  char s21_buff[70] = {0};

  int x1 = 234234;
  unsigned short x2 = 34;

  char *format_string1 = "love %o %o %o love";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string1, x1, x2, x1),
                   sprintf(buff, format_string1, x1, x2, x1));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_o_2) {
  char s21_buff[200] = {};
  char buff[200] = {};
  const char *format_string =
      "%#20.20o, %#.20o, %#020.20o, %#-030.20o, %lo, %ho";
  int res21 =
      s21_sprintf(s21_buff, format_string, 255, -255, 123321, 123, 225, 333);
  int res = sprintf(buff, format_string, 255, -255, 123321, 123, 225, 333);
  ck_assert_int_eq(res21, res);
  ck_assert_str_eq(s21_buff, buff);
}
END_TEST

START_TEST(test_s21_sprintf_s_1) {
  char buff[70] = {0};
  char s21_buff[70] = {0};
  char *x1 = "you";
  char *x2 = "peer";
  char *format_string1 = "%10.2s my favourite %-10s";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string1, x1, x2),
                   sprintf(buff, format_string1, x1, x2));
  ck_assert_str_eq(buff, s21_buff);

  double d = 3.14159265358979323846;
  char *format_string5 = "%.*s";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string5, 3, "hello world"),
                   sprintf(buff, format_string5, 3, "hello world"));
  ck_assert_str_eq(buff, s21_buff);

  char *format_string6 = "%10.2f";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string6, d),
                   sprintf(buff, format_string6, d));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_s_2) {
  char s21_buff[200] = {};
  char buff[200] = {};
  const char *format_string = "%s, %4s, %.2s, %5.2s, %-*s";
  int res21 = s21_sprintf(s21_buff, format_string, "hello world", "hello",
                          "hello", "hello w", 10, "hellow");
  int res = sprintf(buff, format_string, "hello world", "hello", "hello",
                    "hello w", 10, "hellow");
  ck_assert_int_eq(res21, res);
  ck_assert_str_eq(s21_buff, buff);
}
END_TEST

START_TEST(test_s21_sprintf_u_1) {
  char buff[70] = {0};
  char s21_buff[70] = {0};
  unsigned int x1 = 234;
  unsigned int x2 = 345;
  char *format_string1 = "love %u %u love";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string1, x1, x2),
                   sprintf(buff, format_string1, x1, x2));
  ck_assert_str_eq(buff, s21_buff);

  long unsigned int x3 = 2323454;
  short unsigned int x4 = 3;
  char *format_string2 = "love %lu %hu love";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string2, x3, x4),
                   sprintf(buff, format_string2, x3, x4));
  ck_assert_str_eq(buff, s21_buff);

  unsigned int x5 = 2342;
  unsigned int x6 = 345;

  char *format_string3 = "love %10u %10u love";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string3, x5, x6),
                   sprintf(buff, format_string3, x5, x6));
  ck_assert_str_eq(buff, s21_buff);

  format_string3 = "love %#-010X %#08x % 10o %+d %.2f love";
  double x12 = 1.23456789;
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string3, x5, x6, x5, -5, x12),
                   sprintf(buff, format_string3, x5, x6, x5, -5, x12));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_u_2) {
  char s21_buff[200] = {};
  char buff[200] = {};
  const char *format_string = "%hu, %.3u, %10u, %-10u";
  int res21 =
      s21_sprintf(s21_buff, format_string, (unsigned int)12345,
                  (unsigned int)32122, (unsigned int)4444, (unsigned int)0);
  int res = sprintf(buff, format_string, (unsigned int)12345,
                    (unsigned int)32122, (unsigned int)4444, (unsigned int)0);
  ck_assert_int_eq(res21, res);
  ck_assert_str_eq(s21_buff, buff);
}
END_TEST

START_TEST(test_s21_sprintf_x_1) {
  char buff[70] = {0};
  char s21_buff[70] = {0};

  long int x3 = 23423423;
  long int x4 = 3451231;
  char *format_string2 = "love %#lx %#lX love";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string2, x3, x4),
                   sprintf(buff, format_string2, x3, x4));
  ck_assert_str_eq(buff, s21_buff);

  long int x = 4095;
  char *format_string = "%03X";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_x_2) {
  char buff[70] = {0};
  char s21_buff[70] = {0};

  long int x = 65535;
  char *format_string = "%X";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);

  long int x1 = 255;
  char *format_string1 = "0x%x";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string1, x1),
                   sprintf(buff, format_string1, x1));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_x_3) {
  char buff[70] = {0};
  char s21_buff[70] = {0};

  long int x = 255;
  char *format_string = "0x%X";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_x_4) {
  char buff[70] = {0};
  char s21_buff[70] = {0};

  long int x = 4095;
  char *format_string = "%03X";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_x_X) {
  char s21_buff[200] = {};
  char buff[200] = {};
  const char *format_string =
      "%#20.20x, %#.20X, %#020.20X, %#-030.20X, %lx, %hX";
  int res21 = s21_sprintf(s21_buff, format_string, 255, -255, 123321, 123,
                          (long int)225, (short int)333);
  int res = sprintf(buff, format_string, 255, -255, 123321, 123, (long int)225,
                    (short int)333);
  ck_assert_int_eq(res21, res);
  ck_assert_str_eq(s21_buff, buff);
}
END_TEST

START_TEST(test_s21_sprintf_p_1) {
  char buff[70] = {0};
  char s21_buff[70] = {0};
  int x1 = 234;
  int x2 = 345;
  ck_assert_int_eq(s21_sprintf(s21_buff, "love %10p %-10p love", &x1, &x2),
                   sprintf(buff, "love %10p %-10p love", &x1, &x2));
  ck_assert_str_eq(s21_buff, buff);
}
END_TEST

START_TEST(test_s21_sprintf_p_2) {
  char s21_buff[200] = {0};
  char buff[200] = {0};
  const char *format_string = "%30.20p, %20.20p, %-20p, %-020p, %-030.20p";
  int res21 = s21_sprintf(s21_buff, format_string, s21_buff, buff, s21_buff,
                          buff, s21_buff);
  int res =
      sprintf(buff, format_string, s21_buff, buff, s21_buff, buff, s21_buff);
  ck_assert_int_eq(res21, res);
  ck_assert_str_eq(s21_buff, buff);
}
END_TEST

START_TEST(test_s21_sprintf_percent) {
  char buff[100] = {0};
  char s21_buff[100] = {0};
  char *format_string1 = "love %% love";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string1),
                   sprintf(buff, format_string1));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_flags) {
  char buff[100] = {0};
  char s21_buff[100] = {0};
  int x = 42;
  char *format_string = "%-10d";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%+d";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "% d";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%#x";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%05d";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_width) {
  char buff[100] = {0};
  char s21_buff[100] = {0};
  int x = 42;
  char *format_string = "%5d";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%*d";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, 5, x),
                   sprintf(buff, format_string, 5, x));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_length) {
  char buff[100] = {0};
  char s21_buff[100] = {0};
  short y = 12345;
  long z = 987654321;
  long long w = 123456789012345;

  char *format_string = "%hd";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, y),
                   sprintf(buff, format_string, y));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%ld";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, z),
                   sprintf(buff, format_string, z));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%lld";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, w),
                   sprintf(buff, format_string, w));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

START_TEST(test_s21_sprintf_precision) {
  char buff[100] = {0};
  char s21_buff[100] = {0};
  double x = 3.141592653589793;
  float y = 2.71828;
  int z = 42;

  char *format_string = "%.2f";

  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%.3f";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, x),
                   sprintf(buff, format_string, x));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%.1f";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, y),
                   sprintf(buff, format_string, y));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%.4f";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, y),
                   sprintf(buff, format_string, y));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%.3d";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, z),
                   sprintf(buff, format_string, z));
  ck_assert_str_eq(buff, s21_buff);

  format_string = "%.6d";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string, z),
                   sprintf(buff, format_string, z));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

/*SSCANF*/

START_TEST(test_s21_sscanf_c) {
  char x1, x2, y1, y2;
  ck_assert_int_eq(sscanf("0 a", "%c %c", &x1, &x2),
                   s21_sscanf("0 a", "%c %c", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x2, y2);

  ck_assert_int_eq(sscanf("0.a", "%c.%c", &x1, &x2),
                   s21_sscanf("0.a", "%c.%c", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x2, y2);

  ck_assert_int_eq(sscanf("   aaaaaa", "%*3c%c", &x1),
                   s21_sscanf("   aaaaaa", "%*3c%c", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("   a", "%4c", &x1), s21_sscanf("   a", "%4c", &y1));
  ck_assert_int_eq(x1, y1);
}
END_TEST

START_TEST(test_s21_sscanf_d_0) {
  long x11 = 0, y11 = 0;
  long long x21 = 0, y21 = 0;
  ck_assert_int_eq(
      sscanf("4294967594 7 4294967299", "%ld%*d%lld", &x11, &x21),
      s21_sscanf("4294967594 7 4294967299", "%ld%*d%lld", &y11, &y21));
}
END_TEST

START_TEST(test_s21_sscanf_d) {
  int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
  long long x21 = 0, y21 = 0;
  ck_assert_int_eq(sscanf("298/02", "%d%*c%d", &x1, &x2),
                   s21_sscanf("298/02", "%d%*c%d", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x2, y2);

  ck_assert_int_eq(sscanf("298\n\t 3.1", "%d%d", &x1, &x2),
                   s21_sscanf("298\n\t 3.1", "%d%d", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x2, y2);

  ck_assert_int_eq(sscanf("2147483648\n\t 3.1", "%lld %d", &x21, &x2),
                   s21_sscanf("2147483648\n\t 3.1", "%lld %d", &y21, &y2));
  ck_assert_int_eq(x21, y21);
  ck_assert_int_eq(x2, y2);

  short int x4 = 0, y4 = 0;
  ck_assert_int_eq(sscanf("298 3", "%d%hd", &x1, &x4),
                   s21_sscanf("298 3", "%d%hd", &y1, &y4));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x4, y4);

  char x3 = 0, y3 = 0;
  ck_assert_int_eq(sscanf("298 3", "%hhd%hd", &x3, &x4),
                   s21_sscanf("298 3", "%hhd%hd", &y3, &y4));
  ck_assert_int_eq(x3, y3);
  ck_assert_int_eq(x4, y4);
}
END_TEST

START_TEST(test_s21_sscanf_d_w) {
  int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
  ck_assert_int_eq(sscanf("-298 +3", "%d%d", &x1, &x2),
                   s21_sscanf("-298 +3", "%d%d", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x2, y2);

  ck_assert_int_eq(sscanf("298 002", "%2d%3d", &x1, &x2),
                   s21_sscanf("298 002", "%2d%3d", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x2, y2);
}
END_TEST

START_TEST(test_s21_sscanf_i_1) {
  unsigned x1, y1;
  short x2, y2;
  ck_assert_int_eq(sscanf("0xab 298", "%i%hi", &x1, &x2),
                   s21_sscanf("0xab 298", "%i%hi", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x2, y2);

  unsigned long x3, y3;
  ck_assert_int_eq(sscanf("0x1AB 00fa 1", "%li%*i", &x3),
                   s21_sscanf("0x1AB 00fa 1", "%li%*i", &y3));
  ck_assert_int_eq((long)x3, (long)y3);
}
END_TEST

START_TEST(test_s21_sscanf_i_2) {
  unsigned x1, y1;
  short x2, y2;
  ck_assert_int_eq(sscanf("0xab -298", "%i%3hi", &x1, &x2),
                   s21_sscanf("0xab -298", "%i%3hi", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x2, y2);

  long x3, y3;
  ck_assert_int_eq(sscanf("0x1AB 00fa 1", "%li%*i", &x3),
                   s21_sscanf("0x1AB 00fa 1", "%li%*i", &y3));
  ck_assert_int_eq((long)x3, (long)y3);
}
END_TEST

START_TEST(test_s21_sscanf_8) {
  long long int x4, y4;
  ck_assert_int_eq(sscanf("00fa 1", "%lli%*i", &x4),
                   s21_sscanf("00fa 1", "%lli%*i", &y4));
  ck_assert_int_eq(x4, y4);
}
END_TEST

START_TEST(test_s21_sscanf_f) {
  float x1, x2, y1, y2;
  ck_assert_int_eq(sscanf("298.3 4", "%f%f", &x1, &x2),
                   s21_sscanf("298.3 4", "%f%f", &y1, &y2));
  ck_assert_float_eq(x1, y1);
  ck_assert_float_eq(x2, y2);

  ck_assert_int_eq(sscanf("298.3 4", "%f%f", &x1, &x2),
                   s21_sscanf("298.3 4", "%f%f", &y1, &y2));
  ck_assert_float_eq(x1, y1);
  ck_assert_float_eq(x2, y2);

  long double x3, y3;
  ck_assert_int_eq(sscanf("298e-2 2.58849127", "%Lf%3f", &x3, &x2),
                   s21_sscanf("298e-2 2.58849127", "%Lf%3f", &y3, &y2));
  ck_assert_double_eq(x2, y2);
  ck_assert_double_eq(x3, y3);

  float x4, y4;
  ck_assert_int_eq(sscanf("298e-2 2.58849127", "%f%f", &x4, &x2),
                   s21_sscanf("298e-2 2.58849127", "%f%f", &y4, &y2));
  ck_assert_double_eq(x2, y2);
  ck_assert_double_eq(x3, y3);
}
END_TEST

START_TEST(test_s21_sscanf_g_G_1) {
  float x1, y1, x2, y2;
  ck_assert_int_eq(sscanf("298.3 4", "%g %g", &x1, &x2),
                   s21_sscanf("298.3 4", "%g %G", &y1, &y2));
  ck_assert_float_eq(x1, y1);
  ck_assert_float_eq(x2, y2);

  long double x5, y5, x6, y6;
  ck_assert_int_eq(
      sscanf("298e-2 57575272727.31313141", "%Lg %LG", &x5, &x6),
      s21_sscanf("298e-2 57575272727.31313141", "%Lg %LG", &y5, &y6));
  ck_assert_float_eq(x5, y5);
  ck_assert_float_eq(x6, y6);

  float x7, y7;
  double x8, y8;
  ck_assert_int_eq(sscanf("298.3 -4.414141", "%g %lf", &x7, &x8),
                   s21_sscanf("298.3 -4.414141", "%g %lg", &y7, &y8));
  ck_assert_float_eq(x7, y7);
  ck_assert_float_eq(x8, y8);

  float x9, y9;
  double x10, y10;
  ck_assert_int_eq(sscanf("-298.3 4", "%g%lg", &x9, &x10),
                   s21_sscanf("-298.3 4", "%g %lg", &y9, &y10));
  ck_assert_float_eq(x9, y9);
  ck_assert_float_eq(x10, y10);
}
END_TEST

START_TEST(test_s21_sscanf_g_G_2) {
  double x3, y3;
  ck_assert_int_eq(sscanf("123.4567", "%6lg", &x3),
                   s21_sscanf("123.4567", "%6lg", &y3));
  ck_assert_float_eq(x3, y3);

  double x4, y4;
  ck_assert_int_eq(sscanf("   1E-400", "%lG", &x4),
                   s21_sscanf("   1E-400", "%lG", &y4));
  ck_assert_float_eq(x4, y4);

  double x11, y11;
  ck_assert_int_eq(sscanf("-4.414141 -2781.2781781", "%lg %*G", &x11),
                   s21_sscanf("-4.414141 -2781.2781781", "%lg %*G", &y11));
  ck_assert_double_eq(x11, y11);

  long double x1, y1;
  float x2, y2;
  ck_assert_int_eq(
      sscanf("298e-21 2.5656654884 2.58849127E-10", "%Lf%5f", &x1, &x2),
      s21_sscanf("298e-21 2.5656654884 2.58849127E-10", "%Lf%5f", &y1, &y2));
  ck_assert_double_eq(x1, y1);
  ck_assert_float_eq(x2, y2);
}
END_TEST

START_TEST(test_s21_sscanf_o) {
  int x1, y1;
  unsigned int x2, y2;
  ck_assert_int_eq(sscanf("123 456", "%o %o", &x1, &x2),
                   s21_sscanf("123 456", "%o %o", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_uint_eq(x2, y2);

  int x3, y3;
  unsigned int x4, y4;
  ck_assert_int_eq(sscanf("77777 12342134256", "%o %5o", &x3, &x4),
                   s21_sscanf("77777 12342134256", "%o %5o", &y3, &y4));
  ck_assert_int_eq(x3, y3);
  ck_assert_uint_eq(x4, y4);

  int x5, y5;
  unsigned int x6, y6;
  ck_assert_int_eq(sscanf("123456 7654321", "%o%*3o%o", &x5, &x6),
                   s21_sscanf("123456 7654321", "%o%*3o%o", &y5, &y6));
  ck_assert_int_eq(x5, y5);
  ck_assert_uint_eq(x6, y6);
}
END_TEST

START_TEST(test_s21_sscanf_s) {
  char str1[10];
  char str2[10];
  int ret1 = sscanf("Hello World", "%s %s", str1, str2);
  int ret2 = s21_sscanf("Hello World", "%s %s", str1, str2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(str1, "Hello");
  ck_assert_str_eq(str2, "World");

  char str3[20];
  char str4[20];
  ret1 = sscanf("test tetest t", "%s %s", str3, str4);
  ret2 = s21_sscanf("test tetest t", "%s %s", str3, str4);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(str3, "test");
  ck_assert_str_eq(str4, "tetest");

  char str5[5];
  char str6[5];
  ret1 = sscanf("Test", "%4s", str5);
  ret2 = s21_sscanf("Test", "%4s", str6);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(str6, "Test");

  char str7[10];
  char str8[10];
  ret1 = sscanf("textax kek", "%9s %9s", str7, str8);
  ret2 = s21_sscanf("textax kek", "%9s %9s", str7, str8);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(str7, "textax");
  ck_assert_str_eq(str8, "kek");
}
END_TEST

START_TEST(test_s21_sscanf_u_1) {
  unsigned int x1, y1;

  ck_assert_int_eq(sscanf("42", "%u", &x1), s21_sscanf("42", "%u", &y1));
  ck_assert_int_eq(x1, (int)y1);

  ck_assert_int_eq(sscanf("42949672966", "%u", &x1),
                   s21_sscanf("42949672966", "%u", &y1));
  ck_assert_int_eq(x1, (int)y1);

  ck_assert_int_eq(sscanf("0", "%u", &x1), s21_sscanf("0", "%u", &y1));
  ck_assert_int_eq(x1, (int)y1);
}
END_TEST

START_TEST(test_s21_sscanf_u_2) {
  unsigned int x1, y1, x2, y2;
  ck_assert_int_eq(sscanf("-42", "%u", &x1), s21_sscanf("-42", "%u", &y1));
  ck_assert_uint_eq(x1, y1);

  ck_assert_int_eq(sscanf("42 0", "%u %u", &x1, &x2),
                   s21_sscanf("42 0", "%u %u", &y1, &y2));
  ck_assert_int_eq(x1, (int)y1);
  ck_assert_int_eq(x2, (int)y2);

  ck_assert_int_eq(sscanf("4294967295 12345", "%u %u", &x1, &x2),
                   s21_sscanf("4294967295 12345", "%u %u", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x2, y2);

  ck_assert_int_eq(sscanf("42a", "%u", &x1), s21_sscanf("42a", "%u", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("42 42", "%u %u", &x1, &x2),
                   s21_sscanf("42 42", "%u %u", &y1, &y2));
  ck_assert_int_eq(x1, y1);
  ck_assert_int_eq(x2, y2);

  ck_assert_int_eq(sscanf("4294967296", "%u", &x1),
                   s21_sscanf("4294967296", "%u", &y1));
  ck_assert_int_eq(x1, (unsigned int)0);
}
END_TEST
START_TEST(test_s21_sscanf_x_X) {
  int x1, y1;

  ck_assert_int_eq(sscanf("42", "%x", &x1), s21_sscanf("42", "%x", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("ABFFFFFFFF", "%5x", &x1),
                   s21_sscanf("ABFFFFFFFF", "%5x", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("-42", "%x", &x1), s21_sscanf("-42", "%x", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("42", "%X", &x1), s21_sscanf("42", "%X", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("FFFFFFFF", "%X", &x1),
                   s21_sscanf("FFFFFFFF", "%X", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("-42", "%X", &x1), s21_sscanf("-42", "%X", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("   -42", "%x", &x1),
                   s21_sscanf("   -42", "%x", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("   42", "%5x", &x1),
                   s21_sscanf("   42", "%5x", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("0x42", "%x", &x1), s21_sscanf("0x42", "%x", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("0042", "%05x", &x1),
                   s21_sscanf("0042", "%05x", &y1));
  ck_assert_int_eq(x1, y1);

  ck_assert_int_eq(sscanf("42", "%x", &x1), s21_sscanf("42", "%X", &y1));
  ck_assert_int_eq(x1, y1);

  unsigned short x3;
  unsigned long x4;
  ck_assert_int_eq(sscanf("42", "%hx", &x3), s21_sscanf("42", "%hx", &y1));
  ck_assert_int_eq(x3, y1);

  ck_assert_int_eq(sscanf("42", "%lx", &x4), s21_sscanf("42", "%lx", &y1));
  ck_assert_int_eq(x4, y1);
}
END_TEST

START_TEST(test_s21_sscanf_p_1) {
  void *p1, *p2;

  ck_assert_int_eq(sscanf("0x7fff5a6e42f8 0x7ffeebfe7758", "%p%*p", &p1),
                   s21_sscanf("0x7fff5a6e42f8 0x7ffeebfe7758", "%p%*p", &p2));
  ck_assert_int_eq((long)p1, (long)p2);
  ck_assert_int_eq(sscanf("0x7fff5a6e42f8 0x7ffeebfe7758", "%p%*p", &p1),
                   s21_sscanf("0x7fff5a6e42f8 0x7ffeebfe7758", "%p%*p", &p2));
  ck_assert_int_eq((long)p1, (long)p2);
}
END_TEST

START_TEST(test_s21_sscanf_p_2) {
  void *p11, *p21;
  ck_assert_int_eq(sscanf("0x7fff5a6e42f8", "%15p", &p11),
                   s21_sscanf("0x7fff5a6e42f8", "%15p", &p21));
  ck_assert_int_eq((long)p11, (long)p21);
}
END_TEST

START_TEST(test_s21_sscanf_extra) {
  int s21;
  ck_assert_int_eq(-1, s21_sscanf("%0x7fff5a6e42f8", "%%%15q", &s21));
  ck_assert_int_eq(-1, s21_sscanf("%0x7fff5a6e42f8", "4lX", &s21));
}
END_TEST

Suite *

s21_string(void) {
  Suite *s = suite_create("s21_string");

  TCase *s21_string_h = tcase_create("s21_string_h");
  TCase *s21_sscanf = tcase_create("s21_sscanf");
  TCase *s21_sprintf = tcase_create("s21_sprintf");

  /*STRING.H*/

  tcase_add_test(s21_string_h, test_s21_memchr);
  tcase_add_test(s21_string_h, test_s21_memcmp);
  tcase_add_test(s21_string_h, test_s21_memcpy);
  tcase_add_test(s21_string_h, test_s21_memset);
  tcase_add_test(s21_string_h, test_s21_strncat);
  tcase_add_test(s21_string_h, test_s21_strchr);
  tcase_add_test(s21_string_h, test_s21_strncmp);
  tcase_add_test(s21_string_h, test_s21_strncpy);
  tcase_add_test(s21_string_h, test_s21_strcspn);
  tcase_add_test(s21_string_h, test_s21_strerror);
  tcase_add_test(s21_string_h, test_s21_strlen);
  tcase_add_test(s21_string_h, test_s21_strpbrk);
  tcase_add_test(s21_string_h, test_s21_strrchr);
  tcase_add_test(s21_string_h, s21_strrchr_edge_cases_test);
  tcase_add_test(s21_string_h, test_s21_strstr);
  tcase_add_test(s21_string_h, test_s21_strtok);

  /*SPECIAL*/

  tcase_add_test(s21_string_h, test_s21_to_upper);
  tcase_add_test(s21_string_h, test_s21_to_lower_h);
  tcase_add_test(s21_string_h, test_s21_insert);
  tcase_add_test(s21_string_h, s21_insert_test_1);
  tcase_add_test(s21_string_h, s21_insert_test_2);
  tcase_add_test(s21_string_h, s21_insert_test_3);
  tcase_add_test(s21_string_h, s21_insert_test_5);
  tcase_add_test(s21_string_h, s21_trim_test);
  tcase_add_test(s21_string_h, s21_trim_test_1);
  tcase_add_test(s21_string_h, s21_trim_test_2);
  tcase_add_test(s21_string_h, s21_trim_test_3);

  /*SPRINTF*/

  tcase_add_test(s21_sprintf, test_s21_sprintf_с);
  tcase_add_test(s21_sprintf, test_s21_sprintf_d_1);
  tcase_add_test(s21_sprintf, test_s21_sprintf_d_2);
  tcase_add_test(s21_sprintf, test_s21_sprintf_i);
  tcase_add_test(s21_sprintf, test_s21_sprintf_e_1);
  tcase_add_test(s21_sprintf, test_s21_sprintf_e_2);
  tcase_add_test(s21_sprintf, test_s21_sprintf_f_1);
  tcase_add_test(s21_sprintf, test_s21_sprintf_f_2);
  tcase_add_test(s21_sprintf, test_s21_sprintf_g_G);
  tcase_add_test(s21_sprintf, test_s21_sprintf_o_1);
  tcase_add_test(s21_sprintf, test_s21_sprintf_o_2);
  tcase_add_test(s21_sprintf, test_s21_sprintf_s_1);
  tcase_add_test(s21_sprintf, test_s21_sprintf_s_2);
  tcase_add_test(s21_sprintf, test_s21_sprintf_u_1);
  tcase_add_test(s21_sprintf, test_s21_sprintf_u_2);
  tcase_add_test(s21_sprintf, test_s21_sprintf_x_1);
  tcase_add_test(s21_sprintf, test_s21_sprintf_x_2);
  tcase_add_test(s21_sprintf, test_s21_sprintf_x_3);
  tcase_add_test(s21_sprintf, test_s21_sprintf_x_4);
  tcase_add_test(s21_sprintf, test_s21_sprintf_x_X);
  tcase_add_test(s21_sprintf, test_s21_sprintf_p_1);
  tcase_add_test(s21_sprintf, test_s21_sprintf_p_2);
  tcase_add_test(s21_sprintf, test_s21_sprintf_percent);
  tcase_add_test(s21_sprintf, test_s21_sprintf_flags);
  tcase_add_test(s21_sprintf, test_s21_sprintf_width);
  tcase_add_test(s21_sprintf, test_s21_sprintf_length);
  tcase_add_test(s21_sprintf, test_s21_sprintf_precision);

  /*SSCANF*/

  tcase_add_test(s21_sscanf, test_s21_sscanf_c);
  tcase_add_test(s21_sscanf, test_s21_sscanf_d_0);
  tcase_add_test(s21_sscanf, test_s21_sscanf_d);
  tcase_add_test(s21_sscanf, test_s21_sscanf_d_w);
  tcase_add_test(s21_sscanf, test_s21_sscanf_i_1);
  tcase_add_test(s21_sscanf, test_s21_sscanf_i_2);
  tcase_add_test(s21_sscanf, test_s21_sscanf_8);
  tcase_add_test(s21_sscanf, test_s21_sscanf_f);
  tcase_add_test(s21_sscanf, test_s21_sscanf_g_G_1);
  tcase_add_test(s21_sscanf, test_s21_sscanf_g_G_2);
  tcase_add_test(s21_sscanf, test_s21_sscanf_o);
  tcase_add_test(s21_sscanf, test_s21_sscanf_s);
  tcase_add_test(s21_sscanf, test_s21_sscanf_u_1);
  tcase_add_test(s21_sscanf, test_s21_sscanf_u_2);
  tcase_add_test(s21_sscanf, test_s21_sscanf_x_X);
  tcase_add_test(s21_sscanf, test_s21_sscanf_p_1);
  tcase_add_test(s21_sscanf, test_s21_sscanf_p_2);
  tcase_add_test(s21_sscanf, test_s21_sscanf_extra);

  suite_add_tcase(s, s21_string_h);
  suite_add_tcase(s, s21_sscanf);
  suite_add_tcase(s, s21_sprintf);

  return s;
}

int main(void) {
  int count_failed;
  Suite *s = s21_string();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (count_failed == 0) ? 0 : 1;
}
