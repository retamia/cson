# cson

A simple json parser for C

## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "cson.h"


int main(){
    CSON json_obj = parse_cson_with_file("/Users/retamia/Dev/c/cson/test.json");
    CSON_OBJECT object = json_obj->value.object;

    CSON str_value = (CSON)object->get(object, "str");
    printf("%s\n", str_value->value.string);

    CSON array_value = (CSON)object->get(object, "strings");
    CSON_LIST array = array_value->value.array;

    for (unsigned int i = 0; i < array->count; ++i) {
        CSON item_value = (CSON)array->get(array, i);
        printf("%s\n", item_value->value.string);
    }

    return EXIT_SUCCESS;
}


```
