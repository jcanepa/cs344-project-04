#include <stdio.h>  // printf, perror
#include <stdlib.h> // exit
#include <unistd.h> // fork, execlp, close
#include <fcntl.h>  // open

int main(int argc, char const *argv[])
{
    if (argc < 4)
    {
        printf("usage `redirout outfilename command [opt1[, opt2...]]");
    }

    return 0;
}
