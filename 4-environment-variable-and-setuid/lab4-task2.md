##  Task 2: Passing Environment Variables from Parent Process to Child Process:
In Unix, `fork()` creates a new process by duplicating the calling process. The new child process is an exact duplicate of the parent process, except for its PID.

In this task, we would like to know whether the parent’s environment variables are inherited by the child process or not...

1. Compile and run the program named `myprintenv.c`, save the output in `child.txt` file:
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;
void printenv()
{
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++; }
}

void main()
{
    pid_t childPid;
    switch(childPid = fork()) {
        case 0: /* child process */
        printenv();
        exit(0);
    default: /* parent process */
    //printenv(); 
    exit(0); }
}
```
- `environ` is a global variable that holds the environment variables of the process.

2) For the 2nd step, make the parent do the `printenv()` function instead of the child. Compile and run the code again, and save the output in `parent.txt` file.
```c
switch(childPid = fork()) {
        case 0: /* child process */
        // printenv(); 
        exit(0);
    default: /* parent process */
    printenv(); 
    exit(0); }
```

3) Compare the difference of these two files using the `diff` command.
```bash
diff child.txt parent.txt
# there will be no difference
# their environment variables are exactly the same
```
