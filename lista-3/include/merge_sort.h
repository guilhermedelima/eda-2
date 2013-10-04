#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_KEY 50


extern int *create_vector(int length);
extern void print_vector(int *vec, int length);
extern void merge_sort(int init, int end, int *vec);
extern void merge(int init, int end, int middle, int *vec);


#endif
