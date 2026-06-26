# Computer Networks — Week 1: Introduction

**Instructor:** Shazia Rizwan
**Email:** shazia_rizwan@bnu.edu.pk
**Book Reference:** Chapter 1

**Google Classroom Codes:**
| Section | Code |
|---------|------|
| Sec-A | n4m5bcic |
| Sec-B | 233pkym4 |
| Sec-C | cyvy7dcd |

---

## Division of Marks

| Component | Marks |
|-----------|-------|
| Quiz | 15 |
| Assignments | 10 |
| Mid Term Tests (2) | 30 |
| Final Exam | 45 |
| **Total** | **100** |

---

## Recommended Books

- **Computer Networking, A Top-Down Approach** — James F. Kurose and Keith W. Ross, 8th Edition
- **Computer Networks and Internets** — Douglas E. Comer, 6th Edition
- Soft copies will be posted in Google Classroom

---

## Important Topics to be Covered

- Intro to the concept of networking
- Internetworking
- Network standards
- ISO & OSI (The OSI layering model — the Open Systems Interconnection Model)
- Understanding internet
- Web protocols
- Transport vs Network layers
- Congestion control, avoidance and recovery
- Addressing schemes
- IPv4 → IPv6
- Routing algorithms
- Network Management protocols
- Wireless networks
- Cellular networks
- Latest trends in computer networks

---

## Why Networks?

### -1: Apps You Love

Every app you love — Instagram, Google, Netflix — works because of networks you cannot see. By the end of this course, you'll understand what's happening behind the screen.

---

### -2: A Living Network

Networks exist in biology:

- **Nervous system** → neurons + synapses = packet-switched signals
- **Blood circulation** → arteries, veins = high-capacity links
- **Hormonal system** → slow, delayed signaling (high latency, low bandwidth)

Biological failure analogies:
- If routing fails in your nervous system → **paralysis**
- If congestion happens in blood vessels → **heart attack**
- Synapses: allow neurons to communicate with each other and integrate information from different regions of the brain

---

### -3: Ant Colonies & Bee Hives

- No central server. No boss.
- **Ants** communicate via pheromone trails
- **Bees** share info through waggle dance
- Ants solved distributed systems long before humans invented routers

#### Pheromone Trails
- When ants find food, they secrete an invisible chemical called "trail pheromone" as they return to the nest
- This trail leads directly from the nest to the food source
- Other worker ants follow the trail right to the food
- Each worker then reinforces the trail on the way back

#### Waggle Dance
- A communication behavior in honeybees
- A dancing bee moves in a straight line and then in a semicircle to convey information about the **distance and direction** of a food source to other colony members

---

### -4: Cities & Networks

- **Road networks** → congestion, bottlenecks
- **Electric grids** → cascading failures
- **Water supply** → pressure & flow control
- **Gas pipelines** → secure transmission

> Can a city survive if even one of these networks collapses?

---

### -5: Financial Systems

- ATM → Bank → Clearing house → Bank
- Credit card authorization happens in **milliseconds**
- Stock trading relies on **microsecond latency**
- Your money doesn't move. **Messages about your money move.**

---

### -6: Historical Networks

- Social networks
- Postal system
- Trade routes (Silk Road)
- Telegraph networks

> The Internet didn't invent networking. It just made it **faster and global.**

---

### -7: Digital Life

One minute without networks:
- No mobile network
- No internet
- No GPS
- No banking
- No emergency services

> Is this still modern life — or survival mode?

> Wherever there is life, coordination, or intelligence → there is a network.

---

## Computer Network vs Internet

| Term | Definition |
|------|------------|
| **Network** | System for connecting computers using a transmission technology. The computers can communicate with each other by sending and receiving data. |
| **Internet** | Set of networks connected by routers that are configured to pass traffic among any computers attached to any network in the set. |

---

## Networks Today

Networks are part of:
- Businesses
- Homes
- Government
- Education field

