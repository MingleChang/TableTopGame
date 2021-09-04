//
//  main.c
//  Server
//
//  Created by MingleChang on 2021/8/29.
//

#include "common.h"

struct event_base *base;
struct evconnlistener *listener;

static void handler_recieve_data(struct bufferevent *bev, struct connect *connect) {
    printf("Recieve Server Message: %s\n", (char *)connect->buffer);
    char data[4 + connect->buffer_len];
    memset(data, 0, 4+connect->buffer_len);
    memcpy(data, &connect->buffer_len, 4);
    memcpy(data+4, connect->buffer, connect->buffer_len-1);
    bufferevent_write(bev, data, 4 + connect->buffer_len);
}

static void read_callback(struct bufferevent *bev, void *user_data) {
    struct connect *connect = (struct connect *)user_data;
    read_buffer_from_bufferevent(bev, connect, handler_recieve_data);
    
}
static void write_callback(struct bufferevent *bev, void *user_data) {
    struct connect *connect = (struct connect *)user_data;
}
static void error_callback(struct bufferevent *bev, short what, void *user_data) {
    struct connect *connect = (struct connect *)user_data;
    connect_list_remove(connect);
    connect_free(connect);
    bufferevent_free(bev);
}
static void listener_callback(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data) {
    printf("Accept Client ...\n");
    m_hint_server_joint_player(fd);
    struct event_base *base = (struct event_base *)user_data;
    struct bufferevent *bufev;
    bufev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    struct connect *connect = connect_init(bufev);
    connect_list_add(connect);
    bufferevent_setcb(bufev, read_callback, write_callback, error_callback, connect);
    bufferevent_enable(bufev, EV_READ | EV_PERSIST);
}

int main(int argc, const char * argv[]) {
//    printf("%i\n",sizeof(struct header));
//    printf("%i\n",sizeof(struct protocol));
    connect_list_create();
    int result;
    struct evutil_addrinfo hints, *res;
    printf("Start Server ...\n ");
    base = event_base_new();
    bzero(&hints, sizeof(struct evutil_addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    result = evutil_getaddrinfo(NULL, "8086", &hints, &res);
    do {
        listener = evconnlistener_new_bind(base, listener_callback, (void *)base, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1, res->ai_addr, res->ai_addrlen);
        if (listener) {
            break;
        }
    } while ((res = res->ai_next) != NULL);
    
    event_base_dispatch(base);
    event_base_free(base);
    evconnlistener_free(listener);
    printf("End Server ...\n");
    return 0;
}
