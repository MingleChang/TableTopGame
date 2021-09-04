//
//  connect.c
//  TableTopGame
//
//  Created by MingleChang on 2021/8/31.
//

#include "connect.h"

struct connect *connect_init(struct bufferevent *bufev) {
    struct connect *connect = (struct connect *)malloc(sizeof(struct connect));
    connect->fd = bufferevent_getfd(bufev);
    connect->bufev = bufev;
    connect->head_buffer_len = 0;
    connect->head_buffer = NULL;
    connect->buffer_max_len = 0;
    connect->buffer_len = 0;
    connect->buffer = NULL;
    return connect;
}
void connect_clean(struct connect *connect) {
    if (connect == NULL) {
        return;
    }
    connect->head_buffer_len = 0;
    connect->buffer_max_len = 0;
    connect->buffer_len = 0;
    if (connect->head_buffer != NULL) {
        free(connect->head_buffer);
        connect->head_buffer = NULL;
    }
    if (connect->buffer != NULL) {
        free(connect->buffer);
        connect->buffer = NULL;
    }
}
void connect_free(struct connect *connect) {
    if (connect == NULL) {
        return;
    }
    connect_clean(connect);
    free(connect);
}

struct m_list *connect_list;
void connect_list_create(void) {
    connect_list  = m_list_create();
}
void connect_list_add(struct connect *connect) {
    m_list_add(connect_list, connect, connect_free);
}
void connect_list_remove(struct connect *connect) {
    m_list_remove(connect_list, connect);
}
