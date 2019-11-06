#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"

struct proc_stat {
 int pid; // PID of each process
 int total_time; // Use suitable unit of time
 int runtime; // Use suitable unit of time
 int num_run; // number of time the process is executed
 int current_queue; // current assigned queue
 int ticks[5]; // number of ticks each process has received at each of the 5 priority queue
};

int main(int argc, char *argv[])
{
    int j = 0;
    j = 0;
    int priorty = 60;
    if(argc<2){
        printf(1,"provide the name for the lp");
        exit();
    }
    if(argc>=3){
        priorty=atoi(argv[2]);
        printf(1, "priorty of %s changed from %d to %d\n", argv[1], set_priority(priorty), priorty);
    }
    printf(1, "process %s started\n", argv[1]);
    for (volatile int i = 0; i <= 1000000000; i++)
    {
        j++;
        i=j;
    }
    printf(1, "process %s ended\n", argv[1]);
    struct proc_stat p;
    getpinfo(&p);
    printf(1, "PINFO:\n");
    printf(1, "pid:%d\n", p.pid);
    printf(1, "runtime:%d\n", p.runtime);
    printf(1, "total_time:%d\n", p.total_time);
    printf(1, "num_run:%d\n", p.num_run);
    printf(1, "current queue:%d\n", p.current_queue);
    for(int i=0; i<5; i++)
        printf(1, "ticks in queue %d = %d\n", i,p.ticks[i]);

    exit();
}