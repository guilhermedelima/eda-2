#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_KEY 10000 /* Random of 4 digits*/
#define MAX_DIGIT 1000 /* 4 digits*/
#define DIGITS 10 /* 0 to 9 digits*/


extern int *create_vector(int length);
extern void print_vector(int *vec, int length);
extern void radix_sort(int *vec, int length);
extern void bucket_sort(int *vec, int length, int digit);
extern void counting_sort(int *vec, int length, int digit);


#endif
