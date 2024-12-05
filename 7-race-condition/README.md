# Race Condition Vulnerability Lab

**A race condition occurs when** multiple processes access and manipulate the same data concurrently, and the outcome of the execution depends on the particular order in which the access takes place.

 If a privileged program has a race-condition vulnerability, attackers can run a parallel process to “race” against the privileged program, with an intention to change the behaviors of the program.

 ## Environment Setup

 1. **Turning Off Countermeasures:**

    ```bash
    #On Ubuntu 20.04, use the following:
    sudo sysctl -w fs.protected_symlinks=0
    sudo sysctl fs.protected_regular=0
    ```
---
 2. **The Vulnerable Program:** contains a race-condition vulnerability.

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    int main()
    {
        char* fn = "/tmp/XYZ";
        char buffer[60];
        FILE* fp;

        /* get user input */
        scanf("%50s", buffer);

        if (!access(fn, W_OK)) {
            fp = fopen(fn, "a+");
            if (!fp) {
                perror("Open failed");
                exit(1);
            }
            fwrite("\n", sizeof(char), 1, fp);
            fwrite(buffer, sizeof(char), strlen(buffer), fp);
            fclose(fp);
        } else {
            printf("No permission \n");
        }

        return 0;
    }
    ```

- This program is a **root-owned Set-UID program** that appends a string of user input to the end of a temporary file `/tmp/XYZ`.

- Since the code runs with root privileges (effective user ID is zero), it can overwrite any file. To prevent accidentally overwriting other people's files, the program first checks whether the real user ID has access permission to the file `/tmp/XYZ` using the `access()` call. If the real user ID has the right, the program opens the file and appends the user input to it.

- However, there is a **race condition vulnerability** in this program. Due to the time window between the check `access()` and the use `fopen()`, there is a possibility that the file used by `access()` is different from the file used by `fopen()`, even though they have the same file name `/tmp/XYZ`.

- If a malicious attacker can make `/tmp/XYZ` a **symbolic link** pointing to a protected file, such as `/etc/passwd`, inside the time window, the attacker can cause the user input to be appended to `/etc/passwd`, thus gaining root privileges. The vulnerable program runs with root privileges, so it can overwrite any file.
---
3. **Compile & Set up the Set-UID program:**

    ```bash
    gcc vulp.c -o vulp
    sudo chown root vulp
    sudo chmod 4755 vulp
    ```
---
## Task 1: Choosing Our Target

 We would like to exploit the **race condition vulnerability** by targeting  the password file `/etc/passwd`, which is not writable by normal users. This file stores information about all user accounts on the system, like usernames, passwords (or where to find them), and user privileges.

By exploiting the vulnerability, we would like to add a record to the password file, with a goal of creating a **new user account that has the root privilege**.

---

Inside the password file, each user has an entry, which consists of seven fields separated by colons (:). **The entry for the root user is:**
```
root:x:0:0:root:/root:/bin/bash
```
- First field `root`: Username.

- Second field `x`: Password field indicates that the hashed password is stored in `/etc/shadow`.

    - The password field does not hold the actual password; it holds the one-way hash value of the password.

    -  Instead of putting `x` in the password file, we can simply put the password there, so the operating system will not look for the password from the `/etc/shadow`, and will read it directly from `/etc/passwd`.

- Third field `0`: User ID (UID). A UID of `0` means root privileges.

- Fourth field `0`: Group ID (GID).
---

**Choose the password:** This value can be used as the second field in the new user entry.

1. Option 1: Generate a password hash using the `adduser` command on a system you control, and copy the hash from `/etc/shadow`.

2. Option 2: Use a known hash for a password-less login. In Ubuntu, the hash `U6aMy0wojraho` allows login without a password. 
    ```
    test:U6aMy0wojraho:0:0:test:/root:/bin/bash
    ```
---
