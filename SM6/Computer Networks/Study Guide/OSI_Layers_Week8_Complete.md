# Computer Networks – Week 8: OSI Layers (Complete Notes)

---

## OSI Model Overview

The **Open System Interconnection Reference Model (OSI Model)** is an abstract description for layered communications and computer network protocol design. It divides network architecture into **seven layers**.

Developed in **1978** by the International Standards Organization (ISO), the OSI framework has two major components:

- An abstract model of networking — the **Basic Reference Model** (seven-layer model)
- A set of specific protocols

### Why Do We Need Layers?

- Break complex systems into manageable parts
- Easier troubleshooting
- Vendor interoperability

### The Seven Layers

```
7 - Application
6 - Presentation
5 - Session
4 - Transport
3 - Network
2 - Data Link
1 - Physical
```

### Mnemonics to Remember

- **Top → Bottom:** All People Seem To Need Data Processing
- **Bottom → Top:** Please Do Not Throw Sausage Pizza Away
- **Another option:** All Professors Should Teach Networking Daily Please

---

## Layer 7 – Application Layer

- The layer **closest to the end user** — both the OSI application layer and the user interact directly with the software application
- Apps you use daily work at this layer

### Functions

#### 1. Identifying Communication Partners

Before sending data, the system must identify the target device or service using:

- Domain names (e.g., `google.com`)
- IP addresses
- Application identifiers (like user accounts in apps)

#### 2. Determining Resource Availability

The application checks whether:

- The destination device is online
- The service (server) is available
- Required resources (CPU, memory, bandwidth) are sufficient

> **Example:** On WhatsApp — if your friend is offline, the message shows a single tick. If the server is down, the message won't send. Calling someone — if their phone is off, you can't connect.

#### 3. Synchronizing Communication

Ensures that both sender and receiver:

- Follow the same rules/protocols
- Exchange data in the correct order
- Maintain proper timing

> **Example:** While chatting on WhatsApp — messages appear in correct order, typing indicators ("typing…", "Recording…") are synchronized, and read receipts (blue ticks) are updated correctly.

### Application Layer Protocols

| Protocol | Full Name                     |
| -------- | ----------------------------- |
| HTTP     | Hypertext Transfer Protocol   |
| FTP      | File Transfer Protocol        |
| SMTP     | Simple Mail Transfer Protocol |

---

## Layer 6 – Presentation Layer

Also called the **syntax layer**.

- Establishes a context between Application Layer entities
- Responsible for **encryption and decryption** of data
- Responsible for **compression and expansion** of data
- Defines the format in which data is to be exchanged between the two communicating entities
- Provides freedom from compatibility problems

### Functions

1. **Translation** – Converts data formats between different systems
2. **Encryption** – Secures data before transmission
3. **Compression** – Reduces data size for efficient transfer
4. **Security** – User authentication

---

## Layer 5 – Session Layer

- Controls the **dialogues (connections)** between computers
- Establishes, manages, and terminates connections between local and remote applications
- Manages the **mode of communication**: full-duplex, half-duplex, or simplex
- Manages sessions (start, pause, resume, end)
- Manages recovery using **checkpoints**

### Communication Modes

| Mode            | Description                                              | Example                                                                  |
| --------------- | -------------------------------------------------------- | ------------------------------------------------------------------------ |
| **Simplex**     | One-way only, no feedback possible                       | Keyboard to computer, live TV broadcast, sensor sending data to a server |
| **Half-Duplex** | One side transmits at a time; avoids collision/confusion | Classroom discussion                                                     |
| **Full-Duplex** | Both sides communicate simultaneously                    | Voice/Video calls on WhatsApp, phone calls, Zoom meetings                |

### Session Layer Features

#### Checkpointing

- Inserts checkpoints during long data transfers
- Allows resuming from the last checkpoint in case of failure instead of restarting everything
- **Example:** For a 100MB file, checkpoints at 25MB, 50MB, 75MB. If failure occurs at 60MB → resume from 50MB, not from 0.

