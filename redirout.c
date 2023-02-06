#include <stdio.h>  // printf, perror
#include <stdlib.h> // exit
#include <unistd.h> // fork, execlp, close
#include <fcntl.h>  // open

int main(int argc, char *argv[])
{
    // validate argument count
    if (argc < 3)
    {
        printf("\nInsufficient number of arguments supplied to %s\n  usage: `./redirout outfilename command [-opt1[, -opt2...]]`\n", argv[0]);
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
        // child writes syscall output into pipe
        close(pipe_fd[0]);   // closes read end
        dup2(pipe_fd[1], 1); // connect write end to stdout

        // retrieve command arguments
        char *command = argv[2];
        char **arguments = argv + 2;

        // make syscall
        execvp(command, arguments);
        perror("execlp");
        exit(0);
    }
    else
    {
        // parent writes what is read from pipe
        close(pipe_fd[1]);   // closes write end
        dup2(pipe_fd[0], 0); // connects read end to stdin

        // read from pipe, write to file
        char buf[1024];
        ssize_t bytes_to_rw;

        while (bytes_to_rw = read(pipe_fd[0], buf, 1024) > 0)
            write(fd, buf, bytes_to_rw);
        close(pipe_fd[0]);
    }
    close(fd);
    return 0;
}
