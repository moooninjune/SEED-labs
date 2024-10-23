## Task 2: Generating Two Different Files with the Same MD5 Hash:
> if `MD5(M) = MD5(N)`, i.e., the MD5 hashes of M and N are the same, then for any input T, `MD5(M || T) = MD5(N || T)`, where || represents concatenation (joining).

1.	Generate two different files that have the same MD5 hash value.
```bash
md5collgen -p prefix.txt -o out1.bin out2.bin
```
2.	Create a Suffix File (T) with any data. Concatenate the Files with the Suffix. This will create two new files: Calculate the MD5 Hashes of the Output Files.
```bash
echo "I'm the suffix file!" > suffix.txt
cat out1.bin suffix.txt > new1.bin
cat out2.bin suffix.txt > new2.bin
```
3.	We find out that if inputs M and N have the same hash, adding the same suffix T to them will result in two outputs that have the same hash value.
```bash
md5sum new1.bin new2.bin
#they should have the same hash value
```
