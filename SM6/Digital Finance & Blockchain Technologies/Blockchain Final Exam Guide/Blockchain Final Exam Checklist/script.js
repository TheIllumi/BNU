/* ============================================================
   Blockchain Final Exam Study Tracker - logic
   Pure vanilla JS. Progress saved in localStorage. Offline.
   ============================================================ */

"use strict";

/* ---------- Tag helpers ---------- */
const TAG = {
  high:    { label: "High Priority",     cls: "tag-high" },
  revise:  { label: "Must Revise",       cls: "tag-revise" },
  likely:  { label: "Final Exam Likely", cls: "tag-likely" },
  calc:    { label: "Calculation",       cls: "tag-calc" },
  diagram: { label: "Diagram",           cls: "tag-diagram" },
  mcq:     { label: "MCQ",               cls: "tag-mcq" },
  theory:  { label: "Theory",            cls: "tag-theory" },
  short:   { label: "Short Q",           cls: "tag-short" },
  long:    { label: "Long Q",            cls: "tag-long" }
};
// tags that keep an item visible in Revision Mode
const REVISION_TAGS = ["high", "revise", "likely", "calc", "diagram"];

/* shorthand to build a checklist topic item */
function topic(title, tags) { return { kind: "check", title, tags: tags || [] }; }
/* shorthand to build a question bank (grid of N numbered chips) */
function bank(title, count, tags) { return { kind: "bank", title, count, tags: tags || [] }; }

/* ============================================================
   STUDY DATA  (generated from the uploaded guide, faithful counts)
   ============================================================ */
