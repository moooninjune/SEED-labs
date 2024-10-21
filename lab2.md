# Lab 2: MD5 Collision Attack Lab

## Task 1: Generating Two Different Files with the Same MD5 Hash:
> Hashing is about taking any input (like a file, message, or password) and converting it into a fixed-size string of characters, known as a hash value. It's used to ensure that data has not been altered during transmission. When the data is received or retrieved, the hash value is recalculated and compared to the original hash. If they match, the data is intact; if not, it has been altered.

#### A secure one-way hash function must satisfy two key properties:
1. **One-way property:**
   Given a hash value (h), it should be extremely difficult to find the original input (M) such that `hash(M) = h`.
3. **Collision-resistance property:**
   It should be computationally infeasible to find two different inputs (M1 and M2) that result in the same hash value `(hash(M1) = hash(M2))`.

