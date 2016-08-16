//
// Created by retamia on 16/7/13.
//

#ifndef CSON_CSON_H
#define CSON_CSON_H

#include "clist.h"
#include "cmap.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

typedef CSON_MAP CSON_OBJECT;
typedef struct cson *CSON;

enum cson_type{
    NUMBER,
    STRING,
    ARRAY,
    OBJECT,
    BOOL,
    NIL
};

struct cson {
    enum cson_type type;
    union {
        char *string;
        union {
            long i_number;
            double d_number;
        } number;
        CSON_OBJECT object;
        CSON_LIST array;
        bool boolean;
    } *value;
};

CSON_LIST cson_tokenizer(const char *json_str);

CSON parse_cson_with_file(const char *filepath);

CSON parse_tokens(CSON_LIST tokens);

CSON parse_cson(const char *json_str);
#endif //CSON_CSON_H
