#include <stdio.h>
#include <time.h>
#include <cstdlib>

#include "sort.hpp"


void TestSort      (int size, void sort1(uint32_t *array, int size), void sort2(uint32_t *array, int size),\
                    void sort3(uint32_t *array, int size), double *rez1, double *rez2, double *rez3);
double MSDStrTest1 (int size);

int main () {

    

    return 0;
}


void TestSort (int size, void sort1(uint32_t *array, int size), void sort2(uint32_t *array, int size), void sort3(uint32_t *array, int size), double *rez1, double *rez2, double *rez3) {

    uint32_t *array = (uint32_t*) calloc(size, sizeof(uint32_t));
    uint32_t *buf   = (uint32_t*) calloc(size, sizeof(uint32_t));

    for (int i = 0; i < size; i++) {

        array[i] = (rand() + 1) * rand() * 4;
    }

    for (int i = 0; i < size; i++) {

        buf[i] = array[i];
    }

    clock_t time_start = clock();
    sort1(buf, size);
    clock_t time_end   = clock();

    *rez1 = 1000.0 * (time_end - time_start) / CLOCKS_PER_SEC;

    for (int i = 0; i < size; i++) {

        buf[i] = array[i];
    }

    time_start = clock();
    sort2(buf, size);
    time_end   = clock();

    *rez2 = 1000.0 * (time_end - time_start) / CLOCKS_PER_SEC;

    for (int i = 0; i < size; i++) {

        buf[i] = array[i];
    }

    time_start = clock();
    sort3(buf, size);
    time_end   = clock();

    *rez3 = 1000.0 * (time_end - time_start) / CLOCKS_PER_SEC;

    free(array);
}

double MSDStrTest1 (int size) {

    char **array = (char**) calloc(size, sizeof(char*));
    for (int i = 0; i < size; i++) {

        array[i] = (char*) calloc(1001, sizeof(char));
    }

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < 1000; j++) {

            array[i][j] = (char) ('a' + rand() % 26);
        }
    }

    clock_t time_start = clock();
    MSDForStr(array, size, 1000, 1000);
    clock_t time_end   = clock();

    for (int i = 0; i < size; i++) {

        free(array[i]);
    }
    free(array);

    return 1000.0 * (time_end - time_start) / CLOCKS_PER_SEC;
}
