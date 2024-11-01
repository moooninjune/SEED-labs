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
 sudo chown root setuid #setuid is the program's name
 # changes the ownership of the file foo to the user root
 sudo chmod 4755 setuid 
 # the first (4) represents the Set-UID bit
 # (7) for owner: +rwx
 # (5) for group: +rx
 # (5) for others: +rx
```
> When the **Set-UID** bit is set, any user who executes the file will temporarily gain the permissions of the file's owner.

> When any user runs `./prog`, the program will execute with **root** privileges, allowing actions that a normal user usually cannot perform.

3) In your shell (you need to be in a **normal user account**, not the root account, check that by using the command `whoami`), use the `export`
command to set the following environment variables:
```bash
export PATH
export LD_LIBRARY_PATH
export MY_VAR=Hello #this one is defined by you
```
> These environment variables are set in the user’s shell process. After you run `./prog`, , the shell forks a child process, and uses the child to run the program.

- Check whether all the environment variables you set in the shell process (parent) get into the Set-UID child process.
```bash
./setuid | grep PATH
./setuid | grep LD_LIBRARY_PATH
./setuid | grep MY_VAR
```