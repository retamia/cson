//
// Created by retamia on 16/7/13.
//

#ifndef CSON_CSON_H
#define CSON_CSON_H

enum cson_type{
    NUMBER,
    STRING,
    ARRAY,
    OBJECT,
    BOOL,
    NIL,
    UNKNOWN
};

struct cson_object {
    enum cson_type type;
    char *name;
    union {
        double number;
        char *str;
        struct cson *child;
    };
};

struct cson_object *parse_cson_with_file(const char *filepath);

struct cson_object *parse_cson(const char *json_str);
#endif //CSON_CSON_H
