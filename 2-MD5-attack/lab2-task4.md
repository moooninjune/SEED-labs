## Task 4: Making the Two Programs Behave Differently
In the previous task, we have successfully created two programs that have the **same MD5 hash**, but their behaviors are different. However, their differences are only in the data they print out; they still execute the same sequence of instructions. In this task, we would like to achieve something more significant and more meaningful.

You plan to prepare two different programs...
- One program will always execute benign instructions and do good things,
- while the other program will execute malicious instructions and cause damages.
- You find a way to get these two programs **to share the same MD5 hash value.**


1. We create a program `prog.c` that have two arrays **X** and **Y**. We compare the contents of these two arrays; if they are the same, the benign code is executed; otherwise, the malicious code is executed.

```c
#include <stdio.h>

unsigned char X[200] = {
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"};

unsigned char Y[200] = {
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"};

int main()
{
    for (int i = 0; i < 200; i++)
    {
        if (X[i] != Y[i])
        {
            printf("Malicious\n");
            return 0;
        }
    }
    printf("Benign\n");
    return 0;
}
```
```bash
gcc -o prog prog.c
```

2. Find where array **X** and **Y** start:
```
bless prog
```