const studyData = [
  {
    id: "s1", title: "How to Use & Study Plan",
    items: [
      topic("Read: how to use this guide (one-day plan)", ["theory"]),
      topic("Tonight study plan", ["revise"]),
      topic("Tomorrow morning plan", ["revise"]),
      topic("Final notes & exam strategy", ["theory"])
    ]
  },
  {
    id: "s2", title: "Blockchain Core Concepts",
    items: [
      topic("Blockchain (definition & properties)", ["high", "theory", "likely"]),
      topic("Cryptographic hashing (SHA-256)", ["high", "theory", "likely"]),
      topic("Hashing vs encryption (Quiz Q4)", ["high", "theory", "likely"]),
      topic("Digital signatures (auth, non-repudiation, integrity)", ["high", "theory", "likely"]),
      topic("Public & private keys", ["theory"]),
      topic("Decentralisation & distributed ledger", ["theory"]),
      topic("Consensus: PoW vs PoS", ["high", "theory", "likely"]),
      topic("Immutability & transparency", ["theory"]),
      topic("Mining", ["theory"]),
      topic("Nodes & P2P network", ["theory"]),
      topic("Cryptocurrency overview", ["theory"]),
      topic("NFTs", ["theory"])
    ]
  },
  {
    id: "s3", title: "Bitcoin Block & Transaction Structure",
    items: [
      topic("Block structure (80-byte header)", ["high", "diagram", "likely"]),
      topic("Block header fields (version, prevHash, Merkle root, timestamp, nBits, nonce)", ["high", "theory"]),
      topic("Transaction chain", ["high", "diagram", "likely"]),
      topic("Transaction data format (inputs/outputs, txID)", ["high", "theory"]),
      topic("Coinbase transaction", ["theory", "likely"]),
      topic("Merkle tree & Merkle root", ["high", "diagram", "likely"])
    ]
  },
  {
    id: "s4", title: "Bitcoin Mechanics",
    items: [
      topic("UTxO & STxO", ["high", "theory", "likely"]),
      topic("Locking & unlocking scripts (P2PKH)", ["high", "theory"]),
      topic("Proof of Work (PoW)", ["high", "theory", "likely"]),
      topic("Double spending", ["high", "theory", "likely"]),
      topic("Longest chain & forks", ["theory"]),
      topic("51% attack", ["theory"]),
      topic("Reward halving", ["theory"]),
      topic("Wallets (deterministic vs nondeterministic)", ["theory"]),
      topic("Soft fork vs hard fork", ["theory"])
    ]
  },
  {
    id: "s5", title: "Diagrams to Practice",
    items: [
      topic("Blockchain structure (chain of blocks)", ["diagram"]),
      topic("Block structure", ["high", "diagram", "likely"]),
      topic("Merkle tree", ["high", "diagram", "likely"]),
      topic("Bitcoin transaction chain", ["high", "diagram", "likely"]),
      topic("UTxO model", ["high", "diagram"]),
      topic("Locking / unlocking script flow", ["high", "diagram"]),
      topic("Proof of Work mining flow", ["high", "diagram", "likely"]),
      topic("Ethereum smart contract deployment flow", ["high", "diagram", "likely"])
    ]
  },
  {
    id: "s6", title: "Calculations (Part 3 topics)",
    items: [
      topic("Target from nBits (mantissa & exponent)", ["high", "calc", "likely"]),
      topic("Convert nBits to full hex target", ["high", "calc"]),
      topic("Compare two targets / difficulties", ["high", "calc"]),
      topic("Difficulty calculation", ["high", "calc", "likely"]),
      topic("Leading zeros from a target", ["high", "calc", "likely"]),
      topic("Number of computations (n = log2(600P))", ["high", "calc", "likely"]),
      topic("Hash rate from difficulty", ["calc"]),
      topic("Bytecode computations (stack arithmetic)", ["high", "calc", "likely"])
    ]
  },
  {
    id: "s7", title: "Ethereum Basics",
    items: [
      topic("Ethereum (world computer, state machine)", ["high", "theory", "likely"]),
      topic("Bitcoin vs Ethereum", ["high", "theory", "likely"]),
      topic("Ether units (wei to Ether)", ["theory"]),
      topic("Account types: EOA vs contract", ["high", "theory", "likely"]),
      topic("Transactions vs messages", ["theory", "likely"]),
      topic("Gas, gas price, gas limit", ["high", "theory", "likely"]),
      topic("ABI, bytecode, EVM", ["high", "theory"]),
      topic("Wallet connection & MetaMask", ["theory"])
    ]
  },
  {
    id: "s8", title: "Smart Contracts, Remix & Deployment",
    items: [
      topic("Smart contracts (vending machine analogy)", ["high", "theory", "likely"]),
      topic("Solidity", ["theory"]),
      topic("Remix IDE", ["theory"]),
      topic("Contract creation, compilation, deployment", ["high", "theory", "likely"]),
      topic("Test networks & Sepolia", ["theory"]),
      topic("Faucets", ["theory"]),
      topic("Practical workflow (7 steps)", ["high", "revise"])
    ]
  },
  {
    id: "s9", title: "Bytecode Understanding (Week 11)",
    items: [
      topic("What bytecode is", ["high", "theory", "likely"]),
      topic("Why Solidity becomes bytecode", ["theory"]),
      topic("Role of the EVM", ["theory"]),
      topic("Source code vs ABI vs bytecode", ["theory"]),
      topic("Disassembling bytecode", ["high", "calc", "likely"]),
      topic("Stack, memory, storage, call stack", ["high", "theory"]),
      topic("Contract creation vs invocation (to:none vs to:address)", ["high", "theory", "likely"]),
      topic("Hand-assembled contract example", ["calc"]),
      topic("What bytecode questions can come", ["revise"])
    ]
  },
  {
    id: "s10", title: "MCQ Bank",
    items: [
      bank("Easy MCQs", 60, ["mcq"]),
      bank("Medium MCQs", 60, ["mcq"]),
      bank("Hard MCQs", 50, ["mcq"]),
      bank("Tricky / Conceptual MCQs", 40, ["mcq", "high"])
    ]
  },
  {
    id: "s11", title: "Short Questions",
    items: [
      bank("Easy short questions", 50, ["short"]),
      bank("Medium short questions", 50, ["short"]),
      bank("Hard short questions", 40, ["short"]),
      bank("Very important exam questions", 30, ["short", "high", "likely"])
    ]
  },
  {
    id: "s12", title: "Long Questions",
    items: [ bank("Long theoretical questions", 25, ["long", "high"]) ]
  },
  {
    id: "s13", title: "Diagram-Based Questions",
    items: [ bank("Diagram-based questions", 20, ["diagram", "high", "likely"]) ]
  },
  {
    id: "s14", title: "Calculation Practice",
    items: [
      bank("Easy calculations", 10, ["calc"]),
      bank("Medium calculations", 15, ["calc", "high"]),
      bank("Hard calculations", 15, ["calc", "high", "likely"]),
      bank("Exam-level mixed", 5, ["calc", "high", "likely"])
    ]
  },
  {
    id: "s15", title: "Last-Minute Revision",
    items: [
      topic("Key definitions", ["revise", "theory"]),
      topic("Key formulas", ["revise", "calc", "high"]),
      topic("Must-remember diagrams", ["revise", "diagram", "high"]),
      topic("Important differences", ["revise", "theory"]),
      topic("Common MCQ traps", ["revise", "mcq", "high"]),
      topic("Most repeated concepts (high yield)", ["revise", "high", "likely"]),
      topic("Final exam prediction", ["revise", "likely"])
    ]
  }
];

