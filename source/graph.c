//
// Created by mao on 2021/11/20.
//
#include <stdio.h>
#include <stdlib.h>
#include "../header/qNode.h"

#define MAX_NUM 100000000

int get_node_num(const int *edges, int length) {
    int node_num = 0;
    for (int i = 0; i < length; ++i) {
        if (*(edges + i * 3 + 0) > node_num) {
            node_num = *(edges + i * 3 + 0);
        }
        if (*(edges + i * 3 + 1) > node_num) {
            node_num = *(edges + i * 3 + 1);
        }
    }

    return node_num + 1;
}

void bellman_ford(const int *edges, int length, int p, int t) {
    int node_num = get_node_num(edges, length);
    int *dist = (int *) malloc(sizeof(int) * node_num);
    int *path = (int *) malloc(sizeof(int) * node_num);

//    int path[12];
//    int dist[12];
    for (int l = 0; l < 12; ++l) {
        dist[l] = MAX_NUM;
        path[l] = -1;
    }
    dist[p] = 0;

    for (int k = 0; k < node_num; ++k) {
        for (int i = 0; i < length; ++i) {
            int p1 = *(edges + i * 3 + 0);
            int n1 = *(edges + i * 3 + 1);
            int v = *(edges + i * 3 + 2);
            printf("%d %d %d \n", p1, n1, v);
            if (dist[n1] > dist[p1] + v) {
                dist[n1] = dist[p1] + v;
                path[n1] = p1;
            };
        }
    }

    for (int k = 0; k < node_num; ++k) {
        for (int i = 0; i < length; ++i) {
            int p1 = *(edges + i * 3 + 0);
            int n1 = *(edges + i * 3 + 1);
            int v = *(edges + i * 3 + 2);
            printf("%d %d %d \n", p1, n1, v);
            if (dist[n1] > dist[p1] + v) {
                dist[n1] = -MAX_NUM;
                path[n1] = p1;
            };
        }
    }

    for (int j = 0; j < 12; ++j) {
        printf("%d ", dist[j]);
    }
    printf("\n");
    for (int j = 0; j < 12; ++j) {
        printf("%d ", path[j]);
    }


    free(dist);
    free(path);


}

void floyd(const int *edges, int length, int p, int t) {
    int node_num = get_node_num(edges, length);
    int *dist = (int *) malloc(sizeof(int) * node_num * node_num);
    int *path = (int *) malloc(sizeof(int) * node_num * node_num);

    for (int i = 0; i < node_num; ++i) {
        for (int j = 0; j < node_num; ++j) {
            *(dist + i * node_num + j) = MAX_NUM;
            *(path + i * node_num + j) = -1;
            if (i == j) {
                *(dist + i * node_num + j) = 0;
            }
        }
    }

    for (int i = 0; i < length; ++i) {
        int p1 = *(edges + i * 3 + 0);
        int n1 = *(edges + i * 3 + 1);
        int v1 = *(edges + i * 3 + 2);
        *(dist + p1 * node_num + n1) = v1;
    }


    for (int k = 0; k < node_num; ++k) {
        for (int i = 0; i < node_num; ++i) {
            for (int j = 0; j < node_num; ++j) {
                if (*(dist + i * node_num + j) > *(dist + i * node_num + k) + *(dist + k * node_num + j)) {
                    *(dist + i * node_num + j) = *(dist + i * node_num + k) + *(dist + k * node_num + j);
                    *(path + i * node_num + j) = k;
                }
            }
        }
    }


    for (int i = 0; i < node_num; ++i) {
        for (int j = 0; j < node_num; ++j) {
            printf("%d ", *(dist + i * node_num + j));
        }
        printf("\n");
    }

    for (int i = 0; i < node_num; ++i) {
        for (int j = 0; j < node_num; ++j) {
            printf("%d ", *(path + i * node_num + j));
        }
        printf("\n");
    }


    free(dist);
    free(path);
}


void SpFa(const int *edges, int length, int p, int t) {
    int node_num = get_node_num(edges, length);
    int *flag = (int *) malloc(sizeof(int) * node_num);
    int *dist = (int *) malloc(sizeof(int) * node_num);
    int *path = (int *) malloc(sizeof(int) * node_num);
    Que *q = initQueue(node_num);
    pushBack(q, (void *) &p);

    for (int l = 0; l < 12; ++l) {
        flag[l] = 0;
        dist[l] = MAX_NUM;
        path[l] = -1;
    }
    dist[p] = 0;

    int n = 0;
    while (q->size > 0) {
        int *num = (int *) q->front->value;
        for (int k = 0; k < node_num; ++k) {
            for (int i = 0; i < length; ++i) {
                int p1 = *(edges + i * 3 + 0);
                int n1 = *(edges + i * 3 + 1);
                int v = *(edges + i * 3 + 2);
                if (*num != p1) {
                    continue;
                }
//                printf("%d %d %d \n", p1, n1, v);
                if (dist[n1] > dist[p1] + v) {

                    dist[n1] = dist[p1] + v;
                    path[n1] = p1;
                    if (n > node_num) {
                        dist[n1] = -MAX_NUM;
                    }
                    if (flag[n1] == 0) {
                        flag[n1] = 1;
                        pushBack(q, (void *) (edges + i * 3 + 1));
                    }
                };
            }
        }
        n++;
        flag[*num] = 0;
        popFront(q);
    }

    printf("\n");
    for (int i = 0; i < node_num; ++i) {
        printf("%d ", flag[i]);
    }
    printf("\n");
    for (int i = 0; i < node_num; ++i) {
        printf("%d ", dist[i]);
    }
    printf("\n");
    for (int i = 0; i < node_num; ++i) {
        printf("%d ", path[i]);
    }

    clear_q(q);
    free(q);
    free(flag);
    free(dist);
    free(path);
}




void test_graph() {
    int a[][3] = {
            {0, 1, 5},
            {1, 6, 60},
            {1, 5, 30},
            {1, 2, 20},
            {2, 3, 10},
            {3, 2, -15},
            {2, 4, 75},
            {4, 9, 100},
            {5, 4, 25},
            {5, 6, 5},
            {5, 8, 50},
            {6, 7, -50},
            {7, 8, -10},
    };


    bellman_ford((int *) a, sizeof(a) / sizeof(0) / 3, 0, 3);
    floyd((int *) a, sizeof(a) / sizeof(0) / 3, 0, 3);
    SpFa((int *) a, sizeof(a) / sizeof(0) / 3, 0, 3);
}