//
//  common.h
//  TableTopGame
//
//  Created by MingleChang on 2021/8/31.
//

#ifndef common_h
#define common_h

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <event2/dns.h>
#include <event2/event.h>
#include <event2/util.h>
#include <event2/event_struct.h>
#include <event2/listener.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/buffer_compat.h>
#include <event2/bufferevent_compat.h>
#include <event2/bufferevent_struct.h>

#include "macro.h"
#include "connect.h"
#include "protocol.h"
#include "utils.h"
#include "m_list.h"
#include "m_hint.h"

#endif /* common_h */
