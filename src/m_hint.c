//
//  m_hint.c
//  Server
//
//  Created by MingleChang on 2021/9/4.
//

#include "m_hint.h"

void m_hint_server_joint_player(evutil_socket_t fd) {
    printf("角色%i进入游戏...\n", fd);
}

void m_hint_client_home(void) {
    printf("请选择输入下面命令进行下一步：\n");
    printf("[lz]：查看所有房间\n");
    printf("[cz]：创建房间\n");
    printf("[jz {zoom_no}]：加入房间\n");
}
