# Computer Networks - Week 14: Network Security

---

## Applications of Hashing

Hashing is mainly used for:

- Integrity checking
- Password storage
- Digital signatures
- Blockchain

> Hashing -> Integrity achieved
> Encryption -> Confidentiality achieved

### Password Storage

- Websites do not store actual passwords.
- Instead, the password is converted to a hash and stored.
- During login, the entered password is hashed again and compared with the stored hash.

### Blockchain

- Cryptographic hashes link blocks together securely.
- Used heavily in Bitcoin and other cryptocurrencies.

---

## The Difference

| Concept | Purpose |
|---|---|
| Encryption | Hides data |
| Hashing | Verifies data |

---

## Hashing Process Flow

```
Message
   |
Hash Function
   |
Message Digest
   |
Encrypt digest with PRIVATE key
   |
Digital Signature
```

---

## Digital Signatures

- A digital signature is NOT a scanned handwritten signature.
- It is a mathematical proof created using cryptography.

### Purpose

- To authenticate the identity of the sender.
- To ensure that the original content of a message or file has been sent unchanged.

### Properties

- Cannot be copied — Authentic
- Depend on the content of the message or file — Integrity
- Can be verified by any computer user and is not error prone.

---

## Sender Side

1. Creates a hash of the message.
2. Encrypts that hash using their private key.
3. The encrypted hash becomes the digital signature.

---

## Receiver Side

1. Decrypts the signature using the sender's public key.
2. Computes the hash again from the received message.
3. Compares both hashes.
4. If both hashes match, the message is authentic and was not modified.

---

## Keys

### Private Key

- Only known by the sender or the owner of the data.
- Used to create the digital signature.

### Public Key

- Known to everyone.
- Used to verify the digital signatures.

---

## Applications of Digital Signatures

- E-mails
- Data storage
- Electronic fund transfer
- Software distribution
- Smart cards
- Time stamped signatures

---

## How Digital Signatures Work in Emails

### Sender Side

1. Sender writes the email.
2. The email content is passed through a hash function.
3. A fixed-size message digest is generated.
4. The digest is encrypted using the sender's private key, producing an encrypted digest (digital signature).
5. The signature is attached to the email.

### Receiver Side

1. Uses the sender's public key to decrypt the signature, recovering the original digest.
2. Applies the same hash function (as the sender) to the received mail.
3. Compares the two hashes.
4. If they match, the email is authentic.
5. If they do not match, the email was modified.

### Real-World Examples

- Receiving semester grades through email — without digital signatures, an attacker can forge emails to deliver fake data.
- Organizations like Google Gmail and Microsoft Outlook use digital signing technology.
- In emails, it works like a letter with a unique seal:
  - Only the sender owns the sealing stamp.
  - Everyone can verify if the seal is genuine.
  - If someone changes the letter content, the seal breaks mathematically.

---

## Digital Signatures in Electronic Fund Transfer (EFT)

### Transaction Process

1. Customer from Bank A creates a transaction.
2. The banking system applies a hash function to create a message digest.
3. The digest is encrypted using the customer's private key, producing a digital signature.
4. The transaction is transmitted.
5. Bank B receives the transaction details, digital signature, and customer's public key information.

### Verification Process

1. Bank B decrypts the signature using the public key.
2. A new hash is generated from the received transaction.
3. Both hashes are compared.
4. If matched:
   - The transaction is authentic.
   - The sender cannot deny it later (non-repudiation) — cannot claim they did not initiate the transaction.
5. If not matched, the transaction is rejected.

### Real-World EFT Examples

- SWIFT secure banking communication
- PayPal payment verification system
- VISA payment system
- MasterCard transaction authentication

### Additional Security Measures in Banking

- Banks combine OTPs (One-Time Passwords) with digital signatures for multifactor authentication.
- Banks also use AI-based fraud detection systems.
