/* =========================================================
   Final Exam Study Tracker — Computer Networks
   Plain JavaScript. No frameworks. Saves to localStorage.
   Data comes from data.js (STUDY, QUESTIONS, GLOSSARY).
   ========================================================= */

"use strict";

/* ---------- storage keys ---------- */
const LS = {
  topics:   "cn_topics_v1",   // { topicId: "not-started"|"in-progress"|"completed" }
  revision: "cn_revision_v1", // { topicId: true }
  quest:    "cn_quest_v1",    // { qId: "practiced"|"mastered" }
  qrev:     "cn_qrev_v1",     // { qId: true }
  notes:    "cn_notes_v1",    // string
  theme:    "cn_theme_v1",    // "light" | "dark"
  view:     "cn_view_v1"      // last open view
};

/* ---------- state ---------- */
let topicStatus = load(LS.topics, {});
let topicRev    = load(LS.revision, {});
let questState  = load(LS.quest, {});
let questRev    = load(LS.qrev, {});
let currentView = load(LS.view, "dashboard", true) || "dashboard";
let activeFilter = "all";
let searchTerm = "";
const openSections = new Set();   // remember which study sections are expanded

function load(key, fallback, raw) {
  try {
    const v = localStorage.getItem(key);
    if (v === null) return fallback;
    return raw ? v : JSON.parse(v);
  } catch (e) { return fallback; }
}
function save(key, val, raw) {
  try { localStorage.setItem(key, raw ? val : JSON.stringify(val)); } catch (e) {}
}

/* ---------- small helpers ---------- */
const $  = (s, r = document) => r.querySelector(s);
const $$ = (s, r = document) => Array.from(r.querySelectorAll(s));
const icon = id => `<svg class="ic"><use href="#${id}"/></svg>`;
function esc(s) {
  return String(s).replace(/[&<>"']/g, c =>
    ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" }[c]));
}

/* flatten all study topics into one list (keeps section + lec) */
function allTopics() {
  const out = [];
  STUDY.forEach(sec => sec.items.forEach(it =>
    out.push({ ...it, section: sec.section, lec: sec.lec, kind: sec.kind })));
  return out;
}
const statusOf = id => topicStatus[id] || "not-started";
function isNumericalTopic(t) {
  return t.kind === "numerical" || t.tags.includes("Numerical");
}
function isTheoryTopic(t) {
  return t.tags.includes("Theory") || t.kind === "theory" || t.kind === "both";
}

/* =========================================================
   PROGRESS + READINESS MATH
   Theory weight 30%, Numerical weight 70% (teacher's split).
   ========================================================= */
function computeStats() {
  const topics = allTopics();
  const total = topics.length;
  let completed = 0, inProgress = 0, revision = 0;
  let thDone = 0, thTotal = 0, nuDone = 0, nuTotal = 0;
  const diff = { easy: [0, 0], medium: [0, 0], hard: [0, 0] }; // [done, total]

  topics.forEach(t => {
    const st = statusOf(t.id);
    if (st === "completed") completed++;
    else if (st === "in-progress") inProgress++;
    if (topicRev[t.id]) revision++;

    const done = st === "completed";
    if (diff[t.difficulty]) { diff[t.difficulty][1]++; if (done) diff[t.difficulty][0]++; }

    if (isNumericalTopic(t)) { nuTotal++; if (done) nuDone++; }
    else { thTotal++; if (done) thDone++; } // theory bucket = everything not numerical
  });

  // question bank counts
  const qVals = Object.values(questState);
  const practiced = qVals.filter(v => v === "practiced").length;
  const mastered  = qVals.filter(v => v === "mastered").length;

  const overall = total ? Math.round((completed / total) * 100) : 0;
  const thPct = thTotal ? thDone / thTotal : 0;
  const nuPct = nuTotal ? nuDone / nuTotal : 0;
  // readiness: numerical carries 70%, theory 30%
  const readiness = Math.round((nuPct * 0.7 + thPct * 0.3) * 100);

  return {
    total, completed, inProgress, remaining: total - completed, revision,
    thDone, thTotal, nuDone, nuTotal,
    thPctRound: Math.round(thPct * 100), nuPctRound: Math.round(nuPct * 100),
    overall, readiness, diff, practiced, mastered,
    qTotal: QUESTIONS.length
  };
}

function lectureProgress() {
  const map = {};
  STUDY.forEach(sec => {
    if (!map[sec.lec]) map[sec.lec] = { lec: sec.lec, name: sec.section, done: 0, total: 0 };
    sec.items.forEach(it => {
      map[sec.lec].total++;
      if (statusOf(it.id) === "completed") map[sec.lec].done++;
    });
  });
  return Object.values(map).sort((a, b) => a.lec - b.lec);
}

/* =========================================================
   TAG + DIFFICULTY rendering helpers
   ========================================================= */
function tagClass(tag) {
  if (tag === "High Priority" || tag === "Numerical") return "hot";
  if (tag === "Must Revise" || tag === "Formula" || tag === "Exam Likely") return "gold";
  return "";
}
function renderTags(tags) {
  return tags.map(t => `<span class="tag ${tagClass(t)}">${esc(t)}</span>`).join("");
}
function diffBadge(d) {
  return `<span class="diff-badge ${d}">${d}</span>`;
}
function statusIcon(st) {
  if (st === "completed") return icon("i-check");
  if (st === "in-progress") return icon("i-half");
  return icon("i-circle");
}

/* =========================================================
   FILTER logic (used by study + question views)
   ========================================================= */
function topicMatchesFilter(t) {
  const st = statusOf(t.id);
  switch (activeFilter) {
    case "completed":   return st === "completed";
    case "remaining":   return st !== "completed";
    case "in-progress": return st === "in-progress";
    case "revision":    return !!topicRev[t.id];
    case "theory":      return !isNumericalTopic(t);
    case "numerical":   return isNumericalTopic(t);
    case "high":        return t.tags.includes("High Priority");
    case "difficult":   return t.difficulty === "hard";
    default:            return true;
  }
}
function topicMatchesSearch(t) {
  if (!searchTerm) return true;
  const hay = (t.title + " " + t.tags.join(" ") + " " + t.content).toLowerCase();
  return hay.includes(searchTerm);
}

/* =========================================================
   VIEW: DASHBOARD
   ========================================================= */
function viewDashboard() {
  const s = computeStats();
  const C = 2 * Math.PI * 64;                 // gauge circumference (r=64)
  const offset = C - (s.readiness / 100) * C;

  const next = studyNext(5);
  const lec = lectureProgress();

  const diffRow = (name, key) => {
    const [d, t] = s.diff[key];
    const pct = t ? Math.round((d / t) * 100) : 0;
    return `<div class="diff-row ${key}">
      <span class="name">${name}</span>
      <span class="bar"><span style="width:${pct}%"></span></span>
      <span class="n">${d}/${t}</span></div>`;
  };

  return `<div class="view">
    <div class="page-head">
      <h2>Dashboard</h2>
      <p>Your exam is split into Theory (30%) and Numerical (70%). Your readiness score gives numerical work more weight, just like the real paper.</p>
    </div>

    <div class="dash-grid">

      <!-- readiness gauge -->
      <div class="card gauge-card span-5">
        <div class="gauge-wrap">
          <svg viewBox="0 0 150 150">
            <circle class="gauge-track" cx="75" cy="75" r="64"></circle>
            <circle class="gauge-fill" cx="75" cy="75" r="64"
              style="stroke-dasharray:${C};stroke-dashoffset:${offset}"></circle>
          </svg>
          <div class="gauge-center">
            <div class="num">${s.readiness}%</div>
            <div class="lbl">Ready</div>
          </div>
        </div>
        <div class="gauge-info">
          <h3>Exam Readiness</h3>
          <p>${readinessMessage(s.readiness)}</p>
          <div class="weight-bar"><span class="w-num"></span><span class="w-theo"></span></div>
          <div class="weight-legend">
            <span class="li-num"><i></i>Numerical 70%</span>
            <span class="li-theo"><i></i>Theory 30%</span>
          </div>
        </div>
      </div>

      <!-- overall progress -->
      <div class="card span-7">
        <div class="eyebrow">Overall progress</div>
        <div class="mini-stats" style="margin-top:6px">
          <div class="mini-stat"><div class="v">${s.completed}</div><div class="l">Completed</div></div>
          <div class="mini-stat"><div class="v">${s.inProgress}</div><div class="l">In progress</div></div>
          <div class="mini-stat"><div class="v">${s.remaining}</div><div class="l">Remaining</div></div>
          <div class="mini-stat"><div class="v">${s.total}</div><div class="l">Total topics</div></div>
        </div>
        <div class="progressbar"><span style="width:${s.overall}%"></span></div>
        <div class="sec-count" style="margin-top:8px">${s.overall}% of all topics marked done</div>

        <div style="margin-top:18px" class="mini-stats">
          <div class="mini-stat"><div class="v">${s.thDone}/${s.thTotal}</div><div class="l">Theory topics done</div></div>
          <div class="mini-stat"><div class="v">${s.nuDone}/${s.nuTotal}</div><div class="l">Numerical topics done</div></div>
          <div class="mini-stat"><div class="v">${s.revision}</div><div class="l">Marked for revision</div></div>
          <div class="mini-stat"><div class="v">${s.mastered}</div><div class="l">Questions mastered</div></div>
        </div>
      </div>

      <!-- theory progress -->
      <div class="card span-6">
        <div class="eyebrow">Theory preparation <span class="nav-pill">30%</span></div>
        <div class="stat-value" style="margin-top:8px">${s.thPctRound}%</div>
        <div class="stat-sub">${s.thDone} of ${s.thTotal} theory topics completed</div>
        <div class="progressbar gold"><span style="width:${s.thPctRound}%"></span></div>
      </div>

      <!-- numerical progress -->
      <div class="card span-6">
        <div class="eyebrow">Numerical practice <span class="nav-pill strong">70%</span></div>
        <div class="stat-value" style="margin-top:8px">${s.nuPctRound}%</div>
        <div class="stat-sub">${s.nuDone} of ${s.nuTotal} numerical topics completed</div>
        <div class="progressbar accent"><span style="width:${s.nuPctRound}%"></span></div>
      </div>

      <!-- study next -->
      <div class="card span-7">
        <div class="eyebrow">${icon("i-target")} Study next</div>
        <div class="sec-count" style="margin-top:2px">Smart picks based on priority, difficulty and revision flags.</div>
        <div class="next-list">
          ${next.length ? next.map(t => `
            <button class="next-item" data-goto="${t.id}">
              ${icon("i-chev")}
              <span>
                <b>${esc(t.title)}</b>
                <span style="display:block;font-size:11.5px;color:var(--text-faint)">${esc(t.section)} · ${t.difficulty}</span>
              </span>
            </button>`).join("")
            : `<div class="sec-count">All caught up. Great work — switch to Revision Mode for a final pass.</div>`}
        </div>
      </div>

      <!-- difficulty -->
      <div class="card span-5">
        <div class="eyebrow">Difficulty breakdown</div>
        <div class="sec-count" style="margin-top:2px">How much of each difficulty you have finished.</div>
        <div style="margin-top:8px">
          ${diffRow("Easy", "easy")}
          ${diffRow("Medium", "medium")}
          ${diffRow("Hard", "hard")}
        </div>
      </div>

      <!-- question bank summary -->
      <div class="card span-6">
        <div class="eyebrow">${icon("i-help")} Question bank</div>
        <div class="mini-stats" style="margin-top:8px">
          <div class="mini-stat"><div class="v">${s.qTotal}</div><div class="l">Total questions</div></div>
          <div class="mini-stat"><div class="v">${s.practiced}</div><div class="l">Practiced</div></div>
          <div class="mini-stat"><div class="v">${s.mastered}</div><div class="l">Mastered</div></div>
        </div>
      </div>

      <!-- lecture coverage -->
      <div class="card span-6">
        <div class="eyebrow">${icon("i-book")} Lecture coverage</div>
        <div style="margin-top:10px;display:flex;flex-direction:column;gap:7px">
          ${lec.map(l => {
            const pct = l.total ? Math.round((l.done / l.total) * 100) : 0;
            return `<div class="diff-row">
              <span class="name" style="width:auto;flex:none">L${l.lec}</span>
              <span class="bar"><span style="width:${pct}%;background:var(--olive)"></span></span>
              <span class="n">${l.done}/${l.total}</span></div>`;
          }).join("")}
        </div>
      </div>

    </div>
  </div>`;
}

function readinessMessage(r) {
  if (r >= 85) return "You are in strong shape. Keep revising weak spots.";
  if (r >= 60) return "Good momentum. Push the numerical topics a bit more.";
  if (r >= 35) return "You are getting there. Focus on numericals — they are 70%.";
  return "Early stage. Start with high-priority and numerical topics.";
}

/* Study Next recommendation engine.
   Priority order: incomplete High Priority > Hard > revision-marked
   > remaining Numerical > Exam Likely > anything remaining. */
function studyNext(limit) {
  const topics = allTopics().filter(t => statusOf(t.id) !== "completed");
  const score = t => {
    let s = 0;
    if (t.tags.includes("High Priority")) s += 50;
    if (t.difficulty === "hard") s += 30;
    if (topicRev[t.id]) s += 28;
    if (isNumericalTopic(t)) s += 25;
    if (t.tags.includes("Exam Likely")) s += 15;
    if (t.tags.includes("Must Revise")) s += 12;
    if (statusOf(t.id) === "in-progress") s += 10;
    return s;
  };
  return topics.sort((a, b) => score(b) - score(a)).slice(0, limit);
}

/* =========================================================
   VIEW: STUDY GUIDE (collapsible sections + topics)
   ========================================================= */
function viewStudy(opts = {}) {
  const title = opts.title || "Study Guide";
  const sub = opts.sub || "Read each topic in simple English, then mark your status. Everything is saved automatically.";
  const onlyKind = opts.onlyKind || null;     // "theory" | "numerical" | null
  const showFilters = opts.showFilters !== false;

  let visibleCount = 0;
  const sectionsHtml = STUDY.map(sec => {
    // section-level kind filter for theory/numerical pages
    let items = sec.items.filter(it => {
      const t = { ...it, kind: sec.kind, lec: sec.lec };
      if (onlyKind === "numerical" && !isNumericalTopic(t)) return false;
      if (onlyKind === "theory" && isNumericalTopic(t)) return false;
      return topicMatchesFilter(t) && topicMatchesSearch(t);
    });
    if (!items.length) return "";

    const total = sec.items.length;
    const done = sec.items.filter(it => statusOf(it.id) === "completed").length;
    const pct = total ? Math.round((done / total) * 100) : 0;
    visibleCount += items.length;

    const isOpen = openSections.has(sec.section) || !!searchTerm || activeFilter !== "all";

    const topicsHtml = items.map(it => {
      const st = statusOf(it.id);
      const rev = !!topicRev[it.id];
      return `<div class="topic" data-status="${st}" data-topic="${it.id}">
        <div class="topic-row js-topic-toggle">
          <div class="topic-side">
            <button class="status-btn js-status" title="Change status" data-id="${it.id}">${statusIcon(st)}</button>
          </div>
          <div class="topic-main">
            <div class="topic-title">${esc(it.title)} ${diffBadge(it.difficulty)}</div>
            <div class="topic-tags">${renderTags(it.tags)}</div>
          </div>
          <div class="topic-side">
            <button class="rev-btn js-rev ${rev ? "on" : ""}" title="Mark for revision" data-id="${it.id}">${icon("i-flag")}</button>
            <span class="topic-chev">${icon("i-chev")}</span>
          </div>
        </div>
        <div class="topic-content"><div class="topic-content-inner">
          <div class="content-pad"><div class="study">${it.content}</div></div>
        </div></div>
      </div>`;
    }).join("");

    return `<div class="card section-card ${isOpen ? "open" : ""}" data-section="${esc(sec.section)}">
      <div class="section-head js-section-toggle">
        <span class="chev">${icon("i-chev")}</span>
        <span style="flex:1;font-weight:700;font-family:var(--font-display);font-size:16px">${esc(sec.section)}</span>
        <span class="sec-meta">
          <span class="sec-count">${done}/${total}</span>
          <span class="sec-bar"><span style="width:${pct}%"></span></span>
        </span>
      </div>
      <div class="section-body"><div class="section-inner">
        <div class="section-tools">
          <button class="btn tiny ghost js-mark-all" data-section="${esc(sec.section)}">${icon("i-check")}Mark all done</button>
          <button class="btn tiny ghost js-reset-sec" data-section="${esc(sec.section)}">${icon("i-reset")}Reset section</button>
        </div>
        ${topicsHtml}
      </div></div>
    </div>`;
  }).join("");

  return `<div class="view">
    <div class="page-head"><h2>${title}</h2><p>${sub}</p></div>
    ${showFilters ? filterBar() : ""}
    ${searchTerm || activeFilter !== "all" ? `<div class="result-count">${visibleCount} topic(s) shown</div>` : ""}
    ${sectionsHtml || emptyState("No topics match your search or filter.")}
  </div>`;
}

function filterBar() {
  const chips = [
    ["all", "All"], ["remaining", "Remaining"], ["completed", "Completed"],
    ["in-progress", "In progress"], ["revision", "Marked for revision"],
    ["theory", "Theory"], ["numerical", "Numerical"],
    ["high", "High priority"], ["difficult", "Difficult"]
  ];
  return `<div class="filterbar">
    ${chips.map(([k, label]) =>
      `<button class="chip ${activeFilter === k ? "active" : ""}" data-filter="${k}">${label}</button>`).join("")}
  </div>`;
}

function emptyState(msg) {
  return `<div class="card empty"><b>Nothing here yet</b>${esc(msg)}</div>`;
}

/* =========================================================
   VIEW: THEORY / NUMERICAL (reuse study with a kind filter)
   ========================================================= */
function viewTheory() {
  return viewStudy({
    title: "Theory Preparation",
    sub: "Section I of the exam (30%). These are the concept-based topics. Focus on understanding and being able to explain ideas clearly.",
    onlyKind: "theory"
  });
}
function viewNumerical() {
  return viewStudy({
    title: "Numerical Practice",
    sub: "Section II of the exam (70%) — the biggest part of your marks. Practice the methods, formulas and worked steps until you can do them without help.",
    onlyKind: "numerical"
  });
}

/* =========================================================
   VIEW: QUESTION BANK
   ========================================================= */
function viewQuestions() {
  // group questions by category
  const cats = {};
  QUESTIONS.forEach(q => {
    if (searchTerm) {
      const hay = (q.q + " " + q.a + " " + q.cat + " " + q.tags.join(" ")).toLowerCase();
      if (!hay.includes(searchTerm)) return;
    }
    if (!qFilterMatch(q)) return;
    (cats[q.cat] = cats[q.cat] || []).push(q);
  });

  const order = ["Short Theory", "Long Theory", "Numerical", "Practice"];
  const keys = Object.keys(cats).sort((a, b) => {
    const ia = order.indexOf(a), ib = order.indexOf(b);
    return (ia < 0 ? 99 : ia) - (ib < 0 ? 99 : ib);
  });

  const body = keys.map(cat => {
    const qs = cats[cat];
    return `<h3 style="font-family:var(--font-display);font-size:18px;margin:22px 0 12px">${esc(cat)} <span class="sec-count">(${qs.length})</span></h3>
      ${qs.map(renderQuestionCard).join("")}`;
  }).join("");

  return `<div class="view">
    <div class="page-head">
      <h2>Question Bank</h2>
      <p>Theory and numerical questions pulled from your lectures, quizzes and assignments. Open each answer, then mark it practiced or mastered.</p>
    </div>
    ${qFilterBar()}
    ${body || emptyState("No questions match your search or filter.")}
  </div>`;
}

function qFilterBar() {
  const chips = [
    ["all", "All"], ["theory", "Theory"], ["numerical", "Numerical"],
    ["practiced", "Practiced"], ["mastered", "Mastered"],
    ["qrev", "Marked for revision"], ["unseen", "Not started"]
  ];
  return `<div class="filterbar">
    ${chips.map(([k, label]) =>
      `<button class="chip ${activeFilter === k ? "active" : ""}" data-filter="${k}">${label}</button>`).join("")}
  </div>`;
}
function qFilterMatch(q) {
  const st = questState[q.id];
  switch (activeFilter) {
    case "theory":    return q.type === "theory";
    case "numerical": return q.type === "numerical";
    case "practiced": return st === "practiced";
    case "mastered":  return st === "mastered";
    case "qrev":      return !!questRev[q.id];
    case "unseen":    return !st;
    default:          return true;
  }
}
function renderQuestionCard(q) {
  const st = questState[q.id] || "";
  const rev = !!questRev[q.id];
  const isNum = q.type === "numerical";
  return `<div class="card qcard" data-q="${q.id}">
    <div class="qcard-top">
      <span class="q-kind ${isNum ? "num" : ""}">${isNum ? "Numerical" : "Theory"}</span>
      ${diffBadge(q.difficulty)}
      <span class="q-text">${esc(q.q)}</span>
      <span class="q-meta">
        <button class="rev-btn js-qrev ${rev ? "on" : ""}" title="Mark for revision" data-id="${q.id}">${icon("i-flag")}</button>
      </span>
    </div>
    <div class="q-actions">
      <button class="btn tiny js-show-ans" data-id="${q.id}">${icon("i-eye")}Show answer</button>
      <button class="q-state js-qstate ${st === "practiced" ? "on practiced" : ""}" data-id="${q.id}" data-set="practiced">Practiced</button>
      <button class="q-state js-qstate ${st === "mastered" ? "on mastered" : ""}" data-id="${q.id}" data-set="mastered">Mastered</button>
    </div>
    <div class="q-answer"><div class="q-answer-inner">
      <div class="study">${q.a}</div>
    </div></div>
  </div>`;
}

/* =========================================================
   VIEW: REVISION MODE
   ========================================================= */
function viewRevision() {
  const topics = allTopics();
  const revTopics = topics.filter(t => topicRev[t.id]);
  const highPr = topics.filter(t => t.tags.includes("High Priority") && statusOf(t.id) !== "completed");
  const hard = topics.filter(t => t.difficulty === "hard" && statusOf(t.id) !== "completed");
  const remaining = topics.filter(t => statusOf(t.id) !== "completed");
  const formulas = topics.filter(t => t.tags.includes("Formula"));
  const examLikely = topics.filter(t => t.tags.includes("Exam Likely"));
  const numericals = topics.filter(t => isNumericalTopic(t));
  const revQuestions = QUESTIONS.filter(q => questRev[q.id]);

  const compactList = (arr, emptyMsg) => arr.length
    ? `<div class="next-list">${arr.map(t => `
        <button class="next-item" data-goto="${t.id}">
          ${icon("i-chev")}
          <span><b>${esc(t.title)}</b>
          <span style="display:block;font-size:11.5px;color:var(--text-faint)">${esc(t.section)} · ${t.difficulty} ${topicRev[t.id] ? "· flagged" : ""}</span></span>
        </button>`).join("")}</div>`
    : `<div class="sec-count">${emptyMsg}</div>`;

  const block = (titleTxt, count, inner) => `
    <div class="card" style="margin-bottom:16px;padding:20px">
      <div class="eyebrow">${titleTxt} <span class="sec-count">(${count})</span></div>
      <div style="margin-top:10px">${inner}</div>
    </div>`;

  return `<div class="view">
    <div class="rev-banner">
      ${icon("i-flame")}
      <div>
        <h3>Last-Minute Revision</h3>
        <p>Everything you should look at right before the exam, in one place.</p>
      </div>
    </div>

    ${block("Flagged for revision", revTopics.length,
      compactList(revTopics, "You have not flagged any topic yet. Use the flag icon on any topic."))}

    ${block("High-priority topics still left", highPr.length,
      compactList(highPr, "No high-priority topics left. Well done."))}

    ${block("Hard topics still left", hard.length,
      compactList(hard, "No hard topics left to do."))}

    ${block("Numerical methods to drill (70% of the paper)", numericals.length,
      compactList(numericals, "No numerical topics found."))}

    ${block("Formula-heavy topics", formulas.length,
      compactList(formulas, "No formula topics tagged."))}

    ${block("Exam-likely topics", examLikely.length,
      compactList(examLikely, "No exam-likely topics tagged."))}

    ${block("Questions you flagged", revQuestions.length,
      revQuestions.length
        ? `<div class="next-list">${revQuestions.map(q => `
            <button class="next-item" data-qgoto="${q.id}">
              ${icon("i-help")}
              <span><b>${esc(q.q)}</b>
              <span style="display:block;font-size:11.5px;color:var(--text-faint)">${q.type} · ${q.difficulty}</span></span>
            </button>`).join("")}</div>`
        : `<div class="sec-count">No flagged questions. Flag questions in the Question Bank.</div>`)}

    ${block("All remaining topics", remaining.length,
      compactList(remaining, "Everything is complete. You are ready."))}
  </div>`;
}

/* =========================================================
   VIEW: GLOSSARY
   ========================================================= */
function viewGlossary() {
  const items = GLOSSARY.filter(g => {
    if (!searchTerm) return true;
    return (g.term + " " + g.meaning + " " + g.why).toLowerCase().includes(searchTerm);
  });
  return `<div class="view">
    <div class="page-head">
      <h2>Glossary</h2>
      <p>Quick, plain-English meaning of every technical word in the course, plus why it matters for the exam.</p>
    </div>
    ${searchTerm ? `<div class="result-count">${items.length} term(s) shown</div>` : ""}
    <div class="gloss-grid">
      ${items.length ? items.map(g => `
        <div class="card gloss-card">
          <div class="gloss-term">${esc(g.term)}</div>
          <div class="gloss-meaning">${esc(g.meaning)}</div>
          <div class="gloss-why"><b>Why it matters:</b> ${g.why}</div>
        </div>`).join("") : emptyState("No terms match your search.")}
    </div>
  </div>`;
}

/* =========================================================
   VIEW: NOTES
   ========================================================= */
function viewNotes() {
  const notes = load(LS.notes, "", true);
  return `<div class="view">
    <div class="page-head">
      <h2>My Notes</h2>
      <p>Jot down anything: "revise this numerical", "ask about CRC", "learn this definition". Your notes are saved on this device automatically.</p>
    </div>
    <textarea class="notes-area" id="notesBox" placeholder="Start typing your study notes here...">${esc(notes)}</textarea>
    <div class="notes-hint" id="notesHint">Saved on this device.</div>
  </div>`;
}

/* =========================================================
   RENDER + NAV
   ========================================================= */
function render() {
  const main = $("#mainView");
  let html = "";
  switch (currentView) {
    case "dashboard": html = viewDashboard(); break;
    case "study":     html = viewStudy(); break;
    case "theory":    html = viewTheory(); break;
    case "numerical": html = viewNumerical(); break;
    case "questions": html = viewQuestions(); break;
    case "revision":  html = viewRevision(); break;
    case "glossary":  html = viewGlossary(); break;
    case "notes":     html = viewNotes(); break;
    default:          html = viewDashboard();
  }
  main.innerHTML = html;
  main.scrollTop = 0;

  // wire notes textarea
  const box = $("#notesBox");
  if (box) {
    let timer;
    box.addEventListener("input", () => {
      save(LS.notes, box.value, true);
      const hint = $("#notesHint");
      if (hint) { hint.textContent = "Saving..."; clearTimeout(timer);
        timer = setTimeout(() => hint.textContent = "Saved on this device.", 400); }
    });
  }
  renderLectureNav();
}

function setView(v) {
  currentView = v;
  save(LS.view, v, true);
  $$(".nav-link").forEach(b => b.classList.toggle("active", b.dataset.view === v));
  render();
  closeSidebar();
}

function renderLectureNav() {
  const nav = $("#lectureNav");
  if (!nav) return;
  const lec = lectureProgress();
  nav.innerHTML = lec.map(l => {
    const pct = l.total ? Math.round((l.done / l.total) * 100) : 0;
    const cls = pct === 100 ? "full" : pct > 0 ? "partial" : "";
    const short = l.name.replace(/^Lecture \d+ — /, "");
    return `<button class="nav-lecture" data-lec="${l.lec}" title="${esc(l.name)}">
      <span class="lec-dot ${cls}"></span>
      <span style="flex:1;overflow:hidden;text-overflow:ellipsis;white-space:nowrap">L${l.lec} · ${esc(short)}</span>
      <span class="pct">${pct}%</span>
    </button>`;
  }).join("");
}

/* =========================================================
   EVENT DELEGATION (one listener on main)
   ========================================================= */
function onMainClick(e) {
  const t = e.target;

  // status cycle
  const statusBtn = t.closest(".js-status");
  if (statusBtn) {
    e.stopPropagation();
    cycleStatus(statusBtn.dataset.id);
    return;
  }
  // revision flag (topic)
  const revBtn = t.closest(".js-rev");
  if (revBtn) {
    e.stopPropagation();
    toggleRevision(revBtn.dataset.id);
    return;
  }
  // expand topic content
  const topToggle = t.closest(".js-topic-toggle");
  if (topToggle) {
    topToggle.closest(".topic").classList.toggle("open");
    return;
  }
  // section expand
  const secToggle = t.closest(".js-section-toggle");
  if (secToggle) {
    const card = secToggle.closest(".section-card");
    const name = card.dataset.section;
    card.classList.toggle("open");
    if (card.classList.contains("open")) openSections.add(name);
    else openSections.delete(name);
    return;
  }
  // mark all done in section
  const markAll = t.closest(".js-mark-all");
  if (markAll) { e.stopPropagation(); markSection(markAll.dataset.section, "completed"); return; }
  const resetSec = t.closest(".js-reset-sec");
  if (resetSec) { e.stopPropagation(); markSection(resetSec.dataset.section, "not-started"); return; }

  // filter chips
  const chip = t.closest(".chip");
  if (chip) { activeFilter = chip.dataset.filter; render(); return; }

  // study-next / revision goto
  const goto = t.closest("[data-goto]");
  if (goto) { gotoTopic(goto.dataset.goto); return; }
  const qgoto = t.closest("[data-qgoto]");
  if (qgoto) { gotoQuestion(qgoto.dataset.qgoto); return; }

  // question actions
  const showAns = t.closest(".js-show-ans");
  if (showAns) {
    const card = showAns.closest(".qcard");
    const ans = $(".q-answer", card);
    ans.classList.toggle("open");
    showAns.innerHTML = ans.classList.contains("open")
      ? icon("i-x") + "Hide answer" : icon("i-eye") + "Show answer";
    return;
  }
  const qstate = t.closest(".js-qstate");
  if (qstate) { setQuestionState(qstate.dataset.id, qstate.dataset.set); return; }
  const qrev = t.closest(".js-qrev");
  if (qrev) { toggleQuestionRev(qrev.dataset.id); return; }
}

/* lecture nav clicks (sidebar) */
function onLectureNavClick(e) {
  const b = e.target.closest(".nav-lecture");
  if (!b) return;
  const lecNum = b.dataset.lec;
  // open study view and the matching section
  STUDY.forEach(sec => { if (String(sec.lec) === String(lecNum)) openSections.add(sec.section); });
  activeFilter = "all"; searchTerm = ""; $("#globalSearch").value = "";
  setView("study");
  // scroll the first matching section into view
  const target = STUDY.find(sec => String(sec.lec) === String(lecNum));
  if (target) {
    requestAnimationFrame(() => {
      const el = $(`.section-card[data-section="${cssEsc(target.section)}"]`);
      if (el) el.scrollIntoView({ behavior: "smooth", block: "start" });
    });
  }
}
function cssEsc(s) { return s.replace(/"/g, '\\"'); }

/* =========================================================
   STATE MUTATIONS
   ========================================================= */
function cycleStatus(id) {
  const order = { "not-started": "in-progress", "in-progress": "completed", "completed": "not-started" };
  topicStatus[id] = order[statusOf(id)];
  save(LS.topics, topicStatus);
  // update just this topic + its section bar live, plus lecture nav
  patchTopic(id);
  toast(`Marked: ${labelFor(topicStatus[id])}`);
}
function labelFor(st) {
  return st === "completed" ? "Completed" : st === "in-progress" ? "In progress" : "Not started";
}
function toggleRevision(id) {
  if (topicRev[id]) delete topicRev[id]; else topicRev[id] = true;
  save(LS.revision, topicRev);
  const btn = $(`.js-rev[data-id="${cssEsc(id)}"]`);
  if (btn) btn.classList.toggle("on", !!topicRev[id]);
  toast(topicRev[id] ? "Flagged for revision" : "Revision flag removed");
}
function markSection(name, status) {
  const sec = STUDY.find(s => s.section === name);
  if (!sec) return;
  sec.items.forEach(it => {
    if (status === "not-started") delete topicStatus[it.id];
    else topicStatus[it.id] = status;
  });
  save(LS.topics, topicStatus);
  render();
  toast(status === "completed" ? "Section marked done" : "Section reset");
}
function setQuestionState(id, set) {
  if (questState[id] === set) delete questState[id]; else questState[id] = set;
  save(LS.quest, questState);
  // live update the two buttons in this card
  const card = $(`.qcard[data-q="${cssEsc(id)}"]`);
  if (card) {
    $$(".js-qstate", card).forEach(btn => {
      const s = btn.dataset.set;
      const on = questState[id] === s;
      btn.classList.toggle("on", on);
      btn.classList.toggle("practiced", on && s === "practiced");
      btn.classList.toggle("mastered", on && s === "mastered");
    });
  }
}
function toggleQuestionRev(id) {
  if (questRev[id]) delete questRev[id]; else questRev[id] = true;
  save(LS.qrev, questRev);
  const btn = $(`.js-qrev[data-id="${cssEsc(id)}"]`);
  if (btn) btn.classList.toggle("on", !!questRev[id]);
  toast(questRev[id] ? "Question flagged" : "Flag removed");
}

/* update a single topic row + its section progress + lecture nav, no full re-render */
function patchTopic(id) {
  const el = $(`.topic[data-topic="${cssEsc(id)}"]`);
  const st = statusOf(id);
  if (el) {
    el.dataset.status = st;
    const sBtn = $(".js-status", el);
    if (sBtn) sBtn.innerHTML = statusIcon(st);
  }
  // section bar
  const sec = STUDY.find(s => s.items.some(it => it.id === id));
  if (sec) {
    const card = $(`.section-card[data-section="${cssEsc(sec.section)}"]`);
    if (card) {
      const total = sec.items.length;
      const done = sec.items.filter(it => statusOf(it.id) === "completed").length;
      const pct = total ? Math.round((done / total) * 100) : 0;
      const cnt = $(".sec-count", card); if (cnt) cnt.textContent = `${done}/${total}`;
      const bar = $(".sec-bar span", card); if (bar) bar.style.width = pct + "%";
    }
  }
  renderLectureNav();
}

/* navigate to a topic from dashboard/revision */
function gotoTopic(id) {
  const sec = STUDY.find(s => s.items.some(it => it.id === id));
  if (!sec) return;
  openSections.add(sec.section);
  activeFilter = "all"; searchTerm = ""; $("#globalSearch").value = "";
  setView("study");
  requestAnimationFrame(() => {
    const el = $(`.topic[data-topic="${cssEsc(id)}"]`);
    if (el) {
      el.classList.add("open");
      el.scrollIntoView({ behavior: "smooth", block: "center" });
      el.style.transition = "background .3s";
      el.style.background = "var(--olive-soft)";
      setTimeout(() => el.style.background = "", 1200);
    }
  });
}
function gotoQuestion(id) {
  activeFilter = "all"; searchTerm = ""; $("#globalSearch").value = "";
  setView("questions");
  requestAnimationFrame(() => {
    const card = $(`.qcard[data-q="${cssEsc(id)}"]`);
    if (card) {
      const ans = $(".q-answer", card); if (ans) ans.classList.add("open");
      card.scrollIntoView({ behavior: "smooth", block: "center" });
    }
  });
}

/* =========================================================
   TIMER (25 min focus)
   ========================================================= */
let timerSecs = 25 * 60, timerId = null;
function fmt(s) {
  const m = Math.floor(s / 60), sec = s % 60;
  return `${String(m).padStart(2, "0")}:${String(sec).padStart(2, "0")}`;
}
function paintTimer() { const d = $("#timerDisplay"); if (d) d.textContent = fmt(timerSecs); }
function timerStart() {
  if (timerId) return;
  timerId = setInterval(() => {
    timerSecs--;
    paintTimer();
    if (timerSecs <= 0) {
      clearInterval(timerId); timerId = null; timerSecs = 25 * 60; paintTimer();
      toast("Focus session done. Take a short break.");
    }
  }, 1000);
}
function timerPause() { if (timerId) { clearInterval(timerId); timerId = null; } }
function timerReset() { timerPause(); timerSecs = 25 * 60; paintTimer(); }

/* =========================================================
   THEME
   ========================================================= */
function applyTheme(theme) {
  document.body.setAttribute("data-theme", theme);
  save(LS.theme, theme, true);
}
function toggleTheme() {
  const next = document.body.getAttribute("data-theme") === "light" ? "dark" : "light";
  applyTheme(next);
}

/* =========================================================
   EXPORT / IMPORT / RESET
   ========================================================= */
function exportProgress() {
  const data = {
    app: "CN Final Exam Study Tracker",
    version: 1,
    exportedAt: new Date().toISOString(),
    topics: topicStatus, revision: topicRev,
    questions: questState, questionRev: questRev,
    notes: load(LS.notes, "", true), theme: document.body.getAttribute("data-theme")
  };
  const blob = new Blob([JSON.stringify(data, null, 2)], { type: "application/json" });
  const url = URL.createObjectURL(blob);
  const a = document.createElement("a");
  a.href = url;
  a.download = "cn-study-progress.json";
  document.body.appendChild(a); a.click(); a.remove();
  URL.revokeObjectURL(url);
  toast("Progress exported");
}
function importProgress(file) {
  const reader = new FileReader();
  reader.onload = () => {
    try {
      const d = JSON.parse(reader.result);
      if (d.topics) { topicStatus = d.topics; save(LS.topics, topicStatus); }
      if (d.revision) { topicRev = d.revision; save(LS.revision, topicRev); }
      if (d.questions) { questState = d.questions; save(LS.quest, questState); }
      if (d.questionRev) { questRev = d.questionRev; save(LS.qrev, questRev); }
      if (typeof d.notes === "string") save(LS.notes, d.notes, true);
      if (d.theme) applyTheme(d.theme);
      render();
      toast("Progress imported");
    } catch (e) { toast("Could not read that file"); }
  };
  reader.readAsText(file);
}
function resetAll() {
  if (!confirm("Reset ALL progress? This clears every status, flag, question state and note on this device. This cannot be undone.")) return;
  topicStatus = {}; topicRev = {}; questState = {}; questRev = {};
  [LS.topics, LS.revision, LS.quest, LS.qrev, LS.notes].forEach(k => localStorage.removeItem(k));
  render();
  toast("All progress reset");
}

/* =========================================================
   TOAST
   ========================================================= */
let toastTimer;
function toast(msg) {
  const el = $("#toast");
  el.textContent = msg;
  el.classList.add("show");
  clearTimeout(toastTimer);
  toastTimer = setTimeout(() => el.classList.remove("show"), 2000);
}

/* =========================================================
   SIDEBAR (mobile)
   ========================================================= */
function openSidebar() { $("#sidebar").classList.add("open"); $("#sidebarBackdrop").classList.add("show"); }
function closeSidebar() { $("#sidebar").classList.remove("open"); $("#sidebarBackdrop").classList.remove("show"); }

/* =========================================================
   SEARCH (debounced)
   ========================================================= */
let searchTimer;
function onSearch(e) {
  clearTimeout(searchTimer);
  const val = e.target.value.trim().toLowerCase();
  searchTimer = setTimeout(() => {
    searchTerm = val;
    // if searching, jump to a view that can show results
    if (searchTerm && ["dashboard", "notes"].includes(currentView)) setView("study");
    else render();
  }, 160);
}

/* =========================================================
   INIT
   ========================================================= */
function init() {
  applyTheme(load(LS.theme, "light", true) || "light");
  paintTimer();

  // nav
  $$(".nav-link").forEach(b => b.addEventListener("click", () => setView(b.dataset.view)));
  $("#lectureNav").addEventListener("click", onLectureNavClick);

  // main delegated clicks
  $("#mainView").addEventListener("click", onMainClick);

  // search + theme
  $("#globalSearch").addEventListener("input", onSearch);
  $("#themeToggle").addEventListener("click", toggleTheme);

  // timer
  $("#timerStart").addEventListener("click", timerStart);
  $("#timerPause").addEventListener("click", timerPause);
  $("#timerReset").addEventListener("click", timerReset);

  // data tools
  $("#exportBtn").addEventListener("click", exportProgress);
  $("#importBtn").addEventListener("click", () => $("#importFile").click());
  $("#importFile").addEventListener("change", e => {
    if (e.target.files[0]) importProgress(e.target.files[0]);
    e.target.value = "";
  });
  $("#resetAllBtn").addEventListener("click", resetAll);

  // mobile drawer
  $("#menuToggle").addEventListener("click", openSidebar);
  $("#sidebarBackdrop").addEventListener("click", closeSidebar);

  // restore last view
  setView(currentView);
}

document.addEventListener("DOMContentLoaded", init);
