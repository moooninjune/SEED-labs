## Task 9: Capability Leaking:
**Set-UID** lets regular users perform tasks that require higher permissions without giving them full control over the system. But, when a **Set-UID** program finishes its tasks, *it should give up its root privileges*. This is done using the system call `setuid()`, which changes the program's effective user ID to that of a normal user.

However, **capability leaking** happens when a program keeps *some* of its elevated powers after it should have lost them. If the program fails to remove these capabilities before changing its user ID, a spawned **child process** can inherit them. Then the child may perform restricted actions, even without root permissions, bypassing intended security measures.

1) Compile the program `cap_leak.c`, and make it a root-owned Set-UID program:
    (This program is designed to demonstrate how Set-UID works and the potential security risks involved.)
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void main()
{
  int fd;
  char *v[2];

  /* Assume that /etc/zzz is an important system file,
   * and it is owned by root with permission 0644.
   * Before running this program, you should create
   * the file /etc/zzz first. */
  fd = open("/etc/zzz", O_RDWR | O_APPEND);        
  if (fd == -1) {
     printf("Cannot open /etc/zzz\n");
     exit(0);
  }

  // Print out the file descriptor value
  printf("fd is %d\n", fd);

  // Permanently disable the privilege by making the
  // effective uid the same as the real uid
  setuid(getuid());                                

  // Execute /bin/sh
  v[0] = "/bin/sh"; v[1] = 0;
  execve(v[0], v, 0);                             
}
```
```bash
gcc -o cap_leak cap_leak.c
sudo chown root cap_leak
sudo chmod 4755 cap_leak
```
2) Create the file `/etc/zzz`:
```bash
sudo su #change to root
cd /etc #the file should be in /etc/ directory
nano zzz #write anything in it
exit #return to user
```

### Can you exploit the capability leaking vulnerability in this program? (The goal is to write to the /etc/zzz file as a normal user!)

3) Run the `./cap_leak` program:
```bash
./cap_leak
nano /etc/zzz
#you should be able to modify it
```
---
### How did that work? Let's explain in details:

| **Step**                     | **Description**        |
|------------------------------|------------------------|
| **1. Running the Program**   | Executed as `./cap_leak` by a normal user, the program starts with root privileges due to being owned by root and having the Set-UID bit. |
| **2. Opening a File**        | The program attempts to open `/etc/zzz`, succeeding because it has root privileges, allowing access to root-restricted files.       |
| **3. Changing Effective UID** | The program calls `setuid(getuid())`, changing its effective user ID to that of the normal user and losing root privileges for later actions. |
| **4. Executing a Shell**     | The program uses `execve()` to launch a new shell (`/bin/sh`) as a child process. The new shell may retain some elevated capabilities despite the original program losing root privileges. |
| **5. Shell Privileges**      | The child shell can execute commands and may still modify `/etc/zzz` due to potential capability leaking from the original program.  |


