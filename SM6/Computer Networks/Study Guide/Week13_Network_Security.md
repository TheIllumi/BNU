# Computer Networks - Week 13
## Network Security

---

## 1. CRC (Cyclic Redundancy Check)

CRC performs arithmetic using:

- Polynomial division
- Modulo-2 arithmetic
- XOR instead of subtraction

That is why CRC is also called **Polynomial code error detection**.

### Modulo-2 Arithmetic

- Works with only two digits: 0 and 1
- Important rule: There are no carries and no borrows

### CRC and Modulo-2 Arithmetic

- CRC performs polynomial division using XOR instead of subtraction
- In CRC:
  - Addition = XOR
  - Subtraction = XOR
- Modulo-2 arithmetic is simply XOR arithmetic

### CRC Example

**Polynomial form of binary data at the sender end:**

```
x^7 + x^6 + x^3 + 1
= 1.x^7 + 1.x^6 + 0 + 0 + 1.x^3 + 0 + 0 + 1.x^0
```

**Data in bits:** `11001001`

**Generator Polynomial:** x^3 + 1

**Generator in binary:** `1001`

---

## 2. Two-Dimensional Parity Check

### What It Is

An error-detection technique used in data communication. It extends the idea of simple parity (even/odd bits) into both rows and columns, making it more powerful for detecting errors.

### How It Works

1. **Arrange data in a grid (matrix)** — block of bits arranged in rows and columns
2. **Row parity (horizontal check)** — for each row, add an extra bit (parity bit) to ensure even (or odd) parity
3. **Column parity (vertical check)** — after adding row parity bits, compute parity for each column and add an extra row of parity bits

### Example — Original Data (4x4 grid)

```
1  0  1  1
0  1  0  1
1  1  0  0
0  0  1  1
```

### Using Even Parity — Add Row Parity

```
         Row Parity
1  0  1  1  |  1
0  1  0  1  |  0
1  1  0  0  |  0
0  0  1  1  |  0
```

Row parity bit makes the total number of 1s in each row even.

### Using Even Parity — Add Column Parity

```
              Row Parity
1  0  1  1  |  1
0  1  0  1  |  0
1  1  0  0  |  0
0  0  1  1  |  0
-----------
0  0  0  1  |  1   <- Col Parity
```

---

## 3. Error Detection Using 2D Parity Check

### Single-Bit Error

- One row parity and one column parity will fail
- Their intersection pinpoints the exact erroneous bit
- Can be corrected

### Multiple Errors

- Some may be detected, but not always corrected
- Certain patterns (e.g., errors forming a rectangle) may go undetected

---

## 4. Example 1 (Ex-1)

### Original Data

```
1  0  1  1
0  1  0  1
1  1  1  0
0  0  1  0
```

### Using Even Parity — Row Parity

```
         Row Parity
1  0  1  1  |  1
0  1  0  1  |  0
1  1  1  0  |  1
0  0  1  0  |  1
```

### Using Even Parity — Column Parity

```
              Row Parity
1  0  1  1  |  1
0  1  0  1  |  0
1  1  1  0  |  1
0  0  1  0  |  1
-----------
0  0  1  0  |  1   <- Col Parity
```

**Data Transmitted (row by row, including parity bits):**

```
1 0 1 1 1 | 0 1 0 1 0 | 1 1 1 0 1 | 0 0 1 0 1 | 0 0 1 0 1
```

### Single-Bit Error Scenario

Suppose one bit changes accidentally:
- Third row, second column changes from 1 to 0
- Received data becomes corrupted at that position

**Error detection process:**

- Row 3 parity check fails — indicates an error in row 3
- Column 2 parity check fails — indicates an error in column 2
- Their intersection identifies the corrupted bit
- The receiver knows exactly which bit is wrong (the bit at row 3, col 2 is 0 but should be 1)
- The incorrect bit is corrected back to 1

---

## 5. Advantages and Limitations of 2D Parity Check

### Advantages

- Detects all single-bit errors
- Identifies the exact wrong bit
- Corrects single-bit errors automatically
- Stronger than simple one-dimensional parity checking
- Simple to implement

### Limitations

- Cannot reliably detect all multiple-bit errors
- Adds extra redundancy (overhead)

---

## 6. Applications of Two-Dimensional Parity Check

- Serial communication systems
- Wireless sensor devices
- Low-cost embedded systems
- RAM modules
- Cache memory
- RAID systems — parity information is spread across disks; if one disk fails, parity helps recover data
- Servers and banks also use advanced versions of this technique

---

## 7. Modern Networks

Modern networks use stronger error detection techniques such as:

- **CRC (Cyclic Redundancy Check)**
- **Checksum**

These detect burst errors much better than parity methods.

---

## 8. Types of Errors (Visual Representation)

### Single-Bit Error

In a frame, only one bit anywhere is corrupt.

```
Sent:      1 0 1 1 0 0 1 1
Received:  1 0 1 1 0 [1] 1 1   <- one bit flipped
```

### Multiple-Bit Error

Frame is received with more than one bit in a corrupted state.