/* ---------- Assign stable IDs ---------- */
studyData.forEach((sec) => {
  sec.items.forEach((it, i) => {
    it.id = sec.id + "_" + i;
    if (it.kind === "bank") {
      it.unitIds = [];
      for (let n = 1; n <= it.count; n++) it.unitIds.push(it.id + "#" + n);
    }
  });
});

/* ============================================================
   STATE + STORAGE
   ============================================================ */
const STORE_KEY = "btc_study_tracker_v1";
const state = {
  done: {},          // { unitId: true }
  notes: "",
  theme: "dark",
  open: {},          // { sectionId: false }  (true = collapsed)
  filter: "all",
  search: "",
  revision: false
};

function load() {
  try {
    const raw = localStorage.getItem(STORE_KEY);
    if (raw) {
      const saved = JSON.parse(raw);
      Object.assign(state, saved);
      state.done = saved.done || {};
      state.open = saved.open || {};
    }
  } catch (e) { /* ignore corrupt storage */ }
}
let saveTimer = null;
function save() {
  clearTimeout(saveTimer);
  saveTimer = setTimeout(() => {
    try {
      localStorage.setItem(STORE_KEY, JSON.stringify({
        done: state.done, notes: state.notes, theme: state.theme, open: state.open
      }));
    } catch (e) { /* storage may be full/blocked */ }
  }, 120);
}

/* ---------- Unit helpers ---------- */
function allUnits() {
  const ids = [];
  studyData.forEach((sec) => sec.items.forEach((it) => {
    if (it.kind === "bank") it.unitIds.forEach((u) => ids.push(u));
    else ids.push(it.id);
  }));
  return ids;
}
function itemUnits(it) { return it.kind === "bank" ? it.unitIds : [it.id]; }
function itemDoneCount(it) { return itemUnits(it).filter((u) => state.done[u]).length; }
function itemTotal(it) { return it.kind === "bank" ? it.count : 1; }
function itemComplete(it) { return itemDoneCount(it) === itemTotal(it); }
function sectionDone(sec) { return sec.items.reduce((a, it) => a + itemDoneCount(it), 0); }
function sectionTotal(sec) { return sec.items.reduce((a, it) => a + itemTotal(it), 0); }

/* ============================================================
   RENDERING
   ============================================================ */
const el = (sel) => document.querySelector(sel);
const elAll = (sel) => Array.from(document.querySelectorAll(sel));

