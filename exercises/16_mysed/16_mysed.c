#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    // TODO: 在这里添加你的代码
    char* second = strchr(cmd + 2, '/');

    *old_str = (char*)malloc(sizeof(char) * (second - cmd - 1));
    strncpy(*old_str, cmd + 2, second - cmd - 2);
    (*old_str)[second - cmd - 2] = '\0';

    *new_str = (char*)malloc(strlen(cmd) - (second - cmd + 1));
    strncpy(*new_str, second + 1, strlen(cmd) - (second - cmd + 1) - 1);
    (*new_str)[strlen(cmd) - (second - cmd + 1) - 1] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // TODO: 在这里添加你的代码
    char* pos = strstr(str, old);
    if (pos) {
        char buffer[MAX_LINE_LENGTH];
        size_t prefix_len = pos - str;
        snprintf(buffer, sizeof(buffer), "%.*s%s%s", (int)prefix_len, str, new, pos + strlen(old));
        strncpy(str, buffer, MAX_LINE_LENGTH - 1);
        str[MAX_LINE_LENGTH - 1] = '\0';
    }
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;

    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
