#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cson.h"
#include "clist.h"

int main(){
    CONS_LIST list = init_cson_list();
    list->append(list, (void *)"adsa");
    list->push(list, (void *)"54321");
    free_list(list);

    return EXIT_SUCCESS;
}
