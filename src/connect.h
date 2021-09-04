//
//  connect.h
//  TableTopGame
//
//  Created by MingleChang on 2021/8/31.
//

#ifndef connect_h
#define connect_h

#include "common.h"

struct connect {
    evutil_socket_t fd;
    struct bufferevent *bufev;
    
    size_t head_buffer_len;
    void *head_buffer;
    
    size_t buffer_max_len;
    size_t buffer_len;
    void *buffer;
};

struct connect *connect_init(struct bufferevent *bufev);
void connect_clean(struct connect *connect);
void connect_free(struct connect *connect);

void connect_list_create(void);
void connect_list_add(struct connect *connect);
void connect_list_remove(struct connect *connect);

#endif /* connect_h */