#### Adjournment

- Temporarily pauses a session without ending it
- **Example:** While uploading a file, internet disconnects briefly → session is paused, not terminated.

#### Termination

- Cleanly ends communication
- Ensures that both sides agree communication is over and resources are released
- **Example:** Ending a call on WhatsApp, logging out of a website.

#### Restart

- Resumes session after failure using checkpoints
- File download stops at 70% → resumes from last checkpoint
- Common in download managers and cloud uploads (e.g., IDM – Internet Download Manager)
- _May not be needed for small file downloads, stable internet, or one-time quick downloads_

---

## Layer 4 – Transport Layer

- Provides **transparent transfer of data** between end users
- Provides reliable data transfer services to the upper layers
- Controls the reliability of a given link through **flow control**, **segmentation/desegmentation**, and **error control**

### Key Responsibilities

- Ensures data units are delivered **error free**
- Ensures data units are delivered **in sequence**
- Ensures there is **no loss or duplication** of data units
- Provides **connectionless or connection-oriented** service
- Provides connection management
- The transport layer header contains a **segment number** (for sequencing)
- Responsible for connection between two end ports (establish, transfer, release)

### Segmentation & Desegmentation

- Large data is divided into **segments**
- Each segment is sent separately
- At the receiver → segments are **reassembled** (desegmentation)
- **Example:** Sending a large video → divided into small packets → reassembled at receiver

### Flow Control

- Controls the speed of data transmission
- Prevents overwhelming at the receiver end
- **Example:** A slow mobile phone receiving data from a fast server → Transport Layer slows down the sender

### Error Control

- Detects lost or corrupted data
- Requests **retransmission**
- Resend request for the lost data packet or all data

### Connection Control

| Type    | Description                             | Used In                                    |
| ------- | --------------------------------------- | ------------------------------------------ |
| **TCP** | Connection-oriented (reliable)          | Web, email (HTTP/HTTPS, downloading files) |
| **UDP** | Connectionless (fast but less reliable) | Video streaming, gaming, live calls        |

---

## TCP – Transmission Control Protocol (Reliable Communication)

### How TCP Works

**Step 1 – Connection Setup (3-Way Handshake)**

1. PC A → Server B: "Can we communicate?" **(SYN)**
2. Server B → PC A: "Yes, ready!" **(SYN-ACK)**
3. PC A → Server B: "Let's start!" **(ACK)**

**Step 2 – Data Transfer**

- Data is broken into segments
- Each segment has a sequence number

**Step 3 – Acknowledgment**

- Server sends ACK after receiving each segment
- Segment 1 received → ACK sent
- Segment 2 lost → no ACK sent

**Step 4 – Retransmission**

- Sender detects missing ACK → resends segment 2

**Step 5 – Order Guarantee**

- Even if segments arrive out of order, TCP rearranges them

### TCP Summary

- ✔ Reliable delivery
- ✗ Extra overhead (ACKs, retransmissions)
- ✗ Slower but accurate
- **Examples:** Opening a website (HTTP/HTTPS), downloading a file from a server

---

## UDP – User Datagram Protocol (Fast Communication)

### How UDP Works

- **No connection setup** – PC A just starts sending data
- Data sent as **datagrams**
- No sequence tracking (or minimal)
- **No Acknowledgment** – Server does NOT send ACKs
- **No Retransmission** – If a packet is lost → it is ignored

### UDP Summary

- ✔ Faster
- ✔ No delay due to retransmission
- ✗ Possible data loss
- **Examples:** Live video lectures (Zoom, MS Teams), online gaming (real-time actions)

---

## TCP vs UDP – Key Comparison

| Feature         | TCP                       | UDP                           |
| --------------- | ------------------------- | ----------------------------- |
| Connection      | Connection-oriented       | Connectionless                |
| Reliability     | Reliable                  | Unreliable                    |
| Speed           | Slower                    | Faster                        |
| Order Guarantee | Yes                       | No                            |
| Retransmission  | Yes                       | No                            |
| Use Cases       | Web, email, file download | Streaming, gaming, live calls |

