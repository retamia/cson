#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cson.h"
#include "clist.h"

int main(){
    CONS_LIST list = init_cson_list();
    list->append(list, (void *)1);
    list->push(list, (void *)2);
    list->push(list, (void *)3);
    list->push(list, (void *)4);
    list->push(list, (void *)5);
    list->append(list, (void *)0);
    free_list(list);
    return EXIT_SUCCESS;
}
