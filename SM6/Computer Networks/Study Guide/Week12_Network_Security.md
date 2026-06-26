# Computer Networks - Week 12: Network Security

---

## Secure Communication

There are certain desirable properties of secure communication:

- Confidentiality
- Message Integrity
- End-Point Authentication
- Operational Security

---

## 1. Confidentiality

Only the sender and intended receiver should be able to understand the contents of the transmitted message. This requires that the message is encrypted so that an intercepted message cannot be understood by an interceptor, enabling secure communication.

---

## 2. Message Integrity

The content of communication is not altered, either maliciously or by accident, in transit. Extensions to the checksumming techniques encountered in reliable transport and data link protocols can be used to provide such message integrity.

---

## 3. End-Point Authentication

Both the sender and receiver should be able to confirm the identity of the other party involved in the communication. For example, when a user wants to access an inbox, the mail server must verify that the user is the person he or she claims to be.

---

## 4. Operational Security

Almost all organizations (companies, universities, etc.) today have networks attached to the public Internet. Attackers can attempt to:

- Deposit worms into hosts in the network
- Obtain corporate secrets
- Map internal network configurations
- Launch DoS (Denial of Service) attacks

Operational devices such as firewalls and intrusion detection systems are used to counter attacks against an organization's network.

**Firewall:** Sits between the organization's network and the public network, controlling packet access to and from the network.

**Intrusion Detection System (IDS):** A monitoring system that detects suspicious activities and generates alerts for the network administrators about suspicious activity.

---

## Cryptography

Cryptographic techniques allow a sender to disguise data so that an intruder can gain no information from the intercepted data. The receiver must be able to recover the original data from the disguised data.

Cryptography has a long history dating back at least as far as Julius Caesar. Modern cryptographic techniques, including many of those used in the Internet, are based on advances made in the past 30 years.

### The Intruder Model (Alice, Bob, and Trudy)

Alice and Bob exchange control messages and data messages to ensure:

- Secure data exchange
- Confidentiality
- End-point authentication
- Message integrity

**Examples of scenarios:**
- A network user transferring a credit card number securely to a Web server to purchase an item online
- A user interacting with their bank online

**What an intruder (Trudy) can potentially perform:**
- Eavesdropping: sniffing and recording control and data messages on the channel
- Modification, insertion, or deletion of messages or message content

---

## Components of Cryptography

- **Plaintext (cleartext):** Alice's message in its original form
- **Encryption algorithm:** Takes the key and plaintext message as input, produces ciphertext as output
- **Ciphertext:** The encrypted message, which has no meaning for any intruder
- **Decryption algorithm:** Takes the ciphertext and the receiver's key as input, produces the original plaintext as output
- **Key:** A string of numbers or characters used as input to the encryption algorithm

The encryption technique itself is publicly known, standardized, and available to everyone, including a potential intruder. The secrecy lies in the key, not the algorithm.

### Notation

- `KA(m)` refers to the ciphertext form of the plaintext message `m`, encrypted using key `KA`
- Bob decrypts by computing: `KB(KA(m)) = m`

---

## Encryption and Decryption Types

### Symmetric Key Systems

- Sender and receiver's keys are identical and are secret
- Encrypted communication requires the two communicating parties to share a common key for encryption and decryption
- The two parties must somehow agree on the shared key through a secure communication channel
- In a networked world, communicating parties may never meet and may never converse except over the network, hence the need for encryption

### Public Key Systems (Asymmetric)

- A pair of keys is used
- One key is known to both sender and receiver (and indeed to the whole world): the **public key**
- The other key is known only by either the receiver or the sender (but not both): the **private key**

---

## Symmetric Key Cryptography

### Caesar Cipher

- A very old, very simple symmetric key algorithm attributed to Julius Caesar
- Works by taking each letter in the plaintext message and substituting the letter that is `k` letters later in the alphabet (with wraparound: after `z` comes `a`)
- The value of `k` serves as the key

**Example (k = 3):**
- `a` in plaintext becomes `d` in ciphertext
- `b` in plaintext becomes `e` in ciphertext, and so on

