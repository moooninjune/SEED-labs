## Task 8: Invoking External Programs Using system() versus execve():
| Function   | Description | Security Risk |
|------------|-------------|---------------|
| `system()` | Used to run new programs, invokes a shell which is influenced by environment variables (e.g., `PATH`).   | Risky for privileged programs (like Set-UID) as it can be manipulated via environment variables. |
| `execve()` | Also runs new programs, but does **not** invoke a shell. | Safer choice; avoids issues related to shell invocation and other security risks.|


**An example scenario illustrates this risk:**
  * Bob, an auditor, needs to look at all the files on a company’s Unix system to check for fraud but must not be able to change any files.

  * To make this possible, Vince, the system administrator, created a special program that runs with root privileges. When Bob types in a file name, the program displays the file’s contents using `/bin/cat` without allowing any edits.

  * This way, Bob can read any file he needs for his investigation, but he cannot modify anything, keeping the system safe.

1) Compile this program, and make it a root-owned Set-UID program:
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
```bash
gcc -o catall catall.c
sudo chown root catall
sudo chmod 4755 catall
```
2) Create any file text that Bob is supposed to only read from and can't modify:
```bash
echo "Hello Bob! I'm a file you can only read!" > bob.txt
```
3) Now run the `catall` program and use the `bob.txt` file you created as an input:
```bash
./catall bob.txt
#Output
Hello Bob! I'm a file you can only read!
```

### If you (as Bob) run this program, can you compromise system integrity, such as deleting a non-writable file?

Yes, by using a semicolon `;` after the file name, you can pass any second command you want.

```bash
./catall "bob.txt; nano bob.txt"
#Bob will be able to modify any file
./catall "bob.txt; rm bob.txt"
#or even delete them
```
---

4) Comment out the `system(command)` statement, and uncomment the `execve()` statement; the program will use `execve()` to invoke the command. Compile the program, and make it a root-owned **Set-UID**.
```c
// Use only one of the followings.
//system(command);
execve(v[0], v, NULL);
```
```bash
gcc -o catall catall.c
sudo chown root catall
sudo chmod 4755 catall
```

### Do the attacks possible in Step 1 still work with this new setup? Describe and explain your observations regarding the differences in behavior between using `system()` and `execve()`.

No. Using the same command will, you will get the error message "No such file or directory". Commands after a semicolon would not inherit root access with `execve()`, reverting instead to the user's privileges.

`execve()` simply treat the second argument as arguments of a command rather than invoking `/bin/sh` as `system()` do.
