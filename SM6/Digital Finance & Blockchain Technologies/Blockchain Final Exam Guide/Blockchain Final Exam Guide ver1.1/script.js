/* ══════════════════════════════════════════════════════════════
   BLOCKCHAIN STUDY APP — script.js
   All data + all logic. No external dependencies.
   Uses LocalStorage for persistence.
   ══════════════════════════════════════════════════════════════ */

// ─── SVG Icon library ───────────────────────────────────────
const ICON = {
  square:      `<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="3" width="18" height="18" rx="2"/></svg>`,
  halfCircle:  `<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M12 2a10 10 0 0 1 0 20"/><path d="M12 2v20"/></svg>`,
  checkSquare: `<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polyline points="9 11 12 14 22 4"/><path d="M21 12v7a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h11"/></svg>`,
  bookmark:    `<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M19 21l-7-5-7 5V5a2 2 0 0 1 2-2h10a2 2 0 0 1 2 2z"/></svg>`,
  bookmarkFill:`<svg width="14" height="14" viewBox="0 0 24 24" fill="currentColor" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M19 21l-7-5-7 5V5a2 2 0 0 1 2-2h10a2 2 0 0 1 2 2z"/></svg>`,
  check:       `<svg width="13" height="13" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round"><polyline points="20 6 9 17 4 12"/></svg>`,
  xCircle:     `<svg width="13" height="13" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="10"/><line x1="15" y1="9" x2="9" y2="15"/><line x1="9" y1="9" x2="15" y2="15"/></svg>`,
  alertTriangle:`<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M10.29 3.86L1.82 18a2 2 0 0 0 1.71 3h16.94a2 2 0 0 0 1.71-3L13.71 3.86a2 2 0 0 0-3.42 0z"/><line x1="12" y1="9" x2="12" y2="13"/><line x1="12" y1="17" x2="12.01" y2="17"/></svg>`,
  ruler:       `<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M21.3 8.7l-2-2a1 1 0 0 0-1.4 0l-12 12a1 1 0 0 0 0 1.4l2 2a1 1 0 0 0 1.4 0l12-12a1 1 0 0 0 0-1.4z"/><path d="M15.4 4.6l4 4"/><path d="M9.4 10.6l4 4"/><line x1="7.5" y1="14.5" x2="9.5" y2="16.5"/></svg>`,
  chevronRight:`<svg width="13" height="13" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polyline points="9 18 15 12 9 6"/></svg>`,
  eye:         `<svg width="13" height="13" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/></svg>`,
};

// ═══════════════════════════════════════════
// 1. DATA
// ═══════════════════════════════════════════

