//
// Created by retamia on 16/7/20.
//
#include "clist.h"
#include <stdlib.h>

struct cson_list *init_cson_list() {
    struct cson_list *list = (struct cson_list *) malloc(sizeof(struct cson_list));

    if (list == NULL) {
        return NULL;
    }

    list->push   = _insert_to_tail;
    list->append   = _insert_to_head;
    list->count    = 0;
    list->is_empty = _is_empty;

    list->head = NULL;
    list->tail = NULL;

    return list;
}

int _is_empty(struct cson_list *list) {
    if (list == NULL) {
        return true;
    }

    return list->count == 0;
}

struct cson_node *_init_empty_node() {
    struct cson_node *node = (struct cson_node *) malloc(sizeof(struct cson_node));

    if (node == NULL) {
        return NULL;
    }

    node->previous = NULL;
    node->next     = NULL;
    node->value    = NULL;

    return node;
}

/**
 * 插入节点到头部
 * @param list
 * @param value
 * @return bool
 */
int _insert_to_head(struct cson_list *list, void *value) {
    struct cson_node *node = _init_empty_node();

    if (node == NULL) {
        return false;
    }

    if (list->is_empty(list)) {
        list->tail = node;
        node->next = list->head;
    } else {
        node->next = list->head->next;
    }

    node->value = value;
    node->previous = list->head;
    list->head     = node;
    list->count++;
    return true;
}

/**
 * 插入节点到尾部
 * @param list
 * @param value
 * @return bool
 */
int _insert_to_tail(struct cson_list *list, void *value) {


    if (list->is_empty(list)) {
        bool success = list->append(list, value);
        if (!success) {
            return false;
        }

        list->tail = list->head;
        return true;
    }

    struct cson_node *node = _init_empty_node();

    if (node == NULL) {
        return false;
    }
    node->next     = NULL;
    node->value    = value;
    node->previous = list->tail;
    list->tail     = node;
    list->count++;
    return true;
}

void free_list(struct cson_list *list) {
    if (!list->is_empty(list)) {
        struct cson_node *node = list->tail;
        while (node) {
            //todo 如果node是cson_list那就递归调用这个函数
            struct cson_node *prev = node->previous;
            free(node);
            node = prev;
        }
    }
    free(list);
    list = NULL;
}