const CHECK_SVG = '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="3.5" stroke-linecap="round" stroke-linejoin="round"><polyline points="20 6 9 17 4 12"></polyline></svg>';
const CHEVRON_SVG = '<svg class="sec-chevron" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><polyline points="6 9 12 15 18 9"></polyline></svg>';

function tagPills(tags) {
  if (!tags || !tags.length) return "";
  return '<div class="item-tags">' + tags.map((t) => {
    const def = TAG[t]; if (!def) return "";
    return '<span class="tag ' + def.cls + '">' + def.label + "</span>";
  }).join("") + "</div>";
}

function buildSidebar() {
  const list = el("#navList");
  list.innerHTML = studyData.map((sec, i) =>
    '<button class="nav-item" data-jump="' + sec.id + '">' +
      '<span class="nav-dot"></span>' +
      '<span class="nav-label">' + (i + 1) + ". " + sec.title + "</span>" +
      '<span class="nav-count mono" id="navcount_' + sec.id + '"></span>' +
    "</button>"
  ).join("");
  list.querySelectorAll("[data-jump]").forEach((b) => {
    b.addEventListener("click", () => {
      const sec = el("#sec_" + b.dataset.jump);
      sec.classList.remove("collapsed");
      state.open[b.dataset.jump] = false; save();
      sec.querySelector(".sec-chevron").style.transform = "";
      sec.scrollIntoView({ behavior: "smooth", block: "start" });
      closeSidebar();
    });
  });
}

function buildSections() {
  const main = el("#sections");
  main.innerHTML = studyData.map((sec, i) => {
    const collapsed = state.open[sec.id] ? "collapsed" : "";
    const body = sec.items.map((it) => it.kind === "bank" ? renderBank(it) : renderCheck(it)).join("");
    return (
      '<section class="section ' + collapsed + '" id="sec_' + sec.id + '" data-sec="' + sec.id + '">' +
        '<div class="section-head" data-toggle="' + sec.id + '">' +
          CHEVRON_SVG +
          '<div class="sec-title-wrap">' +
            '<div class="sec-title"><span class="sec-index">' + String(i + 1).padStart(2, "0") + "</span>" + sec.title + "</div>" +
            '<div class="sec-meta" id="secmeta_' + sec.id + '"></div>' +
          "</div>" +
          '<div class="sec-progress">' +
            ringSvg(sec.id) +
            '<div class="sec-actions">' +
              '<button class="btn btn-sm ghost" data-markall="' + sec.id + '">Mark all</button>' +
              '<button class="btn btn-sm ghost" data-reset="' + sec.id + '">Reset</button>' +
            "</div>" +
          "</div>" +
        "</div>" +
        '<div class="section-body">' + body + "</div>" +
      "</section>"
    );
  }).join("");

  // wire section interactions
  elAll("[data-toggle]").forEach((h) => h.addEventListener("click", (e) => {
    if (e.target.closest("button[data-markall], button[data-reset]")) return;
    const id = h.dataset.toggle;
    const sec = el("#sec_" + id);
    sec.classList.toggle("collapsed");
    state.open[id] = sec.classList.contains("collapsed");
    save();
  }));
  elAll("[data-markall]").forEach((b) => b.addEventListener("click", (e) => {
    e.stopPropagation();
    const sec = studyData.find((s) => s.id === b.dataset.markall);
    sec.items.forEach((it) => itemUnits(it).forEach((u) => { state.done[u] = true; }));
    save(); refresh(); toast("Marked all done: " + sec.title);
  }));
  elAll("[data-reset]").forEach((b) => b.addEventListener("click", (e) => {
    e.stopPropagation();
    const sec = studyData.find((s) => s.id === b.dataset.reset);
    sec.items.forEach((it) => itemUnits(it).forEach((u) => { delete state.done[u]; }));
    save(); refresh(); toast("Reset section: " + sec.title);
  }));

  // wire checkboxes
  elAll(".item .check").forEach((c) => c.addEventListener("click", () => {
    const id = c.closest(".item").dataset.id;
    if (state.done[id]) delete state.done[id]; else state.done[id] = true;
    save(); refresh();
  }));
  // wire question chips
  elAll(".qchip").forEach((c) => c.addEventListener("click", () => {
    const u = c.dataset.unit;
    if (state.done[u]) delete state.done[u]; else state.done[u] = true;
    save(); refresh();
  }));
  // wire bank mark/reset
  elAll("[data-bankall]").forEach((b) => b.addEventListener("click", () => {
    const it = findItem(b.dataset.bankall);
    it.unitIds.forEach((u) => { state.done[u] = true; }); save(); refresh();
  }));
  elAll("[data-bankreset]").forEach((b) => b.addEventListener("click", () => {
    const it = findItem(b.dataset.bankreset);
    it.unitIds.forEach((u) => { delete state.done[u]; }); save(); refresh();
  }));
}

