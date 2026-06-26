# Computer Networks — Week 16: Network Performance

---

## Determining What to Measure

Before any measurements can take place, one must determine what to measure.

**Network Provider**
- Is the design meeting requirements for various traffic classes or applications?
- How can I demonstrate the superior performance of my service offering?

**Customer**
- Is Network Performance meeting the agreed Performance Agreement?

**3rd Parties**
- What does "the net" look like? Hot spots?
- What Network Provider is "best"?

---

## Key Metrics for Network Performance Evaluation

- Latency
- Throughput
- Response time
- Arrival rate
- Utilization
- Bandwidth
- Loss
- Routing
- Reliability

---

## Four Major Concepts

1. Latency (travel time)
2. Throughput (actual transfer rate)
3. Packet loss
4. Jitter (delay variation)

---

## Bandwidth

### Definition

Bandwidth has two meanings:

1. **Bandwidth in Hertz** — refers to the range of frequencies in a composite signal or the range of frequencies that a channel can pass.
2. **Bandwidth in bits per second** — refers to the speed of bit transmission in a channel or link. Often referred to as Capacity.

### Bandwidth in Hertz (Hz)

- Hertz measures the frequency of a signal or the width of a communication channel.
- Indicates how much of the frequency spectrum is available.
- Used for analog communication channels: traditional landline telephone, FM radio broadcast, older analog TVs, frequency range, wireless spectrum (e.g. bandwidth of 20 MHz), and channel capacity in terms of frequencies.

### Bandwidth in bps

- bps measures the amount of digital data transmitted per second.
- Applies to: internet speed, data communication rate, network throughput, download speed, upload speed, etc.
- If a link is 100 Mbps, it can transmit 100 million bits per second.

### Relationship between Hz and bps

- A communication channel with more frequency bandwidth (Hz) can usually carry more data (bps).
- In computer networks, the term "bandwidth" is commonly used informally to mean transmission speed.

### Measuring Bandwidth

| Unit of Bandwidth   | Abbreviation | Equivalence                                      |
|---------------------|--------------|--------------------------------------------------|
| Bits per second     | bps          | 1 bps = fundamental unit of bandwidth           |
| Kilobits per second | kbps         | 1 kbps = ~1,000 bps = 10^3 bps                 |
| Megabits per second | Mbps         | 1 Mbps = ~1,000,000 bps = 10^6 bps             |
| Gigabits per second | Gbps         | 1 Gbps = ~1,000,000,000 bps = 10^9 bps         |
| Terabits per second | Tbps         | 1 Tbps = ~1,000,000,000,000 bps = 10^12 bps    |

---

## Network Performance

Two primary characteristics:
- **Delay**
- **Throughput**

---

## Delay

- How long does it take for a bit of data to travel across the network from one computer to another.
- Measured in seconds or fractions of seconds.

### Types of Delay

**Propagation Delay**
- Time to travel across a medium (time for a signal to travel).

**Switching Delay**
- Time required for a network component (hub, bridge, packet switch) to forward data.

**Access Delay**
- Time required to get control of the medium.
- Occurs because multiple devices may be trying to use the same medium at the same time.
- Represents the waiting time before transmission begins.
- Access delay is noticeable when crowded Wi-Fi networks feel slow even with good bandwidth.

**Queuing Delay**
- Time required in packet switches waiting in the device buffer.

**Processing Delay**
- Time to process a packet.

---

## Solved Examples

### Example 1 — Required Bit Rate for Text Download

**Problem:** Assume we need to download text documents at the rate of 100 pages per second. What is the required bit rate of the channel? (A page is an average of 24 lines with 80 characters in each line.)

**Solution:** Assuming one character requires 8 bits (ASCII):

```
100 x 24 x 80 x 8 = 1,636,000 bps = 1.636 Mbps
```

```
Mbps = bits per second (bps) / 1,000,000
```

Note: 1 Mbps is the rate of transfer of one million bits per second.

---

### Example 2 — Bit Rate for a Digitized Voice Channel

**Problem:** A digitized voice channel is made by digitizing a 4-kHz (1 kilo hertz = 1000 Hz) bandwidth analog voice signal. We need to sample the signal at twice the highest frequency (two samples per hertz). Each sample requires 8 bits (bit depth). What is the required bit rate?