**Properties:**
- Only 25 possible shifts (shifting by 26 gives the original text)
- Easier to understand and implement
- Simple shifting rule (A->D, B->E, etc.)
- Pattern is predictable
- Easily broken by brute force

**Practice:**
Convert the following using Caesar cipher with k = 3:
> Your network is your net worth

---

### Monoalphabetic Cipher

An improvement on the Caesar cipher. It substitutes one letter of the alphabet with another letter of the alphabet. There is no need to have a regular pattern (e.g., substitution with an offset of k for all letters). Any letter can be substituted for any other letter, as long as each letter has a unique substitute letter, and vice versa.

**Example mapping:**

```
Plaintext letter:  a b c d e f g h i j k l m n o p q r s t u v w x y z
Ciphertext letter: m n b v c x z a s d f g h j k l p o i u y t r e w q
```

**Properties:**
- Better than the Caesar cipher
- There are 26! (on the order of 10^26) possible pairings of letters rather than only 25 possible pairings
- Practically impossible to brute-force manually
- More complex key management
- Each letter maps randomly (e.g., A->Q, B->M, C->Z...)
- No fixed pattern; harder to guess; requires deeper analysis
- A monoalphabetic cipher is not better but is definitely more secure and flexible than a Caesar cipher

**Rule:** In a monoalphabetic cipher, each letter must map to one fixed letter only.

---

### Comparison: Caesar vs Monoalphabetic

| Feature | Caesar Cipher | Monoalphabetic Cipher |
|---|---|---|
| Number of keys | 25 possible shifts | 26! (~4 x 10^26) possibilities |
| Pattern | Fixed shift for all letters | Random mapping per letter |
| Brute force resistance | Weak (easily broken) | Strong |
| Key management | Simple | More complex |
| Predictability | Highly predictable | Unpredictable |

---

### Example 1

- Plaintext: `HELLO`
- Caesar (shift +3): `KHOOR`
- Monoalphabetic (random mapping): `XQZZY`

Notice how the monoalphabetic output looks much less predictable.

---

### Example 2: Decrypting a Caesar Cipher

Ciphertext: `PHHW PH DIWHU FODVV`
Known to be encoded using a Caesar cipher.

Try shift -3:
- P -> M
- H -> E
- H -> E
- W -> T
- ...

**Plaintext: `MEET ME AFTER CLASS`**

---

### Example 3: Caesar Cipher (shift +2)

A school uses a Caesar cipher with a shift of +2 to send short messages.

Message sent: `QPNKPG ENCUU PQY`

Decryption table (using -2 shift):

| Letter | A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Cipher | Q | P | N | K | P | G | | E | N | C | U | U | | P | Q | Y | | | | | | | | | | |
| Decrypt | O | N | L | I | N | E | | C | L | A | S | S | | N | O | W | | | | | | | | | | |

**Decrypted message: `ONLINE CLASS NOW`**

**Limitation of Caesar cipher:** It has only 25 possible shifts, making it extremely vulnerable to brute-force attacks. An attacker can try all 25 shifts and quickly find the original message.

---

### Example 4: Verifying a Monoalphabetic Cipher

A student claims to have encrypted `SUCCESS` using a monoalphabetic cipher and obtained: `XABBCYX`

**Verify whether this is a valid monoalphabetic cipher:**

```
Plaintext:  S U C C E S S
Ciphertext: X A B B C Y X
```

Track mappings:
- S -> X
- S -> Y  **(INCONSISTENT)**

The same plaintext letter `S` maps to two different ciphertext letters (`X` and `Y`). This is a **violation** of the monoalphabetic cipher rule.

**Conclusion:** The ciphertext `XABBCYX` is NOT valid for a monoalphabetic cipher. In a monoalphabetic cipher, each letter must map to one fixed letter only.

---

## Vigenere Cipher

Introduces the idea of a keyword instead of a single shift. It is an improved version of the Caesar cipher.

- Uses a keyword to apply different shifts to different letters
- Caesar = same shift every time
- Vigenere = different shift per letter

**Letter-value mapping (A=0, B=1, ..., Z=25):**

| Letter | A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Value  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| 13| 14| 15| 16| 17| 18| 19| 20| 21| 22| 23| 24| 25|

### Encryption Formula

