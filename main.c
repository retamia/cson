#include <stdio.h>
#include <stdlib.h>
#include "src/cson.h"


int main(){
    CSON json_obj = parse_cson("{\"str\": \"test\", \"nil\": null, \"strings\": [ \"a\", \"b\", \"c\" ] }");
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
