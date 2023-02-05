#include <stdio.h>  // printf, perror
#include <unistd.h> // exit
#include <fcntl.h>  // fork, execlp, close

int main(int argc, char const *argv[])
{
    // parse the command line
    if (argc > 1)
        printf("%s\n", argv[1]); // user provided a dir

    int pipe_fd[2]; // 0 ← in, 1 ← out
    pipe(pipe_fd);

    int fd = open("foo.out", O_CREAT | O_WRONLY, 0644); // r/w permissions

    pid_t pid = fork();

    // handle fork error
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    // child process
    if (pid == 0)
    {
        // read end into stdin
        dup2(pipe_fd[0], 0);
        // close write end
        close(pipe_fd[1]);

        // do wc
        // execlp("/usr/bin");

        perror("execlp");
        exit(0);
    }

    // write();

    // wait(NULL);

    close(fd);
}