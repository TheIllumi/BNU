# Computer Networks — Week 5: Subnetting

---

## 1. Classful IP Addressing

Divides IPv4 into fixed classes:

| Class | First Octet Range | Network Part | Host Part | Default Subnet Mask | CIDR |
|-------|------------------|--------------|-----------|----------------------|------|
| A     | 1 – 126          | 1 octet      | 3 octets  | 255.0.0.0            | /8   |
| B     | 128 – 191        | 2 octets     | 2 octets  | 255.255.0.0          | /16  |
| C     | 192 – 223        | 3 octets     | 1 octet   | 255.255.255.0        | /24  |

---

## 2. Subnet Mask

- IP addresses come paired with a subnet mask.
- There is a **default subnet mask** for each IP class:
  - Class A → `255.0.0.0`
  - Class B → `255.255.0.0`
  - Class C → `255.255.255.0`
- The subnet mask tells **what part of the IP address denotes the network** and which part denotes the client/host.

---

## 3. Problems with Classful IP Addressing

### Problem 1: Address Wastage
- If a company needs **1000 hosts**:
  - Class C → only 254 usable hosts (too small)
  - Class B → 65,534 usable hosts (too large, wastes 64,000+ addresses)

### Problem 2: No Flexibility in Network Size
- Classful addressing forces organizations to choose between:
  - Very small network (Class C)
  - Very large network (Class B)
  - Extremely large network (Class A)
- Modern networks have special needs: e.g., 800 hosts, 5,000 hosts, etc.
- **Solution:** Subnetting & CIDR (Classless Interdomain Routing)

### Problem 3: Exploding Routing Tables
- Backbone routers must have an entry for **each network address**.
- Routing table size started to outgrow the capacity of routers.
- **Routing table contains:** destination network ID, hop count to reach the network, and router ID of next hop.

### Problem 4: IPv4 Address Exhaustion
- The Internet was going to outgrow 32-bit addresses.
- **Solution:** IPv6

---

## 4. Common Problem — IP Address Conflicts

- Assigning an IP address to a device that is already assigned to another device causes the network to not know which device should receive the information.
- Most OSes and devices will show an **"IP Conflict" warning** when two devices share the same IP on a local network.

---

## 5. DHCP — Dynamic Host Configuration Protocol

- **Solution** to IP address conflicts.
- Provided by almost all home routers.
- DHCP **assigns addresses** to devices and keeps track of them.
- DHCP server is given a **range of IP addresses** to assign.
- Makes networks **plug-and-play**.

### The DHCP Process (DORA)

1. **Discover** — Client joins the network and broadcasts: *"Is there any DHCP server that can give me an IP address?"*
2. **Offer** — DHCP server replies with an available IP and configuration:
   - IP address: `192.168.1.25`
   - Subnet mask: `255.255.255.0`
   - Gateway: `192.168.1.1`
3. **Request** — Client sends: *"I accept this IP address."*
4. **Acknowledge (ACK)** — DHCP server confirms and officially assigns the IP address.

---

## 6. Classless IP Addressing (CIDR)

- Introduced by **IETF in 1993**.
- **CIDR = Classless Inter-Domain Routing**
- Goals:
  - Minimize waste of unused IP addresses
  - Control routing table size
  - Slow rapid exhaustion of IPv4 addresses
- CIDR allows **custom-sized networks**: `/20`, `/22`, `/27`, etc.
- Written as: `ddd.ddd.ddd.ddd/m` where `m` = number of 1-bits in the mask.
  - Example: `192.5.48.69/26` → mask of 26 bits

### CIDR Rules
1. The number of addresses requested must be a **power of 2**.
2. The block of addresses assigned must have **contiguous unallocated addresses**.
3. The **first address** of any block must be **divisible by the size of the block**.

### Example — Classless Addressing
- A network with **9 hosts** needs only 4 host bits (binary of 9 = `1001`).
- Class C wastes 8 bits (supports 256 hosts).
- Classless addressing allows a **28-bit prefix** and **4-bit suffix** — perfectly sized.

