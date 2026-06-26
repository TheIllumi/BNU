# Computer Networks (CSC-203 / CSC-332) — All Quizzes
**Instructor: Shazia Rizwan | Spring 2026**

---

## Table of Contents

1. [Quiz 1 — Sample (Section A) with Solution](#quiz-1--sample-section-a-with-solution)
2. [Quiz 1 — Sample 2 (Section A) with Solution](#quiz-1--sample-2-section-a-with-solution)
3. [Quiz 2 — CS S2026, Ver 1 (Section B) with Solution](#quiz-2--cs-s2026-ver-1-section-b-with-solution)
4. [Quiz 2 — CS S2026, Ver 2 (Section C) with Solution](#quiz-2--cs-s2026-ver-2-section-c-with-solution)
5. [Quiz 2 — MBC S2026, Marking Scheme Ver 1 (Section A)](#quiz-2--mbc-s2026-marking-scheme-ver-1-section-a)
6. [Quiz 3 — CS S2026, Marking Scheme Section A](#quiz-3--cs-s2026-marking-scheme-section-a)
7. [Quiz 3 — CS S2026, Marking Scheme Section B](#quiz-3--cs-s2026-marking-scheme-section-b)
8. [Quiz 3 — CS S2026, Marking Scheme Section C](#quiz-3--cs-s2026-marking-scheme-section-c)
9. [Quiz 4 — CS S2026, Section A (Question Only)](#quiz-4--cs-s2026-section-a-question-only)
10. [Quiz 4 — CS S2026, Section B (Question Only)](#quiz-4--cs-s2026-section-b-question-only)

---

## Quiz 1 — Sample (Section A) with Solution

**Course:** Computer Networks (CSC-203)
**Quiz:** Quiz-1 (Spring 2026)
**Date:** 7th April 2026
**Time:** 20 mins | **Marks:** 15
**Section:** A

---

### Question 1 — [CLO2] `[3, 2]`

You are given an IP address: **150.1.2.3**. Find the Class, default subnet mask, number of usable hosts per network. Can you efficiently use it for 600 hosts? Justify your answer.

#### Solution

- **Class:** B (150 → 128–191)
- **Default Mask:** 255.255.0.0
- **Hosts:** 65,534 &nbsp;(65,536 − 2 = 65,534) &nbsp; `[3]`
- **Efficiency:** Not efficient because only 600 needed, but 65K available → Lots of wastage `[2]`

---

### Question 2 — [CLO2] `[2, 6, 2]`

You are given the network: **192.168.40.0/24**. Divide this network into at least 5 equal-sized subnets. Each subnet must support at least 25 hosts. All subnets must be equal in size.

- Find the new subnet mask (in binary) and clearly show the working on borrowing bits.
- List the first 5 subnets, and for each provide:
  - Network address
  - First usable IP
  - Last usable IP
  - Broadcast address
- Identify **one inefficiency** in your design.

#### Solution

Borrow **3 bits** from the host part.

- Original: /24 → New network block: **/27**
- New Subnet Mask: `11111111.11111111.11111111.11100000` → **255.255.255.224** `[2]`
- Total subnets = 2³ = **8** possible subnets
- Host bits left = 5 → Total host addresses = 2⁵ = 32 → Usable = **30 hosts** (≥ 25 ✓)
- Block size = **32**

| Subnet | Network Address | First Usable | Last Usable | Broadcast |
|--------|----------------|--------------|-------------|-----------|
| 1 | 192.168.40.0 | 192.168.40.1 | 192.168.40.30 | 192.168.40.31 |
| 2 | 192.168.40.32 | 192.168.40.33 | 192.168.40.62 | 192.168.40.63 |
| 3 | 192.168.40.64 | 192.168.40.65 | 192.168.40.94 | 192.168.40.95 |
| 4 | 192.168.40.96 | 192.168.40.97 | 192.168.40.126 | 192.168.40.127 |
| 5 | 192.168.40.128 | 192.168.40.129 | 192.168.40.158 | 192.168.40.159 |

**Inefficiency:** We only needed 5 subnets but created 8 → 3 subnets unused → address wastage. `[2]`

---

## Quiz 1 — Sample 2 (Section A) with Solution

**Course:** Computer Networks (CSC-203)
**Quiz:** Quiz-1 (Spring 2026)
**Time:** 20 mins | **Marks:** 15
**Section:** A

---

### Question 1 — [CLO2] `[2, 3]`

Given the default mask **255.255.255.0** for an IP address, identify the class and number of total hosts. Use an IP address as an example and clearly identify the network as well as broadcast address.

#### Solution

- **Class:** C (default mask 255.255.255.0 → Class C)
- **Total Hosts:** 8 bits for hosts = 2⁸ = 256 → Usable = **254** (excluding network & broadcast) `[2]`

**Example 1:** `[3]`

| Field | Value |
|-------|-------|
| IP Address | 192.168.1.10 |
| Class | C |
| Default Mask | 255.255.255.0 (/24) |
| Network part | First 24 bits → 192.168.1 |
| Host part | Last 8 bits → .10 |
| Network Address | 192.168.1.0 (all host bits = 0) |
| Broadcast Address | 192.168.1.255 (all host bits = 1) |
| Usable Hosts | 192.168.1.1 → 192.168.1.254 (254 hosts) *(optional)* |

**Example 2:**

| Field | Value |
|-------|-------|
| IP Address | 192.168.10.20 |
| Class | C |
| Default Mask | 255.255.255.0 (/24) |
| Network part | First 24 bits → 192.168.10 |
| Host part | Last 8 bits → .20 |
| Network Address | 192.168.10.0 |
| Broadcast Address | 192.168.10.255 |
| Usable Hosts | 192.168.10.1 → 192.168.10.254 (254 hosts) *(optional)* |

---

### Question 2 — [CLO2] `[1, 1, 1, 5, 2]`

You are given the network: **192.168.10.0/24**. Divide this network into at least 5 subnets.

- What will be the new subnet mask?
- How many subnets will you actually get?
- How many usable hosts per subnet?
- List all subnet addresses.
- Considering the requirements, do you see any problem with this division into subnets?

#### Solution

To create ≥ 5 subnets → borrow **3 bits** (2³ = 8 ≥ 5) `[1]`

- **New/Custom Subnet Mask:** /27 → `11111111.11111111.11111111.11100000` → **255.255.255.224** `[1]`
- Remaining host bits = 32 − 27 = 5 → Total hosts = 2⁵ = 32 → **Usable hosts = 30** `[1]`
- Block size = 256 − 224 = 32

**All Subnets** (need first 5): `[5]`

| Subnet | Address |
|--------|---------|
| 1 | 192.168.10.0/27 |
| 2 | 192.168.10.32/27 |
| 3 | 192.168.10.64/27 |
| 4 | 192.168.10.96/27 |
| 5 | 192.168.10.128/27 |
| 6 | 192.168.10.160/27 |
| 7 | 192.168.10.192/27 |
| 8 | 192.168.10.224/27 |

**Problem:** Inefficient subnetting — 3 subnets are unused → wastage of address space. `[2]`

---

## Quiz 2 — CS S2026, Ver 1 (Section B) with Solution

**Course:** Computer Networks (CSC-332)
**Quiz:** Quiz-2 (Spring 2026)
**Date:** 10th April 2026
**Time:** 20 mins | **Marks:** 15
**Section:** B

---

### Question — [CLO2] `[1, 1, 1, 4, 5, 3]`

A company has **FIVE** different departments (HR, IT, ADMIN, FINANCE, SUPPORT). The given network is **192.168.50.0/24**. They need to create subnets for all departments. The largest department needs **50 hosts**.

- Write the default Subnet Mask.
- What subnet mask should be used to create equal-size subnets?
- How many subnets will be created?
- List all subnet addresses.
- Assign subnets to each department and provide: Network address, First usable IP, Last usable IP, Broadcast address.
- If the company adds a sixth department, will your design work? If not, explain clearly.

#### Solution

- **Default Subnet Mask:** 255.255.255.0 `[1]`
- **New Subnet Mask:** /27 → `11111111.11111111.11111111.11100000` → **255.255.255.224** `[1]`
  - 3 bits borrowed → **8 subnets** possible `[1]`
- **Host bits remaining:** 5 → 2⁵ = 32 IPs → Usable = **30 host addresses**

> **Note:** Assumption: only 1 department needs 50 hosts. Since each subnet supports 30 hosts max, the largest department can be assigned **two subnets**. That consumes 6 subnets (4 for remaining depts + 2 for the largest dept). Remaining unused subnets = 8 − 6 = **2 subnets** → can accommodate a 6th department. `[3]`

**All Subnets** (192.168.50.0/24, Block size = 32): `[4]`

| Subnet | Network | First Usable | Last Usable | Broadcast | Dept |
|--------|---------|--------------|-------------|-----------|------|
| 1 | 192.168.50.0 | 192.168.50.1 | 192.168.50.30 | 192.168.50.31 | — |
| 2 | 192.168.50.32 | 192.168.50.33 | 192.168.50.62 | 192.168.50.63 | — |
| 3 | 192.168.50.64 | 192.168.50.65 | 192.168.50.94 | 192.168.50.95 | — |
| 4 | 192.168.50.96 | 192.168.50.97 | 192.168.50.126 | 192.168.50.127 | — |
| 5 | 192.168.50.128 | 192.168.50.129 | 192.168.50.158 | 192.168.50.159 | — |
| 6 | 192.168.50.160 | 192.168.50.161 | 192.168.50.190 | 192.168.50.191 | — |
| 7 | 192.168.50.192 | 192.168.50.193 | 192.168.50.222 | 192.168.50.223 | — |
| 8 | 192.168.50.224 | 192.168.50.225 | 192.168.50.254 | 192.168.50.255 | — |

---

## Quiz 2 — CS S2026, Ver 2 (Section C) with Solution

**Course:** Computer Networks (CSC-332)
**Quiz:** Quiz-2 (Spring 2026)
**Date:** 10th April 2026
**Time:** 20 mins | **Marks:** 15
**Section:** C

---

### Question — [CLO2] `[1, 1, 1, 4, 4, 3, 2]`

You are setting up a small company with **at least four departments**. The assigned network is: **192.168.6.0/24**. Each department needs at least **50 hosts**.

- Write the default Subnet Mask.
- What subnet mask should be used to create equal-size subnets?
- How many subnets will be created?
- List all subnet addresses.
- Assign subnets to each department and provide: Network address, First usable IP, Last usable IP, Broadcast address.
- Will this design work efficiently if the number of departments increases to five? Justify.
- Clearly write any assumption you make.

#### Solution

- **Default Subnet Mask:** 255.255.255.0 `[1]`
- **New/Custom Subnet Mask:** Borrow 2 bits → `11111111.11111111.11111111.11000000` → **255.255.255.192** (/26) `[1]`
- **Subnets created:** 2² = **4** `[1]`
- Host bits remaining = 6 → 2⁶ = 64 → Usable = **62 hosts** per subnet (≥ 50 ✓)
- Block size = 256 − 192 = 64

**All Subnets** (192.168.6.0/24): `[4]`

| Subnet | Network | First Usable | Last Usable | Broadcast |
|--------|---------|--------------|-------------|-----------|
| 1 | 192.168.6.0 | 192.168.6.1 | 192.168.6.62 | 192.168.6.63 |
| 2 | 192.168.6.64 | 192.168.6.65 | 192.168.6.126 | 192.168.6.127 |
| 3 | 192.168.6.128 | 192.168.6.129 | 192.168.6.190 | 192.168.6.191 |
| 4 | 192.168.6.192 | 192.168.6.193 | 192.168.6.254 | 192.168.6.255 |

**Fifth department:** No, this design will **not** work efficiently for 5 departments — we only have 4 subnets and all are used. A 5th subnet would require borrowing an extra bit (3 bits total → /27), but that reduces usable hosts to 30, which does **not** meet the 50-host requirement. `[3]`

**Assumption:** No department requires more than 62 IP addresses for its hosts. `[2]`

---

## Quiz 2 — MBC S2026, Marking Scheme Ver 1 (Section A)

**Course:** Computer Networks (CSC-203)
**Quiz:** Quiz-2 (Spring 2026)
**Date:** 9th April 2026
**Time:** 20 mins | **Marks:** 15
**Section:** A

---

### Question 1 — [CLO2] `[3, 2, 10]`

A student was asked to divide the network **192.168.60.0/24** into at least 5 equal-sized subnets, each supporting at least 25 hosts. The student prepared the following solution:

> **Student's (Incorrect) Solution:**
> - New subnet mask: **/26** → `192.168.60.xx000000` → 2² = **4 subnets** ← **INCORRECT**
> - Hosts per subnet = 62

| Subnet | Network | Usable | Broadcast |
|--------|---------|--------|-----------|
| 1 | 192.168.60.0 | 192.168.60.1 – 192.168.60.62 | 192.168.60.63 |
| 2 | 192.168.60.64 | 192.168.60.65 – 192.168.60.126 | 192.168.60.127 |
| 3 | 192.168.60.128 | 192.168.60.129 – 192.168.60.190 | 192.168.60.191 |
| 4 | 192.168.60.192 | 192.168.60.193 – 192.168.60.254 | 192.168.60.255 |

- Identify all mistakes in the solution.
- Provide a brief reason (one sentence) for each mistake.
- Provide the correct solution.

#### Solution / Marking Scheme

**Mistake Identified:** `[3]`

- Student borrowed **2 bits → 4 subnets**
- Requirement = **at least 5 subnets**
- **Error:** 4 < 5 → requirement not met `[2]`
- Hosts requirement (62 ≥ 25) is fulfilled, but the **number of required subnets is NOT met**

**Correct Solution:** `[10]`

- Need at least 5 → must borrow **3 bits** → 2³ = 8 subnets
- /24 + 3 borrowed bits = **/27**
- Correct Mask: `11111111.11111111.11111111.11100000` → **255.255.255.224**
- Usable hosts per subnet: 2⁵ = 32 → 32 − 2 = **30 usable** (≥ 25 ✓)
- Block size = 32

| Subnet | Network | First Usable | Last Usable | Broadcast |
|--------|---------|--------------|-------------|-----------|
| 1 | 192.168.60.0 | 192.168.60.1 | 192.168.60.30 | 192.168.60.31 |
| 2 | 192.168.60.32 | 192.168.60.33 | 192.168.60.62 | 192.168.60.63 |
| 3 | 192.168.60.64 | 192.168.60.65 | 192.168.60.94 | 192.168.60.95 |
| 4 | 192.168.60.96 | 192.168.60.97 | 192.168.60.126 | 192.168.60.127 |
| 5 | 192.168.60.128 | 192.168.60.129 | 192.168.60.158 | 192.168.60.159 |
| 6 *(if required)* | 192.168.60.160 | 192.168.60.161 | 192.168.60.190 | 192.168.60.191 |

---

## Quiz 3 — CS S2026, Marking Scheme Section A

**Course:** Computer Networks (CSC-332)
**Quiz:** Quiz-3 (Spring 2026)
**Date:** 28th April 2026
**Time:** 20 mins | **Marks:** 15

---

### Question 1 — [CLO3]

An exam question required computing the checksum for the following 16-bit words:

```
FFFF    8001    7FFE    0001
```

A student calculates the checksum to be **FFFF** before sending to the receiver.

- Verify this calculation. Show complete working at the sender side. `[4]`
- In case it is NOT correct, list the mistake and compute the correct checksum. Verify your answer at the receiver end (show complete working). `[2, 4]`
- The student argues that FFFF is all 1s, so it must be correct. Do you agree? Justify your answer. `[5]`

#### Solution / Marking Scheme

**Mistake:** Incorrect calculation of checksum due to **ignoring the additional carry** which was not wrapped around by the student.

**Correct checksum = FFFE**

**Student's reasoning is incorrect.** Getting FFFF as a checksum is **not automatically correct**. The student ignored the correct handling of **carry wraparound**. FFFF is the expected result **only after verification** at the receiver end, not necessarily as the checksum value itself.

---

## Quiz 3 — CS S2026, Marking Scheme Section B

**Course:** Computer Networks (CSC-332)
**Quiz:** Quiz-3 (Spring 2026) – Section B
**Date:** 5th May 2026
**Time:** 20 mins | **Marks:** 15

---

### Question 1 — [CLO3]

A sender wants to transmit the following data using 16-bit words and the **1's complement checksum** method:

```
7A2C   91F5   3E10   8B77   6D3A
```

- Compute the checksum to be transmitted. `[4]`
- Show the final transmitted message. `[2]`

At the receiver end, suppose the received data is:

```
7A2C   91F5   3E10   8D77   6D3A   (along with correct checksum)
```

- Verify whether an error is detected or not. `[5]`
- Identify and briefly explain why this error is or is not detected. `[4]`

#### Solution / Marking Scheme

**Final transmitted data:**
```
7A2C   91F5   3E10   8B77   6D3A   BD1B
```

**Error Detection:**
Yes, the error **has been detected**. At the receiver end, one word was changed during transmission — **8D77** instead of the original **8B77** sent by the sender. This 1-bit change altered the sum.

The checksum mechanism works here: even though only a subtle 1-bit error was induced during transmission, the receiver can detect that the data has an error before it is used.

---

## Quiz 3 — CS S2026, Marking Scheme Section C

**Course:** Computer Networks (CSC-332)
**Quiz:** Quiz-3 (Spring 2026) – Section C
**Date:** 5th May 2026
**Time:** 20 mins | **Marks:** 15

---

### Question 1 — [CLO3]

A sender wants to transmit the following data using 16-bit words and the **1's complement checksum** method:

```
7A2C   91F5   3E10   8B77   6D3A
```

- Compute the checksum to be transmitted. `[4]`
- Show the final transmitted message. `[2]`

At the receiver end, suppose the received data is:

```
7A2C   91F5   3E10   8B77   6D8A   (along with correct checksum)
```

- Verify whether an error is detected or not. `[5]`
- Briefly explain why this error is or is not detected. `[4]`

#### Solution / Marking Scheme

**Final transmitted data:**
```
7A2C   91F5   3E10   8B77   6D3A   BD1B
```

**Error Detection:**
Yes, the error **has been detected**. At the receiver end, one word was changed during transmission — **6D8A** instead of the original **6D3A** sent by the sender. This 1-bit change altered the sum.

The checksum mechanism works here: even though only a subtle 1-bit error was induced during transmission, the receiver can detect that the data has an error before it is used.

---

## Quiz 4 — CS S2026, Section A (Question Only)

**Course:** Computer Networks (CSC-332)
**Quiz:** Quiz-4 (Spring 2026)
**Date:** 19th May 2026
**Time:** 20 mins | **Marks:** 15
**Section:** A

---

### Question — [CLO3]

A sender wants to send the following data polynomial:

**D(x) = x⁹ + x⁸ + x⁶ + x⁴ + x³ + x + 1**

The generator polynomial: **G(x) = x⁴ + x + 1**

During transmission, the **last bit (rightmost) of the CRC code gets flipped**.

- Convert the polynomials into binary. `[2]`
- Find the CRC remainder with complete working. `[4]`
- Construct the transmitted frame. `[1]`
- Construct the received frame. `[1]`
- Verify the data by applying the CRC technique at the receiver side with complete working. `[4]`
- Comment on your finding. `[3]`

---

## Quiz 4 — CS S2026, Section B (Question Only)

**Course:** Computer Networks (CSC-332)
**Quiz:** Quiz-4 (Spring 2026)
**Date:** 15th May 2026
**Time:** 20 mins | **Marks:** 15
**Section:** B

---

### Question 1 — [CLO3]

Suppose the following **8-bit data words** are being transmitted from location-A using **Even parity**:

```
1 0 1 1 0 1 1 0
1 1 0 0 1 0 0 1
0 1 1 0 1 1 0 0
1 0 0 1 1 1 0 1
```

- Show complete working on the sender end using **2-D parity checking**. `[4]`
- Write the finally transmitted data (9-bit words). `[1]`
- Suppose two bits got flipped: one at **row 2, column 5** and the other at **row 3, column 6** during transmission. Write the received data words at Location-B. `[2]`
- Apply 2-D parity checking at the receiver end. `[3]`
- List the possible error positions. `[2]`
- What is expected at the receiver end after detecting error(s), if any? `[3]`
