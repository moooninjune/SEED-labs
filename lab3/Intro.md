# Lab 3: RSA Public-Key Encryption and Signature Lab

## RSA:

RSA is a **public-key** cryptosystem that is used for secure communication. The algorithm first generates two large random prime numbers, and then use them to generate public and private key pairs, which can be used to do **encryption, decryption, and digital signature generation and verification.**


![RSA-algorithm](https://github.com/moooninjune/SEED-Crypto-Lab/blob/dca52ec52a3bcfee12e9a5a7522003594a29bd5f/images/lab3-RSA-algorithm.png)

- **Encrypt** with Public Key, **Decrypt** with Private Key.
- **Sign** with Private Key, **Verify** with Public Key.

## BIGNUM APIs:
> We will be using the Big Number library provided by `openssl`, because RSA algorithm involves computations on large numbers and it cannot be directly conducted using simple arithmetic operators in programs.

All the big number APIs can be found from https://linux.die.net/man/3/bn.

**Let's explain some of the APIs that are needed for this lab:**

1. Createing a new context for BIGNUM operations in OpenSSL. This context is essential for efficiently managing **temporary** `BIGNUMs` used in various cryptographic computations.
```c
BN_CTX *ctx = BN_CTX_new()
```
2. Initialize a `BIGNUM` variable.
```c
BIGNUM *a = BN_new()
```
3. Assign a value to a `BIGNUM` variable.
```c
// Assign a value from a decimal number string
BN_dec2bn(&a, "12345678901112231223");

// Assign a value from a hex number string
BN_hex2bn(&a, "2A3B4C55FF77889AED3F");

// Generate a random number of 128 bits
BN_rand(a, 128, 0, 0);

// Generate a random prime number of 128 bits
BN_generate_prime_ex(a, 128, 1, NULL, NULL, NULL);
```
4. Print out a big number (We must write this function).
```c
void printBN(char *msg, BIGNUM * a)
{
// Convert the BIGNUM to number string
char * number_str = BN_bn2dec(a);

// Print out the number string
printf("%s %s\n", msg, number_str);

// Free the dynamically allocated memory
OPENSSL_free(number_str);
}
```
5. Compute `res = a − b` and `res = a + b`:
```c
BN_sub(res, a, b);
BN_add(res, a, b);
```
6. Compute `res = a ∗ b`:
```c
// Note that a BN_CTX structure is needed in this API
BN_mul(res, a, b, ctx)
```
7. Compute `res = a ∗ b mod n`:
```c
BN_mod_mul(res, a, b, n, ctx)
```

8. Compute `res = a^c mod n`:
```c
BN_mod_exp(res, a, c, n, ctx)
```

9. Compute modular inverse, i.e., given a, find b, such that `a ∗ b mod n = 1`. The value b is called the inverse of a, with respect to modular n.
```c
BN_mod_inverse(b, a, n, ctx);
```
10. After finishing the operations, it's important to use the functions meant for **deallocating memory**.
```c
// Used to free memory associated with a BN_CTX structure
BN_CTX_free(ctx)

// Used to free memory allocated for a BIGNUM structure
BN_clear_free(a)

// A general-purpose memory-freeing function used in OpenSSL
OPENSSL_free(number_str);
```

- We will also use the following command for **compilation**:
```bash
# the -lcyrpto tells the compiler to use the crypto library
gcc -o prog prog.c -lcrypto
```
