#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#define N_ELEMENT 10
#define MAX_DIGIT 100000000


extern int *create_vector(int length);
extern void print_vector(int *vec, int length);
extern int *radix_sort(int *vec, int length);
extern int *counting_sort(int *vec, int length, int digit);



#endif