> **Key Point:** TCP controls the network for reliability. UDP trusts the network for speed.

### YouTube Video Example

| Scenario | Behavior                                                                                     |
| -------- | -------------------------------------------------------------------------------------------- |
| **TCP**  | Every frame must arrive correctly. If one packet is missing → resend → causes buffering      |
| **UDP**  | Missing packets are ignored. Video continues smoothly. Maybe a slight glitch, but no pause ✔ |

> That's why **streaming prefers UDP**.

---

## Transport vs Network Layer

| Layer               | Role                                                  |
| ------------------- | ----------------------------------------------------- |
| **Network Layer**   | Gets the data to the correct **network**              |
| **Transport Layer** | Delivers it to the correct **destination end system** |

The Transport Layer ensures **reliable, ordered, and correct delivery** of data between applications on different devices.

---

## Layer 3 – Network Layer

- Performs **network routing functions**
- Reports delivery errors
- **Routers** operate at this layer — sending data throughout the extended network and making the Internet possible
- Decides which **path (route)** the data packet should take
- Ensures it reaches the correct **destination address (IP address)**

### How It Works

1. Checks destination IP
2. Chooses the best route via routers
3. Forwards packets step-by-step until they reach the server

### Routers at the Network Layer

Routers:

- Read the destination IP
- Decide the next hop
- Forward the packet

> The Network Layer finds the **best path** and delivers packets from one network to another using **IP addresses**.

---

## Layer 2 – Data Link Layer

- Delivers data **within the same network**
- Uses **MAC addresses** to identify devices
- Ensures **error-free delivery** between directly connected devices
- Works at the **hardware level** (needs a hardware identifier — MAC address)

> **IP address** gets the data to the correct network, but **MAC address** delivers it to the exact device inside that network.

### Data Link vs Transport Layer

| Data Link Layer                            | Transport Layer                                                        |
| ------------------------------------------ | ---------------------------------------------------------------------- |
| Moves data between **neighboring** devices | Ensures complete and reliable delivery between **sender and receiver** |

### Data Frame

- Created at the Data Link Layer
- Contains:
  - Source MAC address
  - Destination MAC address
- Used for delivery within a **local network**
- **Switches** read frames

---

## Layer 1 – Physical Layer

- Provides the **physical interface** for transmission of information
- Defines rules by which **bits are passed** from one system to another on a physical communication medium
- Covers all **mechanical, electrical, functional, and procedural** aspects for physical communication
- Responsible for actually sending **raw bits (0s and 1s)** as signals over a medium
- Does **not understand data** — only signals

### Physical Layer Specifications

- Voltage levels (how 0 and 1 are represented)
- Timing of voltage changes
- Physical data rates
- Maximum transmission distances
- Physical connectors (RJ45, etc.)
- Cables (Ethernet, fiber optic)

### How It Works (File Sending Example)

**Sending Side:**

1. Other layers prepare the data
2. Data Link Layer creates a frame
3. Physical Layer converts frame into bits (0s and 1s)
4. Converts bits into electrical signals (in a cable)
5. Transmits them over the wire

**Receiving Side:**

- Signals → Bits → Data (reverse process)

---

## Data Encapsulation Summary

When data is sent down the OSI stack:

| Layer               | Action                    | Unit Created     |
| ------------------- | ------------------------- | ---------------- |
| **Transport Layer** | Breaks data into segments | **Segment**      |
| **Network Layer**   | Adds IP address           | **Packet**       |
| **Data Link Layer** | Adds MAC address          | **Frame**        |
| **Physical Layer**  | Sends raw bits            | **Bits/Signals** |

### Device Summary

| Device       | Operates At                    |
| ------------ | ------------------------------ |
| **Routers**  | Network Layer (reads packets)  |
| **Switches** | Data Link Layer (reads frames) |

---

_End of Week-8 OSI Layers Notes_
