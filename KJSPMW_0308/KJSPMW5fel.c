#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    pid_t p = fork();
    pid_t p2 = fork();
    if ( p == -1 )
    {
        perror("Fork failed");
        return EXIT_FAILURE;
    }
    else if ( p == 0 )
    {
        execl("/bin/sh", "bin/sh", "-c", "./error", "NULL");
        return EXIT_FAILURE;
    }

    if ( p2 == -1 )
    {
        perror("Fork failed");
        return EXIT_FAILURE;
    }
    else if ( p2 == 0 )
    {
        execl("/bin/sh", "bin/sh", "-c", "./dividezero", "NULL");
        return EXIT_FAILURE;
    }

    int status;
    if ( waitpid(p, &status, 0) == -1 )
    {
        perror("Waitpid failed");
        return EXIT_FAILURE;
    }

    if ( WIFEXITED(status) )
    {
        const int es = WEXITSTATUS(status);
        printf("Exit status was %d\n", es);
    }

    if ( waitpid(p2, &status, 0) == -1 )
    {
        perror("Waitpid failed");
        return EXIT_FAILURE;
    }

    if ( WIFEXITED(status) )
    {
        const int es = WEXITSTATUS(status);
        printf("Exit status was %d\n", es);
    }
    return EXIT_SUCCESS;
}
