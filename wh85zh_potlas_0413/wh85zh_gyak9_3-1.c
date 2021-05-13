#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Hasznalat: ./wh85zh_gyak9_3-1 PID\n");
        return 1;
    }

    pid_t pid = (pid_t)atoi(argv[1]);
    kill(pid, SIGALRM);
    return 0;
}
