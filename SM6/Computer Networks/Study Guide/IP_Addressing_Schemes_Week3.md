# Computer Networks — Week 3
## IP Addressing Schemes

**Instructor Email:** shazia_rizwan@bnu.edu.pk

| Section | Google Classroom Code |
|---------|----------------------|
| Sec-A   | n4m5bcic             |
| Sec-B   | 233pkym4             |
| Sec-C   | cyvy7dcd             |

---

## 1. Address

- In order for a process running on one host to send packets to a process running on another host, the **receiving process needs to have an address**.
- On the Internet, the host is identified by its **IP address**.

---

## 2. Why IP Address?

- Human beings can be identified by names, CNIC numbers, driver's license numbers.
- Although each can be used to identify people, within a given context one identifier may be more appropriate than another.
  - e.g. We don't call each other by CNIC.
- Similarly, Internet hosts can be identified by their **hostname** (e.g. `www.facebook.com`, `www.google.com`).
  - However, hostnames provide little, if any, information about the **location** of the host within the Internet.
  - A hostname such as `www.eurecom.fr` tells us that the host is probably in France.
  - Hostnames consist of variable-length alphanumeric characters — difficult for routers to process.
- For these reasons, hosts are also identified by **IP addresses**.

---

## 3. IP Address

- It is a **32-bit** long identifier.
- It encodes a **network number (network prefix)** and a **host number**.

---

## 4. Address Assignment — 3 Key Rules

1. Devices on the **same LAN** must use IP addresses in the **same group** (IP network).
2. Devices on **different LANs** separated by at least one router must use IP addresses in **different IP networks**.
3. IP addresses must be **unique** inside the same internetwork.

---

## 5. Internetwork

- A **network** = a group of locally connected computers (e.g. computers connected in one school of BNU or in an office building).
- An **internetwork** = a collection of individual networks, connected by intermediate networking devices, that functions as a single large network.

### Example: Three LANs, Three IP Networks

| IP Network | Address Range |
|------------|--------------|
| Network 1  | All addresses beginning with **10** |
| Network 2  | All addresses beginning with **11** |
| Network 3  | All addresses beginning with **12** |

> Example devices: PC1 (10.1.1.1), PC11 (10.1.1.11), PC12 (10.2.3.12), R1 (10.1.1.251 / 11.1.1.251), PC22 (11.1.10.22), PC2 (11.1.10.2), R2 (11.1.1.252 / 12.1.1.252), PC3 (12.44.55.3), PC33 (12.1.1.33)

---

## 6. IP Address (Summary)

- An IP address **uniquely identifies** every device on an IP network.
- IP addresses operate at the **Network layer** of the TCP/IP protocol.
- IP address must be **unique**; clients on the same network must have the **same network ID**.

---

## 7. Two Flavors of IP Addresses

### IPv4 (Internet Protocol version 4)
- The Internet and most routers are currently configured for this.
- Uses **32-bit** addresses.
- About **290 million** are reserved for special purposes.
- Still commonly used but the world is rapidly moving towards IPv6.

### IPv6 (Internet Protocol version 6)
- Address size: **128-bit**.
- To use IPv6, existing routers and hardware would need to be **upgraded or configured**.

---

## 8. Dotted-Decimal Notation

- IP addresses are usually represented in **dotted-decimal notation**.
- Each group of eight bits (an **octet**) is represented by its decimal equivalent.

### Example 1
```
10000000 | 10001111 | 10001001 | 10010000
  128          143        137        144

IP Address: 128.143.137.144
```

### Example 2
```
11000000 | 10101000 | 10001000 | 00011100
  192          168        136         28

IP Address: 192.168.136.28
```

- **192** → 11000000 (1st byte)
- **168** → 10101000 (2nd byte)
- **136** → 10001000 (3rd byte)
- **28**  → 00011100 (4th byte)

---

## 9. IP Address Structure

An IP address is broken into **two parts**:

