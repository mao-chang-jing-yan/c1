//
// Created by mao on 2022/1/4.
//

#include <stdio.h>
#include <string.h>

void test_str() {
    char str1[14] = "runoob";
    char str2[14] = "google";
    char str3[14];
    unsigned int len;

    /* 复制 str1 到 str3 */
    strcpy(str3, str1);
    printf("strcpy( str3, str1) :  %s\n", str3);

    /* 连接 str1 和 str2 */
    strcat(str1, str2);
    printf("strcat( str1, str2):   %s\n", str1);

    /* 连接后，str1 的总长度 */
    len = strlen(str1);
    printf("strlen(str1) :  %d\n", len);
}