#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>

#include "sort.hpp"


void BubbleSort (uint32_t *array, int size) {

    for (int i = 1; i < size; i++) {

        for (int j = 0; j < size - i; j++) {

            if (array[j] > array[j+1]) {

                uint32_t tmp = array[j];
                array[j]     = array[j+1];
                array[j+1]   = tmp;
            }
        }
    }
}

void InsertionSort (uint32_t *array, int size) {

    for (int i = 1; i < size; i++) {
        
        int j = i;
        while (j > 0 && array[j] < array[j-1]) {

            uint32_t tmp = array[j-1];
            array[j-1]   = array[j];
            array[j]     = tmp;

            j--;
        }
    }
}

void SelectionSort (uint32_t *array, int size) {

    for (int i = 0; i < size; i++) {

        for (int j = i + 1; j < size; j++) {

            if (array[j] < array[i]) {

                uint32_t tmp = array[i];
                array[i]     = array[j];
                array[j]     = tmp;
            }
        }
    }
}

void MergeSort (uint32_t *array, int size) {

    if (size == 1) return;

    MergeSort(array, size / 2);
    MergeSort(array + size / 2, size - size / 2);

    uint32_t *buf = (uint32_t*) calloc(size, sizeof(uint32_t));

    int first = 0, second = 0;
    while (first + second < size) {

        if (array[first] < array[size / 2 + second]) {

            buf[first + second] = array[first];
            first++;
        }
        else {

            buf[first + second] = array[size / 2 + second];
            second++;
        }

        if (first == size / 2) {

            while (first + second < size) {

                buf[first + second] = array[size / 2 + second];
                second++;
            }
        }
        else if (second == size - size / 2) {

            while (first + second < size) {

                buf[first + second] = array[first];
                first++;
            }
        }
    }

    for (int i = 0; i < size; i++) {

        array[i] = buf[i];
    }

    free(buf);
}

void QuickSortMid (uint32_t *array, int size) {

    if (size <= 1) return;

    int l = 0, r = size - 1;
    //int pivot = MedianOfMedians(array, size);
    uint32_t pivot = array[size / 2];
    while (l <= r) {

        while (array[l] < pivot) {

            l++;
        }

        while (array[r] > pivot) {

            r--;
        }
        
        if (l <= r) {

            int tmp = array[r];
            array[r] = array[l];
            array[l] = tmp;

            l++;
            r--;
        }
    }

    QuickSortMid(array, r + 1);
    QuickSortMid(array + l, size - l);
}

void QuickSortMedian (uint32_t *array, int size) {

    if (size <= 1) return;

    int l = 0, r = size - 1;
    uint32_t pivot = 0;

    if (array[0] >= array[size / 2] && array[0] >= array[size - 1]) pivot = array[0];
    else if (array[size / 2] >= array[0] && array[size / 2] >= array[size - 1]) pivot = array[size / 2];
    else pivot = array[size - 1];

    while (l <= r) {

        while (array[l] < pivot) {

            l++;
        }

        while (array[r] > pivot) {

            r--;
        }
        
        if (l <= r) {

            int tmp = array[r];
            array[r] = array[l];
            array[l] = tmp;

            l++;
            r--;
        }
    }

    QuickSortMedian(array, r + 1);
    QuickSortMedian(array + l, size - l);
}

void QuickSortMedianOfMedians (uint32_t *array, int size) {

    if (size <= 1) return;

    int l = 0, r = size - 1;
    uint32_t pivot = MedianOfMedians(array, size);
    while (l <= r) {

        while (array[l] < pivot) {

            l++;
        }

        while (array[r] > pivot) {

            r--;
        }
        
        if (l <= r) {

            int tmp = array[r];
            array[r] = array[l];
            array[l] = tmp;

            l++;
            r--;
        }
    }

    QuickSortMedianOfMedians(array, r + 1);
    QuickSortMedianOfMedians(array + l, size - l);
}

int MedianOfMedians (uint32_t *array, int size) {

    if (size < 5) return array[size / 2];

    int buf_size = size / 5;
    uint32_t *buf = (uint32_t*) calloc(buf_size, sizeof(uint32_t));
    for (int i = 0; i + 5 <= size; i += 5) {

        InsertionSort(array + i, 5);

        buf[i / 5] =  array[i + 2];
    }

    int ans = MedianOfMedians(buf, buf_size);

    free(buf);

    return ans;
}

