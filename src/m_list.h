//
//  m_list.h
//  Server
//
//  Created by MingleChang on 2021/9/1.
//

#ifndef m_list_h
#define m_list_h

#include "common.h"
struct m_list {
    void *data;
    uint8_t is_head;
    uint32_t length;
    void (* free_callback)(void *);
    struct m_list *next;
};

struct m_list *m_list_create(void);
void m_list_add(struct m_list *list, void *data, void (* free_callback)(void *));
void m_list_insert(struct m_list *list, void *data, void (* free_callback)(void *), int index);
void m_list_remove(struct m_list *list, void *data);
void m_list_delete(struct m_list *list, void *data);
void m_list_free_node(struct m_list *node);
#endif /* m_list_h */
