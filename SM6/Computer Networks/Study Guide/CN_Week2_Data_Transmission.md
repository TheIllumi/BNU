# Computer Networks — Week 2: Data Transmission

**Course:** Computer Networks
**Instructor Email:** shazia_rizwan@bnu.edu.pk

**Google Classroom Codes:**
- Section A: `n4m5bcic`
- Section B: `233pkym4`
- Section C: `cyvy7dcd`

---

## 1. The Internet: A "Nuts and Bolts" View

### Billions of Connected Computing Devices
- **Hosts = End Systems** running network apps at the Internet's "edge"

### Packet Switches
- Forward packets (chunks of data)
- Types: **Routers**, **Switches**

### Communication Links
- Fiber, copper, radio, satellite
- Transmission rate: **Bandwidth**

### Networks
- A collection of devices, routers, and links managed by an organization

### Internet = "Network of Networks"
- Interconnected ISPs

### Protocols Are Everywhere
- Control sending and receiving of messages
- Examples: HTTP (Web), streaming video, Skype, TCP, IP, WiFi, 4G, Ethernet

### Internet Standards
- **RFC:** Request for Comments
- **IETF:** Internet Engineering Task Force

> **Example of content delivery networks:** Netflix, YouTube, and Spotify

---

## 2. The Internet: A "Services" View

### Infrastructure View
The Internet is an infrastructure that provides services to applications:
- Web, streaming video, multimedia teleconferencing, email, games, e-commerce, social media, interconnected appliances, …

### Programming Interface
- Provides a programming interface to distributed applications
- "Hooks" allowing sending/receiving apps to "connect" to and use Internet transport service
- Provides service options, analogous to postal service

---

## 3. What's a Protocol?

> **Protocols** define the **format**, **order** of messages sent and received among network entities, and **actions taken** on message transmission and receipt.

---

## 4. A Closer Look at Internet Structure

The Internet is composed of three main parts:

### Network Edge
- **Hosts:** Clients and servers
- Servers often located in data centers

### Access Networks / Physical Media
- Wired and wireless communication links

### Network Core
- Interconnected routers
- Network of networks

---

## 5. Access Networks and Physical Media

**Q: How to connect end systems to an edge router?**

- Residential access networks
- Institutional access networks (school, company)
- Mobile access networks (WiFi, 4G/5G)

---

### 5.1 Home Networks

Components of a typical home network:
- Cable or DSL modem
- Router, Firewall, NAT
- Wired Ethernet (1 Gbps)
- WiFi wireless access point (___ Mbps)
- Connects to/from headend or central office
- Wireless and wired devices often combined in a single box

---

### 5.2 Wireless Access Networks

Shared wireless access network connects end system to router via **base station (access point)**.

#### Wireless Local Area Networks (WLANs)
- Typically within or around a building (~100 ft)

#### Wide-Area Cellular Access Networks
- Provided by mobile/cellular network operator (10s of km)
- 10s Mbps
- 4G cellular networks (5G coming)

---

### 5.3 Enterprise Networks

Used by companies, universities, etc.

- Mix of wired and wireless link technologies
- Connecting a mix of switches and routers
- **Ethernet:** Wired access at 100 Mbps, 1 Gbps, 10 Gbps
- **WiFi:** Wireless access points at 11, 54, 450 Mbps
- Includes Ethernet switch, institutional mail/web servers, institutional router, and enterprise link to ISP (Internet)

---

### 5.4 Data Center Networks

- High-bandwidth links (**10s to 100s Gbps**) connect hundreds to thousands of servers together and to the Internet

---

## 6. Host: Sends Packets of Data

### Host Sending Function
1. Takes application message
2. Breaks it into smaller chunks known as **packets** of length **L bits**
3. Transmits packet into access network at **transmission rate R**
   - Also called: **link capacity** or **link bandwidth**

### Packet Transmission Delay Formula

$$\text{Packet Transmission Delay} = \frac{L \text{ (bits)}}{R \text{ (bits/sec)}}$$

---

## 7. Transmission Media

### Definition
- The **physical path** between transmitter and receiver
- Repeaters or amplifiers may be used to extend the length of the medium

### Classification by Path Type
- **Guided:** Communication follows an exact path (e.g., wire)
- **Unguided:** Communication has no specific path (e.g., radio transmission)

### Classification by Form of Energy
- **Electrical energy** — used on wires
- **Radio transmission** — used for wireless
- **Light** — used for optical fiber

### Guided vs. Unguided Media

