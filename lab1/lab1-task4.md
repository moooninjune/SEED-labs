## Task 4: Padding

#### Revision
| Concept | Info. |
| ------- | ---------- |
| Key ( -K ): A secret value used to encrypt and decrypt data | AES length: 128, 192, or 256 bits (16, 24, or 32 bytes) |
| | DES length: 56 bits (8 bytes) |
| Initialization Vector ( -iv ): A random value used to ensure that identical plaintexts encrypt to different ciphertexts **(Each time you encrypt the same message, you want it to look different**) | AES: 128 bits (16 bytes) |
| | DES: 64 bits (8 bytes) |
| Modes of Operation | Modes that require padding: ECB, CBC. Operate on fixed-size blocks
(e.g., 128 bits for AES) |
| | Modes that don’t require padding: CFB, OFB. Stream-like and don’t need paddings |