void LSD (uint32_t *array, int size) {

    for (int i = 0; i < 4; i++) {

        CountingSort(array, size, i);
    }
}

void CountingSort (uint32_t *array, int size, int digit) {

    int nums[256] = {0};
    uint32_t *buf = (uint32_t*) calloc(size, sizeof(uint32_t));

    for (int i = 0; i < size; i++) {

        nums[GetByte(array[i], digit)]++;
    }

    uint32_t sum = nums[0];
    nums[0] = 0;
    for (int i = 1; i < 256; i++) {

        int tmp = nums[i];
        nums[i] = sum;
        sum += tmp;
    }

    for (int i = 0; i < size; i++) {

        buf[nums[GetByte(array[i], digit)]] = array[i];
        nums[GetByte(array[i], digit)]++;
    }

    for (int i = 0; i < size; i++) {

        array[i] = buf[i];
    }

    free(buf);
}

void CallMSD (uint32_t *array, int size) {

    MSD(array, size, sizeof(uint32_t) - 1);
}

void MSD (uint32_t *array, int size, int digit) {

    if (digit < 0) return;

    int nums[256] = {0};
    uint32_t *buf = (uint32_t*) calloc(size, sizeof(uint32_t));

    for (int i = 0; i < size; i++) {

        nums[GetByte(array[i], digit)]++;
    }

    int sum = 0;
    for (int i = 0; i < 256; i++) {

        int tmp = nums[i];
        nums[i] = sum;
        sum += tmp;
    }

    for (int i = 0; i < size; i++) {

        buf[nums[GetByte(array[i], digit)]] = array[i];
        nums[GetByte(array[i], digit)]++;
    }

    for (int i = 0; i < size; i++) {

        array[i] = buf[i];
    }

    free(buf);

    if (nums[1] - nums[0] > 1) MSD(array + nums[0], nums[1] - nums[0], digit - 1);
    for (int i = 1; i < 256; i++) {

        if (nums[i] - nums[i-1] > 32) {

            MSD(array + nums[i-1], nums[i] - nums[i-1], digit - 1);
        }
        else if (nums[i] - nums[i-1] > 1) {

            InsertionSort(array, nums[i] - nums[i-1]);
        }
    }
}

int GetByte (uint32_t num, int digit) {

    return (num >> digit * 8) & 255;
}

void MSDForStr (char **array, int size, int maxlen, int curlen) {

    //printf("%d\n", curlen);

    if (curlen == 0) return;

    int nums[26] = {0};
    char **buf = (char**) calloc(size, sizeof(char*));

    for (int i = 0; i < size; i++) {

        nums[array[i][maxlen - curlen] - 'a']++;
    }

    int sum = 0;
    for (int i = 0; i < 26; i++) {

        int tmp = nums[i];
        nums[i] = sum;
        sum += tmp;
    }

    for (int i = 0; i < size; i++) {

        buf[nums[array[i][maxlen - curlen] - 'a']] = array[i];

        nums[array[i][maxlen - curlen] - 'a']++;
    }

    for (int i = 0; i < size; i++) {

        array[i] = buf[i];
    }

    free(buf);

    if (nums[1] - nums[0] > 1) MSDForStr(array + nums[0], nums[1] - nums[0], maxlen, curlen - 1);
    for (int i = 1; i < 26; i++) {

        if (nums[i] - nums[i-1] > 32) {

            MSDForStr(array + nums[i-1], nums[i] - nums[i-1], maxlen, curlen - 1);
        }
        else if (nums[i] - nums[i-1] > 1) {

            InsertionSortForStr(array, nums[i] - nums[i-1]);
        }
    }
}

void InsertionSortForStr (char **array, int size) {

    for (int i = 1; i < size; i++) {
        
        int j = i;
        while (j > 0 && strcmp(array[j], array[j-1]) < 0) {

            char *tmp  = array[j-1];
            array[j-1] = array[j];
            array[j]   = tmp;

            j--;
        }
    }
}
