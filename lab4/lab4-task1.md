# Environment Variable and Set-UID Program Lab

## Task 1: Manipulating Environment Variables:
Environment variables are a set of **dynamic named values** that can affect the way running processes will behave on a computer.

- **Example:** $PATH, $HOME, $PWD, $USER, $SHELL, etc...

- Environment variable names are typically written in all **uppercase**.

### How Environment Variables Are Set and Accessed:
1) Setting an environment variable (with a value):
```bash
export VAR_NAME=value
export VAR_NAME="string with spaces"

#Unsetting an environment variable:
unset VAR_NAME
```
2) Viewing all environment variables (list all the current environment variables):
```bash
printenv #all
printenv PWD #for specific search
echo $PWD #same result as above

#Or use the `env` command
env #all
env | grep PWD #for specific search
```