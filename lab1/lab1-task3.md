## Task 3: Encryption Mode – ECB vs. CBC

- Encrypt a `.bmp` picture using ECB (Electronic Code Book) & CBC (Cipher Block Chaining).
```bash
openssl enc -aes-128-ecb -e -in pic_original.bmp -out ecb_pic.bin -K 00112233445566778899aabbccddeeff

openssl enc -aes-128-ecb -e -in pic_original.bmp -out ecb_pic.bin -K 00112233445566778899aabbccddeeff -iv 0102030405060708
```

- Get the **header** (for the .bmp file, the first 54 bytes contain the header info.) from the original picture to the encrypted picture.
- Then the **data** from the original picture (from offset 55 to the end of the file).
- Then **combine** the header and data together into the new encrypted file.
```bash
head -c 54 pic_original.bmp > header

tail -c +55 ecb_pic.bin > ecb_body
cat header ecb_body > ecb_new.bmp

tail -c +55 cbc_pic.bin > cbc_body
cat header cbc_body > cbc_new.bmp
```

- Display the encrypted picture using the picture viewing program `eog filename`.

![Encrypted Picture using ECB](/images/Picture1.png)
