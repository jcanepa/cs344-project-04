#include <stdio.h>  // printf, perror
#include <stdlib.h> // exit
#include <unistd.h> // fork, execlp, close

int main(int argc, char const *argv[])
{

    int pipe_fd[2];
    pipe(pipe_fd);

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        // child process reads
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp");
        exit(0);
    }
    else
    {
        // parent process writes
        close(pipe_fd[0]);
        dup2(pipe_fd[1], 1);
        const char *dir = (argc > 1) ? argv[1] : NULL;
        execlp("ls", "ls", "-1a", dir);
    }
    return 0;
}