function findItem(id) {
  for (const sec of studyData) for (const it of sec.items) if (it.id === id) return it;
  return null;
}

function ringSvg(secId) {
  const r = 16, c = 2 * Math.PI * r;
  return (
    '<div class="sec-ring">' +
      '<svg width="40" height="40" viewBox="0 0 40 40">' +
        '<circle class="ring-bg" cx="20" cy="20" r="' + r + '" fill="none" stroke-width="4"></circle>' +
        '<circle class="ring-fg" id="ring_' + secId + '" cx="20" cy="20" r="' + r + '" fill="none" stroke-width="4" stroke-dasharray="' + c.toFixed(2) + '" stroke-dashoffset="' + c.toFixed(2) + '"></circle>' +
      "</svg>" +
      '<div class="ring-txt" id="ringtxt_' + secId + '">0%</div>' +
    "</div>"
  );
}

function renderCheck(it) {
  return (
    '<div class="item" data-id="' + it.id + '" data-tags="' + it.tags.join(",") + '" data-search="' + it.title.toLowerCase() + '">' +
      '<button class="check" aria-label="Toggle ' + escapeAttr(it.title) + '">' + CHECK_SVG + "</button>" +
      '<div class="item-main">' +
        '<div class="item-title">' + escapeHtml(it.title) + "</div>" +
        tagPills(it.tags) +
      "</div>" +
    "</div>"
  );
}

function renderBank(it) {
  const chips = it.unitIds.map((u, i) =>
    '<button class="qchip" data-unit="' + u + '">' + (i + 1) + "</button>"
  ).join("");
  return (
    '<div class="bank" data-bank="' + it.id + '" data-tags="' + it.tags.join(",") + '" data-search="' + it.title.toLowerCase() + '">' +
      '<div class="bank-head">' +
        '<div class="bank-title">' + escapeHtml(it.title) + tagPills(it.tags) + "</div>" +
        '<div style="display:flex;align-items:center;gap:10px;flex-wrap:wrap">' +
          '<span class="bank-count" id="bankcount_' + it.id + '"></span>' +
          '<div class="bank-actions">' +
            '<button class="btn btn-sm ghost" data-bankall="' + it.id + '">Mark all</button>' +
            '<button class="btn btn-sm ghost" data-bankreset="' + it.id + '">Reset</button>' +
          "</div>" +
        "</div>" +
      "</div>" +
      '<div class="chip-grid">' + chips + "</div>" +
    "</div>"
  );
}

function buildStats() {
  // category cards from key sections
  const cats = [
    { label: "All topics", icon: "book", units: topicUnits() },
    { label: "MCQs", icon: "list", units: bankUnitsOf("s10") },
    { label: "Short questions", icon: "chat", units: bankUnitsOf("s11") },
    { label: "Long questions", icon: "doc", units: bankUnitsOf("s12") },
    { label: "Diagram practice", icon: "shapes", units: secUnits("s5").concat(bankUnitsOf("s13")) },
    { label: "Calculations", icon: "calc", units: bankUnitsOf("s14") }
  ];
  el("#statGrid").innerHTML = cats.map((c) =>
    '<div class="stat" data-cat="' + c.label + '">' +
      '<div class="stat-label">' + c.label + "</div>" +
      '<div class="stat-num mono"><span id="statnum_' + c.label.replace(/\W/g, "") + '">0</span><small> / ' + c.units.length + "</small></div>" +
      '<div class="mini-bar"><span id="statbar_' + c.label.replace(/\W/g, "") + '"></span></div>' +
    "</div>"
  ).join("");
  buildStats._cats = cats;
}
function topicUnits() {
  const ids = [];
  studyData.forEach((s) => s.items.forEach((it) => { if (it.kind === "check") ids.push(it.id); }));
  return ids;
}
function secUnits(secId) {
  const sec = studyData.find((s) => s.id === secId); const ids = [];
  sec.items.forEach((it) => itemUnits(it).forEach((u) => ids.push(u)));
  return ids;
}
function bankUnitsOf(secId) {
  const sec = studyData.find((s) => s.id === secId); const ids = [];
  sec.items.forEach((it) => { if (it.kind === "bank") it.unitIds.forEach((u) => ids.push(u)); });
  return ids;
}

/* ---------- Refresh (update all counts/visuals) ---------- */
function refresh() {
  const units = allUnits();
  const total = units.length;
  const done = units.filter((u) => state.done[u]).length;
  const pct = total ? Math.round((done / total) * 100) : 0;

  el("#heroPct").textContent = pct;
  el("#heroDone").textContent = done;
  el("#heroTotal").textContent = total;
  buildChainStrip(pct);

  // item visual states
  elAll(".item").forEach((row) => {
    row.classList.toggle("done", !!state.done[row.dataset.id]);
  });
  elAll(".qchip").forEach((c) => {
    c.classList.toggle("done", !!state.done[c.dataset.unit]);
  });

  // section rings + meta + sidebar
  studyData.forEach((sec, i) => {
    const d = sectionDone(sec), t = sectionTotal(sec);
    const p = t ? d / t : 0;
    const r = 16, c = 2 * Math.PI * r;
    const ring = el("#ring_" + sec.id);
    if (ring) ring.setAttribute("stroke-dashoffset", (c * (1 - p)).toFixed(2));
    const rt = el("#ringtxt_" + sec.id); if (rt) rt.textContent = Math.round(p * 100) + "%";
    const meta = el("#secmeta_" + sec.id);
    if (meta) meta.textContent = d + " of " + t + " done";
    const secEl = el("#sec_" + sec.id);
    if (secEl) secEl.classList.toggle("complete", d === t && t > 0);
    // sidebar
    const nav = el('[data-jump="' + sec.id + '"]');
    if (nav) {
      nav.classList.toggle("complete", d === t && t > 0);
      nav.classList.toggle("partial", d > 0 && d < t);
      el("#navcount_" + sec.id).textContent = d + "/" + t;
    }
  });

  // bank counts
  studyData.forEach((sec) => sec.items.forEach((it) => {
    if (it.kind === "bank") {
      const dc = itemDoneCount(it);
      const span = el("#bankcount_" + it.id);
      if (span) span.innerHTML = "<b>" + dc + "</b> / " + it.count + " done";
    }
  }));

  // stat cards
  (buildStats._cats || []).forEach((c) => {
    const d = c.units.filter((u) => state.done[u]).length;
    const key = c.label.replace(/\W/g, "");
    const num = el("#statnum_" + key); if (num) num.textContent = d;
    const bar = el("#statbar_" + key);
    if (bar) bar.style.width = (c.units.length ? (d / c.units.length * 100) : 0) + "%";
  });

  applyFilters();
}

function buildChainStrip(pct) {
  const strip = el("#chainStrip");
  const N = 32;
  if (strip.childElementCount !== N) {
    strip.innerHTML = "";
    for (let i = 0; i < N; i++) {
      const b = document.createElement("div");
      b.className = "chain-block";
      strip.appendChild(b);
    }
  }
  const filled = Math.round((pct / 100) * N);
  Array.from(strip.children).forEach((b, i) => b.classList.toggle("filled", i < filled));
}

