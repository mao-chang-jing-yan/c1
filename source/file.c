//
// Created by mao on 2021/12/26.
//

#include <stdio.h>

void file_test(){
    FILE *fp = NULL;
//    char buff[2569];

    fp = fopen("./tmp/test.txt", "rb+");

    fseek(fp, 0, SEEK_END); //定位到文件末
    long nFileLen = ftell(fp); //文件长度
    printf("%ld", nFileLen);
    rewind(fp);


    for (int i = 0; i < nFileLen; ++i) {

        fwrite("\0", 1, 1, fp);
    }


    fclose(fp);
    remove("./tmp");

}