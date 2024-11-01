## Task 8: Invoking External Programs Using system() versus execve():
Using `system()` in privileged programs like **Set-UID** programs is risky due to the influence of the `PATH` environment variable on shell behavior. Unlike `system()`, `execve()` directly executes a program without invoking a shell, making it safer.

**An example scenario illustrates this risk:** Bob, an auditor needing access to all files for an investigation, is given a **Set-UID** program by Vince, the superuser. This program allows Bob to read any file using `/bin/cat`, but prevents him from modifying files, thus protecting system integrity while still granting necessary access.

1) Compile this program, make it a root-owned Set-UID program:
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char *v[3];
  char *command;

  if(argc < 2) {
    printf("Please type a file name.\n");
    return 1; }

  v[0] = "/bin/cat"; v[1] = argv[1]; v[2] = NULL;

  command = malloc(strlen(v[0]) + strlen(v[1]) + 2);
  sprintf(command, "%s %s", v[0], v[1]);

  // Use only one of the followings.
  system(command);
  // execve(v[0], v, NULL);

  return 0 ;
}
```
> If you (as Bob) run this program, can you compromise system integrity, such as deleting a non-writable file?

    Yes.

2) Comment out the `system(command)` statement, and uncomment the `execve()` statement; the program will use `execve()` to invoke the command. Compile the program, and make it a root-owned **Set-UID**.

> Do the attacks possible in Step 1 still work with this new setup? Describe and explain your observations regarding the differences in behavior between using `system()` and `execve()`.

    No.