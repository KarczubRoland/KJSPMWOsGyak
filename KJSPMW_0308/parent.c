#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        execl("child", "Command-Line", NULL);
    }
    waitpid(pid, NULL, 0);

    printf("A gyermek processz lefuttatva!");
    return 0;
}