| Type | Description | Examples |
|------|-------------|---------|
| **Guided** | Waves guided along a physical path | Twisted pair, coaxial cable, optical fiber |
| **Unguided** | Means for transmitting but not guiding waves | Atmosphere, outer space |

---

## 8. Transmission Media Types (Energy Classification)

```
Energy Types
├── Electrical
│   ├── Twisted Pair
│   └── Coaxial Cable
├── Light
│   ├── Optical Fiber
│   ├── Infrared
│   └── Laser
└── Electromagnetic (Radio)
    ├── Terrestrial Radio
    └── Satellite
```

---

## 9. Physical Media — Links Summary

### Bit & Physical Link
- **Bit:** Propagates between transmitter/receiver pairs
- **Physical link:** What lies between transmitter and receiver

### Guided Media
- Signals propagate in solid media: copper, fiber, coax

### Unguided Media
- Signals propagate freely (e.g., radio)

---

### 9.1 Twisted Pair (TP)
- Two insulated copper wires
- **Category 5:** 100 Mbps, 1 Gbps Ethernet
- **Category 6:** 10 Gbps Ethernet

---

### 9.2 Coaxial Cable
- Two concentric copper conductors
- Bidirectional
- Broadband:
  - Multiple frequency channels on cable
  - 100s Mbps per channel

---

### 9.3 Fiber Optic Cable
- Glass fiber carrying light pulses; each pulse = 1 bit
- High-speed operation:
  - High-speed point-to-point transmission (**10s–100s Gbps**)
- Low error rate:
  - Repeaters spaced far apart
  - Immune to electromagnetic noise

---

### 9.4 Wireless Radio
- Signal carried in various "bands" in the electromagnetic spectrum
- No physical "wire"
- Broadcast, **half-duplex** (sender to receiver)
- Propagation environment effects:
  - Reflection
  - Obstruction by objects
  - Interference/noise

#### Radio Link Types

| Type | Speed | Range |
|------|-------|-------|
| Wireless LAN (WiFi) | 10–100s Mbps | ~10s of meters |
| Wide-area (4G cellular) | 10s Mbps | ~10 km |
| Bluetooth (cable replacement) | Limited rates | Short distances |
| Terrestrial microwave | 45 Mbps channels | Point-to-point |
| Satellite | Up to 45 Mbps/channel | 270 ms end-to-end delay |

---

## 10. Repeater

- A WiFi repeater or extender is used to **extend the coverage area** of a WiFi network

---

## 11. WAN (Wide Area Network) Design

- Includes a large number of **Switching Nodes**
- Transmission from any device is routed through internal nodes to the destination
- These nodes are **not concerned with the content** of the data
- Their purpose is to provide a **switching facility** that moves data from node to node until it reaches its destination

---

## 12. WAN Implementation Technologies

WANs are traditionally implemented using one of two technologies:

1. **Circuit Switching**
2. **Packet Switching**

---

## 13. Circuit Switching

### Key Characteristics
- Used for **voice communication**
- A **dedicated communication path** is established between two stations through the nodes of the network
- The path/capacity stays up for the **duration of the connection**
- If there is no data being sent, capacity is **wasted**
- Requires a **dedicated channel** established before any call is made
- The channel is **reserved** between users until the connection is released
- Mainly used for voice communication requiring **real-time services without delay**

### Phases of Circuit Switching
1. **Establish** — Set up the dedicated path
2. **Transfer** — Transmit data
3. **Disconnect** — Release the path

### Duplex Allocation
- **Half duplex** → 1 channel allocated
- **Full duplex** → 2 channels allocated

### Example
- **Telephone Network**

### How It Works (User Example)
- User-A requests a dedicated channel to communicate with User-C
- During the active connection, if User-B tries to communicate with User-D or any other user, it receives a **busy signal** from the network

---

## 14. Message Switching

### Key Characteristics
- Used for **message communication** (SMS, MMS, etc.)
- Complete message is transmitted **without any break**
- **No limit on block size**
- Message is **stored and forwarded** at each node → more time required
- At any particular time, a message exists at **one location** in the network
- **No direct link** between sender and receiver
- Physical links are **allocated dynamically**

### Mechanism
- Uses **Store and Forward Switches**
- Two different messages can take two different paths simultaneously (e.g., Message 1 via A→B→E, Message 2 via C→D→E)

---

## 15. Packet Switching

