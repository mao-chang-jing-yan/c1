//
// Created by mao on 2021/11/26.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define SIZE 10                             // 城市数量
#define ANT_NUM 64                         // 蚂蚁数量
#define ITER_MAX 1024                        // 最大迭代次数

unsigned long long next_random = 19898089;         // 随机数初始值

double cities[SIZE][2] = {};                // 城市列表
double city_map[SIZE][SIZE] = {};           // 城市间距离

double alpha = 3;                              // 信息素重要程度因子
double rho = 0.1;                           // 信息素挥发因子

double Tau[SIZE][SIZE] = {0};               // 信息素矩阵
int Table[ANT_NUM][SIZE] = {0};             // 路径记录表,每一行代表一个蚂蚁走过的路径

int iter = 1;                               // 迭代次数初值

int Eta = 1;                                // 启发函数
int beta = 5;                               // 启发函数重要程度因子

int Q = 2;                                  // 常系数

int route_best[ITER_MAX][SIZE] = {};     // 各代最佳路径
double length_best[ITER_MAX] = {};          // 各代最佳路径的长度
double length_ave[ITER_MAX] = {};           // 各代路径的平均长度



double get_rand_float() {
    next_random = next_random * (unsigned long long) 25214903917 + 11;
    return (((next_random & 0xFFFF) / (float) 65536) - 0.5);
}

void init_data() {
    // 初始化城市坐标
    double cities_[10][2] = {
            {1.0,  2},
            {6.3,  0},
            {12.3, 6},
            {1.1,  22},
            {56,   24},
            {75,   24},
            {73,   84},
            {77,  56},
            {11,   24},
            {13,   23},
    };
    for (int i = 0; i < SIZE; ++i) {
        cities[i][0] = get_rand_float() * 10;
        cities[i][1] = get_rand_float() * 10;
        if (i < 10) {
            cities[i][0] = cities_[i][0];
            cities[i][1] = cities_[i][1];
        }
    }
    // 初始化城市距离数组
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            city_map[i][j] = 1;
        }
    }
    // 初始化城市间信息素列表
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            Tau[i][j] = 1;
        }
    }
}

void print_city_map() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%f ", city_map[i][j]);
        }
        printf("\n");
    }
}

void print_cities() {
    printf("cities\n");
    for (int i = 0; i < SIZE; ++i) {
        printf("%f %f\n", cities[i][0], cities[i][1]);
    }
}

double get_dist(int from, int to) {
    double r = pow(cities[to][1] - cities[from][1], 2) + pow(cities[to][0] - cities[from][0], 2);
    return sqrt(r);
}


void test_yiqun() {
    init_data();
//    print_cities();
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            city_map[i][j] = get_dist(i, j);
            city_map[j][i] = get_dist(i, j);
        }
    }
//    print_city_map();

    while (iter < ITER_MAX) {
        int min_path[SIZE] = {0};
        double min_length = -1;
        double average_length = 0;


        for (int i = 0; i < ANT_NUM; ++i) {
            Table[i][0] = rand() % SIZE;
            // Table[i] 蚂蚁走过的路径
            for (int j = 1; j < SIZE; ++j) {
                int from_city_index = Table[i][j - 1];
                int ALLOW_CITIES[SIZE] = {0};
                double CITIES_P[SIZE] = {0}; // 转移概率 arph*(1-pho)*tau + beta  1 / dist
                for (int k = 0; k < SIZE; ++k) {
                    ALLOW_CITIES[k] = 1;
                }
                for (int k = 0; k < j; ++k) {
                    int city_index = Table[i][k];
                    ALLOW_CITIES[city_index] = 0;
//                    printf("%d ", city_index);
                }
//                printf("%d %d\n", i, j);


//                for (int k = 0; k < SIZE; ++k) {
//                    printf("%d ", ALLOW_CITIES[k]);
//
//                }

                double sum = 0.0;
                for (int k = 0; k < SIZE; ++k) {
                    int to_city_index = k;
                    if (ALLOW_CITIES[k] != 0 && to_city_index != from_city_index) {
                        CITIES_P[k] = alpha * (1.0 - rho) * Tau[from_city_index][to_city_index] + \
                                        beta * 1.0 / city_map[from_city_index][to_city_index];
                        sum = sum + CITIES_P[k];
//                        printf("%f %f ", CITIES_P[k], sum);
                    }
                }
//                printf("%d %d\n", i, j);


                for (int k = 0; k < SIZE; ++k) {
                    if (ALLOW_CITIES[k] == 0 || k == from_city_index) {
                        continue;
                    }
                    CITIES_P[k] = CITIES_P[k] / sum;
//                    printf("%f %f", CITIES_P[k], sum);
//                    printf("%f ", CITIES_P[k]);
                }
//                printf("\n");
                sum = 0.0;
                double rand_p = get_rand_float();
                while (rand_p < 1e-6) {
                    rand_p = get_rand_float();
                }
                int to_city_index = -1;
                for (int k = 0; k < SIZE; ++k) {
                    if (ALLOW_CITIES[k] == 0 || k == from_city_index) {
                        continue;
                    }
                    if (to_city_index == -1) {
                        to_city_index = k;
                    }
                    sum = sum + CITIES_P[k];
                    if (sum >= rand_p) {
                        to_city_index = k;
                        break;
                    }
                }
                printf("sum=%f rand_p=%f from=%d to=%d i=%d j=%d\n", sum, rand_p, from_city_index, to_city_index, i, j);

                Table[i][j] = to_city_index;
                Tau[from_city_index][to_city_index] += Q;
//                printf("%f %f\n", sum, rand_p);

                // 轮盘法选择下一个城市



            }

            double length = 0;
            for (int j = 1; j < SIZE; ++j) {
                int from_index = Table[i][j - 1];
                int to_index = Table[i][j];
                length = length + city_map[from_index][to_index];
            }
            average_length = average_length + length;

            if (min_length == -1 || length < min_length) {
                min_length = length;
                min_path[0] = Table[i][0];
                for (int j = 1; j < SIZE; ++j) {
                    min_path[j] = Table[i][j];
                }
            }
        }
        average_length = average_length / ANT_NUM;
//        if (min_length != -1){
//            double route_best[ITER_MAX][SIZE] = {};     // 各代最佳路径
//            double length_best[ITER_MAX] = {};          // 各代最佳路径的长度
//            double length_ave[ITER_MAX] = {};           // 各代路径的平均长度
        length_best[iter] = min_length;
        length_ave[iter] = average_length;
        for (int i = 0; i < SIZE; ++i) {
            route_best[iter][i] = min_path[i];
        }

//        }

        // 找出此次迭代最短路径
        // 更新信息素矩阵
        // 清零每只蚂蚁走过的路径
//        for (int i = 0; i < ANT_NUM; ++i) {
//            for (int j = 0; j < SIZE; ++j) {
//                Table[i][j] = 0;
//            }
//            Table[i][0] = rand() % SIZE;
//        }
//        printf("%d \n", iter);

        iter++;
    }
//    float b=rand()/(RAND_MAX+1.0);
//    printf("%d \n", get_rand_float());

//    for (int i = 0; i < 100; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//            printf("%d ->", route_best[i][j]);
//        }
//        printf("%f %f \n", length_best[i], length_ave[i]);
//    }
//
//    for (int i = ITER_MAX - 100; i < ITER_MAX; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//            printf("%d ->", route_best[i][j]);
//        }
//        printf("%f %f \n", length_best[i], length_ave[i]);
//    }

    for (int i = 0; i < ITER_MAX; ++i) {
        printf("%d %f %f\n",i, length_best[i], length_best[i] / length_ave[i]);
    }

}