---

## 7. Subnetting

### Why Subnetting?
- Organizations have **multiple networks independently managed** (e.g., Engineering School, Medical School, Library within a University Network).
- **Solution 1:** Allocate a separate address to each network — difficult to manage; each must be addressable from outside.
- **Solution 2:** Add another level of hierarchy → **Subnetting**

### What is Subnetting?
- Splits the **host number portion** of an IP address into:
  - **Subnet number**
  - **(Smaller) host number**
- Results in a **3-layer hierarchy**:

```
Before:  | Network ID |        Host Number        |
After:   | Network ID | Subnet Number | Host Number |
                     ←  Extended Network Prefix  →
```

- Uses: `Network – Subnet – Host`

### Benefits of Subnetting
- Improves **efficiency** of IP address usage.
- **Reduces router complexity** — external routers don't know about internal subnetting.
- Subnet structure is **not visible outside** the organization.
- Subnets can be **freely assigned** within the organization.
- Internally, subnets are treated as **separate networks**.

### Subnetting Rules
- Devices on the **same LAN** must use IP addresses in the **same subnet**.
- Devices on **different LANs** (separated by at least one router) must use **different subnets**.
- IP addresses must be **unique** inside the same internetwork.
- To create subnets: **extend the network portion by borrowing from the host portion**.

---

## 8. Subnet Mask (Custom)

- A subnet mask is a **32-bit number** with:
  - Network/subnet bits → all **1s**
  - Host bits → all **0s**
- Used with **logical AND** to extract the network address from an IP address.

### Example — Logical AND

```
Mask (M):  11111111 . 11111111 . 00000000 . 00000000  →  255.255.0.0
Address (D): 10000000 . 00001010 . 00000010 . 00000011  →  128.10.2.3

AND Result:  10000000 . 00001010 . 00000000 . 00000000  →  128.10.0.0
```

**Network Address = 128.10.0.0**

---

## 9. Subnetting — Worked Examples

### Practice 1: Divide `20.30.40.10/25` into 2 Subnets

- Block ID = 25 bits, Host ID = 32 − 25 = **7 bits**
- For 2 subnets → borrow **1 bit** from host ID
- New prefix = `/26`
- Last octet in binary: `00001010`

#### First Subnet
| Field        | Value             |
|-------------|-------------------|
| First Address | `20.30.40.0/26`  |
| Last Address  | `20.30.40.63/26` |

#### Second Subnet
| Field        | Value               |
|-------------|---------------------|
| First Address | `20.30.40.64/26`  |
| Last Address  | `20.30.40.127/26` |

---

### Practice 2: Divide `20.30.40.10/25` into 4 Subnets

- Block ID = 25 bits, Host ID = 32 − 25 = **7 bits**
- For 4 subnets → borrow **2 bits** from host ID
- New prefix = `/27`
- Last octet in binary: `00001010`

#### Subnet Details Table

| Subnet ID | Subnet Address | Host Address Range            | Broadcast Address |
|-----------|----------------|-------------------------------|-------------------|
| 1         | 20.30.40.0     | 20.30.40.1 – 20.30.40.30     | 20.30.40.31       |
| 2         | 20.30.40.32    | 20.30.40.33 – 20.30.40.62    | 20.30.40.63       |
| 3         | 20.30.40.64    | 20.30.40.65 – 20.30.40.94    | 20.30.40.95       |
| 4         | 20.30.40.96    | 20.30.40.97 – 20.30.40.126   | 20.30.40.127      |

---

### Example: `192.168.20.77/27`

- **Total bits:** 32
- **Prefix length:** 27
- **Host bits:** 32 − 27 = **5 bits**
- **Subnet mask in binary:** `11111111.11111111.11111111.11100000`
  - Last octet `11100000` = **224**
- **Subnet Mask:** `255.255.255.224`
- **Block size:** 256 − 224 = **32**