### Key Characteristics
- Used for **data communication**
- Does **not require a dedicated connection**
- Useful for less time-sensitive internet data or emails
- Data is sent in small chunks called **"Packets"**
- Each packet is passed from **node to node**
- At each node, the entire packet is received, **stored briefly**, then transmitted to the next node
- **Example:** Computer-to-Computer communication

### How It Works
- User-A wants to send data to User-C; User-B wants to send data to User-D — **both can happen simultaneously**
- Information is padded with a **header** containing source and destination addresses
- Intermediate switching nodes **sniff the header** to determine routing and destination

### Difference from Message Switching
- Similar to message switching but uses **short messages** (packets)
- Any message exceeding a network-defined maximum length is **broken into shorter units (packets)** — upper limit on block size
- Each packet is transmitted individually through **virtual links made simultaneously**
- Packets exist at **many places** in the network at any given time

### Performance: Best Effort
- The network does its best to deliver the packet as fast as possible
- **No guarantees** on how fast a packet will arrive

---

## 16. Comparison: Message Switching vs. Packet Switching

| Feature | Message Switching | Packet Switching |
|---------|------------------|-----------------|
| Unit of transfer | Entire message | Fixed-size packets |
| Block size limit | No limit | Upper limit on block size |
| Storage location | One node at a time | Many nodes simultaneously |
| Speed | Slower (entire message stored at each hop) | Faster |
| Path | Dynamically allocated | Independent routing per packet |

---

## 17. Anatomy of a Packet

Every packet contains:
1. **Header address** — indicates the final destination address
2. **Sequence number** — for correct reassembly at the destination
3. **Total packet count** — so recipient knows if any packet failed to arrive
4. **Error recovery:** If a packet fails to arrive, the recipient sends a **retransmission request** to the sender

---

## 18. The Internet and Packet Switching

- The Internet uses **IP (Internet Protocol)**, which is a **packet switching protocol**
- The Internet uses **packet switching, not circuit switching**
- Circuit switching is wasteful because it dedicates an end-to-end circuit to a call
- Packet switching allows a circuit to be used for **different communications simultaneously**

---

## 19. Packet Handling: Two Approaches

Packets can be handled in two ways:

1. **Datagram**
2. **Virtual Circuit**

---

### 19.1 Datagram

- Each packet is treated **independently**
- Packets can take **any practical route**
- Packets may arrive **out of order**
- Packets may **go missing**
- It is up to the **receiver** to re-order packets and recover from missing packets
- A datagram-based network is a **true packet switched network** — no fixed path for transmitting data
- **Connection-less** service — no resources pre-reserved

#### Real-World Example
- University Wi-Fi networks use **datagram packet switching (IP)**
- Authentication may create the *appearance* of a session, but the underlying network is connectionless

### Datagram Packet Forwarding
- Devices send IP packets
- Routers forward packets **independently**
- No fixed end-to-end path is reserved
- Paths can **change dynamically**

---

### 19.2 Virtual Circuit

- A **preplanned route is established** before any packets are sent
- **Call request and call accept packets** establish connection (handshake)
- Each packet contains a **virtual circuit identifier** instead of a destination address
- **No routing decisions** required for each individual packet
- A **clear request** is sent to drop/terminate the circuit
- **Not a dedicated path** (unlike circuit switching)
- **Connection-oriented** — implemented through buffers, etc.

#### Real-World Example
- **ISP MPLS (Multiprotocol Label Switching)** links between campuses use a virtual-circuit-like path
  - MPLS is widely used by ISPs and large enterprises

---

## 20. Datagram vs. Virtual Circuit

| Feature | Datagram | Virtual Circuit |
|---------|----------|----------------|
| Connection | Connectionless | Connection-oriented |
| Path | No fixed path | Pre-established path |
| Routing | Per packet | Per connection (circuit ID used) |
| Resource reservation | None | Buffers, etc. reserved |
| Packet order | May arrive out of order | Arrive in order |
| Overhead per packet | Full destination address | Virtual circuit identifier only |
| Example | University WiFi, Ethernet LAN | ISP MPLS links |

---

## 21. Real-World Examples by Technology

| Technology | Type |
|-----------|------|
| Wi-Fi in labs | Datagram |
| Ethernet in buildings | Datagram |
| ISP MPLS link between campuses | Virtual-circuit-like path |

> **Ethernet** is a wired LAN technology that enables computers and other devices to send and receive data in the form of **frames** over network cables.
>
> **MPLS (Multiprotocol Label Switching)** is widely used by ISPs and large enterprises.

---

## 22. Chapter References

- **Book 1**, Chapter 1
- **Book 2**, Chapter 7
