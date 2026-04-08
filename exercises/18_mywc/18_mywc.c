#include <stdio.h>

#include "mywc.h"

int main(int argc, char* argv[]) {
    const char* filepath = "./text.txt";

    process_file(filepath);
    return 0;
}
