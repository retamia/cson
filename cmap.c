//
// Created by retamia on 16/7/27.
//
#include "cmap.h"

struct cson_map *init_cson_map() {
    CSON_MAP map = (struct cson_map *) malloc(sizeof(struct cson_map));

    if (map == NULL) {
        return NULL;
    }

    //初始化每个链表
    for (int i = 0; i < __CSON_CMAP_M; i++) {
        map->_array[i] = init_cson_list();
        if (map->_array[i] == NULL) {
            return NULL;
        }
    }

    map->size     = 0;
    map->get      = _cson_map_get;
    map->put      = _cson_map_put;
    map->contains = _cson_map_contains;
    map->delete   = _cson_map_del;
    map->is_empty = _cson_map_is_empty;

    return map;
}

void *_cson_map_get(struct cson_map *map, const char *key) {
    if (map->is_empty(map)) {
        return NULL;
    }

    u_int16_t index = _cson_hash(key);
    CSON_LIST list  = map->_array[index];

    void              *value = NULL;
    struct cson_pair  *pair;
    for (unsigned int i      = 0; i < list->count; ++i) {
        pair = (struct cson_pair *) list->get(list, i);
        if (strcmp(pair->key, key) == 0) {
            value = pair->value;
            break;
        }
    }

    return value;
}

void _cson_map_del(struct cson_map *map, const char *key) {

}

void _cson_map_put(struct cson_map *map, const char *key, void *value) {
    if (value == NULL) {
        return;
    }

    if (map->get(map, key) != NULL) {
        return;//todo 已经存在key的情况下覆盖原先的值
    }

    u_int16_t        index = _cson_hash(key);
    struct cson_pair *pair = (struct cson_pair *) malloc(sizeof(struct cson_pair));

    if (pair == NULL) {
        return;
    }

    pair->key   = key;
    pair->value = value;
    CSON_LIST list = map->_array[index];
    list->append(list, pair);
    map->size++;
}

bool _cson_map_contains(struct cson_map *map, const char *key) {
    return map->get(map, key) != NULL;
}

bool _cson_map_is_empty(struct cson_map *map) {
    return map->size == 0;
}

u_int16_t _cson_hash(const char *key) {
    int hash = 31;
    int c;

    while (0 != (c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return (uint16_t) ((hash & __CSON_CMAP_MASK) % __CSON_CMAP_M);
}


void cson_free_map(CSON_MAP map) {
    //todo map某个key的value是map类型 递归
    for (int i = 0; i < __CSON_CMAP_M; ++i) {
        cson_free_list(map->_array[i]);
    }
    map->size = 0;
    free(map);
    map = NULL;
}