**Solution:**

```
2 x 4000 x 8 = 64,000 bps = 64 kbps
```

Note: kHz measures frequency (how many times per second a sound wave oscillates). bps → kbps (divide by 1000).

---

## Throughput

- The rate at which data can be sent through the network.
- The throughput capability of the underlying hardware is called bandwidth.
- Speed can be a synonym for throughput.

### Throughput and Delay Relationship

- If a packet switch has a queue of packets waiting when a new packet arrives, the new packet will be placed at the end of the entire queue and must wait while the switch forwards previous packets.
- Throughput and delay are not completely independent.
- As traffic in a computer network increases, delays increase.
- A network operating at close to 100% of its throughput capacity experiences severe delay.

---

## Packet Reordering

- Packets arrive at the destination but not in the order they were sent.

**Example sequences:**
- `1, 2, 3, 7, 8, 9, 10, 11, ...` — Loss, no reordering
- `1, 2, 3, 7, 8, 9, 4, 5, 6, 10, 11, ...` — Reordering

**Explanation:**
- Packets 7, 8, 9 arrive early; packets 4, 5, 6 arrive late.
- Reordering extent is measured by the number of early packets.
- Receivers must perform work to restore order by buffering packets.

**Definition:** Packet n is designated reordered when its sequence number is less than the Next Expected threshold (set by the arrival of a previous packet).

---

## Failure Recovery Time

Five possible recovery scenarios:

1. **Lost packets** — Packets fail to arrive at the destination.
2. **Induced delay** — Packets arrive but with an added delay.
3. **Duplicate packets** — The same packet is received more than once.
4. **Out-of-order packets** — Packets arrive in an incorrect sequence.
5. **Errored packets** — Packets arrive but contain errors.

---

## Network Performance and Efficiency

### Importance

Effective network performance improves user satisfaction. It is important for:
- Employees in an organization
- E-commerce website customers
- Clients of a financial institution
- Users of educational content

### Network Efficiency

Network efficiency refers to how effectively a computer network utilizes its available resources to transfer data from source to destination. It:
- Delivers data quickly
- Uses bandwidth effectively
- Minimizes delays and errors
- Provides reliable communication

---

## Network Performance Measurement

### Ongoing Monitoring

Performance monitoring on an ongoing basis ensures network quality.

### Traffic Measurement

- Measures the amount and type of traffic on a particular network.
- Enables effective bandwidth management.

### Network Monitoring

- A system that constantly monitors a network for slow or failing systems.
- Notifies the network administrator about availability (percentage of a specified time interval during which the system was available for normal use).
- Network administrator also keeps an eye on link utilization (throughput for the link expressed as a percentage of the access rate).

---

## Types of Measurement Tools

### Passive Measurement Tools

- Monitor existing applications on the network to gather data on performance metrics.
- Ensure no network disruption.
- No additional traffic is introduced for monitoring.
- Provide a realistic assessment of the user experience.
- Used for: link usage, throughput, intrusion detection.
- Drawback: processing overhead (in terms of CPU utilization).

### Active Measurement Tools

- Require an additional level of data traffic.
- Must be scheduled appropriately to minimize impact on existing network traffic.
- Performed by sending test traffic into the network.
- Generate test packets periodically or on-demand.
- Measure the performance of test packets to produce statistics.
- Test packets can be blocked by firewalls or processed at low priority by routers.
- Check: delay, packet loss, and network availability.

---

## Key Performance Metrics — Detailed

### Latency

- The amount of time it takes for data to travel from one defined location to another (sender to receiver).
- Also referred to as delay; unit: milliseconds (ms).
- Ideally, the target latency of a network is as close to zero as possible.
- Variables that can increase latency: packet queuing in switched networks, refractive index of fiber optic cabling.

**Example 1:** If a packet takes 40 ms to reach the destination, Latency = 40 ms.
- Video conferencing requires low latency.
- Online gaming requires very low latency.

---

### Packet Loss

- Number of packets transmitted from one destination to another that fail to transmit.
- Quantified by capturing traffic data on both ends, then identifying missing packets and/or retransmission of packets.
- Causes: network congestion, router performance, and software issues.
- Detected by users in the form of voice and streaming interruptions or incomplete transmission of files.
- **Retransmission** is a method utilized by network protocols to compensate for packet loss. However, it can aggravate network congestion due to increased traffic volume.
- Response time analysis can be done to identify the root cause. A review of response time for TCP connections can pinpoint which applications are contributing to the bottleneck.

