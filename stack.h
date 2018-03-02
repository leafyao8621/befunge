typedef struct Stack Stack;

Stack* malloc_Stack(void);
int push(Stack* stack, int val);
int pop(Stack* stack, int* out);
int copy_val(Stack* stack);
int swap_val(Stack* stack);
int print_Stack(Stack* s);
