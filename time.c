#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"

int main(int argc, char *argv[])
{
    if(argc==1){
        printf(1,"requires more than 1 input\n");
        exit();
        sleep(2);
    }
    int pid;
    int status, wtime, rtime;
    pid = fork();
    if (pid == 0)
    {
        exec(argv[1], argv + 1);
        printf(1, "exec %s failed\n", argv[1]);
    }
    else
    {
        status = waitx(&wtime, &rtime);
        printf(1, "\nWait Time = %d ticks. Run Time = %d ticks. Return status %d \n", wtime, rtime, status);
    }
    exit();
}