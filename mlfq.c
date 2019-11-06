#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"

struct proc *mlfq_queue[5][NPROC + 5];
int front[5], rear[5], size[5] = {0, 0, 0, 0, 0};
#define STARTVATION_LIMIT 200

void enqueue(int priority, struct proc *p)
{
    if (size[priority])
    {
        rear[priority]++;
        rear[priority] %= (NPROC + 5);
    }
    else
    {
        rear[priority] = 0;
        front[priority] = 0;
    }
    mlfq_queue[priority][rear[priority]] = p;
    size[priority]++;
}

struct proc *dequeue(int priority)
{
    if (size[priority])
    {
        int temp = front[priority];
        front[priority]++;
        front[priority] %= (NPROC + 5);
        size[priority]--;
        return mlfq_queue[priority][temp];
    }
    return 0;
}

struct proc *next_process()
{
    for (int i = 0; i < 5; i++)
    {
        if (size[i])
        {
            return dequeue(i);
        }
    }
    return 0;
}

void add_to_mlfq(struct proc *p)
{
    enqueue(p->priority, p);
}
void promote_and_add_to_mlfq(struct proc *p)
{
    if ((p->priority) > 0)
        (p->priority)--;
    add_to_mlfq(p);
}

void displayAll()
{
    for (int i = 0; i < 5; i++)
    {
        cprintf("size=%d queue %d: ", size[i], i);
        for (int j = 0; j < size[i]; j++)
        {
            cprintf("%d ", mlfq_queue[i][(front[i] + j)%((NPROC + 5))]->pid);
        }
        cprintf("\n");
    }
}

int should_be_promoted(struct proc *p)
{
    if((ticks - (p->ltime))>=STARTVATION_LIMIT){
        return 1;
    }
    return 0;
}

void reAdjust()
{
    struct proc *p;
    for (int i = 1; i <= 4; i++)
    {
        int to_insert = front[i];
        int temp = size[i];
        for (int j = 0; j < temp; j++)
        {
            p = mlfq_queue[i][(front[i] + j)%((NPROC + 5))];
            if (should_be_promoted(p)){
                size[i]--;
                // cprintf("process %d promoted from %d\n", p->pid, i);
                promote_and_add_to_mlfq(p);
            }
            else{
                mlfq_queue[i][to_insert] = p;
                to_insert++;
                to_insert%=(NPROC + 5);
            }
        }
        rear[i] = (front[i]+size[i]-1)%(NPROC + 5);
    }
}