/* ============================================================
   FILTER / SEARCH / REVISION
   ============================================================ */
function applyFilters() {
  const q = state.search.trim().toLowerCase();
  let anyVisible = false;

  studyData.forEach((sec) => {
    const secEl = el("#sec_" + sec.id);
    let visibleInSec = 0;

    sec.items.forEach((it) => {
      const node = it.kind === "bank"
        ? secEl.querySelector('[data-bank="' + it.id + '"]')
        : secEl.querySelector('.item[data-id="' + it.id + '"]');
      if (!node) return;

      const complete = itemComplete(it);
      const dc = itemDoneCount(it);
      let show = true;

      // search
      if (q && it.title.toLowerCase().indexOf(q) === -1) {
        const tagMatch = it.tags.some((t) => TAG[t] && TAG[t].label.toLowerCase().indexOf(q) !== -1);
        if (!tagMatch) show = false;
      }
      // filter chips
      if (show && state.filter === "completed" && !complete) show = false;
      if (show && state.filter === "remaining" && complete) show = false;
      if (show && state.filter === "high" && it.tags.indexOf("high") === -1) show = false;
      // revision mode: keep if remaining OR has a revision-worthy tag
      if (show && state.revision) {
        const isRevisionTag = it.tags.some((t) => REVISION_TAGS.indexOf(t) !== -1);
        const remaining = !complete;
        if (!(isRevisionTag || remaining)) show = false;
      }

      node.classList.toggle("item-hidden", !show);
      if (show) visibleInSec++;
    });

    // hide whole section if nothing matches (only when filtering/searching)
    const filtering = q || state.filter !== "all" || state.revision;
    secEl.classList.toggle("hidden", filtering && visibleInSec === 0);
    if (visibleInSec > 0) anyVisible = true;

    // auto-expand sections that have matches during active search
    if (q && visibleInSec > 0) secEl.classList.remove("collapsed");
  });

  el("#emptyState").style.display = anyVisible ? "none" : "block";
}

/* ============================================================
   STUDY TIMER (25-min focus)
   ============================================================ */
const timer = { total: 25 * 60, left: 25 * 60, running: false, handle: null };
function fmt(s) {
  const m = Math.floor(s / 60), sec = s % 60;
  return String(m).padStart(2, "0") + ":" + String(sec).padStart(2, "0");
}
function renderTimer() {
  el("#timerTime").textContent = fmt(timer.left);
  el("#timerWrap").classList.toggle("running", timer.running);
  el("#timerToggle").innerHTML = timer.running ? PAUSE_SVG : PLAY_SVG;
}
function tickTimer() {
  if (timer.left <= 0) {
    stopTimer();
    timer.left = 0; renderTimer();
    toast("Focus session complete. Take a short break.");
    return;
  }
  timer.left--; renderTimer();
}
function startTimer() {
  if (timer.running) return;
  timer.running = true;
  timer.handle = setInterval(tickTimer, 1000);
  renderTimer();
}
function stopTimer() {
  timer.running = false;
  clearInterval(timer.handle);
  renderTimer();
}
function resetTimer() {
  stopTimer(); timer.left = timer.total; renderTimer();
}
const PLAY_SVG = '<svg viewBox="0 0 24 24" fill="currentColor"><polygon points="6 4 20 12 6 20 6 4"></polygon></svg>';
const PAUSE_SVG = '<svg viewBox="0 0 24 24" fill="currentColor"><rect x="6" y="5" width="4" height="14" rx="1"></rect><rect x="14" y="5" width="4" height="14" rx="1"></rect></svg>';
const RESET_SVG = '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><polyline points="1 4 1 10 7 10"></polyline><path d="M3.51 15a9 9 0 1 0 2.13-9.36L1 10"></path></svg>';

/* ============================================================
   THEME + SIDEBAR + TOAST
   ============================================================ */
