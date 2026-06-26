# Computer Networks — Addresses
**Date:** 26 & 27 Feb 2026

---

## Address Classes

| Class   | Used By                        |
|---------|-------------------------------|
| Class A | Large organizations, governments |
| Class B | Medium sized organizations     |
| Class C | Small organizations            |

---

## Total Number of Hosts & Networks

- **1 address** is reserved as the **network address**
- **1 address** is reserved as the **broadcast address**

$$\text{Number of hosts} = 2^{\text{number of host bits}} - 2$$

$$\text{Number of networks} = 2^{\text{variable no. of bits for network}}$$

> **Example:** Total Class B networks = 2¹⁴ = **16,384 networks**
> (6 + 8 = 14 bits for network)

---

## IPv4 Networks

IPv4 = **32 bits total**

| Class   | Network Bits | Total Networks |
|---------|-------------|----------------|
| Class A | 7 bits      | 2⁷ = 128       |
| Class B | 14 bits     | 2¹⁴ = 16,384   |
| Class C | 21 bits     | 2²¹ = 2,097,152|

- **Class A** → few networks, many hosts
- **Class B** → medium networks, medium hosts
- **Class C** → many networks, few hosts

---

## Default Subnet Mask

- Tells a computer **which part is the network** and which part is the device (host)
- Before subnetting was invented, each class had a **built-in mask**
- This built-in mask is called the **default subnet mask**
  - Mask bit **1** → Network
  - Mask bit **0** → Host

---

## Default Subnet Mask / CIDR Notation

**CIDR = Classless Inter-Domain Routing**

| Class   | Default Mask  | CIDR | Network Bits |
|---------|--------------|------|--------------|
| Class A | 255.0.0.0    | /8   | 8            |
| Class B | 255.255.0.0  | /16  | 16           |
| Class C | 255.255.255.0| /24  | 24           |

### Identifying Class from First Octet

| If IP starts with... | Class | Default Mask  |
|----------------------|-------|--------------|
| 1 – 126              | A     | 255.0.0.0    |
| 128 – 191            | B     | 255.255.0.0  |
| 192 – 223            | C     | 255.255.255.0|

---

## Example — Finding Default Subnet Mask

**Q:** What is the default subnet mask of `172.20.5.6`?

- 172 falls in range **128–191** → **Class B**
- Default mask → **255.255.0.0**

---

## Calculating Network Address

- The **network address** is the **first address** in a subnet
- It identifies the network itself (not a device)
- Calculated using: **IP address AND Subnet Mask**

### Example-1

```
IP:   192.168.10.25
Mask: 255.255.255.0  (/24)
```

**Step 1: Write down the Mask**
- 255.255.255.0 means:
  - First 3 octets = Network
  - Last octet = Host

**Step 2: Set Host Part to 0**
→ Network Address = **192.168.10.0**

---

### Alternate Way (Bitwise AND)

```
IP:    11000000 . 10101000 . 00001010 . 00011001   (192.168.10.25)
AND
Mask:  11111111 . 11111111 . 11111111 . 00000000   (255.255.255.0)
       ─────────────────────────────────────────
       11000000 . 10101000 . 00001010 . 00000000
```

**Decimal notation:** 192.168.10.0

**Network Address = 192.168.10.0**

---

## Class A — Example

```
IP Address :        10.2.100.17
Default Subnet Mask: 255.0.0.0
Directed Broadcast Address (DBA): 10.255.255.255
```

---

## Class B — Deep Dive

Class B is identified when the **first octet is 128–191** (64 values):

```
10 000000 = 128
10 000001 = 129
10 000010 = 130
10 000011 = 131
    ...
10 111111 = 191
```

### Class B Network Range Example

For a network starting with **128**:
- IP range: `128.0.0.0` – `128.0.255.255`
- First IP = network address
- Last IP = broadcast address
- Usable hosts = 65536 − 2 = **65,534 hosts**

### Class B Full Example

```
Given host IP: 130.1.2.3
Class B (from 130)

Default Mask:  255.255.0.0

  130.1.2.3
  AND
  255.255.0.0
  ──────────
  130.1.0.0   ← Network Address (AND with zero clears host bits)
```

- `130.1.2.3` belongs to network **130.1.0.0**
- If this is BNU's address, the whole world sees it as `130.1.0.0`
- **Possible IP range:** `130.1.0.0` – `130.1.255.255`
- **Network Address:** `130.1.0.0`
- **Directed Broadcast Address (DBA):** `130.1.255.255`

---

## Class C — Example

```
IP Address:          192.168.10.11
Default Subnet Mask: 255.255.255.0
Network Address:     192.168.10.0
DBA:                 192.168.10.255
```

---

## IPv4 Host Bits — Rules to Remember

| Host Bits Condition              | Meaning                  |
|----------------------------------|--------------------------|
| All bits = **0**                 | Network Address          |
| All bits = 0 except last = **1** | First usable IP address  |
| All bits = 1 except last = **0** | Last usable IP address   |
| All bits = **1**                 | Directed Broadcast Address (DBA) |

---

## Class Exercise

**Task:**
1. Write an IP address that belongs to **Class B**
2. Write the **default Subnet Mask**
3. Write the **Network Address**

### Sample Solution

| Task                                   | Solution                                       |
|----------------------------------------|------------------------------------------------|
| IP address belonging to Class B        | `172.16.189.5` (128–191 → Class B)             |
| Default Subnet Mask                    | `255.255.0.0`                                  |
| Network Address                        | `172.16.0.0` (last 2 octets set to zero)       |

---

## Practice Examples

### Questions

| #  | IP Address       | Mask            | Network Address |
|----|------------------|-----------------|-----------------|
| Q1 | 192.168.5.23     | 255.255.255.0   | ?               |
| Q2 | 10.45.78.9       | 255.0.0.0       | ?               |
| Q3 | 172.16.200.15    | 255.255.0.0     | ?               |
| Q4 | 192.168.1.199    | 255.255.255.0   | ?               |

### Answers

| #  | Network Address  |
|----|------------------|
| Q1 | 192.168.5.0      |
| Q2 | 10.0.0.0         |
| Q3 | 172.16.0.0       |
| Q4 | 192.168.1.0      |

---

## Reference

- **Book:** Douglas E. Comer
- **Chapter:** 21