The Internet has grown into a communication system that reaches all countries of the world. Many users have high-speed Internet access through cable modems, DSL, optical fiber, or wireless technologies.

---

## The Internet: Evolution

**Originally:** Desktop computers + servers transmitting web pages and emails.

**Today:** Smartphones, laptops, tablets, TVs, gaming consoles, home security systems, home appliances, watches, eye glasses, cars, traffic control systems, and much more.

---

## IoT, IoE, and IIoT

| Term | Definition |
|------|------------|
| **IoT** (Internet of Things) | Network + things (any physical object that generates data) |
| **IoE** (Internet of Everything) | Network + things + people + data + processes |
| **IIoT** (Industrial Internet of Things) | A network of intelligent devices connected to form systems that monitor, collect, exchange and analyze data |

> Number of devices connected to the Internet in 2030 is expected to reach **50 billion**, compared to approximately 8 billion population of the world today.

---

## End Systems

- End systems are connected via a network of **communication links** and **packet switching**
- Communication links are made up of different types of physical media:
  - Coaxial cable
  - Copper wire
  - Optical fiber
  - Radio spectrum
- Different links can transmit data at **different transmission rates**

---

## Internet Service Providers (ISPs)

End systems access the Internet through ISPs. Types include:
- Residential ISPs (local cable or telephone companies)
- Corporate ISPs
- University ISPs
- WiFi ISPs (airports, hotels, coffee shops, public places)
- Cellular data ISPs (mobile access for smartphones and other devices)

ISPs that provide access to end systems must also be **interconnected**.

---

## Protocols

> Protocols control the sending and receiving of information within the Internet.

### TCP/IP

- **IP (Internet Protocol):** Specifies the format of packets sent and received among routers and end systems. Obtains the address to which data is sent. The set of rules governing the format of data sent via the internet or local network.
- **TCP (Transmission Control Protocol):** Responsible for data delivery once the IP address has been found.

Everyone must agree on what each protocol does so that people can create systems and products that **interoperate**.

### Human Protocol vs Network Protocol

**Human Protocol:**
- Person A sends: *"Hi"*
- Person B replies: *"Hi"*
- Person A sends: *"Got the time?"*
- Person B replies: *"2:00"*

**Network Protocol:**
- Client sends: TCP connection request
- Server replies: TCP connection reply
- Client sends: `GET http://www.pearsonhighered.com/cs-resources/`
- Server replies: `<file>`

In human protocols, there are specific messages we send and specific actions we take in response. If one entity understands the concept of time and the other does not, the protocol won't interoperate and no useful work can be accomplished. In networking — it takes two (or more) communicating entities running the **same protocol** to accomplish a task.

### Network Protocol Entities

In a network protocol, the entities exchanging messages and taking actions are **hardware or software components** — for example: computer, smartphone, tablet, router, or other network-capable device.

- **Congestion-control protocols** in end systems control the rate at which packets are transmitted between sender and receiver
- **Protocols in routers** determine a packet's path from source to destination

---

## Types of Networks by Size

### LAN — Local Area Network
- Occupies a smaller area: a room, a floor, or a building
- Also have WLANs (Wireless LANs)
- Examples: home WiFi network, a business office, group of buildings

### WAN — Wide Area Network
- Occupies larger areas: cities and countries
- Example: the Internet

### MAN — Metropolitan Area Network
- Covers a larger area by connecting LANs
- Size is larger than LANs and smaller than WANs
- Covers the area of a city or town
- Example: all university libraries in Lahore connected together

LAN & WAN are compared by: speed of transmission, bandwidth, security, reliability, management, and standards.

---

## Network Topology

**Topology** = physical and logical layout of the network

- **Physical layout** refers to the connected devices and nodes
- **Logical topology** focuses on the pattern of data transfer between network nodes

### Bus Topology
- All nodes are connected to a single cable called a **"backbone"**
- A LAN topology
- If the backbone is broken, the **entire segment fails**

### Ring Topology
- Device connections create a **circular data path**
- Each networked device is connected to **two others**, like points on a circle

