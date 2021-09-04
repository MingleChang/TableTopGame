//
//  utils.c
//  Server
//
//  Created by MingleChang on 2021/8/31.
//

#include "utils.h"
void read_buffer_from_bufferevent(struct bufferevent *bev, struct connect *connect, void ( *callback)(struct bufferevent *, struct connect *)) {
    size_t len = 0;
    size_t length = 0;
    while (1) {
        if (connect->head_buffer == NULL) {
            length = 4;
            connect->head_buffer = malloc(length);
            memset(connect->head_buffer, 0, length);
            connect->head_buffer_len = bufferevent_read(bev, connect->head_buffer, length);
            if (connect->head_buffer_len < length) {
                return;
            }else {
                memcpy(&connect->buffer_max_len, connect->head_buffer, connect->head_buffer_len);
                connect->buffer = malloc(connect->buffer_max_len);
            }
        }else if (connect->head_buffer_len < 4) {
            length = 4 - connect->head_buffer_len;
            len = bufferevent_read(bev, connect->head_buffer + connect->head_buffer_len, length);
            connect->head_buffer_len = connect->head_buffer_len + len;
            if (connect->head_buffer_len < 4) {
                return;
            }else {
                memcpy(&connect->buffer_max_len, connect->head_buffer, connect->head_buffer_len);
                connect->buffer = malloc(connect->buffer_max_len);
            }
        }else {
            length = connect->buffer_max_len - connect->buffer_len;
            len = bufferevent_read(bev, connect->buffer + connect->buffer_len, length);
            connect->buffer_len = connect->buffer_len + len;
            if (connect->buffer_len < connect->buffer_max_len) {
                return;
            }else if (connect->buffer_len == connect->buffer_max_len){
                printf("Recieve Message: %s\n", (char *)connect->buffer);
                callback(bev, connect);
                connect_clean(connect);
            }
        }
    }
}