```
Ciphertext = (Plaintext value + Key value) mod 26
```

### Decryption Formula

```
Plaintext = (Ciphertext value - Key value) mod 26
```

---

### Example 5: Vigenere Cipher

**Plaintext:** `HELLO WORLD`
**Key:** `KEY` (K=10, E=4, Y=24) — repeated as needed: K E Y K E Y K E Y K

**Step 1 - Letter values:**

| Plain Text   | H | E | L  | L  | O  | W  | O  | R  | L  | D |
|---|---|---|---|---|---|---|---|---|---|---|
| Letter value | 7 | 4 | 11 | 11 | 14 | 22 | 14 | 17 | 11 | 3 |

**Step 2 - Apply Key:**

| Apply Key    | K  | E | Y  | K  | E | Y  | K  | E | Y  | K  |
|---|---|---|---|---|---|---|---|---|---|---|
| Key value    | 10 | 4 | 24 | 10 | 4 | 24 | 10 | 4 | 24 | 10 |

**Step 3 - Add and apply mod 26 (wrap around):**

| Add          | 17 | 8 | 35 | 21 | 18 | 46 | 24 | 21 | 35 | 13 |
|---|---|---|---|---|---|---|---|---|---|---|
| Wrap (mod 26)| 17 | 8 |  9 | 21 | 18 | 20 | 24 | 21 |  9 | 13 |
| **Cipher**   | **R** | **I** | **J** | **V** | **S** | **U** | **Y** | **V** | **J** | **N** |

**Result: `RIJVS UYVJN`**

---

### Limitations of Vigenere Cipher (Why it is not used in modern networks)

The Vigenere cipher is no longer used as a practical security mechanism in modern networks. It is mainly a historical and educational cipher useful for understanding how modern encryption evolved.

**Reasons it is not used:**
- Vulnerable to frequency analysis
- Too slow for digital systems
- Can be broken with statistical methods
- Does not support large-scale secure communication

In real systems such as banking networks, web traffic (HTTPS), and email security, it is not used at all.

---

## Modern Symmetric Encryption: AES

**AES (Advanced Encryption Standard)** is the most widely used encryption in modern networks.

- **Type:** Symmetric (one shared key)
- AES = a locked box with one shared key: sender locks, receiver unlocks with the same key

**Used in:**
- HTTPS web traffic (after connection is established)
- WhatsApp
- Banking transactions
- Cloud storage encryption
- Wi-Fi security

**Advantages:**
- Very fast
- Efficient for large data
- Strong security when the key is protected

---

## Asymmetric Encryption: RSA

RSA stands for **Rivest-Shamir-Adleman**, named after its creators Ron Rivest, Adi Shamir, and Leonard Adleman, who first described the algorithm in 1977.

- Public key cryptography
- Asymmetric encryption
- Foundation of secure communication on the internet
- Uses a **public key** (shared with everyone) for encryption
- Uses a separate **private key** (kept secret) for decryption
- The private key is mathematically linked to the public key but is impossible to derive from it in any practical time

**Used in:**
- HTTPS handshake (secure websites)
- Digital certificates
- Software authentication
- Secure email systems

**Analogy:**
- Public key = Locked mailbox slot: anyone can drop a message inside (encrypt)
- Private key = Only the owner can open the mailbox and read messages (decrypt)
- The lock is designed so that seeing the slot does NOT reveal how to open it
- Knowing the public key does NOT help you compute the private key due to computational hardness

---

## Hybrid Encryption: Real World Model

**Example: HTTPS (online banking / shopping)**

1. Browser connects to website
2. RSA is used to securely exchange a session key
3. AES is then used for all actual data encryption

This is called **hybrid encryption**.

Modern internet security does not rely on one algorithm. It combines:
- RSA for secure key exchange
- AES for fast data encryption

---

## Cyclic Redundancy Check (CRC)

CRC is one of the most popular error-checking schemes. It is a strong error-detecting code used in network protocols (like Ethernet) to detect data corruption during transmission.

**How it works:**
- A message is treated as one long binary number, which is divided by a preset number (the generator/divisor)
- The remainder is used as the CRC code

