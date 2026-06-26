# Computer Networks - Week 15

---

## Cloud Computing

Availability of computing services -- servers, storage, databases, networking, software, analytics and more -- over the Internet ("the cloud").

Companies offering these computing services are called **cloud providers** and typically charge for cloud computing services based on usage.

---

## Characteristics of Cloud Computing

### Shared Resources and Resource Management

1. Cloud uses a shared pool of resources.
2. Uses Internet technology to offer scalable and elastic services.
3. The term **"elastic computing"** refers to the ability of dynamically and on-demand acquiring computing resources and supporting a variable workload.
4. Resources are metered and users are charged accordingly.
5. It is more cost-effective due to optimized resource utilization.
6. Data is stored in the "cloud", in certain cases closer to the site where it is used.
7. Data appears to the users as if stored in a location-independent manner.
8. The data storage strategy can increase reliability, as well as security, and can lower communication costs.
9. The maintenance and security are efficiently operated by service providers.

---

## Advantages of Cloud Computing

1. Resources such as CPU cycles, storage, and network bandwidth are shared.
2. Resources can be aggregated to support data-intensive applications.
3. Data sharing facilitates collaborative activities.
4. Many applications require multiple types of analysis of shared data sets.
5. Many decisions are carried out by groups scattered around the globe.
6. Eliminates the initial investment costs for a private computing infrastructure and the maintenance and operation costs.
7. **Cost reduction:** concentration of resources creates the opportunity to pay as you go for computing.
8. **Elasticity:** the ability to accommodate workloads with very large peak-to-average ratios.
9. **User convenience:** virtualization allows users to operate in familiar environments rather than in unique environments with unique features.

---

## Types of Cloud

1. **Public Cloud** - the infrastructure is made available to the general public or a large industry group and is owned by the organization selling cloud services.
2. **Private Cloud** - the infrastructure is operated solely for an organization.
3. **Hybrid Cloud** - composition of two or more clouds (public, private, or community) as unique entities but bound by a standardised technology that enables data and application portability.
4. **Community / Federated Cloud** - the infrastructure is shared by several organizations and supports a community that has shared concerns.

---

## Application Layer

Today, most applications are networked applications -- sets of interacting programs running on two or more hosts. When a software developer writes a program, it is usually a program designed to talk to another program on a different host.

### Networked Applications

- Networked applications can use an infinite number of alternative interaction patterns.
- **Application architectures** are patterns of interactions between networked applications on different machines.

### Evolution of Application Architectures

Stand-alone programs (running on PCs and laptops) → Client/server architecture (PCs sharing processing chores with servers with WWW) → Peer-to-peer computing (client providing server capabilities to another client; no need to have and manage servers) → Distributed computing architecture (program on one machine calls programs on other machines).

---

## Types of Cloud Services

### IaaS - Infrastructure as a Service

- Provides virtual servers, storage, and networking.
- Business organizations use computing infrastructure instead of buying expensive hardware.
- Examples:
  - **Amazon Web Services EC2** (for virtual servers)
  - **Microsoft Azure Virtual Machines** (supports various OSes and scalable resources)

### PaaS - Platform as a Service

- Developers use ready-made environments to build applications.
- Examples:
  - **Google App Engine** (for developing and hosting web and mobile applications)
  - Supports programming languages like Python, Java, Go, PHP, etc.

### SaaS - Software as a Service

- Examples:
  - **Zoom Communications**
  - **Dropbox**
  - **Salesforce** (CRM platform)

---

## Deployment Models of Cloud Computing

### Public Cloud

- IT infrastructure like servers, networking, and storage resources are offered as virtual resources over the Internet.
- Resources are fully managed and made accessible by the cloud provider.
- Open to all users and organizations.
- Less usage cost as users pay for only what they use.
- Less control over data.
- Highly scalable.
- Example: Universities use public cloud.

#### Public Cloud Security

- Follows a **shared responsibility model**.
- The public cloud provider is responsible for the security **of** the cloud -- they protect the infrastructure that runs all services offered in the cloud.
- The customer is responsible for security **in** the cloud.
- The service determines the amount of configuration at the customer end.
- Some cloud computing services offer greater control and customizability but also increase the customer's security responsibility.

---

### Private Cloud

- A single organization controls and maintains the underlying infrastructure to deliver IT resources.
- Example scenario: An organization with several departments (finance, marketing) needs computing resources. In a private cloud setup, the organization purchases server hardware, maintains it in a central data center, and delivers resources to the different departments over a network. Individual teams may additionally invest in software infrastructure like operating systems or database software.
- Example: Banks using private cloud.

