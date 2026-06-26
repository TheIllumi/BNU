# Computer Networks — Week 6
## Forwarding & Routing
**Reference:** Chapter 18.8 — Douglas E. Comer

---

## 1. Network Communication

- Communication involves at least two entities:
  - One that **sends** information
  - Another that **receives** information
- Most packet switching communications systems contain **intermediate entities** (devices that forward packets)
- For successful communication, all entities in a network must agree on how information will be **represented and communicated**
  - Example: when two electronic entities communicate over a wired network, both sides must agree on the voltages to be used and the format of messages

---

## 2. Interoperability

- **Interoperability** = the ability of two entities to communicate without any misunderstandings → correct interoperability
- **Communication protocol / network protocol / protocol** = some specifications for network communication
- **Protocol** = a procedure to be followed during an exchange
- Another aspect of a protocol: define the **appropriate action** to take for each possible abnormal condition
  - e.g., an error or unexpected condition occurs, a response is expected, but no response arrives

---

## 3. Protocol Suites

- Protocols must be both **complete** and **efficient**
- To avoid duplication of effort, each protocol should handle a part of communication **not handled by other protocols**
- → Protocols are designed in complete, cooperative sets called **suites** or **families**
- Each protocol in a suite handles **one aspect** of communication
- The entire suite is designed to allow protocols to work together efficiently

---

## 4. Layering Models

- The fundamental abstraction used to collect protocols into a unified whole → a **layering model**
- A layering model describes how all aspects of a communication problem can be **partitioned into pieces** that work together
- Each piece = a **layer**
- Protocols in a suite are organized into a **linear sequence**
- This helps both protocol designers and implementors to concentrate on **one aspect of communication** at a given time

---

## 5. The Network Layer

- Responsible to take packets from the **source to the destination**
- Getting to the destination may require making many **hops** at intermediate routers along the way
- Network layer is the **lowest layer** that deals with **end-to-end transmission**

### Network Layer Responsibilities:
- Must know about the **topology of the network** (the set of all routers and links) and choose appropriate paths
- Must avoid overloading some communication lines and routers while leaving others idle (**traffic control**)
- Responsible to resolve issues when the source and destination are in **different networks**

---

## 6. Store-and-Forward Packet Switching

- The goal of a WAN is to allow as many computers as possible to **send packets simultaneously**
- The fundamental paradigm used to achieve simultaneous transmission → **store and forward**
- A switch **buffers packets in memory**

### Store & Forward Paradigm

- **Store operation** — occurs when a packet arrives:
  - I/O hardware inside the switch places a copy of the packet in memory
- **Forward operation** — occurs once a packet has arrived and is waiting in memory:
  - The processor examines the packet, determines its destination, and sends the packet to the destination

### Example 1 — ISP Routing

```
Host H1  →  Router A  →  [ISP Routers: B, C, D, E]  →  Router F  →  LAN  →  Host H2
                                    (WAN cloud)
```

- Host H1 is directly connected to the ISP's router A
- Host H2 is on a LAN (e.g., an office Ethernet) with a router F (owned by the customer)
- A host can transmit a packet to the nearest router, either on its own LAN or over a point-to-point link to the ISP
- The packet is stored there until it has fully arrived and the link has finished processing (verifying the checksum)
- Then it is forwarded to the next router along the path until it reaches the destination host, where it is delivered

---

## 7. Switches & Routers

| Device | Role |
|--------|------|
| **Switch** | Connects devices within the same network (LAN) |
| **Router** | Connects different networks (LAN to LAN or LAN to Internet) |

- Devices (PCs, phones, printers) connect to a **switch**
- The switch connects to a **router**
- The router connects to the **Internet**

---

## 8. Addressing in a WAN

- WAN addresses follow a key concept used in the Internet: **hierarchical addressing**
- Divides each address into two parts: **(site, computer at the site)**
  - Also referred to as **prefix** and **suffix**

### Hierarchical Addressing

