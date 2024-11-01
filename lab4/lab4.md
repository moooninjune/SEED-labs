# Environment Variable and Set-UID Program Lab

## What are Environment variables?
Environment variables are a set of **dynamic named values** that can affect the way running processes will behave on a computer.

If a program uses environment variables, but
the programmer does not know that they are used, the program may have vulnerabilities.

## How environment variables affect the behavior of Set-UID programs?
Set-UID are privileged programs. It's an important security mechanism in Unix.

When a Set-UID program runs, it assumes the owner's privileges. For example, if the program's owner is root, then when anyone runs this program, the program gains the root's privileges during its execution.