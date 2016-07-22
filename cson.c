//
// Created by retamia on 16/7/13.
//
#include "cson.h"
#include <stdlib.h>
#include <stdio.h>

struct cson_object *parse_cson(const char *json_str) {
    //todo tokenizer
    //todo parse json string
}

struct cson_object *parse_cson_with_file(const char *file_path) {
    FILE *json_file = fopen(file_path, "rb");

    if (json_file == NULL) {
        perror("json file open error");
    }

    fseek(json_file, 0, SEEK_END);
    size_t file_size = (size_t) ftell(json_file);
    fseek(json_file, 0, SEEK_SET);

    char *json_str = (char *) malloc((file_size + 1) * sizeof(char));

    if (json_str == NULL) {
        perror("run out of memory");
    }

    fread(json_str, file_size, sizeof(char), json_file);
    json_str[file_size] = '\0';
    printf("%s", json_str);
    struct cson_object *node = parse_cson(json_str);
    free(json_str);
    fclose(json_file);
    return node;
}
