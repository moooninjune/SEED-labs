## Task 3: Encryption Mode – ECB vs. CBC

- Encrypt a `.bmp` picture using ECB (Electronic Code Book) & CBC (Cipher Block Chaining).
```bash
openssl enc -aes-128-ecb -e -in pic_original.bmp -out ecb_pic.bin -K 00112233445566778899aabbccddeeff

openssl enc -aes-128-ecb -e -in pic_original.bmp -out ecb_pic.bin -K 00112233445566778899aabbccddeeff -iv 0102030405060708
```
