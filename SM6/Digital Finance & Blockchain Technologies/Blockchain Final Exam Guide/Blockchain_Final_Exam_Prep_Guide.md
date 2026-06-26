# Blockchain Final Exam Complete Preparation Guide

> Built from your full course material: Week 1 Blockchain Overview, Week 2 Bitcoin, Week 7 (Difficulty, Target/Leading Zeros, Number of Computations), Week 9 Ethereum Basics, Week 11 Bytecode and Transactions, the Bitcoin White Paper, Quiz 1, and Assignments 1 and 2.

---

## 1. How to Use This Guide (One Day Before the Exam)

You have one night and one morning. Use the guide like this:

1. **First pass (read everything once, fast):** Read Sections 2 to 9. Do not memorise yet. Just understand the flow. Goal: nothing should feel new tomorrow.
2. **Second pass (active recall):** Cover the answers in Sections 10 and 11. Try to answer out loud. Mark anything you miss.
3. **Hands and pen (diagrams):** Practice drawing every diagram in Section 6 at least twice on paper. Diagrams are guaranteed marks in Part 2.
4. **Numbers (calculations):** Drill Sections 7 and 14 until the formulas come automatically. Part 3 is 20 marks and is the most "scoreable" part because answers are exact.
5. **Final loop:** Read Section 16 (Last-Minute Revision Sheet) right before sleeping and again 30 minutes before the exam.

**Exam weight reminder (so you spend time wisely):**

| Part | Type | Marks | Where it comes from |
|------|------|-------|---------------------|
| Part 1 | MCQs | 10 | Mostly Week 1 overview + post-midterm theory (Ethereum, smart contracts, bytecode) |
| Part 2 | Theory / diagram / conceptual | 20 | Anywhere. Must include block structure, Merkle tree, Bitcoin transaction chain |
| Part 3 | Maths / computational | 20 | Must include leading zeros, number of computations, bytecode |

**> Remember this:** Diagrams (Part 2) and calculations (Part 3) together are 40 of 50 marks. Prioritise them tonight.

---

## 2. Complete Topic-Wise Notes

Each topic below has: Definition, Why it matters, How it works, Exam points, Common mistakes, and a Memory trick.

### 2.1 Blockchain

**Definition:** A blockchain is a distributed and decentralised digital ledger that records transactions in blocks, where blocks are linked together using cryptography and maintained by a network of nodes. Once data is added, it cannot be easily altered.

**Why it matters:** It lets strangers transact and agree on a shared history without trusting any central authority (no bank in the middle).

**How it works:** Transactions are grouped into a block. Each block stores the hash of the previous block's header. This chaining of hashes means changing one old block breaks every hash after it, which is why the ledger is immutable and append-only.

**Exam points:**
- Distributed + decentralised + immutable + cryptographically linked.
- A blockchain is a "chain of blocks"; a block is a "collection of transactions".
- It is maintained collectively by nodes, with no central authority.

**Common mistake:** Saying blockchain "encrypts" data. Bitcoin does **not** encrypt transaction data. All records are public. It uses hashing and digital signatures, not encryption for confidentiality.

**Memory trick:** **D-D-I-C**: Distributed, Decentralised, Immutable, Cryptographically linked.

### 2.2 Cryptographic Hashing

**Definition:** A hash function converts an input of any length into a fixed-length output (called hash, digest, or digital fingerprint). Bitcoin uses SHA-256 (output is 256-bit / 32-byte).

**Why it matters:** Hashing gives blockchain its identity, integrity, and Proof-of-Work. It is the single most-used tool in Bitcoin.

**How it works (3 key properties):**
1. **Fixed-length output:** Any input gives a 256-bit output in SHA-256.
2. **Near-random and unique:** Change one bit of input, the output changes completely (avalanche effect). This detects tampering.
3. **One-way (trapdoor):** Easy to compute hash from input; practically impossible to get input back from hash.

A good hash is also **collision resistant** (hard to find two inputs with the same output) and computationally efficient.

**Where Bitcoin uses hashing:**
- Addresses (a shorthand of the public key).
- Transactions (identifier + integrity).
- Blocks (identifier + integrity via block header hash).
- Proof-of-Work (computational effort).

**Double hashing:** Bitcoin almost always hashes twice. For example `SHA256(SHA256(data))` for blocks and transactions, and `RIPEMD160(SHA256(pubKey))` for addresses.

**Exam points:**
- SHA-256 output = 256 bits = 32 bytes = 64 hex characters.
- Hashing is one-way; encryption is two-way.
- RIPEMD160 produces a 160-bit address.

**Common mistake:** Confusing hashing with encryption (see 2.3 table).

**Memory trick:** **FUO**: Fixed length, Unique (avalanche), One-way.

### 2.3 Hashing vs Encryption (this is Quiz 1 Question 4, 2 marks)

| Feature | Hashing | Encryption |
|---------|---------|------------|
| Direction | One-way (cannot reverse) | Two-way (can decrypt with key) |
| Output length | Fixed (e.g. 256-bit) | Varies with input |
| Key needed? | No key | Needs a key (symmetric or asymmetric) |
| Purpose in blockchain | Integrity, identity, Proof-of-Work | Confidentiality (Bitcoin does NOT use this for data) |
| Example | SHA-256, RIPEMD160 | RSA, ECDSA, AES |

**Exam-ready answer:** Hashing is a one-way function producing a fixed-length digest used for integrity and identity; you cannot recover the original input. Encryption is a two-way process using keys to convert plaintext to ciphertext and back, used for confidentiality. Bitcoin uses hashing (SHA-256, RIPEMD160) for integrity and Proof-of-Work, and digital signatures for authentication, but it does **not** encrypt transaction data because all records are public.

### 2.4 Digital Signatures

**Definition:** A digital signature certifies a message using the signer's private key, and anyone can verify it using the signer's public key.

**Why it matters:** It proves who owns the coins and stops forgery. In Bitcoin, only the owner of a private key can spend the matching coins.

**How it works:**
1. Alice hashes the message (transaction) and signs (encrypts) the hash with her **private key** to create a signature.
2. She sends the message, the signature, and her public key.
3. A verifier decrypts the signature with Alice's **public key** and compares it to the message hash. If they match, the signature is valid.

**Three guarantees (memorise these three words):**
- **Authentication:** Only the private key owner could have signed.
- **Non-repudiation:** The signer cannot later deny it.
- **Integrity:** The message was not tampered with.

**Exam points:**
- Uses public-key (asymmetric) cryptography, commonly RSA or ECDSA. Bitcoin uses ECDSA on the SECP256K1 curve.
- Quiz 1 Q3 answer: Digital signatures provide **integrity and authentication** (option b).
- Sign with private key, verify with public key.

**Common mistake:** Saying you sign with the public key. You **sign with the private key** and **verify with the public key**.

**Memory trick:** **A-N-I**: Authentication, Non-repudiation, Integrity. "Sign Private, Verify Public."

### 2.5 Public and Private Keys (Bitcoin)

**Definition:** A key pair where the private key is a secret random number, and the public key is derived from it. They are mathematically linked but you cannot go backwards.

**How it works in Bitcoin:**
1. `privateKey k (256-bit)` = a randomly generated 256-bit number.
2. `publicKey K (256-bit)` = `SECP256K1(k)` via Elliptic Curve (a one-way function).
3. `address (160-bit)` = `RIPEMD160(SHA256(K))`.

**Exam points:**
- Public key (or its hash, the address) is used to **receive**; private key is used to **send/sign**.
- Address is 160-bit, a shorter shorthand of the 256-bit public key (about 37.5% shorter).
- You cannot deduce the private key from the public key, nor the public key from the address.

**Memory trick:** "Public to receive, Private to spend."

### 2.6 Proof of Work (PoW)

**Definition:** A consensus protocol where a miner proves they spent real computational effort to earn the right to create the next block. Verifiers can confirm it with a single hash.

**Why it matters:** It is how a decentralised network agrees on one history without a central authority, and how it prevents double spending. This is Satoshi's main contribution.

**How it works:**
1. Miner collects valid transactions, builds the Merkle root, sets the timestamp.
2. The target (number of leading zeros) is set by the difficulty nBits in the header.
3. Miner picks a nonce and computes `hash = SHA256(SHA256(blockHeader))`.
4. Miner keeps changing the nonce (brute force) until the hash is less than or equal to the target (i.e. begins with the required number of zero bits).
5. The first miner to succeed broadcasts the block and earns the reward.

**Key fact:** To find a hash beginning with n zero bits, you need about `2^n` computations, because each bit has probability 0.5 and the total probability is `0.5^n`.

**Exam points:**
- PoW = "one CPU one vote." Majority decision is the longest chain.
- The average work is exponential in the number of zero bits.
- Target block time = 10 minutes (Bitcoin).
- Reward = new coins + transaction fees.

**Common mistake:** Saying the hash must "equal" the target. It must be **less than or equal to** the target.

**Memory trick:** "More zeros = smaller target = harder = more work (2^n)."

### 2.7 Double Spending

**Definition:** Trying to spend the same coins (the same UTxO) twice.

**Why it matters:** A digital coin is just data and could be copied. Preventing this without a central authority is the core problem Bitcoin solves.

**How blockchain prevents it:**
- Every input must reference a specific **unspent** output (UTxO). An output cannot be consumed twice.
- Nodes receiving both conflicting transactions discard both as invalid.
- If two valid blocks appear (a fork), the **longest chain** wins; the losing branch is discarded.
- To reverse a confirmed transaction an attacker must redo PoW for that block and all blocks after it and outpace the whole honest network (a 51% attack).

**Exam points:**
- Detected by tracing the output to see if already spent.
- "Wait for 6 blocks (about 60 minutes)" to be safe.
- An attacker can only take back his own payment, not steal others' coins (he lacks their private keys).

**Memory trick:** "Spend twice, both die." (Both conflicting transactions are rejected.)

### 2.8 Merkle Tree and Merkle Root

**Definition:** A Merkle tree (binary hash tree) summarises all transactions in a block by repeatedly hashing pairs of hashes until a single hash, the **Merkle root**, remains. Only the root is stored in the block header.

**Why it matters:** It lets you verify a transaction is in a block efficiently and lets old spent transactions be pruned to save disk space.

**How it works:**
```
hash_j   = SHA256(SHA256(tx_j))            // leaf = txID
hash_m_n = SHA256(SHA256(txID_m + txID_n)) // parent of two children
```
Pair, hash, pair, hash, until one root is left. If the number of transactions is odd, the last hash is duplicated to keep the tree balanced (even leaves).

**Exam points:**
- Merkle root sits in the **block header** (Quiz 1 Q2 answer: option c).
- To prove a transaction is included you need only `log2(N)` hashes (the Merkle path/branch).
- The interior hashes need not be stored; they can be regenerated.

**Common mistake:** Drawing the root at the bottom. The leaves (Tx0..Tx3) are at the bottom, the root is at the top, inside the header.

**Memory trick:** "Leaves at bottom, Root in the header, pair-and-hash upward."

### 2.9 Spent (STxO) and Unspent (UTxO) Transaction Outputs

**Definition:** An output of a transaction is either already spent (STxO) or still spendable (UTxO).

**How it works:**
- An output holds a value (in satoshi) and a locking script with the recipient's address.
- In Bitcoin an output is **indivisible**: it must be spent in its entirety.
- Full nodes track all UTxOs in a **UTxO set**. STxOs are not tracked (if an input cannot link to a UTxO, it is invalid).
- Your balance = sum of all UTxOs your wallet keys can spend.

**Exam points:**
- An input must reference a previous **UTxO** (via txID + output index).
- Because outputs are indivisible, extra value is returned as a **change** output.
- Any input value not accounted for in outputs becomes the **transaction fee**.

**Memory trick:** "UTxO = unspent cash you still hold; STxO = receipt already used."

### 2.10 Block Structure

**Definition:** A block has an 80-byte header plus a body of transactions.

**The 80-byte header has 6 fields:**

| Field | Size | Purpose |
|-------|------|---------|
| Version | 4 bytes | Software version |
| Previous block header hash | 32 bytes | Links to the previous block (the chain) |
| Merkle root | 32 bytes | Root of all transactions' Merkle tree |
| Timestamp | 4 bytes | Unix epoch time of creation |
| Difficulty target (nBits) | 4 bytes | PoW difficulty (leading zeros) |
| Nonce | 4 bytes | Number varied during mining |

The full block also has block size, the 80-byte header, a transaction count, and the transaction array. Each block is capped near 1 MB and the first transaction is the **coinbase** transaction.

**Exam points:** Header = 80 bytes. Block target time = 10 minutes. PoW requires the header hash to begin with n zeros.

**Memory trick:** **V-P-M-T-D-N**: Version, Previous hash, Merkle root, Timestamp, Difficulty, Nonce.

### 2.11 Transaction Chain and Transaction Data Format

**Definition:** Each transaction has one or more inputs and one or more outputs. Inputs spend earlier UTxOs; outputs create new UTxOs. Linking them forms a chain.

**Transaction (top-level) format:**

| Bytes | Field | Description |
|-------|-------|-------------|
| 4 | version | Transaction version |
| 1-9 | txInCount + txInArray | Number of inputs + the inputs |
| 1-9 | txOutCount + txOutArray | Number of outputs + the outputs |
| 4 | lockTime | Lock time or block number |

**Input (txIn) format:** referenced UTxO txID (32) + output index (4) + unlocking script length + scriptSig + sequence (4).

**Output (txOut) format:** value in satoshi (8 bytes) + locking script length + scriptPubKey.

**Key formulas:**
```
txID     = SHA256(SHA256(txRecord))      // 32-byte
outPoint = txID (32) + outputIndex (4)   // 36-byte, identifies one UTxO
```

**Exam points:**
- Unit is **satoshi** = 10^-8 BTC (1 BTC = 100 million satoshi).
- The sum of inputs can exceed the payment; the extra goes back as change.
- compactSize is a 1 to 9 byte variable-length integer used for counts/lengths.

**Memory trick:** "Inputs eat old UTxOs, outputs make new ones, txID = double hash."

### 2.12 Coinbase Transaction

**Definition:** The first transaction in every block. It pays the successful miner the reward (new coins + fees) and has no real input UTxO.

**Exam points:**
- All bitcoins ever created came from coinbase transactions.
- Its input is a special "coinbase" type with a null referenced txID and null output index; the coinbase data is arbitrary and can be used as an extra nonce.

**Memory trick:** "Coinbase = the miner pays himself, born from nothing."

### 2.13 Locking and Unlocking Scripts (P2PKH)

**Definition:** Outputs are locked by a **locking script (scriptPubKey)**. To spend, the input supplies an **unlocking script (scriptSig)** that satisfies it.

**The P2PKH (Pay-to-Public-Key-Hash) scripts:**
```
scriptSig:    <sig> <pubKeyA>
scriptPubKey: OP_DUP OP_HASH160 <addressA> OP_EQUALVERIFY OP_CHECKSIG
```

**Execution (stack-based, left to right):**
1. push `<sig>`
2. push `<pubKeyA>`
3. `OP_DUP` duplicates the public key
4. `OP_HASH160` hashes it to an address
5. push `<addressA>`
6. `OP_EQUALVERIFY` checks the hashed public key equals the stored address (fail = stop)
7. `OP_CHECKSIG` verifies the signature against the public key

**Why the public key is in scriptSig:** The output stores only the 160-bit address (a hash). You cannot get the public key from the address, but you need the public key to check the signature, so the spender provides it in the unlocking script.