- Format: **(switch #, Port #)**
- Each address is a **pair of decimal integers**
- Example: A computer connected to port 6 on packet switch 2 is assigned address **[2, 6]**
- As a single binary value:
  - **Initial bits** → represent the packet switch number
  - **Remaining bits** → identify a computer

#### Diagram:
```
[1,2] ─┐                      ┌─ [2,1]
       ├── Packet Switch 1 ──── Packet Switch 2
[1,5] ─┘                      └─ [2,6]
```

---

## 9. Next-Hop Forwarding

- When a packet arrives, a packet switch must choose an **outgoing path** over which to forward the packet
- If a packet is destined for a **local computer** → the switch sends the packet directly to the destination
- Otherwise → the packet must be forwarded over one of the connections that leads to another switch

### How it works:
1. Software in the packet switch uses the **destination address** in the packet to make the decision
2. The software **extracts the packet switch number** from the address
3. If the extracted value is **identical to the packet switch's own ID** → packet is intended for a local computer
4. Otherwise → packet is intended for a computer on another packet switch

### Key principle:
- A packet switch does **not** need to keep complete information about how to reach all possible computers
- It does **not** need to compute the entire route a packet will follow
- A switch only needs to know **which outgoing link to use** to reach a given switch → compute the **next hop**

### Forwarding Table (Example — Switch 2):

| To Reach | Send To |
|----------|---------|
| Switch 1 | Interface 1 |
| Switch 2 | Local Delivery |
| Switch 3 | Interface 4 |

### Example 2 — Using the Table:
- If a packet is destined for **[3, 5]**, switch 2 extracts 3, consults the table, and forwards the packet to **interface 4** (which leads to switch 3)
- A switch uses only the **first part** of the destination address until the packet reaches the final switch
- Then the final switch uses the **second part** to choose a specific computer

---

## 10. Computing Path in a WAN

- The easiest way to think about route computation → model the network as a **graph**
- Software uses the graph to compute the **shortest path** to all possible destinations
- Each **node** in the graph = a switch in the network (individual computers are not part of the graph)
- If the network contains a direct connection between a pair of switches → the graph contains an **edge/link** between the corresponding nodes

### Example Graph:
```
Switches: 1, 2, 3, 4
Connections (edges): 1-3, 3-2, 3-4, 2-4
```
*(Switch 1 connects only to Switch 3; Switches 2, 3, 4 form a triangle)*

---

## 11. Calculating Forwarding Tables

> Notation: **(k, j)** denotes a link from node **k** to node **j**

### Forwarding Table — Node 1:

| To Reach | Next Hop |
|----------|----------|
| 1 | — |
| 2 | (1,3) |
| 3 | (1,3) |
| 4 | (1,3) |

### Forwarding Table — Node 2:

| To Reach | Next Hop |
|----------|----------|
| 1 | (2,3) |
| 2 | — |
| 3 | (2,3) |
| 4 | (2,4) |

### Forwarding Table — Node 3:

| To Reach | Next Hop |
|----------|----------|
| 1 | (3,1) |
| 2 | (3,2) |
| 3 | — |
| 4 | (3,4) |

### Forwarding Table — Node 4:

| To Reach | Next Hop |
|----------|----------|
| 1 | (4,3) |
| 2 | (4,2) |
| 3 | (4,3) |
| 4 | — |

---

## 12. Default Routes

- Sometimes a forwarding table contains **many entries pointing to the same next hop**
  - This happens when the packet switch has only **one connection to the network**
  - Example: For Node 1 — except for its own entry, all entries point to link **(1,3)**

- To eliminate duplicate entries → **default route** mechanism
- Only **one default entry** is allowed in a forwarding table
- The default entry has **lower priority** than other entries (denoted by `*`)

### Node 1 — With Default Route:

| To Reach | Next Hop |
|----------|----------|
| 1 | — |
| * | (1,3) |

### Node 2 — With Default Route:

| To Reach | Next Hop |
|----------|----------|
| 2 | — |
| 4 | (2,4) |
| * | (2,3) |

### Node 4 — With Default Route:

| To Reach | Next Hop |
|----------|----------|
| 2 | (4,2) |
| 4 | — |
| * | (4,3) |

*(Node 3 has no default route — all destinations have unique next hops)*

---

## 13. Forwarding vs. Routing

### Forwarding
- **Router-local action** of transferring a packet from an input link interface to the appropriate output link interface
- Takes place at very short timescales (typically a **few nanoseconds**)
- Typically implemented in **hardware**

### Routing
- **Network-wide process** that determines the end-to-end paths that packets take from source to destination
- Often implemented in **software**

### Real-World Analogies:

**Example 1 — Bank System:**
| | |
|---|---|
| **Routing** | Bank system decides: transfer to another bank → go through central clearing system; international transfer → use SWIFT network |
| **Forwarding** | Each system node sends transaction to next system, processes based on instructions |
| Summary | Routing = Which path should money take? / Forwarding = Send it to the next system |

**Example 2 — E-commerce (Order Delivery):**
| | |
|---|---|
| **Routing** | Platform decides which warehouse will fulfill order, which courier partner to use |
| **Forwarding** | Warehouse staff packs item, sends to courier hub; Courier hubs pass package step-by-step |

---

## 14. Forwarding Table (Detailed)

- A **key element** in every network router
- A router forwards a packet by examining the value of one or more fields in the **arriving packet's header**
- Uses these header values to **index into its forwarding table**
- The value stored in the forwarding table entry indicates the **outgoing link interface** to which the packet is to be forwarded

### Forwarding Table Structure (Data Plane):

```
Routing Algorithm  →  Local Forwarding Table
  (Control Plane)          (Data Plane)

  header | output
  -------|-------
   0100  |   3
   0110  |   2
   0111  |   2
   1001  |   1
```

- **Routing Algorithm** (control plane) determines values in the forwarding table
- **Forwarding table** (data plane) maps header values to output interfaces
- Example: A packet arriving with header value **0110** is forwarded to output link **2**

---

## 15. Forwarding Table — Worked Example (Ex-1)

### Setup:
A router has the following directly connected networks:

| Network Address | Subnet Mask | Interface |
|-----------------|-------------|-----------|
| 192.168.1.0 | 255.255.255.0 | eth0 |
| 192.168.2.0 | 255.255.255.0 | eth1 |
| 10.0.0.0 | 255.0.0.0 | eth2 |

> **Interface** = connection point of a device to a network

### Question: Determine which interface will be used for:

**1. 192.168.1.45**
- Matches: `192.168.1.0/24`
- **Interface → eth0**

**2. 192.168.2.200**
- Matches: `192.168.2.0/24`
- **Interface → eth1**

**3. 10.5.6.7**
- Matches: `10.0.0.0/8`
- **Interface → eth2**

---

## 16. Routing Algorithm

- A **routing algorithm runs in every router**
- Both forwarding and routing functions are contained within a router
- The routing algorithm function in one router **communicates** with the routing algorithm function in other routers to compute the values for its forwarding table
- **Routing** = Sending packets from source to destination

---

## 17. Routing Table

- Every switch/router maintains one in the network
- Switch/router looks up the destination in a table to find the link
- **Table tells what to do with the packet**
- Also called: **Routing Table**

### Routing Table Structure:
**Database of 3 columns:**
| Column | Description |
|--------|-------------|
| Destination | Target node/network |
| Cost | Delay, latency, or dollar cost charged by service providers |
| Link to use (Next Hop) | The route to take |

- **Path** = sequence of links (e.g., A – C – E)
- Each router maintains **its own table**

### Costs:
- Links are shown with costs
- Cost can represent:
  - **Delay or latency**
  - **Dollar cost** of shipping data charged by service providers
- Goal: find the **minimum cost** route for the packet

---

## 18. Distance Vector Routing

- Looks at the network as a set of **nodes and edges** (a graph)
  - Edge = link
  - Each link has a cost

### Key Properties:
- Every node has info about **immediate neighbors only**
- Uses the **Bellman-Ford Equation**
- **Initially:** Distance/cost to reach neighbor is known
- **Finally:** Distance/cost to all nodes are known
- Routing Table = **Distance Vector**
- Cost = **estimated cost** to destination (updated in each iteration)

---

## 19. Distance Vector Routing — Worked Example

### Network Graph:
```
        1
   A ─────── B
   |    3   /|
 5 |      /  | 9
   |    /    |
   C ──────── E
     4
   C ─── D
         |
       2 |
         E
```

**Edge costs:**
- A–B: 1
- A–C: 5
- B–C: 3
- B–E: 9
- C–D: 4
- D–E: 2

---

### Initial Routing Tables (based only on direct neighbors):

#### Node A:
| Destination | Distance | Next Hop |
|-------------|----------|----------|
| A | 0 | A |
| B | 1 | B |
| C | 5 | C |
| D | ∞ | — |
| E | ∞ | — |

#### Node B:
| Destination | Distance | Next Hop |
|-------------|----------|----------|
| A | 1 | A |
| B | 0 | B |
| C | 3 | C |
| D | ∞ | — |
| E | 9 | E |

#### Node C:
| Destination | Distance | Next Hop |
|-------------|----------|----------|
| A | 5 | A |
| B | 3 | B |
| C | 0 | C |
| D | 4 | D |
| E | ∞ | — |

#### Node D:
| Destination | Distance | Next Hop |
|-------------|----------|----------|
| A | ∞ | — |
| B | ∞ | — |
| C | 4 | C |
| D | 0 | D |
| E | 2 | E |

#### Node E:
| Destination | Distance | Next Hop |
|-------------|----------|----------|
| A | ∞ | — |
| B | 9 | B |
| C | ∞ | — |
| D | 2 | D |
| E | 0 | E |

---

### DVR Update — Node A (Iteration 1)

Node A receives **distance vectors from its neighbors B and C**:

| — | From B (Distance) | From C (Distance) |
|---|---|---|
| To A | 1 | 5 |
| To B | 0 | 3 |
| To C | 3 | 0 |
| To D | ∞ | 4 |
| To E | 9 | ∞ |

#### Bellman-Ford Calculations at Node A:

**To reach A:**
- Distance = 0, Next Hop = A

**To reach B:**
- Via B: (A→B) + (B→B) = 1 + 0 = **1**
- Next Hop = **B**

**To reach C:**
- Via C: (A→C) + (C→C) = 5 + 0 = **5**
- Next Hop = **C**

**To reach D:**
- Via B: (A→B) + (B→D) = 1 + ∞ = ∞
- Via C: (A→C) + (C→D) = 5 + 4 = **9** ← minimum
- Next Hop = **C** (then to D)

**To reach E:**
- Via B: (A→B) + (B→E) = 1 + 9 = **10** ← minimum
- Via C: (A→C) + (C→E) = 5 + ∞ = ∞
- Next Hop = **B** (then to E)

#### Updated Routing Table — Node A:

| Destination | Distance | Next Hop |
|-------------|----------|----------|
| A | 0 | A |
| B | 1 | B |
| C | 5 | C |
| D | 9 | C, D |
| E | 10 | B, E |

---

## 20. In-Class Task (Assignment 3)

> **Task:** Update the routing tables at **Node D** and **Node E** using the Distance Vector Routing algorithm (Bellman-Ford), based on the network graph above.
>
> Submit handwritten work (scanned via CamScanner) as PDF in GCR under **Assignment 3**.
> **Deadline will be strictly followed.**

---

## 21. Book Reference

- **Chapter 18.8** — *Douglas E. Comer* (Internetworking with TCP/IP)