### Star Topology
- All nodes are **individually connected to a central connection point** — like a hub or a switch
- The central hub is usually a fast, self-contained computer responsible for routing all traffic to other nodes

### Mesh Topology
- There is **no central connection point**
- Each node is connected to at least one other node and usually to more than one
- Each node is capable of sending and receiving messages from other nodes
- Nodes act as **relays**, passing on a message towards its final destination

### Hybrid Topology
- A combination of two or more topology types
- Most common examples: **Star-Ring** and **Star-Bus** networks
- In large networks, the star bus topology is combined with the linear bus
- The linear bus provides a **backbone** that connects multiple stars

---

## Transmission Mode

> "Transmission Mode is used to define the **direction of the signal flow** between the linked devices."

Three types:

```
Transmission Modes
├── Simplex
├── Half-Duplex
└── Full-Duplex
```

### Simplex Mode
- Communication is **unidirectional**
- Only one of the two stations can transmit; the other can only receive
- Examples:
  - Radio, TV (receive data but cannot transmit back)
  - Data transmission from computer to printer
  - Keyboard, mouse, joystick → computer
  - Loud speaker
  - Fire alarm system
  - TV and remote

### Half-Duplex Mode
- Each station can **both transmit and receive but not at the same time**
- When one device is sending, the other can only receive and vice versa
- Full channel capacity is allocated to whichever entity is transmitting at a specific time
- Examples:
  - One-lane road with two-directional traffic
  - Internet surfing
  - Walkie Talkies

> **Note:** WiFi is half duplex — if a client is sending data to the AP (Access Point), the AP cannot also send data to the same or any other client at the same time. For example, if you are downloading a file and sending an email at the same time, these two processes happen in turns — but the lag goes unnoticed because the time difference is very small.

### Full-Duplex Mode
- Both stations can **transmit and receive simultaneously**
- Like a two-way street with traffic flowing in both directions at the same time
- The sharing can take place in two ways:
  1. The link contains two physically separate transmission paths: one for sending, one for receiving
  2. The capacity of the channel is divided between signals traveling in opposite directions
- Examples:
  - Audio calls on telephones (you can talk and hear at the same time)
  - Remote desktop connection (send and receive data between PCs on the same network)
  - Telephone Networks
  - Wired Ethernet (a device can send and receive / upload and download simultaneously)

---

## Internet Domain Names

- Internet address names are strictly controlled so no one could add a computer to the Internet with the same address as another computer
- Address name has two parts: **computer name** and its **domain**
  - Format: `computer.domain`
  - Some addresses: `computer.computer.computer.domain`
  - Example: `www.bnu.edu.pk`
  - Example: `www.kelley.indiana.edu` (Web server for the Kelley School of Business at Indiana University)

### Common U.S. Domain Names

| Domain | Meaning |
|--------|---------|
| EDU | Educational institution, usually a university |
| COM | Commercial business |
| GOV | Government department or agency |
| MIL | Military unit |
| ORG | Nonprofit organization |

### Country Domain Names

As networks in other countries were connected to the Internet, they were assigned their own domain names:

| Domain | Country |
|--------|---------|
| CA | Canada |
| AU | Australia |
| UK | United Kingdom |
| DE | Germany |

### New Top-Level Domains (Business-Specific)

| Domain | Meaning |
|--------|---------|
| AERO | Aerospace companies |
| MUSEUM | Museums |
| NAME | Individuals |
| PRO | Professionals such as accountants and lawyers |
| BIZ | Businesses |

---

## Components of Networks

| Component | Description |
|-----------|-------------|
| **Server** | Stores data or software that can be accessed by clients. Several servers may work together over the network with a client to support a business application. |
| **Client** | The input–output hardware device at the user's end of a communication circuit. Provides users with access to the network and the data and software on the server. |
| **Circuit** | The pathway through which messages travel — a copper wire, fiber-optic cable, or wireless transmission. Many devices perform special functions such as switches and routers. |