**Memory trick:** "Lock asks for address match, then a valid signature: DUP, HASH160, EQUALVERIFY, CHECKSIG."

### 2.14 Difficulty Target and Leading Zeros

(Full maths is in Section 7. Summary here.)

**Definition:** The target is a 256-bit number stored compactly as 4-byte nBits. A valid hash must be less than or equal to the target. A smaller target needs more leading zeros, which is harder.

**Core formulas:**
```
target     = mantissa * 2^(8 * (exponent - 3))
difficulty = difficulty_1_target / current_target
```

**Memory trick:** "Small target, many zeros, high difficulty."

### 2.15 Hash Rate and Number of Computations

**Definition:** Hash rate P is hashes per second (one hash = one double SHA-256). Over one 10-minute block, total work is `P * 600`.

**Core formula:**
```
P * 600 = 2^n     =>     n = log(600P) / log(2)
```
Also `hashRate = difficulty * 2^32 / 600`.

**Memory trick:** "600 seconds times hash rate equals 2 to the n."

---

## 3. Week-by-Week Coverage

### Week 1: Blockchain Overview (Digital Finance and Blockchain slides)
- **Motivation:** lack of trust in centralised systems; need for transparency and immutability; reducing intermediaries; secure peer-to-peer value transfer; resistance to fraud and tampering.
- **Centralised vs decentralised ledger:** one central record-keeper vs every node keeping a synced copy.
- **Overview flow:** transaction requested -> block created -> block broadcast to every node -> nodes validate -> miners get a reward for PoW -> block added to chain -> transaction complete.
- **Components:** Digital Signatures, Hashing, Consensus Mechanism, Distributed Ledger, Network Nodes.
- **Digital signatures:** public-key crypto, private + public keys, authentication and non-repudiation, RSA or ECDSA.
- **Hashing:** fixed-size output, one-way, collision-resistant, links blocks, SHA-256. Families: MD (MD2..MD6), SHA (SHA0, SHA1, SHA2, SHA3); SHA2 has 256 and 512.
- **Consensus:** nodes agree on ledger state, prevents double spending. PoW vs PoS:
  - PoW: block probability depends on **computational power**; miners get block rewards + fees; 51% attack needs >51% of computing power.
  - PoS: block probability depends on **amount staked**; validators get fees; attacker needs >51% of staked coins.
- **Cryptocurrency:** digital currency, uses cryptography, no central authority, examples Bitcoin and Ethereum. Quiz slide answer: cryptocurrency uses **SHA256**. The "immutable / cannot be altered" concept answer is **Public Distributed Ledger**.
- **Smart contracts:** self-executing code, automatically enforce agreements, run on platforms like Ethereum, reduce intermediaries; coined by **Nick Szabo** in the 1990s; vending-machine analogy; immutable once deployed.
- **NFTs:** unique, non-interchangeable digital assets representing ownership; used in art, gaming, music, collectibles.

### Week 2: Bitcoin
- White paper by **Satoshi Nakamoto**, 31 Oct 2008; Bitcoin v0.1.0 on 9 Jan 2009.
- First truly decentralised peer-to-peer digital cash, no central authority, solves double spending via PoW.
- Uses **hashing** (identity, integrity, PoW) and **digital signatures** (authentication, non-repudiation, integrity). Does **not** encrypt data.
- Block structure (80-byte header), transaction chain, UTxO model, scripts, coinbase, mining, longest chain, 51% attack, halving, wallets, addresses (covered in detail in Sections 2 and 5).
- Reward halving: 50 (2009) -> 25 (2013) -> 12.5 (2017) -> 6.25 (2021) -> 3.125 (2024), every 210,000 blocks; cap near 21 million BTC.
- Bitcoin and Ethereum are **permissionless**.

### Week 7: Calculations (three notes)
- **Difficulty calculation:** `difficulty = difficulty_1_target / current_target`, with the simplified mantissa/exponent form.
- **Target and leading zeros:** `target = mantissa * 2^(8(exponent-3))`, then count leading hex zeros.
- **Number of computations:** `P * 600 = 2^n`, `n = log(600P)/log(2)`.
(Full worked examples in Section 7.)

### Week 9: Ethereum Basics and Smart Contracts
- Ethereum: public, decentralised, programmable blockchain ("world computer"); proposed by **Vitalik Buterin** in late 2013.
- Cryptocurrency = **Ether**; consensus in these notes = PoW; hash = **Ethash**; block time = **14 seconds** (Bitcoin = 10 minutes).
- EVM, gas, accounts (EOA vs contract), transactions vs messages, opcodes (full detail in Section 8).

### Week 11: Bytecode and Transactions
- How Solidity becomes EVM bytecode, opcodes, the stack, memory, storage, contract creation vs invocation, hand-assembled bytecode examples (full detail in Section 9).

### Bitcoin White Paper (supporting reading)
- Sections: Introduction, Transactions, Timestamp Server, Proof-of-Work, Network, Incentive, Reclaiming Disk Space, Simplified Payment Verification, Combining/Splitting Value, Privacy, Calculations, Conclusion.
- Key ideas: electronic coin = chain of digital signatures; PoW = one-CPU-one-vote; longest chain wins; attacker catch-up probability drops exponentially with z (Gambler's Ruin / Binomial Random Walk).

---

## 4. Blockchain Core Concepts (Detailed)

- **Blockchain:** distributed immutable ledger of cryptographically linked blocks (see 2.1).
- **Blocks:** containers of transactions with an 80-byte header (see 2.10).
- **Transactions:** transfers of value with inputs and outputs (see 2.11).
- **Distributed ledger:** every node holds a synced copy; no single owner.
- **Decentralisation:** no central authority; control is spread across nodes. This removes single points of failure and censorship.
- **Consensus:** the rule by which nodes agree on one valid history (PoW, PoS). Prevents double spending.
- **Immutability:** past data cannot change because each block's hash depends on the previous block's hash; changing one block invalidates all later ones.
- **Transparency:** all transactions are public and visible to anyone on the network.
- **Cryptographic hashing:** one-way fixed-length fingerprint; SHA-256 (see 2.2).
- **Digital signatures:** prove ownership and integrity; sign with private, verify with public (see 2.4).
- **Public and private keys:** asymmetric key pair; public to receive, private to spend (see 2.5).
- **Proof of Work:** spend computation to win the right to add a block (see 2.6).
- **Double spending:** spending the same coins twice; prevented by UTxO checks + longest chain (see 2.7).
- **Mining:** the PoW process of varying the nonce to find a valid hash, earning new coins + fees.
- **Nodes:** computers running the protocol. Roles: routing, full nodes (store full chain, >500 GB), mining nodes, wallets, and lightweight/SPV nodes.
- **P2P network:** peers connect directly (TCP port 8333), discover peers via DNS seeds, broadcast transactions and blocks on a best-effort basis.

---

## 5. Bitcoin Concepts (Detailed)

- **Bitcoin as a cryptocurrency:** first decentralised peer-to-peer electronic cash; secure, trusted, no double spending, sustained by mining rewards.
- **Bitcoin network:** thousands of nodes maintaining the ledger collectively without a central authority.
- **Block structure:** 80-byte header + transactions; first transaction is the coinbase (see 2.10, 2.12).
- **Transaction structure:** version, inputs, outputs, lockTime (see 2.11).
- **Inputs and outputs:** input references a UTxO and unlocks it; output creates a new UTxO with a value and locking script.
- **UTxO:** unspent transaction output, the spendable "coin" (see 2.9).
- **Spent and unspent outputs:** STxO (used, not tracked) vs UTxO (tracked in the UTxO set).
- **Coinbase transaction:** miner's reward transaction (see 2.12).
- **Transaction chain:** outputs become the inputs of later transactions, linked by txID + output index.
- **Locking script (scriptPubKey):** locks an output to a recipient's address.
- **Unlocking script (scriptSig):** signature + public key that satisfies the locking script (see 2.13).
- **Transaction verification:** trace each input to its UTxO, sum values, check funds, verify signatures, reject double spends.
- **Merkle tree / Merkle root:** binary hash tree summarising transactions; root in header (see 2.8).
- **Block header:** the 80-byte structure with 6 fields (see 2.10).
- **Nonce:** 4-byte number miners vary to find a valid hash.
- **Timestamp:** 4-byte Unix epoch creation time.
- **Previous block hash:** 32-byte link to the prior block (makes the chain).
- **Difficulty target:** nBits-encoded threshold; hash must be at or below it (see 2.14, Section 7).
- **Wallet:** application managing keys, addresses, balance, and building/signing transactions. Types: nondeterministic (JBOK) and deterministic (HD, from a seed).
- **51% attack:** controlling most computing power to rewrite recent blocks; can only reclaim own spent coins.
- **Halving:** block reward halves every 210,000 blocks until it reaches the satoshi limit (around 2140), cap near 21 million BTC.
- **Soft fork vs hard fork:** soft fork is backward compatible (no new coin); hard fork is not (creates a new coin, e.g. Bitcoin Cash).

---

## 6. Diagrams I Should Practice

Practice each on paper until you can draw it from memory. For each, I give the diagram, labels, and how to draw it under exam pressure.

### 6.1 Blockchain Structure (chain of blocks)
```
 +-----------+      +-----------+      +-----------+
 | Block j-1 | <--- | Block j   | <--- | Block j+1 |
 |  Header   |      |  Header   |      |  Header   |
 | prevHash  |      | prevHash  |      | prevHash  |
 +-----------+      +-----------+      +-----------+
```
**How to draw:** Three boxes left to right. Each box has a "prevHash" pointing back to the previous block. Arrows point backward (each block references the one before). Label the first as Genesis if asked.

### 6.2 Block Structure (this is required in Part 2)
```
                 Block j
 +-------------------------------------------+
 | HEADER (80 bytes)                         |
 |   Version | hash(header_{j-1})            |
 |   Merkle_Root | Timestamp                 |
 |   Target_Hash_nBits | Nonce               |
 +-------------------------------------------+
 | TRANSACTIONS                              |
 |        Hash01            Hash23           |
 |       /      \          /      \          |
 |   Hash0   Hash1     Hash2   Hash3         |
 |    |        |         |        |          |
 |   Tx0      Tx1       Tx2      Tx3         |
 +-------------------------------------------+
 hash(header_j) must begin with n zeros (PoW)
```
**Labels:** Header (6 fields), Merkle tree of transactions, Merkle root inside the header, "PoW requires hash begins with n zeros."
**How to draw:** Big box split into Header (top) and Transactions (bottom). In the header list the 6 fields. In the body draw a small Merkle tree. Add a note that hash(header) needs n leading zeros.
**Common mistake:** Forgetting the previous-block hash inside the header, or putting the Merkle root in the body instead of the header.

### 6.3 Merkle Tree (required in Part 2)
```
              Merkle Root
             /            \
        Hash01            Hash23
        /    \            /    \
    Hash0   Hash1     Hash2   Hash3
      |       |         |       |
     Tx0     Tx1       Tx2     Tx3

 Hash0 = SHA256(SHA256(Tx0))
 Hash01 = SHA256(SHA256(Hash0 + Hash1))
```
**How to draw:** 4 transactions at the bottom, hash each to a leaf, pair leaves and hash up, then pair again to the root. Mention: odd number of leaves -> duplicate the last one. Mention: only `log2(N)` hashes needed to prove inclusion (Merkle path).

### 6.4 Bitcoin Transaction Chain (required in Part 2; this is Quiz 1 Q5)
```
 LEGEND: [orange] = Spent (STxO)   [green] = Unspent (UTxO)
 Unit = satoshi (10^-8 BTC), 10K uniform transaction fee

 120K,A
   |
 txID_0  --> 50K,B
         --> 60K,C
              |
        txID_1 (in: txID_0,0=50K) --> 40K,D
                                         |
        txID_2 (in: txID_0,1=60K) --> 30K,E
                                  --> 20K,F
              |
   txID_3 (in: 40K,D) --> 20K,G (UTxO)   [G: 20K unspent]
                      --> 10K,D (change)  [D: 10K UTxO]
   txID_4 (in: 30K,E) --> 20K,H
   txID_5 (in: 20K,F) --> 10K,I
              |
   txID_6 (in: 20K,H from txID_4,0  AND  10K,I from txID_5,0)
          --> 20K,J (UTxO)   [J: 20K unspent, combined inputs]
```
**Quiz 1 Q5 answers:**
- (i) In txID_0, how many outputs are created? **2** (50K,B and 60K,C). Answer = **b) 2**.
- (ii) Path from 120K,A to 20K,J: `txID_0 -> txID_2 -> (txID_4 and txID_5) -> txID_6`. The 60K from txID_0 splits in txID_2 into 30K,E and 20K,F; 30K,E feeds txID_4 (gives 20K,H) and 20K,F feeds txID_5 (gives 10K,I); txID_6 combines 20K,H and 10K,I to produce 20K,J (10K is the fee).
- (iii) If txID_6 did not combine inputs, could it generate 20K,J? **No.** A single input of 20K,H minus the 10K uniform fee leaves only 10K, not enough for 20K,J. It needs the combined inputs (20K + 10K = 30K, minus 10K fee = 20K) to produce 20K,J. Combining inputs is exactly why multiple inputs are allowed.

**How to draw:** Boxes for each txID. Inside each, inputs on the left (orange/spent) and outputs on the right. Use arrows from an output to the input that consumes it. Mark final outputs (G, J, etc.) as green UTxOs.

### 6.5 UTxO Model
```
 Previous Tx                 New Tx
 +-----------+   referenced  +------------------------+
 | Output:   |  ----------> | Input: prevTxID + index |
 | value,    |   (as input) | + scriptSig (sig,pubKey)|
 | address   |              +------------------------+
 +-----------+              | Output: value, address  |  -> new UTxO
   (UTxO)                   +------------------------+
```
**How to draw:** An old output (UTxO) flows in as the input of a new transaction; the new transaction creates new outputs (new UTxOs). Note: outputs are indivisible, leftover goes back as change.

### 6.6 Locking and Unlocking Script Flow (P2PKH)
```
 scriptSig (unlock):  <sig> <pubKeyA>
 scriptPubKey (lock): OP_DUP OP_HASH160 <addressA> OP_EQUALVERIFY OP_CHECKSIG

 Stack run:
 push <sig>                     -> [sig]
 push <pubKeyA>                 -> [pubKeyA, sig]
 OP_DUP                         -> [pubKeyA, pubKeyA, sig]
 OP_HASH160                     -> [addr', pubKeyA, sig]
 push <addressA>                -> [addressA, addr', pubKeyA, sig]
 OP_EQUALVERIFY (addr'==addressA?) -> [pubKeyA, sig]
 OP_CHECKSIG (verify sig with pubKeyA) -> [TRUE]
```
**How to draw:** Two script boxes (unlock then lock). Then a stack column showing each step. Emphasise EQUALVERIFY (address match) then CHECKSIG (signature check).

### 6.7 Proof of Work Mining Flow
```
 Collect valid Tx -> build Merkle root -> assemble 80-byte header
        |
        v
   pick nonce
        |
        v
 hash = SHA256(SHA256(header))
        |
        v
  hash <= target ?  --no--> change nonce (loop)
        | yes
        v
 broadcast block -> other nodes verify (1 hash) -> add to chain -> reward
```
**How to draw:** A vertical flow with a decision diamond "hash <= target?". The "no" arrow loops back to "change nonce." The "yes" arrow leads to broadcast and reward.

