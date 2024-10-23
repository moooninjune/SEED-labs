## Task 2: Encryption using Different Ciphers and Modes:

1. Create any plaintext file using `echo` or `cat`.
```bash
echo "I'm a plaintext file! Encrypt me using different modes!" > plaintext.txt
```
2. Encrypt using the command `openssl enc -ciphertype`.
```bash
openssl enc -aes-128-cbc -e -in plaintext.txt -out cipher1.bin -K 00112233445566778899aabbccddeeff -iv 0102030405060708

openssl enc -aes-128-cfb -e -in plaintext.txt -out cipher2.bin -K 00112233445566778899aabbccddeeff -iv 0102030405060708

openssl enc -bf-cbc -e -in plaintext.txt -out cipher3.bin -K 00112233445566778899aabbccddeeff -iv 0102030405060708
```
