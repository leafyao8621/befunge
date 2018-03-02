#include "model.h"
#include "stack.h"
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        puts("Please only pass in source file name");
        return 1;
    }
    int dbg = 0;
    if (argc == 3) {
        dbg = 1;
    }
    Data* data = init_from_file(argv[1]);
    if (!data) {
        puts("Cannot open file");
        return 2;
    }
    //print_map(data);
    Stack* stack = malloc_Stack();
    Cursor* cursor = malloc_Cursor();
    while (!handle(data, cursor, stack, dbg));
}
