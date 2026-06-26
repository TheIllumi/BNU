# Computer Networks - Week 10
## Internet Transport Protocols, DHCP, SNMP, VoIP, and Checksum

---

## 1. Internet Transport Protocols

The two main Internet transport protocols are:

- **TCP** (Transmission Control Protocol)
- **UDP** (User Datagram Protocol)

---

## 2. TCP (Transmission Control Protocol)

- Internetworking protocol
- Resides within **Layer 4 (Transport Layer)** of the OSI model
- Provides end-to-end transport of data units using **connection-oriented services** across multiple packet-switching networks
- Provides **reliable host-to-host data transfer**

### Key Characteristics

- **Connection-Oriented protocol** - A connection must be established using **3-way handshaking** before data is transmitted
- TCP data transfer takes more time than UDP because 3-way handshaking is done both for establishing and removing the connection
- Operates in **Full Duplex Mode**
- Header size of a TCP packet is **bigger** than the UDP header (~20 bytes)
- Performs **error checking**
- Packets are **ordered** - received in the same order as they are sent
- Used by application layer protocols: **HTTP, FTP, Telnet**, etc.

---

## 3. UDP (User Datagram Protocol)

- **Connectionless protocol** - no connection needs to be established
- Packets are sent directly over the network
- **Non-reliable** - sender does not know for sure if the packet has reached the receiver
- No sender-receiver handshaking
- UDP segments may be **lost** or **delivered out-of-order**
- Does not have an option for error checking
- **Full Duplex**
- **Unreliable but FAST**
- Applications must deal with lost packets
- Used by protocols: **VoIP, DHCP, SNMP, RIP, DNS**, etc.

---

## 4. TCP vs UDP - Comparison

| Feature | TCP | UDP |
|---|---|---|
| Connection type | Connection-oriented | Connectionless |
| Data transfer | Confirmed (reliable) | Unconfirmed (unreliable) |
| Overhead | High | Low |
| Header size | ~20 bytes | 8 bytes |
| Flow control | Yes | No |

---

## 5. DHCP (Dynamic Host Configuration Protocol)

- A **client/server protocol** that automatically provides an IP host with its **IP address** and related configuration information such as:
  - Subnet mask
  - Default gateway
- Used in:
  - Home Wi-Fi routers (automatically assign IPs to phones/laptops)
  - School or university labs
  - Office networks
  - Large enterprise networks

---

## 6. SNMP (Simple Network Management Protocol)

- A networking protocol used for the **management and monitoring** of network-connected devices in IP networks
- Example use case - A university network with 50 computers, 5 switches, and 2 routers. The admin can use SNMP to:
  - Monitor traffic on each switch
  - Get alerts when a router fails
  - Check which device is overloaded

---

## 7. VoIP (Voice over Internet Protocol)

- Technology that allows voice calls using a **broadband Internet connection** instead of a regular (analog) phone line
- No need for separate telephone infrastructure
- Works over LAN/WiFi
- Voice travels like data on the internet (as a highway)
- Examples: MS Teams, Zoom, customer support call centers, help desks, employees in an organization, WhatsApp, etc.

---

## 8. Checksum

### What is a Checksum?

- A **small value calculated from a block of data**
- Used to **detect errors** during transmission or storage
- Acts like a **digital fingerprint** of the data

### Why is it Needed?

When data travels across a network, it can get corrupted due to:
- Noise
- Signal interference
- Hardware issues

A checksum provides a way to verify whether the data received is exactly the same as what was sent.

### How Does it Work?

**Sender side:**
1. Take the data
2. Apply a mathematical operation (like addition)
3. Generate a checksum
4. Send data + checksum

**Receiver side:**
1. Perform the same calculation on received data
2. Compare with received checksum
3. Matched → Data is correct
4. NOT matched → Error detected

> Note: Checksum **detects** errors but does **not correct** them.

---

## 9. Checksum - Basic Example (Ex-1)

