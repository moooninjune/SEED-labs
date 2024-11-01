## Task 6: The PATH Environment Variable and Set-UID Programs:
Calling `system()` within a **Set-UID** program is risky because the shell program invoked can be influenced by user-defined environment variables, such as **PATH**. Malicious users can alter these variables to manipulate the behavior of the **Set-UID** program, potentially leading to security vulnerabilities.

- **Note:** The `PATH` variable is an environment variable that tells the operating system where to look for executable files (programs) when you type a command in the terminal.

1) This **Set-UID** program is supposed to execute the `/bin/ls` command:
```c
#include <stdlib.h>

int main()
{
    system("ls");
    return 0;
}
```
- We want to edit this code to run our own malicious code instead of `/bin/ls`. Edit the code and compile it, change its owner to root, and make it a **Set-UID** program. Name the program `ls`.
```c
#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf("Hello! This is not the ls command anymore! I edited it! \n");
    return 0;
}
```
```bash
sudo chown root ls 
sudo chmod 4755 ls #make it set-uid
```

2) Now, if we write `ls`, it still runs the correct `/bin/ls` command. What we have to do is edit the environment variable `PATH` to our own path (where our `ls` program exists).
```bash
export PATH=/home/seed/lab4/task6:$PATH
```
```bash
#BEFORE
printenv PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:.

#AFTER
printenv PATH
/home/seed/lab4/task6:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:.
```
- **Note:** If you changed PATH in your current terminal session using `export`, this change is temporary and will only last until you close the terminal. When you open a new terminal session, PATH will revert to its original value.

3) Now try to run the `ls` command ;)
```bash
$ ls #will run your malicious code!
Hello! This is not the ls command anymore! I edited it!

$ /bin/ls #this one will list all the files just right
ls ls.c task6 task6.c
```
- Why did it run our code instead of executing the `/bin/ls`?