| Part | Description |
|------|-------------|
| **Network Address** | Identifies the network; each network has a unique network address |
| **Host/Local Address** | Uniquely identifies a device within a network |

- Each device on a network has the **same network address** portion.
- It is possible to have the same host/local address on **different networks**.
- The complete IP address (network + host) is **always unique**.
- Each physical network is assigned a **unique network number** that appears as a prefix.
- No two networks can share the same network number.
- No two computers on a given network can share the same host address.

---

## 10. IP Address Classes (IPv4)

The IP protocol defines **five** address classes: **A, B, C, D, and E**.

- Classes A–C use different sizes for the network ID and host ID portions.
- **Class D** → multicast addresses.
- **Class E** → experimental; not used.

### How to Determine the Class (First 4 Bits)

| Condition | Class |
|-----------|-------|
| First bit = **0** | Class A |
| First bit = **1**, 2nd bit = **0** | Class B |
| First two bits = **11**, 3rd bit = **0** | Class C |
| First three bits = **111**, 4th bit = **0** | Class D |
| First four bits = **1111** | Class E |

---

## 11. Why Classify? (Need for Classification)

- If 16 bits were used for network and 16 for host, the Internet could have 65,536 (2¹⁶) networks, each with 65,536 hosts.
- But if a network of only **1,000 computers** joins, it wastes **64,000+ IP addresses**.
- Classification solves this by matching network/host bit sizes to actual needs.

---

## 12. Address Classes — Network vs Host Parts

| Class | Length of Network Part | Length of Host Part |
|-------|------------------------|---------------------|
| A     | 1 octet (8 bits)       | 3 octets (24 bits)  |
| B     | 2 octets (16 bits)     | 2 octets (16 bits)  |
| C     | 3 octets (24 bits)     | 1 octet (8 bits)    |

### Breakdown
- **8 bits** for network → 24 bits for hosts → 256 networks, each with **16,777,216** hosts.
- **16 bits** for network → 16 bits for hosts → 65,536 networks, each with **65,536** hosts.
- **24 bits** for network → 8 bits for hosts → 16,777,216 networks, each with **256** hosts.

---

## 13. Classful IP Address Diagram

```
Class A:  | 0 | Network Prefix (8 bits) | Host Number (24 bits)       |
           bit0  bit1           bit7    bit8                         bit31

Class B:  | 1 | 0 | Network ID (16 bits) | Host (16 bits)             |
           bit0 bit1 bit2       bit15   bit16                        bit31

Class C:  | 1 | 1 | 0 | Network ID (24 bits) | Host (8 bits)          |
           bit0 bit1 bit2 bit3  bit23         bit24                   bit31

Class D:  | 1 | 1 | 1 | 0 | Multicast Group ID                       |
           bit0 bit1 bit2 bit3 bit4                                   bit31

Class E:  | 1 | 1 | 1 | 1 | 0 | (Reserved for future use)            |
           bit0 bit1 bit2 bit3 bit4 bit5                              bit31
```

---

## 14. Range of IP Addresses

| Class | First Octet Range | Full Range |
|-------|-------------------|------------|
| A | 0 – 127 (starts with binary **0**) | 0.0.0.0 → 127.255.255.255 |
| B | 128 – 191 (starts with binary **10**) | 128.0.0.0 → 191.255.255.255 |
| C | 192 – 223 (starts with binary **110**) | 192.0.0.0 → 223.255.255.255 |

### Class A — First Byte Range (bits)
| Bit 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | Decimal |
|-------|---|---|---|---|---|---|---|---------|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | * | * | * | * | * | * | * | — |
| 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 127 |

### Class B — First Byte Range (bits)
| Bit 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | Decimal |
|-------|---|---|---|---|---|---|---|---------|
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 128 |
| 1 | 0 | * | * | * | * | * | * | — |
| 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 191 |