**Data:** 10, 20, 30

- Sender computes: 10 + 20 + 30 = **60**
- Sender sends: Data (10, 20, 30) + Checksum (60)
- Receiver computes: 10 + 20 + 30 = 60 → **No error**

If data changes during transmission (e.g., 10, **25**, 30):
- Receiver computes: 10 + 25 + 30 = **65**
- 65 ≠ 60 → **Error detected**

---

## 10. Checksum in the Transport Layer

- The Transport Layer is where checksum is most commonly used
- Protocols like **TCP and UDP** use checksums to detect errors in data
- The sender calculates a checksum and attaches it to the segment
- The receiver recalculates and compares:
  - Same → data is correct
  - Different → data is corrupted
- TCP checksum ensures reliable communication
- UDP checksum provides optional error detection

### IPv4 Datagram Checksum

- The sender of an IPv4 datagram computes the checksum based on the data and embeds it in the frame
- The receiver computes the checksum locally and ascertains the data integrity
- A host transmits a packet to the nearest router; the packet is stored until it fully arrives and the link finishes processing by verifying the checksum

---

## 11. Checksum - Complement Method (Ex-2)

**Data:** 5 four-bit numbers: 7, 11, 12, 0, 6

- Simple method: Send the sum along with data → send (7, 11, 12, 0, 6, **36**)
- Receiver adds five numbers, compares with sum; same = no error

**Improved method (using complement):**
- Send the **negative (complement)** of the sum, called the checksum
- Send (7, 11, 12, 0, 6, **-36**)
- Receiver adds ALL numbers including checksum
- If result is **0** → no error
- Otherwise → error

---

## 12. Sender Side - Step-by-Step Procedure

1. The message is divided into 4-bit values
2. The checksum word is set to **0**
3. All values including the checksum are added
4. The sum is **complemented** and becomes the checksum
5. The checksum is sent **with** the data

---

## 13. Receiver Side - Step-by-Step Procedure

1. The message (including checksum) is divided into 4-bit values
2. All values are added
3. The sum is complemented and becomes the new checksum
4. If the value of checksum is **0** → message is accepted
5. Otherwise → message is **rejected**

---

## 14. Revisiting Ex-1 - Full Worked Example (4-bit words)

**Data:** 7, 11, 12, 0, 6

### Sender Side

| Values |
|---|
| 7 |
| 11 |
| 12 |
| 0 |
| 6 |
| 0 (Initial Checksum) |

- Sum = **36** → Binary: **100100**
- Since we have 4-bit words → **wrapping bits**
  - Take lower 4 bits: **0100** = 6
  - Carry: **10** = 2
  - Wrap: 0100 + 10 = **0110** = 6
- Take 1's Complement of 0110 → **1001** = **9**
- **Checksum = 9**
- **Data Sent: 7, 11, 12, 0, 6, 9**

### Receiver Side

- Receives: 7, 11, 12, 0, 6, **9**
- Sum = 7 + 11 + 12 + 0 + 6 + 9 = **45** → Binary: **101101**
- Lower 4 bits: **1101** = 13
- Carry: **10** = 2
- Wrap: 1101 + 10 = **1111** = 15
- 1's Complement of 1111 → **0000** = **0**
- Result = 0 → **Data Verified, no error**

---

## 15. Example-2 - Hexadecimal Checksum (16-bit words)

**Data to send:** `3456 ABCC 02BC EEEE`

### Sender Side Calculation

```
  3456
+ ABCC
+ 02BC
+ EEEE
+ 0000  (Initial Checksum)
```

Step-by-step column addition (right to left) with carries:

- Carry row: 1, 2, 2, 2
- Sum = **D1CC**
- Wrapping carry: C + 1 = **D** → Sum becomes **D1CD**
- Wait - following the slides:
  - Initial Sum = **D1CC**
  - Wrapping carry = 1 (overflow)
  - After wrap: **D1CD**

