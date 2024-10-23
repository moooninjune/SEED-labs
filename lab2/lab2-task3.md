## Task 3: Generating Two Executable Files with the Same MD5 Hash

- Your job is to create two different versions of a `C program`, such that the contents of their xyz arrays are different, but the hash values of the executables are the same.
- This demonstrates an `MD5 collision`, where different inputs result in the same hash.

1. Write and Compile the C Program, using `nano` to write and `gcc` to compile.
```bash
nano array1.c
gcc array1.c -o array1
```

2. Fill the program’s array with fixed values like 0x41 (which is ASCII for letter A).

3. We want to divide the executable file *into three parts:* a prefix (must be multiple of 64 bytes), a 128-byte region, and a suffix. Use the hex editor `bless` to determine the position where the array begins and ends.
```bash
ls -l array1
-rwxrwxr-x 1 seed seed 16992 Oct 19 07:18 array1
# this shows the total program size = 16992
```
