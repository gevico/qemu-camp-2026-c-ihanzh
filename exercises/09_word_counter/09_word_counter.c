#include <ctype.h>
#include <stdio.h>

int count_word(const char* str) {
    int count = 0;
    const char* p = str;
    while (*p && *p == ' ') ++p;
    while (*p) {
        if (*p && *p == ' ') {
            count += 1;
            while (*p && *p == ' ') ++p;
        }
        ++p;
    }
    if (*(p - 1) != ' ') count += 1;
    return count;
}

int main() {
    char str[] = "Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    // TODO: 在这里添加你的代码
    wordCount = count_word(str);
    printf("单词数量: %d\n", wordCount);

    return 0;
}
