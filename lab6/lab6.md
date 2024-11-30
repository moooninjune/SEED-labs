# Buffer Overflow Attack Lab (Server Version)

## Lab Environment Setup:
**Buffer overflow** is defined as the condition in which a program attempts to write data beyond the boundary of a buffer.

This vulnerability can be used by a malicious user to **alter the flow control of the program**, leading to the execution of malicious code.

- We need to make sure the **address randomization countermeasure** (a security feature that randomizes memory addresses used by a program) is turned off.
    ```bash
    sudo /sbin/sysctl -w kernel.randomize_va_space=0
    ```
---
**The Vulnerable Program:** [stack.c](/lab6/stack.c) has a buffer overflow vulnerability...

The program reads input (up to 517 bytes) from a remote user via a TCP connection, redirecting it to a buffer in the `bof()` function.
    
However, the buffer's size `BUF_SIZE` is smaller than 517 bytes, and since `strcpy()` doesn't enforce size limits, this creates a buffer overflow vulnerability. The program runs with root privileges, so exploiting this flaw could allow remote users to gain root access to the server.

- To compile the vulnerable program:

```bash
#gcc -DBUF_SIZE=$(L1): Sets the buffer size (using a variable L1) 
#-fno-stack-protector: Disables StackGuard, a gcc feature that prevents stack buffer overflows
#-z execstack: Makes the stack executable
gcc -DBUF_SIZE=$(L1) -o stack -z execstack -fno-stack-protector stack.c

#or just type `make` to run the commands specified in the Makefile
#`make install` copies the compiled binary into the `bof-containers` folder
make
make install
```

Here is the [`Makefile`](/lab6/Makefile) file. You can compile the [`server.c`](/lab6/server.c) code using different `BUF_SIZE` values in `Makefile`.

The server program `server.c` listens on port 9090 for TCP connections. When a connection is established, it runs the `stack.c` program and redirects the TCP connection as the `stdin` for `stack`. This allows `stack` to read data provided by the **remote client**.

---
### Docker & Compose:

```bash
$ docker-compose build # Build the container image
$ docker-compose up # Start the container
$ docker-compose down # Shut down the container

# Aliases for the Compose commands above
$ dcbuild # Alias for: docker-compose build
$ dcup # Alias for: docker-compose up
$ dcdown # Alias for: docker-compose down
```

All the containers will be running in the background. To run commands on a container, we often need to get a **shell** on that container.

```bash
dockps # Alias for: docker ps --format "{{.ID}} {{.Names}}"
docksh <id> # Alias for: docker exec -it <id> /bin/bash

# The following example shows how to get a shell inside hostC
dockps
b1004832e275 hostA-10.9.0.5
0af4ea7a3e2e hostB-10.9.0.6
9652715c8e0a hostC-10.9.0.7

docksh 96
root@9652715c8e0a:/#
```

## Task 2: Level-1 Attack: