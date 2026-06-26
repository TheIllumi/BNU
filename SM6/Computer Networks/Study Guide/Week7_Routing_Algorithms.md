# Computer Networks — Week 7
## Routing Algorithms

---

## 1. What is a Routing Algorithm?

- A **routing algorithm** determines good paths (routes) from senders to receivers through the network of routers.
- A **"good" path** = one that has the **least cost**.
- Routing algorithms that compute these paths are of fundamental importance.

---

## 2. Graph Model

- A **graph** is used to formulate routing problems.
- A graph **G = (N, E)** consists of:
  - **N** — a set of nodes
  - **E** — a collection of edges
- Each edge is a pair of nodes from N.
- In the context of network-layer routing:
  - **Nodes** represent **Routers** (points at which packet-forwarding decisions are made)
  - **Edges** represent the **physical links** between routers

### Edge Cost

- Each edge has a **value representing its cost**.
- An edge's cost may reflect:
  - Physical length of the link
  - Link speed
  - Monetary cost associated with a link
- For any edge **(x, y)** in E, the cost is denoted as **c(x, y)**.
- If the pair (x, y) does **not** belong to E → **c(x, y) = ∞**
- Only **undirected graphs** are considered → **c(x, y) = c(y, x)**
  - However, in an algorithm, cost may be considered different in different directions.
- A node **y** is said to be a **neighbor** of node **x** if (x, y) belongs to E.

---

## 3. Goal of a Routing Algorithm

- Identify the **least costly paths** between sources and destinations.
- A **path** in G = (N, E) is a sequence of nodes.
- The **cost of a path** = sum of all the edge costs along the path.

---

## 4. Finding Cost of a Path

- Between any two nodes x and y, there are typically **many paths**.
- Each path has a particular cost.
- One or more of these paths is a **least-cost path**.
- The **least-cost problem** → Find a path between source and destination that has the **least cost**.

### Example

- Least-cost path from **u → w**: **(u, x, y, w)**
- **Path Cost = 3** (1 + 1 + 1)

### Shortest Path

- If **all edges have the same cost**, the least-cost path is also the **shortest path** (fewest number of links between source and destination).

---

## 5. Exercise — Ex-1

- **Find the least-cost path from node u to z** (using the standard 6-node graph with nodes u, v, w, x, y, z).
- There are **17 possible paths** between u and z.
- Computing this manually is an example of a **centralized routing algorithm** — run in one location (e.g., your brain).

---

## 6. Centralized Routing Algorithm (Link-State)

### Definition

- Computes the least-cost path using **complete, global knowledge** about the network.
- Takes **connectivity between all nodes** and **all link costs** as inputs.
- Algorithms with global state information → called **Link-State (LS) algorithms**.
- Must be aware of the cost of **each link** in the network.

### How It Works

1. All routers send their network information (topology, link costs) to a **central controller**.
2. The controller computes the best paths (often using **Dijkstra's Algorithm**).
3. Routes are **distributed back to routers**.

### Real-World Example — OSPF

- **Link-State Routing → OSPF (Open Shortest Path First)**
- OSPF is a link-state **Interior Gateway Routing Protocol (IGP)** designed for IP networks.
- Specifically designed to route traffic **within a single Autonomous System (AS)**.
- Does **not** handle routing policies between organizations.
- An **Autonomous System (AS)** = a network under one administrative control (e.g., a university, company, or ISP).

### Advantages

- Accurate routing decisions (global view)
- Optimal paths are usually found

### Disadvantages

- Single point of failure
- High overhead (needs full network info)
- Less scalable for very large networks

---

## 7. Decentralized Routing Algorithm (Distance-Vector)

### Definition

- The calculation of the least-cost path is carried out in an **iterative, distributed manner** by the routers.
- **No node** has complete information about the costs of all network links.
- Each node begins with only knowledge of the costs of its **own directly attached links**.
- Through an iterative process of calculation and exchange of information with **neighboring nodes**, each node gradually calculates the least-cost path.
- Example algorithm: **Distance-Vector (DV) algorithm**

### How It Works

- Routers exchange information **only with neighbors**.
- Each router updates its **routing table iteratively**.
- No global knowledge of the entire network.

### Real-World Example — RIP

- **Distance Vector Routing → RIP (Routing Information Protocol)**
- Used to exchange routing information within **small to medium-sized IP networks**.

### Advantages

- No single point of failure
- Scales better in large/distributed networks
- Simpler to implement

### Disadvantages

- **Slower convergence**
- May suffer from **routing loops**
- Problems like **count-to-infinity**

### Count-to-Infinity Problem

- Occurs when routers continuously increase the hop count to a destination that is **no longer reachable**, instead of quickly realizing the destination is down.
- Routers keep "counting" upward (1, 2, 3, …) toward infinity because they **mistakenly believe a path still exists**.

| Network Behavior           |
|----------------------------|
| Routers rely on neighbors  |
| Route becomes invalid      |
| Keep increasing hop count  |
| Slow convergence           |

---

## 8. Alternate Classification: Static vs. Dynamic

### Static Routing Algorithm

- Routes change **very slowly over time**, often as a result of **human intervention** (e.g., manually editing link costs).
- **Characteristics:**
  - Routes are manually configured by the network administrator
  - No automatic updates
  - Routes are predefined
  - Simple to understand and implement
  - No routing protocol required
  - Predictable behaviour

- **Disadvantages:**
  - Not scalable for large networks
  - No automatic adaptation to failures
  - High administrative effort

- **Example Use Case:**
  - A university lab with 20–30 computers, 1 router connected to the internet, no frequent network changes.
  - Router configuration: all traffic → send to ISP router (default route).
  - Military/banking systems where route changes must be controlled.
    - No automatic updates from unknown routers.
    - Reduces risk of routing attacks.

### Dynamic Routing Algorithm

- Routing paths change as **network traffic loads or topology change**.
- Can run either **periodically** or in **direct response** to topology or link cost changes.
- More **responsive** to network changes.

- **Routing Protocols Used:**
  - **RIP** — Routing Information Protocol (distance-vector)
  - **OSPF** — Open Shortest Path First (link-state, finds best path within an AS)
  - **BGP** — Border Gateway Protocol (constructs an autonomous systems graph based on information exchanged between BGP routers)

- **Advantages:**
  - Automatically handles failures
  - Scalable for large networks
  - Less manual configuration

- **Disadvantages:**
  - Higher CPU and memory usage (CPU computes and updates routes)
  - More complex
  - Possible security risks

- **CPU in a Router Calculates:**
  - Shortest paths
  - Best routes
  - Cost/metrics

- **Real-World Analogy:** Dynamic routing is like **Google Maps** — automatically recalculates based on current conditions.

- **Real-World Examples of Dynamic Routing:**
  - Opening a website like Google or YouTube — data travels across:
    - Your university network
    - ISPs like PTCL (to ensure uninterrupted internet service)
    - Data centers and clouds (AWS, Google Cloud, etc.)
    - 4G and 5G mobile networks (switching between towers continuously)
    - Multinational companies (international presence)

- **Why We Use Dynamic Routing:**
  - Servers are constantly added/removed
  - Load balancing is required
  - Failures must be handled instantly
  - Fastest available path must be calculated
  - High availability must be ensured

---

## 9. Alternate Classification: Load-Sensitive vs. Load-Insensitive

### Load-Sensitive Algorithm

- **Link costs vary dynamically** to reflect the current level of congestion in the underlying link.
- A **high cost** → the link is currently congested.
- The routing algorithm tends to choose routes **around congested links**.

### Load-Insensitive Algorithm

- A link's cost does **not** explicitly reflect its current (or recent past) level of congestion.
- **Today's Internet routing algorithms** (RIP, OSPF, BGP) are **load-insensitive**.

### Why Not Load-Sensitive?

**If routing decisions changed based on traffic load:**
- Routes would keep changing rapidly.
- Routes constantly flipping → **oscillations** (constant switching: A → B, B → A …)
- Network becomes **unstable**.

**Technical Reasons:**
- To be load-sensitive, routers would need:
  - Continuous measurement of traffic on all links
  - Frequent updates to all routers → huge CPU and memory overhead
  - This creates **huge control overhead and consumes bandwidth**
- By the time load info is shared:
  - It is already **outdated**
  - Decisions are based on **old data**

**Particularly bad for:**
- Video calls
- Streaming
- Real-time applications

---

## 10. Summary Table

| Classification | Type A | Type B |
|---|---|---|
| **By knowledge** | Centralized (Link-State / LS) | Decentralized (Distance-Vector / DV) |
| **By adaptability** | Static | Dynamic |
| **By load** | Load-Sensitive | Load-Insensitive |

---

## 11. Book Reference

- **Chapter 5**
- *Computer Networking: A Top-Down Approach* — James Kurose & Keith W. Ross
