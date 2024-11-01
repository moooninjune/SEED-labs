## Task 3: Environment Variables and execve():
How are environment variables affected when a new program is executed via `execve()`?

The function `execve()` calls a system call to load a new command and execute it; this function never returns. No new process is created; instead, the calling process’s text, data, bss, and stack are **overwritten** by that of the program loaded. `execve()` runs the new program inside the calling process.

1) Compile and run this program named `myenv.c`. This program simply executes a program called `/usr/bin/env`, which prints out the environment variables of the current process.

2) Change the invocation of `execve()` to the following:
```c
execve("/usr/bin/env", argv, environ);
```

3) Are the environment variables automatically inherited by the new program?
    
    When the third arguments set as NULL, no output. But when it turns to environ, all environment variables are printed. Because `environ` is the user environment which holds those environment variables.
