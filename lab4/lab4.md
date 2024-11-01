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
$VAR_NAME
# $VAR_NAME returns the home directory path.
echo $VAR_NAME
# You can also display the value of a variable using echo
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
How are environment variables affected when a new program is executed via `execve()`?

The function `execve()` calls a system call to load a new command and execute it; this function never returns. No new process is created; instead, the calling process’s text, data, bss, and stack are **overwritten** by that of the program loaded. `execve()` runs the new program inside the calling process.

1) Compile and run this program:
```c
#include <unistd.h>

extern char **environ;
int main()
{
    char *argv[2];
    argv[0] = "/usr/bin/env";
    argv[1] = NULL;
    execve("/usr/bin/env", argv, NULL); 
    return 0 ;
}
//  This program simply executes a program called /usr/bin/env, which prints out the environment variables of the current process.
```

2) Change the invocation of `execve()` to the following:
```c
execve("/usr/bin/env", argv, environ);
```

3) Are the environment variables automatically inherited by the new program?
    
    When the third arguments set as NULL, no output. But when it turns to environ, all environment variables are printed. Because `environ` is the user environment which holds those environment variables.

##  Task 4: Environment Variables and system(): 
How are environment variables affected when a new program is executed via `system()`?

The function `system()` is used to execute a command, but unlike `execve()`, it executes `/bin/sh -c command`, i.e., it executes `/bin/sh`, and asks the shell to execute the `command`.

- Compile and run this program to verify this:
```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("/usr/bin/env");
    return 0 ;
}
```

- We see that the environment variables of the parent process is passed to the new program `/bin/sh`.

## Task 5: Environment Variable and Set-UID Programs:
**Set-UID** is an important security mechanism in Unix. When a **Set-UID** program runs, it assumes the owner’s privileges. For example, if the program’s owner is **root**, when anyone runs this program, the program gains the root’s privileges during its execution. 

Since **Set-UID** escalates the user’s privilege, it is quite risky. The behaviors of **Set-UID** programs are decided by their program logic, but users can affect the behaviors via environment variables.

1) Are environment variables inherited by the **Set-UID** program’s process from the user’s process? (Compile and run this program):
```c
#include <stdio.h>
#include <stdlib.h>

extern char **environ;
int main()
{
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++; }
}
```
2) Change the program's ownership to **root**, and make it a **Set-UID** program.
```bash
 sudo chown root prog
 sudo chmod 4755 foo 
 # the first (4) represents the Set-UID bit
 # (7) for owner: +rwx
 # (5) for group: +rx
 # (5) for others: +rx
```
- When the **Set-UID** bit is set, any user who executes the file will temporarily gain the permissions of the file's owner.
- When any user runs `./prog`, the program will execute with **root** privileges, allowing actions that a normal user usually cannot perform.

3) In your shell (you need to be in a **normal user account**, not the root account), use the `export`
command to set the following environment variables:
```bash
export PATH
export LD_LIBRARY_PATH
export ANY_NAME #this one is defined by you
```
- These environment variables are set in the user’s shell process. After you run `./prog`, , the shell forks a child process, and uses the child to run the program.
- Please check whether all the environment variables you set in the shell process (parent) get into the Set-UID child process.