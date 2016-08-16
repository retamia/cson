#include <stdio.h>
#include <stdlib.h>
#include "clist.h"
#include "cmap.h"
#include "cson.h"


int main(){
    /*CSON_LIST list = init_cson_list();
    list->append(list, (void *)1);
    list->push(list, (void *)2);
    list->push(list, (void *)3);
    list->push(list, (void *)4);
    list->push(list, (void *)5);
    list->append(list, (void *)0);

    for(unsigned int i =0; i<6;i++){
        printf("list index:%d, value:%d\n", i, (int)list->get(list, i));
    }

    cson_free_list(list);

    CSON_MAP map = init_cson_map();
    map->put(map, "aaa", (void *)1);
    map->put(map, "bbb", (void *)2);
    map->put(map, "ccc", (void *)3);
    map->put(map, "ddd", (void *)4);

    printf("map key:%s, value: %d\n", "aaa", (int)map->get(map, "aaa"));
    printf("map key:%s, value: %d\n", "bbb", (int)map->get(map, "bbb"));
    printf("map key:%s, value: %d\n", "ccc", (int)map->get(map, "ccc"));
    printf("map key:%s, value: %d\n", "ddd", (int)map->get(map, "ddd"));

    cson_free_map(map);*/

    parse_cson_with_file("/Users/retamia/Dev/c/cson/test.json");

    return EXIT_SUCCESS;
}
