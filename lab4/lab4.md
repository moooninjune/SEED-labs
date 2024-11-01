# Environment Variable and Set-UID Program Lab

## Task 1: Manipulating Environment Variables:
Environment variables are a set of **dynamic named values** that can affect the way running processes will behave on a computer.

- **Example:** $PATH, $HOME, $PWD, $USER, $SHELL, etc...

- Environment variable names are typically written in all **uppercase**.

If a program uses environment variables, but the programmer does not know that they are used, the program may have vulnerabilities.

### How Environment Variables Are Set and Accessed:
1) Setting an environment variable (with a value):
```bash
export VAR_NAME=value
export VAR_NAME="string with spaces"
```
2) Unsetting an environment variable:
```bash
unset VAR_NAME
```
3) Accessing an environment variable:
```bash
# $VAR_NAME returns the home directory path.
$VAR_NAME
# You can also display the value of a variable
echo $VAR_NAME
```
4) Viewing all environment variables (list all the current environment variables):
```bash
printenv #all
printenv PWD #for specific search

#or use the enc command
env #all
env | grep PWD #for specific search
```
##  Task 2: Passing Environment Variables from Parent Process to Child Process:
In Unix, `fork()` creates a new process by duplicating the calling process. The new child process is an exact duplicate of the parent process, except for its PID.

In this task, we would like to know whether the parent’s environment variables are inherited by the child process or not...

1. Compile and run this program, save the output in `child.txt` file:
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
        i++;
    }
}

void main() {
    pid_t childPid;
    switch(childPid = fork()) {
        case 0: /* child process */
        printenv(); 
        exit(0);
    default: /* parent process */
    // printenv(); 
    exit(0); }
}
```

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
## Task 3: Environment Variables and execve():
