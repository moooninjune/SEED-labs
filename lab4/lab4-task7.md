## Task 7: The LD_PRELOAD Environment Variable and Set-UID Programs:
A **dynamic loader/linker** is the part of an operating system that loads (from storage to RAM) and links the shared libraries needed by an executable at run time.

In Linux, `ld.so` or `ld-linux.so` are the dynamic loaders that handle loading shared libraries. **Two key environment variables affect this process:**
| Variable | Purpose |
| -------- | --------- |
| `LD_LIBRARY_PATH` | Specifies a list of directories that the dynamic linker should search first when looking for shared libraries before the default paths. |
| `LD_PRELOAD` | Forces the dynamic linker to load specific user-specified libraries before any others, regardless of where they are. |

### How do these environment variables influence the behavior of dynamic loader/linker when running... :

1) As a regular program, normal user:
    - Create and compile `mylib.c`:
    ```c
    #include <stdio.h>
    void sleep (int s)
    {
        /* If this is invoked by a privileged program, you can do damages here! */
        printf("I am not sleeping!\n");
    }
    ```
    ```bash
    gcc -fPIC -g -c mylib.c
    gcc -shared -o libmylib.so.1.0.1 mylib.o -lc
    ```
    - Set the `LD_PRELOAD` environment variable:
    ```bash
    export LD_PRELOAD=./libmylib.so.1.0.1
    ```
    - Compile `myprog.c` too:
    ```c
    /* myprog.c */
    #include <unistd.h>
    int main()
    {
        sleep(1);
        return 0;
    }
    ```
    ```bash
    gcc -o myprog myprog.c
    ```
    - Now run the program `./myprog` as a normal program:
    ```bash
    # output
    I am not sleeping!
    ```

2) As a **Set-UID** root program, normal user:
```bash
sudo chown root myprog
sudo chmod 4755 myprog
./myprog
#it won't print (I am not sleeping!)
#bc it's actually sleep :(
```
3) As a **Set-UID** root program, root user:
```bash
sudo su 
#when you run `sudo su` without specifying a user, it defaults to switching to the root user

export LD_PRELOAD=./libmylib.so.1.0.1

./myprog
#I am not sleeping!
exit
#to return from root
```

4) As a **Set-UID** user1 program, another (non-root,non-user1) normal user:
```bash
#No need to actually add user user1, just type:
sudo chown user1 ./myprog.out
#if you want to add a user:
sudo adduser user1

sudo chown user1 myprog
sudo chmod 4755 myprog
export LD_PRELOAD=./libmylib.so.1.0.1

./prog
#it won't print (I am not sleeping!)
#bc it's actually sleep :(
```
---
### Observation:
When `myprog` runs, it uses the environment (including `LD_PRELOAD`) of its owner, not the user who executed it.

Setting `LD_PRELOAD` can modify the behavior of `myprog`, but this only applies if the environment of the owner allows it.

| Scenario                                      | Output                | Explanation                                                                           |
|-----------------------------------------------|-----------------------|---------------------------------------------------------------------------------------|
| Regular Program, Normal User                  | I am not sleeping!    | The program uses the caller's environment, including `LD_PRELOAD`.                  |
| Set-UID Root Program, Normal User             | actually sleep        | The program executes the standard `sleep` function since it ignores `LD_PRELOAD`.   |
| Set-UID Root Program, Root User               | I am not sleeping!    | The root user’s environment is respected, allowing the custom `sleep` from `LD_PRELOAD` to execute. |
| Set-UID User1 Program, Non-root, Non-user1 Normal User | actually sleep        | Similar to the Set-UID root scenario, it runs in the owner (user1) environment, ignoring the caller's `LD_PRELOAD`. |

- **Caller:** This refers to the user who executes (calls) the program at runtime. For example, if User A runs a program, User A is the caller.