const TOPICS = [
  // Week 1 / Core Concepts
  { id: "t01", name: "Blockchain — Definition & Properties", week: "Week 1", priority: "high",
    notes: `<h4>Definition</h4><p>A blockchain is a distributed and decentralised digital ledger that records transactions in blocks, linked using cryptography (hashing), maintained by a network of nodes. Once added, data cannot be easily altered.</p>
    <h4>4 Core Properties — D-D-I-C</h4><ul><li><strong>Distributed</strong> — every node holds a copy</li><li><strong>Decentralised</strong> — no central authority</li><li><strong>Immutable</strong> — changing one block breaks all subsequent hashes</li><li><strong>Cryptographically linked</strong> — each block contains hash of the previous</li></ul>
    <h4>Key Exam Points</h4><ul><li>A blockchain is a "chain of blocks"; a block is a "collection of transactions".</li><li>Maintained collectively by nodes with no central authority.</li><li><strong>Does NOT encrypt data</strong> — uses hashing + digital signatures, not encryption for confidentiality.</li><li>"Public Distributed Ledger" ensures data cannot be altered (Week 1 quiz answer).</li></ul>
    <div class="trick">🧠 Memory Trick: <strong>D-D-I-C</strong> — Distributed, Decentralised, Immutable, Cryptographically linked</div>
    <div class="mistake">Common Mistake: Saying blockchain "encrypts" data. Bitcoin does NOT encrypt transactions — all records are public.</div>` },

  { id: "t02", name: "Cryptographic Hashing (SHA-256)", week: "Week 1", priority: "high",
    notes: `<h4>Definition</h4><p>A hash function converts any input into a fixed-length output (hash/digest/fingerprint). Bitcoin uses SHA-256 producing 256-bit output.</p>
    <h4>3 Key Properties — FUO</h4><ul><li><strong>Fixed-length output</strong>: any input → 256-bit output</li><li><strong>Unique (avalanche)</strong>: change 1 bit of input → completely different output</li><li><strong>One-way (trapdoor)</strong>: cannot reverse hash to get input</li></ul>
    <h4>Also: Collision resistant, computationally efficient</h4>
    <h4>Where Bitcoin uses hashing</h4><ul><li>Addresses: RIPEMD160(SHA256(pubKey))</li><li>Transactions: SHA256(SHA256(txRecord)) = txID</li><li>Blocks: SHA256(SHA256(header)) for integrity and PoW</li><li>Proof-of-Work: find hash with n leading zeros</li></ul>
    <h4>Key Numbers</h4><ul><li>SHA-256 output: 256 bits = 32 bytes = 64 hex characters</li><li>RIPEMD160 output: 160 bits (Bitcoin address)</li><li>Bitcoin always double-hashes: SHA256(SHA256(data))</li></ul>
    <div class="trick">🧠 FUO: Fixed, Unique (avalanche), One-way</div>
    <div class="mistake">Hashing ≠ Encryption. Hashing is one-way; encryption is two-way (with a key).</div>` },

  { id: "t03", name: "Hashing vs Encryption", week: "Week 1", priority: "high",
    notes: `<h4>Side-by-Side Comparison (Quiz 1, Q4)</h4>
    <table><tr><th>Feature</th><th>Hashing</th><th>Encryption</th></tr>
    <tr><td>Direction</td><td>One-way (cannot reverse)</td><td>Two-way (decrypt with key)</td></tr>
    <tr><td>Output length</td><td>Fixed (256-bit)</td><td>Varies with input</td></tr>
    <tr><td>Key needed?</td><td>No key</td><td>Needs a key</td></tr>
    <tr><td>Purpose in Bitcoin</td><td>Integrity, identity, PoW</td><td>NOT used for data in Bitcoin</td></tr>
    <tr><td>Examples</td><td>SHA-256, RIPEMD160</td><td>RSA, ECDSA, AES</td></tr></table>
    <h4>Exam-Ready Answer</h4><p>Hashing is a one-way function producing a fixed-length digest used for integrity and identity. Encryption is two-way using keys to convert plaintext to ciphertext and back. Bitcoin uses hashing (SHA-256, RIPEMD160) for integrity and PoW, and digital signatures for authentication, but does NOT encrypt transaction data because all records are public.</p>
    <div class="mistake">This is Quiz 1 Q4 (2 marks) — know this cold.</div>` },

  { id: "t04", name: "Digital Signatures", week: "Week 1", priority: "high",
    notes: `<h4>Definition</h4><p>A digital signature certifies a message using the signer's private key; anyone verifies using the signer's public key.</p>
    <h4>How it works (3 steps)</h4><ul><li>Alice hashes the transaction and signs (encrypts hash) with her <strong>private key</strong> → creates signature</li><li>She sends: message + signature + public key</li><li>Verifier decrypts signature with Alice's <strong>public key</strong>, compares to message hash. Match = valid.</li></ul>
    <h4>3 Guarantees — A-N-I</h4><ul><li><strong>Authentication</strong> — only private key owner could have signed</li><li><strong>Non-repudiation</strong> — signer cannot deny it</li><li><strong>Integrity</strong> — message was not tampered</li></ul>
    <h4>Key Exam Points</h4><ul><li>Uses asymmetric cryptography — RSA or ECDSA. Bitcoin uses ECDSA on SECP256K1 curve.</li><li>Quiz 1 Q3: provides <strong>integrity and authentication</strong> (option b)</li><li><strong>Sign with PRIVATE key, verify with PUBLIC key</strong></li></ul>
    <div class="trick">🧠 A-N-I: Authentication, Non-repudiation, Integrity. "Sign Private, Verify Public."</div>
    <div class="mistake">Never say you sign with the public key. Sign = private. Verify = public.</div>` },

  { id: "t05", name: "Public & Private Keys (Bitcoin)", week: "Week 2", priority: "medium",
    notes: `<h4>Key Generation Flow</h4><ul><li>privateKey k (256-bit) = random 256-bit number</li><li>publicKey K (256-bit) = SECP256K1(k) — elliptic curve, one-way</li><li>address (160-bit) = RIPEMD160(SHA256(K))</li></ul>
    <h4>Key Exam Points</h4><ul><li>Public key (or address) used to <strong>receive</strong>; private key used to <strong>send/sign</strong></li><li>Address = 160-bit; ~37.5% shorter than 256-bit public key</li><li>Cannot deduce private key from public key, nor public key from address</li></ul>
    <div class="trick">🧠 "Public to receive, Private to spend."</div>` },

  { id: "t06", name: "Proof of Work (PoW)", week: "Week 2", priority: "high",
    notes: `<h4>Definition</h4><p>A consensus protocol where a miner proves spent computational effort to earn the right to create the next block. Verifiers confirm with a single hash.</p>
    <h4>How it works (5 steps)</h4><ol><li>Collect valid transactions, build Merkle root, set timestamp</li><li>Target (n leading zeros) set by nBits in header</li><li>Pick a nonce, compute hash = SHA256(SHA256(blockHeader))</li><li>Change nonce and repeat until hash ≤ target (brute force)</li><li>First miner to succeed broadcasts block, earns reward</li></ol>
    <h4>Key Facts</h4><ul><li>Finding a hash with n zero bits requires ≈ 2^n computations</li><li>PoW = "one CPU one vote." Majority = longest chain.</li><li>Target block time = 10 minutes (Bitcoin)</li><li>Reward = new coins + transaction fees</li></ul>
    <div class="trick">🧠 "More zeros = smaller target = harder = more work (2^n)."</div>
    <div class="mistake">Hash must be LESS THAN OR EQUAL TO the target, not equal to.</div>` },

  { id: "t07", name: "Double Spending Prevention", week: "Week 2", priority: "medium",
    notes: `<h4>Definition</h4><p>Trying to spend the same coins (same UTxO) twice. A digital coin is just data and could be copied — preventing this without central authority is Bitcoin's core problem.</p>
    <h4>How Blockchain Prevents It</h4><ul><li>Every input must reference a specific <strong>unspent</strong> output (UTxO). An output cannot be consumed twice.</li><li>Nodes receiving both conflicting transactions discard both as invalid.</li><li>If two valid blocks appear (fork), the <strong>longest chain wins</strong>; losing branch is discarded.</li><li>To reverse a confirmed transaction: redo PoW for that block + all after it + outpace honest network (51% attack).</li></ul>
    <h4>Key Exam Points</h4><ul><li>Detected by tracing output to see if already spent</li><li>Wait for 6 blocks (~60 minutes) for safety</li><li>Attacker can only take back his own payment, not steal others' coins</li></ul>
    <div class="trick">🧠 "Spend twice, both die." (Both conflicting transactions rejected.)</div>` },

  { id: "t08", name: "Merkle Tree & Merkle Root", week: "Week 2", priority: "high",
    notes: `<h4>Definition</h4><p>A binary hash tree summarising all transactions in a block by repeatedly hashing pairs until a single hash — the Merkle root — remains. Only the root is stored in the block header.</p>
    <h4>Construction</h4><pre>Hash0   = SHA256(SHA256(Tx0))         // leaf
Hash01  = SHA256(SHA256(Hash0+Hash1)) // parent</pre>
    <p>Pair, hash, pair, hash until one root. Odd leaves → duplicate the last one.</p>
    <h4>Key Exam Points</h4><ul><li>Merkle root sits in the <strong>block header</strong> (Quiz 1 Q2 answer: option c)</li><li>To prove a tx is included: only log₂(N) hashes needed (Merkle path)</li><li>Allows old spent transactions to be pruned (disk space saving)</li></ul>
    <div class="trick">🧠 "Leaves at bottom, Root in the header, pair-and-hash upward."</div>
    <div class="mistake">Common mistake: drawing root at the bottom. Leaves (Tx0..Tx3) at bottom; root at TOP, in the header.</div>` },

  { id: "t09", name: "UTxO (Unspent Transaction Output)", week: "Week 2", priority: "high",
    notes: `<h4>Definition</h4><p>An output of a transaction is either already spent (STxO) or still spendable (UTxO).</p>
    <h4>How it works</h4><ul><li>An output holds a value (satoshi) and a locking script (recipient address)</li><li>Outputs are <strong>indivisible</strong> — must be spent entirely</li><li>Full nodes track all UTxOs in a UTxO set. STxOs are NOT tracked.</li><li>Your balance = sum of all UTxOs your keys can spend</li></ul>
    <h4>Key Exam Points</h4><ul><li>Input must reference a previous <strong>UTxO</strong> (via txID + output index)</li><li>Because outputs are indivisible, extra value returns as a <strong>change</strong> output</li><li>Any unaccounted input value = <strong>transaction fee</strong></li></ul>
    <div class="trick">🧠 "UTxO = unspent cash you still hold; STxO = receipt already used."</div>` },

  { id: "t10", name: "Block Structure (80-byte header)", week: "Week 2", priority: "high",
    notes: `<h4>The 80-byte Header — 6 Fields (V-P-M-T-D-N)</h4>
    <table><tr><th>Field</th><th>Size</th><th>Purpose</th></tr>
    <tr><td>Version</td><td>4 bytes</td><td>Software version</td></tr>
    <tr><td>Previous block header hash</td><td>32 bytes</td><td>Links to previous block (the chain)</td></tr>
    <tr><td>Merkle root</td><td>32 bytes</td><td>Root of all transactions' Merkle tree</td></tr>
    <tr><td>Timestamp</td><td>4 bytes</td><td>Unix epoch creation time</td></tr>
    <tr><td>Difficulty target (nBits)</td><td>4 bytes</td><td>PoW difficulty (leading zeros)</td></tr>
    <tr><td>Nonce</td><td>4 bytes</td><td>Number varied during mining</td></tr></table>
    <h4>Full Block</h4><p>Block size + 80-byte header + transaction count + transaction array. First transaction = coinbase. Cap ≈ 1 MB.</p>
    <h4>Key Exam Points</h4><ul><li>Header = exactly 80 bytes</li><li>4 four-byte fields: Version, Timestamp, nBits, Nonce</li><li>2 thirty-two-byte fields: prevHash, Merkle root</li><li>PoW requires header hash to begin with n zeros</li></ul>
    <div class="trick">🧠 V-P-M-T-D-N: Version, Previous hash, Merkle root, Timestamp, Difficulty, Nonce</div>
    <div class="mistake">Full transaction list is NOT in the 80-byte header. The Merkle ROOT is. (Quiz trap.)</div>` },

  { id: "t11", name: "Transaction Chain & Format", week: "Week 2", priority: "high",
    notes: `<h4>Transaction Top-Level Format</h4>
    <table><tr><th>Bytes</th><th>Field</th></tr>
    <tr><td>4</td><td>version</td></tr>
    <tr><td>1-9</td><td>txInCount + txInArray</td></tr>
    <tr><td>1-9</td><td>txOutCount + txOutArray</td></tr>
    <tr><td>4</td><td>lockTime</td></tr></table>
    <h4>Key Formulas</h4><pre>txID     = SHA256(SHA256(txRecord))   // 32-byte
outPoint = txID(32) + outputIndex(4) // 36-byte, identifies one UTxO</pre>
    <h4>Key Exam Points</h4><ul><li>Unit = satoshi = 10⁻⁸ BTC (1 BTC = 10⁸ satoshi)</li><li>Sum of inputs can exceed payment; extra goes back as change</li><li>compactSize = 1-9 byte variable-length integer for counts</li><li>outPoint = 32 + 4 = 36 bytes</li></ul>
    <div class="trick">🧠 "Inputs eat old UTxOs, outputs make new ones, txID = double hash."</div>` },

  { id: "t12", name: "Coinbase Transaction", week: "Week 2", priority: "medium",
    notes: `<h4>Definition</h4><p>The first transaction in every block. Pays the successful miner the reward (new coins + fees) and has no real input UTxO.</p>
    <h4>Key Exam Points</h4><ul><li>All bitcoins ever created came from coinbase transactions</li><li>Its input has a null referenced txID and null output index</li><li>Coinbase data is arbitrary — can be used as an extra nonce</li><li>Mining reward = new BTC + all transaction fees in the block</li></ul>
    <div class="trick">🧠 "Coinbase = the miner pays himself, born from nothing."</div>` },

  { id: "t13", name: "Locking & Unlocking Scripts (P2PKH)", week: "Week 2", priority: "medium",
    notes: `<h4>Scripts</h4><pre>scriptSig (unlock):    &lt;sig&gt; &lt;pubKeyA&gt;
scriptPubKey (lock):   OP_DUP OP_HASH160 &lt;addressA&gt; OP_EQUALVERIFY OP_CHECKSIG</pre>
    <h4>Stack Execution (left to right)</h4><ol>
    <li>push &lt;sig&gt;</li><li>push &lt;pubKeyA&gt;</li><li>OP_DUP — duplicate pubKey</li><li>OP_HASH160 — hash to address</li><li>push &lt;addressA&gt;</li><li>OP_EQUALVERIFY — check hashed pubKey = stored address</li><li>OP_CHECKSIG — verify signature against pubKey → TRUE</li></ol>
    <h4>Key Exam Points</h4><ul><li>Output stores only 160-bit address (hash). Spender provides pubKey in scriptSig.</li><li>scriptPubKey = locking; scriptSig = unlocking</li></ul>
    <div class="trick">🧠 "DUP, HASH160, EQUALVERIFY, CHECKSIG." Lock asks for address match then valid signature.</div>` },

  { id: "t14", name: "Difficulty Target & Leading Zeros", week: "Week 7", priority: "high",
    notes: `<h4>Formula</h4><pre>target = mantissa × 2^(8 × (exponent − 3))</pre>
    <p>nBits format: 0x[exponent][mantissa] — first byte = exponent, next 3 bytes = mantissa.</p>
    <h4>Example: nBits = 0x1d00ffff (difficulty-1 target)</h4><pre>exponent = 0x1d = 29, mantissa = 0x00ffff
target = 0x00ffff × 2^(8×(29−3)) = 0x00ffff × 2^208
Leading zeros: 8 hex zeros = 32 bits</pre>
    <h4>Key Exam Points</h4><ul><li>Smaller target = more leading zeros = harder mining</li><li>Each hex digit = 4 bits; count hex zeros × 4 = zero bits</li><li>difficulty_1 nBits = 0x1d00ffff</li></ul>
    <div class="trick">🧠 "Small target, many zeros, high difficulty."</div>
    <div class="mistake">Use (exponent − 3), NOT exponent. Don't mix decimal and hex.</div>` },

  { id: "t15", name: "Hash Rate & Number of Computations", week: "Week 7", priority: "high",
    notes: `<h4>Core Formula</h4><pre>P × 600 = 2^n  ⟹  n = log₂(600 × P)
hashRate = difficulty × 2^32 / 600</pre>
    <h4>Key Exam Points</h4><ul><li>P = hash rate in hashes/second; 600 = 10 minutes in seconds</li><li>To find n leading zero bits: ≈ 2^n computations needed</li><li>Each probability 0.5 per bit, so n bits → 0.5^n probability → 2^n average tries</li></ul>
    <h4>Example</h4><pre>P = 10^6 H/s: n = log₂(600×10^6) = log₂(6×10^8) ≈ 29.2 → n ≈ 29
P = 10^9 H/s: n ≈ 39.1 → n ≈ 39  (difference ≈ 10)</pre>
    <div class="trick">🧠 "600 seconds times hash rate equals 2 to the n."</div>
    <div class="mistake">Don't forget the 600! And use log base 2, not log base 10 (divide by log10(2) ≈ 0.301 if needed).</div>` },

  { id: "t16", name: "Difficulty Calculation", week: "Week 7", priority: "high",
    notes: `<h4>Formula</h4><pre>difficulty = difficulty_1_target / current_target</pre>
    <p>The difficulty_1_target (genesis/reference) = 0x00ffff × 2^208 (nBits 0x1d00ffff)</p>
    <h4>Simplified Form</h4><pre>difficulty ≈ (mantissa_1 / mantissa_current) × 2^(8×(exp_1 − exp_current))</pre>
    <h4>Example: nBits 0x1705c739</h4><pre>exponent = 0x17 = 23, mantissa = 0x05c739 = 378681
difficulty = (65535/378681) × 2^(8×(29−23)) = 0.173 × 2^48 ≈ 4.88×10^13</pre>
    <h4>Key Exam Points</h4><ul><li>Bigger difficulty = smaller target = harder</li><li>difficulty = reference/current (NOT current/reference)</li><li>Re-targets every 2016 blocks (~2 weeks)</li></ul>
    <div class="mistake">difficulty = reference/current, not current/reference!</div>` },

  // Ethereum
  { id: "t17", name: "Ethereum — Overview", week: "Week 9", priority: "high",
    notes: `<h4>Overview</h4><p>A public, decentralised, distributed, programmable blockchain ("world computer"). Proposed by <strong>Vitalik Buterin</strong> in late 2013.</p>
    <h4>Key Facts</h4><ul><li>Cryptocurrency: <strong>Ether</strong></li><li>Consensus (per notes): <strong>PoW</strong>; hash = <strong>Ethash</strong></li><li>Block time: <strong>14 seconds</strong> (Bitcoin = 10 minutes)</li><li>Turing-complete (supports general computation via smart contracts)</li><li>State machine: Genesis → State 1 → State 2… each state = new block</li><li>Smart contracts language: <strong>Solidity</strong></li></ul>
    <h4>Bitcoin vs Ethereum</h4>
    <table><tr><th>Feature</th><th>Bitcoin</th><th>Ethereum</th></tr>
    <tr><td>Purpose</td><td>Cryptocurrency</td><td>Programmable platform</td></tr>
    <tr><td>Currency</td><td>BTC</td><td>Ether</td></tr>
    <tr><td>Block time</td><td>10 minutes</td><td>14 seconds</td></tr>
    <tr><td>Hash function</td><td>SHA-256</td><td>Ethash</td></tr>
    <tr><td>Model</td><td>UTxO</td><td>Account/state</td></tr>
    <tr><td>Description</td><td>Digital cash</td><td>"World computer"</td></tr></table>` },

  { id: "t18", name: "Smart Contracts", week: "Week 9", priority: "high",
    notes: `<h4>Definition</h4><p>Self-executing programs stored and run on the blockchain. Automatically enforce "if…then" rules. Deterministic, trustless, secure, and <strong>immutable once deployed</strong>.</p>
    <h4>Key Facts</h4><ul><li>Term coined by <strong>Nick Szabo</strong> in the 1990s</li><li>Analogy: <strong>vending machine</strong> — input coins → deterministic output</li><li>Use cases: payments, dApps, supply chain, DeFi, crowdfunding, NFTs</li><li>On Ethereum: written in Solidity, compiled to EVM bytecode</li></ul>
    <div class="trick">🧠 "Vending machine: put coin in, get item out — no middleman."</div>` },

  { id: "t19", name: "Solidity, Remix IDE, Deployment", week: "Week 9", priority: "medium",
    notes: `<h4>Solidity</h4><p>Main Ethereum language for smart contracts. Compiles to EVM bytecode.</p>
    <h4>Remix IDE</h4><p>Browser-based IDE at remix.ethereum.org. Write, compile, deploy, and interact with contracts — no local node needed.</p>
    <h4>7-Step Practical Workflow</h4><ol><li>Open Remix IDE</li><li>Create a Solidity (.sol) file</li><li>Write the contract</li><li>Compile → produces ABI + bytecode</li><li>Deploy (connect MetaMask, choose network)</li><li>Use testnet + faucet (e.g. Sepolia + free test ETH) and pay gas</li><li>Interact with contract (call functions via transactions)</li></ol>
    <h4>Key Concepts</h4><ul><li>ABI = JSON interface of functions (how frontend calls them)</li><li>Bytecode = compiled EVM opcodes stored and run on-chain</li><li>Sepolia = popular Ethereum testnet</li><li>Faucet = service giving free test ETH</li></ul>` },

  { id: "t20", name: "EVM — Ethereum Virtual Machine", week: "Week 11", priority: "high",
    notes: `<h4>Definition</h4><p>Stack-based runtime executing bytecode. Makes code portable across machines. Formal tuple: (block_state, transaction, message, code, memory, stack, pc, gas).</p>
    <h4>EVM Specs</h4><ul><li>140 opcodes (Turing complete); each opcode = 1 byte</li><li>Stack depth = 1024 items; each item = 256-bit (32-byte) word</li><li>Top 16 stack items directly accessible (DUPx, SWAPx)</li><li>Program counter (PC) starts at 0</li></ul>
    <h4>Storage Areas</h4><ul><li><strong>Stack</strong>: fast, non-persistent, 32-byte items, top 16 accessible</li><li><strong>Memory</strong>: starts empty, byte-addressable, cleared at end of execution. MSTORE at offset n → bytes n to n+31</li><li><strong>Storage</strong>: 2^256 slots of 32 bytes, <strong>persistent</strong> across executions. SSTORE/SLOAD expensive.</li><li><strong>Call stack</strong>: limit 1024 deep</li></ul>
    <h4>Key Exam Points</h4><ul><li>Reading storage: cheap; <strong>Writing storage (SSTORE): very expensive</strong></li><li>Storage is persistent; memory is cleared each execution</li></ul>` },

  { id: "t21", name: "Gas (Ethereum)", week: "Week 9", priority: "high",
    notes: `<h4>Definition</h4><p>The fee unit for computation; every executed opcode costs gas.</p>
    <h4>Key Terms</h4><ul><li><strong>Gas</strong>: fee per opcode; uses miner's resources</li><li><strong>Gas price</strong>: how much Ether paid per unit of gas</li><li><strong>Gas limit</strong>: maximum gas sender allows</li><li><strong>Final cost = gas used × gas price</strong></li></ul>
    <h4>Opcode Gas Costs (sample)</h4><ul><li>STOP = 0; ADD = 3; MUL = 5; SUB = 3; DIV = 5; comparisons (LT/GT/EQ) = 3</li><li>Reading storage: cheap; <strong>SSTORE (write) = very expensive</strong></li></ul>
    <h4>Ether Units</h4><pre>1 Ether = 10^18 wei
1 gwei = 10^9 wei</pre>
    <div class="mistake">If transaction needs more than gas limit → it FAILS.</div>` },

  { id: "t22", name: "EOA vs Contract Account", week: "Week 9", priority: "high",
    notes: `<h4>Two Account Types</h4>
    <table><tr><th>Feature</th><th>EOA</th><th>Contract Account</th></tr>
    <tr><td>Controlled by</td><td>ECDSA private key</td><td>Contract code</td></tr>
    <tr><td>Has code?</td><td>No</td><td>Yes</td></tr>
    <tr><td>Can initiate tx?</td><td>Yes (always originates)</td><td>No (sends messages)</td></tr>
    <tr><td>Holds storage?</td><td>No</td><td>Yes</td></tr></table>
    <h4>Account 4-Tuple</h4><pre>(nonce, balance, contract_code, storage)</pre>
    <p>No contract_code → externally controlled (EOA).</p>
    <h4>Transactions vs Messages</h4><ul><li><strong>Transaction</strong>: signed data package always sent by EOA (wallet). Mined into block.</li><li><strong>Message</strong>: sent by a contract to another account. Exists virtually only. NOT mined.</li></ul>
    <div class="trick">🧠 EOA = key-controlled, Contract = code-controlled. Every transaction originates from an EOA.</div>` },

  { id: "t23", name: "Bytecode & Opcodes", week: "Week 11", priority: "high",
    notes: `<h4>Key Opcodes (memorise hex values)</h4>
    <table><tr><th>Hex</th><th>Opcode</th><th>Action</th><th>Gas</th></tr>
    <tr><td>0x60</td><td>PUSH1</td><td>Push 1 byte onto stack</td><td>3</td></tr>
    <tr><td>0x61</td><td>PUSH2</td><td>Push 2 bytes</td><td>3</td></tr>
    <tr><td>0x01</td><td>ADD</td><td>Pop two, push sum</td><td>3</td></tr>
    <tr><td>0x02</td><td>MUL</td><td>Pop two, push product</td><td>5</td></tr>
    <tr><td>0x03</td><td>SUB</td><td>Pop two, push difference</td><td>3</td></tr>
    <tr><td>0x35</td><td>CALLDATALOAD</td><td>Load 32 bytes of call data</td><td>3</td></tr>
    <tr><td>0x52</td><td>MSTORE</td><td>Write 32 bytes to memory</td><td>3</td></tr>
    <tr><td>0x55</td><td>SSTORE</td><td>Write to persistent storage</td><td>~20000</td></tr>
    <tr><td>0x34</td><td>CALLVALUE</td><td>Push wei sent with tx</td><td>2</td></tr>
    <tr><td>0xf3</td><td>RETURN</td><td>Return data from memory</td><td>0</td></tr></table>
    <h4>EVM is Stack-Based (RPN)</h4><p>3 5 + 2 * means (3+5)×2=16. Operands pushed first, operator pops and pushes result.</p>
    <h4>Key Rule</h4><p>0x60 = PUSH1, so "60 03" = PUSH1 0x03. The byte AFTER a PUSH opcode is its argument, NOT an opcode.</p>` },

  { id: "t24", name: "Contract Creation vs Invocation", week: "Week 11", priority: "high",
    notes: `<h4>The Key Distinction</h4><ul><li><strong>to: none/empty</strong> → Create/deploy a contract. EVM treats data field as init code to execute. Produces runtime bytecode stored at new address.</li><li><strong>to: contractAddress</strong> → Invoke an existing contract. EVM treats data field as input data (function call).</li></ul>
    <h4>Deployment Flow</h4><ol><li>Send tx with to=empty, data=bytecode</li><li>EVM runs init code</li><li>Init code must end with RETURN that returns runtime code</li><li>Runtime code stored at new contract address</li></ol>
    <h4>Hand-Assembled Example</h4><p>Save-data contract (runtime): <code>0x600035600055</code></p><pre>PUSH1 0x00  → CALLDATALOAD → PUSH1 0x00 → SSTORE</pre>
    <p>Sending 0x67 → stores 0x6700000…0 (padded to 32 bytes on left side).</p>
    <div class="mistake">to:none = create; to:address = invoke. MSTORE opcode = 0x52; SSTORE = 0x55.</div>` },

  // Week-based overviews
  { id: "t25", name: "Week 1 — Blockchain Overview", week: "Week 1", priority: "medium",
    notes: `<h4>Key Coverage</h4><ul><li>Motivation: lack of trust in centralised systems, need for transparency, immutability, reducing intermediaries</li><li>Centralised vs decentralised ledger</li><li>Transaction flow: request → block → broadcast → nodes validate → PoW reward → add to chain</li><li>5 Components: Digital Signatures, Hashing, Consensus, Distributed Ledger, Network Nodes</li><li>PoW vs PoS comparison</li><li>Smart contracts (Nick Szabo, 1990s), NFTs</li></ul>
    <h4>Quiz Answers</h4><ul><li>Cryptocurrency hashing algorithm = SHA256</li><li>"Cannot be altered" = Public Distributed Ledger</li><li>PoW: block prob ∝ computational power; PoS: block prob ∝ amount staked</li></ul>` },

  { id: "t26", name: "Week 2 — Bitcoin (White Paper)", week: "Week 2", priority: "medium",
    notes: `<h4>Key Coverage</h4><ul><li>White paper by Satoshi Nakamoto, 31 Oct 2008</li><li>Bitcoin v0.1.0 released 9 Jan 2009</li><li>Electronic coin = chain of digital signatures</li><li>Solves double spending via PoW; no central authority</li><li>Reward halving: 50→25→12.5→6.25→3.125 BTC every 210,000 blocks; cap ≈ 21 million BTC</li><li>Wallets: JBOK (nondeterministic) vs HD (deterministic, from seed)</li><li>51% attack: can only reclaim own spent coins</li><li>Soft fork (backward compatible) vs hard fork (new coin)</li><li>SPV nodes: keep only block headers</li><li>TCP port: 8333; block size: 1 MB; SegWit ≈ 4 MB</li></ul>` },

  { id: "t27", name: "Ethereum Account & Transaction Details", week: "Week 9", priority: "medium",
    notes: `<h4>Transaction Fields (sent by EOA)</h4><ul><li>Nonce, To, Value (wei), Gas Price, Gas Limit, Data, Signature (v, r, s)</li></ul>
    <h4>Nonce</h4><p>In an Ethereum account: prevents replay attacks and double spending. Increments with each transaction.</p>
    <h4>Ethereum Address</h4><p>20 bytes = 40 hex characters</p>
    <h4>Wallet</h4><p>MetaMask holds keys and signs transactions. Origin of every transaction = EOA with private key.</p>
    <h4>Ether Units</h4><pre>wei (1), gwei (10^9), Ether (10^18 wei)</pre>` },

  { id: "t28", name: "Bitcoin Halving & Supply", week: "Week 2", priority: "low",
    notes: `<h4>Halving Schedule</h4><ul><li>50 BTC (2009) → 25 BTC (2013) → 12.5 BTC (2017) → 6.25 BTC (2021) → 3.125 BTC (2024)</li><li>Every 210,000 blocks</li><li>Total supply cap ≈ 21 million BTC</li><li>Halving stops after ≈ 6,930,000 blocks (33 halvings)</li></ul>
    <h4>Difficulty Re-targeting</h4><p>Every 2,016 blocks (~2 weeks). Formula: oldTarget × (actual time / (2016 × 10 min)). Max change: factor of 4.</p>` },

  { id: "t29", name: "Bitcoin White Paper — Calculations Section", week: "Week 2", priority: "medium",
    notes: `<h4>Attacker Catch-Up Probability</h4><p>Modelled as a Binomial Random Walk (Gambler's Ruin). Probability drops exponentially with z (number of confirmations).</p>
    <h4>White Paper Table Results</h4><ul><li>q=0.1, P&lt;0.1% requires z=5</li><li>q=0.3, P&lt;0.1% requires z=24</li></ul>
    <h4>Key Idea</h4><p>An attacker with q fraction of hash power can only take back his own payment. Cannot steal others (lacks private keys). With z confirmations, his chance of catching up is (q/p)^z × something dropping exponentially.</p>` },

  { id: "t30", name: "NFTs & Other Blockchain Applications", week: "Week 1", priority: "low",
    notes: `<h4>NFTs</h4><p>Non-Fungible Tokens: unique, non-interchangeable digital assets representing ownership. Used in art, gaming, music, collectibles.</p>
    <h4>Permissioned vs Permissionless</h4><p>Bitcoin and Ethereum are <strong>permissionless</strong> — anyone can join and participate.</p>
    <h4>Base58 Encoding</h4><p>Used for Bitcoin addresses. Omits: 0 (zero), O (capital o), l (lowercase L), I (capital i) — to avoid visual confusion. Base58Check appends 4-byte checksum.</p>
    <h4>Bitcoin Byte Order</h4><p>Bitcoin uses little-endian byte order.</p>` },
];

