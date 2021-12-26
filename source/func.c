//
// Created by mao on 2021/11/7.
//

#include <stdio.h>
#include <stdlib.h>
#include "../header/func.h"


void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int test_sort() {
    int a[][6] = {
            {1, 4, 3, 1, 3, 2},
            {3, 2, 1, 3, 2, 4},
            {2, 3, 3, 2, 3, 1},
    };

    int length_i = sizeof(a) / sizeof(int) / 6;
    int length_j = 6;
    if (length_i < 3 || length_j < 3) {
        return -1;
    }


    int sum = 0;
    for (int k = 0; k < length_j; ++k) {
        for (int i = 1; i < length_i - 1; ++i) {
            for (int j = 1; j < length_j - 1; ++j) {
                int top = a[i - 1][j];
                int min = top;
                int bottom = a[i + 1][j];
                if (bottom < min) {
                    min = bottom;
                }
                int left = a[i][j - 1];
                if (left < min) {
                    min = left;
                }
                int right = a[i][j + 1];
                if (right < min) {
                    min = right;
                }
                if (
                        a[i][j] < top &&
                        a[i][j] < bottom &&
                        a[i][j] < left &&
                        a[i][j] < right &&
                        min > a[i][j]
                        ) {
                    sum = sum + min - a[i][j];
                    a[i][j] = min;
                }
                if (a[i][j] == min){

                }
            }
        }
    }


    printf("%d \n", sum);

    return -1;
}


void bubble_sort(int data[], int length) {
    int min_index;
    int min;
    for (int i = 0; i < length; ++i) {
        min_index = i;
        min = data[i];
        for (int j = i; j < length; ++j) {
            if (data[j] < min) {
                min = data[j];
                min_index = j;
            }
        }
        if (min_index != i) {
//            data[min_index] = data[i];
//            data[i] = min;
            swap(&data[min_index], &data[i]);
        }
    }
}

void insert_sort(int data[], int length) {
    for (int i = 0; i < length; ++i) {
        for (int j = i; j < length; ++j) {
            if (data[i] > data[j]) {
                swap(&data[i], &data[j]);
            }
        }
    }
}

void quick_sort(int data[], int length) {
    for (int i = length - 1; i > 0; --i) {
        for (int j = i; j >= 0; --j) {
            if (data[i] < data[j]) {
                swap(&data[i], &data[j]);
            }
        }
    }
}



void test_sort_() {
    int a[] = {1, 2, 3, 3, 2, 1, -1};
    int length = sizeof(a) / sizeof(int);

//    insert_sort(a, length);
//    bubble_sort(a, length);
    quick_sort(a, length);

    for (int i = 0; i < 6; ++i) {
        printf("%d ", a[i]);
    }

}


void test_func(){
    VOID p = NULL;
    p = test_sort_;
    for (int i = 0; i < 10; ++i) {
//        FUNC c = (FUNC) p;
//        c();
        ((FUNC) p)();
    }
}
