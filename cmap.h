//
// Created by retamia on 16/7/22.
//

#ifndef CSON_CMAP_H
#define CSON_CMAP_H

#define __CSON_CMAP_MASK 0x7FFFFFFF
#define __CSON_CMAP_M 0x00002717

#include <stdio.h>
#include "clist.h"
#include <stdlib.h>
#include <string.h>

struct cson_pair {
    const char *key;
    void *value;
};

typedef struct cson_map *CSON_MAP;

typedef void *(*cson_map_get)(struct cson_map *, const char *key);

typedef void (*cson_map_del)(struct cson_map *, const char *key);

typedef void (*cson_map_put)(struct cson_map *, const char *, void *);

typedef bool (*cson_map_contains)(struct cson_map *, const char *);

typedef bool (*cson_map_is_empty)(struct cson_map *);

typedef void (*cson_map_put_pair)(CSON_MAP ,struct cson_pair *);

struct cson_map {
    cson_map_get      get;
    cson_map_del      delete;
    cson_map_put      put;
    cson_map_contains contains;
    cson_map_is_empty is_empty;
    cson_map_put_pair put_pair;
    CSON_LIST         _array[__CSON_CMAP_M];
    u_int16_t         size;
};

void *_cson_map_get(struct cson_map *map, const char *key);

void _cson_map_del(struct cson_map *map, const char *key);

void _cson_map_put(struct cson_map *map, const char *key, void *value);

void _cson_map_put_pair(CSON_MAP map, struct cson_pair *pair);

bool _cson_map_contains(struct cson_map *map, const char *key);

bool _cson_map_is_empty(struct cson_map *map);

u_int16_t _cson_hash(const char *key);

struct cson_map *init_cson_map();

void cson_free_map(CSON_MAP map);

#endif //CSON_CMAP_H
