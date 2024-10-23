## Task 4: Padding

#### Revision
| ------- | ---------- | -------- |
| Key ( -K ): A secret value used to encrypt and decrypt data | AES length: 128, 192, or 256 bits (16, 24, or 32 bytes) | DES length: 56 bits (8 bytes) |
| Initialization Vector ( -iv ): A random value used to ensure that identical plaintexts encrypt to different ciphertexts **(Each time you encrypt the same message, you want it to look different**) | AES: 128 bits (16 bytes) | DES: 64 bits (8 bytes) |
| Modes of Operation | Modes that require padding: ECB, CBC. Operate on fixed-size blocks (e.g., 128 bits for AES) | Modes that don’t require padding: CFB, OFB. Stream-like and don’t need paddings |

> Hexadecimal Representation: Each pair of hex digits represents one byte.
> - Example: 112233445566 → 6 bytes: 11, 22, 33, 44, 55, 66 (total 6 pairs)

> You select a cipher type (e.g., AES) and then choose a mode of operation (e.g., CFB, ECB, CBC) based on the security requirements and the nature of your data.