// ═══════════════════════
// MCQs
// ═══════════════════════
const MCQS = [
  // EASY
  { id:"m01", diff:"easy", q:"Which hashing algorithm does Bitcoin use for PoW?", opts:["MD5","SHA-1","SHA-256","AES"], ans:2, exp:"Bitcoin uses double SHA-256 for Proof of Work and block identification." },
  { id:"m02", diff:"easy", q:"The Merkle root is stored in the:", opts:["Transaction list","Wallet","Block header","Mining pool"], ans:2, exp:"Merkle root sits in the block header (not the body). This is a classic trap." },
  { id:"m03", diff:"easy", q:"Digital signatures provide:", opts:["Confidentiality only","Integrity and authentication","Compression","Hashing"], ans:1, exp:"Quiz 1 Q3 answer: integrity and authentication (also non-repudiation — the ANI trio)." },
  { id:"m04", diff:"easy", q:"Bitcoin was proposed by:", opts:["Vitalik Buterin","Nick Szabo","Satoshi Nakamoto","Adam Back"], ans:2, exp:"Satoshi Nakamoto published the Bitcoin whitepaper on 31 Oct 2008." },
  { id:"m05", diff:"easy", q:"The Bitcoin white paper was published in:", opts:["2006","2008","2010","2013"], ans:1, exp:"31 October 2008." },
  { id:"m06", diff:"easy", q:"A blockchain is best described as:", opts:["Centralised database","Distributed immutable ledger","Cloud server","Single file"], ans:1, exp:"Distributed (every node has a copy) + immutable (hash-linked blocks)." },
  { id:"m07", diff:"easy", q:"Ether is the cryptocurrency of:", opts:["Bitcoin","Litecoin","Ethereum","Cardano"], ans:2, exp:"Ether is Ethereum's native cryptocurrency. BTC is Bitcoin's." },
  { id:"m08", diff:"easy", q:"Smart contracts are mainly associated with:", opts:["Bitcoin","Ethereum","Dogecoin","Ripple"], ans:1, exp:"Ethereum is the primary smart contract platform, using Solidity." },
  { id:"m09", diff:"easy", q:"The smallest unit of Bitcoin is:", opts:["wei","satoshi","gwei","bit"], ans:1, exp:"1 satoshi = 10⁻⁸ BTC. Named after Satoshi Nakamoto." },
  { id:"m10", diff:"easy", q:"The smallest unit related to Ether is:", opts:["satoshi","wei","gwei","finney"], ans:1, exp:"1 Ether = 10¹⁸ wei. Wei is named after Wei Dai." },
  { id:"m11", diff:"easy", q:"Proof of Work requires miners to vary the:", opts:["Merkle root","Timestamp only","Nonce","Version"], ans:2, exp:"Miners brute-force the nonce until the hash meets the target requirement." },
  { id:"m12", diff:"easy", q:"Bitcoin's target block time is:", opts:["1 minute","10 minutes","14 seconds","1 hour"], ans:1, exp:"Bitcoin targets 10 minutes per block. Difficulty re-adjusts every 2016 blocks." },
  { id:"m13", diff:"easy", q:"Ethereum's block time (per notes) is:", opts:["10 minutes","1 minute","14 seconds","30 seconds"], ans:2, exp:"Ethereum has ~14 second block times vs Bitcoin's 10 minutes." },
  { id:"m14", diff:"easy", q:"SHA-256 output length is:", opts:["128 bits","160 bits","256 bits","512 bits"], ans:2, exp:"SHA-256 = 256 bits = 32 bytes = 64 hex characters." },
  { id:"m15", diff:"easy", q:"A Bitcoin address is produced using:", opts:["SHA-256 only","RIPEMD160(SHA256(pubKey))","MD5","AES"], ans:1, exp:"address = RIPEMD160(SHA256(publicKey)). 160-bit output." },
  { id:"m16", diff:"easy", q:"Which key is used to SIGN a transaction?", opts:["Public key","Private key","Session key","Symmetric key"], ans:1, exp:"Sign with PRIVATE key. Verify with public key." },
  { id:"m17", diff:"easy", q:"Which key is used to VERIFY a signature?", opts:["Private key","Public key","Master key","Seed"], ans:1, exp:"Public key is shared with everyone and used for verification." },
  { id:"m18", diff:"easy", q:"The first transaction in a block is the:", opts:["Genesis transaction","Coinbase transaction","UTxO","Merkle transaction"], ans:1, exp:"Coinbase transaction pays the miner and has no real input UTxO." },
  { id:"m19", diff:"easy", q:"UTxO stands for:", opts:["Unique Transaction Output","Unspent Transaction Output","Used Transaction Output","Universal Token Output"], ans:1, exp:"UTxO = Unspent Transaction Output — the tracked, spendable unit in Bitcoin." },
  { id:"m20", diff:"easy", q:"An input of a transaction must reference a:", opts:["STxO","UTxO","Coinbase","Nonce"], ans:1, exp:"Inputs reference UTxOs (unspent outputs). STxOs are already spent and not tracked." },
  { id:"m21", diff:"easy", q:"The Bitcoin block header size is:", opts:["64 bytes","80 bytes","100 bytes","1 MB"], ans:1, exp:"Exactly 80 bytes: 4×4-byte fields + 2×32-byte fields." },
  { id:"m22", diff:"easy", q:"Hashing is a:", opts:["Two-way function","One-way function","Encryption scheme","Compression scheme"], ans:1, exp:"Hashing is irreversible (one-way). Encryption is two-way with a key." },
  { id:"m23", diff:"easy", q:"Which consensus does Bitcoin use?", opts:["PoS","PoW","PoA","PBFT"], ans:1, exp:"Bitcoin uses Proof of Work. Ethereum (per notes) also used PoW." },
  { id:"m24", diff:"easy", q:"The EVM is a:", opts:["Stack-based processor","Register machine","GPU","Database"], ans:0, exp:"The EVM is stack-based, not register-based like x86." },
  { id:"m25", diff:"easy", q:"Solidity compiles to:", opts:["Java bytecode","EVM bytecode","Machine code","WASM only"], ans:1, exp:"Solidity → EVM bytecode, which runs on all nodes' EVMs identically." },
  { id:"m26", diff:"easy", q:"Remix is a:", opts:["Wallet","Browser IDE for Solidity","Blockchain","Faucet"], ans:1, exp:"Remix IDE at remix.ethereum.org — write, compile, deploy Solidity contracts." },
  { id:"m27", diff:"easy", q:"Sepolia is a:", opts:["Wallet","Testnet","Token","Compiler"], ans:1, exp:"Sepolia is a popular Ethereum test network for deploying without real ETH." },
  { id:"m28", diff:"easy", q:"Gas in Ethereum is:", opts:["A coin","The fee unit for computation","A wallet","A block"], ans:1, exp:"Gas = computational cost unit. Every opcode costs gas. Final cost = gas used × gas price." },
  { id:"m29", diff:"easy", q:"Bitcoin and Ethereum are:", opts:["Permissioned","Permissionless","Private","Closed"], ans:1, exp:"Both are permissionless — anyone can join, validate, and transact." },
  { id:"m30", diff:"easy", q:"Smart contract term was coined by:", opts:["Satoshi","Vitalik","Nick Szabo","Adam Back"], ans:2, exp:"Nick Szabo coined 'smart contracts' in the 1990s. Vitalik proposed Ethereum in 2013." },
  { id:"m31", diff:"easy", q:"Mining reward currently consists of:", opts:["Only fees","New coins + transaction fees","Only new coins","Interest"], ans:1, exp:"Reward = newly created BTC (coinbase) + all transaction fees in the block." },
  { id:"m32", diff:"easy", q:"Vitalik Buterin proposed Ethereum in:", opts:["2008","2011","2013","2017"], ans:2, exp:"Vitalik published the Ethereum whitepaper in late 2013." },
  { id:"m33", diff:"easy", q:"Bitcoin's maximum supply is about:", opts:["1 million","21 million","100 million","Unlimited"], ans:1, exp:"~21 million BTC hard cap. Mining rewards halve every 210,000 blocks." },
  { id:"m34", diff:"easy", q:"The locking script in Bitcoin is called:", opts:["scriptSig","scriptPubKey","coinbase","nonce"], ans:1, exp:"scriptPubKey locks the output. scriptSig (unlocking) satisfies it to spend." },
  { id:"m35", diff:"easy", q:"Which ensures data cannot be altered? (Week 1 quiz)", opts:["Public Distributed Ledger","PoW only","PoS only","Hash encryption"], ans:0, exp:"'Public Distributed Ledger' is the Week 1 quiz slide answer." },
  { id:"m36", diff:"easy", q:"Cryptocurrency uses which hashing algorithm? (Week 1 quiz)", opts:["Scrypt","Ethash","SHA256","None"], ans:2, exp:"SHA256 is the Week 1 quiz answer for the hashing algorithm used by cryptocurrency." },
  { id:"m37", diff:"easy", q:"Each opcode in the EVM takes:", opts:["1 byte","4 bytes","32 bytes","256 bytes"], ans:0, exp:"Each EVM opcode = 1 byte. Stack items = 32 bytes." },
  { id:"m38", diff:"easy", q:"EVM stack item size is:", opts:["8 bits","32 bits","256 bits","512 bits"], ans:2, exp:"EVM stack items = 256 bits = 32 bytes. PC starts at 0." },
  { id:"m39", diff:"easy", q:"Storage in the EVM is:", opts:["Volatile","Persistent","Cleared each call","On the stack"], ans:1, exp:"Storage is persistent across executions (SSTORE/SLOAD). Memory is cleared each call." },
  { id:"m40", diff:"easy", q:"PUSH1 opcode in hex is:", opts:["0x50","0x60","0x55","0x01"], ans:1, exp:"0x60 = PUSH1. 0x61 = PUSH2. 0x55 = SSTORE. 0x01 = ADD." },
  { id:"m41", diff:"easy", q:"SSTORE writes to:", opts:["Stack","Memory","Storage","Call stack"], ans:2, exp:"SSTORE (0x55) writes to persistent storage. MSTORE (0x52) writes to memory." },
  { id:"m42", diff:"easy", q:"The coinbase tx input references:", opts:["A UTxO","No previous UTxO (null)","The Merkle root","The nonce"], ans:1, exp:"Coinbase tx has no real input — it references null. It's how new BTC is created." },
  { id:"m43", diff:"easy", q:"A change output exists because Bitcoin outputs are:", opts:["Divisible","Indivisible","Encrypted","Free"], ans:1, exp:"Outputs are indivisible — spent entirely. Leftover value returns as a change output." },
  { id:"m44", diff:"easy", q:"Halving happens every:", opts:["10,000 blocks","210,000 blocks","2,016 blocks","1 year"], ans:1, exp:"Every 210,000 blocks (≈4 years) the block reward halves." },
  { id:"m45", diff:"easy", q:"Difficulty re-targets every:", opts:["210,000 blocks","2,016 blocks","144 blocks","Every block"], ans:1, exp:"Every 2,016 blocks (≈2 weeks), difficulty adjusts to maintain 10-minute block time." },
  { id:"m46", diff:"easy", q:"A soft fork is:", opts:["Backward compatible","Not compatible","Always a new coin","A wallet"], ans:0, exp:"Soft fork = backward compatible (no new chain). Hard fork = not compatible (may create new coin)." },
  { id:"m47", diff:"easy", q:"Bitcoin uses which signature algorithm?", opts:["RSA","ECDSA (SECP256K1)","DSA","AES"], ans:1, exp:"Bitcoin uses ECDSA on the SECP256K1 elliptic curve." },
  { id:"m48", diff:"easy", q:"An EOA is controlled by:", opts:["Contract code","A private key","The EVM","A faucet"], ans:1, exp:"EOA (Externally Owned Account) = key-controlled. Contract accounts = code-controlled." },
  { id:"m49", diff:"easy", q:"The block reward in 2021 was:", opts:["50 BTC","25 BTC","12.5 BTC","6.25 BTC"], ans:3, exp:"2021 reward was 6.25 BTC (halved from 12.5 in 2020). 2024 halved to 3.125 BTC." },
  { id:"m50", diff:"easy", q:"Recommended confirmations for safety (Bitcoin):", opts:["1 block","3 blocks","6 blocks","100 blocks"], ans:2, exp:"6 blocks (≈60 minutes) is the standard safe confirmation count." },

  // MEDIUM
  { id:"m51", diff:"medium", q:"To find a hash with n leading zero bits, you need about:", opts:["n","2n","2^n","n^2"], ans:2, exp:"Probability of each bit being 0 is 0.5, so P(n zeros) = 0.5^n → need 2^n average tries." },
  { id:"m52", diff:"medium", q:"The target formula is:", opts:["mantissa × 2^(8×exponent)","mantissa × 2^(8×(exponent−3))","mantissa / exponent","2^exponent"], ans:1, exp:"target = mantissa × 2^(8×(exponent−3)). The '−3' is critical!" },
  { id:"m53", diff:"medium", q:"Difficulty equals:", opts:["current/difficulty_1_target","difficulty_1_target/current_target","target×nonce","hashRate×600"], ans:1, exp:"difficulty = difficulty_1_target / current_target. Note the order!" },
  { id:"m54", diff:"medium", q:"A smaller target means:", opts:["Easier mining","More leading zeros and harder mining","Fewer zeros","No change"], ans:1, exp:"Smaller target → more leading zeros required → more work (harder). Bigger target = easier." },
  { id:"m55", diff:"medium", q:"For nBits 0x1d00ffff, the exponent is:", opts:["0x00","0xff","0x1d (29)","0xffff"], ans:2, exp:"nBits = 0x[exponent][mantissa]. First byte 0x1d = 29 is the exponent." },
  { id:"m56", diff:"medium", q:"For nBits 0x1d00ffff, the mantissa is:", opts:["0x1d","0x00ffff","0xffff00","0x29"], ans:1, exp:"Bytes 2-4 of nBits = 0x00ffff = 65535. This is the difficulty-1 (genesis) target." },
  { id:"m57", diff:"medium", q:"n = log(600P)/log(2) computes:", opts:["Hash rate","Difficulty in bits (computations)","Block size","Reward"], ans:1, exp:"n = log₂(600×P) gives the number of leading zero bits matching the required work." },
  { id:"m58", diff:"medium", q:"hashRate = difficulty × 2^32 / (blank):", opts:["60","600","2016","210000"], ans:1, exp:"hashRate = difficulty × 2^32 / 600 (600 seconds = 10 minutes)." },
  { id:"m59", diff:"medium", q:"txID is computed as:", opts:["SHA256(tx)","SHA256(SHA256(txRecord))","RIPEMD160(tx)","MD5(tx)"], ans:1, exp:"txID = double SHA-256 of the entire transaction record. Always double-hash in Bitcoin." },
  { id:"m60", diff:"medium", q:"An OutPoint is:", opts:["txID only","txID + output index","Address","Nonce"], ans:1, exp:"outPoint = txID (32 bytes) + outputIndex (4 bytes) = 36 bytes. Identifies one UTxO." },
  { id:"m61", diff:"medium", q:"Which opcode duplicates the top stack value?", opts:["OP_HASH160","OP_DUP","OP_EQUALVERIFY","OP_CHECKSIG"], ans:1, exp:"OP_DUP duplicates the top stack item. Used in P2PKH to check the public key." },
  { id:"m62", diff:"medium", q:"The Merkle tree handles an odd number of leaves by:", opts:["Dropping the last tx","Duplicating the last hash","Adding a zero","Splitting it"], ans:1, exp:"Odd leaves → duplicate the last hash to make the count even." },
  { id:"m63", diff:"medium", q:"To prove a tx is in a block you need about:", opts:["N hashes","log₂(N) hashes","N² hashes","1 hash"], ans:1, exp:"Merkle path/branch length = log₂(N). Very efficient verification." },
  { id:"m64", diff:"medium", q:"Reading EVM storage is:", opts:["Very expensive","Cheap/free relative to writing","Impossible","On the stack"], ans:1, exp:"SLOAD (read) is cheap. SSTORE (write) is very expensive (~20000 gas)." },
  { id:"m65", diff:"medium", q:"Writing EVM storage (SSTORE) is:", opts:["Free","Cheap","Very expensive","Disabled"], ans:2, exp:"SSTORE costs ~20000 gas — the most expensive common operation in the EVM." },
  { id:"m66", diff:"medium", q:"An Ethereum account 4-tuple is:", opts:["(nonce, balance, code, storage)","(key, value, hash, nonce)","(to, from, value, gas)","(pc, stack, memory, gas)"], ans:0, exp:"(nonce, balance, contract_code, storage). If no code → EOA." },
  { id:"m67", diff:"medium", q:"A message in Ethereum is sent by:", opts:["A wallet","A contract","A miner","The EVM only"], ans:1, exp:"Messages are sent by contracts to other accounts (virtual, not mined). Transactions are sent by wallets." },
  { id:"m68", diff:"medium", q:"A transaction in Ethereum is always sent by:", opts:["A contract","A wallet (EOA)","The EVM","A faucet"], ans:1, exp:"Every transaction originates from an EOA (wallet). Contracts send messages, not transactions." },
  { id:"m69", diff:"medium", q:"Final transaction cost in Ethereum is:", opts:["gas + gas price","gas used × gas price","gas limit only","value × gas"], ans:1, exp:"Cost = gas_used × gas_price. If tx uses less than limit, you pay only for what's used." },
  { id:"m70", diff:"medium", q:"EVM stack depth is:", opts:["16","256","1024","Unlimited"], ans:2, exp:"EVM stack can hold 1024 items. Top 16 are directly accessible via DUPx/SWAPx." },
  { id:"m71", diff:"medium", q:"Sending a transaction with to: none means:", opts:["Invoke a contract","Create/deploy a contract","Transfer ETH","Nothing"], ans:1, exp:"to: none → deploy a contract. to: existingAddress → invoke that contract." },
  { id:"m72", diff:"medium", q:"PUSH2 opcode is:", opts:["0x60","0x61","0x62","0x52"], ans:1, exp:"PUSH1=0x60, PUSH2=0x61, PUSH3=0x62... MSTORE=0x52, SSTORE=0x55." },
  { id:"m73", diff:"medium", q:"MSTORE opcode is:", opts:["0x52","0x55","0x51","0x60"], ans:0, exp:"MSTORE=0x52 (writes to memory). SSTORE=0x55 (writes to persistent storage)." },
  { id:"m74", diff:"medium", q:"The block reward in 2024 is:", opts:["6.25 BTC","3.125 BTC","12.5 BTC","1.5625 BTC"], ans:1, exp:"After the 2024 halving: 3.125 BTC. (6.25 → 3.125)." },
  { id:"m75", diff:"medium", q:"difficulty_1 nBits is:", opts:["0x1705c739","0x1d00ffff","0x00000000","0xffffffff"], ans:1, exp:"0x1d00ffff is the genesis/difficulty-1 target nBits. All difficulty calculations reference this." },
  { id:"m76", diff:"medium", q:"Ethereum hash function (per notes):", opts:["SHA-256","Ethash","Scrypt","Keccak only"], ans:1, exp:"Ethereum uses Ethash. Bitcoin uses SHA-256 (double). Both are different algorithms." },
  { id:"m77", diff:"medium", q:"An Ethereum address is how many hex characters:", opts:["64","40","128","20"], ans:1, exp:"20 bytes = 40 hex characters. Compare: Bitcoin address = 160 bits = 20 bytes too." },
  { id:"m78", diff:"medium", q:"Which is NOT in the 80-byte header?", opts:["Version","Merkle root","Full transaction list","Nonce"], ans:2, exp:"Full transaction list is in the block BODY, not the 80-byte header. Header has Merkle ROOT." },
  { id:"m79", diff:"medium", q:"txID size is:", opts:["20 bytes","32 bytes","4 bytes","64 bytes"], ans:1, exp:"txID = SHA256(SHA256(txRecord)) = 32 bytes = 64 hex chars." },
  { id:"m80", diff:"medium", q:"Each hex digit in a target represents:", opts:["1 bit","2 bits","4 bits","8 bits"], ans:2, exp:"1 hex digit = 4 bits. Count hex zeros × 4 = leading zero BITS." },

  // HARD
  { id:"m81", diff:"hard", q:"nBits 0x1705c739 gives leading zeros of about:", opts:["32 bits","72 bits","8 bits","16 bits"], ans:1, exp:"exp=0x17=23, mantissa=0x05c739. target=0x05c739×2^160. 18 hex zeros = 72 bits." },
  { id:"m82", diff:"hard", q:"If difficulty_1_target = 2^224 and current = 2^220, difficulty is:", opts:["4","8","16","2"], ans:2, exp:"difficulty = 2^224 / 2^220 = 2^4 = 16." },
  { id:"m83", diff:"hard", q:"If difficulty=8, difficulty_1=2^240, current target is:", opts:["2^243","2^237","2^240","2^30"], ans:1, exp:"current = difficulty_1_target / difficulty = 2^240 / 8 = 2^240 / 2^3 = 2^237." },
  { id:"m84", diff:"hard", q:"For P = 10^6 H/s, n is about:", opts:["20","29","40","68"], ans:1, exp:"n = log₂(600×10^6) = log₂(6×10^8) ≈ 29.2 → n ≈ 29." },
  { id:"m85", diff:"hard", q:"For P = 10^9 H/s, n is about:", opts:["29","39","49","68"], ans:1, exp:"n = log₂(600×10^9) = log₂(6×10^11) ≈ 39.1 → n ≈ 39." },
  { id:"m86", diff:"hard", q:"If n = 40, hash rate P is about:", opts:["1.8 × 10^9","6 × 10^8","10^6","2^40"], ans:0, exp:"P = 2^40 / 600 = 1,099,511,627,776 / 600 ≈ 1.83 × 10^9 H/s ≈ 1.8 GH/s." },
  { id:"m87", diff:"hard", q:"Difference in n between P=10^6 and P=10^9 is about:", opts:["3","6","10","30"], ans:2, exp:"Ratio = 10^3; log₂(10^3) = 3×log₂(10) ≈ 3×3.32 ≈ 9.97 → difference ≈ 10 bits." },
  { id:"m88", diff:"hard", q:"Bytecode 0x6003600501600202600055 stores at slot 0:", opts:["8","16","32","0"], ans:1, exp:"PUSH1 3, PUSH1 5, ADD(8), PUSH1 2, MUL(16), PUSH1 0, SSTORE → stores 16 (0x10)." },
  { id:"m89", diff:"hard", q:"Bytecode 0x6011600055 stores at slot 0:", opts:["0x11 (17)","0x10 (16)","0","0x55"], ans:0, exp:"PUSH1 0x11 (=17), PUSH1 0x00, SSTORE → stores 17 at slot 0." },
  { id:"m90", diff:"hard", q:"In 0x600035600055, 0x35 is:", opts:["PUSH1","CALLDATALOAD","SSTORE","ADD"], ans:1, exp:"60 = PUSH1 (consumes next byte 0x00), then 0x35 = CALLDATALOAD." },
  { id:"m91", diff:"hard", q:"Sending 0x67 to a save-data contract stores:", opts:["0x000...067","0x6700...0 (high bits)","Nothing","Error"], ans:1, exp:"EVM reads 32 bytes, left-pads missing bytes. 0x67 goes to highest byte → 0x6700...0." },
  { id:"m92", diff:"hard", q:"hashRate from difficulty 4.9×10^13 is about:", opts:["3.5×10^20 H/s","10^6 H/s","600 H/s","2^32"], ans:0, exp:"hashRate = 4.9×10^13 × 2^32 / 600 ≈ 4.9×10^13 × 4.295×10^9 / 600 ≈ 3.5×10^20 H/s." },
  { id:"m93", diff:"hard", q:"Bytecode 0x600a600302600055 stores:", opts:["13","30","10","3"], ans:1, exp:"PUSH1 10, PUSH1 3, MUL(30), PUSH1 0, SSTORE → stores 30." },
  { id:"m94", diff:"hard", q:"For q=0.1, P<0.1% requires z =:", opts:["3","5","11","24"], ans:1, exp:"From the white paper table: q=0.1, z=5 gives P<0.1%." },
  { id:"m95", diff:"hard", q:"For q=0.3, P<0.1% requires z =:", opts:["5","11","24","89"], ans:2, exp:"From the white paper table: q=0.3, z=24 gives P<0.1%." },
  { id:"m96", diff:"hard", q:"If P doubles, achievable n increases by about:", opts:["0","1","2","10"], ans:1, exp:"log₂(2P×600) = log₂(600P) + log₂(2) = n + 1. Doubling P adds exactly 1 bit." },
  { id:"m97", diff:"hard", q:"The difficulty formula gives 4.9×10^13 from nBits 0x1705c739. What's the mantissa?", opts:["0x1d","0x1705","0x05c739","0xc739"], ans:2, exp:"nBits = 0x[exp][mantissa]. exp=0x17, mantissa=0x05c739=378681." },
  { id:"m98", diff:"hard", q:"The probability of n zero bits is:", opts:["0.5×n","0.5^n","n^2","2^n"], ans:1, exp:"Each bit has 0.5 chance of being zero. P(n zeros) = 0.5^n = 1/2^n." },
  { id:"m99", diff:"hard", q:"In RPN, '3 5 + 2 *' equals:", opts:["11","16","13","30"], ans:1, exp:"(3+5)×2 = 8×2 = 16. EVM is stack-based — this is how it computes." },
  { id:"m100", diff:"hard", q:"CODECOPY is used during:", opts:["Invocation only","Contract deployment to copy runtime code","Hashing","Mining"], ans:1, exp:"CODECOPY copies runtime bytecode during deployment init code execution." },
];