```
Sent:      1 0 1 1 0 0 1 1
Received:  1 0 1 [0] [0] 1 1 1   <- two bits flipped
```

### Burst Error

Frame contains more than 1 consecutive bits corrupted.

```
Sent:      1 0 1 1 0 0 1 1
Received:  1 [1 0 0 0] 1 1 1   <- consecutive bits flipped
```

---

## 9. Message Authentication

Message authentication addresses two concerns:

- **Data Integrity** — ensuring that data arriving at the destination is in its original form
- **Source Authentication** — ensuring that data is coming from an authentic source

### Requirements of Message Authentication

- No modification
- No insertion
- No deletion
- No replay

### Replay Attack

A replay attack occurs when transmitted authentication or access control information is intercepted and then re-transmitted to either produce an unauthorized effect or gain unauthorized access.

**Example:** In the story of Ali Baba and the Forty Thieves, the robber captain utters "Open Sesame!" to gain entrance to the cave. After overhearing the phrase, Ali Baba reuses it to open the doorway himself — this is essentially a replay attack.

Reference: https://www.comparitech.com/blog/information-security/what-is-a-replay-attack/

---

## 10. Cryptographic Hash Functions

### Applications

- Message authentication
- Digital signature
- Other applications (Internet protocols)

### What Is a Hash Function?

- A hash function maps a message of arbitrary length to a fixed m-bit output
- The output is known as the **fingerprint** or **message digest**
- Even a tiny change in input produces a completely different hash
- Same input always gives the same hash

**Formula:** `h = H(M)`

Where:
- H = hash function
- M = input message (variable length)
- h = hash value / message digest

**h acts as an authenticator.**

### Popular Hash Functions

| Hash Function | Output Length |
|---|---|
| SHA-256 | 256 bits |
| MD5 | 128 bits |
| Bcrypt | Variable |
| RIPEMD | 160 bits |

---

## 11. One-Way Hash Functions

- Given an input, it is easy to compute the output
- It is practically impossible to reverse-engineer a hash output and derive the original input
- Hence a hash function is also called a **one-way function**
- You cannot use hashing for encryption and decryption — decryption is impossible due to the one-way nature

### Use of Hash Output

- A hash output is useful to represent an input — it is called a **fingerprint**
- Useful for ensuring data is not tampered or corrupted when travelling across a network
- The hash of "sent data" should always equal the hash of "received data"
- Comparison of data is the most common use of hashing

---

## 12. Message Authentication Methods

### Method 1 — Using Symmetric Encryption

- The message digest is encrypted using a symmetric encryption key
- Authenticity is assured by the assumption that only the sender and receiver share the encryption key

**Process:**

```
Source A:
  Message --> H --> hash
  hash --> E (encrypt with key K) --> encrypted hash
  Message + encrypted hash --> transmitted

Destination B:
  Received Message --> H --> hash_new
  encrypted hash --> D (decrypt with key K) --> hash_orig
  Compare hash_new with hash_orig
```

### Method 2 — Using Public Key Encryption

- The message digest can also be encrypted using public key encryption
- Provides message authentication
- Does not require the distribution of shared keys to communicating parties

**Process:**

```
Source A:
  Message --> H --> hash
  hash --> E (encrypt with sender's private key PR_a) --> encrypted hash
  Message + encrypted hash --> transmitted

Destination B:
  Received Message --> H --> hash_new
  encrypted hash --> D (decrypt with sender's public key PU_a) --> hash_orig
  Compare hash_new with hash_orig
```

---

## 13. Digital Signatures

### The Problem

- In real life, signatures on contracts and credit card bills provide **non-repudiation** — a party cannot deny having signed something
- The question is: can we achieve the same in the electronic world?
- Note: Message Authentication Code (MAC) does NOT provide non-repudiation because both sender and receiver share the same key — either party could have generated the MAC

### Non-Repudiation

A common example in cybersecurity occurs in e-commerce: when a customer makes an online purchase and signs off using their private key (via digital signature), they cannot later claim that they did not authorize the transaction.

### MAC vs Digital Signature

| | MAC | Digital Signature |
|---|---|---|
| Generation | One party | One party |
| Verification | One party | Many parties |
| Non-repudiation | No | Yes |

### Digital Signature Definition

A **digital signature** is a data string which associates a message with some originating entity.

### Digital Signature Scheme

1. **Signing algorithm** — takes a message and a private signing key, outputs a signature
2. **Verification algorithm** — takes a public verification key, a message, and a signature

### Properties Provided

- Authentication
- Data integrity
- Non-repudiation

---

## 14. Digital Signatures and Hash Functions

- Digital signatures are very often used with hash functions
- The hash of a message is signed, instead of the message itself

### Requirements for the Hash Function Used

The hash function must be:

- **Pre-image resistant** — given a hash h, it is computationally infeasible to find any input M such that H(M) = h
- **Weak collision resistant** — given an input M, it is computationally infeasible to find a different input M' such that H(M) = H(M')
- **Strong collision resistant** — it is computationally infeasible to find any two different inputs M and M' such that H(M) = H(M')

---

## Book References

- Chapter 29 — Douglas E. Comer
- Chapter 6 — James W. Kurose