From the slides, the working shows:

| Step | Value |
|---|---|
| Sum (before wrap) | D 1 C C |
| Wrapping carry | + 1 |
| Final SUM | D 1 C D |
| 1's Complement (Checksum) | 2 E 3 2 |

- **Checksum = 2E32**
- **Data Sent: 3456 ABCC 02BC EEEE 2E32**

### Receiver Side Verification

Receiver adds all including checksum:

```
  3456
+ ABCC
+ 02BC
+ EEEE
+ 2E32  (Checksum)
```

- Sum = **FFFE** + carry wrap → **FFFF**
- 1's Complement of FFFF = **0000**
- Result = 0000 → **NO ERROR FOUND AT RECEIVER END**

---

## 16. Example-3

**Find the checksum at the receiver side if the following data is received (checksum in blue):**

`3456 ABCE 02BC EEEE 2E32`

> Note: The second word changed from ABCC to ABCE - this is an error detection exercise. The receiver recomputes and checks if the final checksum equals 0000. Since the data is corrupted, the result will NOT be 0000 and the error will be detected.

---

## 17. Example-4

**Apply checksum as an error detection mechanism for the following data using 16-bit words:**

`4500 0034 B612 4000 4006 0A00 008B 5BC6 AEE0`

- Show complete working at the **sender side**
- Show complete working at the **receiver side**
- Give conclusion: was correct data sent or not?

---

## 18. Example-5 - 16-bit 1's Complement Checksum

**Data:** `ABCD 1234 F0F0 0F0F AAAA 5555 8001 7FFE`

### Part 1: Calculate the Checksum (Sender Side)

Column-by-column addition with carries:

| Row | Values |
|---|---|
| Carry | 3, 3, 3, 3 |
| | A B C D |
| | 1 2 3 4 |
| | F 0 F 0 |
| | 0 F 0 F |
| | A A A A |
| | 5 5 5 5 |
| | 8 0 0 1 |
| | 7 F F E |
| Initial Checksum | 0 0 0 0 |
| Sum | B D F E |

- Carry wrap: carry = 3 → + 3
- Final Sum: **B E 0 1**

Taking 1's Complement of BE01:

```
B = 1011  →  0100 = 4
E = 1110  →  0001 = 1
0 = 0000  →  1111 = F
1 = 0001  →  1110 = E
```

- **Checksum = 41FE**

### Part 2: Final Transmitted Data from Sender

`ABCD 1234 F0F0 0F0F AAAA 5555 8001 7FFE 41FE`

### Part 3: Corrupted Transmission

During transmission:
- F0F0 → **F0F1** (bit flipped)
- 0F0F → **0F0E** (bit flipped)

**Received data at receiver:**

`ABCD 1234 F0F1 0F0E AAAA 5555 8001 7FFE 41FE`

### Receiver Recalculation and Conclusion

- Original sum + checksum = BE01 + 41FE = **FFFF** (correct case → all F's = no error after complement)
- New sum with corrupted values = **FFFC** with carry = 3
- FFFC + 3 = **FFFF** → error goes **undetected**

### Limitation Observed

This demonstrates a **limitation of 1's complement arithmetic**:
- It only verifies the overall sum
- **Checksum fails when multiple errors balance each other**, producing the same final sum
- This is a known weakness - complementary bit errors can cancel out

---

## 19. Where is Checksum Used? (Syllabus Topic)

- **Transport Layer protocols: TCP and UDP**
  - TCP: mandatory checksum, ensures reliable communication
  - UDP: optional checksum, provides basic error detection
- **IPv4 datagrams**: checksum is computed over the IP header
- **Communication protocols TCP/IP and UDP** implement checksum to determine whether received data is corrupted during transmission

---

## 20. Book References

- **James Kurose, W. Ross** - Chapter 5
- **Douglas E. Comer** - Chapter 18 (Protocols/Checksum), Chapter 24.8 (Checksum)

---
