#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"
struct proc_stat {
 int pid; // PID of each process
 int runtime; // Use suitable unit of time
 int total_time; // Use suitable unit of time
 int num_run; // number of time the process is executed
 int current_queue; // current assigned queue
 int ticks[5]; // number of ticks each process has received at each of the 5 priority queue
};
int
main(int argc, char *argv[])
{
  /* setpriority(1); */
  /* int pid = toint(argv[1]); */
  /* printf(1, "*%d*\n", pid); */
  /* int wtime = 0, rtime = 0; */
//   setpriority(1);
  int j;
  for (j = 0; j < 5; j++) {
    printf(1,"%d\n", j);
    int pid = fork();
    if(pid < 0){
      printf(1, "fork failed lmao\n");
      continue;
    }
    if (pid == 0) {
        volatile int i;
        for(i = 0; i < 1000000000; i++){
            ;
        }
        printf(1,"%d\n", j);
        exit();
    } else {
        // wait();
    }
  }
  for(j=0;j<20;j++){
      wait();
  }
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