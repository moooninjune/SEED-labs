## Task 4: Padding

### Revision:

- You select a cipher type (e.g., AES), and then choose a mode of operation (e.g., CFB, ECB, CBC) based on the security requirements.

- For block ciphers, when the size of a plaintext is not a multiple of the block size, *padding* may be required.

| Concept | 1 | 2 |
| ------- | ---------- | -------- |
| **Key ( -K ):** A secret value used to encrypt and decrypt data | `AES length`: 128, 192, or 256 bits (16, 24, or 32 bytes) | `DES length`: 56 bits (8 bytes) |
| **Initialization Vector ( -iv ):** A random value used to ensure that identical plaintexts encrypt to different ciphertexts | `AES`: 128 bits (16 bytes) | `DES`: 64 bits (8 bytes) |
| **Modes of Operation** | **Modes that require padding:** `ECB`, `CBC` (Fixed-size blocks) | **Modes that don’t require padding:** `CFB`, `OFB` (Stream-like) |

> Hexadecimal Representation: Each pair of hex digits represents one byte.
> 
> Example: 112233445566 → 6 bytes: 11, 22, 33, 44, 55, 66 (total 6 pairs)

1. Use ECB, CBC, CFB, and OFB modes to encrypt 3 files (you can pick any cipher).
```bash
echo -n "12345" > f1.txt # 5 bytes
echo -n "1234567890" > f2.txt # 10 bytes
echo -n "1234567890123456" > f3.txt # 16 bytes

openssl enc -aes-128-cbc -e -in f1.txt -out f1.enc -K 00112233445566778899aabbccddeeff -iv 0102030405060708
openssl enc -aes-128-cbc -e -in f2.txt -out f2.enc -K 00112233445566778899aabbccddeeff -iv 0102030405060708
openssl enc -aes-128-cbc -e -in f2.txt -out f2.enc -K 00112233445566778899aabbccddeeff -iv 0102030405060708
# repeat the process for the other modes ECB, CFB, OFB
```

2. To inspect the padding, we decrypt using `openssl enc` *(you must use the option `-nopad` because decryption removes the padding by default).*
```bash
openssl enc -aes-128-cbc -d -in f1.enc -out f1_dec.txt -nopad -K 00112233445566778899aabbccddeeff -iv 0102030405060708
```

3. You can then use a hex tool `hexdump -C` to view the contents of the decrypted files.
