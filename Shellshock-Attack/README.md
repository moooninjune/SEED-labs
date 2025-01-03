# Shellshock Attack Lab

- **Bash:** A Unix shell that provides end users an interface to issue system commands and execute scripts.

- **Shellshock:** A vulnerability in Bash that allows remote code execution without confirmation. A series of random characters `() { :; };` confuses Bash because it doesn't know what to do with them, so by default, it executes the code after it.

- **The source of the issue is that** Bash can have internal function declaration in its environment variable.

- This [pdf file](https://www.exploit-db.com/docs/english/48112-the-shellshock-attack-%5Bpaper%5D.pdf?ref=benheater.com) can help you understand how shellshock attacks work.

- Here you can view the [tasks solutions & results](/Shellshock-Attack/Tasks.pdf) that I've done to solve this lab.