### 6.8 Ethereum Smart Contract Deployment Flow
```
 Solidity (.sol)
       |  write contract in Remix IDE
       v
 Compile (Solidity compiler)  -> produces ABI + EVM Bytecode
       |
       v
 Deploy: send transaction with "to: empty/none" and data = bytecode
       |  connect wallet (MetaMask), choose network (Sepolia testnet)
       |  pay gas (get test ETH from a faucet)
       v
 EVM runs init code, RETURNs runtime bytecode -> stored at a new contract address
       |
       v
 Interact: send transactions (to: contract address) to call functions
```
**How to draw:** Vertical flow: Solidity -> Compiler -> (ABI + Bytecode) -> Deploy transaction -> EVM stores runtime code at an address -> Interact via function-call transactions. Note Remix, MetaMask, Sepolia, faucet, gas.

---

## 7. Mathematical and Computational Questions (Part 3, 20 marks)

This is the highest-value section to master. Learn the three formula families: **Target**, **Difficulty**, **Computations/Hash rate**, plus **Bytecode**.

### 7.1 Target from nBits (mantissa and exponent)

**Formula:**
```
target = mantissa * 2^(8 * (exponent - 3))
```
nBits is `0x[exponent][mantissa]`: the first byte is the exponent, the next 3 bytes are the mantissa.

**When to use:** Whenever you are given nBits (or a mantissa and exponent) and asked for the target or the number of leading zeros.

**Easy example:** nBits = `0x1d00ffff`.
- exponent = `0x1d` = 29, mantissa = `0x00ffff` = 65535.
- target = 65535 * 2^(8*(29-3)) = 65535 * 2^208.
- Hex form: `00000000FFFF0000...0000` (256-bit).
- Leading zeros: 8 hex zeros = **32 bits**. **Final answer: target = 0x00ffff * 2^208, 32 leading zero bits.**

**Medium example:** nBits = `0x1705c739`.
- exponent = `0x17` = 23, mantissa = `0x05c739` = 378681.
- target = 0x05c739 * 2^(8*(23-3)) = 0x05c739 * 2^160.
- Hex: `0000000000000000000005c739` then 160 bits of zeros.
- Leading zeros: 18 hex zeros = **72 bits**. **Final answer: target = 0x05c739 * 2^160, 72 leading zero bits.**

**Hard example (Assignment 1 Q1):** mantissa = `0x1b0404`, exponent = `0x1d` (29).
- target = 0x1b0404 * 2^(8*(29-3)) = 0x1b0404 * 2^208.
- 0x1b0404 = 1,770,500 (decimal). **Final answer: target = 0x1b0404 * 2^208 = 1,770,500 * 2^208.**
- In 256-bit hex it is `1b0404` shifted left by 208 bits (so it occupies the upper bytes, with the exact leading-zero count depending on the top byte 0x1b = 0001 1011, which has 3 leading zero bits within its nibble-byte, giving fewer leading zeros than the 0x00ffff case).

**Common mistakes:** Using `(exponent)` instead of `(exponent - 3)`; mixing decimal and hex; forgetting that each hex digit = 4 bits when counting zeros.

### 7.2 Convert nBits to Full Hex Target (Assignment 2 Q1)

**Question:** mantissa = `0x00ffff`, exponent = `0x1d`. Find full target in hex.
**Solution:**
```
target = 0x00ffff * 2^(8*(0x1d - 3)) = 0x00ffff * 2^(8*26) = 0x00ffff * 2^208
```
Multiplying by 2^208 shifts left by 208 bits = 52 hex digits. So write `00ffff` followed by 52 hex zeros, padded to 64 hex digits total:
```
00000000FFFF0000000000000000000000000000000000000000000000000000
```
**Final answer:** `0x00000000FFFF0000000000000000000000000000000000000000000000000000` (the classic difficulty-1 target). Leading zeros = 32 bits.

### 7.3 Compare Two Targets / Difficulties

**Rule:** Smaller target = harder = higher difficulty = more leading zeros.

**Assignment 1 Q2:** A: mantissa `0x00ffff`, exp `0x1d`; B: mantissa `0x00ffff`, exp `0x1c`. Which is harder?
- A target = 0x00ffff * 2^(8*(29-3)) = 0x00ffff * 2^208.
- B target = 0x00ffff * 2^(8*(28-3)) = 0x00ffff * 2^200.
- B is smaller (2^200 < 2^208). **Smaller target = harder. Final answer: B is harder.**

**Assignment 2 Q2:** A: current target = 2^230; B: current target = 2^220. Which is harder?
- 2^220 < 2^230, so B has the smaller target. **Final answer: B is harder (smaller target, more leading zeros, more work).**

**Common mistake:** Thinking a bigger exponent or bigger target means harder. It is the opposite: bigger target = easier.

### 7.4 Difficulty Calculation

**Formula:**
```
difficulty = difficulty_1_target / current_target
```
Simplified with mantissa/exponent:
```
difficulty = (mantissa_1 / mantissa) * 2^(8 * (exponent_1 - exponent))
```
where difficulty-1 is `0x1d00ffff` (mantissa_1 = 65535, exponent_1 = 29).

**Worked example (from notes):** current nBits = `0x1705c739` (mantissa = 378681, exponent = 23).
```
difficulty = (65535 / 378681) * 2^(8*(29 - 23))
           = 0.173 * 2^48
           ~ 0.173 * 2.81 * 10^14
           ~ 4.9 * 10^13
```
**Final answer: difficulty ~ 4.9 * 10^13.** (The Week 2 notes also quote 48,712,405,953,118 = 2^45.5 for a related target; the method is identical, just different inputs.)

**Easy example (Assignment 1 Q3):** difficulty_1_target = 2^224, current target = 2^220.
```
difficulty = 2^224 / 2^220 = 2^(224-220) = 2^4 = 16
```
**Final answer: difficulty = 16.**

**Medium example (Assignment 1 Q4):** difficulty = 8, difficulty_1_target = 2^240. Find current target.
```
difficulty = difficulty_1_target / current_target
8 = 2^240 / current_target
current_target = 2^240 / 8 = 2^240 / 2^3 = 2^237
```
**Final answer: current target = 2^237.**

**Common mistake:** Inverting the ratio. Difficulty = reference target divided by current target, not the other way round.

### 7.5 Leading Zeros from a Target

**Method:**
1. Compute target = mantissa * 2^(8(exponent-3)).
2. Write it as a 256-bit (64 hex digit) number.
3. Count leading hex zeros; each hex zero = 4 bits.

**Example:** difficulty-1 target `0x00000000FFFF...` has 8 hex zeros = **32 leading zero bits**.

**From the Week 2 notes (worked):** target `0x05c739 * 2^160` written in 256-bit hex gives 72 + 4 + 1 = **77 leading zero bits** when you account for the top zero bits inside the 0x05 byte. (0x05 = 0000 0101, so 5 extra zero bits above the 72.) For exam purposes: count the full hex zeros first (72 bits), then add the leading zero bits inside the first non-zero byte.

### 7.6 Number of Computations (Part 3 required topic)

**Formula:**
```
P * 10 min * 60 sec = 2^n      =>      P * 600 = 2^n
n = log(600P) / log(2)  =  log2(600P)
```
P = hash rate (hashes/second), 600 = seconds in 10 minutes, 2^n = expected hash attempts, n = difficulty in bits.

**Worked example (from notes):** P = 10^20 hashes/sec.
```
total = P * 600 = 10^20 * 600 = 6 * 10^22
n = log2(6 * 10^22) ~ 75
```
**Final answer: about 2^75 hash computations, n ~ 75.**

**Easy example (Assignment 1 Q5):** P = 10^6 hashes/sec. Find n.
```
600P = 600 * 10^6 = 6 * 10^8
n = log2(6 * 10^8) = log10(6*10^8)/log10(2) = (8.778)/(0.301) ~ 29.2
```
**Final answer: n ~ 29 (about 2^29 computations).**

**Medium example (Assignment 2 Q3):** Find P when n = 40.
Rearrange: `2^n = 600P  =>  P = 2^n / 600`.
```
P = 2^40 / 600 = 1,099,511,627,776 / 600 ~ 1.83 * 10^9 hashes/sec
```
**Final answer: P ~ 1.83 * 10^9 hashes/sec (about 1.8 GH/s).**

**Hard example (Assignment 2 Q4):** Miner A: P = 10^6; Miner B: P = 10^9. Find the difference in n.
```
n_A = log2(600 * 10^6) = log2(6*10^8) ~ 29.2
n_B = log2(600 * 10^9) = log2(6*10^11) ~ 39.1
difference = n_B - n_A ~ 9.9 ~ 10
```
Shortcut: ratio of P is 10^3, and `log2(10^3) = 3 * log2(10) ~ 3 * 3.32 = 9.97`. **Final answer: difference in n is about 10 bits.**

**Worked classroom example (Week 2 notes):** 100,000 CPUs each at 10 trillion hashes/sec.
```
Total in 10 min = 10^5 * 10*10^12 * 600 = 6 * 10^20
2^n / 2 (average) = 6 * 10^20  =>  n = 68
```
**Final answer: n = 68.**

**Common mistakes:** Forgetting 600 seconds; using log base 10 without dividing by log10(2); mixing "average" (divide by 2) with "expected total".

### 7.7 Hash Rate from Difficulty

**Formula:**
```
hashRate = difficulty * 2^32 / (60 sec * 10 min) = difficulty * 2^32 / 600
```
**Example:** difficulty = 4.9 * 10^13.
```
hashRate = 4.9*10^13 * 2^32 / 600 ~ 4.9*10^13 * 4.295*10^9 / 600 ~ 3.5 * 10^20 hashes/sec
```
**Final answer: about 3.5 * 10^20 H/s (~ 350 EH/s),** which matches the real Bitcoin hash rate order quoted in the notes (385 EH/s).

### 7.8 Bytecode Computations (Part 3 required topic)

**Stack arithmetic example (from Week 11 notes):** Compute (3 + 5) * 2 and store at slot 0.
```
PUSH1 0x03    -> stack: [3]
PUSH1 0x05    -> stack: [5, 3]
ADD           -> stack: [8]        // 3 + 5
PUSH1 0x02    -> stack: [2, 8]
MUL           -> stack: [16]       // 8 * 2
PUSH1 0x00    -> stack: [0, 16]
SSTORE        -> stores 16 (0x10) at storage slot 0
```
Assembled bytecode: `0x6003600501600202600055`.
**How to read it:** `60` = PUSH1, so `6003` = PUSH1 0x03, `6005` = PUSH1 0x05, `01` = ADD, `6002` = PUSH1 0x02, `02` = MUL, `6000` = PUSH1 0x00, `55` = SSTORE. **Final stored value: 0x10 = 16.**

**RPN reminder:** EVM is stack-based, like Reverse Polish Notation. `3 5 + 2 *` means (3+5)*2.

**Practice:** Disassemble `0x6011600055`.
```
60 11 -> PUSH1 0x11 (17)
60 00 -> PUSH1 0x00
55    -> SSTORE
```
**Final answer: stores 0x11 = 17 at slot 0.**

---

## 8. Ethereum and Smart Contracts

### 8.1 Ethereum
A public, decentralised, distributed, **programmable** blockchain. Proposed in late 2013 by **Vitalik Buterin**. It is often called the "world computer": one shared computer everyone uses, no single owner, and using its resources costs money (gas).

Key facts from the notes:
- Cryptocurrency: **Ether** (Bitcoin's is BTC).
- Consensus (in these notes): **PoW** (same era as Bitcoin). Hash function: **Ethash** (Bitcoin uses SHA-256).
- Block time: **14 seconds** (Bitcoin: 10 minutes).
- Turing-complete: supports general computation via smart contracts.
- Apps (dApps) can be written in many languages; the platform-specific language is **Solidity**.

Ethereum as a state machine: it is a deterministic, practically unbounded **state machine** with a global singleton state. Transactions move it from one state to the next (Genesis State -> State 1 -> State 2 -> ...). Each new state corresponds to a new block.

### 8.2 Difference Between Bitcoin and Ethereum

| Feature | Bitcoin | Ethereum |
|---------|---------|----------|
| Purpose | Dedicated to cryptocurrency | General-purpose programmable platform |
| Currency | BTC | Ether |
| Block time | 10 minutes | 14 seconds |
| Hash function | SHA-256 (double) | Ethash |
| Smart contracts | Limited (Bitcoin Script) | Full (Solidity, Turing-complete) |
| Model | UTxO model | Account/state model |
| Description | Digital cash | "World computer" |

### 8.3 Smart Contracts
Self-executing programs stored and run on the blockchain. They automatically enforce "if...then" rules, are deterministic, trustless, secure, and **immutable once deployed** (cannot be modified). Term coined by **Nick Szabo** in the 1990s. Analogy: a **vending machine** (input coins -> deterministic output/change). Use cases: payments, dApps, supply chain, DeFi, crowdfunding, NFTs.

### 8.4 Solidity
The main Ethereum programming language for writing smart contracts. It compiles to EVM bytecode. Solidity hides the low-level tedium (constructors, packaging code, encoding function calls into transaction data).

### 8.5 Remix IDE
A browser-based IDE at `https://remix.ethereum.org` where you can write, compile, deploy, and interact with Solidity contracts without setting up your own Ethereum node.

### 8.6 Contract Creation, Compilation, Deployment
- **Creation:** write the `.sol` contract in Remix.
- **Compilation:** the Solidity compiler produces the **ABI** and the **EVM bytecode**.
- **Deployment:** send a transaction with `to` empty (none) and `data` = bytecode. The EVM runs the init code and RETURNs the runtime code, which is stored at a new contract address. Sending to `none` means "create a contract"; sending to an existing address means "invoke that contract".

### 8.7 Test Networks, Sepolia, Faucets
- **Test networks (testnets):** networks for testing with worthless test coins, so you do not spend real ETH.
- **Sepolia:** a popular Ethereum test network.
- **Faucet:** a service that gives free test ETH (e.g. to your wallet on Sepolia) so you can pay test gas and deploy/interact.

### 8.8 Gas and Gas Fee
- **Gas:** the fee unit for computation; every executed opcode costs gas (it uses a miner's/validator's resources).
- **Gas price:** how much Ether the sender pays per unit of gas.
- **Gas limit:** the maximum gas the sender allows for the transaction.
- **Final cost = gas used * gas price.** If a transaction needs more than the gas limit, it **fails**; if it uses less, the sender only pays for what was used.
- Sample opcode gas costs: STOP = 0, ADD = 3, MUL = 5, SUB = 3, DIV = 5, EXP = 10+, comparisons (LT/GT/EQ) = 3. Reading storage is cheap/free; **writing storage (SSTORE) is very expensive**.

### 8.9 ABI, Bytecode, EVM
- **ABI (Application Binary Interface):** the JSON description of the contract's functions and how to encode calls to them.
- **Bytecode:** the compiled low-level EVM instructions (opcodes) actually stored and run on-chain.
- **EVM (Ethereum Virtual Machine):** the stack-based runtime that executes bytecode. It makes code portable across machines. Specs: 140 opcodes (Turing complete), each opcode = 1 byte; stack depth = 1024 items, each item = 256-bit (32-byte) word, top 16 directly accessible; the program counter (PC) starts at 0; formal tuple `(block_state, transaction, message, code, memory, stack, pc, gas)`.

**Source code vs ABI vs Bytecode:**

| Item | What it is | Used by |
|------|-----------|---------|
| Source code (Solidity) | Human-readable contract | Developer |
| ABI | JSON interface of functions | Frontend/wallet to call functions |
| Bytecode | Compiled EVM opcodes | EVM to execute on-chain |

### 8.10 Wallet Connection and MetaMask
A wallet (e.g. **MetaMask**) holds your keys and signs transactions. In Remix you connect a wallet to deploy to a real/test network. The **origin of every transaction is an account controlled and signed by a private key** (an EOA).

### 8.11 Account Types
Ethereum has two account types (each identified by an address):
- **Externally Owned Account (EOA):** controlled by an ECDSA private key, no code stored, the default user wallet. It can sign transactions, call contract functions, and send Ether. Every transaction originates from an EOA.
- **Smart Contract Account:** controlled by its contract code, can hold storage, and runs code when triggered by a transaction or message.

Abstractly an account is a 4-tuple: `(nonce, balance, contract_code, storage)`. If there is no contract_code, the account is externally controlled.

### 8.12 Transactions vs Messages (Ethereum)
- A **transaction** is a signed data package always sent by a wallet (EOA). Fields: Nonce, To, Value (wei), Gas Price, Gas Limit, Data, Signature (v, r, s). Two types: wallet-to-wallet and wallet-to-contract.
- A **message** is like a transaction but is sent by a contract to another account, exists only virtually (not mined into a block). When a contract calls another contract, a virtual message is sent; when a wallet calls a contract, a transaction is sent.

### 8.13 Ether Units (quick reference)
wei (1), Babbage (10^3), Lovelace (10^6), Shannon (10^9, gwei), Szabo (10^12), Finney (10^15), **Ether (10^18)**, Grand (10^21). So **1 Ether = 10^18 wei**.

### 8.14 Practical Workflow (memorise the 7 steps)
1. Open **Remix IDE** (`remix.ethereum.org`).
2. Create a Solidity (`.sol`) file.
3. Write the contract.
4. Compile the contract (produces ABI + bytecode).
5. Deploy the contract (connect MetaMask, choose network).
6. Use a **testnet/faucet** (e.g. Sepolia + free test ETH) and pay gas.
7. Interact with the contract (call functions via transactions).

---

## 9. Bytecode Understanding (Week 11)

### 9.1 What Bytecode Is
Bytecode is the machine language the EVM understands and executes. A smart contract, for the EVM, is just a sequence of **opcodes** (one byte each) and their arguments, similar to assembly code. Example complete bytecode:
```
0x616061604052346000575b6060806100166000396000f36060604052...
```

### 9.2 Why Solidity Becomes Bytecode
The EVM cannot run Solidity directly. The compiler turns human-readable Solidity into low-level EVM bytecode that is portable and executable on every node's EVM identically (deterministic).

### 9.3 Role of the EVM
The EVM is a **stack-based processor** that reads the bytecode one opcode at a time (tracked by the PC), pushing and popping 32-byte values on a stack, using temporary memory, and persistent storage. It charges gas per opcode.

### 9.4 Source Code vs ABI vs Bytecode
See the table in 8.9. In short: Solidity is what you write, the ABI is how others call your functions, and bytecode is what actually runs on-chain.

### 9.5 Disassembling Bytecode (how it appears)
Bytecode is read as `PC | Command | Opcode | Operation | Argument`. The opcode dictates how many argument bytes follow. Example from the notes:
```
PC | Command  | Opcode | Operation  | Argument
0  | 0x616061 | 0x61   | PUSH2      | 0x6061
3  | 0x6040   | 0x60   | PUSH1      | 0x40
5  | 0x52     | 0x52   | MSTORE     | None
6  | 0x34     | 0x34   | CALLVALUE  | None
```
Note: `PUSH1` = 0x60 (1 arg byte), `PUSH2` = 0x61 (2 arg bytes), up to PUSH32. Why many PUSH opcodes? To avoid wasting gas pushing 32 bytes when 1 byte is enough.

### 9.6 Stack, Memory, Storage, Call Stack
- **Stack:** fast, non-persistent, 32-byte items, top 16 directly accessible (DUPx, SWAPx, 1<=x<=16). "Stack too deep" error if you exceed local-variable limits.
- **Memory:** starts empty each execution, byte-addressable (2^256 slots of 1 byte), written with MSTORE, read with MLOAD; cleared at the end; more gas than stack. MSTORE at offset n overwrites bytes n to n+31.
- **Storage:** 2^256 slots of 32 bytes, **persistent** across executions, attached to the contract address. SSTORE/SLOAD are much more gas-expensive than memory ops. Storage is unique per deployed contract (not global, not per sender).
- **Call stack:** when a contract calls another, the current stack/memory are pushed to the call stack (limit 1024 deep). Exceeding it means the call is not made.

### 9.7 Contract Creation vs Invocation (key exam idea)
- Send transaction with `to: none` => EVM treats `data` as **code to execute** (contract creation/deployment).
- Send transaction with `to: createdAddress` => EVM treats `data` as **input data** to the existing contract's code (invocation).
- Important subtlety: code executed during a plain creation transaction is discarded unless it ends with RETURN that returns the **runtime code**. The EVM stores as the contract only the bytecode left in memory and RETURNed.

### 9.8 Hand-Assembled Contract Example (from the notes)
Goal: a contract that saves whatever data you send it at storage slot 0.
- Final (runtime) code:
```
PUSH1 0x00
CALLDATALOAD   // load 32 bytes of call data
PUSH1 0x00
SSTORE         // save at slot 0
```
Assembles to `0x600035600055` (6 bytes).
- Deployment (init) code that returns the runtime code:
```
0x6006600c60003960066000f3600035600055
```
Disassembled: PUSH1 0x06 (length), PUSH1 0x0c (offset), PUSH1 0x00, CODECOPY, PUSH1 0x06, PUSH1 0x00, RETURN, then the 6-byte runtime code padded at offset 0x0c.
- Behaviour: sending `0x67` stores it in the high-order bits (`0x67000...0`), because the EVM reads 32 bytes and pads missing bytes with zeros. Sending 33 bytes saves only the first 32; the extra byte is dropped and does not overflow to slot 1.

### 9.9 What Bytecode Questions Can Come
1. **Disassemble** a short hex string into opcodes (PUSH/ADD/MUL/SSTORE).
2. **Compute the stack** after a sequence of opcodes.
3. **State the final storage value** after SSTORE.
4. **Explain creation vs invocation** (`to: none` vs `to: address`).
5. **Identify** which opcode is which (0x60 = PUSH1, 0x01 = ADD, 0x02 = MUL, 0x55 = SSTORE, 0x52 = MSTORE).

**Solved practice:** Disassemble `0x600a600302600055` and give the stored value.
```
60 0a -> PUSH1 0x0a (10)
60 03 -> PUSH1 0x03 (3)
02    -> MUL  (10 * 3 = 30)
60 00 -> PUSH1 0x00
55    -> SSTORE
```
**Final answer: stores 30 (0x1e) at slot 0.**

---

## 10. MCQs

> Try to answer before reading the bolded answer. Cover the right side.

### Easy MCQs

1. Which hashing algorithm does Bitcoin use for PoW? a) MD5 b) SHA-1 c) SHA-256 d) AES. **Answer: c.** Bitcoin uses double SHA-256.
2. The Merkle root is stored in the: a) Transaction list b) Wallet c) Block header d) Mining pool. **Answer: c.**
3. Digital signatures provide: a) Confidentiality only b) Integrity and authentication c) Compression d) Hashing. **Answer: b.**
4. Bitcoin was proposed by: a) Vitalik Buterin b) Nick Szabo c) Satoshi Nakamoto d) Adam Back. **Answer: c.**
5. The Bitcoin white paper was published in: a) 2006 b) 2008 c) 2010 d) 2013. **Answer: b.** (31 Oct 2008.)
6. A blockchain is best described as a: a) Centralised database b) Distributed immutable ledger c) Cloud server d) Single file. **Answer: b.**
7. Ether is the cryptocurrency of: a) Bitcoin b) Litecoin c) Ethereum d) Cardano. **Answer: c.**
8. Smart contracts are mainly associated with: a) Bitcoin b) Ethereum c) Dogecoin d) Ripple. **Answer: b.**
9. The smallest unit of Bitcoin is: a) wei b) satoshi c) gwei d) bit. **Answer: b.** (1 satoshi = 10^-8 BTC.)
10. The smallest unit related to Ether is: a) satoshi b) wei c) gwei d) finney. **Answer: b.** (1 Ether = 10^18 wei.)
11. Proof of Work requires miners to vary the: a) Merkle root b) Timestamp only c) Nonce d) Version. **Answer: c.**
12. Bitcoin's target block time is: a) 1 minute b) 10 minutes c) 14 seconds d) 1 hour. **Answer: b.**
13. Ethereum's block time (per notes) is: a) 10 minutes b) 1 minute c) 14 seconds d) 30 seconds. **Answer: c.**
14. SHA-256 output length is: a) 128 bits b) 160 bits c) 256 bits d) 512 bits. **Answer: c.**
15. A Bitcoin address is produced using: a) SHA-256 only b) RIPEMD160(SHA256(pubKey)) c) MD5 d) AES. **Answer: b.**
16. Which key is used to sign a transaction? a) Public key b) Private key c) Session key d) Symmetric key. **Answer: b.**
17. Which key is used to verify a signature? a) Private key b) Public key c) Master key d) Seed. **Answer: b.**
18. The first transaction in a block is the: a) Genesis transaction b) Coinbase transaction c) UTxO d) Merkle transaction. **Answer: b.**
19. UTxO stands for: a) Unique Transaction Output b) Unspent Transaction Output c) Used Transaction Output d) Universal Token Output. **Answer: b.**
20. An input of a transaction must reference a: a) STxO b) UTxO c) Coinbase d) Nonce. **Answer: b.**
21. The Bitcoin block header size is: a) 64 bytes b) 80 bytes c) 100 bytes d) 1 MB. **Answer: b.**
22. Hashing is a: a) Two-way function b) One-way function c) Encryption scheme d) Compression scheme. **Answer: b.**
23. Which consensus does Bitcoin use? a) PoS b) PoW c) PoA d) PBFT. **Answer: b.**
24. PoS stands for: a) Proof of Speed b) Proof of Stake c) Proof of Security d) Proof of Storage. **Answer: b.**
25. Smart contract term was coined by: a) Satoshi b) Vitalik c) Nick Szabo d) Adam Back. **Answer: c.**
26. The EVM is a: a) Stack-based processor b) Register machine c) GPU d) Database. **Answer: a.**
27. Solidity compiles to: a) Java bytecode b) EVM bytecode c) Machine code d) WASM only. **Answer: b.**
28. Remix is a: a) Wallet b) Browser IDE for Solidity c) Blockchain d) Faucet. **Answer: b.**
29. Sepolia is a: a) Wallet b) Testnet c) Token d) Compiler. **Answer: b.**
30. A faucet gives you: a) Real ETH b) Test ETH c) Gas refund d) Private keys. **Answer: b.**
31. Gas in Ethereum is: a) A coin b) The fee unit for computation c) A wallet d) A block. **Answer: b.**
32. Bitcoin and Ethereum are: a) Permissioned b) Permissionless c) Private d) Closed. **Answer: b.**
33. Which is a distributed ledger property? a) Central control b) Immutability c) Easy editing d) Single copy. **Answer: b.**
34. Mining reward currently consists of: a) Only fees b) New coins + transaction fees c) Only new coins d) Interest. **Answer: b.**
35. NFTs are: a) Interchangeable b) Unique non-interchangeable assets c) Coins d) Wallets. **Answer: b.**
36. Vitalik Buterin proposed Ethereum in: a) 2008 b) 2011 c) 2013 d) 2017. **Answer: c.**
37. Bitcoin's maximum supply is about: a) 1 million b) 21 million c) 100 million d) Unlimited. **Answer: b.**
38. A node that stores the full chain is a: a) SPV node b) Full node c) Light node d) Wallet only. **Answer: b.**
39. The locking script in Bitcoin is called: a) scriptSig b) scriptPubKey c) coinbase d) nonce. **Answer: b.**
40. The unlocking script is called: a) scriptPubKey b) scriptSig c) witness only d) Merkle path. **Answer: b.**
41. Which ensures data cannot be altered by users? a) Public Distributed Ledger b) PoW only c) PoS only d) Hash encryption. **Answer: a.** (Quiz slide answer.)
42. Cryptocurrency uses which hashing algorithm (Week 1 quiz)? a) Scrypt b) Ethash c) SHA256 d) None. **Answer: c.**
43. The Merkle root summarises: a) All blocks b) All transactions in a block c) All nodes d) All wallets. **Answer: b.**
44. Each opcode in the EVM takes: a) 1 byte b) 4 bytes c) 32 bytes d) 256 bytes. **Answer: a.**
45. EVM stack item size is: a) 8 bits b) 32 bits c) 256 bits d) 512 bits. **Answer: c.**
46. The program counter (PC) starts at: a) 1 b) 0 c) 256 d) Random. **Answer: b.**
47. Storage in the EVM is: a) Volatile b) Persistent c) Cleared each call d) On the stack. **Answer: b.**
48. Memory in the EVM is: a) Persistent b) Non-persistent (cleared each execution) c) On-chain forever d) Free to write to storage. **Answer: b.**
49. PUSH1 opcode in hex is: a) 0x50 b) 0x60 c) 0x55 d) 0x01. **Answer: b.**
50. SSTORE writes to: a) Stack b) Memory c) Storage d) Call stack. **Answer: c.**
51. The coinbase transaction input references: a) A UTxO b) No previous UTxO (null) c) The Merkle root d) The nonce. **Answer: b.**
52. A change output exists because Bitcoin outputs are: a) Divisible b) Indivisible c) Encrypted d) Free. **Answer: b.**
53. The longest chain is: a) Discarded b) The valid chain c) Ignored d) The shortest work. **Answer: b.**
54. A 51% attacker can: a) Steal anyone's coins b) Only reclaim his own spent coins c) Print unlimited coins d) Change others' private keys. **Answer: b.**
55. Halving happens every: a) 10,000 blocks b) 210,000 blocks c) 2,016 blocks d) 1 year. **Answer: b.**
56. Difficulty re-targets every: a) 210,000 blocks b) 2,016 blocks c) 144 blocks d) Block. **Answer: b.**
57. A soft fork is: a) Backward compatible b) Not compatible c) Always a new coin d) A wallet. **Answer: a.**
58. Bitcoin uses which signature algorithm? a) RSA b) ECDSA (SECP256K1) c) DSA d) AES. **Answer: b.**
59. Which is NOT a blockchain component (Week 1)? a) Digital signatures b) Hashing c) Consensus d) Antivirus. **Answer: d.**
60. An EOA is controlled by: a) Contract code b) A private key c) The EVM d) A faucet. **Answer: b.**

### Medium MCQs

