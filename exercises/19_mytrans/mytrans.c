// mytrans.c
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myhash.h"

void trim(char *str) {
    if (str == NULL) {
        return;
    }

    /* 去掉前导空白 */
    char *start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }

    /* 去掉尾部空白 */
    char *end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
}

int load_dictionary(const char *filename, HashTable *table, uint64_t *dict_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("无法打开词典文件");
        return -1;
    }

    char line[1024];
    char current_word[100] = {0};
    char current_translation[1024] = {0};
    int in_entry = 0;

    // TODO: 在这里添加你的代码
    while (1) {
        if (!fgets(line, sizeof(line), file)) {
            break;
        }

        if (line[0] != '#') {
            continue;
        }
        strncpy(current_word, line + 1, sizeof(current_word) - 1);
        current_word[sizeof(current_word) - 1] = '\0';
        trim(current_word);

        if (!fgets(line, sizeof(line), file)) {
            break;
        }

        char *begin = strchr(line, ':');
        if (!begin) {
            continue;
        }
        begin++;

        strncpy(current_translation, begin, sizeof(current_translation) - 1);
        current_translation[sizeof(current_translation) - 1] = '\0';
        trim(current_translation);

        if (hash_table_insert(table, current_word, current_translation)) {
            (*dict_count)++;
        }
    }

    fclose(file);
    return 0;
}
