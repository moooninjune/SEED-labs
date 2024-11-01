##  Task 4: Environment Variables and system(): 
How are environment variables affected when a new program is executed via `system()`?

| Function | Execution | Environment Variables Inheritance | Security |
| -------- | --------- | ---------- | -------- |
| `execve()` | Directly runs the specified command | Only the environment variables explicitly passed to it | Lower risk because behavior is more predictable |
| `system()` | Runs `/bin/sh -c command`, using a shell to execute the command | Inherits all environment variables from the caller (e.g., `PATH`) | Higher risk, as inherited variables (like `PATH`) can alter shell behavior |

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