### Peer-to-Peer Networks
- Some networks are designed to connect a set of similar computers that **share data and software with each other**
- The computers function as **equals**, rather than relying on a central server
- A network does not need a server

---

## Types of Networks

### Intranet
- A LAN that uses the same technologies as the Internet (e.g., Web servers, Java, HTML)
- Open **only to those inside the organization**
- Some pages on a Web server may be open to the public; some may be on an intranet and therefore hidden from those connecting from the Internet
- Sometimes provided by a completely separate Web server hidden from the Internet
- Example: an intranet for the IT Department at BNU with information on faculty expense budgets and class scheduling in the current semester

### Extranet
- Also uses the same technologies as the Internet
- Open for **users outside the organization** who access it over the Internet
- Can provide access to information services, inventories, and internal organizational databases — provided only to customers, suppliers, or those who have paid for access
- Access control methods: passwords, smart cards
- Example: many universities provide extranets for Web-based courses so that only enrolled students can access course materials and discussions

---

## Network Standards

- Standards are necessary in almost every business and public service entity
- Historical example: the transmission of electric current was not standardized until the end of the nineteenth century — customers had to choose between Thomas Edison's **direct current (DC)** and George Westinghouse's **alternating current (AC)**
- **Primary reason for standards:** Ensure that hardware and software produced by different vendors can work together
- Without networking standards, it would be difficult to share information
- Standards mean customers are **not locked into one vendor** — they can buy hardware and software from any vendor whose equipment meets the standard
- The use of standards makes it much easier to develop software and hardware that link different networks

---

## ISO — International Organization for Standardization

- One of the most important standards-making bodies
- Makes **technical recommendations** about data communication interfaces
- Website: [www.iso.org](http://www.iso.org)
- Based in **Geneva, Switzerland**
- Membership is composed of the national standards organizations of each ISO member country

---

## Keeping Up with Technology

- The data communications and networking arena **changes rapidly**
- It is therefore important for network managers to keep up with these changes
- For a network to operate, many different standards must be used simultaneously
- Either the sender and receiver of a message must use the same standards, or there are devices between the two that **translate** from one standard to another
- Networks often use software and hardware designed for different standards — a lot of translation is done

---

## Wireless LAN and BYOD

- Mobile devices (smartphones, tablets) have prompted employers to allow employees to bring these devices to work and use them to access data such as work email
- This movement is called **Bring Your Own Device (BYOD)**
- Employers need to add or expand their **Wireless Local Area Networks (WLANs)** to support all these new devices

### Security with BYOD

- Employees can access not only email but also critical company assets such as information about clients, suppliers, or sales
- Employers need to manage access to company applications for BYOD carefully
- Two main approaches:

| Approach | Description |
|----------|-------------|
| **Native Apps** | Requires an app to be developed for each application for every potential device (iPhone, Android, Windows) |
| **Browser-Based (Responsive Design / HTML5)** | Does not create an app; employees access the application through a Web browser |

Both approaches have their pros and cons.

---

## Massively Online

### Gaming
- Massively multiplayer online games (e.g., **World of Warcraft**) allow you to play with thousands of players in real time

### Education
- Today, education is also massively online
- Platforms: **edX, Khan Academy, Lynda.com, Code Academy** — offer thousands of education modules for children and adults
- **MOOC (Massive Open Online Courses):** Enable students who otherwise wouldn't have access to elite universities to get top knowledge without paying full tuition
- Offered free of charge (and sometimes for credit) by: Stanford, UC Berkeley, MIT, UCLA, Carnegie Mellon

### Politics
- Candidates reach out to voters not only through Facebook but also through Reddit and Google Hangouts
- Massively online allows activists to reach masses of people in a very short period of time

---

## Future Need

- Not only engineers who deeply understand the technical aspects of networks
- Also **highly social individuals** who embrace technology in creative ways to allow business to achieve a competitive edge

> **So you are in the right place at the right time!**
