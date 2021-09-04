//
//  m_list.c
//  Server
//
//  Created by MingleChang on 2021/9/1.
//

#include "m_list.h"

struct m_list *m_list_create(void) {
    struct m_list *list = (struct m_list *)malloc(sizeof(struct m_list));
    list->is_head = 1;
    list->length = 0;
    list->data = NULL;
    list->free_callback = NULL;
    list->next = NULL;
    return list;
}

struct m_list *m_list_init(void *data, void (* free_callback)(void *)) {
    struct m_list *list = (struct m_list *)malloc(sizeof(struct m_list));
    list->is_head = 0;
    list->length = 0;
    list->data = data;
    list->free_callback = free_callback;
    list->next = NULL;
    return list;
}

void m_list_add(struct m_list *list, void *data, void (* free_callback)(void *)) {
    struct m_list *temp = list;
    while (temp->next) {
        temp = temp->next;
    }
    struct m_list *node = m_list_init(data, free_callback);
    temp->next = node;
    list->length = list->length + 1;
}

void m_list_insert(struct m_list *list, void *data, void (* free_callback)(void *), int index) {
    if (index >= list->length) {
        m_list_add(list, data, free_callback);
        return;
    }
    struct m_list *temp = list;
    int i = 0;
    while (temp->next) {
        if (i == index) {
            break;
        }
        temp = temp->next;
        i = i + 1;
    }
    struct m_list *node = m_list_init(data, free_callback);
    node->next = temp->next;
    temp->next = node;
    list->length = list->length + 1;
}
void m_list_remove(struct m_list *list, void *data) {
    struct m_list *temp = list;
    while (temp->next) {
        if (temp->next->data == data) {
            temp->next = temp->next->next;
            list->length = list->length - 1;
            break;
        }
        temp = temp->next;
    }
}
void m_list_delete(struct m_list *list, void *data) {
    struct m_list *temp = list;
    while (temp->next) {
        if (temp->next->data == data) {
            struct m_list *node = temp->next;
            temp->next = temp->next->next;
            list->length = list->length - 1;
            m_list_free_node(node);
            break;
        }
        temp = temp->next;
    }
}
void m_list_free_node(struct m_list *node) {
    if (node->free_callback) {
        node->free_callback(node->data);
    }
    free(node);
}
