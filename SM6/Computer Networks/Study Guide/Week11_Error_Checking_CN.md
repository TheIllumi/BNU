# Computer Networks - Week 11
## Error Checking

**Reference:** Douglas E. Comer, Chapter 8

---

## Checksum - Comments

Checksum relies on 1's complement arithmetic because it:

- Preserves carries (no loss of information)
- Enables a simple "all 1s" verification rule
- Is efficient and easy to implement
- Works well for typical network errors

---

## Sources of Transmission Errors

- E. Comer, Chapter 8 (RIY)

---

## Types of Errors

### Single Bit Error
- A single bit in a block of bits is changed
- All other bits in the block are unchanged
- Often results from very short-duration interference

### Burst Error
- Multiple bits in a block of bits are changed
- Often results from longer-duration interference

### Erasure (Ambiguity)
- The signal that arrives at a receiver is ambiguous
- Does not clearly correspond to either a logical 1 or a logical 0
- Can result from distortion or interference

---

## Single Parity Checking (SPC)

### Overview
- One form of SPC defines a block to be an 8-bit unit of data (i.e., a single byte)
- On the sending side, an encoder adds an extra bit (parity bit) to each byte before transmission
- A receiver removes the parity bit and uses it to check whether bits in the byte are correct

### How It Works
- Before parity can be used, the sender and receiver must be configured for either **even parity** or **odd parity**
- When using **even parity**, the sender chooses a parity bit of **0** if the byte has an even number of 1 bits
- The sender chooses **1** if the byte has an odd number of 1 bits
- Even or odd parity specifies whether the 9 bits sent across a channel have an even or odd number of 1 bits

### Parity Bit Table

| Original Data | Even Parity | Odd Parity |
|---------------|-------------|------------|
| 0 0 0 0 0 0 0 0 | 0 | 1 |
| 0 1 0 1 1 0 1 1 | 1 | 0 |
| 0 1 0 1 0 1 0 1 | 0 | 1 |
| 1 1 1 1 1 1 1 1 | 0 | 1 |
| 1 0 0 0 0 0 0 0 | 1 | 0 |
| 0 1 0 0 1 0 0 1 | 1 | 0 |

### Limitations
- A weak form of channel coding — can detect errors but **cannot correct** them
- Can only handle errors where an **odd number of bits** are changed
- If one of the nine bits (including the parity bit) is changed during transmission, the receiver will declare the incoming byte invalid
- If a burst error occurs in which **two, four, six, or eight bits** change value, the receiver will incorrectly classify the incoming byte as valid

### Applications
- Simplest error detection method
- Used in simple communication links at the data link layer of the OSI model to detect errors in frames
- Widely used in serial data transmission (e.g., microcontroller to device communication, embedded systems)
- Examples: computer communicating with a sensor or modem, RAM error detection
- Too weak for large data transmission
- Still useful in IoT devices, embedded systems, and low-speed communication links
- Modern networks prefer **Checksum** and **CRC**

### Position of the Parity Bit
- The position of the parity bit depends on the system design, protocol, or teaching convention
- In most computer organization and networking examples, common practice is to add the parity bit at the **left end (MSB side)**
  - Keeps original data unchanged
  - Easier to treat parity as a "check bit" added externally
- Sometimes, parity bit is added as **LSB**
  - Easier in serial transmission systems
  - Some hardware shifts bits and appends parity at the end
- Parity bit is not tied to MSB or LSB by theory; it is simply an extra bit added for error detection
- Always check the system specification or question instruction

---

## Worked Examples

### Example 1 - Even Parity (Single Bit Error Detection)

**Given Data:** `10101101`

**Step 1 - Count 1s:**
Total number of 1s = 5 (Odd)

**Step 2 - Determine Parity Bit (Even Parity):**
Total number of 1s should be even, so we need an additional 1 bit.
Parity bit = **1**

**Step 3 - Transmitted Data:**
`10101101 1`

**Step 4 - Receiver Check:**
Receiver counts number of 1s: Total 1s = 6 (Even) → **No error detected**

**Step 5 - Simulating a Bit Flip:**
- Given Data: `10101101`
- Received Data: `101001011`
- Count 1s: 5 → Odd → **Error detected**

---

### Example 2 - Even Parity (Two Bit Flips — Undetected)

- Original: `101011011`
- Received: `100011011`
- Count 1s: 6 → Even → **No error detected** (error goes unnoticed)

---

### Example 3 - Odd Parity

**Given Data:** `10101101`
- Count 1s: 5 → Odd
- Parity Bit added: **0** (already odd, no need to add a 1)
- **Transmitted Data:** `10101101 0`

---

### Example 4 - Even Parity, 16-bit Data (Practice)

**Problem:**
A system uses even parity for 16-bit data words. The parity bit is added at the LSB side. The 16-bit data to be transmitted is: `D596`.

1. Calculate the parity bit
2. Write the transmitted 17-bit word
3. Show how the receiver checks correctness

**Solution:**

**Step 1 - Convert D596 to binary:**

| Hex | Binary |
|-----|--------|
| D   | 1101   |
| 5   | 0101   |
| 9   | 1001   |
| 6   | 0110   |

Data: `1101 0101 1001 0110`

**Step 2 - Count 1s:**

| Nibble | 1s |
|--------|----|
| 1101   | 3  |
| 0101   | 2  |
| 1001   | 2  |
| 0110   | 2  |

Total: 3 + 2 + 2 + 2 = **9 ones** (Odd)

**Step 3 - Determine Parity Bit:**
Current 1s = 9 (Odd). To make it even, parity bit = **1**

**Step 4 - Transmitted Frame (parity at LSB):**
`1101 0101 1001 0110 1`
Total 1s: 10 → Even → **No error detected**

---

### Example 5 - Parity Bit Checking (Assignment/Submission)

**Problem:**
Suppose the sender wants to send the word **PopQuiz**. ASCII is applied character by character and parity is applied.

1. Convert the following decimal values into binary (to align with 8-bit ASCII codes):
   `80  111  112  81  117  105  122`
2. Work out the final data stream in binary
3. Assume **even parity** is used for each character on the **MSB side**
4. Show complete working at the receiver end to decide if correct data has been received or not

---

## Error Handling Strategies

Mathematical techniques have been developed to overcome data errors for better reliability. These are known collectively as **channel coding**.

Two broad categories:

### 1. Forward Error Correction (FEC)
- Adds additional information to data that allows a receiver to verify that data arrives correctly and to correct errors, if possible
- Allows a receiver to determine exactly which bits have been changed and to compute correct values

### 2. Automatic Repeat reQuest (ARQ)
- Requires the cooperation of a sender
- Sender and receiver exchange messages to ensure that all data arrives correctly

---

## General Notes on Transmission Errors

- Transmission errors are inevitable
- Error detection mechanisms add overhead
- Need to carefully choose exactly which error detection and compensation mechanisms will be used

---

## Reference

- **Book:** Douglas E. Comer
- **Chapter:** 8