// ═══════════════════════
// QUESTION BANK
// ═══════════════════════
const QUESTIONS = {
  short: [
    { id:"sq01", q:"What is a blockchain?", a:"A blockchain is a distributed, decentralised, immutable digital ledger that records transactions in cryptographically linked blocks. It is maintained by a network of nodes with no central authority. Changing one block invalidates all subsequent block hashes." },
    { id:"sq02", q:"What are the three guarantees of a digital signature?", a:"Authentication (only the private key owner could have signed), Non-repudiation (signer cannot deny it), Integrity (message was not tampered with). Acronym: ANI." },
    { id:"sq03", q:"What is the difference between hashing and encryption?", a:"Hashing: one-way, fixed-length output, no key, used for integrity/identity. Encryption: two-way, variable output, needs a key, used for confidentiality. Bitcoin uses hashing (SHA-256) but does NOT encrypt transaction data." },
    { id:"sq04", q:"What is Proof of Work?", a:"A consensus mechanism where miners prove computational effort by finding a hash (SHA256(SHA256(header))) with n leading zero bits (below the target). This requires ~2^n attempts. The first miner to succeed earns the block reward. Verification requires only one hash." },
    { id:"sq05", q:"What is a UTxO?", a:"Unspent Transaction Output. A discrete, indivisible unit of bitcoin value locked by a script. Inputs reference specific UTxOs. Outputs that have been spent become STxOs (no longer tracked). Your balance = sum of UTxOs your keys can spend." },
    { id:"sq06", q:"List the 6 fields of a Bitcoin block header.", a:"Version (4B), Previous Block Header Hash (32B), Merkle Root (32B), Timestamp (4B), Difficulty Target nBits (4B), Nonce (4B). Total = 80 bytes. Mnemonic: V-P-M-T-D-N." },
    { id:"sq07", q:"What is the Merkle root and where is it stored?", a:"The Merkle root is the single top-level hash of a binary hash tree summarising all transactions in a block. It is stored in the block HEADER (not the body). Allows log₂(N) proof of transaction inclusion (Merkle path)." },
    { id:"sq08", q:"How does Bitcoin prevent double spending?", a:"(1) Inputs must reference a specific unspent UTxO — already spent outputs are invalid. (2) Conflicting transactions are both discarded. (3) The longest chain wins in case of fork. (4) To reverse a confirmed tx, attacker must outpace the entire honest network (51% attack)." },
    { id:"sq09", q:"What is a coinbase transaction?", a:"The first transaction in every block. It has no real input UTxO (null referenced txID). It pays the miner the block reward (newly created BTC + all tx fees). All BTC ever in existence originated from coinbase transactions." },
    { id:"sq10", q:"What is gas in Ethereum?", a:"Gas is the fee unit measuring computational work. Every opcode costs gas. Gas limit = max gas sender allows. Gas price = ETH paid per gas unit. Final cost = gas used × gas price. If limit is exceeded, tx fails. Writing storage (SSTORE) is very expensive; reading is cheap." },
    { id:"sq11", q:"What is the difference between an EOA and a contract account?", a:"EOA (Externally Owned Account): controlled by ECDSA private key, no code, signs transactions. Contract Account: controlled by code, has storage, triggered by tx or message. Every transaction originates from an EOA. Account 4-tuple: (nonce, balance, contract_code, storage)." },
    { id:"sq12", q:"What is the EVM?", a:"The Ethereum Virtual Machine is a stack-based processor that executes EVM bytecode. Stack depth 1024, each item 256-bit. Top 16 accessible. Program counter starts at 0. Charges gas per opcode. Makes execution deterministic and portable. 140 opcodes." },
    { id:"sq13", q:"What is the difference between a transaction and a message in Ethereum?", a:"Transaction: signed package sent by a wallet (EOA), mined into a block, can wallet-to-wallet or wallet-to-contract. Message: sent by a contract to another account, exists only virtually (not mined), triggered when a contract calls another." },
    { id:"sq14", q:"What does PUSH1 0x60 mean in EVM bytecode?", a:"0x60 is the PUSH1 opcode, which pushes 1 byte onto the stack. The byte following 0x60 in the bytecode is the argument. So 0x6005 = PUSH1 0x05 → pushes the value 5. The byte after any PUSH opcode is data, not an opcode." },
    { id:"sq15", q:"What is the target formula from nBits?", a:"target = mantissa × 2^(8 × (exponent − 3)). nBits format: first byte = exponent, next 3 bytes = mantissa. Example: 0x1d00ffff → exp=29, mantissa=0x00ffff, target=0x00ffff × 2^208, 32 leading zero bits." },
    { id:"sq16", q:"How do you calculate difficulty?", a:"difficulty = difficulty_1_target / current_target. difficulty_1_target = 0x00ffff × 2^208 (nBits 0x1d00ffff). Bigger difficulty = smaller target = harder. Re-adjusts every 2016 blocks." },
    { id:"sq17", q:"What is the formula for n from hash rate P?", a:"n = log₂(600 × P) where P is hash rate in H/s and 600 is seconds in 10 minutes. Equivalently, P × 600 = 2^n." },
    { id:"sq18", q:"What is the Merkle path and why is it useful?", a:"The Merkle path (branch) is the set of sibling hashes needed to recompute the Merkle root from a specific transaction. Only log₂(N) hashes needed. This allows SPV nodes to verify a transaction is in a block without storing all transactions (Simplified Payment Verification)." },
    { id:"sq19", q:"What is P2PKH?", a:"Pay-to-Public-Key-Hash. The standard Bitcoin transaction type. ScriptPubKey (lock): OP_DUP OP_HASH160 <address> OP_EQUALVERIFY OP_CHECKSIG. ScriptSig (unlock): <sig> <pubKey>. The output stores only the 160-bit address hash; the spender provides the public key." },
    { id:"sq20", q:"What is to:none vs to:address in an Ethereum transaction?", a:"to:none (empty) → contract creation/deployment. EVM treats data as init code; runs it; stores runtime code returned by RETURN at new contract address. to:existingAddress → contract invocation. EVM treats data as input/calldata to the contract's functions." },
  ],
  long: [
    { id:"lq01", q:"Explain the complete Bitcoin transaction chain with UTxO model. How are inputs and outputs linked? Include scriptSig and scriptPubKey.", a:"A Bitcoin transaction has inputs and outputs. Each input references a previous UTxO via outPoint (txID + outputIndex = 36 bytes). The input includes a scriptSig (unlocking script: <sig> <pubKey>). Each output creates a new UTxO with a value (satoshi) and scriptPubKey (locking script): OP_DUP OP_HASH160 <address> OP_EQUALVERIFY OP_CHECKSIG.\n\nOutputs are INDIVISIBLE — spent entirely. Leftover value returns as a change output. Any unaccounted input value = transaction fee (collected by the miner).\n\nThe stack executes: push sig → push pubKey → DUP → HASH160 → push address → EQUALVERIFY (check match) → CHECKSIG (verify signature) → TRUE.\n\ntxID = SHA256(SHA256(txRecord)) = 32 bytes. This txID links the chain: previous output → current input → new output." },
    { id:"lq02", q:"Describe the complete Proof of Work mining process, including target calculation and the role of the nonce.", a:"1. Miner collects valid transactions from the mempool, verifying each (inputs reference UTxOs, signatures valid, no double spends).\n2. Builds the Merkle tree → Merkle root.\n3. Assembles the 80-byte header: Version, prevHash, Merkle root, timestamp, nBits (difficulty), nonce=0.\n4. The target is decoded from nBits: target = mantissa × 2^(8×(exp−3)). A valid hash must be ≤ target (fewer leading zero bits allowed).\n5. Miner computes hash = SHA256(SHA256(header)). If hash ≤ target → found. Else → increment nonce and repeat.\n6. Average computations needed = 2^n (where n = leading zero bits).\n7. When found: broadcast block → other nodes verify with ONE hash → accept → add to chain → miner earns coinbase reward + fees.\n8. Difficulty retargets every 2016 blocks (oldTarget × actualTime / (2016×600))." },
    { id:"lq03", q:"Compare and contrast Bitcoin and Ethereum in detail.", a:"PURPOSE: Bitcoin = peer-to-peer electronic cash. Ethereum = programmable 'world computer'.\nCURRENCY: BTC (satoshi = 10^-8 BTC) vs Ether (wei = 10^-18 ETH).\nBLOCK TIME: 10 minutes vs 14 seconds.\nHASH: SHA-256 (double) vs Ethash.\nCONSENSUS: Both PoW in these notes.\nMODEL: UTxO (indivisible outputs) vs Account/state (balance model).\nSMART CONTRACTS: Limited (Bitcoin Script) vs Full Turing-complete (Solidity).\nPRIVACY: Bitcoin transactions public. Both permissionless.\nFOUNDER: Satoshi Nakamoto (2008) vs Vitalik Buterin (2013).\nSUPPLY: ~21M BTC cap vs no hard cap for ETH.\nSCALABILITY: 1MB blocks, ~7 TPS vs higher TPS with smart contracts." },
    { id:"lq04", q:"Explain the Ethereum smart contract deployment lifecycle from Solidity to on-chain execution.", a:"1. WRITE: Developer writes contract in Solidity (.sol file) in Remix IDE.\n2. COMPILE: Solidity compiler produces two artefacts:\n   - ABI (JSON interface for calling functions)\n   - EVM Bytecode (machine code the EVM runs)\n3. DEPLOY: Send a transaction to the network with to:empty and data=bytecode.\n   - Connect MetaMask wallet.\n   - Choose network (e.g. Sepolia testnet to avoid real ETH cost).\n   - Get test ETH from a faucet.\n   - Pay gas.\n4. EVM EXECUTION: The EVM runs the init code. The init code must end with RETURN that returns the runtime bytecode.\n5. STORAGE: Runtime bytecode is stored at a new contract address.\n6. INTERACT: Send transactions to the contract address with data encoding the function call. EVM executes the runtime code.\n\nKey: to:none=create; to:address=invoke." },
    { id:"lq05", q:"Explain the EVM stack, memory, and storage. Include gas costs and persistence.", a:"STACK: Fast, non-persistent. 1024 items max. Each item 256-bit. Top 16 directly accessible (DUPx 1-16, SWAPx 1-16). Opcodes pop/push values. 'Stack too deep' error relates to top-16 limit.\n\nMEMORY: Byte-addressable (2^256 bytes). Starts empty each execution. MSTORE at offset n writes bytes n to n+31 (32 bytes). MLOAD reads 32 bytes. Cleared at end of call. More expensive than stack operations.\n\nSTORAGE: 2^256 slots of 32 bytes. PERSISTENT across transactions/executions. Stored on-chain at the contract address. SSTORE (write) ≈ 20,000 gas — very expensive. SLOAD (read) ≈ 2,100 gas — relatively cheap. Each contract has its own private storage.\n\nCALL STACK: When contract calls contract, current context pushed to call stack. Limit 1024 deep.\n\nGAS: STOP=0, ADD=3, MUL=5, SSTORE=~20000. Final cost = gas_used × gas_price. Exceed limit → tx fails, all changes reverted." },
    { id:"lq06", q:"Derive and explain the target, difficulty, and number of computations formulas with examples.", a:"TARGET FORMULA:\ntarget = mantissa × 2^(8 × (exponent − 3))\nnBits = 0x[exp][mantissa] e.g. 0x1d00ffff: exp=29, mantissa=0x00ffff.\ntarget = 65535 × 2^208 (difficulty-1).\nLeading zeros = 8 hex zeros × 4 bits = 32 bits.\n\nDIFFICULTY:\ndifficulty = difficulty_1_target / current_target\nSimplified: (mantissa_ref / mantissa_curr) × 2^(8×(exp_ref - exp_curr))\nExample: nBits 0x1705c739 → difficulty = (65535/378681) × 2^48 ≈ 4.88×10^13.\n\nCOMPUTATIONS:\nP × 600 = 2^n  →  n = log₂(600P)\nFor P=10^6: n = log₂(6×10^8) ≈ 29.\nFor P=10^9: n ≈ 39. Difference = 10 (because log₂(10^3) ≈ 10).\n\nHASH RATE FROM DIFFICULTY:\nhashRate = difficulty × 2^32 / 600\nFor d=4.9×10^13: hashRate ≈ 3.5×10^20 H/s ≈ 350 EH/s." },
    { id:"lq07", q:"Explain bytecode disassembly and stack execution with a worked example.", a:"EVM bytecode is a sequence of 1-byte opcodes with optional arguments.\n\nKey rule: 0x60 = PUSH1, consuming the NEXT byte as data (not an opcode). 0x61 = PUSH2 (consumes next 2 bytes). Etc.\n\nOPCODE TABLE: 0x60=PUSH1, 0x01=ADD, 0x02=MUL, 0x03=SUB, 0x35=CALLDATALOAD, 0x52=MSTORE, 0x55=SSTORE.\n\nEXAMPLE: Disassemble 0x6003600501600202600055\n  60 03 → PUSH1 0x03  → stack: [3]\n  60 05 → PUSH1 0x05  → stack: [5, 3]\n  01    → ADD          → stack: [8]   (3+5)\n  60 02 → PUSH1 0x02  → stack: [2, 8]\n  02    → MUL          → stack: [16]  (8×2)\n  60 00 → PUSH1 0x00  → stack: [0, 16]\n  55    → SSTORE       → stores 16 at slot 0\n\nFinal answer: 0x10 = 16 stored at storage slot 0.\n\nEVM is Reverse Polish Notation (RPN): operands pushed first, then operator." },
    { id:"lq08", q:"Explain how the Bitcoin white paper solves the double spending problem without a trusted third party.", a:"The white paper proposes a timestamp server using Proof of Work.\n\nPROBLEM: Digital data can be copied. Without a bank, how do you prevent Alice from spending the same coins twice?\n\nSOLUTION (5 layers):\n1. UTXO TRACKING: Every node tracks which outputs are unspent. An input must reference a specific UTxO. Once consumed, that output is marked spent (STxO). Cannot be referenced again.\n2. CONFLICT REJECTION: If two transactions try to spend the same UTxO, honest nodes accept the first, reject the second.\n3. LONGEST CHAIN: If both get into different blocks (fork), the chain with the most cumulative PoW wins. Miners always extend the longest chain.\n4. PoW COST: To double-spend after confirmation, attacker must redo all PoW for that block + every block added since. This requires >50% of network hash rate (51% attack).\n5. CONFIRMATIONS: Wait for 6 blocks. Each block requires ~2^n computations. Attacker's catch-up probability drops exponentially with z confirmations (Gambler's Ruin analysis in white paper).\n\nKEY: Attacker can only reclaim his OWN spent coins — cannot steal others (lacks private keys)." },
  ],
  diagram: [
    { id:"dq01", q:"Draw and label the Bitcoin block structure (80-byte header).", a:"Draw a large box labelled 'Block j'. Top section = HEADER (80 bytes) containing 6 labelled fields:\n1. Version (4B)\n2. Previous Block Header Hash (32B) ← links to Block j-1\n3. Merkle Root (32B)\n4. Timestamp (4B)\n5. Difficulty Target nBits (4B)\n6. Nonce (4B)\n\nBottom section = TRANSACTIONS with a small Merkle tree:\n- 4 transactions Tx0..Tx3 at bottom\n- Hash0..Hash3 above them\n- Hash01, Hash23 above those\n- Merkle Root at top (same as in header)\n\nAdd note: 'SHA256(SHA256(header)) must begin with n zeros (PoW)'\nAdd arrow from prevHash pointing to previous block." },
    { id:"dq02", q:"Draw the Merkle tree for 4 transactions.", a:"Bottom row (leaves): Tx0  Tx1  Tx2  Tx3\nLeaf hashes: Hash0=SHA256(SHA256(Tx0)), Hash1, Hash2, Hash3\nLevel 2: Hash01=SHA256(SHA256(Hash0+Hash1)), Hash23=SHA256(SHA256(Hash2+Hash3))\nRoot: MerkleRoot = SHA256(SHA256(Hash01+Hash23))\n\nLabelling:\n- Arrows pointing upward from leaves to root\n- Root is at TOP\n- Note: 'Odd tx count → duplicate last hash'\n- Note: 'Only log₂(N) hashes needed to prove inclusion'\n- Root stored in BLOCK HEADER" },
    { id:"dq03", q:"Draw the Bitcoin transaction chain (Quiz 1 Q5 diagram).", a:"Draw transaction boxes chained together:\n\nBlock: 120K,A → [txID_0] → outputs: 50K,B (orange/spent), 60K,C (orange/spent)\n50K,B → [txID_1] → 40K,D (orange/spent)\n60K,C → [txID_2] → 30K,E (orange/spent), 20K,F (orange/spent)\n40K,D → [txID_3] → 20K,G (green/UTxO), 10K,D_change (green/UTxO)\n30K,E → [txID_4] → 20K,H (orange/spent)\n20K,F → [txID_5] → 10K,I (orange/spent)\n20K,H + 10K,I → [txID_6] → 20K,J (green/UTxO)\n\nOrange = spent (STxO), Green = unspent (UTxO). 10K uniform fee deducted each tx.\nAnswers: (i) txID_0 creates 2 outputs. (ii) 120K→J path: txID_0→txID_2→txID_4+txID_5→txID_6. (iii) Cannot get 20K,J without combining inputs (20K,H alone minus 10K fee = only 10K)." },
    { id:"dq04", q:"Draw the Proof of Work (PoW) mining flow diagram.", a:"Vertical flowchart:\n\n[Collect valid Tx] → [Build Merkle root] → [Assemble 80-byte header]\n       ↓\n[Pick nonce = 0]\n       ↓\n[hash = SHA256(SHA256(header))]\n       ↓\n[Diamond: hash ≤ target?]\n   NO ↙           ↘ YES\n[Change nonce]    [Broadcast block]\n   (loop)               ↓\n                  [Other nodes verify (1 hash)]\n                        ↓\n                  [Add to chain]\n                        ↓\n                  [Miner earns reward + fees]\n\nLabel the loop. Note: 'Average 2^n attempts needed'. Note: 'Only 1 hash to verify (asymmetric effort)'." },
    { id:"dq05", q:"Draw the Ethereum smart contract deployment flow.", a:"Vertical flow diagram:\n\n[Solidity (.sol) — write in Remix IDE]\n       ↓ compile\n[Solidity Compiler]\n       ↓ produces\n[ABI] + [EVM Bytecode]\n       ↓\n[Deploy: tx with to:empty, data=bytecode]\n[MetaMask → Sepolia testnet → pay gas (faucet)]\n       ↓\n[EVM runs init code → RETURN runtime code]\n       ↓\n[Runtime bytecode stored at new contract address]\n       ↓\n[Interact: send tx to contract address, data=function call]\n\nKey labels: Remix, Solidity, ABI, bytecode, MetaMask, Sepolia, faucet, gas, to:none=create, to:address=invoke." },
    { id:"dq06", q:"Draw the blockchain chain-of-blocks structure.", a:"Three blocks left to right, each with an arrow pointing LEFT (backward reference):\n\n[Block j-1]  ←hash  [Block j]  ←hash  [Block j+1]\n  Header              Header              Header\n  prevHash            prevHash            prevHash\n\nLabels on each block: Header (top), Transactions (bottom), prevHash field.\nArrow annotation: 'prevHash links to header hash of previous block'\nLabel first block as 'Genesis Block (height 0)' if asked.\nNote: 'Changing any block invalidates all subsequent hashes → immutability'" },
    { id:"dq07", q:"Draw the UTxO model diagram.", a:"Two boxes side by side:\n\nLeft box: 'Previous Transaction Output (UTxO)'\n  Contents: value (satoshi), locking scriptPubKey, address\n\nArrow pointing right labelled: 'Referenced as input (outPoint = txID + outputIndex)'\n\nRight box: 'New Transaction'\n  Input side: prevTxID + index + scriptSig (sig, pubKey)\n  Output side: value + scriptPubKey → New UTxO\n\nNote below right box: 'Outputs are indivisible. Leftover value → change output. Unaccounted value → transaction fee.'" },
    { id:"dq08", q:"Draw the P2PKH locking/unlocking script stack execution.", a:"Two boxes at top:\nscriptSig (unlock): <sig>  <pubKeyA>\nscriptPubKey (lock): OP_DUP  OP_HASH160  <addressA>  OP_EQUALVERIFY  OP_CHECKSIG\n\nStack execution column:\nStep 1: push <sig>         → Stack: [sig]\nStep 2: push <pubKeyA>     → Stack: [pubKeyA, sig]\nStep 3: OP_DUP             → Stack: [pubKeyA, pubKeyA, sig]\nStep 4: OP_HASH160         → Stack: [addr', pubKeyA, sig]\nStep 5: push <addressA>    → Stack: [addressA, addr', pubKeyA, sig]\nStep 6: OP_EQUALVERIFY     → Stack: [pubKeyA, sig]  (check addr'==addressA)\nStep 7: OP_CHECKSIG        → Stack: [TRUE]\n\nNote: EQUALVERIFY = address match check. CHECKSIG = signature verification." },
  ],
  calc: [
    { id:"cq01", q:"[TARGET] Given nBits = 0x1d00ffff, find: (a) the target, (b) leading zero bits.", a:"exponent = 0x1d = 29\nmantissa = 0x00ffff = 65535\n\ntarget = 65535 × 2^(8×(29−3)) = 65535 × 2^208\n\nIn hex: 00000000FFFF0000...0000 (256-bit)\nLeading hex zeros: 8 → × 4 bits each\n\nANSWER: target = 0x00ffff × 2^208, leading zero bits = 32" },
    { id:"cq02", q:"[TARGET] Given nBits = 0x1705c739, find: (a) the target, (b) leading zero bits.", a:"exponent = 0x17 = 23\nmantissa = 0x05c739 = 378681\n\ntarget = 0x05c739 × 2^(8×(23−3)) = 0x05c739 × 2^160\n\nLeading hex zeros: 18 → × 4 bits each\n\nANSWER: target = 0x05c739 × 2^160, leading zero bits = 72" },
    { id:"cq03", q:"[TARGET] Given mantissa = 0x1b0404, exponent = 0x1d (29), find the target.", a:"target = 0x1b0404 × 2^(8×(29−3)) = 0x1b0404 × 2^208\n\n0x1b0404 = 1,770,500 (decimal)\n\nANSWER: target = 0x1b0404 × 2^208 = 1,770,500 × 2^208\n\nNote: 0x1b in binary = 00011011, so the top byte has 3 leading zero bits." },
    { id:"cq04", q:"[DIFFICULTY] nBits_ref = 0x1d00ffff, nBits_current = 0x1705c739. Find the difficulty.", a:"difficulty_1_target = 0x00ffff × 2^(8×(29−3)) = 0x00ffff × 2^208\ncurrent_target     = 0x05c739 × 2^(8×(23−3)) = 0x05c739 × 2^160\n\ndifficulty = (0x00ffff / 0x05c739) × 2^(8×(29−23))\n           = (65535 / 378681) × 2^48\n           = 0.17305 × 2.815×10^14\n           ≈ 4.87 × 10^13\n\nANSWER: difficulty ≈ 4.87 × 10^13" },
    { id:"cq05", q:"[DIFFICULTY] If difficulty_1_target = 2^224 and current_target = 2^220, what is the difficulty?", a:"difficulty = difficulty_1_target / current_target\n           = 2^224 / 2^220\n           = 2^(224−220)\n           = 2^4\n           = 16\n\nANSWER: difficulty = 16" },
    { id:"cq06", q:"[COMPUTATIONS] A miner runs at P = 10^6 H/s. Find n (number of leading zero bits).", a:"n = log₂(600 × P)\n  = log₂(600 × 10^6)\n  = log₂(6 × 10^8)\n\nlog₂(6×10^8) = log(6×10^8) / log(2) = 8.778 / 0.301 ≈ 29.16\n\nANSWER: n ≈ 29" },
    { id:"cq07", q:"[COMPUTATIONS] A miner runs at P = 10^9 H/s. Find n.", a:"n = log₂(600 × 10^9)\n  = log₂(6 × 10^11)\n  = log(6×10^11) / log(2)\n  = 11.778 / 0.301\n  ≈ 39.1\n\nANSWER: n ≈ 39\n\nNote: Difference from P=10^6 is ≈10 bits (log₂(10^3) ≈ 9.97)" },
    { id:"cq08", q:"[COMPUTATIONS] If n = 40, what is the hash rate P?", a:"P × 600 = 2^40\nP = 2^40 / 600\n  = 1,099,511,627,776 / 600\n  ≈ 1.83 × 10^9 H/s\n\nANSWER: P ≈ 1.83 GH/s ≈ 1.83 × 10^9 hashes/sec" },
    { id:"cq09", q:"[COMPUTATIONS] 100,000 CPUs each at 10 trillion H/s. Find n.", a:"Total in 10 min = 10^5 × 10×10^12 × 600\n               = 10^5 × 10^13 × 600\n               = 6 × 10^20\n\nAverage work = 2^n / 2 = 6×10^20\n→ 2^n = 1.2×10^21\n→ n = log₂(1.2×10^21) ≈ 69.9 ≈ 70\n\nANSWER: n ≈ 68−70" },
    { id:"cq10", q:"[HASH RATE] Find hash rate from difficulty = 4.9 × 10^13.", a:"hashRate = difficulty × 2^32 / 600\n         = 4.9×10^13 × 4,294,967,296 / 600\n         = 4.9×10^13 × 4.295×10^9 / 600\n         = 2.104×10^23 / 600\n         ≈ 3.51 × 10^20 H/s\n\nANSWER: ≈ 3.5 × 10^20 H/s ≈ 350 EH/s\n(Consistent with quoted real Bitcoin hash rate of ~385 EH/s)" },
    { id:"cq11", q:"[BYTECODE] Disassemble 0x6003600501600202600055 and find the stored value.", a:"60 03 → PUSH1 0x03    stack: [3]\n60 05 → PUSH1 0x05    stack: [5, 3]\n01    → ADD            stack: [8]     (3+5=8)\n60 02 → PUSH1 0x02    stack: [2, 8]\n02    → MUL            stack: [16]    (8×2=16)\n60 00 → PUSH1 0x00    stack: [0, 16]\n55    → SSTORE         stores 16 at slot 0\n\nANSWER: 0x10 = 16 stored at storage slot 0" },
    { id:"cq12", q:"[BYTECODE] Disassemble 0x6011600055 and find the stored value.", a:"60 11 → PUSH1 0x11    stack: [0x11 = 17]\n60 00 → PUSH1 0x00    stack: [0, 17]\n55    → SSTORE         stores 17 at slot 0\n\nANSWER: 0x11 = 17 stored at storage slot 0" },
    { id:"cq13", q:"[BYTECODE] Disassemble 0x600a600302600055 and find the stored value.", a:"60 0a → PUSH1 0x0a = 10   stack: [10]\n60 03 → PUSH1 0x03 = 3    stack: [3, 10]\n02    → MUL               stack: [30]   (10×3=30)\n60 00 → PUSH1 0x00        stack: [0, 30]\n55    → SSTORE             stores 30 at slot 0\n\nANSWER: 0x1e = 30 stored at storage slot 0" },
    { id:"cq14", q:"[BYTECODE] Disassemble 0x600035600055 (the save-data runtime contract).", a:"60 00 → PUSH1 0x00          stack: [0]    (offset for CALLDATALOAD)\n35    → CALLDATALOAD         stack: [calldata[0:32]]\n60 00 → PUSH1 0x00          stack: [0, calldata]\n55    → SSTORE               stores calldata at slot 0\n\nBehavior: Stores the first 32 bytes of call data at storage slot 0.\nSending 0x67 → stores 0x6700000...0 (padded with 31 trailing zero bytes).\nSending 33 bytes → only first 32 bytes stored; extra byte dropped." },
    { id:"cq15", q:"[MIXED] M2: Miner runs at P = 2×10^9 H/s. Find n for 10-minute block.", a:"n = log₂(600 × P)\n  = log₂(600 × 2×10^9)\n  = log₂(1.2 × 10^12)\n\nlog(1.2×10^12) / log(2) = 12.079 / 0.301 ≈ 40.1\n\nANSWER: n ≈ 40 bits\n\nAlternatively: log₂(1.2×10^12) ≈ log₂(10^12) + log₂(1.2) ≈ 39.86 + 0.26 ≈ 40.1" },
  ]
};

