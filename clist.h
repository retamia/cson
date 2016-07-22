//
// Created by retamia on 16/7/20.
//

#ifndef CSON_CLIST_H
#define CSON_CLIST_H

#define true 1
#define false 0
#define bool int
typedef struct cson_list * CONS_LIST;
typedef int (*insert_to_head)(struct cson_list *, void *);

typedef int (*insert_to_tail)(struct cson_list *, void *);

typedef int (*_list_is_empty)(struct cson_list *);

struct cson_list {
    struct cson_node *head;  //指向链表头部
    struct cson_node *tail;  //指向链表尾部
    unsigned short   count;
    insert_to_head   append;
    insert_to_tail   push;
    _list_is_empty   is_empty;
};

struct cson_node {
    void             *value;
    struct cson_node *next;
    struct cson_node *previous;
};

struct cson_list *init_cson_list();

int _insert_to_head(struct cson_list *list, void *value);

int _insert_to_tail(struct cson_list *list, void *value);

int _is_empty(struct cson_list *list);

void free_list(struct cson_list *list);

#endif //CSON_CLIST_H