### Class C — First Byte Range (bits)
| Bit 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | Decimal |
|-------|---|---|---|---|---|---|---|---------|
| 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 192 |
| 1 | 1 | 0 | * | * | * | * | * | — |
| 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 223 |

---

## 15. Class A — Detailed

- **8 bits** for network part, **24 bits** for host part.
- 1 bit is fixed (the leading `0`) → 7 bits left for network IDs → **2⁷ = 128** possible network IDs.
- Possible hosts = **2²⁴**.
- Default subnet mask: **255.0.0.0**

### Special Addresses
- **First IP** (all host bits = 0) → **Network Address**
- **Last IP** (all host bits = 1) → **Directed Broadcast Address (DBA)**

### Example
```
IP Address  : 10.2.100.17
Subnet Mask : 255.0.0.0
Network Addr: 10.0.0.0
DBA         : 10.255.255.255
```

> A subnet mask determines which portion of the IP address is the network and which is the host.

---

## 16. Class B — Detailed

- First byte range: **128 – 191** (64 values).
- Binary progression:
  - 10 000000 = 128
  - 10 000001 = 129
  - 10 000010 = 130
  - ...
  - 10 111111 = 191

### Calculations
- Total bits = 32; first 2 bits fixed → 30 bits free.
- Total possible addresses = **2³⁰**.
- Network ID = 2 octets; 2 bits fixed → 14 bits left → **2¹⁴ = 16,384** possible networks.
- Host ID = 2 octets → **2¹⁶ = 65,536** addresses per network.
- **Usable hosts = 65,536 − 2 = 65,534** (subtract network & broadcast).

### Default subnet mask: **255.255.0.0**

### Example 1 — Network starting with 128
```
Network range: 128.0.0.0 → 128.0.255.255
First IP = Network Address
Last IP  = Broadcast Address
Usable   = 65,534 hosts
```

### Example 2 — Finding Network Address
```
IP Address    : 130.1.2.3       (Class B, first octet 130 ∈ 128–191)
Subnet Mask   : 255.255.0.0

AND operation:
  130.1.2.3
& 255.255.0.0
= 130.1.0.0   ← Network Address

Network Range : 130.1.0.0 → 130.1.255.255
Network Addr  : 130.1.0.0
DBA           : 130.1.255.255
```

---

## 17. Class C — Detailed

- First byte range: **192 – 223** (starts with binary `110`).
- Default subnet mask: **255.255.255.0**

### Example
```
IP Address     : 192.168.10.11
Network Address: 192.168.10.0
DBA            : 192.168.10.255
```

---

## 18. Important Rules to Remember for IPv4

| Host Part Bits | Meaning |
|----------------|---------|
| All **0s** | Network Address |
| All **0s** except last bit (= 1) | First usable IP address |
| All **1s** except last bit (= 0) | Last usable IP address |
| All **1s** | Directed Broadcast Address (DBA) |

---

## 19. IPv4 Summary Table

| IP Class | First Octet Range | Default Subnet Mask | Number of Blocks (Networks) | IPs Per Block |
|----------|-------------------|---------------------|-----------------------------|---------------|
| A        | 1 – 126           | 255.0.0.0           | 126                         | 16,777,214    |
| B        | 128 – 191         | 255.255.0.0         | 16,384                      | 65,534        |
| C        | 192 – 223         | 255.255.255.0       | 2,097,152                   | 254           |

> Note: Class A range in this table starts at 1 (0.x.x.x is reserved).

---

## 20. Class Exercise

**Q: Write an IP address that belongs to Class B. Write the default Subnet Mask and Network Address.**

### Sample Solution

| Task | Answer |
|------|--------|
| IP Address (Class B) | **172.16.189.5** (first octet 172 ∈ 128–191 → Class B) |
| Default Subnet Mask  | **255.255.0.0** |
| Network Address      | **172.16.0.0** (last 2 octets set to zero) |

---

## 21. Reference

- **Book:** *Internetworking with TCP/IP* by **Douglas E. Comer**
- **Chapter:** 21