// ═══════════════════════
// DIAGRAMS
// ═══════════════════════
const DIAGRAMS = [
  { id:"d01", name:"Blockchain Chain of Blocks", priority:true,
    ascii:`+-----------+      +-----------+      +-----------+
| Block j-1 | <--- | Block j   | <--- | Block j+1 |
|  Header   |      |  Header   |      |  Header   |
| prevHash  |      | prevHash  |      | prevHash  |
+-----------+      +-----------+      +-----------+
   ^                   ^                   ^
hash(j-2)          hash(j-1)           hash(j)`,
    notes:"Three boxes left-to-right. Each block's header contains the hash of the previous block. Arrows point BACKWARD (each block references the one before it). Label first block as 'Genesis Block'. Key: changing one block invalidates all subsequent hashes → immutability." },

  { id:"d02", name:"Block Structure (80-byte header)", priority:true,
    ascii:`                 Block j
+-------------------------------------------+
| HEADER (80 bytes)                         |
|   Version (4B) | hash(header_{j-1}) (32B) |
|   Merkle_Root (32B) | Timestamp (4B)      |
|   Target_nBits (4B) | Nonce (4B)          |
+-------------------------------------------+
| TRANSACTIONS                              |
|          Merkle Root                      |
|         /            \                    |
|     Hash01           Hash23              |
|    /     \          /     \              |
| Hash0  Hash1     Hash2  Hash3            |
|   |      |         |      |              |
|  Tx0    Tx1       Tx2    Tx3             |
+-------------------------------------------+
hash(header_j) must begin with n zeros (PoW)`,
    notes:"Top = HEADER (6 fields). Bottom = TRANSACTIONS with Merkle tree. Merkle ROOT is stored in the header, NOT the body. Must include: previous block hash, nonce, and note about PoW requirement." },

  { id:"d03", name:"Merkle Tree", priority:true,
    ascii:`          Merkle Root  (stored in header)
         /              \
     Hash01             Hash23
     /    \             /    \
 Hash0   Hash1      Hash2   Hash3
   |       |          |       |
  Tx0     Tx1        Tx2     Tx3

Hash0 = SHA256(SHA256(Tx0))
Hash01 = SHA256(SHA256(Hash0 + Hash1))`,
    notes:"LEAVES at BOTTOM (Tx0..Tx3), ROOT at TOP stored in header. Pair-and-hash upward. Odd tx count → duplicate last hash. Merkle PATH = log₂(N) hashes to prove inclusion. THIS IS GUARANTEED IN PART 2." },

  { id:"d04", name:"Bitcoin Transaction Chain", priority:true,
    ascii:`LEGEND: [orange]=Spent(STxO)  [green]=Unspent(UTxO)
Unit = satoshi. 10K uniform tx fee.

         120K,A
            |
         txID_0  --> 50K,B [orange]
                 --> 60K,C [orange]
                      |
  txID_1 (in:50K,B) --> 40K,D [orange]
  txID_2 (in:60K,C) --> 30K,E [orange]
                     --> 20K,F [orange]
                          |
  txID_3 (in:40K,D) --> 20K,G [GREEN UTxO]
                     --> 10K,D [GREEN UTxO]
  txID_4 (in:30K,E) --> 20K,H [orange]
  txID_5 (in:20K,F) --> 10K,I [orange]
                          |
  txID_6 (in:20K,H + 10K,I) --> 20K,J [GREEN UTxO]`,
    notes:"Quiz 1 Q5 diagram. Boxes for each txID. Inputs on left (orange=spent), outputs on right. Arrows from output to input that consumes it. Final UTxOs coloured green. txID_6 combines TWO inputs to get 20K,J (20+10−10fee=20K)." },

  { id:"d05", name:"UTxO Model", priority:false,
    ascii:` Previous Tx Output (UTxO)      New Transaction
 +--------------------+   referenced  +------------------------+
 | Output:            |  ----------> | Input:                  |
 | value (satoshi),   |   outPoint   | prevTxID + outputIndex  |
 | locking script     |   36 bytes   | + scriptSig (sig+pubKey)|
 +--------------------+              +------------------------+
                                     | Output: value + script  | → new UTxO
                                     +------------------------+
                                     Outputs indivisible → change output
                                     Unaccounted value → tx fee`,
    notes:"Previous UTxO flows into new transaction as input. New outputs created. Key: outputs are INDIVISIBLE (spent entirely). Extra value → change output. Missing value → transaction fee." },

  { id:"d06", name:"P2PKH Script Stack Execution", priority:false,
    ascii:`scriptSig (unlock):  <sig> <pubKeyA>
scriptPubKey (lock): OP_DUP OP_HASH160 <addressA> OP_EQUALVERIFY OP_CHECKSIG

Stack execution (left to right):
push <sig>          → stack: [sig]
push <pubKeyA>      → stack: [pubKeyA, sig]
OP_DUP              → stack: [pubKeyA, pubKeyA, sig]
OP_HASH160          → stack: [addr', pubKeyA, sig]
push <addressA>     → stack: [addressA, addr', pubKeyA, sig]
OP_EQUALVERIFY      → stack: [pubKeyA, sig]  ✓ addr'==addressA?
OP_CHECKSIG         → stack: [TRUE]          ✓ sig valid?`,
    notes:"Show two script boxes (unlock + lock), then stack execution column. Emphasise: EQUALVERIFY checks address match; CHECKSIG checks signature. Output stores only 160-bit hash (address); spender provides the actual pubKey in scriptSig." },

  { id:"d07", name:"Proof of Work Mining Flow", priority:true,
    ascii:`[Collect valid Tx from mempool]
            ↓
[Build Merkle root from Tx hashes]
            ↓
[Assemble 80-byte header: V,prevHash,MerkleRoot,Timestamp,nBits,Nonce=0]
            ↓
[Pick/increment nonce]
            ↓
[hash = SHA256(SHA256(header))]
            ↓
       hash ≤ target?
      NO ↙          ↘ YES
[change nonce]    [broadcast block to network]
  (loop ≈2^n      [other nodes verify — 1 hash]
  attempts)       [add to longest chain]
                  [miner earns: new BTC + tx fees]`,
    notes:"Vertical flowchart with decision diamond. 'NO' branch loops back to nonce change. 'YES' leads to broadcast/reward. Key annotation: 'Average 2^n attempts' and 'Only 1 hash to VERIFY (asymmetric effort)'. This is Satoshi's main contribution." },

  { id:"d08", name:"Smart Contract Deployment Flow", priority:true,
    ascii:`Solidity (.sol)
    | write contract in Remix IDE (remix.ethereum.org)
    ↓
Solidity Compiler
    | compile
    ↓
ABI (JSON interface) + EVM Bytecode
    |
    ↓
Deploy Transaction: to=empty, data=bytecode
    | connect MetaMask
    | choose Sepolia testnet
    | get test ETH from faucet
    | pay gas
    ↓
EVM executes init code → RETURN runtime bytecode
    ↓
Runtime bytecode stored at NEW CONTRACT ADDRESS
    ↓
Interact: tx to contract_address, data=function call`,
    notes:"Vertical flow: Solidity → Compiler → ABI+Bytecode → Deploy tx (to:none) → EVM stores runtime code → Interact. Key labels: Remix, MetaMask, Sepolia, faucet, gas, to:none=create, to:address=invoke. THIS IS GUARANTEED IN PART 2." },
];