1. To find a hash with n leading zero bits you need about: a) n b) 2n c) 2^n d) n^2 computations. **Answer: c.**
2. The target formula is: a) mantissa * 2^(8*exponent) b) mantissa * 2^(8*(exponent-3)) c) mantissa / exponent d) 2^exponent. **Answer: b.**
3. Difficulty equals: a) current_target / difficulty_1_target b) difficulty_1_target / current_target c) target * nonce d) hashRate * 600. **Answer: b.**
4. A smaller target means: a) Easier mining b) More leading zeros and harder mining c) Fewer zeros d) No change. **Answer: b.**
5. For nBits 0x1d00ffff, the exponent is: a) 0x00 b) 0xff c) 0x1d (29) d) 0xffff. **Answer: c.**
6. For nBits 0x1d00ffff, the mantissa is: a) 0x1d b) 0x00ffff c) 0xffff00 d) 0x29. **Answer: b.**
7. n = log(600P)/log(2) computes: a) Hash rate b) Difficulty in bits c) Block size d) Reward. **Answer: b.**
8. hashRate = difficulty * 2^32 / : a) 60 b) 600 c) 2016 d) 210000. **Answer: b.**
9. txID is computed as: a) SHA256(tx) b) SHA256(SHA256(txRecord)) c) RIPEMD160(tx) d) MD5(tx). **Answer: b.**
10. An OutPoint is: a) txID only b) txID + output index c) Address d) Nonce. **Answer: b.**
11. The signature in P2PKH is stored in: a) scriptPubKey b) scriptSig c) Merkle root d) Header. **Answer: b.**
12. OP_CHECKSIG verifies the: a) Address only b) Signature using the public key c) Hash of the block d) Nonce. **Answer: b.**
13. Which opcode duplicates the top stack value? a) OP_HASH160 b) OP_DUP c) OP_EQUALVERIFY d) OP_CHECKSIG. **Answer: b.**
14. The Merkle tree needs an even number of leaves; an odd one is fixed by: a) Dropping the last tx b) Duplicating the last hash c) Adding a zero d) Splitting it. **Answer: b.**
15. To prove a tx is in a block you need about: a) N hashes b) log2(N) hashes c) N^2 hashes d) 1 hash. **Answer: b.**
16. Reading EVM storage is: a) Very expensive b) Cheap/free relative to writing c) Impossible d) On the stack. **Answer: b.**
17. Writing EVM storage (SSTORE) is: a) Free b) Cheap c) Very expensive d) Disabled. **Answer: c.**
18. An Ethereum account 4-tuple is: a) (nonce, balance, code, storage) b) (key, value, hash, nonce) c) (to, from, value, gas) d) (pc, stack, memory, gas). **Answer: a.**
19. A message in Ethereum is sent by: a) A wallet b) A contract c) A miner d) The EVM only. **Answer: b.**
20. A transaction in Ethereum is always sent by: a) A contract b) A wallet (EOA) c) The EVM d) A faucet. **Answer: b.**
21. Final transaction cost in Ethereum is: a) gas + gas price b) gas used * gas price c) gas limit only d) value * gas. **Answer: b.**
22. If a transaction needs more than the gas limit it: a) Succeeds with refund b) Fails c) Waits d) Splits. **Answer: b.**
23. The EVM has how many opcodes (per notes)? a) 100 b) 140 c) 256 d) 64. **Answer: b.**
24. EVM stack depth is: a) 16 b) 256 c) 1024 d) Unlimited. **Answer: c.**
25. The top how many stack items are directly accessible? a) 8 b) 16 c) 32 d) 64. **Answer: b.**
26. Sending a transaction with to: none means: a) Invoke a contract b) Create/deploy a contract c) Transfer ETH d) Nothing. **Answer: b.**
27. Sending a transaction with to: contractAddress means: a) Create a contract b) Invoke the contract c) Burn ETH d) Mine. **Answer: b.**
28. PUSH2 opcode is: a) 0x60 b) 0x61 c) 0x62 d) 0x52. **Answer: b.**
29. MSTORE opcode is: a) 0x52 b) 0x55 c) 0x51 d) 0x60. **Answer: a.**
30. CALLVALUE pushes: a) The gas price b) The wei sent with the transaction c) The nonce d) The block number. **Answer: b.**
31. The contract code stored on-chain is the: a) Init code b) Runtime code RETURNed c) ABI d) Source code. **Answer: b.**
32. Bitcoin uses which byte order: a) Big-endian b) Little-endian c) Mixed d) None. **Answer: b.**
33. Base58 omits which to avoid confusion: a) a, b, c b) 0, O, l, I c) 1, 2, 3 d) x, y, z. **Answer: b.**
34. Base58Check appends a checksum of length: a) 1 byte b) 2 bytes c) 4 bytes d) 8 bytes. **Answer: c.**
35. The address is shorter than the public key by about: a) 10% b) 25% c) 37.5% d) 50%. **Answer: c.**
36. A wallet where all keys derive from one seed is: a) JBOK b) Deterministic (HD) c) Random d) SPV. **Answer: b.**
37. A "Just a Bunch Of Keys" wallet is: a) Deterministic b) Nondeterministic c) HD d) Cold. **Answer: b.**
38. An SPV node keeps: a) The full chain b) Only block headers c) All UTxOs d) All transactions. **Answer: b.**
39. New nodes connect to peers on TCP port: a) 80 b) 443 c) 8333 d) 3000. **Answer: c.**
40. The block reward in 2021 was: a) 50 b) 25 c) 12.5 d) 6.25 BTC. **Answer: d.**
41. After 2024 halving the reward is: a) 6.25 b) 3.125 c) 12.5 d) 1.5625 BTC. **Answer: b.**
42. Selfish mining is shown doable with about: a) 51% b) 25% c) 10% d) 75% of power. **Answer: b.**
43. Recommended waiting confirmations for safety: a) 1 block b) 3 blocks c) 6 blocks d) 100 blocks. **Answer: c.**
44. The Genesis block height is: a) 0 b) 1 c) -1 d) 210000. **Answer: a.**
45. difficulty_1 nBits is: a) 0x1705c739 b) 0x1d00ffff c) 0x00000000 d) 0xffffffff. **Answer: b.**
46. Ethereum hash function (per notes): a) SHA-256 b) Ethash c) Scrypt d) Keccak only. **Answer: b.**
47. An Ethereum address is how many hex characters: a) 64 b) 40 c) 128 d) 20. **Answer: b.** (20 bytes = 40 hex.)
48. The nonce in an Ethereum account prevents: a) Gas spikes b) Replay attacks and double spending c) Forks d) Mining. **Answer: b.**
49. Which is NOT in the 80-byte header? a) Version b) Merkle root c) Full transaction list d) Nonce. **Answer: c.**
50. A hard fork: a) Is backward compatible b) Creates a new cryptocurrency c) Is just a patch d) Needs no new chain. **Answer: b.**
51. The double-hash for block ID is: a) SHA256 once b) SHA256(SHA256(header)) c) RIPEMD160 d) MD5. **Answer: b.**
52. Transaction fee equals: a) Outputs - inputs b) Inputs - outputs (unaccounted value) c) Always 10K d) Zero. **Answer: b.**
53. The Merkle path length to verify inclusion grows as: a) N b) log2(N) c) 2^N d) constant 1. **Answer: b.**
54. Bitcoin block size limit (original) was: a) 1 KB b) 1 MB c) 8 MB d) 4 GB. **Answer: b.**
55. SegWit effectively increased capacity to about: a) 2 MB b) 4 MB c) 8 MB d) 1 GB. **Answer: b.**
56. ECDSA in Bitcoin uses the curve: a) Curve25519 b) SECP256K1 c) P-256 d) Ed448. **Answer: b.**
57. The EVM tuple includes which of these: a) (block_state, transaction, message, code, memory, stack, pc, gas) b) (block, tx, fee) c) (key, value) d) (header, body). **Answer: a.**
58. Which is persistent across executions? a) Stack b) Memory c) Storage d) PC. **Answer: c.**
59. CODECOPY is used during: a) Invocation only b) Contract deployment to copy runtime code c) Hashing d) Mining. **Answer: b.**
60. In RPN, "3 5 + 2 *" equals: a) 11 b) 16 c) 13 d) 30. **Answer: b.** ((3+5)*2 = 16.)

### Hard MCQs

1. nBits 0x1705c739 gives leading zeros of about: a) 32 bits b) 72 bits c) 8 bits d) 16 bits. **Answer: b.** (18 hex zeros.)
2. If difficulty_1_target = 2^224 and current = 2^220, difficulty is: a) 4 b) 8 c) 16 d) 2. **Answer: c.** (2^4.)
3. If difficulty = 8 and difficulty_1 = 2^240, current target is: a) 2^243 b) 2^237 c) 2^240 d) 2^30. **Answer: b.**
4. For P = 10^6 H/s, n is about: a) 20 b) 29 c) 40 d) 68. **Answer: b.**
5. For P = 10^20 H/s, n is about: a) 60 b) 68 c) 75 d) 80. **Answer: c.**
6. If n = 40, hash rate P is about: a) 1.8 * 10^9 b) 6 * 10^8 c) 10^6 d) 2^40. **Answer: a.** (2^40/600.)
7. Difference in n between P=10^6 and P=10^9 is about: a) 3 b) 6 c) 10 d) 30. **Answer: c.** (log2(10^3)~10.)
8. The Week 2 worked difficulty 48,712,405,953,118 equals about: a) 2^32 b) 2^45.5 c) 2^48 d) 2^80. **Answer: b.**
9. With target 0x05c739*2^160, leading zeros counting inside 0x05 are about: a) 72 b) 77 c) 80 d) 32 bits. **Answer: b.**
10. Bytecode 0x6003600501600202600055 stores: a) 8 b) 16 c) 32 d) 0. **Answer: b.** ((3+5)*2=16.)
11. Bytecode 0x6011600055 stores: a) 0x11 (17) b) 0x10 (16) c) 0 d) 0x55. **Answer: a.**
12. In 0x600035600055, 0x35 is: a) PUSH1 b) CALLDATALOAD c) SSTORE d) ADD. **Answer: b.**
13. Sending 0x67 to a save-data contract stores: a) 0x000...067 b) 0x67000...0 (high bits) c) Nothing d) Error. **Answer: b.**
14. Sending 33 bytes to it stores: a) All 33 bytes b) First 32 bytes; extra dropped c) Last byte only d) Overflows to slot 1. **Answer: b.**
15. The difficulty re-target uses: oldTarget * (actual time of 2016 blocks / (2016*10 min)). The max change per cycle is a factor of: a) 2 b) 4 c) 8 d) 10. **Answer: b.**
16. The number of blocks until reward stops is: a) 6,930,000 b) 210,000 c) 21,000,000 d) 2,016. **Answer: a.** (33*210,000.)
17. Halving "n" where 50/(2^n) < 10^-8 gives n >: a) 16 b) 22 c) 32.2 d) 64. **Answer: c.**
18. outPoint size is: a) 32 bytes b) 36 bytes c) 4 bytes d) 80 bytes. **Answer: b.** (32 + 4.)
19. The header has how many 4-byte fields and 32-byte fields: a) 4 four-byte + 2 thirty-two-byte b) 6 four-byte c) 2 four-byte d) 3 each. **Answer: a.** (Version, Timestamp, nBits, Nonce are 4-byte; prevHash and Merkle root are 32-byte.)
20. The probability of n zero bits is: a) 0.5*n b) 0.5^n c) n^2 d) 2^n. **Answer: b.**
21. The attacker catch-up probability with z (p>q): a) Increases with z b) Drops exponentially with z c) Constant d) Linear. **Answer: b.**
22. The white paper models the race as a: a) Linear walk b) Binomial Random Walk (Gambler's Ruin) c) Markov chain only d) Normal distribution. **Answer: b.**
23. From the white paper q=0.1, P<0.1% requires z =: a) 3 b) 5 c) 11 d) 24. **Answer: b.**
24. For q=0.3, P<0.1% requires z =: a) 5 b) 11 c) 24 d) 89. **Answer: c.**
25. hashRate from difficulty 4.9*10^13 is about: a) 3.5*10^20 H/s b) 10^6 H/s c) 600 H/s d) 2^32. **Answer: a.**
26. Each hex digit in a target equals how many bits: a) 1 b) 2 c) 4 d) 8. **Answer: c.**
27. Bytecode 0x600a600302600055 stores: a) 13 b) 30 c) 10 d) 3. **Answer: b.** (10*3.)
28. The MSTORE at offset n overwrites bytes: a) n only b) n to n+31 c) n to n+7 d) all memory. **Answer: b.**
29. Call stack depth limit is: a) 16 b) 256 c) 1024 d) Unlimited. **Answer: c.**
30. "Stack too deep" relates to the: a) Call stack 1024 limit b) Top-16 directly accessible stack items c) Storage limit d) Memory. **Answer: b.**
31. difficulty = (65535/378681)*2^(8*(29-23)) is about: a) 4.9*10^13 b) 16 c) 2^32 d) 600. **Answer: a.**
32. The 256-bit hash space with 32 leading zeros corresponds to nBits: a) 0x1705c739 b) 0x1d00ffff c) 0xffffffff d) 0x00000001. **Answer: b.**
33. If P doubles, the achievable n increases by about: a) 0 b) 1 c) 2 d) 10. **Answer: b.** (log2(2)=1.)
34. txID for a transaction is which size: a) 20 bytes b) 32 bytes c) 4 bytes d) 64 bytes. **Answer: b.**
35. The coinbase data can serve as: a) The Merkle root b) An extra nonce c) The signature d) The address. **Answer: b.**
36. Bitcoin difficulty-1 target hex begins with how many hex zeros: a) 4 b) 8 c) 16 d) 18. **Answer: b.**
37. PUSH opcodes range from PUSH1 to: a) PUSH8 b) PUSH16 c) PUSH32 d) PUSH64. **Answer: c.**
38. To deploy with desired runtime code you must end the init code with: a) STOP b) RETURN c) SSTORE d) REVERT. **Answer: b.**
39. With to: created (existing) the data field is treated as: a) Bytecode to execute b) Input data to the contract c) A new contract d) Ignored. **Answer: b.**
40. After a plain creation tx without RETURN, eth.getCode shows: a) The runtime code b) 0x (empty) c) The init code d) An error. **Answer: b.**
41. 1 Exa hash (per notes) is about: a) 10^6 b) 10^9 c) 10^12 (trillion) per the EH/s note d) 10^18. **Answer: c.** (Note approximates 2^40 ~ 10^12.)
42. Mining "n=68" example used: a) 1000 CPUs b) 100,000 CPUs at 10 TH/s c) 1 GPU d) 10^20 H/s. **Answer: b.**
43. SegWit replaced block size with: a) Block weight b) Block height c) Block hash d) Block nonce. **Answer: a.**
44. Bitcoin Cash resulted from a: a) Soft fork b) Hard fork c) Airdrop d) Merge. **Answer: b.**
45. The genesis block was created on: a) 31 Oct 2008 b) 9 Jan 2009 c) 1 Jan 1970 d) 2013. **Answer: b.**
46. Ethereum moved from PoW to PoS in: a) 2020 b) Sept 2022 c) 2017 d) Never (per notes it remained PoW). **Answer: b.** (Notes mention Ethereum moved to PoS in Sept 2022; the Week 9 slides describe PoW-era Ethereum.)
47. A 256-bit number has how many hex digits: a) 32 b) 64 c) 128 d) 256. **Answer: b.**
48. The reward total sums to about: a) 21 million BTC b) 19.3 million c) 6.93 million d) 210,000. **Answer: a.**
49. Hash rate unit Bitcoin uses (per notes): a) MH/s b) EH/s (Exa) c) KH/s d) GH/s. **Answer: b.**
50. The compactSize 0xfd prefix means the number is stored in: a) 1 byte b) uint16 (2 bytes) c) uint32 (4 bytes) d) uint64 (8 bytes). **Answer: b.**

### Tricky / Conceptual MCQs

