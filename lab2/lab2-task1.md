# Lab 2: MD5 Collision Attack Lab

## Task 1: Generating Two Different Files with the Same MD5 Hash:
> **Hashing** is about taking any input (like a file or a message) and converting it into a fixed-size string of characters, known as a hash value.
> Used to ensure that data has not been altered during transmission. When the data is received or retrieved, the hash value is **recalculated and compared to the original hash**. If they match, the data is intact; if not, it has been altered.

**A secure one-way hash function must satisfy two key properties:**
   1. **One-way property:**
   
      Given a hash value (h), it should be extremely difficult to find the original input (M) such that `hash(M) = h`.
   2. **Collision-resistance property:**
   
      It should be computationally infeasible to find two different inputs (M1 and M2) that result in the same hash value `(hash(M1) = hash(M2))`.
      

> **MD5 (Message-Digest Algorithm 5)** is a hashing algorithm that takes an **input** in blocks of `512 bits (or 64 bytes)` and produces an **output**: `128-bit hash value`. It’s unsuitable for secure applications; better alternative is *SHA-256*.

```bash
echo "Make any prefix file you want" > prefix.txt

md5collgen -p prefix.txt -o out1.bin out2.bin

diff out1.bin out2.bin
# they should differ

md5sum out1.bin
md5sum out2.bin
# they should have the same hash value even though they differ in content
```
