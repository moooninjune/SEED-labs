## Task 3: Generating Two Executable Files with the Same MD5 Hash

- Your job is to create two different versions of a `C program`, such that the contents of their arrays are different, but the hash values of the executables are the same.
- This demonstrates an `MD5 collision`, where different inputs result in the same hash.

1. Write and Compile the C Program, using `nano` to write and `gcc` to compile.
```bash
nano array1.c
gcc array1.c -o array1
```

2. Fill the program’s array with fixed values like 0x41 (which is ASCII for letter A).

    (*we do this because it'll be easier to locate 200 A’s in the binary*)
```c
#include <stdio.h>
unsigned char xyz[200] = {
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"};

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

![Bless command output](https://github.com/moooninjune/SEED-Crypto-Lab/blob/ff93ab992f025efe9781d1648e18262bdb492e13/images/lab2-task3-bless.png)

> We found the total program size = 16992 (using `ls -l array1`),
> then where the array **starts at = 12320 (in decimal)** and **ends at = 12519**.
> We want to create a prefix & a suffix files to save all the content except the **128Bytes** from the middle of the array.

> So, the prefix will start from 0 to 12352 (from the beginning of the array & is a multiple of 64), and the suffix will start from 12480 (from the end of the array & keeping only 128Bytes in-between) to the end of the code.

4. Use the `head` & `tail` commands. Then use `md5collgen` on the prefix to generate two outputs that have the same MD5 hash value. Use `cat` to append.

> MD5 (prefix || P) = MD5 (prefix || Q)

> MD5 (prefix || P || suffix) = MD5 (prefix || Q || suffix)

```bash
head -c 12352 array1 > prefix

md5collgen -p prefix -o p q

tail -c +12480 array1 > suffix
# The numbers in head & tail are decimal !!

cat p suffix > new1
cat q suffix > new2

diff new1 new2
# they should differ

md5sum new1 new2
# they should have the same hash
```

![Output](https://github.com/moooninjune/SEED-Crypto-Lab/blob/37a15f4508fe12c82c8e70d0ea1cf657623fa8ee/images/lab2-task3-output.png)
