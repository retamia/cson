# cson

A simple json parser for C


## API

CSON parse_cson(const char *json_str)

### Example

```c

    CSON json_obj = parse_cson("{\"str\": \"test\", \"nil\": null, \"strings\": [ \"a\", \"b\", \"c\" ] }");
    CSON_OBJECT object = json_obj->value.object;
    
    CSON str_value = (CSON)object->get(object, "str");
    printf("%s\n", str_value->value.string);  // print test
    
    CSON array_value = (CSON)object->get(object, "strings");
    CSON_LIST array = array_value->value.array;
    CSON item_value = (CSON)array->get(array, 0);
    printf("%s\n", item_value->value.string); // print a

```

CSON parse_cson_with_file(const char *file_path)

## TODO

support number type
...
