#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int     fd[2], nbytes;
    pid_t   childpid;
    char    string[] = "Karczub Roland , KJSPMW\n";
    char    readbuffer[80];

    pipe(fd);

    if((childpid = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }

    if(childpid == 0)
    {
        close(fd[0]);
        write(fd[1], string, (strlen(string)+1));
        exit(0);
    }
    else
    {
        close(fd[1]);
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
        printf("%s", readbuffer);
    }

    return 0;
}
