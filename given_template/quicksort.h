#ifndef QUICKSORT_H_
#define QUICKSORT_H_
#include <cstddef>

void quicksort(int *arr, std::size_t len);
int kthSmallestNaive(int *arr, std::size_t len, int k);
int kthSmallest(int *arr, std::size_t len, int k);

#endif
