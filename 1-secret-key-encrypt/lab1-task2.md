## Task 2: Encryption using Different Ciphers and Modes:

1. Create any plaintext file using `echo` or `cat`.
```bash
echo "I'm a plaintext file! Encrypt me using different modes!" > plaintext.txt
```

2. Encrypt using different ciphers and modes with the command `openssl enc -ciphertype`.
```bash
openssl enc -aes-128-cbc -e -in plaintext.txt -out cipher1.bin -K 00112233445566778899aabbccddeeff -iv 0102030405060708

openssl enc -aes-128-cfb -e -in plaintext.txt -out cipher2.bin -K 00112233445566778899aabbccddeeff -iv 0102030405060708

openssl enc -bf-cbc -e -in plaintext.txt -out cipher3.bin -K 00112233445566778899aabbccddeeff -iv 0102030405060708
```

3. Then, decrypt each ciphertext to make sure it'll give the same old plaintext.
```bash
openssl enc -aes-128-cbc -d -in cipher1.bin -out cipher1.txt -K 00112233445566778899aabbccddeeff -iv 0102030405060708

#the same for the rest...
```
```bash
diff plaintext.txt cipher1.txt
diff plaintext.txt cipher2.txt
diff plaintext.txt cipher3.txt

#there shouldn't be any difference!
```

### NOTES:
| Option | Meaning |
| ------ | ------ |
| -in file | input file |
| -out file | output file |
| -e | encrypt |
| -d | decrypt |
| -K/-iv | key/iv in hex is the next argument *(K is capital letter)* |
| -[pP] | print the iv/key (then exit if -P) |



