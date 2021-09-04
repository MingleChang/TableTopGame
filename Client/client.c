//
//  main.c
//  Client
//
//  Created by MingleChang on 2021/8/29.
//

#include "client.h"

struct connect *client;

struct event_base *base;
struct bufferevent *event;
struct bufferevent *io_event;

static void handler_recieve_data(struct bufferevent *bev, struct connect *connect) {
    printf("Recieve Client Message: %s\n", (char *)connect->buffer);
}

static void read_callback(struct bufferevent *bev, void *user_data) {
    struct connect *connect = (struct connect *)user_data;
    read_buffer_from_bufferevent(bev, connect, handler_recieve_data);
}
    
static void write_callback(struct bufferevent *bev, void *user_data) {

}
static void error_callback(struct bufferevent *bev, short what, void *user_data) {
    if (what & BEV_EVENT_CONNECTED) {
        return;
    }
    bufferevent_free(bev);
    event_base_loopexit(base, 0);
}

static void io_read_callback(struct bufferevent *bev, void *user_data) {
    char buff[MAXLINE];
    memset(buff, 0, MAXLINE);
    size_t len = bufferevent_read(bev, buff, MAXLINE - 1);
    buff[len - 1] = '\0';
    handle_input(buff);
//    char data[4 + len];
//    memset(data, 0, 4+len);
//    memcpy(data, &len, 4);
//    memcpy(data+4, buff, len-1);
//    bufferevent_write(event, data, 4 + len);
}
static void io_write_callback(struct bufferevent *bev, void *user_data) {

}
static void io_error_callback(struct bufferevent *bev, short what, void *user_data) {
    
}

int main(int argc, const char * argv[]) {
    printf("Start Client\n");
    struct evdns_base *dns_base;
    base = event_base_new();
    dns_base = evdns_base_new(base, 1);
    event = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    io_event = bufferevent_socket_new(base, STDIN_FILENO, BEV_OPT_CLOSE_ON_FREE);
    client = connect_init(event);
    bufferevent_socket_connect_hostname(event, dns_base, AF_UNSPEC, "127.0.0.1", 8086);
    bufferevent_setcb(event, read_callback, NULL, error_callback, client);
    bufferevent_enable(event, EV_READ | EV_PERSIST);
    bufferevent_setcb(io_event, io_read_callback, NULL, io_error_callback, base);
    bufferevent_enable(io_event, EV_READ | EV_PERSIST);
    m_hint_client_home();
    event_base_dispatch(base);
    event_base_free(base);
    return 0;
}