1. Bitcoin keeps data: a) Encrypted for privacy b) Public and unencrypted c) Hidden d) Compressed. **Answer: b.** Bitcoin does not encrypt data; it uses hashing and signatures.
2. Which best prevents double spending without a central authority? a) Encryption b) Proof of Work + longest chain + UTxO checks c) Bigger blocks d) Faucets. **Answer: b.**
3. You sign with the private key because: a) It is public b) Only you hold it, proving ownership c) It is faster d) It hides data. **Answer: b.**
4. A bigger target means mining is: a) Harder b) Easier c) Impossible d) Unchanged. **Answer: b.** (Counterintuitive: bigger target = fewer zeros = easier.)
5. If two valid blocks appear at once: a) Both kept forever b) A fork forms; longest chain later wins c) Network halts d) Coins double. **Answer: b.**
6. A 51% attacker cannot: a) Reverse his own recent tx b) Take coins he never owned c) Re-mine the coinbase to himself d) Censor transactions. **Answer: b.** He lacks others' private keys.
7. The Merkle root changes if: a) The nonce changes b) Any transaction changes c) The timestamp changes only d) The version changes. **Answer: b.**
8. To change the Merkle root during mining you can: a) Edit a past block b) Change the extra nonce in the coinbase c) Change SHA-256 d) Lower the target. **Answer: b.**
9. Reading EVM storage vs writing: a) Both free b) Reading cheaper, writing very expensive c) Writing free d) Both expensive equally. **Answer: b.**
10. Sending a contract less than 32 bytes of data results in: a) Error b) Zero-padding of the remaining bytes c) Truncation of the contract d) A new contract. **Answer: b.**
11. The runtime code is stored, not the init code, because: a) Init code is larger b) The EVM stores only what RETURN leaves in memory c) Init code is encrypted d) Solidity forbids it. **Answer: b.**
12. Hashing gives integrity because: a) It is reversible b) One bit change avalanches the output c) It uses a key d) It compresses. **Answer: b.**
13. A transaction with inputs > outputs leaves the difference as: a) Burned b) The transaction fee to the miner c) Change to receiver d) Lost. **Answer: b.**
14. Why are there PUSH1 to PUSH32 opcodes? a) Backward compatibility b) To save gas by pushing only the bytes needed c) Security d) Random design. **Answer: b.**
15. The address is used in the output (not the public key) because: a) It is longer b) It is shorter and the public key is supplied later in scriptSig c) It is encrypted d) It hides the value. **Answer: b.**
16. Ethereum is called the "world computer" because: a) It is the biggest server b) All participants share one programmable state machine c) It runs Windows d) It stores files. **Answer: b.**
17. A message (Ethereum) differs from a transaction in that it: a) Is signed by a wallet b) Is sent by a contract and not mined into a block c) Costs no gas ever d) Creates accounts. **Answer: b.**
18. Smart contracts are immutable once deployed, which means: a) They can be edited anytime b) Bugs cannot simply be patched (deploy like launching a rocket) c) They self-update d) They expire. **Answer: b.**
19. Selfish mining lets a miner: a) Steal private keys b) Waste others' work and earn more than honest mining c) Lower difficulty d) Skip PoW. **Answer: b.**
20. Why double-hash (SHA256 twice)? a) For speed b) For extra protection against certain attacks (length-extension) c) To shorten output d) To encrypt. **Answer: b.**
21. Which statement is TRUE? a) PoS uses more energy than PoW b) PoW uses more energy than PoS c) Both use equal energy d) Neither uses energy. **Answer: b.**
22. The "difficulty 1" reference target represents: a) 8 leading hex zeros (32 bits) b) 18 hex zeros c) 64 zeros d) 0. **Answer: a.**
23. If all 32-bit nonce values fail, a miner can: a) Give up b) Change timestamp or extra nonce, then re-hash c) Lower SHA-256 d) Skip the block. **Answer: b.**
24. The chain is immutable mainly because: a) Files are read-only b) Each block hash depends on the previous, so editing one breaks all later c) Nodes refuse logins d) It is encrypted. **Answer: b.**
25. EOA vs contract account: which has code? a) EOA b) Contract account c) Both d) Neither. **Answer: b.**
26. A faucet exists so developers can: a) Buy real ETH cheaply b) Get free test ETH to pay test gas c) Mine faster d) Store keys. **Answer: b.**
27. Gas limit too low causes: a) Refund b) Out-of-gas failure c) Faster execution d) Free execution. **Answer: b.**
28. The UTxO set shrinks when: a) A new UTxO is created b) A UTxO is consumed (spent) c) A block is mined d) Difficulty rises. **Answer: b.**
29. Which proves a transaction is in a block without the whole block? a) The nonce b) The Merkle branch/path c) The timestamp d) The version. **Answer: b.**
30. Why is the previous block hash in the header? a) For mining speed b) To chain blocks and enforce immutability c) For privacy d) For gas. **Answer: b.**
31. Which is NOT a property of a good hash? a) Collision resistance b) One-way c) Reversibility d) Avalanche effect. **Answer: c.**
32. A coinbase transaction's purpose: a) Combine inputs b) Pay the miner the block reward c) Encrypt data d) Set difficulty. **Answer: b.**
33. The longest chain represents: a) The most transactions b) The greatest proof-of-work effort c) The newest block d) The richest miner. **Answer: b.**
34. Why use addresses (160-bit) instead of public keys (256-bit) in outputs? a) Security only b) Shorter, saving space, with the public key revealed only when spending c) Encryption d) Faster mining. **Answer: b.**
35. Which is TRUE about Bitcoin privacy? a) Fully anonymous b) Pseudonymous: visible transactions, anonymous key owners c) Encrypted addresses d) Hidden amounts. **Answer: b.**
36. CALLDATALOAD in a save-data contract: a) Stores to disk b) Pushes 32 bytes of transaction data to the stack c) Mines d) Sends ETH. **Answer: b.**
37. Which statement about Solidity is correct? a) The EVM runs Solidity directly b) Solidity is compiled to bytecode for the EVM c) Solidity is a wallet d) Solidity replaces gas. **Answer: b.**
38. Bitcoin's main contribution per Satoshi is: a) Encryption b) Preventing double spending in a decentralised network via PoW c) Faster payments d) Smart contracts. **Answer: b.**
39. Why might a low-fee transaction get "stuck"? a) Invalid signature b) Miners deprioritise it; it may stay unconfirmed c) Wrong hash d) Too many outputs. **Answer: b.**
40. The vending machine analogy explains smart contracts because both are: a) Random b) Deterministic: given input, produce a fixed output/state change c) Centralised d) Reversible. **Answer: b.**

---

## 11. Short Questions and Answers

### Easy Short Questions

1. **What is a blockchain?** A distributed, immutable digital ledger of cryptographically linked blocks maintained by a network of nodes.
2. **What is a block?** A collection of transactions with an 80-byte header.
3. **What is a transaction?** A transfer of value with one or more inputs and one or more outputs.
4. **What is hashing?** A one-way function turning any input into a fixed-length digest.
5. **Which hash does Bitcoin use?** Double SHA-256.
6. **What is the SHA-256 output size?** 256 bits (32 bytes, 64 hex).
7. **What is a digital signature?** Signing a message with a private key so others can verify ownership with the public key.
8. **What three things does a digital signature provide?** Authentication, non-repudiation, integrity.
9. **Which key signs and which verifies?** Private key signs, public key verifies.
10. **What is PoW?** A consensus protocol where miners prove computational effort to add a block.
11. **What is mining?** Varying the nonce to find a valid block hash and earn rewards.
12. **What is double spending?** Spending the same coins twice.
13. **What is a Merkle root?** The single top hash summarising all transactions in a block, stored in the header.
14. **Where is the Merkle root stored?** In the block header.
15. **What is a UTxO?** An unspent transaction output, the spendable coin.
16. **What is an STxO?** A spent transaction output, no longer usable.
17. **What is the coinbase transaction?** The first transaction in a block, paying the miner the reward.
18. **What is a nonce?** A number miners vary to find a valid hash.
19. **What is the block header size?** 80 bytes.
20. **What is Bitcoin's target block time?** 10 minutes.
21. **What is Ethereum's block time (per notes)?** 14 seconds.
22. **What is the smallest unit of Bitcoin?** 1 satoshi = 10^-8 BTC.
23. **What is the smallest unit of Ether?** 1 wei; 1 Ether = 10^18 wei.
24. **What is a smart contract?** Self-executing code stored on the blockchain that enforces rules automatically.
25. **Who coined "smart contract"?** Nick Szabo, in the 1990s.
26. **Who proposed Ethereum?** Vitalik Buterin (late 2013).
27. **What is Ether?** Ethereum's cryptocurrency.
28. **What is Solidity?** Ethereum's smart contract programming language.
29. **What is Remix?** A browser-based IDE for writing and deploying Solidity contracts.
30. **What is Sepolia?** An Ethereum test network.
31. **What is a faucet?** A service giving free test ETH.
32. **What is gas?** The fee unit for computation on Ethereum.
33. **What is the EVM?** The Ethereum Virtual Machine, a stack-based runtime executing bytecode.
34. **What is bytecode?** The compiled EVM opcodes stored and run on-chain.
35. **What is an ABI?** The JSON interface describing a contract's functions.
36. **What is a node?** A computer running the blockchain protocol.
37. **What is a full node?** A node storing the complete blockchain.
38. **What is a P2P network?** A peer-to-peer network where nodes connect directly.
39. **What is decentralisation?** No single central authority controls the network.
40. **What is immutability?** Past data cannot be changed.
41. **What is transparency in blockchain?** All transactions are publicly visible.
42. **What is a distributed ledger?** A ledger copied and synced across all nodes.
43. **What is consensus?** The rule by which nodes agree on one valid history.
44. **Name two consensus mechanisms.** Proof of Work and Proof of Stake.
45. **What is an NFT?** A unique, non-interchangeable digital asset.
46. **What is a wallet?** Software that manages keys, addresses, balance, and builds/signs transactions.
47. **What is a private key in Bitcoin?** A randomly generated 256-bit secret number.
48. **What is a Bitcoin address?** A 160-bit hash of the public key: RIPEMD160(SHA256(pubKey)).
49. **What is the locking script called?** scriptPubKey.
50. **What is the unlocking script called?** scriptSig.

### Medium Short Questions

1. **State the target formula.** target = mantissa * 2^(8*(exponent-3)).
2. **State the difficulty formula.** difficulty = difficulty_1_target / current_target.
3. **State the number-of-computations formula.** P * 600 = 2^n, so n = log(600P)/log(2).
4. **State the hash-rate-from-difficulty formula.** hashRate = difficulty * 2^32 / 600.
5. **How many computations for n leading zero bits?** About 2^n.
6. **What does a smaller target mean?** Harder mining, more leading zeros.
7. **How is txID computed?** SHA256(SHA256(txRecord)), 32 bytes.
8. **What is an OutPoint?** txID (32 bytes) + output index (4 bytes) = 36 bytes.
9. **List the six block header fields.** Version, previous block hash, Merkle root, timestamp, difficulty target (nBits), nonce.
10. **Why is the previous block hash in the header?** To chain blocks and enforce immutability.
11. **What happens to an odd number of Merkle leaves?** The last hash is duplicated for an even count.
12. **How many hashes prove a transaction is in a block?** log2(N) (the Merkle path).
13. **Explain transaction fee.** Inputs minus outputs; unaccounted value goes to the miner.
14. **Why is a change output created?** Because outputs are indivisible and must be spent fully.
15. **Why store the address (not the public key) in an output?** It is shorter; the public key is provided in scriptSig when spending.
16. **What are the P2PKH scripts?** scriptSig: <sig> <pubKey>; scriptPubKey: OP_DUP OP_HASH160 <address> OP_EQUALVERIFY OP_CHECKSIG.
17. **What does OP_CHECKSIG do?** Verifies the signature using the public key.
18. **What does OP_EQUALVERIFY do?** Checks the hashed public key equals the stored address; stops if not.
19. **Difference between Bitcoin and Ethereum?** Bitcoin is dedicated cash (UTxO, SHA-256, 10 min); Ethereum is a programmable platform (accounts, Ethash, 14 s, Solidity).
20. **What are the two Ethereum account types?** Externally Owned Account (EOA) and Smart Contract Account.
21. **What is the Ethereum account 4-tuple?** (nonce, balance, contract_code, storage).
22. **Difference between a transaction and a message (Ethereum)?** A transaction is signed by a wallet and mined; a message is sent by a contract and is virtual.
23. **What is the final transaction cost?** gas used * gas price.
24. **What happens if gas runs out?** The transaction fails.
25. **How many opcodes does the EVM have?** 140 (Turing complete).
26. **What is the EVM stack depth and item size?** 1024 items, each 256-bit (top 16 accessible).
27. **Difference between memory and storage in the EVM?** Memory is volatile and cleared each execution; storage is persistent and expensive to write.
28. **What does to: none mean when sending a transaction?** Create/deploy a contract.
29. **What does to: contractAddress mean?** Invoke the existing contract.
30. **What is the runtime code?** The bytecode RETURNed during deployment and stored on-chain.
31. **What does PUSH1 (0x60) do?** Pushes the next 1 byte onto the stack.
32. **What does SSTORE (0x55) do?** Writes a value to storage.
33. **What does MSTORE (0x52) do?** Writes a 32-byte word to memory.
34. **What does CALLVALUE do?** Pushes the wei sent with the transaction.
35. **Disassemble 0x6003600501.** PUSH1 0x03, PUSH1 0x05, ADD.
36. **What is the reward halving schedule?** Every 210,000 blocks: 50, 25, 12.5, 6.25, 3.125 BTC.
37. **How often does difficulty re-target?** Every 2,016 blocks (about 2 weeks).
38. **What is the maximum re-target change per cycle?** A factor of 4.
39. **What is a soft fork vs hard fork?** Soft fork is backward compatible (no new coin); hard fork is not (new coin, e.g. Bitcoin Cash).
40. **What curve does Bitcoin's ECDSA use?** SECP256K1.
41. **What byte order does Bitcoin use?** Little-endian.
42. **What does Base58 omit?** 0, O, l, I (error-prone characters).
43. **What is Base58Check?** Base58 with a 4-byte checksum appended.
44. **What is an SPV node?** A lightweight node storing only block headers.
45. **What port do Bitcoin nodes use?** TCP 8333.
46. **How does a 51% attack work?** Controlling most computing power to out-mine and rewrite recent blocks.
47. **What can a 51% attacker NOT do?** Steal coins he never owned (no private keys).
48. **What is the Genesis block?** The first block (height 0), created 9 Jan 2009.
49. **What is the UTxO set?** The set of all currently spendable outputs tracked by full nodes.
50. **Why double-hash?** Extra protection (e.g. against length-extension attacks) and consistency.

### Hard Short Questions

