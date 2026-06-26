/* =========================================================
   STUDY DATA — built from all 17 course Markdown files.
   Content is rewritten in simple English while keeping the
   real meaning, examples, formulas and numericals.

   Each topic: { id, title, lec, content(HTML), status,
                 difficulty, tags[], revision }
   Tags drive filters: High Priority, Must Revise, Theory,
   Numerical, Formula, Definition, Diagram, Exam Likely,
   Practice Needed.
   ========================================================= */

const STUDY = [
/* ===================== LECTURE 1 ===================== */
{
  section:"Lecture 1 — Introduction to Networks", lec:1, kind:"theory",
  items:[
    { id:"l1-why", title:"What a network is, and why it matters", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely"],
      content:`
        <div class="simple"><b>In simple words:</b> A network is just computers and devices joined together so they can send and receive data with each other.</div>
        <h4>Two key terms</h4>
        <table><tr><th>Term</th><th>Meaning</th></tr>
        <tr><td><b>Network</b></td><td>A system that connects computers using some transmission technology so they can share data.</td></tr>
        <tr><td><b>Internet</b></td><td>A set of many networks joined by routers, so any computer on any network can talk to any other.</td></tr></table>
        <p>Networks are everywhere we don't see them: the nervous system (neurons pass signals like packets), blood vessels (high-capacity links), ant colonies (pheromone trails, no central boss), roads, power grids, and money systems. The course point: <b>wherever there is life, coordination, or intelligence, there is a network.</b></p>
        <h4>IoT family</h4>
        <ul>
          <li><b>IoT</b> (Internet of Things): network + physical things that make data.</li>
          <li><b>IoE</b> (Internet of Everything): network + things + people + data + processes.</li>
          <li><b>IIoT</b> (Industrial IoT): smart devices in industry that monitor and exchange data.</li>
        </ul>
        <p>By 2030 about <b>50 billion</b> devices are expected online, versus roughly 8 billion people today.</p>` },

    { id:"l1-types", title:"Network sizes: LAN, MAN, WAN", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <div class="simple"><b>The idea:</b> we name networks by how much area they cover.</div>
        <table><tr><th>Type</th><th>Covers</th><th>Example</th></tr>
        <tr><td><b>LAN</b> — Local Area Network</td><td>A room, floor, or building</td><td>Home WiFi, office network</td></tr>
        <tr><td><b>MAN</b> — Metropolitan Area Network</td><td>A city or town (joins LANs)</td><td>All university libraries in Lahore connected</td></tr>
        <tr><td><b>WAN</b> — Wide Area Network</td><td>Cities and whole countries</td><td>The Internet</td></tr></table>
        <p>LAN and WAN are compared on speed, bandwidth, security, reliability, management, and standards.</p>` },

    { id:"l1-topology", title:"Network topology (Bus, Ring, Star, Mesh, Hybrid)", difficulty:"medium",
      tags:["Theory","Diagram","Exam Likely"],
      content:`
        <div class="simple"><b>Topology</b> = the shape/layout of how devices are connected.</div>
        <ul>
          <li><b>Bus:</b> all nodes share one main cable (the "backbone"). If the backbone breaks, the whole segment fails.</li>
          <li><b>Ring:</b> devices form a circle; each device connects to two neighbours, data flows around the ring.</li>
          <li><b>Star:</b> every node connects to one central point (hub/switch). The hub routes all traffic.</li>
          <li><b>Mesh:</b> no central point; each node links to one or more others and can relay messages onward.</li>
          <li><b>Hybrid:</b> a mix, e.g. Star-Bus or Star-Ring. A linear bus backbone often connects several stars.</li>
        </ul>` },

    { id:"l1-transmode", title:"Transmission modes: Simplex, Half-Duplex, Full-Duplex", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <div class="simple">This describes <b>which direction</b> data can flow between two devices.</div>
        <table><tr><th>Mode</th><th>Direction</th><th>Examples</th></tr>
        <tr><td><b>Simplex</b></td><td>One way only</td><td>Keyboard → computer, TV broadcast, fire alarm</td></tr>
        <tr><td><b>Half-Duplex</b></td><td>Both ways, but one at a time</td><td>Walkie-talkie, WiFi, one-lane two-way road</td></tr>
        <tr><td><b>Full-Duplex</b></td><td>Both ways at the same time</td><td>Phone call, wired Ethernet, Zoom audio</td></tr></table>
        <div class="warn"><b>Exam note:</b> WiFi is half-duplex. The access point cannot send and receive at the exact same moment — it takes turns, but so fast you don't notice.</div>` },

    { id:"l1-protocols", title:"Protocols, TCP/IP, and standards", difficulty:"medium",
      tags:["Theory","Definition","Exam Likely"],
      content:`
        <div class="simple"><b>Protocol</b> = an agreed set of rules for how messages are formatted, ordered, sent, and answered.</div>
        <p>Just like humans greet then talk, machines follow a protocol: client sends a TCP connection request, server replies, client asks for a page, server sends the file. Both sides must run the <b>same protocol</b> or nothing works.</p>
        <h4>TCP/IP</h4>
        <ul>
          <li><b>IP (Internet Protocol):</b> decides the format of packets and the address data is sent to.</li>
          <li><b>TCP (Transmission Control Protocol):</b> handles actual reliable delivery once the address is known.</li>
        </ul>
        <h4>Standards & ISO</h4>
        <p>Standards let hardware/software from different vendors work together, so customers are not locked to one company. <b>ISO</b> (International Organization for Standardization, based in Geneva) makes technical recommendations for data communication. <b>RFC</b> = Request for Comments; <b>IETF</b> = Internet Engineering Task Force.</p>` },

    { id:"l1-extras", title:"Intranet, Extranet, components, domain names", difficulty:"easy",
      tags:["Theory","Definition"],
      content:`
        <h4>Intranet vs Extranet</h4>
        <ul>
          <li><b>Intranet:</b> uses Internet technology but is open <b>only to people inside</b> the organization.</li>
          <li><b>Extranet:</b> similar tech, but opened to selected <b>outsiders</b> (customers, suppliers, enrolled students) over the Internet, with access control like passwords.</li>
        </ul>
        <h4>Components</h4>
        <ul><li><b>Server:</b> stores data/software clients can use.</li>
        <li><b>Client:</b> the user's device that accesses the network.</li>
        <li><b>Circuit:</b> the pathway messages travel (copper, fiber, wireless).</li>
        <li><b>Peer-to-peer:</b> equal computers share directly, no central server needed.</li></ul>
        <h4>Domain names</h4>
        <p>Format <code>computer.domain</code> e.g. <code>www.bnu.edu.pk</code>. Common top-levels: EDU (education), COM (business), GOV (government), ORG (nonprofit); country codes like PK, UK, DE.</p>` }
  ]
},

/* ===================== LECTURE 2 ===================== */
{
  section:"Lecture 2 — Data Transmission & Switching", lec:2, kind:"theory",
  items:[
    { id:"l2-internet", title:"The Internet: nuts-and-bolts and services view", difficulty:"easy",
      tags:["Theory","Definition"],
      content:`
        <div class="simple">The Internet can be seen two ways: <b>what it's made of</b> (hardware view) and <b>what it does</b> (services view).</div>
        <h4>Nuts and bolts</h4>
        <ul>
          <li><b>Hosts / end systems:</b> devices running apps at the edge.</li>
          <li><b>Packet switches:</b> forward chunks of data — routers and switches.</li>
          <li><b>Links:</b> fiber, copper, radio, satellite. Their speed = <b>bandwidth</b>.</li>
          <li>The Internet = a "network of networks" of interconnected ISPs.</li>
        </ul>
        <h4>Services view</h4>
        <p>It is infrastructure that gives services to apps (web, email, video, games) and a programming interface ("hooks") so apps can connect and use Internet transport.</p>` },

    { id:"l2-host-delay", title:"How a host sends packets + transmission delay", difficulty:"medium",
      tags:["Numerical","Formula","Exam Likely","Practice Needed"],
      content:`
        <p>A host takes an app message, breaks it into <b>packets</b> of length <b>L bits</b>, and pushes them onto the link at rate <b>R bits/sec</b> (also called link capacity or bandwidth).</p>
        <div class="formula">Transmission Delay = L (bits) / R (bits per second)</div>
        <div class="example">If a packet is 8000 bits and the link is 1,000,000 bps, delay = 8000 / 1,000,000 = 0.008 s = 8 ms.</div>` },

    { id:"l2-media", title:"Transmission media (guided & unguided)", difficulty:"easy",
      tags:["Theory","Definition","Diagram"],
      content:`
        <div class="simple"><b>Transmission medium</b> = the physical path a signal travels on.</div>
        <table><tr><th>Type</th><th>Meaning</th><th>Examples</th></tr>
        <tr><td><b>Guided</b></td><td>Signal follows a solid path</td><td>Twisted pair, coaxial, optical fiber</td></tr>
        <tr><td><b>Unguided</b></td><td>Signal travels freely</td><td>Radio, atmosphere, space</td></tr></table>
        <h4>Common guided media</h4>
        <ul>
          <li><b>Twisted pair:</b> Cat 5 → 100Mbps/1Gbps; Cat 6 → 10Gbps.</li>
          <li><b>Coaxial:</b> two concentric conductors, broadband, 100s Mbps per channel.</li>
          <li><b>Fiber optic:</b> light pulses, very high speed (10s–100s Gbps), low error, immune to electrical noise.</li>
          <li><b>Wireless radio:</b> no wire, broadcast, usually half-duplex; affected by reflection, obstruction, interference.</li>
        </ul>` },

    { id:"l2-switching", title:"Circuit vs Message vs Packet switching", difficulty:"medium",
      tags:["Theory","Exam Likely","Must Revise","Definition"],
      content:`
        <div class="simple">Three ways to move data through a wide-area network.</div>
        <h4>Circuit switching</h4>
        <ul><li>A <b>dedicated path</b> is set up first and kept for the whole call (used for voice, e.g. telephone).</li>
        <li>Phases: <b>Establish → Transfer → Disconnect</b>.</li>
        <li>If no data is sent, the reserved capacity is <b>wasted</b>.</li></ul>
        <h4>Message switching</h4>
        <ul><li>The <b>whole message</b> is sent and <b>stored-and-forwarded</b> at each node. No size limit, slower.</li></ul>
        <h4>Packet switching</h4>
        <ul><li>Data is split into small <b>packets</b>, each forwarded node to node. Used for data/Internet. Faster, shares the link.</li></ul>
        <table><tr><th>Feature</th><th>Message</th><th>Packet</th></tr>
        <tr><td>Unit</td><td>Whole message</td><td>Small fixed packets</td></tr>
        <tr><td>Size limit</td><td>None</td><td>Upper limit</td></tr>
        <tr><td>Speed</td><td>Slower</td><td>Faster</td></tr></table>` },

    { id:"l2-datagram-vc", title:"Datagram vs Virtual Circuit", difficulty:"medium",
      tags:["Theory","Exam Likely","Definition","Must Revise"],
      content:`
        <div class="simple">Two ways packets can be handled inside packet switching.</div>
        <table><tr><th>Feature</th><th>Datagram</th><th>Virtual Circuit</th></tr>
        <tr><td>Connection</td><td>Connectionless</td><td>Connection-oriented</td></tr>
        <tr><td>Path</td><td>No fixed path</td><td>Pre-set path</td></tr>
        <tr><td>Routing</td><td>Per packet</td><td>Per connection (circuit ID)</td></tr>
        <tr><td>Order</td><td>May arrive out of order</td><td>Arrive in order</td></tr>
        <tr><td>Example</td><td>University WiFi, Ethernet LAN</td><td>ISP MPLS links</td></tr></table>
        <p>A datagram network is a "true" packet-switched network — no fixed route. The receiver re-orders packets and handles losses. The Internet's IP is a packet-switching, datagram protocol.</p>` },

    { id:"l2-packet-anatomy", title:"Anatomy of a packet", difficulty:"easy",
      tags:["Theory","Diagram"],
      content:`
        <p>Every packet carries:</p>
        <ol>
          <li><b>Header address</b> — the final destination.</li>
          <li><b>Sequence number</b> — so the receiver can reassemble in order.</li>
          <li><b>Total packet count</b> — so the receiver knows if any are missing.</li>
          <li><b>Error recovery</b> — if a packet is missing, the receiver asks for a retransmission.</li>
        </ol>` }
  ]
},

/* ===================== LECTURE 3 ===================== */
{
  section:"Lecture 3 — IP Addressing Schemes", lec:3, kind:"both",
  items:[
    { id:"l3-why-ip", title:"Why we use IP addresses", difficulty:"easy",
      tags:["Theory","Definition"],
      content:`
        <div class="simple">To send data to a process on another host, that host needs an <b>address</b>. On the Internet that is the <b>IP address</b>.</div>
        <p>Hostnames like <code>www.google.com</code> are easy for people but tell little about location and are hard for routers to process. So hosts also get IP addresses.</p>
        <ul>
          <li>An IP address is a <b>32-bit</b> identifier (IPv4).</li>
          <li>It encodes a <b>network number (prefix)</b> + a <b>host number</b>.</li>
        </ul>
        <h4>Three address rules</h4>
        <ol><li>Devices on the <b>same LAN</b> share the same network part.</li>
        <li>Devices on <b>different LANs</b> (split by a router) use different networks.</li>
        <li>Every IP must be <b>unique</b> in the same internetwork.</li></ol>` },

    { id:"l3-dotted", title:"Dotted-decimal notation", difficulty:"easy",
      tags:["Numerical","Practice Needed","Exam Likely"],
      content:`
        <p>An IPv4 address is 32 bits split into four 8-bit <b>octets</b>, each written in decimal.</p>
        <div class="example">
        <pre>11000000 . 10101000 . 10001000 . 00011100
   192        168        136         28</pre>
        IP address = <b>192.168.136.28</b></div>
        <p>To convert: each octet's bits use place values 128,64,32,16,8,4,2,1 — add the ones where the bit is 1.</p>` },

    { id:"l3-classes", title:"IPv4 address classes A–E", difficulty:"medium",
      tags:["Theory","Numerical","Exam Likely","Must Revise","Definition"],
      content:`
        <div class="simple">IPv4 splits addresses into 5 classes. A, B, C are for normal use; D is multicast; E is experimental.</div>
        <h4>Find the class from the first bits</h4>
        <table><tr><th>Leading bits</th><th>Class</th></tr>
        <tr><td>0...</td><td>A</td></tr><tr><td>10...</td><td>B</td></tr>
        <tr><td>110...</td><td>C</td></tr><tr><td>1110...</td><td>D (multicast)</td></tr>
        <tr><td>1111...</td><td>E (experimental)</td></tr></table>
        <h4>Network vs host split</h4>
        <table><tr><th>Class</th><th>First octet</th><th>Network part</th><th>Host part</th><th>Default mask</th></tr>
        <tr><td>A</td><td>1–126</td><td>8 bits</td><td>24 bits</td><td>255.0.0.0</td></tr>
        <tr><td>B</td><td>128–191</td><td>16 bits</td><td>16 bits</td><td>255.255.0.0</td></tr>
        <tr><td>C</td><td>192–223</td><td>24 bits</td><td>8 bits</td><td>255.255.255.0</td></tr></table>
        <div class="warn"><b>Memorise the ranges:</b> 1–126 = A, 128–191 = B, 192–223 = C. This is needed in almost every numerical question.</div>` },

    { id:"l3-special", title:"Network address, broadcast & usable hosts", difficulty:"medium",
      tags:["Numerical","Formula","Exam Likely","Must Revise","Practice Needed"],
      content:`
        <table><tr><th>Host bits</th><th>Meaning</th></tr>
        <tr><td>All 0s</td><td>Network address</td></tr>
        <tr><td>All 0s except last = 1</td><td>First usable IP</td></tr>
        <tr><td>All 1s except last = 0</td><td>Last usable IP</td></tr>
        <tr><td>All 1s</td><td>Directed Broadcast Address (DBA)</td></tr></table>
        <div class="formula">Usable hosts = 2^(host bits) − 2
Networks = 2^(network bits)</div>
        <p>We subtract 2 because one address is the network and one is the broadcast.</p>
        <div class="example">Class B has 16 host bits → 2^16 − 2 = <b>65,534</b> usable hosts. Class B has 14 network bits → 2^14 = <b>16,384</b> networks.</div>` },

    { id:"l3-summary", title:"IPv4 summary & IPv6 intro", difficulty:"easy",
      tags:["Theory","Numerical"],
      content:`
        <table><tr><th>Class</th><th>First octet</th><th>Default mask</th><th>Networks</th><th>Hosts/block</th></tr>
        <tr><td>A</td><td>1–126</td><td>255.0.0.0</td><td>126</td><td>16,777,214</td></tr>
        <tr><td>B</td><td>128–191</td><td>255.255.0.0</td><td>16,384</td><td>65,534</td></tr>
        <tr><td>C</td><td>192–223</td><td>255.255.255.0</td><td>2,097,152</td><td>254</td></tr></table>
        <h4>IPv4 vs IPv6</h4>
        <ul><li><b>IPv4:</b> 32-bit addresses, most routers still use it, running out of space.</li>
        <li><b>IPv6:</b> 128-bit addresses, much larger space; needs upgraded routers/hardware.</li></ul>` }
  ]
},

/* ===================== LECTURE 4 ===================== */
{
  section:"Lecture 4 — Addresses, Masks & Network Address", lec:4, kind:"both",
  items:[
    { id:"l4-mask", title:"Default subnet mask & CIDR", difficulty:"easy",
      tags:["Theory","Numerical","Definition","Exam Likely"],
      content:`
        <div class="simple"><b>Subnet mask</b> tells which part of an IP is the network and which is the host. Mask bit 1 = network, 0 = host.</div>
        <p><b>CIDR</b> (Classless Inter-Domain Routing) writes the mask as a /number = how many 1-bits it has.</p>
        <table><tr><th>Class</th><th>Default mask</th><th>CIDR</th></tr>
        <tr><td>A</td><td>255.0.0.0</td><td>/8</td></tr>
        <tr><td>B</td><td>255.255.0.0</td><td>/16</td></tr>
        <tr><td>C</td><td>255.255.255.0</td><td>/24</td></tr></table>
        <div class="example">Default mask of <code>172.20.5.6</code>? 172 is in 128–191 → Class B → mask <b>255.255.0.0</b>.</div>` },

    { id:"l4-netaddr", title:"Finding the network address (bitwise AND)", difficulty:"medium",
      tags:["Numerical","Formula","Exam Likely","Practice Needed","Must Revise"],
      content:`
        <div class="simple">Network address = first address of a subnet. Get it by ANDing the IP with the mask (it zeroes the host bits).</div>
        <div class="example">
        <pre>IP:    11000000.10101000.00001010.00011001  (192.168.10.25)
AND
Mask:  11111111.11111111.11111111.00000000  (255.255.255.0)
=      11000000.10101000.00001010.00000000  (192.168.10.0)</pre>
        Network Address = <b>192.168.10.0</b></div>
        <p>Shortcut: where the mask is 255 keep the octet, where it is 0 set the octet to 0.</p>
        <h4>Class examples</h4>
        <ul><li><code>10.2.100.17</code> /8 → network 10.0.0.0, DBA 10.255.255.255</li>
        <li><code>130.1.2.3</code> /16 → network 130.1.0.0, DBA 130.1.255.255</li>
        <li><code>192.168.10.11</code> /24 → network 192.168.10.0, DBA 192.168.10.255</li></ul>` },

    { id:"l4-practice", title:"Practice: find these network addresses", difficulty:"medium",
      tags:["Numerical","Practice Needed"],
      content:`
        <table><tr><th>IP</th><th>Mask</th><th>Network address</th></tr>
        <tr><td>192.168.5.23</td><td>255.255.255.0</td><td><b>192.168.5.0</b></td></tr>
        <tr><td>10.45.78.9</td><td>255.0.0.0</td><td><b>10.0.0.0</b></td></tr>
        <tr><td>172.16.200.15</td><td>255.255.0.0</td><td><b>172.16.0.0</b></td></tr>
        <tr><td>192.168.1.199</td><td>255.255.255.0</td><td><b>192.168.1.0</b></td></tr></table>
        <p>Reference: Comer, Chapter 21.</p>` }
  ]
},

/* ===================== LECTURE 5 ===================== */
{
  section:"Lecture 5 — Subnetting & CIDR", lec:5, kind:"numerical",
  items:[
    { id:"l5-problems", title:"Why subnetting? Problems with classful addressing", difficulty:"medium",
      tags:["Theory","Exam Likely","Definition"],
      content:`
        <div class="simple">Classful addressing wastes addresses because the jumps between class sizes are huge.</div>
        <ul>
          <li><b>Address wastage:</b> need 1000 hosts? Class C (254) too small, Class B (65,534) wastes 64,000+.</li>
          <li><b>No flexibility:</b> only small/large/huge choices, no in-between.</li>
          <li><b>Exploding routing tables:</b> backbone routers need an entry per network.</li>
          <li><b>IPv4 exhaustion:</b> 32-bit space runs out → solution is IPv6.</li>
        </ul>
        <p>The fixes are <b>Subnetting</b> and <b>CIDR</b>.</p>` },

    { id:"l5-cidr", title:"Classless addressing (CIDR) rules", difficulty:"medium",
      tags:["Theory","Numerical","Definition","Exam Likely"],
      content:`
        <p>CIDR (introduced by IETF in 1993) allows custom-sized networks like /20, /22, /27. Written as <code>ddd.ddd.ddd.ddd/m</code> where m = number of 1-bits in the mask.</p>
        <h4>Three CIDR rules</h4>
        <ol><li>The number of addresses requested must be a <b>power of 2</b>.</li>
        <li>The block must be <b>contiguous</b> unallocated addresses.</li>
        <li>The <b>first address</b> must be divisible by the block size.</li></ol>
        <div class="example">A network with 9 hosts needs 4 host bits (since 2^4=16 ≥ 9+2). So a /28 prefix fits perfectly instead of wasting a whole Class C.</div>` },

    { id:"l5-dhcp", title:"DHCP and the DORA process", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <div class="simple"><b>DHCP</b> automatically gives a device its IP address and settings, so networks become plug-and-play and avoid IP conflicts.</div>
        <h4>DORA — the 4 steps</h4>
        <ol>
          <li><b>Discover:</b> client broadcasts "any DHCP server out there?"</li>
          <li><b>Offer:</b> server offers an IP + mask + gateway.</li>
          <li><b>Request:</b> client says "I accept this IP".</li>
          <li><b>Acknowledge (ACK):</b> server confirms and assigns it.</li>
        </ol>` },

    { id:"l5-subnetting", title:"What subnetting is + how to do it", difficulty:"hard",
      tags:["Numerical","Formula","High Priority","Exam Likely","Practice Needed","Must Revise"],
      content:`
        <div class="simple">Subnetting splits the host part into a <b>subnet number</b> + a smaller host number, making a 3-level hierarchy: Network – Subnet – Host.</div>
        <p>You <b>borrow bits</b> from the host part to create subnets.</p>
        <div class="formula">Number of subnets = 2^(borrowed bits)
Hosts per subnet = 2^(remaining host bits) − 2
Block size = 256 − (last octet of mask)</div>
        <h4>Method (step by step)</h4>
        <ol>
          <li>Find the class and default mask.</li>
          <li>Decide bits to borrow: pick the smallest b with 2^b ≥ subnets needed (or remaining host bits big enough for required hosts).</li>
          <li>New prefix = default + borrowed; build the custom mask.</li>
          <li>Block size = 256 − mask's last non-255 octet.</li>
          <li>List subnets by stepping the relevant octet by block size.</li>
        </ol>` },

    { id:"l5-worked", title:"Worked example: 192.168.20.77/27", difficulty:"hard",
      tags:["Numerical","Exam Likely","Practice Needed","High Priority"],
      content:`
        <div class="example">
        <p>Prefix /27 → host bits = 32 − 27 = <b>5</b>. Mask = <code>11111111.11111111.11111111.11100000</code> → last octet 224 → <b>255.255.255.224</b>. Block size = 256 − 224 = <b>32</b>.</p>
        <pre>.0   – .31
.32  – .63
.64  – .95   <- 77 falls here
.96  – .127
...</pre>
        <table><tr><th>Field</th><th>Value</th></tr>
        <tr><td>Network address</td><td>192.168.20.64</td></tr>
        <tr><td>Broadcast</td><td>192.168.20.95</td></tr>
        <tr><td>First usable host</td><td>192.168.20.65</td></tr>
        <tr><td>Last usable host</td><td>192.168.20.94</td></tr>
        <tr><td>Hosts</td><td>2^5 − 2 = 30</td></tr></table></div>` },

    { id:"l5-design", title:"Design examples (by subnets or by hosts)", difficulty:"hard",
      tags:["Numerical","Practice Needed","Exam Likely"],
      content:`
        <div class="example"><b>Need 14 subnets, 14 hosts each — 192.10.10.0 (Class C)</b><br>
        Borrow 4 bits → 2^4 = 16 subnets, mask 255.255.255.240, usable = 16 − 2 = 14 (correct)</div>
        <div class="example"><b>Need 250 subnets — 101.0.0.0 (Class A)</b><br>
        Borrow 8 bits → 256 subnets, mask 255.255.0.0, hosts 2^16 = 65,536, usable 65,534.</div>
        <div class="example"><b>Need 10 subnets — 172.59.0.0 (Class B)</b><br>
        Borrow 4 bits → 16 subnets, mask 255.255.240.0, hosts 2^12 = 4,096, usable 4,094.</div>
        <p>Tip: "at least N subnets" → smallest b with 2^b ≥ N. "At least H hosts" → smallest h with 2^h − 2 ≥ H.</p>` }
  ]
},

/* ===================== LECTURE 6 ===================== */
{
  section:"Lecture 6 — Forwarding & Routing", lec:6, kind:"both",
  items:[
    { id:"l6-layering", title:"Protocols, suites & layering", difficulty:"easy",
      tags:["Theory","Definition"],
      content:`
        <div class="simple"><b>Interoperability</b> = two devices communicate with no misunderstanding. A <b>protocol</b> is the procedure they both follow.</div>
        <p>Because one protocol can't do everything well, protocols are built in cooperative sets called <b>suites/families</b>; each handles one part. A <b>layering model</b> splits the whole communication problem into stacked layers so designers focus on one piece at a time.</p>` },

    { id:"l6-store-forward", title:"Store-and-forward packet switching", difficulty:"medium",
      tags:["Theory","Definition","Exam Likely"],
      content:`
        <div class="simple">A switch fully receives a packet into memory (<b>store</b>), then sends it on (<b>forward</b>).</div>
        <ul>
          <li><b>Store:</b> on arrival, the packet is copied into memory.</li>
          <li><b>Forward:</b> the processor reads the destination and sends it toward it.</li>
        </ul>
        <p>The packet waits until it has fully arrived and the checksum is verified, then moves to the next router until it reaches the destination host.</p>
        <h4>Switch vs Router</h4>
        <table><tr><th>Device</th><th>Role</th></tr>
        <tr><td>Switch</td><td>Connects devices in the same LAN</td></tr>
        <tr><td>Router</td><td>Connects different networks (LAN↔LAN, LAN↔Internet)</td></tr></table>` },

    { id:"l6-hierarchical", title:"Hierarchical addressing & next-hop forwarding", difficulty:"medium",
      tags:["Theory","Numerical","Definition","Exam Likely"],
      content:`
        <p>WAN addresses are split into <b>(switch #, port #)</b> — a prefix (site) and suffix (computer). Example: port 6 on switch 2 → address <b>[2,6]</b>.</p>
        <h4>Next-hop forwarding</h4>
        <p>A switch only needs to know <b>which outgoing link</b> reaches the next switch — not the full route. It reads the switch number from the destination address; if it equals its own ID, deliver locally, otherwise forward.</p>
        <div class="example">Switch 2 receives a packet for <b>[3,5]</b>: it extracts "3", looks in its table, and forwards to the interface leading to switch 3.</div>` },

    { id:"l6-fwd-tables", title:"Forwarding tables & default routes", difficulty:"medium",
      tags:["Numerical","Diagram","Exam Likely","Practice Needed"],
      content:`
        <p>Each router keeps a forwarding table mapping "to reach X" → "use this link". When many entries point to the same next hop (a switch with one connection), we replace them with a single <b>default route</b> marked <code>*</code> (lowest priority).</p>
        <div class="example"><b>Node 1, with default route:</b>
        <pre>To Reach | Next Hop
   1     |   —
   *     | (1,3)</pre>
        All non-local traffic goes out link (1,3).</div>
        <h4>Longest-prefix worked example</h4>
        <table><tr><th>Destination</th><th>Matches</th><th>Interface</th></tr>
        <tr><td>192.168.1.45</td><td>192.168.1.0/24</td><td>eth0</td></tr>
        <tr><td>192.168.2.200</td><td>192.168.2.0/24</td><td>eth1</td></tr>
        <tr><td>10.5.6.7</td><td>10.0.0.0/8</td><td>eth2</td></tr></table>` },

    { id:"l6-fwd-vs-routing", title:"Forwarding vs Routing", difficulty:"medium",
      tags:["Theory","Exam Likely","Must Revise","Definition"],
      content:`
        <div class="simple">Easy way to remember: <b>Routing</b> decides the whole path; <b>Forwarding</b> is the single quick step of moving a packet to the next link.</div>
        <table><tr><th></th><th>Forwarding</th><th>Routing</th></tr>
        <tr><td>Scope</td><td>Local to one router</td><td>Network-wide</td></tr>
        <tr><td>Speed</td><td>Nanoseconds</td><td>Slower</td></tr>
        <tr><td>Built in</td><td>Hardware</td><td>Software</td></tr></table>
        <p><b>Analogy (e-commerce):</b> Routing = which warehouse and courier to use. Forwarding = each hub passing the package one step onward.</p>` },

    { id:"l6-dvr", title:"Distance Vector Routing (Bellman-Ford)", difficulty:"hard",
      tags:["Numerical","High Priority","Exam Likely","Practice Needed","Must Revise"],
      content:`
        <div class="simple">Each router knows only its direct neighbours at first, then shares tables until everyone learns the least-cost path to everyone.</div>
        <ul><li>Uses the <b>Bellman-Ford equation</b>.</li>
        <li>The routing table is called the <b>distance vector</b>.</li>
        <li>Cost is an estimate, refined every iteration.</li></ul>
        <h4>Worked update at Node A</h4>
        <p>Graph edges: A–B=1, A–C=5, B–C=3, B–E=9, C–D=4, D–E=2.</p>
        <div class="example">
        <pre>To reach D:  via B = 1+∞ = ∞
             via C = 5+4 = 9  ← min  (next hop C)
To reach E:  via B = 1+9 = 10 ← min  (next hop B)
             via C = 5+∞ = ∞</pre>
        Updated Node A table: A=0, B=1, C=5, D=9 (via C), E=10 (via B).</div>
        <div class="warn"><b>Likely task:</b> update routing tables at other nodes (D, E) the same way using Bellman-Ford.</div>` }
  ]
},

/* ===================== LECTURE 7 ===================== */
{
  section:"Lecture 7 — Routing Algorithms", lec:7, kind:"theory",
  items:[
    { id:"l7-graph", title:"Routing as a graph (least-cost path)", difficulty:"medium",
      tags:["Theory","Numerical","Definition","Exam Likely"],
      content:`
        <div class="simple">A routing algorithm finds the <b>least-cost path</b> from sender to receiver. We model the network as a graph G = (N, E).</div>
        <ul><li><b>Nodes (N):</b> routers.</li><li><b>Edges (E):</b> physical links, each with a cost.</li>
        <li>Cost of edge (x,y) = c(x,y). If no link, c = ∞. Undirected: c(x,y)=c(y,x).</li></ul>
        <p>Cost of a path = sum of edge costs. If all edges cost the same, least-cost = shortest path (fewest links).</p>
        <div class="example">Least-cost path u → w is (u,x,y,w) with cost 1+1+1 = 3.</div>` },

    { id:"l7-ls-vs-dv", title:"Centralized (Link-State) vs Decentralized (Distance-Vector)", difficulty:"medium",
      tags:["Theory","High Priority","Exam Likely","Must Revise","Definition"],
      content:`
        <table><tr><th></th><th>Link-State (LS)</th><th>Distance-Vector (DV)</th></tr>
        <tr><td>Knowledge</td><td>Global — knows every link</td><td>Local — only neighbours</td></tr>
        <tr><td>How</td><td>Central controller, Dijkstra's algorithm</td><td>Iterative exchange with neighbours</td></tr>
        <tr><td>Protocol</td><td><b>OSPF</b></td><td><b>RIP</b></td></tr>
        <tr><td>Pros</td><td>Accurate, optimal paths</td><td>No single point of failure, scales, simple</td></tr>
        <tr><td>Cons</td><td>Single point of failure, high overhead</td><td>Slow convergence, loops, count-to-infinity</td></tr></table>
        <p><b>OSPF</b> = Open Shortest Path First, an interior gateway protocol that routes inside one <b>Autonomous System</b> (a network under one administration, e.g. a university or ISP).</p>` },

    { id:"l7-count-infinity", title:"Count-to-infinity problem", difficulty:"medium",
      tags:["Theory","Exam Likely","Definition"],
      content:`
        <div class="simple">When a destination goes down, DV routers may keep raising the hop count (1,2,3,…) toward infinity because they wrongly believe a path still exists.</div>
        <p>This causes slow convergence and routing loops. It happens because routers trust their neighbours' old information.</p>` },

    { id:"l7-static-dynamic", title:"Static vs Dynamic; Load-sensitive vs Load-insensitive", difficulty:"medium",
      tags:["Theory","Exam Likely","Definition","Must Revise"],
      content:`
        <h4>Static vs Dynamic</h4>
        <table><tr><th>Static</th><th>Dynamic</th></tr>
        <tr><td>Routes set manually, rarely change</td><td>Routes adapt to traffic/topology</td></tr>
        <tr><td>No protocol, predictable, simple</td><td>Uses RIP / OSPF / BGP</td></tr>
        <tr><td>Used in small labs, military/banking (controlled)</td><td>Used across the real Internet (like Google Maps re-routing)</td></tr></table>
        <p><b>BGP</b> = Border Gateway Protocol, builds a graph of autonomous systems from info exchanged between BGP routers.</p>
        <h4>Load-sensitive vs Load-insensitive</h4>
        <p>Load-sensitive costs change with congestion; load-insensitive costs don't. Today's Internet (RIP, OSPF, BGP) is <b>load-insensitive</b> because load-sensitive routing causes route <b>oscillations</b> (A→B, B→A…), huge overhead, and decisions based on already-outdated data — bad for video calls and streaming.</p>` }
  ]
},

/* ===================== LECTURE 8 ===================== */
{
  section:"Lecture 8 — OSI Model (7 Layers)", lec:8, kind:"theory",
  items:[
    { id:"l8-overview", title:"OSI overview & mnemonics", difficulty:"easy",
      tags:["Theory","High Priority","Exam Likely","Must Revise","Definition"],
      content:`
        <div class="simple">The <b>OSI model</b> (made by ISO in 1978) splits networking into <b>7 layers</b>, so complex systems become manageable and vendors interoperate.</div>
        <pre>7 Application
6 Presentation
5 Session
4 Transport
3 Network
2 Data Link
1 Physical</pre>
        <h4>Memory aids</h4>
        <ul><li>Top→Bottom: <b>A</b>ll <b>P</b>eople <b>S</b>eem <b>T</b>o <b>N</b>eed <b>D</b>ata <b>P</b>rocessing</li>
        <li>Bottom→Top: <b>P</b>lease <b>D</b>o <b>N</b>ot <b>T</b>hrow <b>S</b>ausage <b>P</b>izza <b>A</b>way</li></ul>` },

    { id:"l8-upper", title:"Layers 7–5: Application, Presentation, Session", difficulty:"medium",
      tags:["Theory","Exam Likely","Definition"],
      content:`
        <h4>Layer 7 — Application</h4>
        <p>Closest to the user. Identifies communication partners, checks resource availability, and synchronizes communication. Protocols: <b>HTTP, FTP, SMTP</b>.</p>
        <h4>Layer 6 — Presentation</h4>
        <p>The "syntax layer": <b>translation, encryption/decryption, compression</b>. Makes data readable by the other system.</p>
        <h4>Layer 5 — Session</h4>
        <p>Starts, manages, and ends sessions. Handles modes (simplex/half/full duplex) and recovery using <b>checkpoints</b> (resume a big transfer from the last checkpoint instead of restarting).</p>` },

    { id:"l8-transport", title:"Layer 4: Transport (TCP & UDP, handshake)", difficulty:"medium",
      tags:["Theory","High Priority","Exam Likely","Must Revise","Definition"],
      content:`
        <p>Provides reliable transfer to upper layers via <b>flow control</b>, <b>segmentation/reassembly</b>, and <b>error control</b>. Adds sequence numbers and manages connections.</p>
        <h4>TCP 3-way handshake</h4>
        <ol><li>A → B: SYN ("can we talk?")</li><li>B → A: SYN-ACK ("yes, ready")</li><li>A → B: ACK ("let's start")</li></ol>
        <table><tr><th>Feature</th><th>TCP</th><th>UDP</th></tr>
        <tr><td>Connection</td><td>Oriented</td><td>Connectionless</td></tr>
        <tr><td>Reliable</td><td>Yes</td><td>No</td></tr>
        <tr><td>Speed</td><td>Slower</td><td>Faster</td></tr>
        <tr><td>Use</td><td>Web, email, downloads</td><td>Streaming, gaming, live calls</td></tr></table>
        <div class="warn"><b>YouTube point:</b> streaming prefers UDP — a lost packet is ignored so video keeps flowing instead of buffering.</div>` },

    { id:"l8-lower", title:"Layers 3–1: Network, Data Link, Physical", difficulty:"medium",
      tags:["Theory","Diagram","Exam Likely","Definition"],
      content:`
        <h4>Layer 3 — Network</h4>
        <p>Routing + logical addressing. <b>Routers</b> read the destination <b>IP</b>, pick the best route, and forward hop by hop.</p>
        <h4>Layer 2 — Data Link</h4>
        <p>Delivers data <b>within the same network</b> using <b>MAC addresses</b>. <b>Switches</b> read frames; error-free node-to-node delivery.</p>
        <h4>Layer 1 — Physical</h4>
        <p>Sends raw <b>bits</b> as electrical/optical/radio signals over the medium. Defines voltages, timing, connectors (RJ45), cables. Understands signals, not data.</p>
        <div class="simple"><b>Remember:</b> IP address gets data to the right network; MAC address delivers it to the exact device in that network.</div>` },

    { id:"l8-encap", title:"Encapsulation & PDUs summary", difficulty:"easy",
      tags:["Theory","Diagram","Exam Likely","Must Revise"],
      content:`
        <table><tr><th>Layer</th><th>Action</th><th>Unit (PDU)</th></tr>
        <tr><td>Transport</td><td>Break into segments, add ports</td><td>Segment</td></tr>
        <tr><td>Network</td><td>Add IP addresses</td><td>Packet</td></tr>
        <tr><td>Data Link</td><td>Add MAC + FCS trailer</td><td>Frame</td></tr>
        <tr><td>Physical</td><td>Send raw bits</td><td>Bits</td></tr></table>
        <p>Each layer wraps the data in its own header (and trailer) — this is <b>encapsulation</b>.</p>
        <table><tr><th>Device</th><th>Works at</th></tr>
        <tr><td>Router</td><td>Network layer (packets)</td></tr>
        <tr><td>Switch</td><td>Data Link layer (frames)</td></tr></table>` }
  ]
},

/* ===================== LECTURE 10 ===================== */
{
  section:"Lecture 10 — Transport Protocols, DHCP, SNMP, VoIP & Checksum", lec:10, kind:"both",
  items:[
    { id:"l10-tcp-udp", title:"TCP vs UDP in detail", difficulty:"medium",
      tags:["Theory","Exam Likely","Definition","Must Revise"],
      content:`
        <h4>TCP</h4>
        <ul><li>Layer 4, connection-oriented (needs 3-way handshake first).</li>
        <li>Reliable, ordered, does error checking, full duplex, header ~20 bytes.</li>
        <li>Used by HTTP, FTP, Telnet.</li></ul>
        <h4>UDP</h4>
        <ul><li>Connectionless, no handshake, unreliable but fast.</li>
        <li>May lose or reorder segments; header 8 bytes.</li>
        <li>Used by VoIP, DHCP, SNMP, RIP, DNS.</li></ul>
        <table><tr><th>Feature</th><th>TCP</th><th>UDP</th></tr>
        <tr><td>Overhead</td><td>High</td><td>Low</td></tr>
        <tr><td>Flow control</td><td>Yes</td><td>No</td></tr>
        <tr><td>Header</td><td>~20 bytes</td><td>8 bytes</td></tr></table>` },

    { id:"l10-services", title:"DHCP, SNMP, VoIP", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely"],
      content:`
        <ul>
          <li><b>DHCP</b> — client/server protocol that auto-assigns IP, subnet mask, and gateway. Used in home WiFi, labs, offices.</li>
          <li><b>SNMP</b> — manages and monitors network devices; admins watch traffic, get failure alerts, find overloaded devices.</li>
          <li><b>VoIP</b> — voice calls over the Internet instead of analog phone lines; voice travels like data. Examples: Teams, Zoom, WhatsApp.</li>
        </ul>` },

    { id:"l10-checksum-basic", title:"Checksum: what it is & how it works", difficulty:"medium",
      tags:["Theory","Numerical","High Priority","Exam Likely","Definition","Must Revise"],
      content:`
        <div class="simple"><b>Checksum</b> = a small value calculated from data, like a digital fingerprint, used to <b>detect</b> errors (it does not correct them).</div>
        <h4>How it works</h4>
        <p><b>Sender:</b> add up the data → get checksum → send data + checksum.<br>
        <b>Receiver:</b> redo the calculation → compare. Match = no error; mismatch = error detected.</p>
        <div class="example">Data 10, 20, 30 → sum 60 sent. If 20 became 25, receiver gets 65 ≠ 60 → error detected.</div>
        <p>Most used in the <b>Transport Layer</b> (TCP mandatory, UDP optional) and in IPv4 headers.</p>` },

    { id:"l10-checksum-1s", title:"1's complement checksum (full method)", difficulty:"hard",
      tags:["Numerical","High Priority","Exam Likely","Practice Needed","Must Revise","Formula"],
      content:`
        <div class="simple">Better method: send the <b>complement</b> of the sum. Then the receiver adds everything including the checksum and should get <b>0</b> (or all 1s before complement).</div>
        <h4>Sender steps</h4>
        <ol><li>Split message into fixed-size words (4-bit or 16-bit).</li>
        <li>Set checksum word = 0.</li>
        <li>Add all words; <b>wrap any carry</b> back into the low bits.</li>
        <li>Take the <b>1's complement</b> of the sum → that is the checksum.</li>
        <li>Send data + checksum.</li></ol>
        <h4>Receiver steps</h4>
        <ol><li>Add all words including the checksum (wrap carries).</li>
        <li>Take 1's complement. If result = 0 → accept; else reject.</li></ol>
        <div class="example"><b>4-bit example, data 7,11,12,0,6</b><br>
        Sum = 36 = 100100 → wrap: 0100 + 10 = 0110 (=6) → 1's complement 1001 = <b>9</b> = checksum.<br>
        Receiver: 7+11+12+0+6+9 = 45 = 101101 → wrap 1101+10 = 1111 → complement 0000 → no error.</div>` },

    { id:"l10-checksum-hex", title:"16-bit hex checksum example", difficulty:"hard",
      tags:["Numerical","Exam Likely","Practice Needed"],
      content:`
        <div class="example"><b>Data:</b> 3456 ABCC 02BC EEEE<br>
        Add the four words (with carries wrapped) → sum D1CD → 1's complement → checksum <b>2E32</b>.<br>
        Send: 3456 ABCC 02BC EEEE 2E32.<br>
        Receiver adds all five → FFFF → complement 0000 → <b>no error</b>.</div>
        <div class="warn"><b>Limitation:</b> if two errors cancel each other out (complementary bit flips), the sum stays the same and the checksum <b>fails to detect</b> the error.</div>` }
  ]
},

/* ===================== LECTURE 11 ===================== */
{
  section:"Lecture 11 — Error Checking & Parity", lec:11, kind:"both",
  items:[
    { id:"l11-errors", title:"Types of transmission errors", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <ul>
          <li><b>Single-bit error:</b> exactly one bit flips. Often from very short interference.</li>
          <li><b>Burst error:</b> several bits change. Often from longer interference.</li>
          <li><b>Erasure (ambiguity):</b> the received signal isn't clearly 0 or 1.</li>
        </ul>` },

    { id:"l11-parity", title:"Single parity checking (even/odd)", difficulty:"medium",
      tags:["Theory","Numerical","Exam Likely","Definition","Practice Needed"],
      content:`
        <div class="simple">Add one extra <b>parity bit</b> to a byte so the total number of 1s is even (even parity) or odd (odd parity). Sender and receiver must agree which.</div>
        <p><b>Even parity:</b> if the data already has an even number of 1s, parity bit = 0; if odd, parity bit = 1.</p>
        <div class="example">Data <code>10101101</code> has five 1s (odd). For even parity, add a 1 → send <code>101011011</code>. Receiver counts 1s = even → no error.</div>
        <h4>Limitation</h4>
        <p>Only detects an <b>odd</b> number of flipped bits. If 2, 4, 6, or 8 bits flip, it wrongly says "valid". Cannot correct errors. Good for simple links, embedded systems, RAM; modern networks prefer checksum and CRC.</p>` },

    { id:"l11-parity-ex", title:"Parity worked example (D596, LSB)", difficulty:"medium",
      tags:["Numerical","Practice Needed","Exam Likely"],
      content:`
        <div class="example"><b>16-bit data D596, even parity, parity at LSB</b><br>
        D=1101, 5=0101, 9=1001, 6=0110 → <code>1101 0101 1001 0110</code><br>
        Count 1s: 3+2+2+2 = 9 (odd) → parity bit = 1 to make it even.<br>
        Transmitted: <code>1101 0101 1001 0110 1</code> (now ten 1s, even).</div>
        <div class="warn"><b>Two-flip trap:</b> if two bits flip, the count stays even and the error is missed.</div>` },

    { id:"l11-channel", title:"Channel coding: FEC vs ARQ", difficulty:"easy",
      tags:["Theory","Definition"],
      content:`
        <p>Maths techniques to handle errors are called <b>channel coding</b>.</p>
        <ul>
          <li><b>FEC (Forward Error Correction):</b> adds extra info so the receiver can find and <b>correct</b> errors itself.</li>
          <li><b>ARQ (Automatic Repeat reQuest):</b> sender and receiver exchange messages; bad data is <b>re-sent</b>.</li>
        </ul>` }
  ]
},

/* ===================== LECTURE 12 ===================== */
{
  section:"Lecture 12 — Network Security: Cryptography & CRC", lec:12, kind:"both",
  items:[
    { id:"l12-secure", title:"Goals of secure communication", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <ul>
          <li><b>Confidentiality:</b> only sender and receiver understand the message (needs encryption).</li>
          <li><b>Message Integrity:</b> content isn't changed in transit.</li>
          <li><b>End-point Authentication:</b> each side confirms who the other is.</li>
          <li><b>Operational Security:</b> firewalls and intrusion detection guard the network.</li>
        </ul>
        <p><b>Firewall:</b> sits between the org network and the public Internet, controlling packets. <b>IDS:</b> watches for suspicious activity and alerts admins.</p>` },

    { id:"l12-crypto", title:"Cryptography basics (Alice, Bob, Trudy)", difficulty:"medium",
      tags:["Theory","Definition","Exam Likely"],
      content:`
        <p>Cryptography disguises data so an intruder learns nothing; the receiver can recover the original.</p>
        <ul>
          <li><b>Plaintext:</b> original message. <b>Ciphertext:</b> encrypted message.</li>
          <li><b>Encryption algorithm</b> + <b>key</b> → ciphertext. <b>Decryption algorithm</b> + key → plaintext.</li>
        </ul>
        <div class="simple"><b>Key idea:</b> the algorithm is public; the secret is the <b>key</b>.</div>
        <p>Trudy (the intruder) may eavesdrop, modify, insert, or delete messages.</p>` },

    { id:"l12-symmetric", title:"Symmetric ciphers: Caesar, Monoalphabetic, Vigenère", difficulty:"hard",
      tags:["Theory","Numerical","High Priority","Exam Likely","Practice Needed","Must Revise","Formula"],
      content:`
        <h4>Symmetric vs Public-key</h4>
        <p><b>Symmetric:</b> both sides share one secret key. <b>Public-key (asymmetric):</b> a public key (everyone) + a private key (one side only).</p>
        <h4>Caesar cipher</h4>
        <p>Shift each letter by k. Only 25 shifts → easily brute-forced.</p>
        <div class="example">"HELLO" with +3 → "KHOOR". "PHHW PH DIWHU FODVV" with −3 → "MEET ME AFTER CLASS".</div>
        <h4>Monoalphabetic cipher</h4>
        <p>Each letter maps to one fixed random letter → 26! (~4×10^26) keys, far stronger. Rule: one plaintext letter must map to exactly one ciphertext letter.</p>
        <h4>Vigenère cipher</h4>
        <p>Uses a keyword so each letter gets a different shift (A=0…Z=25).</p>
        <div class="formula">Encrypt: Cipher = (Plain + Key) mod 26
Decrypt: Plain = (Cipher − Key) mod 26</div>
        <div class="example">"HELLO" with key "KEY" → R I J V S. Vigenère is historical only now — broken by frequency analysis.</div>` },

    { id:"l12-aes-rsa", title:"Modern encryption: AES, RSA & hybrid", difficulty:"medium",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <ul>
          <li><b>AES</b> (symmetric): one shared key, very fast, used after the HTTPS connection is set up, in WhatsApp, banking, WiFi.</li>
          <li><b>RSA</b> (asymmetric, Rivest-Shamir-Adleman, 1977): public key encrypts, private key decrypts. Used in the HTTPS handshake and digital certificates.</li>
        </ul>
        <div class="simple"><b>Hybrid encryption (HTTPS):</b> RSA safely exchanges a session key, then AES encrypts all the actual data. Best of both — secure key exchange + fast bulk encryption.</div>` },

    { id:"l12-crc", title:"CRC (Cyclic Redundancy Check) & XOR", difficulty:"hard",
      tags:["Numerical","High Priority","Exam Likely","Practice Needed","Must Revise","Formula"],
      content:`
        <div class="simple"><b>CRC</b> treats the message as a big binary number, divides it by a fixed generator using <b>XOR</b> (modulo-2), and the remainder is the CRC code. Also called polynomial code error detection.</div>
        <p>In modulo-2 maths there are no carries/borrows; addition and subtraction are both <b>XOR</b>. XOR: same bits → 0, different → 1.</p>
        <h4>Sender steps</h4>
        <ol><li>Append (L−1) zeros to the message (L = generator length).</li>
        <li>XOR-divide by the generator.</li><li>Remainder = CRC; append it to the data and send.</li></ol>
        <h4>Receiver steps</h4>
        <ol><li>XOR-divide received data by the same generator.</li>
        <li>Remainder 0 → no error; non-zero → error.</li></ol>
        <div class="example"><b>Message 1101011011, generator 10011 (L=5)</b><br>
        Append 4 zeros → 11010110110000 → XOR-divide → remainder <b>1110</b>.<br>
        Send 11010110111110. Receiver divides → remainder 0 → no error.</div>
        <p><b>Detection power:</b> CRC catches all bursts of length ≤ CRC length; CRC-32 catches ~99.99999998% of longer bursts.</p>` }
  ]
},

/* ===================== LECTURE 13 ===================== */
{
  section:"Lecture 13 — CRC, 2D Parity, Hashing & Signatures", lec:13, kind:"both",
  items:[
    { id:"l13-2dparity", title:"Two-dimensional parity check", difficulty:"hard",
      tags:["Numerical","High Priority","Exam Likely","Practice Needed","Must Revise"],
      content:`
        <div class="simple">Extends simple parity into <b>rows and columns</b>. It can find AND correct a single-bit error by its row+column intersection.</div>
        <h4>How</h4>
        <ol><li>Arrange data in a grid.</li><li>Add a parity bit to each row.</li><li>Add a parity row for each column.</li></ol>
        <div class="example"><b>Single-bit error:</b> one row's parity fails and one column's parity fails. Their crossing point is the wrong bit → flip it back.</div>
        <h4>Advantages / Limits</h4>
        <ul><li>Detects all single-bit errors and fixes them; stronger than 1D parity.</li>
        <li>Can miss some multiple-bit errors (e.g. errors forming a rectangle); adds overhead.</li></ul>
        <p>Used in serial links, sensors, RAM, cache, RAID (parity rebuilds a failed disk).</p>` },

    { id:"l13-msgauth", title:"Message authentication & replay attacks", difficulty:"medium",
      tags:["Theory","Definition","Exam Likely"],
      content:`
        <p>Message authentication ensures two things:</p>
        <ul><li><b>Data integrity:</b> data arrives unchanged.</li>
        <li><b>Source authentication:</b> data really came from the claimed sender.</li></ul>
        <p>Requirements: no modification, no insertion, no deletion, no replay.</p>
        <div class="simple"><b>Replay attack:</b> an attacker records valid auth info and re-sends it later to gain access. Like overhearing "Open Sesame" and reusing it.</div>` },

    { id:"l13-hash", title:"Cryptographic hash functions", difficulty:"medium",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <div class="simple">A <b>hash function</b> turns any-length input into a fixed-size output (a fingerprint / message digest). Same input → same hash; tiny change → totally different hash.</div>
        <div class="formula">h = H(M)
H = hash function, M = message, h = digest</div>
        <table><tr><th>Hash</th><th>Output</th></tr>
        <tr><td>SHA-256</td><td>256 bits</td></tr><tr><td>MD5</td><td>128 bits</td></tr>
        <tr><td>RIPEMD</td><td>160 bits</td></tr></table>
        <p><b>One-way:</b> easy to compute forward, practically impossible to reverse. So hashing is for verifying, not for encryption/decryption. If hash(sent) = hash(received), the data wasn't tampered.</p>` },

    { id:"l13-signatures", title:"Digital signatures & MAC vs signature", difficulty:"medium",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <p>A <b>digital signature</b> ties a message to its sender and provides <b>non-repudiation</b> (the signer can't deny it). The hash of a message is signed, not the whole message.</p>
        <h4>Method 1 — symmetric:</h4> sign the digest with a shared key (good for authentication, but no non-repudiation).
        <h4>Method 2 — public key:</h4> sign the digest with the sender's <b>private key</b>; anyone verifies with the sender's <b>public key</b>.
        <table><tr><th></th><th>MAC</th><th>Digital signature</th></tr>
        <tr><td>Verification</td><td>One party</td><td>Many parties</td></tr>
        <tr><td>Non-repudiation</td><td>No</td><td>Yes</td></tr></table>
        <p>The hash used must be pre-image resistant, weak collision resistant, and strong collision resistant.</p>` }
  ]
},

/* ===================== LECTURE 14 ===================== */
{
  section:"Lecture 14 — Hashing, Signatures, Banking & Email", lec:14, kind:"theory",
  items:[
    { id:"l14-hashuse", title:"Where hashing is used; hashing vs encryption", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely"],
      content:`
        <p>Hashing is used for integrity checking, password storage, digital signatures, and blockchain.</p>
        <div class="simple"><b>Hashing → integrity. Encryption → confidentiality.</b> Encryption hides data; hashing verifies data.</div>
        <ul><li><b>Passwords:</b> sites store the hash, not the real password. At login they hash your entry and compare.</li>
        <li><b>Blockchain:</b> hashes link blocks securely (used in Bitcoin).</li></ul>` },

    { id:"l14-sign-flow", title:"How digital signatures work (sender & receiver)", difficulty:"medium",
      tags:["Theory","Diagram","Exam Likely","Must Revise"],
      content:`
        <p>A digital signature is mathematical proof, not a scanned handwriting. It authenticates the sender and proves the content is unchanged.</p>
        <h4>Sender side</h4>
        <ol><li>Hash the message.</li><li>Encrypt the hash with the <b>private key</b> → that is the signature.</li><li>Attach it to the message.</li></ol>
        <h4>Receiver side</h4>
        <ol><li>Decrypt the signature with the sender's <b>public key</b> → original hash.</li>
        <li>Hash the received message again.</li><li>Compare. Match → authentic and unmodified.</li></ol>
        <h4>Keys</h4>
        <p><b>Private key:</b> known only to owner, creates signatures. <b>Public key:</b> known to all, verifies them.</p>` },

    { id:"l14-apps", title:"Signatures in email & banking (EFT)", difficulty:"easy",
      tags:["Theory","Exam Likely"],
      content:`
        <p>Applications: emails, data storage, electronic fund transfer, software distribution, smart cards, time-stamped signatures.</p>
        <h4>Email</h4>
        <p>Like a unique wax seal: only the sender owns the stamp, anyone can check it, and if the letter is changed the seal "breaks" mathematically. Used by Gmail and Outlook.</p>
        <h4>Banking / EFT</h4>
        <p>Bank A signs a transaction with the customer's private key; Bank B verifies with the public key. If hashes match, the transaction is authentic and the sender <b>can't deny it</b> later (non-repudiation). Used by SWIFT, PayPal, VISA, MasterCard. Banks add OTPs and AI fraud detection too.</p>` }
  ]
},

/* ===================== LECTURE 15 ===================== */
{
  section:"Lecture 15 — Cloud Computing & Data Packets", lec:15, kind:"theory",
  items:[
    { id:"l15-cloud", title:"Cloud computing & its characteristics", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <div class="simple"><b>Cloud computing</b> = using computing services (servers, storage, databases, software) over the Internet, paying for what you use.</div>
        <h4>Key traits</h4>
        <ul><li>Shared pool of resources, metered and billed by usage.</li>
        <li><b>Elastic computing:</b> get more or fewer resources on demand to match the workload.</li>
        <li>Cost-effective; providers handle maintenance and security.</li></ul>
        <p>Advantages: no big upfront hardware cost, easy data sharing/collaboration, scalable, familiar virtual environments.</p>` },

    { id:"l15-types", title:"Types of cloud & service models", difficulty:"medium",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <h4>Deployment types</h4>
        <ul><li><b>Public:</b> open to all over the Internet, highly scalable, less control (e.g. universities). Uses a <b>shared responsibility model</b>: provider secures the cloud, customer secures their data in the cloud.</li>
        <li><b>Private:</b> one organization owns it, isolated, limited scalability (e.g. banks).</li>
        <li><b>Hybrid:</b> mix of public + private; sensitive data private, flexible workloads public.</li>
        <li><b>Community/Federated:</b> shared by several organizations with common concerns.</li></ul>
        <h4>Service models</h4>
        <ul><li><b>IaaS:</b> virtual servers/storage/network (AWS EC2, Azure VMs).</li>
        <li><b>PaaS:</b> ready environments to build apps (Google App Engine).</li>
        <li><b>SaaS:</b> ready software (Zoom, Dropbox, Salesforce).</li></ul>` },

    { id:"l15-encap", title:"OSI layers & encapsulation (packet journey)", difficulty:"medium",
      tags:["Theory","Diagram","Exam Likely","Must Revise"],
      content:`
        <p>Each layer wraps data with its own header/trailer — <b>encapsulation</b>.</p>
        <table><tr><th>Layer</th><th>PDU</th><th>Key addition</th></tr>
        <tr><td>7 Application</td><td>Data</td><td>Raw user data</td></tr>
        <tr><td>6 Presentation</td><td>Data</td><td>Encryption, compression</td></tr>
        <tr><td>5 Session</td><td>Data</td><td>Session management</td></tr>
        <tr><td>4 Transport</td><td>Segment/Datagram</td><td>Port number (16-bit)</td></tr>
        <tr><td>3 Network</td><td>Packet</td><td>Source & dest IP</td></tr>
        <tr><td>2 Data Link</td><td>Frame</td><td>MAC + FCS trailer</td></tr>
        <tr><td>1 Physical</td><td>Bits</td><td>Electrical/optical/radio signals</td></tr></table>
        <p>IP address routes data to the device; the <b>port number</b> sends it to the correct program. MAC = physical hardware ID (can be spoofed temporarily).</p>` }
  ]
},

/* ===================== LECTURE 16 ===================== */
{
  section:"Lecture 16 — Network Performance", lec:16, kind:"both",
  items:[
    { id:"l16-bandwidth", title:"Bandwidth (Hz vs bps) & units", difficulty:"medium",
      tags:["Theory","Numerical","Definition","Exam Likely","Must Revise"],
      content:`
        <p>Bandwidth has two meanings:</p>
        <ul><li><b>In Hertz:</b> the range of frequencies a channel can carry (analog — radio, old TV, wireless spectrum).</li>
        <li><b>In bits/sec:</b> the digital data rate, often called <b>capacity</b> (internet speed). A 100 Mbps link sends 100 million bits/sec.</li></ul>
        <p>More frequency bandwidth (Hz) usually carries more data (bps). Units: bps → kbps (10^3) → Mbps (10^6) → Gbps (10^9) → Tbps (10^12).</p>` },

    { id:"l16-delay", title:"Delay and its types", difficulty:"medium",
      tags:["Theory","Definition","Exam Likely","Must Revise"],
      content:`
        <p><b>Delay</b> = time for a bit to travel across the network, in seconds.</p>
        <ul>
          <li><b>Propagation delay:</b> time for the signal to travel the medium.</li>
          <li><b>Switching delay:</b> time for a device to forward data.</li>
          <li><b>Access delay:</b> waiting to get control of the medium (why busy WiFi feels slow).</li>
          <li><b>Queuing delay:</b> waiting in a switch's buffer.</li>
          <li><b>Processing delay:</b> time to process a packet.</li>
        </ul>` },

    { id:"l16-bitrate", title:"Required bit-rate numericals", difficulty:"hard",
      tags:["Numerical","Formula","Exam Likely","Practice Needed","High Priority"],
      content:`
        <div class="example"><b>Text download, 100 pages/sec</b> (page = 24 lines × 80 chars, 8 bits/char):<br>
        100 × 24 × 80 × 8 = <b>1,536,000 bps ≈ 1.536 Mbps</b>.</div>
        <div class="example"><b>Digitized voice, 4 kHz, 2 samples/Hz, 8 bits/sample:</b><br>
        2 × 4000 × 8 = <b>64,000 bps = 64 kbps</b>.</div>
        <div class="formula">Mbps = bps / 1,000,000     kbps = bps / 1,000</div>` },

    { id:"l16-metrics", title:"Throughput, packet loss, latency, jitter", difficulty:"hard",
      tags:["Numerical","Formula","Exam Likely","Practice Needed","High Priority","Must Revise"],
      content:`
        <ul>
          <li><b>Latency:</b> time data takes from sender to receiver (ms). If a packet takes 40 ms, latency = 40 ms.</li>
          <li><b>Throughput:</b> useful data actually delivered per second.</li>
          <li><b>Bandwidth</b> = capacity (a bus that can carry 100); <b>throughput</b> = what's actually used (carries 85).</li>
          <li><b>Jitter:</b> variation in packet arrival times. 20,25,18,30 ms → high jitter, bad for calls/streaming.</li>
        </ul>
        <div class="formula">Packet Loss % = (Sent − Received) / Sent × 100
Efficiency % = (Useful Throughput / Bandwidth) × 100
Goodput = Throughput − Overhead − Retransmissions</div>
        <div class="example">Sent 1000, received 980 → loss = 20/1000 = <b>2%</b>.<br>
        Bandwidth 100, throughput 80 → efficiency <b>80%</b>.<br>
        Throughput 900, overhead 50, retransmit 30 → goodput = <b>820 Mbps</b>.</div>` },

    { id:"l16-measure", title:"Measurement tools & failure recovery", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely"],
      content:`
        <table><tr><th>Passive tools</th><th>Active tools</th></tr>
        <tr><td>Watch existing traffic, no extra load</td><td>Inject test packets</td></tr>
        <tr><td>Realistic user view; CPU overhead</td><td>Measure delay/loss/availability; may be blocked by firewalls</td></tr></table>
        <p>Five recovery scenarios: lost packets, induced delay, duplicate packets, out-of-order packets, errored packets.</p>` },

    { id:"l16-trends", title:"Emerging trends, SDN, edge & zero trust", difficulty:"easy",
      tags:["Theory","Definition","Exam Likely"],
      content:`
        <p>Trends: mobile adoption, experiment-driven decisions, business process automation (more cloud dependence).</p>
        <ul>
          <li><b>5G:</b> higher speed, lower delay.</li>
          <li><b>SDN (Software Defined Networking):</b> network control separated from devices into a central, programmable controller.</li>
          <li><b>Edge computing:</b> process data near where it's made (sensor → nearby edge device → only key data to cloud). Benefits: low latency, less bandwidth, real-time decisions (self-driving cars, smart cities, healthcare wearables).</li>
        </ul>
        <p><b>Zero Trust security:</b> never trust by default; verify every request continuously; least-privilege access. Used in banking, government, defense, cloud.</p>` }
  ]
}
];

/* ===================== QUESTION BANK =====================
   Pulled from quizzes, assignments, in-class tasks, and
   likely theory questions. type: theory | numerical
   kind label: MCQ-style not present; we keep Short / Long /
   Numerical / Theory categories. */

const QUESTIONS = [
  // ---- THEORY (Section I, 30%) ----
  { id:"q-t1", cat:"Short Theory", type:"theory", lec:1, difficulty:"easy",
    tags:["Theory","Exam Likely"],
    q:"Differentiate between a network and the Internet.",
    a:`<p><b>Network:</b> a system connecting computers with some transmission technology so they can share data. <b>Internet:</b> many networks joined by routers so any computer on any network can communicate. The Internet is a "network of networks".</p>` },

  { id:"q-t2", cat:"Short Theory", type:"theory", lec:1, difficulty:"easy",
    tags:["Theory","Exam Likely","Must Revise"],
    q:"Explain simplex, half-duplex and full-duplex with one example each.",
    a:`<p><b>Simplex:</b> one direction only (keyboard → computer). <b>Half-duplex:</b> both directions but one at a time (walkie-talkie, WiFi). <b>Full-duplex:</b> both at once (phone call, wired Ethernet).</p>` },

  { id:"q-t3", cat:"Long Theory", type:"theory", lec:2, difficulty:"medium",
    tags:["Theory","Exam Likely"],
    q:"Compare circuit switching, message switching and packet switching.",
    a:`<p><b>Circuit:</b> dedicated path reserved for the whole call (voice/telephone); wastes capacity when idle. <b>Message:</b> whole message stored-and-forwarded at each node, no size limit, slow. <b>Packet:</b> data split into small packets routed node to node, shares the link, fast — used by the Internet (IP).</p>` },

  { id:"q-t4", cat:"Long Theory", type:"theory", lec:8, difficulty:"medium",
    tags:["Theory","High Priority","Exam Likely","Must Revise"],
    q:"List the 7 OSI layers and give the PDU and one job of each.",
    a:`<p>7 Application (Data — user apps), 6 Presentation (Data — encryption/compression), 5 Session (Data — session control), 4 Transport (Segment — ports, reliability), 3 Network (Packet — IP routing), 2 Data Link (Frame — MAC delivery), 1 Physical (Bits — raw signals).</p>` },

  { id:"q-t5", cat:"Short Theory", type:"theory", lec:7, difficulty:"medium",
    tags:["Theory","Exam Likely","Must Revise"],
    q:"Compare Link-State and Distance-Vector routing.",
    a:`<p><b>Link-State:</b> global knowledge, central controller + Dijkstra, protocol OSPF; accurate but single point of failure and high overhead. <b>Distance-Vector:</b> knows only neighbours, iterative exchange, protocol RIP; no single failure point and scales, but slow convergence and count-to-infinity.</p>` },

  { id:"q-t6", cat:"Short Theory", type:"theory", lec:7, difficulty:"easy",
    tags:["Theory","Exam Likely"],
    q:"Why are today's Internet routing algorithms load-insensitive?",
    a:`<p>Load-sensitive routing would need constant traffic measurement and frequent updates (huge overhead), the data is outdated by the time it's shared, and routes would keep flipping (oscillations) making the network unstable — bad for real-time apps.</p>` },

  { id:"q-t7", cat:"Long Theory", type:"theory", lec:12, difficulty:"medium",
    tags:["Theory","Exam Likely","Must Revise"],
    q:"Explain symmetric vs asymmetric encryption and what hybrid encryption is.",
    a:`<p><b>Symmetric (AES):</b> one shared secret key, fast, for bulk data. <b>Asymmetric (RSA):</b> public key encrypts, private key decrypts, used for key exchange. <b>Hybrid (HTTPS):</b> RSA safely shares a session key, then AES encrypts the actual data — secure and fast.</p>` },

  { id:"q-t8", cat:"Short Theory", type:"theory", lec:13, difficulty:"medium",
    tags:["Theory","Exam Likely"],
    q:"Why is a hash function called one-way, and how does it ensure integrity?",
    a:`<p>It's easy to compute the hash from the input but practically impossible to reverse it. If the hash of the received data equals the hash of the sent data, the data was not changed — so integrity is verified.</p>` },

  { id:"q-t9", cat:"Short Theory", type:"theory", lec:13, difficulty:"medium",
    tags:["Theory","Exam Likely","Must Revise"],
    q:"What is non-repudiation and why does a MAC not provide it but a digital signature does?",
    a:`<p>Non-repudiation means the signer cannot later deny signing. A MAC uses a shared key, so either party could have made it — no proof of who. A digital signature uses the sender's private key (only they have it), so it proves the sender and can't be denied.</p>` },

  { id:"q-t10", cat:"Long Theory", type:"theory", lec:15, difficulty:"easy",
    tags:["Theory","Exam Likely"],
    q:"Describe public, private and hybrid clouds with one example each.",
    a:`<p><b>Public:</b> open to all over the Internet, scalable, less control (universities). <b>Private:</b> one organization, isolated, limited scale (banks). <b>Hybrid:</b> mixes both — sensitive data private, flexible workloads public.</p>` },

  { id:"q-t11", cat:"Short Theory", type:"theory", lec:16, difficulty:"medium",
    tags:["Theory","Exam Likely","Must Revise"],
    q:"Differentiate bandwidth, throughput and goodput.",
    a:`<p><b>Bandwidth:</b> maximum capacity of the link. <b>Throughput:</b> data actually delivered per second. <b>Goodput (useful throughput):</b> throughput minus overhead and retransmissions — the real user data.</p>` },

  { id:"q-t12", cat:"Short Theory", type:"theory", lec:6, difficulty:"medium",
    tags:["Theory","Exam Likely","Must Revise"],
    q:"Differentiate forwarding and routing.",
    a:`<p><b>Forwarding:</b> the local, fast (nanoseconds) step of moving a packet from an input to the right output link, usually in hardware. <b>Routing:</b> the network-wide process of deciding end-to-end paths, usually in software.</p>` },

  // ---- NUMERICAL (Section II, 70%) ----
  { id:"q-n1", cat:"Numerical", type:"numerical", lec:3, difficulty:"medium",
    tags:["Numerical","Exam Likely","Practice Needed"],
    q:"Given IP 150.1.2.3: find class, default mask, usable hosts. Is it efficient for 600 hosts?",
    a:`<p>150 is in 128–191 → <b>Class B</b>, mask <b>255.255.0.0</b>, hosts = 65,536 − 2 = <b>65,534</b>. <b>Not efficient</b> for 600 hosts — 65K available means about 65,000 addresses wasted.</p>` },

  { id:"q-n2", cat:"Numerical", type:"numerical", lec:5, difficulty:"hard",
    tags:["Numerical","High Priority","Exam Likely","Practice Needed","Must Revise"],
    q:"Divide 192.168.40.0/24 into at least 5 equal subnets, each ≥ 25 hosts. Find the mask and first 5 subnets.",
    a:`<p>Need ≥5 subnets → borrow <b>3 bits</b> (2³ = 8 ≥ 5). New prefix <b>/27</b>, mask <b>255.255.255.224</b>. Host bits = 5 → usable 30 (which is ≥ 25, correct). Block size 32.</p>
    <table><tr><th>Subnet</th><th>Network</th><th>First</th><th>Last</th><th>Broadcast</th></tr>
    <tr><td>1</td><td>.0</td><td>.1</td><td>.30</td><td>.31</td></tr>
    <tr><td>2</td><td>.32</td><td>.33</td><td>.62</td><td>.63</td></tr>
    <tr><td>3</td><td>.64</td><td>.65</td><td>.94</td><td>.95</td></tr>
    <tr><td>4</td><td>.96</td><td>.97</td><td>.126</td><td>.127</td></tr>
    <tr><td>5</td><td>.128</td><td>.129</td><td>.158</td><td>.159</td></tr></table>
    <p><b>Inefficiency:</b> only 5 needed but 8 created → 3 wasted.</p>` },

  { id:"q-n3", cat:"Numerical", type:"numerical", lec:5, difficulty:"hard",
    tags:["Numerical","High Priority","Exam Likely","Practice Needed"],
    q:"A company has 5 departments on 192.168.6.0/24; each needs ≥ 50 hosts. Find the mask and subnets. Does it work for a 6th?",
    a:`<p>Need ≥50 hosts → 6 host bits (2⁶−2 = 62). Borrow <b>2 bits</b> → /26, mask <b>255.255.255.192</b>, <b>4 subnets</b> of 62 hosts, block size 64.</p>
    <table><tr><th>Subnet</th><th>Network</th><th>First</th><th>Last</th><th>Broadcast</th></tr>
    <tr><td>1</td><td>.0</td><td>.1</td><td>.62</td><td>.63</td></tr>
    <tr><td>2</td><td>.64</td><td>.65</td><td>.126</td><td>.127</td></tr>
    <tr><td>3</td><td>.128</td><td>.129</td><td>.190</td><td>.191</td></tr>
    <tr><td>4</td><td>.192</td><td>.193</td><td>.254</td><td>.255</td></tr></table>
    <p>A <b>5th/6th department won't fit</b>: only 4 subnets exist. Borrowing a 3rd bit (/27) drops hosts to 30, failing the 50-host requirement.</p>` },

  { id:"q-n4", cat:"Numerical", type:"numerical", lec:5, difficulty:"medium",
    tags:["Numerical","Exam Likely","Practice Needed"],
    q:"A student split 192.168.60.0/24 into /26 (4 subnets) for a 'at least 5 subnets, ≥25 hosts' task. Find the mistake and correct it.",
    a:`<p><b>Mistake:</b> /26 gives only 4 subnets, but ≥5 are required (4 < 5). Hosts (62) were fine, but the subnet count is wrong.</p>
    <p><b>Correct:</b> borrow 3 bits → /27, mask <b>255.255.255.224</b>, 8 subnets, 30 usable hosts each (≥ 25, correct), block size 32.</p>` },

  { id:"q-n5", cat:"Numerical", type:"numerical", lec:10, difficulty:"hard",
    tags:["Numerical","High Priority","Exam Likely","Practice Needed","Must Revise"],
    q:"Compute the 1's complement checksum for 16-bit words: 7A2C 91F5 3E10 8B77 6D3A. Then a received word 8B77→8D77: is the error detected?",
    a:`<p>Add the five 16-bit words with carry wrap, then take the 1's complement → checksum <b>BD1B</b>. Transmitted: 7A2C 91F5 3E10 8B77 6D3A BD1B.</p>
    <p>At the receiver, 8B77 became <b>8D77</b> (a 1-bit change). This changes the sum, so the final check is non-zero → <b>error detected</b>. The checksum catches even a subtle single-bit change.</p>` },

  { id:"q-n6", cat:"Numerical", type:"numerical", lec:10, difficulty:"hard",
    tags:["Numerical","Exam Likely","Practice Needed"],
    q:"Words FFFF 8001 7FFE 0001 — a student says checksum = FFFF. Is that right? Justify.",
    a:`<p><b>No.</b> The student ignored the carry wraparound. The correct checksum is <b>FFFE</b>. Getting "FFFF" isn't automatically correct — all-1s (FFFF) is the expected result of <b>verification at the receiver</b> after wrapping carries, not necessarily the checksum value itself.</p>` },

  { id:"q-n7", cat:"Numerical", type:"numerical", lec:12, difficulty:"hard",
    tags:["Numerical","High Priority","Exam Likely","Practice Needed","Must Revise"],
    q:"CRC: D(x)=x⁹+x⁸+x⁶+x⁴+x³+x+1, generator G(x)=x⁴+x+1. The last CRC bit gets flipped in transit. Find the CRC, frames, and comment.",
    a:`<p>Binary: D = <code>1101011011</code>, G = <code>10011</code> (L=5). Append L−1 = 4 zeros, XOR-divide → CRC remainder. Build the transmitted frame (data + CRC). Flip the last CRC bit for the received frame, then XOR-divide by G at the receiver.</p>
    <p><b>Comment:</b> because a bit was flipped, the receiver's remainder is non-zero → the <b>error is detected</b>. CRC reliably catches single-bit errors.</p>` },

  { id:"q-n8", cat:"Numerical", type:"numerical", lec:12, difficulty:"medium",
    tags:["Numerical","Exam Likely","Practice Needed"],
    q:"Encrypt 'HELLO' using a Caesar cipher with shift +3, and decrypt 'PHHW PH' with shift −3.",
    a:`<p>HELLO +3 → <b>KHOOR</b>. PHHW PH −3 → <b>MEET ME</b>.</p>` },

  { id:"q-n9", cat:"Numerical", type:"numerical", lec:12, difficulty:"hard",
    tags:["Numerical","Exam Likely","Practice Needed","Must Revise"],
    q:"Encrypt 'HELLO WORLD' with the Vigenère cipher using key 'KEY'.",
    a:`<p>Key values K=10,E=4,Y=24 repeated. Cipher = (Plain + Key) mod 26 per letter → <b>RIJVS UYVJN</b>.</p>` },

  { id:"q-n10", cat:"Numerical", type:"numerical", lec:13, difficulty:"hard",
    tags:["Numerical","High Priority","Exam Likely","Practice Needed"],
    q:"Apply 2-D even parity to four 8-bit words. Two bits flip (row2 col5, row3 col6). Apply checking at the receiver and list possible error positions.",
    a:`<p>Add a row-parity bit to each word (make 1s even), then a column-parity row. Transmit the 9-bit words. After the two flips, recheck: the failing rows are 2 and 3, and the failing columns are 5 and 6. With <b>two errors</b>, 2-D parity detects that errors exist but the intersections give <b>four possible positions</b> (r2c5, r2c6, r3c5, r3c6) — it cannot pinpoint/correct them. Single-bit errors it can correct; two-bit errors it can only flag.</p>` },

  { id:"q-n11", cat:"Numerical", type:"numerical", lec:11, difficulty:"medium",
    tags:["Numerical","Exam Likely","Practice Needed"],
    q:"16-bit data D596, even parity at the LSB. Find the parity bit and the transmitted 17-bit word.",
    a:`<p>D596 → 1101 0101 1001 0110 → nine 1s (odd) → parity bit = <b>1</b> (to make it even). Transmitted: <b>1101 0101 1001 0110 1</b>.</p>` },

  { id:"q-n12", cat:"Numerical", type:"numerical", lec:16, difficulty:"medium",
    tags:["Numerical","Exam Likely","Practice Needed","Must Revise"],
    q:"Bandwidth 200 Mbps, throughput 160 Mbps. Sent 1000 packets, 980 received. Find efficiency and packet loss.",
    a:`<p>Efficiency = 160/200 × 100 = <b>80%</b>. Packet loss = (1000−980)/1000 × 100 = <b>2%</b>.</p>` },

  { id:"q-n13", cat:"Numerical", type:"numerical", lec:16, difficulty:"medium",
    tags:["Numerical","Exam Likely","Practice Needed"],
    q:"A digitized voice channel: 4 kHz, 2 samples/Hz, 8 bits/sample. Find the bit rate.",
    a:`<p>2 × 4000 × 8 = <b>64,000 bps = 64 kbps</b>.</p>` },

  { id:"q-n14", cat:"Numerical", type:"numerical", lec:6, difficulty:"hard",
    tags:["Numerical","High Priority","Exam Likely","Practice Needed","Must Revise"],
    q:"Using Distance-Vector (Bellman-Ford), update Node A given A–B=1, A–C=5, B–C=3, B–E=9, C–D=4, D–E=2.",
    a:`<p>To D: min(1+∞, 5+4) = 9 via C. To E: min(1+9, 5+∞) = 10 via B. Updated A: A=0, B=1, C=5, D=9 (via C), E=10 (via B).</p>` },

  { id:"q-n15", cat:"Numerical", type:"numerical", lec:4, difficulty:"easy",
    tags:["Numerical","Exam Likely","Practice Needed"],
    q:"Find the network address for 172.16.200.15 with mask 255.255.0.0.",
    a:`<p>Mask keeps the first two octets, zeroes the rest → network address <b>172.16.0.0</b>.</p>` },

  { id:"q-n16", cat:"Numerical", type:"numerical", lec:5, difficulty:"hard",
    tags:["Numerical","Exam Likely","Practice Needed"],
    q:"For 192.168.20.77/27 find network address, broadcast, host range and host count.",
    a:`<p>/27 → mask 255.255.255.224, block 32. 77 is in the .64–.95 block. Network <b>192.168.20.64</b>, broadcast <b>192.168.20.95</b>, hosts <b>.65–.94</b>, count 2⁵−2 = <b>30</b>.</p>` }
];

/* ===================== GLOSSARY ===================== */
const GLOSSARY = [
  { term:"Protocol", meaning:"An agreed set of rules for communication.", why:"Both devices must run the <b>same</b> protocol or they can't understand each other." },
  { term:"Packet", meaning:"A small chunk of data sent over the network.", why:"Large messages are split into packets so links can be shared efficiently." },
  { term:"Host / End system", meaning:"A device at the edge that runs apps (PC, phone).", why:"Hosts are the senders and receivers; routers just move data between them." },
  { term:"Router", meaning:"A device that connects different networks and forwards packets.", why:"Routers read the destination IP and pick the next hop toward it." },
  { term:"Switch", meaning:"A device that connects devices inside one LAN.", why:"It reads frames and delivers them using MAC addresses." },
  { term:"Bandwidth", meaning:"The maximum data a link can carry (capacity).", why:"It sets the ceiling; real speed (throughput) is usually a bit lower." },
  { term:"Throughput", meaning:"The data actually delivered per second.", why:"Shows real performance, always ≤ bandwidth." },
  { term:"Goodput", meaning:"Useful data only = throughput − overhead − retransmissions.", why:"It's what the user really receives, e.g. video quality depends on it." },
  { term:"Latency", meaning:"Time for data to travel sender → receiver (ms).", why:"Low latency matters for calls and gaming." },
  { term:"Jitter", meaning:"Variation in packet arrival times.", why:"High jitter breaks voice and video smoothness." },
  { term:"IP address", meaning:"A 32-bit ID for a device on an IP network.", why:"Network part + host part route data to the right device." },
  { term:"Subnet mask", meaning:"A pattern that marks which bits are network vs host (1=network, 0=host).", why:"Used with bitwise AND to find the network address." },
  { term:"CIDR", meaning:"Classless addressing written as /m (number of mask 1-bits).", why:"Lets us make custom-sized networks and reduce address waste." },
  { term:"Subnetting", meaning:"Borrowing host bits to split a network into smaller subnets.", why:"Saves addresses and reduces router complexity." },
  { term:"Block size", meaning:"256 minus the mask's last non-255 octet.", why:"Tells you the step between subnet network addresses." },
  { term:"Broadcast address (DBA)", meaning:"The last address of a subnet (all host bits = 1).", why:"Used to reach every device on that subnet at once." },
  { term:"DHCP", meaning:"Protocol that auto-assigns IP, mask and gateway.", why:"Makes networks plug-and-play and prevents IP conflicts (DORA process)." },
  { term:"NAT", meaning:"Network Address Translation — maps private IPs to one public IP.", why:"Lets many devices share one public address and hides internal IPs." },
  { term:"Forwarding", meaning:"The local, fast step of moving a packet to the right output link.", why:"Happens in hardware in nanoseconds." },
  { term:"Routing", meaning:"The network-wide process of choosing end-to-end paths.", why:"Decides the route before forwarding carries it out." },
  { term:"Forwarding table", meaning:"A router's map of 'to reach X, use link Y'.", why:"Indexed by header values to choose the output interface." },
  { term:"Default route", meaning:"A single low-priority entry (*) for all unlisted destinations.", why:"Removes many duplicate table entries for a switch with one link." },
  { term:"Least-cost path", meaning:"The path with the smallest total edge cost.", why:"The main goal of any routing algorithm." },
  { term:"Link-State (OSPF)", meaning:"Routing with full network knowledge using Dijkstra.", why:"Accurate but heavier; works within one Autonomous System." },
  { term:"Distance-Vector (RIP)", meaning:"Routing using only neighbour info and Bellman-Ford.", why:"Simple and scalable but converges slowly." },
  { term:"Count-to-infinity", meaning:"Routers keep raising hop counts to a dead destination.", why:"A weakness of distance-vector routing causing loops." },
  { term:"Autonomous System (AS)", meaning:"A network under one administration.", why:"OSPF routes within an AS; BGP routes between them." },
  { term:"OSI model", meaning:"A 7-layer reference model for networking (ISO, 1978).", why:"Breaks communication into manageable, interoperable layers." },
  { term:"Encapsulation", meaning:"Each layer wrapping data in its own header/trailer.", why:"Builds segment → packet → frame → bits as data goes down the stack." },
  { term:"PDU", meaning:"Protocol Data Unit — the data name at each layer.", why:"Segment (4), Packet (3), Frame (2), Bits (1)." },
  { term:"MAC address", meaning:"A hardware ID used for delivery inside a LAN.", why:"IP finds the network; MAC finds the exact device." },
  { term:"Port number", meaning:"A 16-bit ID for an app/service on a device.", why:"IP reaches the device; the port reaches the right program." },
  { term:"TCP", meaning:"Reliable, connection-oriented transport (3-way handshake).", why:"Used where correctness matters: web, email, downloads." },
  { term:"UDP", meaning:"Fast, connectionless transport with no guarantees.", why:"Used for streaming, gaming and calls where speed beats reliability." },
  { term:"3-way handshake", meaning:"SYN, SYN-ACK, ACK to start a TCP connection.", why:"Sets up a reliable session before data flows." },
  { term:"Checksum", meaning:"A small value used to detect data errors.", why:"Receiver recomputes and compares; it detects but can't correct." },
  { term:"1's complement", meaning:"Flip every bit (0↔1).", why:"Used to build and verify checksums; verification gives all 1s / zero." },
  { term:"Carry wraparound", meaning:"Adding the overflow carry back into the low bits.", why:"Required for a correct fixed-width checksum sum." },
  { term:"Parity bit", meaning:"An extra bit making the number of 1s even or odd.", why:"Simplest error detection; catches odd numbers of flips only." },
  { term:"2-D parity", meaning:"Parity on both rows and columns.", why:"Can detect and correct a single-bit error at the intersection." },
  { term:"CRC", meaning:"Error check using XOR polynomial division.", why:"Strong burst-error detection used in Ethernet." },
  { term:"XOR", meaning:"Logic op: same bits → 0, different → 1.", why:"Used in CRC instead of subtraction — no borrows, fast in hardware." },
  { term:"FEC", meaning:"Forward Error Correction — extra bits fix errors.", why:"Receiver corrects without asking for a resend." },
  { term:"ARQ", meaning:"Automatic Repeat reQuest — resend bad data.", why:"Sender and receiver cooperate to guarantee delivery." },
  { term:"Confidentiality", meaning:"Only sender and receiver understand the message.", why:"Achieved by encryption; a core security goal." },
  { term:"Integrity", meaning:"Data isn't altered in transit.", why:"Checked with checksums or hashes." },
  { term:"Authentication", meaning:"Confirming who the other party is.", why:"Stops impersonation in communication." },
  { term:"Symmetric key (AES)", meaning:"One shared secret key for both sides.", why:"Fast for large data once a key is shared." },
  { term:"Asymmetric key (RSA)", meaning:"Public key encrypts, private key decrypts.", why:"Solves the problem of sharing keys securely." },
  { term:"Hybrid encryption", meaning:"RSA exchanges a key, AES encrypts the data.", why:"Combines secure key exchange with fast bulk encryption (HTTPS)." },
  { term:"Caesar cipher", meaning:"Shift each letter by k.", why:"Teaching example; only 25 keys, easily broken." },
  { term:"Monoalphabetic cipher", meaning:"Each letter maps to one fixed random letter.", why:"26! keys — far stronger than Caesar." },
  { term:"Vigenère cipher", meaning:"Keyword gives a different shift per letter.", why:"Stronger historically, but broken by frequency analysis." },
  { term:"Hash function", meaning:"Maps any input to a fixed-size fingerprint.", why:"One-way; used to verify integrity and store passwords." },
  { term:"Digital signature", meaning:"A hash signed with the sender's private key.", why:"Provides authentication, integrity and non-repudiation." },
  { term:"Non-repudiation", meaning:"The signer can't deny signing.", why:"Important for banking and contracts." },
  { term:"Replay attack", meaning:"Re-sending captured valid data to gain access.", why:"Why auth messages must not be reusable." },
  { term:"Firewall", meaning:"Filters packets between a network and the Internet.", why:"Blocks unwanted or malicious traffic." },
  { term:"IDS", meaning:"Intrusion Detection System that alerts on suspicious activity.", why:"Helps admins react to attacks quickly." },
  { term:"Cloud computing", meaning:"Computing services delivered over the Internet, pay-per-use.", why:"No upfront hardware; scalable on demand (elastic)." },
  { term:"Elastic computing", meaning:"Getting more/less resources on demand.", why:"Handles variable workloads cost-effectively." },
  { term:"IaaS / PaaS / SaaS", meaning:"Infrastructure / Platform / Software as a Service.", why:"Different levels of cloud service: VMs, build platforms, ready apps." },
  { term:"Shared responsibility model", meaning:"Provider secures the cloud; customer secures data in it.", why:"Defines who handles which security task in public cloud." },
  { term:"SDN", meaning:"Software Defined Networking — control split into a central controller.", why:"Makes networks programmable and flexible." },
  { term:"Edge computing", meaning:"Processing data near where it's created.", why:"Lowers latency and bandwidth for real-time use (cars, IoT)." },
  { term:"Zero Trust", meaning:"Never trust by default; verify every request.", why:"Strong security model with least-privilege access." },
  { term:"Bellman-Ford", meaning:"Equation distance-vector routing uses to find least cost.", why:"Each node updates costs from neighbour vectors." },
  { term:"Store-and-forward", meaning:"Fully receive a packet, then send it on.", why:"Lets many computers share links; checksum verified before forwarding." }
];