**Example 2:**
```
Packets Sent     = 1000
Packets Received = 980
Packet Loss Rate = [(1000 - 980) / 1000] x 100 = 2%
```

---

### Throughput

- Commonly defined as the amount of material or items passing through a particular system or process.
- For network performance measurement: the amount of data or number of data packets that can be delivered in a pre-defined time frame.
- Actual amount of useful data successfully delivered.

**Example 3:**
```
Bandwidth              = 100 Mbps
Actual data transferred = 75 Mbps
Throughput             = 75 Mbps
```
Since throughput is lower than bandwidth, some capacity is being lost due to overhead or congestion.

---

### Bandwidth (as a Performance Metric)

- Usually measured in bits per second.
- Amount of data that can be transferred over a given time period.
- Bandwidth is a measure of capacity rather than speed.
- Analogy: A bus may be capable of carrying 100 passengers (bandwidth), but the bus may actually only transport 85 passengers (throughput).
- A fiber connection with 1 Gbps bandwidth can theoretically transmit 1,000,000,000 bits/sec.

---

### Jitter

- Variation in time delay for data packets sent over a network.
- Jitter is the variation in packet arrival times.
- Identifies disruption in the normal sequencing of data packets.
- Jitter is related to latency; it expresses itself in increased or uneven latency between data packets.
- Can disrupt network performance, leading to packet loss and network congestion.
- Some level of jitter is to be expected and can usually be tolerated.

**Example 4:**
```
Packet 1 = 20 ms
Packet 2 = 25 ms
Packet 3 = 18 ms
Packet 4 = 30 ms
```
Significant variation in arrival times = High jitter.

High jitter affects: voice calls, video conferencing, live streaming.

---

### Latency vs. Throughput

- **Throughput** is a measurement of actual system performance — data transfer over a given time.
- **Latency** is a measurement of the delay in transfer time.
- Latency has a direct impact on throughput.
- Throughput is measured in units completed, which is inherently influenced by latency in the system.

---

## Network Efficiency — Calculations

### Example 5

A network link can transmit 100 Mbps, but only 80 Mbps of useful data reaches users because of protocol overhead and retransmissions.

```
Network Efficiency = (Useful Throughput / Available Bandwidth) x 100
                   = (80 / 100) x 100
                   = 80%
```

### Example 6

```
Bandwidth  = 200 Mbps
Throughput = 160 Mbps

Efficiency = (160 / 200) x 100 = 80%
```

---

## Throughput vs. Useful Throughput (Goodput)

| Metric              | Definition                                                                 |
|---------------------|----------------------------------------------------------------------------|
| Throughput          | Total rate at which data is successfully transferred over the network      |
| Useful Throughput   | Rate at which actual user/application data is delivered                    |

```
Useful Throughput (Goodput) = Throughput - Overhead - Retransmissions
```

Throughput measures the total amount of data delivered per second, including:
- Application data
- Protocol headers (TCP, IP, Ethernet)
- Acknowledgments
- Retransmissions

Useful throughput excludes:
- Protocol overhead
- Retransmissions
- Control packets

### Example 7

A network transfers 100 Mbps of data consisting of:
```
80 Mbps  — user data
15 Mbps  — headers and control information
5 Mbps   — retransmitted packets

Throughput = 100 Mbps
```

### Example 8

```
Total throughput  = 100 Mbps
Headers           = 15 Mbps
Retransmissions   =  5 Mbps

Useful Throughput = 100 - 15 - 5 = 80 Mbps

Throughput        = 100 Mbps
Useful Throughput =  80 Mbps
```

### Example 9 — Downloading a File

```
Network bandwidth        = 1 Gbps
Measured throughput      = 900 Mbps
TCP/IP overhead          =  50 Mbps
Retransmissions          =  30 Mbps

Useful Throughput = 900 - 50 - 30 = 820 Mbps
```
The user effectively receives data at 820 Mbps, even though the network is carrying 900 Mbps.

### Applications of Useful Throughput

- Streaming video quality depends on useful throughput.
- Cloud file uploads depend on useful throughput.
- Web page loading speed depends on useful throughput.

