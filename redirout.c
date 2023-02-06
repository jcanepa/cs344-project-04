#include <stdio.h>  // printf, perror
#include <stdlib.h> // exit
#include <unistd.h> // fork, execlp, close
#include <fcntl.h>  // open

int main(int argc, char *argv[])
{
    // validate argument count
    if (argc < 3)
    {
        printf("usage: `redirout outfilename command [-opt1[, -opt2...]]`\n");
        exit(1);
    }

    // open descriptor of specified file
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0644);

    // i/o pipe
    int pipe_fd[2];
    pipe(pipe_fd);

    // fork child process
    pid_t pid = fork();

    if (pid == -1)
    {
        // error!
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        // child and passes syscall output into pipe
        close(pipe_fd[0]);   // closes read end of pipe
        dup2(pipe_fd[1], 1); // connect write end to stdout

        // parse command arguments
        char *arguments[argc - 2];
        int index = 0;
        for (int i = 2; i < argc; i++)
        {
            arguments[index] = argv[i];
            index++;
        }
        arguments[index] = NULL;

        // make syscall
        execvp(argv[2], arguments);
        perror("execlp");
        exit(0);
    }
    else
    {
        // parent
        close(pipe_fd[1]);   // closes write end of pipe
        dup2(pipe_fd[0], 0); // connects read end to stdin

        char buf[1024];
        ssize_t bytes_to_rw = read(pipe_fd[0], buf, 1024);
        write(fd, buf, bytes_to_rw);
    }

    // housekeeping
    close(fd);
    close(pipe_fd[0]);

    return 0;
}
