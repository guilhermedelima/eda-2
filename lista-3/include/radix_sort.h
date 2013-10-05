#ifndef RADIX_SORT_H
#define RADIX_SORT_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define MAX_KEY 100000 /* Random of 5 digits (MAX) */
#define DIGITS 10 /* 0 to 9 digits */


extern int *create_vector(int length);
extern void print_vector(int *vec, int length);
extern int check_max_digit(int *vec, int length);
extern void radix_sort(int *vec, int length);
extern void bucket_sort(int *vec, int length, int digit);
extern void counting_sort(int *vec, int length, int digit);


#endif
