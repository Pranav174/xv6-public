// #include "proc.h"

void mlfq_init(void);
struct proc* next_process();
void add_to_mlfq(struct proc* p);
void displayAll();
void reAdjust();