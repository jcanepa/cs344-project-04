#include <stdio.h>  // printf, perror
#include <unistd.h> // exit
#include <fcntl.h>  // fork, execlp, close

int main(int argc, char const *argv[])
{
    // parse the command line
    const char *directory = (argc > 1)
                                ? argv[1]
                                : NULL;

    // make a pipe
    int pipe_fd[2]; // 0 ← in, 1 ← out
    pipe(pipe_fd);

    // fork
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        // child process
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp");
    }
    else
    {
        // parent process
        close(pipe_fd[0]);
        dup2(pipe_fd[1], 1);
        execlp("ls", "ls", "-1a", directory);
    }
    return 0;
}