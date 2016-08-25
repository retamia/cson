//
// Created by retamia on 16/7/13.
//

#include "cson.h"

int scan_null(const char *json_str) {
    if (*json_str == 'n' && *(json_str + 1) == 'u' && *(json_str + 2) == 'l' && *(json_str + 3) == 'l') {
        return true;
    } else {
        return false;
    };
}

char *scan_string(const char *json_str) {
    unsigned short str_len = 1;

    while ('"' != *(json_str + str_len)) {
        str_len += 1;
    }
    str_len += 2;
    char *token = malloc(str_len * sizeof(char));
    memcpy(token, json_str, str_len - 1);
    token[str_len] = '\0';
    return token;
}

char *scan_negative(const char *json_str) {
    int  index = 1;
    char c;

    while (',' != (c = *(json_str + index))) {
        if (!(c >= 48 && c <= 57)) {
            perror("json string parse negative number error");
            exit(EXIT_FAILURE);
        }

        ++index;
    }

    char *token = malloc(index * sizeof(char));
    memcpy(token, json_str, index);
    token[index] = '\0';
    return token;
}

char *scan_natural(const char *json_str) {
    int  index = 0;
    char c     = *json_str;
    while (',' != c && '\n' != c) {
        if (!(c >= 48 && c <= 57)) {
            perror("json string parse natural number error");
            exit(EXIT_FAILURE);
        }
        c = *(json_str + index);
        ++index;
    }

    char *token = malloc(index * sizeof(char));
    memcpy(token, json_str, index - 1);
    token[index] = '\0';
    return token;
}

char *_convertStringToken(const char *str) {

    if (str[0] != '"') {
        perror("convert string token error");
        exit(EXIT_FAILURE);
    }

    size_t len  = strlen(str);
    char   *ret = malloc((len - 1) * sizeof(char));

    if (ret == NULL) {
        perror("run out of memory");
        exit(EXIT_FAILURE);
    }

    memcpy(ret, str + 1, len);
    ret[len - 2] = '\0';
    return ret;
}

CSON _parse_value(const char *value, CSON_LIST tokens) {
    CSON cson_value = (CSON) malloc(sizeof(struct cson));

    if (value[0] == '"') {
        cson_value->type = STRING;
        char *str_val = _convertStringToken(value);
        cson_value->value.string = str_val;
    } else if (value[0] == '{') {
        cson_value->type = OBJECT;
        CSON_OBJECT cson_sub_object = _parse_object(tokens);
        cson_value->value.object = cson_sub_object;
    } else if (value[0] == 'n') {
        cson_value->type = NIL;
        //cson_value->value = NULL;
    } else if (value[0] == '[') {
        cson_value->type        = ARRAY;
        cson_value->value.array = _parse_array(tokens);
    } else if (value[0] == 't') {
        cson_value->type          = BOOL;
        cson_value->value.boolean = true;
    } else if (value[0] == 'f') {
        cson_value->type          = BOOL;
        cson_value->value.boolean = false;
    }
    // TODO parse number value

    return cson_value;
}

CSON_OBJECT _parse_object(CSON_LIST tokens) {
    CSON_OBJECT cson_object = init_cson_map();

    char *first;
    while (strcmp("}", first = (char *) tokens->pop(tokens)) != 0) {
        char *key   = first;
        char *colon = (char *) tokens->pop(tokens);
        char *value = (char *) tokens->pop(tokens);

        if (strcmp(":", colon) != 0) {
            perror("parse json object colon error");
            exit(EXIT_FAILURE);
        }

        if (key[0] != '"') {
            perror("parse json object key error");
            exit(EXIT_FAILURE);
        }

        char *new_key = _convertStringToken(key);
        free(key);
        CSON cson_value = _parse_value(value, tokens);

        cson_object->put(cson_object, new_key, cson_value);
    }

    return cson_object;
}

CSON_LIST _parse_array(CSON_LIST tokens) {
    CSON_LIST list = init_cson_list();

    char *first;
    while (strcmp("]", first = (char *) tokens->pop(tokens)) != 0) {
        char *value     = first;
        CSON cson_value = _parse_value(value, tokens);
        list->push(list, cson_value);
    }

    return list;
}

CSON_LIST cson_tokenizer(const char *json_str) {
    CSON_LIST tokens = init_cson_list();
    char      c;
    while ('\0' != (c = *json_str++)) {
        if (c == '\n' || c == ' ') {
            continue;
        }

        if (c == '"') {
            char *token = scan_string(json_str - 1);
            tokens->push(tokens, token);
            json_str += (strlen(token) - 1);
        } else if (c == ':') {
            char *token = (char *) malloc(2 * sizeof(char));
            strcpy(token, ":\0");
            tokens->push(tokens, token);
        } else if (c == 'n') {
            bool result = scan_null(json_str - 1);
            if (!result) {
                perror("json parser null syntax error");
                exit(EXIT_FAILURE);
            }

            char *token = (char *) malloc(5 * sizeof(char));;
            strcpy(token, "null\0");
            tokens->push(tokens, token);
            json_str += 4;
        } else if (c == '-') {
            char *token = scan_negative(json_str - 1);
            tokens->push(tokens, token);
            json_str += (strlen(token) - 1);
        } else if (c >= 48 && c <= 57) {
            char *token = scan_natural(json_str - 1);
            tokens->push(tokens, token);
            json_str += (strlen(token) - 1);
        } else if (c == '{') {
            char *token = (char *) malloc(2 * sizeof(char));
            strcpy(token, "{\0");
            tokens->push(tokens, token);
        } else if (c == '}') {
            char *token = (char *) malloc(2 * sizeof(char));
            strcpy(token, "}\0");
            tokens->push(tokens, token);
        } else if (c == '[') {
            char *token = (char *) malloc(2 * sizeof(char));
            strcpy(token, "[\0");
            tokens->push(tokens, token);
        } else if (c == ']') {
            char *token = (char *) malloc(2 * sizeof(char));
            strcpy(token, "]\0");
            tokens->push(tokens, token);
        } else if (c == 't') {
            char *token = (char *) malloc(5 * sizeof(char));
            strcpy(token, "true\0");
            tokens->push(tokens, token);
            json_str += 4;
        } else if (c == 'f') {
            char *token = (char *) malloc(6 * sizeof(char));
            strcpy(token, "false\0");
            tokens->push(tokens, token);
            json_str += 5;
        }
    }

    return tokens;
}

CSON parse_cson(const char *json_str) {
    CSON_LIST tokens = cson_tokenizer(json_str);

    for (int i = 0; i < tokens->count; ++i) {
        printf("[DEBUG] token: %s\n", (char *) tokens->get(tokens, i));
    }

    CSON cson = parse_tokens(tokens);
    cson_free_list(tokens);
    return cson;
}

CSON parse_tokens(CSON_LIST tokens) {
    char *start = (char *) tokens->pop(tokens);
    CSON cson   = (CSON) malloc(sizeof(struct cson));

    if (cson == NULL) {
        perror("init cson error, run out of memory");
    }

    cson->type = NIL;

    if (strcmp(start, "{") == 0) {
        cson->type         = OBJECT;
        cson->value.object = _parse_object(tokens);
    } else if (strcmp(start, "[") == 0) {
        cson->type        = ARRAY;
        cson->value.array = _parse_array(tokens);
    } else {
        perror("parser error");
        exit(EXIT_FAILURE);
    }

    return cson;
}

CSON parse_cson_with_file(const char *file_path) {
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

    CSON cson = parse_cson(json_str);

    free(json_str);
    fclose(json_file);
    return cson;
}
