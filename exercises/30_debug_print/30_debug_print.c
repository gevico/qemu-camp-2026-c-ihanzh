#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#ifdef DEBUG_LEVEL

#if DEBUG_LEVEL == 1
#define DEBUG_PRINT(fmt, ...) \
    do { printf("DEBUG: func=%s, line=%d\n", __func__, __LINE__); } while (0)
#elif DEBUG_LEVEL == 2
#define DEBUG_PRINT(fmt, ...)                                            \
    do {                                                               \
        printf("DEBUG: func=%s, line=%d, ", __func__, __LINE__);      \
        printf(fmt, __VA_ARGS__);                                      \
        printf("\n");                                               \
    } while (0)
#elif DEBUG_LEVEL == 3
#define DEBUG_PRINT(fmt, ...)                                            \
    do {                                                               \
        printf("DEBUG: func=%s, line=%d, ", __func__, __LINE__);      \
        printf(fmt, __VA_ARGS__);                                      \
        printf("\n");                                               \
        void *buffer[16];                                               \
        int nptrs = backtrace(buffer, 16);                              \
        char **strings = backtrace_symbols(buffer, nptrs);              \
        if (strings) {                                                  \
            for (int i = 0; i < nptrs; i++)                            \
                printf("%s\n", strings[i]);                         \
            free(strings);                                              \
        }                                                               \
    } while (0)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

#else

#define DEBUG_PRINT(fmt, ...) do {} while (0)

#endif

// !MUST BE ENSURE THE DEBUG_PRINT("x=%d", x) AT THE 48 LINE


// 测试代码
void test() {
    int x = 42;
    DEBUG_PRINT("x=%d", x);
}

int main() {
    test();
    return 0;
}
