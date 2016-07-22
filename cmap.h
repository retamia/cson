//
// Created by retamia on 16/7/22.
//

#ifndef CSON_CMAP_H
#define CSON_CMAP_H

#include "clist.h"

struct cson_pair {
    char *key;
    void *value;
};

typedef struct cson_pair *(*cons_map_get)(struct cson_map *, const char *key);

typedef struct cson_pair *(*cons_map_del)(struct cson_map *, const char *key);

//todo hash table 实现
struct cson_map {
    cons_map_get get;
    cons_map_del del;
};

struct cson_pair *_cons_map_get(struct cson_map *map, const char *key);

struct cson_pair *_cons_map_del(struct cson_map *map, const char *key);

unsigned short _cson_hash(const char *key);


#endif //CSON_CMAP_H
