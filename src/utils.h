//
//  utils.h
//  Server
//
//  Created by MingleChang on 2021/8/31.
//

#ifndef utils_h
#define utils_h

#include "common.h"

void read_buffer_from_bufferevent(struct bufferevent *bev, struct connect *connect, void ( *callback)(struct bufferevent *, struct connect *));

#endif /* utils_h */
