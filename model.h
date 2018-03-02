#include "stack.h"
typedef struct Data Data;
typedef struct Cursor Cursor;

Data* init_from_file(char* file_name);
Cursor* malloc_Cursor(void);
int move(Cursor* c);
int handle(Data* d, Cursor* c, Stack* s, int dbg);
