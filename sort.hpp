#ifndef _SORT_HPP_
#define _SORT_HPP_


#include <stdint.h>


void BubbleSort    (uint32_t *array, int size);
void InsertionSort (uint32_t *array, int size);
void SelectionSort (uint32_t *array, int size);

void QuickSortMid             (uint32_t *array, int size);
void QuickSortMedian          (uint32_t *array, int size);
void QuickSortMedianOfMedians (uint32_t *array, int size);
int MedianOfMedians           (uint32_t *array, int size);

void MergeSort (uint32_t *array, int size);

void LSD          (uint32_t *array, int size);
void CountingSort (uint32_t *array, int size, int digit);
void CallMSD      (uint32_t *array, int size);
void MSD          (uint32_t *array, int size, int digit);
int  GetByte      (uint32_t num, int digit);

void MSDForStr           (char **array, int size, int maxlen, int curlen);
void InsertionSortForStr (char **array, int size);



#endif