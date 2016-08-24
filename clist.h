//
// Created by retamia on 16/7/20.
//

#ifndef CSON_CLIST_H
#define CSON_CLIST_H

#define true 1
#define false 0
#define bool int
typedef struct cson_list *CSON_LIST;

typedef int (*insert_to_head)(struct cson_list *, void *);

typedef int (*insert_to_tail)(struct cson_list *, void *);

typedef int (*_list_is_empty)(struct cson_list *);

typedef void *(*_get)(struct cson_list *, const unsigned int);

typedef void *(*_pop)(struct cson_list *);

struct cson_list {
    struct cson_node *head;  //指向链表头部
    struct cson_node *tail;  //指向链表尾部
    unsigned int     count;
    insert_to_head   append;
    insert_to_tail   push;
    _get             get;
    _list_is_empty   is_empty;
    _pop             pop;
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

void *_get_by_index(struct cson_list *list, const unsigned int index);

void cson_free_list(struct cson_list *list);

void *_cson_pop(struct cson_list *list);

#endif //CSON_CLIST_H
