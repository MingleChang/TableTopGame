//
//  handle_input.c
//  TableTopGame
//
//  Created by MingleChang on 2021/9/4.
//

#include "handle_input.h"

void handle_input(char *data) {
    char *value = data;
    char *sep = " ";
    char *command = strsep(&value, sep);
    if (strcmp(command, "lz") == 0) {
        printf("查看房间列表\n");
    }
    if (strcmp(command, "cz") == 0) {
        printf("创建房间\n");
    }
    if (strcmp(command, "jz") == 0) {
        printf("加入房间：%s\n", value);
    }
}