// ═══════════════════════
// REVISION CONTENT
// ═══════════════════════
const REVISION = {
  definitions: [
    { term:"Blockchain", def:"distributed immutable ledger of hash-linked blocks, maintained by nodes with no central authority" },
    { term:"Hashing", def:"one-way fixed-length fingerprint function (SHA-256 = 256-bit output)" },
    { term:"Digital signature", def:"sign with private key, verify with public key; gives Authentication, Non-repudiation, Integrity" },
    { term:"PoW", def:"prove computational effort; ~2^n work for n zero bits required in hash" },
    { term:"UTxO", def:"unspent transaction output; input must reference one; outputs are indivisible" },
    { term:"Merkle root", def:"top hash of binary hash tree of all transactions; stored in block HEADER" },
    { term:"Coinbase", def:"first transaction in each block; pays miner; no real input UTxO" },
    { term:"EVM", def:"stack-based runtime executing bytecode; charges gas per opcode" },
    { term:"Gas", def:"fee per opcode; final cost = gas_used × gas_price; SSTORE very expensive" },
    { term:"EOA vs Contract", def:"key-controlled (wallet) vs code-controlled (smart contract); every tx from EOA" },
    { term:"Transaction vs Message", def:"wallet-sent+mined vs contract-sent+virtual" },
    { term:"nBits", def:"4-byte compact encoding of target: 0x[exp][mantissa]; target = mantissa × 2^(8×(exp−3))" },
  ],
  formulas:`target     = mantissa × 2^(8 × (exponent − 3))
difficulty = difficulty_1_target / current_target
P × 600    = 2^n  →  n = log₂(600P)
hashRate   = difficulty × 2^32 / 600
txID       = SHA256(SHA256(txRecord))
address    = RIPEMD160(SHA256(publicKey))
1 BTC = 10^8 satoshi  |  1 Ether = 10^18 wei
outPoint   = txID(32B) + outputIndex(4B) = 36B
Final gas cost = gas_used × gas_price`,
  differences: [
    "Hashing vs encryption: one-way (no key) vs two-way (with key)",
    "UTxO vs STxO: unspent (tracked) vs spent (not tracked)",
    "scriptPubKey vs scriptSig: locking (output) vs unlocking (input)",
    "PoW vs PoS: computing power vs staked coins determines block creator",
    "EOA vs contract account: private key vs code controlled",
    "Transaction vs message (Ethereum): wallet-sent+mined vs contract-sent+virtual",
    "Soft fork vs hard fork: backward compatible (no new coin) vs not (may create new coin)",
    "Bitcoin vs Ethereum: cash/UTxO/SHA-256/10min vs platform/accounts/Ethash/14s",
    "Stack vs Memory vs Storage: non-persistent fast / non-persistent byte-addressable / persistent expensive",
    "to:none vs to:address: deploy contract vs invoke contract",
  ],
  traps: [
    "Bitcoin does NOT encrypt transaction data — all records are public",
    "Bigger target = EASIER, not harder (more leading zeros = harder)",
    "Sign with PRIVATE key, verify with PUBLIC key",
    "Merkle root is in the HEADER, not the body/transaction list",
    "Reading storage is cheap; WRITING storage (SSTORE) is very expensive",
    "to:none = CREATE contract; to:address = INVOKE existing contract",
    "difficulty = reference/current (NOT current/reference)",
    "Bitcoin double-hashes: SHA256(SHA256(data)), not SHA256 once",
    "Hash must be LESS THAN OR EQUAL TO target (not just equal)",
    "The byte after a PUSH opcode is DATA, not another opcode",
  ],
  highYield: ["SHA-256","Merkle root in header","PoW (2^n)","UTxO/double spending","Longest chain","ANI trio (Auth,Non-rep,Integrity)","target formula","difficulty formula","n=log₂(600P)","Bytecode disassembly","EVM gas","SSTORE expensive","to:none=create","Block structure V-P-M-T-D-N","scriptSig/scriptPubKey","coinbase tx","RIPEMD160(SHA256(pubKey))","Sepolia testnet","satoshi/wei"],
  diagrams: ["Block Structure (6 fields, 80 bytes) ★★★","Merkle Tree (leaves at bottom, root in header) ★★★","Bitcoin Transaction Chain (UTxO colours) ★★★","Proof of Work Mining Flow ★★","Smart Contract Deployment ★★","Blockchain Chain of Blocks ★"],
};