**Sender side:**
1. Append (L-1) zeros to the original message, where L is the length of the generator
2. Divide the padded message by the generator using XOR division
3. The remainder is the CRC
4. Append the CRC to the original data and transmit

**Receiver side:**
1. Divide the received message (data + CRC) by the same generator
2. If remainder = 0: no error detected
3. If remainder is not 0: error detected

In practice, the CRC algorithm is implemented using binary logic on a bit-by-bit basis to simplify memory requirements.

---

## Logical XOR

XOR is used in CRC instead of regular subtraction because:
- No borrowing
- Fast in hardware
- Easy to implement
- XOR = subtraction without carry/borrow

**XOR Truth Table:**

| A | B | A XOR B |
|---|---|---|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

- Same bits --> 0
- Different bits --> 1
- Called a **difference detector**

**Real applications of XOR:**
- CRC (error detection)
- Encryption (simple ciphers)
- Parity checking
- Digital circuits

---

### XOR Example 1

```
1011 XOR 1100 = ?

  1 0 1 1
  1 1 0 0
---------
  0 1 1 1

Answer: 0111
```

---

### XOR Example 2

```
1111 XOR 0101 = ?

  1 1 1 1
  0 1 0 1
---------
  1 0 1 0

Answer: 1010
```

Compare bits: same = 0, different = 1.

---

### CRC Example 3 (Sender and Receiver)

**Given:**
- Message to be sent: `1101011011`
- Preset generator/divisor: `10011`
- Length of generator: L = 5
- Bits to append: L - 1 = 4
- Data becomes: `11010110110000`

**Sender side (XOR division):**

Divide `11010110110000` by `10011`:

```
Divisor: 10011
Dividend: 11010110110000

Step 1: 11010 XOR 10011 = 01001 -> bring down 1 -> 10011
Step 2: 10011 XOR 10011 = 00000 -> bring down 1 -> 00001
Step 3: 00001 -> too small, bring down 1 -> 00011
Step 4: 00011 -> too small, bring down 0 -> 00110
Step 5: 00110 -> too small, bring down 0 -> 01100
Step 6: 01100 -> bring down 0 -> 11000 -> too small? no
         Actually continue XOR division...

Remainder: 1110
```

**CRC remainder = `1110`**

**Data sent = original data + CRC = `11010110111110`**

**Receiver side:**
- Divide `11010110111110` by `10011`
- Remainder = `00000` (zero)
- Conclusion: **No error detected**

---

### CRC Example 4

**Given:**
- Data: `101100`
- Generator/Divisor: `1101`
- Remainder at sender side: `111`

**Steps:**
1. Append 3 zeros (L-1 = 4-1 = 3): `101100000`
2. Divide by `1101` using XOR division
3. Remainder = `111`
4. Data sent = `101100` + `111` = `101100111`

**At receiver side:**
- Divide `101100111` by `1101`
- Remainder = `000`
- **No error detected**

---

### CRC Detection Capability

- The probability of detecting an error is 100% for all errors of the same length as the CRC or less
- Example: CRC-16 is guaranteed to detect errors if 16 or fewer bits are affected
- If the burst error is longer than the CRC, CRC is not perfect but is close to it:
  - CRC-16 detects about 99.998% of all burst errors longer than 16 bits
  - CRC-32 detects about 99.99999998% of all burst errors longer than 32 bits

---

## CRC Summary

CRC helps the receiver determine: "Did the data arrive correctly, or was it corrupted during transmission?"

**Sender:**
1. Calculates the CRC remainder
2. Appends it to the data
3. Sends both together

**Receiver:**
1. Performs the same CRC calculation
2. Checks the remainder
3. If remainder = 0: data assumed correct
4. If remainder is not 0: error detected

---

## Assignment / Practice (Ex-6)

**To be submitted (can work in pairs, submit one solution):**

Encrypt the following quote using the Vigenere cipher technique:

> A father gives nothing better than good education
> — Hazrat Muhammad PBUH

**Key:** `LEMON`

Use the letter-value table (A=0, B=1, ..., Z=25) and the formula:
```
Ciphertext = (Plaintext value + Key value) mod 26
```

---

## Book References

- Chapter 29, Douglas E. Comer
- Chapter 6, James W. Kurose