function applyTheme() {
  document.documentElement.setAttribute("data-theme", state.theme);
  el("#themeToggle").innerHTML = state.theme === "dark" ? SUN_SVG : MOON_SVG;
}
const SUN_SVG = '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="4"></circle><path d="M12 2v2M12 20v2M4.9 4.9l1.4 1.4M17.7 17.7l1.4 1.4M2 12h2M20 12h2M4.9 19.1l1.4-1.4M17.7 6.3l1.4-1.4"></path></svg>';
const MOON_SVG = '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M21 12.79A9 9 0 1 1 11.21 3 7 7 0 0 0 21 12.79z"></path></svg>';

function openSidebar() { el("#sidebar").classList.add("open"); el("#backdrop").classList.add("show"); }
function closeSidebar() { el("#sidebar").classList.remove("open"); el("#backdrop").classList.remove("show"); }

let toastTimer = null;
function toast(msg) {
  const t = el("#toast");
  t.textContent = msg; t.classList.add("show");
  clearTimeout(toastTimer);
  toastTimer = setTimeout(() => t.classList.remove("show"), 2200);
}

/* ---------- escape helpers ---------- */
function escapeHtml(s) { return s.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;"); }
function escapeAttr(s) { return escapeHtml(s).replace(/"/g, "&quot;"); }

/* ============================================================
   INIT
   ============================================================ */
function init() {
  load();
  applyTheme();
  buildSidebar();
  buildStats();
  buildSections();

  // notes
  const notes = el("#notes");
  notes.value = state.notes || "";
  notes.addEventListener("input", () => {
    state.notes = notes.value; save();
    el("#notesSaved").textContent = "Saved";
    clearTimeout(notes._t);
    notes._t = setTimeout(() => { el("#notesSaved").textContent = "Saved automatically"; }, 1000);
  });

  // search
  el("#search").addEventListener("input", (e) => { state.search = e.target.value; applyFilters(); });

  // filter chips
  elAll(".filter-chips [data-filter]").forEach((b) => b.addEventListener("click", () => {
    state.filter = b.dataset.filter;
    elAll(".filter-chips [data-filter]").forEach((x) => x.classList.toggle("active", x === b));
    applyFilters();
  }));

  // revision mode
  el("#revisionToggle").addEventListener("click", () => {
    state.revision = !state.revision;
    el("#revisionToggle").classList.toggle("active", state.revision);
    el("#revisionToggle").textContent = state.revision ? "Revision mode: ON" : "Revision mode";
    if (state.revision) toast("Revision mode: showing priority and remaining items");
    applyFilters();
  });

  // theme
  el("#themeToggle").addEventListener("click", () => {
    state.theme = state.theme === "dark" ? "light" : "dark"; applyTheme(); save();
  });

  // reset all
  el("#resetAll").addEventListener("click", () => {
    if (confirm("Reset ALL progress? This clears every checkmark. Your notes are kept.")) {
      state.done = {}; save(); refresh(); toast("All progress reset");
    }
  });

  // collapse / expand all
  el("#expandAll").addEventListener("click", () => {
    studyData.forEach((s) => { state.open[s.id] = false; el("#sec_" + s.id).classList.remove("collapsed"); });
    save();
  });
  el("#collapseAll").addEventListener("click", () => {
    studyData.forEach((s) => { state.open[s.id] = true; el("#sec_" + s.id).classList.add("collapsed"); });
    save();
  });

  // timer
  el("#timerToggle").addEventListener("click", () => { timer.running ? stopTimer() : startTimer(); });
  el("#timerReset").addEventListener("click", resetTimer);
  el("#timerReset").innerHTML = RESET_SVG;
  renderTimer();

  // mobile sidebar
  el("#menuBtn").addEventListener("click", openSidebar);
  el("#backdrop").addEventListener("click", closeSidebar);

  refresh();
}

document.addEventListener("DOMContentLoaded", init);
