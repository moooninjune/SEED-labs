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