#### Subnet Ranges (Last Octet)
```
192.168.20.0   – 31
192.168.20.32  – 63
192.168.20.64  – 95    ← 77 falls here
192.168.20.96  – 127
192.168.20.128 – 159
192.168.20.160 – 191
192.168.20.192 – 223
192.168.20.224 – 255
```

#### Results for 192.168.20.77/27
| Field              | Value             |
|--------------------|-------------------|
| Network Address    | 192.168.20.64     |
| Broadcast Address  | 192.168.20.95     |
| First Usable Host  | 192.168.20.65     |
| Last Usable Host   | 192.168.20.94     |
| No. of Hosts       | 2⁵ − 2 = **30**   |

---

### For Practice: `172.16.45.200/26`
*(Complete the working as done in the previous example)*

---

## 10. Subnetting — Design Examples

### Ex-1: Design subnets for 14 subnets, 14 usable hosts each

- **Network Address:** `192.10.10.0`
- **Class:** C → Default Mask: `255.255.255.0`
- **Host part:** `00000000`
- **Bits borrowed:** 4
- **Possible subnets:** 2⁴ = **16**
- **Custom Subnet Mask:** `255.255.255.11110000` → `255.255.255.240`
- **Total host addresses:** 2⁴ = 16
- **Usable addresses:** 16 − 2 = **14** ✓

---

### Ex-2: 3 subnets, 45 usable hosts — Address: `200.175.14.0`

| Field                    | Value            |
|--------------------------|------------------|
| Class                    | C                |
| Default Subnet Mask      | 255.255.255.0    |
| Bits Borrowed            | 2                |
| Total Subnets            | 2² = 4           |
| Total Host Addresses     | 2⁶ = 64          |
| Usable Addresses         | 64 − 2 = **62**  |

---

### Ex-3: 250 subnets — Address: `101.0.0.0`

| Field                    | Value            |
|--------------------------|------------------|
| Class                    | A                |
| Default Subnet Mask      | 255.0.0.0        |
| Bits Borrowed            | 8                |
| Custom Subnet Mask       | 255.255.0.0      |
| Total Subnets            | 2⁸ = **256**     |
| Total Host Addresses     | 2¹⁶ = **65,536** |
| Usable Addresses         | 65,536 − 2 = **65,534** |

---

### Ex-4: 10 subnets — Address: `172.59.0.0`

| Field                    | Value             |
|--------------------------|-------------------|
| Class                    | B                 |
| Default Subnet Mask      | 255.255.0.0       |
| Bits Borrowed            | 4                 |
| Custom Subnet Mask       | 255.255.240.0     |
| Total Subnets            | 2⁴ = **16**       |
| Total Host Addresses     | 2¹² = **4,096**   |
| Usable Addresses         | 4,096 − 2 = **4,094** |

---

### Ex-5: 50 usable hosts — Address: `172.59.0.0`

| Field                    | Value                        |
|--------------------------|------------------------------|
| Class                    | B                            |
| Default Subnet Mask      | 255.255.0.0                  |
| Bits for hosts           | 6 (2⁶ = 64 ≥ 52)            |
| Bits Borrowed            | 2 + 8 = **10**               |
| Custom Subnet Mask       | `255.255.11111111.11000000`  |
| Custom Subnet Mask       | **255.255.255.192**          |
| Total Subnets            | 2¹⁰ = **1,024**              |
| Total Host Addresses     | 2⁶ = **64**                  |
| Usable Addresses         | 64 − 2 = **62**              |

---

## 11. Address Masks (Classless Addressing)

- Classless addressing requires **additional bit information** with each address.
- This information specifies the exact **boundary between the network prefix and host suffix**.
- A subnet is a group of IP addresses all having the **same value in the network/block ID** part.
- **Subnet number:** A dotted-decimal number representing a particular IP subnet.

---

## 12. Book Reference

- **Chapter 21**
- *Douglas E. Comer* — Internetworking with TCP/IP
