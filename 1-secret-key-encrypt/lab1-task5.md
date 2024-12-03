## Task 5: Error Propagation – Corrupted Cipher Text

1.	Create a text file that is at least 1000 bytes long.

2.	Encrypt the file using the AES-128 cipher.
```bash
openssl enc -aes-128-ecb -e -in longfile.txt -out ecb_enc -K 00112233445566778899aabbccddeeff
# only ECB doesn't need -iv
# repeat the process for different modes
```

3.	**A single bit of the 55th byte in the encrypted file got corrupted.** You can achieve this corruption using the hex editor `bless filename`.
    - just double click on the byte to change it.

4.	Decrypt the corrupted ciphertext file using the correct key and IV (SAME KEY).
```bash
openssl enc -aes-128-ecb -d -in ecb_enc -out ecb_dec -K 00112233445566778899aabbccddeeff
```

- How much information can you recover by decrypting the corrupted file, if the encryption mode is `ECB`, `CBC`, `CFB`, or `OFB`?

| Mode | Effect | Explanation |
| ---- | ------ | ----------- |
| ECB | ![ECB](https://github.com/moooninjune/SEED-Crypto-Lab/blob/4660286daf224061726c1baf2b272004662ad28b/images/lab1-task5-ecb.png) | **No error propagation**, only the block containing the corrupted byte is affected. The rest of the text remains intact. |
| CBC | ![CBC](https://github.com/moooninjune/SEED-Crypto-Lab/blob/4660286daf224061726c1baf2b272004662ad28b/images/lab1-task5-cbc.png) | The corrupted block and the following block become unreadable. This mode shows a more significant impact because of the chaining nature. |
| CFB | ![CFB](https://github.com/moooninjune/SEED-Crypto-Lab/blob/4660286daf224061726c1baf2b272004662ad28b/images/lab1-task5-cfb.png) | Like CBC, the corrupted byte affects both the corrupted block and the next blocks, leading to ***more*** distortion. |
| OFB | ![OFB](https://github.com/moooninjune/SEED-Crypto-Lab/blob/25ebdb246bb70ebca84cf0c7e326b3b2a809d3fe/images/lab1-task5-ofb.png) | **No error propagation**, only the block containing the corruption is affected, while subsequent blocks remain unaffected. |