#### Key Properties

- Infrastructure is isolated from outside access.
- Limited scalability as infrastructure is limited.

---

### Hybrid Cloud

- A company uses both public and private cloud.
- It is an IT infrastructure design that integrates a company's internal IT resources with third-party cloud provider infrastructure and services.
- Data and applications can be stored and run across multiple environments.
- Example: Companies combining both as hybrid environments.

#### Why Organizations Adopt Hybrid Cloud

Organizations typically adopt hybrid cloud strategies to:

- Overcome private cloud limitations.
- Continue using their existing on-premises data center.
- Access the public cloud as needed.

Organizations that use a hybrid approach typically have:

- Sensitive data
- Expensive IT infrastructure
- Fluctuating workloads/requirements

#### Hybrid Cloud - Use Cases by Sector

**Banking and Financial Institutions**
- Private: Customer financial records, transaction data.
- Public: Mobile banking apps, data analytics, customer support systems.

**Universities**
- Private: Student records, exam data, internal administration data.
- Public: Online learning resources, collaboration tools, research computing (e.g., MS Teams).

**Healthcare Organizations**
- Private: Patient medical records, internal hospital databases.
- Public: Appointment portals, analytics.

**Government Organizations**
- Private: National databases, defense systems, citizens' data.
- Public: Online services (tax services, passport services, smart city platforms), digital portals.

**Retail and E-commerce Companies**
- Private: Payment processing, inventory details/databases.
- Public: Online shopping websites, customer analytics, promotional campaigns.

---

## More Examples of Cloud in Practice

- **Netflix** using cloud for global streaming.
- **Spotify** scaling music services worldwide.
- **Zoom Communications** managing remote meetings.

---

## Understanding Data Packets

### OSI Layers and Encapsulation

Each layer wraps the original data in its own Header and Trailer. This process is called **encapsulation**.

---

### Layer 7 - Application Layer

- Contains raw data of the user, e.g., an email or a web page request.
- PDU: **Data / Message**

---

### Layer 6 - Presentation Layer

- Data is translated, encrypted, and compressed here so the receiving device can interpret it correctly.
- PDU: **Data / Message**

---

### Layer 5 - Session Layer

- Starts, maintains, and terminates the communication connection/sessions between systems.
- PDU: **Data / Message**

---

### Layer 4 - Transport Layer

- Data from the upper layers is broken down into smaller, manageable chunks.
- Adds a **port number**.
- PDU: **Segment** (TCP) and **Datagram** (UDP)

**Port Number:**
- A 16-bit logical identifier used to direct network traffic to the correct application or service on a device.
- IP address routes data to the device itself; the port number ensures the data reaches the correct program.

---

### Layer 3 - Network Layer

- Handles routing and logical addressing.
- Adds a Source and Destination **IP Address**.
- Routers use this information to determine the best path for the data.
- PDU: **Packet** (TCP) / **Datagram** (UDP)

---

### Layer 2 - Data Link Layer

- Responsible for node-to-node delivery.
- Wraps the packet with Source and Destination **MAC Addresses**.
- Adds an error-checking Trailer called the **Frame Check Sequence (FCS)** to ensure the data was not corrupted in transit.
- PDU: **Frame**

**Note:** MAC address identifies the physical hardware while an IP address identifies the logical network address of a device. MAC spoofing is possible -- mostly temporary or done on a random basis.

---

### Layer 1 - Physical Layer

- Converts the 1s and 0s of the data Frame into physical electrical, optical, or radio signals.
- Moves the raw bits over the physical medium (cables or Wi-Fi).
- PDU: **Bits**

---

## Summary: OSI Encapsulation at a Glance

| Layer | Name             | PDU           | Key Addition                          |
|-------|------------------|---------------|---------------------------------------|
| 7     | Application      | Data/Message  | Raw user data                         |
| 6     | Presentation     | Data/Message  | Encryption, compression, translation  |
| 5     | Session          | Data/Message  | Session management                    |
| 4     | Transport        | Segment/Datagram | Port numbers                       |
| 3     | Network          | Packet/Datagram  | Source & Destination IP addresses  |
| 2     | Data Link        | Frame         | MAC addresses, FCS trailer            |
| 1     | Physical         | Bits          | Electrical/optical/radio signals      |
