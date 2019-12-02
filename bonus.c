#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"
struct proc_stat
{
  int pid;           // PID of each process
  int runtime;       // Use suitable unit of time
  int total_time;    // Use suitable unit of time
  int num_run;       // number of time the process is executed
  int current_queue; // current assigned queue
  int ticks[5];      // number of ticks each process has received at each of the 5 priority queue
};
int number_of_processes = 10;
int main(int argc, char *argv[])
{
  int j;
  for (j = 0; j < number_of_processes; j++)
  {
    printf(1, "%d\n", j);
    int pid = fork();
    if (pid < 0)
    {
      printf(1, "fork failed lmao\n");
      continue;
    }
    if (pid == 0)
    {
      volatile int i;
      for (volatile int k = 0; k < number_of_processes; k++)
      {
        if (k <= j)
        {
          sleep(200); //io time
        }
        else
        {
          for (i = 0; i < 100000000; i++)
          {
            ;
          }
        }
        // cps();
      }
      printf(1, "%d\n", j);
      exit();
    }
  }
  for (int l = 0; l < 25; l++)
  {
    cps();
    sleep(100);
  }
  for (j = 0; j < 20; j++)
  {
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
  for (int i = 0; i < 5; i++)
    printf(1, "ticks in queue %d = %d\n", i, p.ticks[i]);

  exit();
}