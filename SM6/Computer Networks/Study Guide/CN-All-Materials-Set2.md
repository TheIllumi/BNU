# Computer Networks — All Materials (Set 2)
**Instructor: Shazia Rizwan | Spring 2026**

---

## Table of Contents

1. [Practice Slides — Week 7: Routing Algorithms & Subnetting](#practice-slides--week-7-routing-algorithms--subnetting)
2. [The Assignment: Vigenère Cipher (with Solution)](#the-assignment-vigenère-cipher-with-solution)
3. [Assignment 2 — Question Sheet (Section A)](#assignment-2--question-sheet-section-a)
4. [Assignment 2 — Khadijah Zahoor (F2023-956, Section C)](#assignment-2--khadijah-zahoor-f2023-956-section-c)
5. [Assignment 2 — Sara Haider (F2023-744, Section C)](#assignment-2--sara-haider-f2023-744-section-c)

---

## Practice Slides — Week 7: Routing Algorithms & Subnetting

**File:** `Practice-CS-1.pptx`
**Reference:** Kurose & Ross, Computer Networks — Chapter 4, 5

---

### Routing Algorithms — Overview

A routing algorithm determines good paths (routes) from senders to receivers through a network of routers. A "good" path is one with the **least cost**.

---

### Graph Model

A graph **G = (N, E)** consists of:
- **N** — a set of nodes (representing **routers**, the points at which packet-forwarding decisions are made)
- **E** — a collection of edges (representing **physical links** between routers)

Each edge has a **cost value** reflecting, e.g., the physical length of the link, the link speed, or monetary cost. Notation:
- `c(x, y)` = cost of edge between nodes x and y
- If `(x, y) ∉ E`, then `c(x, y) = ∞`
- Only **undirected graphs** are considered here: `c(x, y) = c(y, x)`
- A node `y` is a **neighbor** of `x` if `(x, y) ∈ E`

---

### Least-Cost Path

The **cost of a path** = sum of all edge costs along the path.

**Goal:** Find the path between source and destination with the **minimum total cost**.

**Example:** Least-cost path from node `u` to node `w`
- Path: `(u, x, y, w)`
- Path cost = **3**

**Shortest path:** If all edges have the same cost, the least-cost path is also the shortest path (fewest links).

---

### Exercise 1 — Least-Cost Path

> Find the least-cost path from node `u` to `z`.
>
> *(Checking all 17 possible paths between u and z is an example of a **centralized routing algorithm** — the algorithm was run in one location: your brain.)*

---

### Centralized Routing Algorithm

Computes least-cost paths using **complete, global knowledge** about the network.

- Takes connectivity between all nodes and all link costs as input
- Algorithms with global state information → **Link-State (LS) algorithms**
- Must be aware of the cost of **every link** in the network

**How it works:**
1. All routers send their network information (topology, link costs) to a central controller
2. The controller computes the best paths (often using **Dijkstra's Algorithm**)
3. Routes are distributed back to routers

**Example protocol:** Link-State Routing → **OSPF** (Open Shortest Path First)
- An Interior Gateway Routing Protocol (IGP) — routes traffic within a single Autonomous System (AS)
- An **Autonomous System (AS)** = a network under one administrative control (e.g., a university, company, or ISP)
- Does **not** handle routing policies between organizations

**Advantages:**
- Accurate routing decisions (global view)
- Optimal paths are usually found

**Disadvantages:**
- Single point of failure
- High overhead (needs full network info)
- Less scalable for very large networks

---

### Decentralized Routing Algorithm

Least-cost path calculation is carried out in an **iterative, distributed** manner by routers.

- No node has complete information about all network links
- Each node begins with only the knowledge of its **own directly attached links**
- Iterative process: exchange info with neighboring nodes → gradually calculates least-cost path
- Example: **Distance-Vector (DV) algorithm**

**How it works:**
- Routers exchange information only with neighbors
- Each router updates its routing table iteratively
- No global knowledge of the entire network

**Example protocol:** Distance Vector Routing → **RIP** (Routing Information Protocol)
- Used within small to medium-sized IP networks

**Advantages:**
- No single point of failure
- Scales better in large/distributed networks
- Simpler to implement

**Disadvantages:**
- Slower convergence
- May suffer from routing loops
- Count-to-infinity problem

#### Count-to-Infinity Problem
Occurs when routers continuously **increase the hop count** to a destination that is no longer reachable, instead of quickly realizing the destination is down. Routers keep counting upward (1, 2, 3, …) toward infinity because they mistakenly believe a path still exists.

---

### Static vs. Dynamic Routing Algorithms

#### Static Routing

Routes are **manually configured** by the network administrator and remain fixed unless changed manually.

| Property | Detail |
|----------|--------|
| Updates | No automatic updates |
| Routes | Predefined |
| Complexity | Simple to understand and implement |
| Protocol | No routing protocol required |
| Behaviour | Predictable |

**Disadvantages:**
- Not scalable for large networks
- No automatic adaptation to failures
- High administrative effort

**Example use case:** A university lab with 20–30 computers, 1 router connected to the internet, no frequent network changes. All traffic → send to ISP router (default route).

**Also used in:** Military/banking systems where route changes must be controlled — no automatic updates from unknown routers, reduces risk of routing attacks.

#### Dynamic Routing

Uses routing protocols:
- **RIP** — Routing Information Protocol (distance-vector)
- **OSPF** — Open Shortest Path First (link-state, within an AS)
- **BGP** — Border Gateway Protocol (constructs an autonomous systems graph based on information exchanged between BGP routers)

Routers exchange information and routes adapt to network changes (like Google Maps).

**Advantages:**
- Automatically handles failures
- Scalable for large networks
- Less manual configuration

**Disadvantages:**
- Higher CPU and memory usage (router CPU computes shortest paths, best routes, cost/metrics)
- More complex
- Possible security risks

**Real-world example:** When you open Google or YouTube, data travels across:
- Your university network
- ISPs like PTCL
- Data centers and clouds (AWS, Google Cloud)
- 4G/5G mobile networks (switching between towers continuously)
- Multinational companies with international presence

**Why dynamic routing is used:** Servers are constantly added/removed, load balancing is required, failures must be handled instantly, fastest available path must be calculated, and high availability must be ensured.

---

### Load-Sensitive vs. Load-Insensitive Algorithms

| Type | Description |
|------|-------------|
| **Load-Sensitive** | Link costs vary dynamically to reflect current congestion. A high cost indicates a congested link → routing algorithms avoid congested links. |
| **Load-Insensitive** | A link's cost does NOT explicitly reflect its current congestion level. |

**Today's Internet routing protocols (RIP, OSPF, BGP)** are **load-insensitive**.

**Why not load-sensitive?**
- Routers would need continuous measurement of traffic on all links
- Frequent updates → huge control overhead, consumes bandwidth
- By the time load info is shared it is already outdated → decisions based on old data
- Bad for: video calls, streaming, real-time applications
- Causes **route oscillations**: routes constantly flipping (A → B, B → A…) → network becomes unstable

---

### Practice: Subnetting

#### Example 1 — Given IP: 192.168.10.0/26

| | |
|--|--|
| **Network Part** | 26 bits |
| **Host Part** | 6 bits (32 − 26 = 6) |
| **Default Subnet Mask** | 255.255.255.0 |
| **Custom Subnet Mask** | `11111111.11111111.11111111.11000000` → **255.255.255.192** |

#### Example 2 — Host Range for 192.168.10.0/26

- Host bits = 6
- Binary range: `00000000` – `00111111` → decimal 0–63 → **64 total addresses**
- First usable host: **192.168.10.1**
- Last usable host: **192.168.10.62**
- Broadcast: **192.168.10.63**

#### Example 3 — Number of Subnets for 192.168.10.0/26

- Formula: Number of subnets = 2^(borrowed bits)
- Original network: /24 → New subnet: /26 → **Borrowed bits = 26 − 24 = 2**
- Number of subnets = 2² = **4**

**Subnet bit patterns:**
- `00` → 1st Subnet
- `01` → 2nd Subnet
- `10` → 3rd Subnet
- `11` → 4th Subnet

**Subnet 1:**
- Possible addresses: `192.168.10.00 000000` to `192.168.10.00 111111`
- Range: 192.168.10.0 – 192.168.10.63
- **Subnet Address:** 192.168.10.0
- **Usable Hosts:** 192.168.10.1 – 192.168.10.62
- **Broadcast:** 192.168.10.63

**Subnet 2:**
- Possible addresses: `192.168.10.01 000000` to `192.168.10.01 111111`
- Range: 192.168.10.64 – 192.168.10.127
- **Subnet Address:** 192.168.10.64
- **Usable Hosts:** 192.168.10.65 – 192.168.10.126
- **Broadcast:** 192.168.10.127

**Subnet 3 & Subnet 4:** *(Complete as exercise)*

---

## The Assignment: Vigenère Cipher (with Solution)

**File:** `The_Assignment__Vigenère_Cipher.pdf`

---

### How Vigenère Cipher Works

```
Ciphertext = (Plaintext letter value + Key letter value) mod 26
```

**Plaintext:** `A FATHER GIVES NOTHING BETTER THAN GOOD EDUCATION`
**Key:** `LEMON` (repeating)

**Key letter values:** L=11, E=4, M=12, O=14, N=13

---

### Key Repetition

```
Key repeats: L E M O N L E M O N L E M O N L E M O N L E M O N ...
```

---

### Step-by-Step Encryption Table

| Plaintext | Value | Key | Key Value | Sum | Mod 26 | Cipher |
|-----------|-------|-----|-----------|-----|--------|--------|
| A | 0 | L | 11 | 11 | 11 | **L** |
| F | 5 | E | 4 | 9 | 9 | **J** |
| A | 0 | M | 12 | 12 | 12 | **M** |
| T | 19 | O | 14 | 33 | 7 | **H** |
| H | 7 | N | 13 | 20 | 20 | **U** |
| E | 4 | L | 11 | 15 | 15 | **P** |
| R | 17 | E | 4 | 21 | 21 | **V** |
| G | 6 | M | 12 | 18 | 18 | **S** |
| I | 8 | O | 14 | 22 | 22 | **W** |
| V | 21 | N | 13 | 34 | 8 | **I** |
| E | 4 | L | 11 | 15 | 15 | **P** |
| S | 18 | E | 4 | 22 | 22 | **W** |
| N | 13 | M | 12 | 25 | 25 | **Z** |
| O | 14 | O | 14 | 28 | 2 | **C** |
| T | 19 | N | 13 | 32 | 6 | **G** |
| H | 7 | L | 11 | 18 | 18 | **S** |
| I | 8 | E | 4 | 12 | 12 | **M** |
| N | 13 | M | 12 | 25 | 25 | **Z** |
| G | 6 | O | 14 | 20 | 20 | **U** |
| B | 1 | N | 13 | 14 | 14 | **O** |
| E | 4 | L | 11 | 15 | 15 | **P** |
| T | 19 | E | 4 | 23 | 23 | **X** |
| T | 19 | M | 12 | 31 | 5 | **F** |
| E | 4 | O | 14 | 18 | 18 | **S** |
| R | 17 | N | 13 | 30 | 4 | **E** |
| T | 19 | L | 11 | 30 | 4 | **E** |
| H | 7 | E | 4 | 11 | 11 | **L** |
| A | 0 | M | 12 | 12 | 12 | **M** |
| N | 13 | O | 14 | 27 | 1 | **B** |
| G | 6 | N | 13 | 19 | 19 | **T** |
| O | 14 | L | 11 | 25 | 25 | **Z** |
| O | 14 | E | 4 | 18 | 18 | **S** |
| D | 3 | M | 12 | 15 | 15 | **P** |
| E | 4 | O | 14 | 18 | 18 | **S** |
| D | 3 | N | 13 | 16 | 16 | **Q** |
| U | 20 | L | 11 | 31 | 5 | **F** |
| C | 2 | E | 4 | 6 | 6 | **G** |
| A | 0 | M | 12 | 12 | 12 | **M** |
| T | 19 | O | 14 | 33 | 7 | **H** |
| I | 8 | N | 13 | 21 | 21 | **V** |
| O | 14 | L | 11 | 25 | 25 | **Z** |
| N | 13 | E | 4 | 17 | 17 | **R** |

---

### Final Ciphertext

```
LJMHUPV SWIPW ZCG SMZOP XFSE ELMBT ZSPSQ FGMHVZR
```

---

## Assignment 2 — Question Sheet (Section A)

**Course:** Computer Networks (CSC-203)
**Assignment:** Assignment-2 (Spring 2026)
**Date:** 11th March 2026 | **Due Date:** 13th March 2026 (5pm) | **Marks:** 15
**Section:** A

---

### Task: Explore Private Address Spaces in IPv4 for Each Address Class `[CLO1]`

Prepare a 2-page handout on the following:

1. Why were private IP address ranges introduced in IPv4 networks? `[3]`
2. How is security managed? `[2]`
3. Role of routers here? `[2]`
4. Examples `[2]`
5. Pros & Cons `[2]`
6. Check your home WiFi network. Find out your device IP address, is it private or public, find the default router (gateway) IP? `[3]`
7. Clearly include sources/references in your submission. `[1]`

---

## Assignment 2 — Khadijah Zahoor (F2023-956, Section C)

**Course:** Computer Networks (CSC-203)
**Assignment:** Assignment-2 (Spring 2026)
**Date:** 11th March 2026 | **Due Date:** 13th March 2026 (5pm) | **Marks:** 15
**Name:** Khadijah Zahoor | **Reg. No.:** F2023-956 | **Section:** C

---

### 1. Why were private IP address ranges introduced in IPv4 networks? `[3]`

Private IP address ranges were introduced to solve the problem of **IPv4 address exhaustion**. IPv4 uses a 32-bit addressing system that provides approximately 4.3 billion unique IP addresses. As the number of internet users, computers, smartphones, and IoT devices increased rapidly, the available public IP addresses started running out.

To address this issue, the Internet Engineering Task Force (IETF) defined private IP address ranges in **RFC 1918**. These addresses are used within local networks such as homes, schools, offices, and organizations.

Devices using private IP addresses cannot directly communicate with the public internet. Instead, they communicate through a router that performs **Network Address Translation (NAT)**. NAT converts private IP addresses into a public IP address when accessing the internet. This allows multiple devices inside a local network to share a single public IP address, helping conserve the limited IPv4 address space and making network management more efficient.

---

### 2. How is security managed? `[2]`

Security in private IP networks is mainly managed through **network isolation and address translation**. Private IP addresses are not accessible directly from the public internet. This prevents external users from directly accessing internal devices within a local network.

Routers use **Network Address Translation (NAT)** to hide internal IP addresses when devices communicate with the internet. Additionally, routers often include **firewalls** that monitor incoming and outgoing network traffic. These security mechanisms help prevent unauthorized access and protect the internal network from potential cyber threats.

---

### 3. Role of routers here? `[2]`

Routers play a very important role in private IP networks:

- They act as the **default gateway**, connecting the local network to the internet.
- Perform **NAT**, converting private IP addresses into a public IP address so that devices inside the local network can access external networks.
- Manage network communication and often provide **DHCP** (Dynamic Host Configuration Protocol) services, which automatically assign IP addresses to devices connected to the network.

Therefore, routers ensure proper communication between devices in a local network and external networks such as the internet.

---

### 4. Examples `[2]`

According to RFC 1918, the following IP address ranges are reserved for private networks:

| Class | Private IP Range |
|-------|-----------------|
| Class A | 10.0.0.0 – 10.255.255.255 |
| Class B | 172.16.0.0 – 172.31.255.255 |
| Class C | 192.168.0.0 – 192.168.255.255 |

---

### 5. Pros & Cons `[2]`

**Advantages:**
- Helps conserve the limited IPv4 address space
- Provides basic network security by hiding internal IP addresses
- Allows multiple devices to share one public IP address through NAT
- Efficient for local network communication

**Disadvantages:**
- Requires NAT configuration for internet access
- Some applications such as peer-to-peer networking may face connectivity issues
- Troubleshooting network problems can become more complex

---

### 6. Home WiFi Network Check `[3]`

After running the `ipconfig` command in Command Prompt, the following information was obtained from the Wi-Fi adapter:

| Field | Value |
|-------|-------|
| **Device IP Address** | 192.168.0.124 |
| **Subnet Mask** | 255.255.255.0 |
| **Default Gateway (Router IP)** | 192.168.0.1 |

The IP address **192.168.0.124** falls within the range 192.168.0.0 – 192.168.255.255, which belongs to the **Class C private IP address range** defined in RFC 1918.

Therefore, my device is using a **Private IPv4 address**.

The default gateway **192.168.0.1** represents the router that connects the local network to the internet and performs NAT so that devices in the private network can communicate with external networks.

---

### References `[1]`

- https://datatracker.ietf.org/doc/html/rfc1918
- https://www.geeksforgeeks.org/computer-networks/private-ip-addresses-in-networking/
- https://www.cisco.com/c/en/us/support/docs/ip/network-address-translation-nat/4606-8.html
- https://www.techtarget.com/searchnetworking/tip/Introduction-to-IP-addressing-and-subnetting

---

## Assignment 2 — Sara Haider (F2023-744, Section C)

**Course:** Computer Networks (CSC-203)
**Assignment:** Assignment-2 (Spring 2026)
**Date:** 11th March 2026 | **Due Date:** 13th March 2026 (5pm) | **Marks:** 15
**Name:** Sara Haider | **Reg. No.:** F2023-744 | **Section:** C

---

### 1. Why were private IP address ranges introduced in IPv4 networks? `[3]`

Private IP address ranges were introduced to solve the problem of **IPv4 address exhaustion**. The IPv4 system provides about 4.3 billion unique addresses, which is insufficient for the rapidly growing number of internet devices.

To address this issue, special private address ranges were defined in **RFC 1918**. These addresses are used within local networks such as homes, offices, and organizations. Devices with private IP addresses cannot be accessed directly from the public internet.

Instead, they communicate with external networks through a router using **Network Address Translation**, which converts private IP addresses into a public IP address.

This approach allows many devices within a private network to share a single public IP address, helping conserve the limited IPv4 address space.

---

### 2. How is security managed? `[2]`

Security in private IP networks is managed mainly through **network isolation and address translation**. Devices using private IP addresses are not directly reachable from the public internet, which provides a basic level of protection. Routers use NAT to hide internal IP addresses when communicating with external networks. In addition, routers and firewalls can filter incoming and outgoing traffic, preventing unauthorized access to internal devices.

---

### 3. Role of routers here? `[2]`

Routers play a critical role in private IP networks:

- Act as the **default gateway** that connects the local network to the internet.
- Perform **Network Address Translation (NAT)**, converting private IP addresses into a public IP address so that devices can communicate with external servers.
- Manage network traffic and may assign IP addresses to devices using **DHCP**.

---

### 4. Examples `[2]`

| Class | Private IP Range |
|-------|-----------------|
| Class A | 10.0.0.0 – 10.255.255.255 |
| Class B | 172.16.0.0 – 172.31.255.255 |
| Class C | 192.168.0.0 – 192.168.255.255 |

---

### 5. Pros & Cons `[2]`

**Advantages:**
- Conserves the limited IPv4 address space
- Provides basic network security by hiding internal devices
- Allows multiple devices to share one public IP address

**Disadvantages:**
- Requires NAT configuration for internet access
- Some applications may experience connectivity issues due to NAT
- Troubleshooting network problems can sometimes become more complex

---

### 6. Home WiFi Network Check `[3]`

After running the `ipconfig` command in Command Prompt, the following information was obtained from the Wi-Fi adapter:

| Field | Value |
|-------|-------|
| **Device IP Address** | 192.168.1.6 |
| **Subnet Mask** | 255.255.255.0 |
| **Default Gateway (Router IP)** | 192.168.1.1 |

The IP address **192.168.1.6** belongs to the **Class C private address range (192.168.0.0 – 192.168.255.255)** defined in RFC 1918. Since 192.168.1.6 falls within the 192.168.x.x range, it is a **Private IPv4 Address**.

The Default Gateway **192.168.1.1** represents the router, which connects the local network to the internet and performs Network Address Translation to allow private devices to communicate with the public internet.

Private IP address ranges:
- 10.0.0.0 – 10.255.255.255
- 172.16.0.0 – 172.31.255.255
- 192.168.0.0 – 192.168.255.255

---

### References `[1]`

- https://www.geeksforgeeks.org/computer-networks/private-ip-addresses-in-networking/
- https://datatracker.ietf.org/doc/html/rfc1918
- https://www.cisco.com/c/en/us/support/docs/ip/network-address-translation-nat/4606-8.html
- https://www.techtarget.com/searchnetworking/tip/Introduction-to-IP-addressing-and-subnetting
