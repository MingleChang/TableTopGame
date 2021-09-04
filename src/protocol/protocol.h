//
//  protocol.h
//  Server
//
//  Created by MingleChang on 2021/9/1.
//

#ifndef protocol_h
#define protocol_h

#include "common.h"

#define PROTOCOL_VERSION 0x0001
#define PROTOCOL_AUTH 0x2435

#define PROTOCOL_TYPE_ZOOM_LIST_REQ 0x0010
#define PROTOCOL_TYPE_ZOOM_LIST_RES 0x0011
#define PROTOCOL_TYPE_ZOOM_CREATE_REQ 0x0012
#define PROTOCOL_TYPE_ZOOM_CREATE_RES 0x0013
#define PROTOCOL_TYPE_ZOOM_JOINT_REQ 0x0014
#define PROTOCOL_TYPE_ZOOM_JOINT_RES 0x0015

struct header {
    uint16_t version;   //协议版本号：PROTOCOL_VERSION，用于兼容
    uint16_t auth;      //认证：PROTOCOL_AUTH，如果不为PROTOCOL_AUTH则说明不符合协议规范
    uint32_t no;        //序号：当前发送数据编号
    uint32_t type;      //类型：数据类型定义
    uint32_t length;    //数据长度
};

struct protocol {
    struct header header;
    void *data;
};

#endif /* protocol_h */
