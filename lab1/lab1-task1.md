# Lab 1: Secret-Key Encryption Lab

## Task 1: Frequency Analysis:
Given a ciphertext encrypted using a **monoalphabetic substitution cipher** *(each letter in the original text is replaced by another letter, where the replacement does not vary)*, find the original text using frequency analysis:
  1. Using the provided `freq.py` program, you’ll find the letters statistics.
     ```bash
     # don't forget to change the permission!
     chmod +x freq.py
     ./freq.py
     ```
    
  2. Make use of these: [Letters frequency](https://en.wikipedia.org/wiki/Frequency_analysis), [Bigram frequency](https://en.wikipedia.org/wiki/Bigram), [Trigram frequency](https://en.wikipedia.org/wiki/Trigram).
  
  3. Use the command `tr` to change the letters back to the original text.
     (We notice that *ytn* is probably *the*, and *vup* is probably *and*, and so on).
     ```bash
     tr 'ytn' 'THE' < ciphertext.txt > out.txt
     tr 'vup' 'AND' < ciphertext.txt > out1.txt
     ```
     *Remember that tr treats each character individually and not as a pair.
  
  4. Keep finding patterns until you get the final original text.