// ═══════════════════════════════════════════
// 2. STATE
// ═══════════════════════════════════════════

const STATE_KEY = "blockStudyState_v1";

let state = {
  topics: {}, // id → { status, difficulty, revision }
  diagrams: {}, // id → { status } (memorized/needs-practice/untouched)
  calcs: {}, // id → { done }
  questions: {}, // id → { practiced, mastered, revision }
  mcq: {
    history: {}, // id → { answered, correct }
    currentIdx: 0,
    order: [],
    filter: "all",
  },
  theme: "dark",
};

function loadState() {
  try {
    const saved = localStorage.getItem(STATE_KEY);
    if (saved) {
      const parsed = JSON.parse(saved);
      state = { ...state, ...parsed };
    }
  } catch (e) { /* ignore */ }
}

function saveState() {
  try {
    localStorage.setItem(STATE_KEY, JSON.stringify(state));
  } catch (e) { /* ignore */ }
}

// ═══════════════════════════════════════════
// 3. UTILITIES
// ═══════════════════════════════════════════

function $(id) { return document.getElementById(id); }

function showToast(msg, duration = 2200) {
  const t = $("toast");
  t.textContent = msg;
  t.classList.remove("hidden");
  clearTimeout(t._timer);
  t._timer = setTimeout(() => t.classList.add("hidden"), duration);
}

function getTopicState(id) {
  return state.topics[id] || { status: "not-started", difficulty: "medium", revision: false };
}

function statusIcon(status) {
  if (status === "completed") return `<span class="icon" style="color:var(--teal)">${ICON.checkSquare}</span>`;
  if (status === "in-progress") return `<span class="icon" style="color:var(--amber)">${ICON.halfCircle}</span>`;
  return `<span class="icon">${ICON.square}</span>`;
}

function diffBadge(diff) {
  const map = { easy: "badge-easy", medium: "badge-medium", hard: "badge-hard" };
  const label = { easy: "Easy", medium: "Medium", hard: "Hard" };
  return `<span class="badge ${map[diff] || 'badge-medium'}">${label[diff] || diff}</span>`;
}

function highlightText(text, query) {
  if (!query) return text;
  const re = new RegExp(`(${query.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')})`, "gi");
  return text.replace(re, "<mark>$1</mark>");
}

// ═══════════════════════════════════════════
// 4. VIEWS / NAVIGATION
// ═══════════════════════════════════════════

const VIEW_TITLES = {
  dashboard: "Dashboard",
  topics: "Study Topics",
  mcq: "MCQ Practice",
  questions: "Question Bank",
  diagrams: "Diagram Practice",
  calculations: "Calculation Practice",
  revision: "Last-Minute Revision",
  search: "Search",
};

function switchView(viewId) {
  document.querySelectorAll(".view").forEach(v => v.classList.remove("active"));
  document.querySelectorAll(".nav-item").forEach(n => n.classList.remove("active"));
  const viewEl = $(`view-${viewId}`);
  if (viewEl) viewEl.classList.add("active");
  const navEl = document.querySelector(`.nav-item[data-view="${viewId}"]`);
  if (navEl) navEl.classList.add("active");
  $("topbarTitle").textContent = VIEW_TITLES[viewId] || viewId;

  // Refresh view if needed
  if (viewId === "dashboard") updateDashboard();
  if (viewId === "topics") renderTopics();
  if (viewId === "mcq") renderMCQ();
  if (viewId === "questions") renderQuestions();
  if (viewId === "diagrams") renderDiagrams();
  if (viewId === "calculations") renderCalcs();
  if (viewId === "revision") renderRevision();
}

// ═══════════════════════════════════════════
// 5. DASHBOARD
// ═══════════════════════════════════════════

function updateDashboard() {
  const total = TOPICS.length;
  const done = TOPICS.filter(t => getTopicState(t.id).status === "completed").length;
  const rev = TOPICS.filter(t => getTopicState(t.id).revision).length;
  const pct = total ? Math.round(done / total * 100) : 0;

  $("topicsDone").textContent = done;
  $("topicsDoneOf").textContent = `of ${total} total`;
  $("revisionCount").textContent = rev;

  const dg = DIAGRAMS.length;
  const dgDone = DIAGRAMS.filter(d => (state.diagrams[d.id]||{}).status === "memorized").length;
  const dgPct = dg ? Math.round(dgDone / dg * 100) : 0;

  const cl = QUESTIONS.calc.length;
  const clDone = QUESTIONS.calc.filter(c => (state.calcs[c.id]||{}).done).length;
  const clPct = cl ? Math.round(clDone / cl * 100) : 0;

  const qAll = [...QUESTIONS.short, ...QUESTIONS.long, ...QUESTIONS.diagram].length;
  const qDone = qAll ? [...QUESTIONS.short, ...QUESTIONS.long, ...QUESTIONS.diagram].filter(q => (state.questions[q.id]||{}).practiced).length : 0;
  const qPct = qAll ? Math.round(qDone / qAll * 100) : 0;

  // Progress bars
  setBar("barTopics", "pctTopics", pct);
  setBar("barDiagrams", "pctDiagrams", dgPct);
  setBar("barCalcs", "pctCalcs", clPct);
  setBar("barQuestions", "pctQuestions", qPct);

  // MCQ accuracy
  const hist = state.mcq.history || {};
  const attempted = Object.keys(hist).length;
  const correct = Object.values(hist).filter(h => h.correct).length;
  $("mcqAttempted").textContent = attempted;
  $("mcqCorrect").textContent = correct;
  const acc = attempted ? Math.round(correct / attempted * 100) : 0;
  $("mcqAccuracy").textContent = attempted ? acc + "%" : "—";
  $("mcqStat").textContent = `${attempted} attempted`;

  // Readiness score
  const readiness = Math.round(
    pct * 0.35 +
    (attempted ? acc : 0) * 0.25 +
    dgPct * 0.20 +
    clPct * 0.20
  );
  $("readinessScore").textContent = readiness;
  const circumference = 2 * Math.PI * 36; // r=36 → ~226.2
  $("readinessFill").style.strokeDashoffset = circumference - (readiness / 100) * circumference;

  // Difficulty breakdown
  const remaining = TOPICS.filter(t => getTopicState(t.id).status !== "completed");
  const easyR = remaining.filter(t => getTopicState(t.id).difficulty === "easy").length;
  const medR  = remaining.filter(t => getTopicState(t.id).difficulty === "medium").length;
  const hardR = remaining.filter(t => getTopicState(t.id).difficulty === "hard").length;
  $("dEasy").textContent = easyR;
  $("dMedium").textContent = medR;
  $("dHard").textContent = hardR;

  // Study Next
  const incomplete = TOPICS.filter(t => getTopicState(t.id).status !== "completed");
  const recommended = [
    ...incomplete.filter(t => t.priority === "high"),
    ...incomplete.filter(t => getTopicState(t.id).difficulty === "hard" && t.priority !== "high"),
    ...incomplete.filter(t => t.priority === "medium" && getTopicState(t.id).difficulty !== "hard"),
  ].slice(0, 5);

  const sn = $("studyNext");
  if (recommended.length === 0) {
    sn.innerHTML = '<div style="color:var(--teal);font-size:.85rem">All topics completed — great work.</div>';
  } else {
    sn.innerHTML = recommended.map(t => `
      <div class="study-next-item" onclick="openTopic('${t.id}')">
        ${statusIcon(getTopicState(t.id).status)} ${t.name}
        ${t.priority === "high" ? '<span class="badge badge-high">HIGH</span>' : ''}
        ${diffBadge(getTopicState(t.id).difficulty)}
      </div>
    `).join("");
  }
}

function setBar(barId, pctId, pct) {
  $(barId).style.width = pct + "%";
  $(pctId).textContent = pct + "%";
}

// ═══════════════════════════════════════════
// 6. TOPICS
// ═══════════════════════════════════════════

function renderTopics(filter = {}) {
  const search = ($("topicSearch") ? $("topicSearch").value.toLowerCase() : "");
  const statusF = ($("topicFilter") ? $("topicFilter").value : "all");
  const diffF = ($("diffFilter") ? $("diffFilter").value : "all");

  let list = TOPICS.filter(t => {
    const ts = getTopicState(t.id);
    const nameMatch = t.name.toLowerCase().includes(search) || (t.week||"").toLowerCase().includes(search);
    const statusMatch = statusF === "all" || ts.status === statusF || (statusF === "revision" && ts.revision);
    const diffMatch = diffF === "all" || ts.difficulty === diffF;
    return nameMatch && statusMatch && diffMatch;
  });

  const html = list.map(t => {
    const ts = getTopicState(t.id);
    return `
    <div class="topic-item ${ts.status}" onclick="openTopic('${t.id}')">
      <span class="topic-status-icon">${statusIcon(ts.status)}</span>
      <div class="topic-info">
        <div class="topic-name">${t.name}</div>
        <div class="topic-meta">${t.week || ""}${t.priority === "high" ? " • HIGH PRIORITY" : ""}</div>
      </div>
      <div class="topic-badges">
        ${ts.revision ? `<span class="badge badge-revision">${ICON.bookmark} Rev</span>` : ""}
        ${diffBadge(ts.difficulty)}
        ${t.priority === "high" ? '<span class="badge badge-high">★</span>' : ""}
      </div>
    </div>`;
  }).join("");

  $("topicsList").innerHTML = html || '<p class="text-muted">No topics match the filter.</p>';
}

// ═══════════════════════════════════════════
// 7. TOPIC MODAL
// ═══════════════════════════════════════════

let currentModalTopicId = null;

function openTopic(id) {
  const topic = TOPICS.find(t => t.id === id);
  if (!topic) return;
  currentModalTopicId = id;
  const ts = getTopicState(id);

  $("modalTitle").textContent = topic.name;
  $("modalBody").innerHTML = topic.notes || "<p>No notes available.</p>";

  // Update status buttons
  document.querySelectorAll(".status-btn").forEach(btn => {
    btn.classList.toggle("active", btn.dataset.status === ts.status);
  });

  // Update revision button
  $("revisionToggleText").textContent = ts.revision ? "Remove Revision" : "Add to Revision";
  $("modalRevisionToggle").classList.toggle("btn-primary", ts.revision);

  // Update diff buttons
  document.querySelectorAll(".diff-btn").forEach(btn => {
    btn.classList.toggle("selected", btn.dataset.diff === ts.difficulty);
  });

  $("topicModal").classList.remove("hidden");
}

function closeModal() {
  $("topicModal").classList.add("hidden");
  currentModalTopicId = null;
  renderTopics();
  updateDashboard();
}

// ═══════════════════════════════════════════
// 8. MCQ ENGINE
// ═══════════════════════════════════════════

let mcqList = [];
let mcqAnswered = {}; // index → { chosen, correct }

function initMCQ() {
  const filter = $("mcqDiffFilter") ? $("mcqDiffFilter").value : "all";
  mcqList = filter === "all" ? [...MCQS] : MCQS.filter(m => m.diff === filter);
  if (!state.mcq.order || state.mcq.order.length === 0) {
    state.mcq.order = mcqList.map((_, i) => i);
    state.mcq.currentIdx = 0;
  }
  mcqAnswered = {};
}

function renderMCQ() {
  // Update stats bar
  const hist = state.mcq.history || {};
  const attempted = Object.keys(hist).length;
  const correct = Object.values(hist).filter(h => h.correct).length;
  $("mcqAttempted").textContent = attempted;
  $("mcqCorrect").textContent = correct;
  $("mcqAcc").textContent = attempted ? Math.round(correct / attempted * 100) + "%" : "—";

  initMCQ();
  renderMCQCard();
  renderMCQStrip();
}

function renderMCQCard() {
  const filter = ($("mcqDiffFilter") ? $("mcqDiffFilter").value : "all");
  const list = filter === "all" ? MCQS : MCQS.filter(m => m.diff === filter);
  if (list.length === 0) {
    $("mcqCard").innerHTML = "<p>No MCQs for this filter.</p>";
    return;
  }

  const idx = Math.max(0, Math.min(state.mcq.currentIdx, list.length - 1));
  state.mcq.currentIdx = idx;
  const mcq = list[idx];
  const hist = state.mcq.history[mcq.id];

  $("mcqCounter").textContent = `Q ${idx + 1} / ${list.length}  •  ${mcq.diff.toUpperCase()}`;
  $("mcqQuestion").textContent = mcq.q;

  const optsHtml = mcq.opts.map((opt, i) => {
    let cls = "mcq-option";
    if (hist) {
      if (i === mcq.ans) cls += " correct";
      else if (i === hist.chosen && !hist.correct) cls += " wrong";
    }
    return `<button class="${cls}" onclick="answerMCQ('${mcq.id}', ${i})">${String.fromCharCode(65+i)}. ${opt}</button>`;
  }).join("");
  $("mcqOptions").innerHTML = optsHtml;

  const exp = $("mcqExplanation");
  if (hist) {
    exp.classList.remove("hidden");
    exp.innerHTML = `<strong style="color:${hist.correct ? 'var(--teal)' : 'var(--rose)'}">${hist.correct ? "Correct" : "Incorrect"}</strong> — ${mcq.exp}`;
  } else {
    exp.classList.add("hidden");
  }

  // Update nav strip
  renderMCQStrip(list);
}

function renderMCQStrip(list) {
  if (!list) {
    const filter = ($("mcqDiffFilter") ? $("mcqDiffFilter").value : "all");
    list = filter === "all" ? MCQS : MCQS.filter(m => m.diff === filter);
  }
  const strip = $("mcqNavStrip");
  strip.innerHTML = list.map((m, i) => {
    const hist = state.mcq.history[m.id];
    let cls = "mcq-dot";
    if (i === state.mcq.currentIdx) cls += " current";
    else if (hist) cls += hist.correct ? " answered-correct" : " answered-wrong";
    return `<div class="${cls}" onclick="goMCQ(${i})" title="${m.q.substring(0,40)}">${i+1}</div>`;
  }).join("");
}

function answerMCQ(id, chosen) {
  const mcq = MCQS.find(m => m.id === id);
  if (!mcq || state.mcq.history[id]) return; // Already answered
  const correct = chosen === mcq.ans;
  state.mcq.history[id] = { chosen, correct };
  saveState();
  renderMCQCard();

  // Update stats
  const hist = state.mcq.history;
  const attempted = Object.keys(hist).length;
  const correctCount = Object.values(hist).filter(h => h.correct).length;
  $("mcqAttempted").textContent = attempted;
  $("mcqCorrect").textContent = correctCount;
  $("mcqAcc").textContent = Math.round(correctCount / attempted * 100) + "%";
}

function revealMCQ() {
  const filter = ($("mcqDiffFilter") ? $("mcqDiffFilter").value : "all");
  const list = filter === "all" ? MCQS : MCQS.filter(m => m.diff === filter);
  const mcq = list[state.mcq.currentIdx];
  if (!mcq) return;
  if (!state.mcq.history[mcq.id]) {
    // Mark as answered with "reveal" (no score)
    state.mcq.history[mcq.id] = { chosen: -1, correct: false, revealed: true };
    saveState();
    renderMCQCard();
  }
}

function goMCQ(idx) {
  state.mcq.currentIdx = idx;
  renderMCQCard();
  renderMCQStrip();
}

// ═══════════════════════════════════════════
// 9. QUESTION BANK
// ═══════════════════════════════════════════

let currentQType = "short";

function renderQuestions(type) {
  if (type) currentQType = type;
  const list = QUESTIONS[currentQType] || [];
  const html = list.map((q, i) => {
    const qs = state.questions[q.id] || {};
    return `
    <div class="q-item">
      <div class="q-header" onclick="toggleAnswer('${q.id}')">
        <div class="q-num">Q${i+1}</div>
        <div class="q-text">${q.q}</div>
        <div class="q-actions">
          <button class="q-toggle-btn ${qs.practiced ? 'active' : ''}" onclick="toggleQState(event,'${q.id}','practiced')">Practised</button>
          <button class="q-toggle-btn ${qs.mastered ? 'mastered' : ''}" onclick="toggleQState(event,'${q.id}','mastered')">Mastered</button>
          <button class="q-toggle-btn ${qs.revision ? 'revision-active' : ''}" onclick="toggleQState(event,'${q.id}','revision')">${ICON.bookmark}</button>
        </div>
      </div>
      <div class="q-answer" id="qa-${q.id}">
        <pre>${q.a}</pre>
      </div>
    </div>`;
  }).join("");
  $("questionBankList").innerHTML = html || "<p>No questions found.</p>";
}

