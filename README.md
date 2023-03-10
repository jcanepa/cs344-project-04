# CS344 Project 04, OSU-Cascades

Project contains two programs:

- `lscw` implements the `|` shell pipe operator from scratch.
- `redirout` redirects the output of the user's command into a specified file.

Both projects demonstrate multi-processing, i/o, pipes, syscalls. The following functions `fork()`, `execlp()`, `execvp()`, `open()`, `read()`, `close()` were relied upon heavily.

## Compilation

```
make
```

## `lscw`

Usage:

```
./lscw ~
```

Where `~` is any valid path. Ex: `/usr/bin`.

## `redirout`

Usage:

```
./redirout out.txt ls -l -a
```

Where `out.txt` is the filename to pipe command output to. And `ls ...` is a valid shell command.

After running the program above, see the output file.

```
cat out.txt
```
