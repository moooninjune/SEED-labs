## Task 3: Generating Two Executable Files with the Same MD5 Hash

- Your job is to create two different versions of a `C program`, such that the contents of their xyz arrays are different, but the hash values of the executables are the same.
- This demonstrates an `MD5 collision`, where different inputs result in the same hash.

1. Write and Compile the C Program, using `nano` to write and `gcc` to compile.
```bash
nano array1.c
gcc array1.c -o array1
```

2. Fill the program’s array with fixed values like 0x41 (which is ASCII for letter A).
```c
#include <stdio.h>
unsigned char xyz[200] = {
/* The actual contents of this array are up to you */
};
int main()
{
int i;
for (i=0; i<200; i++){
printf("%x", xyz[i]);
}
printf("\n");
}
```

3. We want to divide the executable file into three parts: a *prefix* (must be multiple of 64 bytes), a *128-byte* region, and a *suffix*. Use the hex editor `bless` to determine the position where the array begins and ends.
```bash
ls -l array1
-rwxrwxr-x 1 seed seed 16992 Oct 19 07:18 array1
# this shows the total program size = 16992
```

4. Use the `head` & `tail` commands. Then use `md5collgen` on the prefix to generate two outputs that have the same MD5 hash value. Extract the `128B` from each output so we could use it to replace the 128B in the original program. Use `cat` to append.

> MD5 (prefix || P) = MD5 (prefix || Q)

> MD5 (prefix || P || suffix) = MD5 (prefix || Q || suffix)

```bash
head -c 12352 array1 > prefix

md5collgen -p prefix -o out1 out2

tail -c +12480 array1 > suffix
tail -c 128 out1 > p
tail -c 128 out2 > q

cat p suffix > new1
cat q suffix > new2

diff new1 new2
# they should differ

md5sum new1 new2
# they should have the same hash
```