function toggleAnswer(id) {
  const el = $(`qa-${id}`);
  if (el) el.classList.toggle("visible");
}

function toggleQState(e, id, field) {
  e.stopPropagation();
  if (!state.questions[id]) state.questions[id] = {};
  state.questions[id][field] = !state.questions[id][field];
  saveState();
  renderQuestions();
  updateDashboard();
}

// ═══════════════════════════════════════════
// 10. DIAGRAMS
// ═══════════════════════════════════════════

function renderDiagrams() {
  const html = DIAGRAMS.map(d => {
    const ds = state.diagrams[d.id] || {};
    const statusIco = ds.status === "memorized"
      ? `<span style="color:var(--teal)">${ICON.checkSquare}</span>`
      : ds.status === "needs-practice"
      ? `<span style="color:var(--amber)">${ICON.alertTriangle}</span>`
      : `<span style="color:var(--text3)">${ICON.square}</span>`;
    return `
    <div class="diagram-card">
      <div class="diagram-header" onclick="toggleDiagram('${d.id}')">
        <div class="diagram-status-icon">${statusIco}</div>
        <div class="diagram-title">${d.name}</div>
        ${d.priority ? '<span class="diagram-priority">EXAM PRIORITY</span>' : ''}
        <span style="color:var(--text3);font-size:.75rem">${ICON.chevronRight}</span>
      </div>
      <div class="diagram-body" id="db-${d.id}">
        <div class="diagram-ascii">${d.ascii}</div>
        <div class="diagram-notes">${d.notes}</div>
        <div class="diagram-actions">
          <button class="d-btn ${ds.status === 'memorized' ? 'memorized' : ''}" onclick="setDiagramStatus('${d.id}','memorized')">Memorized</button>
          <button class="d-btn ${ds.status === 'needs-practice' ? 'needs-practice' : ''}" onclick="setDiagramStatus('${d.id}','needs-practice')">Needs Practice</button>
          <button class="d-btn" onclick="setDiagramStatus('${d.id}','untouched')">Reset</button>
        </div>
      </div>
    </div>`;
  }).join("");
  $("diagramsList").innerHTML = html;
}

function toggleDiagram(id) {
  const el = $(`db-${id}`);
  if (el) el.classList.toggle("open");
}

function setDiagramStatus(id, status) {
  if (!state.diagrams[id]) state.diagrams[id] = {};
  state.diagrams[id].status = status;
  saveState();
  renderDiagrams();
  updateDashboard();
  showToast(status === "memorized" ? "Marked as memorized" : status === "needs-practice" ? "Flagged for practice" : "Status reset");
}

// ═══════════════════════════════════════════
// 11. CALCULATIONS
// ═══════════════════════════════════════════

function renderCalcs() {
  const html = QUESTIONS.calc.map((c, i) => {
    const cs = state.calcs[c.id] || {};
    // Extract type from bracket at start of question
    const typeMatch = c.q.match(/^\[([^\]]+)\]/);
    const type = typeMatch ? typeMatch[1].toLowerCase().replace(/ /g, '-') : "mixed";
    const typeCls = {target:"ct-target",difficulty:"ct-difficulty",computations:"ct-computations",bytecode:"ct-bytecode","hash-rate":"ct-computations",mixed:"ct-mixed"}[type] || "ct-mixed";
    const typeLabel = typeMatch ? typeMatch[1] : "MIXED";

    return `
    <div class="calc-item">
      <div class="calc-header" onclick="toggleCalc('${c.id}')">
        <span class="calc-type ${typeCls}">${typeLabel}</span>
        <div class="calc-q">${c.q.replace(/^\[[^\]]+\]\s*/,'')}</div>
        <span class="calc-status-badge ${cs.done ? 'done' : ''}">${cs.done ? ICON.checkSquare : ICON.square}</span>
      </div>
      <div class="calc-solution" id="cs-${c.id}">
        <pre>${c.a}</pre>
        <div class="calc-actions">
          <button class="calc-complete-btn ${cs.done ? 'done' : ''}" onclick="toggleCalcDone(event,'${c.id}')">
            ${cs.done ? "Completed" : "Mark Complete"}
          </button>
        </div>
      </div>
    </div>`;
  }).join("");
  $("calcList").innerHTML = html;
}

function toggleCalc(id) {
  const el = $(`cs-${id}`);
  if (el) el.classList.toggle("open");
}

function toggleCalcDone(e, id) {
  e.stopPropagation();
  if (!state.calcs[id]) state.calcs[id] = {};
  state.calcs[id].done = !state.calcs[id].done;
  saveState();
  renderCalcs();
  updateDashboard();
}

// ═══════════════════════════════════════════
// 12. REVISION VIEW
// ═══════════════════════════════════════════

function renderRevision() {
  // Definitions
  $("revDefinitions").innerHTML = REVISION.definitions.map(d =>
    `<li><strong>${d.term}:</strong> ${d.def}</li>`
  ).join("");

  // Formulas
  $("revFormulas").textContent = REVISION.formulas;

  // Differences
  $("revDifferences").innerHTML = REVISION.differences.map(d => `<li>${d}</li>`).join("");

  // Traps
  $("revTraps").innerHTML = REVISION.traps.map(t => `<li>${t}</li>`).join("");

  // High yield
  $("revHighYield").innerHTML = REVISION.highYield.map(t => `<span class="tag">${t}</span>`).join("");

  // Diagrams
  $("revDiagrams").innerHTML = REVISION.diagrams.map(d => {
    return `<div class="rev-diagram-item">${ICON.ruler} ${d}</div>`;
  }).join("");

  // Bookmarks (revision-marked topics)
  const bookmarked = TOPICS.filter(t => getTopicState(t.id).revision);
  if (bookmarked.length === 0) {
    $("revisionBookmarks").innerHTML = '<div class="bookmark-empty">No topics bookmarked for revision yet. Star topics in the Topics view.</div>';
  } else {
    $("revisionBookmarks").innerHTML = bookmarked.map(t => `
      <div class="bookmark-item" onclick="openTopic('${t.id}')">
        ${ICON.bookmarkFill} ${t.name}
        <span style="margin-left:auto;color:var(--text3);font-size:.75rem">${t.week || ""}</span>
      </div>
    `).join("");
  }
}

// ═══════════════════════════════════════════
// 13. SEARCH
// ═══════════════════════════════════════════

function doSearch(query) {
  const q = query.toLowerCase().trim();
  const results = [];
  if (!q) { $("searchResults").innerHTML = ""; return; }

  TOPICS.forEach(t => {
    if (t.name.toLowerCase().includes(q)) {
      results.push({ type: "Topic", text: t.name, action: () => openTopic(t.id) });
    }
  });

  MCQS.forEach(m => {
    if (m.q.toLowerCase().includes(q)) {
      results.push({ type: `MCQ (${m.diff})`, text: m.q, action: () => {} });
    }
  });

  [...QUESTIONS.short, ...QUESTIONS.long, ...QUESTIONS.diagram, ...QUESTIONS.calc].forEach(q2 => {
    if (q2.q.toLowerCase().includes(q)) {
      results.push({ type: "Question", text: q2.q, action: () => {} });
    }
    if (q2.a.toLowerCase().includes(q)) {
      const snippet = q2.a.substring(0, 100);
      results.push({ type: "Answer snippet", text: q2.q + " — " + snippet + "…", action: () => {} });
    }
  });

  DIAGRAMS.forEach(d => {
    if (d.name.toLowerCase().includes(q) || d.notes.toLowerCase().includes(q)) {
      results.push({ type: "Diagram", text: d.name, action: () => switchView("diagrams") });
    }
  });

  REVISION.definitions.forEach(d => {
    if (d.term.toLowerCase().includes(q) || d.def.toLowerCase().includes(q)) {
      results.push({ type: "Definition", text: `${d.term}: ${d.def}`, action: () => {} });
    }
  });

  const deduped = results.slice(0, 40);
  if (deduped.length === 0) {
    $("searchResults").innerHTML = '<p class="text-muted" style="padding:1rem 0">No results found.</p>';
    return;
  }

  $("searchResults").innerHTML = deduped.map((r, i) => `
    <div class="search-result-item" onclick="searchResultClick(${i})">
      <div class="sr-type">${r.type}</div>
      <div class="sr-text">${highlightText(r.text.substring(0, 200), q)}</div>
    </div>
  `).join("");

  window._searchResults = deduped;
}

function searchResultClick(i) {
  const r = (window._searchResults || [])[i];
  if (r && typeof r.action === "function") r.action();
}

// ═══════════════════════════════════════════
// 14. EXPORT / IMPORT / RESET
// ═══════════════════════════════════════════

function exportProgress() {
  const data = JSON.stringify(state, null, 2);
  const blob = new Blob([data], { type: "application/json" });
  const url = URL.createObjectURL(blob);
  const a = document.createElement("a");
  a.href = url;
  a.download = "blockchain_study_progress.json";
  a.click();
  URL.revokeObjectURL(url);
  showToast("Progress exported");
}

function importProgress(file) {
  if (!file) return;
  const reader = new FileReader();
  reader.onload = (e) => {
    try {
      const parsed = JSON.parse(e.target.result);
      state = { ...state, ...parsed };
      saveState();
      showToast("Progress imported");
      updateDashboard();
      renderTopics();
    } catch (err) {
      showToast("Invalid file.");
    }
  };
  reader.readAsText(file);
}

function resetProgress() {
  if (!confirm("Reset ALL progress? This cannot be undone.")) return;
  state = {
    topics: {}, diagrams: {}, calcs: {}, questions: {},
    mcq: { history: {}, currentIdx: 0, order: [], filter: "all" },
    theme: state.theme,
  };
  saveState();
  showToast("↺ Progress reset.");
  updateDashboard();
  renderTopics();
  renderMCQ();
  renderDiagrams();
  renderCalcs();
}

// ═══════════════════════════════════════════
// 15. THEME
// ═══════════════════════════════════════════

function toggleTheme() {
  state.theme = state.theme === "dark" ? "light" : "dark";
  document.documentElement.setAttribute("data-theme", state.theme);
  $("themeToggle").textContent = state.theme === "dark" ? "🌙 Toggle Theme" : "☀️ Toggle Theme";
  saveState();
}

// ═══════════════════════════════════════════
// 16. SIDEBAR TOGGLE (MOBILE)
// ═══════════════════════════════════════════

function toggleSidebar() {
  const sidebar = document.getElementById("sidebar");
  sidebar.classList.toggle("open");
}

// ═══════════════════════════════════════════
// 17. INIT
// ═══════════════════════════════════════════

function init() {
  loadState();

  // Apply theme
  document.documentElement.setAttribute("data-theme", state.theme || "dark");
  $("themeToggle").textContent = state.theme === "dark" ? "🌙 Toggle Theme" : "☀️ Toggle Theme";

  // Navigation
  document.querySelectorAll(".nav-item").forEach(btn => {
    btn.addEventListener("click", () => {
      switchView(btn.dataset.view);
      if (window.innerWidth <= 768) toggleSidebar();
    });
  });

  // Sidebar toggle
  $("hamburger").addEventListener("click", toggleSidebar);
  $("sidebarClose").addEventListener("click", toggleSidebar);

  // Theme toggle
  $("themeToggle").addEventListener("click", toggleTheme);

  // Modal close
  $("modalClose").addEventListener("click", closeModal);
  $("topicModal").addEventListener("click", (e) => {
    if (e.target === $("topicModal")) closeModal();
  });

  // Status buttons
  document.querySelectorAll(".status-btn").forEach(btn => {
    btn.addEventListener("click", () => {
      if (!currentModalTopicId) return;
      if (!state.topics[currentModalTopicId]) state.topics[currentModalTopicId] = {};
      state.topics[currentModalTopicId].status = btn.dataset.status;
      document.querySelectorAll(".status-btn").forEach(b => b.classList.remove("active"));
      btn.classList.add("active");
      saveState();
    });
  });

  // Revision toggle
  $("modalRevisionToggle").addEventListener("click", () => {
    if (!currentModalTopicId) return;
    if (!state.topics[currentModalTopicId]) state.topics[currentModalTopicId] = {};
    const ts = state.topics[currentModalTopicId];
    ts.revision = !ts.revision;
    $("revisionToggleText").textContent = ts.revision ? "Remove Revision" : "Add to Revision";
    $("modalRevisionToggle").classList.toggle("btn-primary", ts.revision);
    saveState();
  });

  // Difficulty buttons
  document.querySelectorAll(".diff-btn").forEach(btn => {
    btn.addEventListener("click", () => {
      if (!currentModalTopicId) return;
      if (!state.topics[currentModalTopicId]) state.topics[currentModalTopicId] = {};
      state.topics[currentModalTopicId].difficulty = btn.dataset.diff;
      document.querySelectorAll(".diff-btn").forEach(b => b.classList.remove("selected"));
      btn.classList.add("selected");
      saveState();
    });
  });

  // MCQ buttons
  $("prevMCQ").addEventListener("click", () => {
    if (state.mcq.currentIdx > 0) { state.mcq.currentIdx--; renderMCQCard(); }
  });
  $("nextMCQ").addEventListener("click", () => {
    const filter = $("mcqDiffFilter").value;
    const list = filter === "all" ? MCQS : MCQS.filter(m => m.diff === filter);
    if (state.mcq.currentIdx < list.length - 1) { state.mcq.currentIdx++; renderMCQCard(); }
  });
  $("revealMCQ").addEventListener("click", revealMCQ);
  $("shuffleMCQ").addEventListener("click", () => {
    state.mcq.currentIdx = Math.floor(Math.random() * (MCQS.length));
    renderMCQCard();
    showToast("🔀 Shuffled!");
  });
  $("resetMCQ").addEventListener("click", () => {
    if (!confirm("Reset MCQ score?")) return;
    state.mcq.history = {};
    saveState();
    renderMCQ();
    showToast("↺ MCQ score reset.");
  });
  $("mcqDiffFilter").addEventListener("change", () => {
    state.mcq.currentIdx = 0;
    renderMCQCard();
  });

  // Question tabs
  document.querySelectorAll(".qtab").forEach(tab => {
    tab.addEventListener("click", () => {
      document.querySelectorAll(".qtab").forEach(t => t.classList.remove("active"));
      tab.classList.add("active");
      renderQuestions(tab.dataset.qtype);
    });
  });

  // Topic filters
  $("topicSearch").addEventListener("input", renderTopics);
  $("topicFilter").addEventListener("change", renderTopics);
  $("diffFilter").addEventListener("change", renderTopics);
  $("markAllTopics").addEventListener("click", () => {
    if (!confirm("Mark ALL topics as completed?")) return;
    TOPICS.forEach(t => {
      if (!state.topics[t.id]) state.topics[t.id] = {};
      state.topics[t.id].status = "completed";
    });
    saveState();
    renderTopics();
    updateDashboard();
    showToast("All topics marked done");
  });

  // Export / Import / Reset
  $("exportBtn").addEventListener("click", exportProgress);
  $("importBtnTrigger").addEventListener("click", () => $("importFileInput").click());
  $("importFileInput").addEventListener("change", (e) => importProgress(e.target.files[0]));
  $("resetBtn").addEventListener("click", resetProgress);

  // Global search (topbar mini)
  $("globalSearch").addEventListener("input", (e) => {
    const q = e.target.value.trim();
    if (q.length >= 2) {
      switchView("search");
      $("searchInput").value = q;
      doSearch(q);
    }
  });

  // Search view
  $("searchInput").addEventListener("input", (e) => doSearch(e.target.value));

  // Keyboard: Escape closes modal
  document.addEventListener("keydown", (e) => {
    if (e.key === "Escape" && !$("topicModal").classList.contains("hidden")) closeModal();
  });

  // Initial render
  switchView("dashboard");
}

// Expose functions used in inline onclick handlers
window.openTopic = openTopic;
window.goMCQ = goMCQ;
window.answerMCQ = answerMCQ;
window.toggleAnswer = toggleAnswer;
window.toggleQState = toggleQState;
window.toggleDiagram = toggleDiagram;
window.setDiagramStatus = setDiagramStatus;
window.toggleCalc = toggleCalc;
window.toggleCalcDone = toggleCalcDone;
window.searchResultClick = searchResultClick;

// Start
document.addEventListener("DOMContentLoaded", init);