1. **Compute difficulty if difficulty_1 = 2^224 and current = 2^220.** 2^4 = 16.
2. **Find current target if difficulty = 8 and difficulty_1 = 2^240.** 2^240 / 8 = 2^237.
3. **Find n for P = 10^6.** n = log2(6*10^8) ~ 29.
4. **Find n for P = 10^20.** n = log2(6*10^22) ~ 75.
5. **Find P for n = 40.** P = 2^40 / 600 ~ 1.83*10^9 H/s.
6. **Difference in n for P = 10^6 vs 10^9?** About 10 bits.
7. **Convert nBits 0x1d00ffff to a target.** 65535 * 2^208 = 0x00000000FFFF0000...0000 (32 leading zero bits).
8. **Convert nBits 0x1705c739 to a target.** 0x05c739 * 2^160 (72 leading zero bits).
9. **What is difficulty for nBits 0x1705c739?** (65535/378681)*2^48 ~ 4.9*10^13.
10. **What does 0x6003600501600202600055 store?** (3+5)*2 = 16 (0x10) at slot 0.
11. **What does 0x6011600055 store?** 0x11 (17) at slot 0.
12. **What does 0x600a600302600055 store?** 10*3 = 30 at slot 0.
13. **Why store runtime code, not init code?** The EVM keeps only what RETURN leaves in memory at the end of the creation transaction.
14. **What happens if you send 0x67 to a save-data contract?** It is stored in the high-order bits: 0x67000...0 (zeros padded).
15. **What if you send 33 bytes?** Only the first 32 are saved; the extra byte is dropped and does not overflow.
16. **State the re-target equation.** newTarget = oldTarget * (actual time of last 2016 blocks / (2016 * 10 min)).
17. **How many blocks until reward stops?** 6,930,000 (= 33 * 210,000), around 2140.
18. **Why does reward stop at n = 32?** Because 50/(2^n) < 10^-8 gives n > 32.2, so it halts at n = 32.
19. **What is the attacker catch-up behaviour with z (p > q)?** Probability drops exponentially with z.
20. **What model does the white paper use for the attack race?** Binomial Random Walk / Gambler's Ruin.
21. **For q = 0.1, what z gives P < 0.1%?** z = 5.
22. **For q = 0.3, what z gives P < 0.1%?** z = 24.
23. **What is the probability of n zero bits?** 0.5^n.
24. **Compute hashRate for difficulty 4.9*10^13.** ~ 3.5*10^20 H/s (~ 350 EH/s).
25. **How many bits is each hex digit in a target?** 4.
26. **What is the size of an outPoint?** 36 bytes (32 + 4).
27. **What is the call stack depth limit?** 1024.
28. **What causes "stack too deep"?** Exceeding the top-16 directly accessible stack items.
29. **What does CODECOPY do during deployment?** Copies the runtime code into memory to be RETURNed.
30. **What does CALLDATALOAD do?** Pushes 32 bytes of transaction call data onto the stack.
31. **Disassemble 0x600035600055.** PUSH1 0x00, CALLDATALOAD, PUSH1 0x00, SSTORE (save call data at slot 0).
32. **Why are there PUSH1 to PUSH32?** To save gas by pushing only as many bytes as needed.
33. **What is 1 Exa hash approximated as (notes)?** ~ 10^12 (2^40).
34. **What did the n = 68 example use?** 100,000 CPUs at 10 TH/s each over 10 minutes.
35. **What did SegWit replace block size with?** Block weight (raising effective limit to ~4 MB).
36. **When did Ethereum move to PoS?** September 2022 (Week 9 slides describe PoW-era Ethereum).
37. **What is the difficulty-1 mantissa/exponent?** mantissa 0x00ffff, exponent 0x1d (29).
38. **What is the compactSize prefix 0xfe for?** A number stored in uint32 (4 bytes).
39. **What is the EVM formal tuple?** (block_state, transaction, message, code, memory, stack, pc, gas).
40. **Why can a contract bug not be simply patched?** Contracts are immutable once deployed; there is no UNDO.

### Very Important Exam Questions (most likely to appear)

1. **Explain the block structure with the 80-byte header.** (See 2.10 and diagram 6.2.)
2. **Draw and explain a Merkle tree and Merkle root.** (See 2.8 and diagram 6.3.)
3. **Explain the Bitcoin transaction chain (with the Quiz 1 diagram).** (See 2.11 and diagram 6.4.)
4. **Explain Proof of Work and mining step by step.** (See 2.6 and diagram 6.7.)
5. **Explain how blockchain prevents double spending.** (See 2.7.)
6. **Explain the UTxO model (UTxO vs STxO).** (See 2.9 and diagram 6.5.)
7. **Differentiate hashing and encryption.** (See 2.3, Quiz 1 Q4.)
8. **Explain digital signatures and their three guarantees.** (See 2.4.)
9. **Compute a target from nBits and count leading zeros.** (See 7.1, 7.2, 7.5.)
10. **Compute difficulty given two targets.** (See 7.4.)
11. **Compute the number of hash computations / n from hash rate.** (See 7.6.)
12. **Disassemble bytecode and give the stored value.** (See 7.8, 9.8.)
13. **Explain the locking and unlocking script flow (P2PKH).** (See 2.13 and diagram 6.6.)
14. **Explain the Ethereum smart contract deployment workflow.** (See 8.14 and diagram 6.8.)
15. **Differentiate Bitcoin and Ethereum.** (See 8.2.)
16. **Explain the EVM (stack, memory, storage, gas, opcodes).** (See 8.9, 9.6.)
17. **Explain creation vs invocation (to: none vs to: address).** (See 9.7.)
18. **Explain the two Ethereum account types (EOA vs contract).** (See 8.11.)
19. **Explain transactions vs messages in Ethereum.** (See 8.12.)
20. **Explain the coinbase transaction and reward halving.** (See 2.12, 5.)
21. **Explain consensus: PoW vs PoS.** (See Week 1 in Section 3.)
22. **Explain immutability via hash chaining.** (See 4.)
23. **Explain why Bitcoin does not encrypt data.** All records are public; it uses hashing and signatures only.
24. **Explain the longest-chain rule and forks.** (See 2.7, white paper Section 5.)
25. **Explain the 51% attack and its limits.** (See 5.)
26. **Explain wallets (deterministic vs nondeterministic).** (See 5.)
27. **Explain gas, gas price, gas limit, and final cost.** (See 8.8.)
28. **Explain the components of a blockchain (Week 1).** Digital signatures, hashing, consensus, distributed ledger, network nodes.
29. **Explain smart contracts with the vending machine analogy.** (See 8.3.)
30. **Explain how a transaction is verified (signature + funds).** (See 5, transaction verification.)

---

## 12. Long Theoretical Questions (with Answers)

**Q1. Explain blockchain structure with a diagram.**
A blockchain is a chain of blocks where each block has an 80-byte header and a body of transactions. The header holds the version, the previous block's header hash, the Merkle root, a timestamp, the difficulty target (nBits), and a nonce. Because each block stores the previous block's hash, editing any old block changes its hash and invalidates every later block, giving immutability. The body's transactions are summarised by a Merkle tree whose root sits in the header. (Draw diagram 6.2.)

**Q2. Explain the Bitcoin transaction chain.**
Each transaction has inputs and outputs. An output holds a value and a locking script with the recipient's address; it becomes a UTxO. To spend, a later transaction's input references that UTxO by txID and output index and supplies an unlocking script. Outputs are indivisible, so leftover value returns as change, and any unaccounted value becomes the miner's fee. Linking outputs to later inputs forms a chain whose integrity is protected by hashing. (Draw diagram 6.4.)

**Q3. Explain the Merkle tree and Merkle root.**
A Merkle tree is a binary hash tree. Each transaction is hashed (double SHA-256) into a leaf, leaves are paired and hashed into parents, and this repeats until one root remains, the Merkle root, stored in the block header. If there is an odd number of leaves, the last is duplicated. Benefits: efficient inclusion proofs needing only log2(N) hashes (the Merkle path), and pruning of spent transactions to save space. (Draw diagram 6.3.)

**Q4. Explain Proof of Work and mining.**
Miners collect valid transactions, build the Merkle root, and assemble the 80-byte header. They repeatedly change the nonce and compute hash = SHA256(SHA256(header)) until the hash is less than or equal to the target (begins with n zero bits). Because each bit is 0.5 probable, about 2^n attempts are needed. The first miner to succeed broadcasts the block and earns new coins plus fees. Others verify with a single hash. Difficulty auto-adjusts every 2016 blocks to keep a 10-minute pace. (Draw diagram 6.7.)

**Q5. Explain double spending and how blockchain prevents it.**
Double spending is reusing the same coins. Bitcoin prevents it because each input must reference an unspent output (UTxO); an output cannot be consumed twice. Nodes reject conflicting transactions, and when forks occur, the longest chain (most PoW) wins, discarding the other branch. Reversing a confirmed transaction requires redoing its PoW and all later blocks while outpacing the honest network (51% attack), which is computationally impractical.

**Q6. Explain the UTxO model.**
Bitcoin tracks value as Unspent Transaction Outputs. Each output is either spent (STxO) or unspent (UTxO). Full nodes maintain a UTxO set; spending consumes UTxOs (removing them) and creates new ones. Outputs are indivisible, so change outputs are common. A user's balance is the sum of UTxOs their keys can unlock.

**Q7. Explain block structure and transaction format.**
The block has a block size field, the 80-byte header (version, prev hash, Merkle root, timestamp, nBits, nonce), a transaction count, and the transaction array. A transaction has a version, input count and inputs (each referencing a UTxO with txID, index, scriptSig, sequence), output count and outputs (each with value and scriptPubKey), and lockTime. The first transaction is the coinbase.

**Q8. Explain Ethereum smart contract deployment.**
Write the contract in Solidity (Remix IDE), compile it to produce the ABI and EVM bytecode, then deploy by sending a transaction with an empty `to` field and `data` set to the bytecode. The EVM runs the init code and RETURNs the runtime code, stored at a new contract address. You connect a wallet (MetaMask), choose a network (e.g. Sepolia testnet), and pay gas using free test ETH from a faucet. Afterwards you interact by sending transactions to the contract address. (Draw diagram 6.8.)

**Q9. Compare Bitcoin and Ethereum.**
Bitcoin is dedicated digital cash using the UTxO model, double SHA-256, and a 10-minute block time. Ethereum is a general-purpose, programmable "world computer" using an account/state model, Ethash, a 14-second block time, and Solidity smart contracts. Both are permissionless. (See table 8.2.)

**Q10. Explain bytecode and the EVM.**
Bytecode is the EVM's machine language: a sequence of one-byte opcodes and arguments. The EVM is a stack-based processor with 140 opcodes, a 1024-deep stack of 256-bit items, volatile memory, and persistent storage. It executes bytecode opcode by opcode (tracked by the PC), charging gas per operation. Solidity compiles to this bytecode so it runs identically on every node.

**Q11. Explain digital signatures in Bitcoin.**
The owner signs a transaction hash with their private key, producing a signature kept in scriptSig along with the public key. Verifiers hash the public key to check it matches the address, then decrypt the signature with the public key and compare to the transaction hash. This guarantees authentication, non-repudiation, and integrity.

**Q12. Explain hashing and its role in Bitcoin.**
Hashing maps any input to a fixed 256-bit output, is one-way, and avalanches on any change. Bitcoin uses it for addresses (identity), transactions and blocks (identity + integrity), and Proof-of-Work (computational effort). Double hashing (SHA256 twice) is standard.

**Q13. Explain consensus and compare PoW and PoS.**
Consensus is how decentralised nodes agree on one history, preventing double spending. PoW makes block probability depend on computing power; miners earn rewards and a 51% attack needs majority computing power. PoS makes it depend on staked coins; validators earn fees and an attack needs majority stake. PoW uses far more energy; Ethereum moved to PoS in 2022.

**Q14. Explain immutability and transparency.**
Immutability comes from hash chaining: each block commits to the previous block's hash, so editing one breaks all later hashes. Transparency means all transactions are public; anyone can audit the ledger, though key owners remain pseudonymous.

**Q15. Explain wallets and key generation.**
A wallet manages keys, addresses, balance, and transaction building/signing. Keys: private (random 256-bit), public = SECP256K1(private), address = RIPEMD160(SHA256(public)). Wallets are nondeterministic (independent keys, JBOK) or deterministic (HD, all keys from one seed).

**Q16. Explain the coinbase transaction and reward halving.**
The coinbase is each block's first transaction; it pays the miner new coins plus fees and has no referenced UTxO. The new-coin reward halves every 210,000 blocks (50, 25, 12.5, 6.25, 3.125) until it cannot be halved (around 2140), capping supply near 21 million BTC.

**Q17. Explain the longest-chain rule and forks.**
Miners may produce competing blocks, creating a fork. Nodes treat the longest chain (greatest cumulative PoW) as valid and discard shorter branches. Ties resolve when the next block extends one branch, and nodes switch to it.

**Q18. Explain the 51% attack and its limitations.**
An attacker with majority computing power can out-mine the network to rewrite recent blocks and reverse their own spending. They cannot steal others' coins (no private keys) or create coins from nothing beyond legitimately re-mining the coinbase. Catch-up probability falls exponentially with confirmations.

**Q19. Explain gas in Ethereum.**
Every opcode costs gas, paid in Ether. The sender sets a gas price (Ether per gas) and gas limit (maximum gas). Final cost = gas used * gas price. If execution exceeds the gas limit, the transaction fails; if it uses less, the sender pays only for what was used. Writing storage is the most expensive operation.

**Q20. Explain EOA vs contract accounts.**
An EOA is controlled by a private key, holds no code, and is the source of every transaction. A contract account is controlled by its code, can hold storage, and runs when triggered by a transaction or message. Abstractly each is (nonce, balance, contract_code, storage).

**Q21. Explain contract creation vs invocation in the EVM.**
Sending a transaction with `to: none` tells the EVM the `data` is code to execute (deployment); the runtime code RETURNed is stored at a new address. Sending with `to: contractAddress` tells the EVM the `data` is input for the existing contract's code (invocation).

**Q22. Explain the Bitcoin scripting system (P2PKH).**
Outputs are locked by scriptPubKey (OP_DUP OP_HASH160 <address> OP_EQUALVERIFY OP_CHECKSIG). Inputs unlock with scriptSig (<sig> <pubKey>). Executing them on a stack first checks the hashed public key matches the address, then verifies the signature. (Draw diagram 6.6.)

**Q23. Explain difficulty and the difficulty target.**
The target is a 256-bit threshold stored compactly as nBits. A valid hash must be at or below it. difficulty = difficulty_1_target / current_target. Smaller targets mean more leading zeros and more work. Difficulty re-targets every 2016 blocks (max factor of 4) to maintain 10-minute blocks.

**Q24. Explain how the number of computations relates to difficulty.**
To find a hash with n leading zero bits you need about 2^n attempts. Given hash rate P, over a 10-minute block P*600 = 2^n, so n = log2(600P). Higher hash rate or higher n means exponentially more work.

