# Cryptography Ciphers Program

## Overview

This C program implements a collection of 13 classical cryptography ciphers, allowing users to encrypt text through a console-based interface. The ciphers included are Atbash, Caesar, August, Affine, Vigenere, Gronsfeld, Beaufort, Autokey, Running Key, Hill, Rail Fence, Route, and Myszkowski. The program provides a menu-driven interface for selecting a cipher, inputting text, and specifying keys or parameters as needed.

## Features

- Implements 13 distinct ciphers, each with unique encryption mechanisms.
- Supports case-sensitive text input, preserving the case of letters in the output.
- Handles non-alphabetic characters by leaving them unchanged in the output.
- Includes input validation for ciphers requiring specific parameters (e.g., coprime keys for Affine and Hill ciphers).
- Provides a simple console menu for selecting and applying ciphers.

## Ciphers Included

1. Atbash: A substitution cipher that reverses the alphabet (A to Z, B to Y, etc.).
2. Caesar: Shifts each letter by a fixed number of positions (default shift of 3).
3. August: A special case of the Caesar cipher with a shift of 1.
4. Affine: Uses a linear transformation (ax + b mod 26) with keys a and b, where a is coprime with 26.
5. Vigenere: A polygraphic substitution cipher using a keyword to determine shifts.
6. Gronsfeld: Similar to Vigenere but uses a numeric key for shifts.
7. Beaufort: A reciprocal cipher using a keyword, where the key letter determines the shift.
8. Autokey: Extends the Vigenere cipher by appending the plaintext to the key.
9. Running Key: Uses a long key (e.g., a book passage) to shift letters, matching the plaintext length.
10. Hill: A matrix-based cipher using a 2x2 key matrix for linear transformations.
11. Rail Fence: A transposition cipher arranging letters in a zigzag pattern across rails.
12. Route: Arranges text in a grid and reads it in a spiral pattern.
13. Myszkowski: A columnar transposition cipher with columns ordered by a keyword.

## Acknowledgments

This program is designed for educational purposes, implementing classical ciphers as described in cryptographic literature.