---

## Challenges in Network Performance

- Network performance measurement solutions should be designed with the user in mind.
- Slight degradation or latency may be acceptable.
- Finding acceptable limits is key to establishing relevant testing and monitoring.

**Packet Shaping**
- A method used to prioritize packet delivery for different applications.
- Ensures adequate bandwidth is consistently allocated to the most important categories.

**File Compression**
- Decreases the bandwidth and memory consumed.

**Real-time detection**
- If problems with servers, routing, delivery, or bandwidth can be detected in real time, practical solutions and preventative strategies become possible.

---

## Factors Affecting Network Efficiency

**Congestion**
- Too many devices compete for network resources.

**Protocol Overhead**
- Headers, acknowledgments, and control messages consume bandwidth.

**Transmission Errors**
- Corrupted packets require retransmission.

**Distance**
- Longer distances increase propagation delay.

**Network Hardware**
- Old switches, routers, and cables can reduce performance.

**Security Mechanisms**
- Encryption and inspection may add processing delay.

---

## Application-Specific Requirements

### Online Banking
- Low latency
- High reliability
- Minimal packet loss
- Even a small delay can affect transaction processing.

### Video Streaming
- High throughput
- Low jitter
- If throughput drops below the video bit rate, buffering occurs.

### Cloud Storage / Cloud Computing
- Sufficient bandwidth
- Low latency
- Reliable connectivity
- Poor network efficiency slows file synchronization and application performance.

---

## Emerging Trends

Three major trends:
1. Mobile adoption
2. Experiment-driven decision making
3. Business Process Automation

### Mobile Connectivity

- IT networks allow employees to work from anywhere.
- On average, employees now work 47 hours per week.
- Security must not be compromised.

**Why extended working hours per week?**
- Digital connectivity (smartphones, emails, messaging apps, remote work tools).
- Increased competition in global markets demanding higher productivity and faster response times.
- Knowledge-based jobs measured by outcomes, not hours.
- Hybrid and remote work leading to unintentional extended working hours.
- Economic pressures: high living costs driving overtime, freelance work, and online side businesses.

### Experiment-Driven Decisions

- Based on data collected by testing and retesting different variables.
- Aims for optimal results.
- Software today enables businesses to base decisions on real-time changes.
- Better innovation expected as businesses take risks with experiments.

### Business Process Automation (BPA)

- Networks are the backbone of automated business activities.
- Automated systems continuously exchange data between applications, servers, databases, cloud platforms, and IoT devices, generating large volumes of network traffic.
- Examples: Customer Relationship Management (CRMs), AI chatbots, online transaction systems.
- Results in greater dependence on cloud networks.

**Examples of automation today:**
- Automated banking
- Online shopping
- Industrial robotics
- Logistics tracking
- Real-time decision making

---

## Technologies Required Today

### Network Technologies

- **Fiber optic networks**
- **5G** — higher speed, lower delay, better support for modern smart devices
- **Software Defined Networking (SDN)** — network control is separated from physical network devices, creating a programmable, flexible network where traffic is managed dynamically through a central controller
- **Edge computing**

### Edge Computing

Data processing happens closer to where the data is generated, instead of sending everything to a central cloud or remote data center.

**How it works:**
1. Data is generated from a device (sensor, phone, camera, machine).
2. Processed by a nearby edge device (router, local server).
3. Only important data is sent to the cloud.

**Benefits:**
- Low latency
- Reduced bandwidth usage
- Real-time processing enabling real-time decisions

**Use cases:**
- Smart cities — traffic lights adjust based on real-time traffic flow information
- Industrial automation — quick fault detection in factories
- Autonomous vehicles — instant decisions on braking and steering without waiting for a cloud response
- Healthcare — wearable devices monitor patients and generate alerts
- IoT devices — sensors process data locally and send summaries

---

## Security Requirements

### Threats

- Cyberattacks
- Ransomware
- Unauthorized access

### Modern Network Security Relies On

- Firewalls
- VPNs
- Encrypted communication
- Intrusion detection systems
- Zero trust security

### Zero Trust Security

- No implicit trust — every request must be verified.
- Continuous verification.
- Least privilege access (minimum access granted to complete a job).

**Used in:** banking systems, remote work environments, government systems, defense networks, cloud services.
