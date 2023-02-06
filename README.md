# cs344-project-04

Project contains two programs:  
- `lscw` implements pipe the `|` shell operator using syscalls in C.
- `redirout` redirects the output of the user's command into a specified file using pipes.

Both demonstrate multi-processing, i/o, syscalls. The following functions `fork()`, `execlp()`, `execvp()`, `open()`, `read()`, `close()`.

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
./redirout output.txt ls -l -a
```