**Q25. Explain the white paper's view of security (calculations section).**
The honest-vs-attacker race is a Binomial Random Walk (Gambler's Ruin). If honest nodes hold a CPU majority (p > q), the probability an attacker catches up from z blocks behind drops exponentially with z, which is why waiting for about 6 confirmations makes reversal practically impossible.

---

## 13. Diagram-Based Questions

For each: what to draw, how to label, what to write under it, and common mistakes.

1. **Blockchain chain of blocks.** Draw 3 linked blocks; label prevHash arrows pointing back. Write: hash chaining gives immutability. Mistake: arrows pointing forward.
2. **Block structure (80-byte header + body).** Draw header with 6 fields and a body with a Merkle tree. Write: hash(header) needs n zeros (PoW). Mistake: Merkle root in body.
3. **Merkle tree of 4 transactions.** Draw leaves Tx0..Tx3, parents Hash01/Hash23, root on top. Write the hash formulas. Mistake: root at the bottom.
4. **Bitcoin transaction chain (Quiz 1).** Draw txID_0..txID_6 with inputs/outputs and arrows. Write the path A to J. Mistake: forgetting the 10K fee at each step.
5. **UTxO model.** Draw an old output flowing into a new transaction's input, then new outputs. Write: outputs are indivisible, change returns. Mistake: showing partial spend of one output.
6. **Locking/unlocking script flow.** Draw scriptSig + scriptPubKey and the stack steps. Write: EQUALVERIFY then CHECKSIG. Mistake: checking signature before address.
7. **PoW mining flow.** Draw the loop with decision "hash <= target?". Write: change nonce on failure. Mistake: "hash == target".
8. **Digital signature signing/verifying.** Draw Alice signing with private key, verifier using public key. Write: authentication, non-repudiation, integrity. Mistake: signing with public key.
9. **Hashing input to fixed output.** Draw arbitrary-length input -> hash function -> fixed-length output. Write: one-way, avalanche. Mistake: showing a reverse arrow.
10. **PoW vs PoS comparison.** Draw two columns. Write: PoW = computing power, PoS = stake. Mistake: swapping the two.
11. **Centralised vs decentralised ledger.** Draw one central node vs a mesh of nodes. Write: decentralised removes single point of failure. Mistake: a hub-and-spoke for "decentralised".
12. **Ethereum as a state machine.** Draw Genesis State -> State 1 -> State 2 via transactions. Write: each state = a new block. Mistake: omitting the transactions on arrows.
13. **Ethereum smart contract deployment.** Draw Solidity -> compiler -> ABI + bytecode -> deploy -> contract address -> interact. Write: Remix, Sepolia, faucet, gas. Mistake: missing the compile-to-bytecode step.
14. **EVM components.** Draw PC, gas, stack, memory, storage, EVM code (ROM). Write: stack/memory volatile, storage persistent. Mistake: making storage volatile.
15. **EVM stack ADD operation.** Draw a stack before/after ADD (e.g. 7 and 2 become 9). Write: stack-based, RPN. Mistake: wrong operand order.
16. **Account types (EOA vs contract).** Draw both account states; EOA has no code/storage, contract has code hash + storage. Write: EOA controlled by key, contract by code. Mistake: giving the EOA code.
17. **Transaction vs message (Ethereum).** Draw wallet->contract (transaction) and contract->contract (message). Write: messages are virtual, not mined. Mistake: labelling contract->contract as a transaction.
18. **Bytecode disassembly table.** Draw the PC | Command | Opcode | Operation | Argument table. Write: opcode dictates argument count. Mistake: wrong PC offsets.
19. **Merkle tree after pruning (white paper).** Draw the tree keeping only Tx3 and the needed branch hashes. Write: spent transactions pruned, interior hashes not stored. Mistake: keeping all leaves.
20. **Simplified Payment Verification (SPV).** Draw block headers chain + a Merkle branch for one transaction. Write: SPV keeps headers only, verifies via Merkle branch. Mistake: storing full blocks.

---

## 14. Calculation Practice (40 Solved Problems)

### Easy

**C1.** nBits = 0x1d00ffff. Find the target.
Solution: exp = 29, mantissa = 0x00ffff = 65535. target = 65535 * 2^(8*(29-3)) = 65535 * 2^208. **Answer: 0x00ffff * 2^208.**

**C2.** How many leading zero bits in C1's target? Solution: hex form 00000000FFFF...; 8 hex zeros * 4 = **32 bits.**

**C3.** difficulty_1 = 2^224, current = 2^220. Find difficulty. Solution: 2^224/2^220 = 2^4 = **16.**

**C4.** difficulty_1 = 2^232, current = 2^224. Find difficulty. Solution: 2^(232-224) = 2^8 = **256.**

**C5.** P = 10^6 H/s. Find n. Solution: n = log2(600*10^6) = log2(6*10^8) ~ **29.**

**C6.** P = 10^9 H/s. Find n. Solution: n = log2(6*10^11) ~ **39.**

**C7.** Disassemble 0x6005600301. Solution: PUSH1 0x05, PUSH1 0x03, ADD. **Stack result: 8.**

**C8.** What does 0x6011600055 store? Solution: PUSH1 0x11, PUSH1 0x00, SSTORE. **Stores 17 (0x11) at slot 0.**

**C9.** How many satoshi in 1 BTC? Solution: 1 BTC = 10^8 satoshi = **100,000,000.**

**C10.** How many wei in 1 Ether? Solution: **10^18 wei.**

### Medium

**C11.** nBits = 0x1705c739. Find target and leading zeros. Solution: exp 23, mantissa 0x05c739. target = 0x05c739 * 2^160; 18 hex zeros = **72 leading zero bits.**

**C12.** mantissa = 0x1b0404, exp = 0x1d. Find target. Solution: 0x1b0404 = 1,770,500. target = 1,770,500 * 2^208 = **0x1b0404 * 2^208.**

**C13.** difficulty = 8, difficulty_1 = 2^240. Find current target. Solution: current = 2^240/8 = **2^237.**

**C14.** difficulty = 16, difficulty_1 = 2^224. Find current target. Solution: 2^224/16 = **2^220.**

**C15.** n = 40. Find P. Solution: P = 2^40/600 = 1.0995*10^12/600 ~ **1.83*10^9 H/s.**

**C16.** n = 30. Find P. Solution: P = 2^30/600 = 1.0737*10^9/600 ~ **1.79*10^6 H/s.**

**C17.** Compare A (mantissa 0x00ffff, exp 0x1d) and B (mantissa 0x00ffff, exp 0x1c). Solution: A = m*2^208, B = m*2^200; B smaller. **B is harder.**

**C18.** Compare current target 2^230 vs 2^220. Solution: 2^220 smaller. **2^220 is harder.**

**C19.** What does 0x6003600501600202600055 store? Solution: (3+5)*2 = 16. **Stores 0x10 = 16 at slot 0.**

**C20.** What does 0x600a600302600055 store? Solution: 10*3 = 30. **Stores 30 (0x1e) at slot 0.**

**C21.** difficulty for nBits 0x1705c739. Solution: (65535/378681)*2^(8*(29-23)) = 0.173*2^48 ~ **4.9*10^13.**

**C22.** hashRate for difficulty 4.9*10^13. Solution: 4.9*10^13 * 2^32 / 600 ~ **3.5*10^20 H/s.**

**C23.** Reward after 3 halvings from 50 BTC. Solution: 50 -> 25 -> 12.5 -> **6.25 BTC.**

**C24.** Reward after 4 halvings. Solution: **3.125 BTC.**

**C25.** outPoint size. Solution: txID 32 + index 4 = **36 bytes.**

### Hard

**C26.** P = 10^20 H/s. Find n. Solution: 600P = 6*10^22; n = log2(6*10^22) ~ **75.**

**C27.** Difference in n for P = 10^6 vs 10^9. Solution: log2(10^3) ~ **10 bits.**

**C28.** 100,000 CPUs at 10 TH/s for 10 min. Find n. Solution: total = 10^5 * 10^13 * 600 = 6*10^20; 2^n/2 = 6*10^20 gives **n = 68.**

**C29.** Convert 0x00ffff*2^208 to full 64-hex target. Solution: 0x00ffff shifted left 208 bits (52 hex) padded to 64 hex: **00000000FFFF0000000000000000000000000000000000000000000000000000.**

**C30.** Leading zeros of 0x05c739*2^160 counting inside 0x05. Solution: 72 (hex zeros) + 5 (zero bits in 0x05 = 00000101) = **77 leading zero bits.**

**C31.** Blocks until reward stops. Solution: 33 * 210,000 = **6,930,000 blocks.**

**C32.** Halving count where 50/2^n < 10^-8. Solution: 2^n > 5*10^9 gives n > 32.2, so halts at **n = 32.**

**C33.** Total computations to find a hash with 80 leading zeros. Solution: about **2^80 attempts.**

**C34.** If P doubles, change in achievable n. Solution: log2(2) = **+1 bit.**

**C35.** difficulty_1 = 2^256/2^224 form? difficulty_1_target ~ 32 leading zeros. If current target = 2^208, difficulty = 2^(224-208) = **2^16 = 65,536.** (Using 224-bit difficulty-1 reference.)

**C36.** Disassemble 0x600c600302. Solution: PUSH1 0x0c (12), PUSH1 0x03, MUL = 36. **Result 36 on stack.**

**C37.** Disassemble 0x600435020600055 carefully: PUSH1 0x04, then 0x35 CALLDATALOAD, 0x02 MUL... (illustrative) note opcode boundaries matter. Solution principle: **read 0x60 as PUSH1 consuming the next byte; the byte after a PUSH is its argument, not an opcode.**

**C38.** For q = 0.1, smallest z with P < 0.1%. Solution (white paper table): **z = 5.**

**C39.** For q = 0.3, smallest z with P < 0.1%. Solution: **z = 24.**

**C40.** Send 0x67 to a save-data contract; what is stored at slot 0? Solution: 0x67 then 31 zero bytes: **0x6700000000000000000000000000000000000000000000000000000000000000.**

### Exam-Level Mixed

**M1.** Given nBits 0x1d00ffff, find target, leading zeros, and difficulty (vs itself). Answer: target 0x00ffff*2^208, 32 zero bits, difficulty = 1 (it is the reference).

**M2.** A miner runs at P = 2*10^9 H/s. Find n for a 10-minute block. Answer: 600P = 1.2*10^12; n = log2(1.2*10^12) ~ 40.1, so **n ~ 40.**

**M3.** difficulty doubles. What happens to current target and leading zeros? Answer: target halves (smaller), leading zeros increase by 1, work doubles.

**M4.** Disassemble and evaluate 0x6002600301600202600055. Answer: PUSH 2, PUSH 3, ADD (5), PUSH 2, MUL (10), PUSH 0, SSTORE. **Stores 10 at slot 0.**

**M5.** From difficulty 4.9*10^13, estimate hash rate and compare to "385 EH/s". Answer: ~3.5*10^20 H/s = ~350 EH/s, close to the quoted 385 EH/s.

---

## 15. One-Day Study Plan

### Tonight (evening to night)

**Must-study topics (in order):**
1. Hashing, digital signatures, public/private keys (Sections 2.2 to 2.5).
2. Block structure, Merkle tree, transaction chain, UTxO (2.8 to 2.13) since these are guaranteed in Part 2.
3. Proof of Work and double spending (2.6, 2.7).
4. The three calculation families (Section 7): target, difficulty, computations.
5. Ethereum + smart contracts + bytecode (Sections 8 and 9).

**High-priority questions:** All 30 "Very Important Exam Questions" (Section 11) and the 25 long questions (Section 12).

**Diagrams to practice tonight (draw each twice):** Block structure (6.2), Merkle tree (6.3), transaction chain (6.4), PoW flow (6.7), smart contract deployment (6.8).

**Calculations to practice tonight:** C1 to C5, C11 to C16, C26 to C28, plus all bytecode disassembly (C7, C8, C19, C20, C36).

**Before sleeping:** Read Section 16 once, slowly.

### Tomorrow morning (before the exam)

1. Re-draw the 5 key diagrams from memory (15 minutes).
2. Re-do 5 calculations from memory: one target, one difficulty, one n-from-P, one bytecode (15 minutes).
3. Read Section 16 again (10 minutes).
4. Skim the tricky MCQs (Section 10) for traps (10 minutes).
5. Walk in calm. You have covered everything.

---

## 16. Last-Minute Revision Sheet

### Key definitions (one line each)
- **Blockchain:** distributed immutable ledger of hash-linked blocks.
- **Hashing:** one-way fixed-length fingerprint (SHA-256 = 256-bit).
- **Digital signature:** sign with private, verify with public; gives authentication, non-repudiation, integrity.
- **PoW:** prove computational effort; about 2^n work for n zero bits.
- **UTxO:** unspent output; an input must reference one; outputs are indivisible.
- **Merkle root:** top hash of all transactions, stored in the header.
- **Coinbase:** first transaction, pays the miner the reward.
- **EVM:** stack-based runtime executing bytecode, charges gas.
- **Gas:** fee per opcode; cost = gas used * gas price.
- **EOA vs contract:** key-controlled vs code-controlled accounts.

### Key formulas
```
target     = mantissa * 2^(8 * (exponent - 3))
difficulty = difficulty_1_target / current_target
P * 600    = 2^n        =>   n = log2(600P)
hashRate   = difficulty * 2^32 / 600
txID       = SHA256(SHA256(txRecord))
address    = RIPEMD160(SHA256(publicKey))
1 BTC      = 10^8 satoshi ;  1 Ether = 10^18 wei
```

### Must-remember diagrams
Block structure, Merkle tree, transaction chain, PoW flow, smart contract deployment. (Sections 6.2, 6.3, 6.4, 6.7, 6.8.)

### Important differences
- **Hashing vs encryption:** one-way vs two-way (with key).
- **UTxO vs STxO:** unspent (tracked) vs spent (not tracked).
- **scriptPubKey vs scriptSig:** locking vs unlocking.
- **PoW vs PoS:** computing power vs stake.
- **EOA vs contract account:** key vs code controlled.
- **Transaction vs message (Ethereum):** wallet-sent and mined vs contract-sent and virtual.
- **Soft fork vs hard fork:** backward compatible vs not.
- **Bitcoin vs Ethereum:** cash/UTxO/SHA-256/10 min vs platform/accounts/Ethash/14 s.

### Common MCQ traps
- Bitcoin does **not** encrypt data.
- Bigger target = **easier**, not harder.
- Sign with **private** key, verify with public.
- Merkle root is in the **header**, not the body.
- Reading storage is cheap; **writing** storage is expensive.
- `to: none` = create contract; `to: address` = invoke.
- difficulty = reference / current (not current / reference).

### Most repeated concepts (high yield)
SHA-256, Merkle root in header, PoW (2^n), UTxO/double spending, longest chain, digital signature trio, target/difficulty formulas, n = log2(600P), bytecode disassembly, EVM gas, smart contract deployment via Remix/Sepolia/faucet.

---

## 17. Final Exam Prediction

Based on the syllabus weighting and your uploaded material:

### Most likely MCQ topics (Part 1, 10 marks)
- Which hash Bitcoin uses (SHA-256); cryptocurrency uses SHA256.
- Where the Merkle root sits (header).
- What digital signatures provide.
- Ether/Ethereum facts (Buterin, gas, Solidity, Remix, Sepolia, faucet).
- PoW vs PoS; permissionless networks.
- Smallest units (satoshi, wei).
- "Public Distributed Ledger" ensures data cannot be altered.

### Most likely theoretical questions (Part 2, 20 marks)
- Block structure (almost certain).
- Merkle tree and Merkle root (almost certain).
- Bitcoin transaction chain (almost certain, likely the Quiz 1 diagram).
- Hashing vs encryption (it was a quiz item).
- Digital signatures and their three guarantees.
- Ethereum vs Bitcoin; EOA vs contract accounts; gas.

### Most likely diagram questions
- Block structure, Merkle tree, transaction chain (the three named in the syllabus).
- PoW mining flow and smart contract deployment.

### Most likely calculation questions (Part 3, 20 marks)
- Target from nBits + count leading zeros (very likely, matches Assignment 1 and 2).
- Difficulty from two targets (matches Assignments).
- Number of computations / n from hash rate (named in syllabus).
- Bytecode disassembly and stored value (named in syllabus; matches Week 11).

**Highest-confidence prediction:** Expect at least one leading-zeros/target problem, one difficulty problem, one n-from-P problem, and one bytecode problem in Part 3; and block structure + Merkle tree + transaction chain in Part 2.

---

## 18. Final Notes

- Everything in this guide comes from your uploaded material (Weeks 1, 2, 7, 9, 11, the white paper, Quiz 1, and Assignments 1 and 2).
- Study order: understand first (Sections 2 to 9), then drill questions (10 to 14), then revise (15 to 17).
- The 40 marks in Parts 2 and 3 are the most reliable to score. Lock in the diagrams and the four calculation types.
- Good luck. You are well prepared.
