#include <stdio.h>

void my_strcpy(char* dest, const char* src) {
    size_t i = 0;
    for (const char* p = src; *p; p += 1) {
        dest[i] = src[i];
        i += 1;
    }
}

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];

    // TODO: 在这里添加你的代码
    my_strcpy(destination, source);

    printf("拷贝后的字符串: %s", destination);

    return 0;
}
