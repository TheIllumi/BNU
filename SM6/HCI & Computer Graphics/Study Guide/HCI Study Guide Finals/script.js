/* =====================================================================
   HCI & Computer Graphics - Final Exam Study Tracker
   Logic only. All study content lives in data.js, all colours in themes.css.
   Progress is saved in the browser using localStorage.
   ===================================================================== */

(function () {
  "use strict";

  /* ---------------- constants & helpers ---------------- */
  const STORE_KEY = "hci_state_v1";
  const $ = (sel, root) => (root || document).querySelector(sel);
  const $$ = (sel, root) => Array.from((root || document).querySelectorAll(sel));
  const ico = (name) => ICONS[name] || "";
  const esc = (s) => String(s).replace(/[&<>"]/g, (c) => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;" }[c]));
  const stripHTML = (html) => { const d = document.createElement("div"); d.innerHTML = html; return d.textContent || ""; };

  /* ---------------- flatten study items ---------------- */
  const allItems = [];
  studyData.forEach((sec) => sec.items.forEach((it) => allItems.push(Object.assign({ section: sec.section, sectionId: sec.id, sectionIcon: sec.icon }, it))));
  const inItems = allItems.filter((i) => i.scope === "in");
  const inMcqs = mcqBank.filter((q) => q.scope === "in");
  const inWritten = writtenQuestions.filter((q) => q.scope === "in");
  const totalQuestions = inMcqs.length + inWritten.length;

  /* ---------------- state ---------------- */
  const defaultState = () => ({
    theme: "light",
    topics: {},     // id -> {status, reviewed, revision}
    mcqs: {},       // id -> {attempted, lastCorrect, revision}
    written: {},    // id -> {practiced, mastered, revision}
    notes: "",
    filter: "all",
    open: {},       // sectionId -> bool
    mcqDiff: "All",
    mcqShowAns: false,
    writtenTab: "scenario"
  });

  let state = defaultState();

  function load() {
    try {
      const raw = localStorage.getItem(STORE_KEY);
      if (raw) state = Object.assign(defaultState(), JSON.parse(raw));
    } catch (e) { state = defaultState(); }
  }
  function save() {
    try { localStorage.setItem(STORE_KEY, JSON.stringify(state)); } catch (e) {}
  }

  const T = (id) => state.topics[id] || (state.topics[id] = { status: "not-started", reviewed: false, revision: false });
  const Q = (id) => state.mcqs[id] || (state.mcqs[id] = { attempted: false, lastCorrect: null, revision: false });
  const W = (id) => state.written[id] || (state.written[id] = { practiced: false, mastered: false, revision: false });

  /* ---------------- progress maths ---------------- */
  function metrics() {
    const totalT = inItems.length;
    const completed = inItems.filter((i) => T(i.id).status === "completed").length;
    const inprog = inItems.filter((i) => T(i.id).status === "in-progress").length;
    const reviewed = inItems.filter((i) => T(i.id).reviewed).length;
    const revisionMarked = inItems.filter((i) => T(i.id).revision).length;

    const highItems = inItems.filter((i) => i.priority === "high");
    const highDone = highItems.filter((i) => T(i.id).status === "completed").length;

    const mcqAtt = inMcqs.filter((q) => Q(q.id).attempted).length;
    const wAtt = inWritten.filter((q) => { const s = W(q.id); return s.practiced || s.mastered; }).length;
    const attempted = mcqAtt + wAtt;

    const pTopics = totalT ? completed / totalT : 0;
    const pRev = totalT ? reviewed / totalT : 0;
    const pPrac = totalQuestions ? attempted / totalQuestions : 0;
    const pHigh = highItems.length ? highDone / highItems.length : 0;

    const w = SYLLABUS.readinessWeights;
    const readiness = Math.round(w.topics * pTopics + w.revision * pRev + w.practice * pPrac + w.highPriority * pHigh);

    return {
      totalT, completed, inprog, remaining: totalT - completed, reviewed, revisionMarked,
      highTotal: highItems.length, highDone, attempted, totalQuestions,
      pTopics, pRev, pPrac, pHigh, readiness,
      coverage: allItems.length ? Math.round((inItems.length / allItems.length) * 100) : 100
    };
  }

  /* ---------------- small UI bits ---------------- */
  function toast(msg) {
    const t = $("#toast"); t.textContent = msg; t.classList.add("show");
    clearTimeout(t._t); t._t = setTimeout(() => t.classList.remove("show"), 2000);
  }

  function tagsFor(it) {
    const out = [];
    if (it.scope === "out") out.push('<span class="tag out">Out of Syllabus</span>');
    if (it.priority === "high" && it.scope === "in") out.push('<span class="tag high">High Priority</span>');
    if (it.examLikely && it.scope === "in") out.push('<span class="tag exam">Exam Likely</span>');
    if (T(it.id).revision) out.push('<span class="tag revise">Must Revise</span>');
    if (it.difficulty === "Hard") out.push('<span class="tag diff">Difficult</span>');
    if (it.diagram) out.push('<span class="tag def">Diagram</span>');
    return out.join("");
  }

  function statusPill(st) {
    if (st === "completed") return '<span class="pill s-done">' + ico("check") + 'Completed</span>';
    if (st === "in-progress") return '<span class="pill s-prog">' + ico("dot") + 'In Progress</span>';
    return '<span class="pill s-not">' + ico("dot") + 'Not Started</span>';
  }

  function ringSVG(pct, cap) {
    const C = 364.42, off = C * (1 - pct / 100);
    return '<div class="ring"><svg viewBox="0 0 132 132"><circle class="track" cx="66" cy="66" r="58"></circle>' +
      '<circle class="fill" cx="66" cy="66" r="58" stroke-dasharray="' + C + '" stroke-dashoffset="' + off + '"></circle></svg>' +
      '<div class="center"><div class="pct">' + pct + '%</div><div class="cap">' + cap + '</div></div></div>';
  }

  /* ---------------- navigation ---------------- */
  const NAV = [
    { group: "Overview" },
    { id: "dashboard", label: "Dashboard", icon: "home", view: "dashboardView" },
    { id: "scope", label: "Exam Scope", icon: "scope", view: "scopeView" },
    { group: "Study" },
    { id: "study", label: "Study Guide", icon: "book", view: "studyView" },
    { group: "Practice" },
    { id: "mcq", label: "MCQ Practice", icon: "list", view: "mcqView" },
    { id: "written", label: "Scenario & Written", icon: "scenario", view: "scenarioView" },
    { id: "diagram", label: "Diagram Practice", icon: "diagram", view: "diagramView" },
    { group: "Revision" },
    { id: "revision", label: "Revision Mode", icon: "refresh", view: "revisionView" },
    { group: "Tools" },
    { id: "timer", label: "Focus Timer", icon: "clock", view: "timerView" },
    { id: "notes", label: "Notes", icon: "note", view: "notesView" },
    { id: "glossary", label: "Glossary", icon: "glossary", view: "glossaryView" }
  ];

  function navCount(id) {
    const m = metrics();
    if (id === "study") return m.completed + "/" + m.totalT;
    if (id === "mcq") return String(mcqBank.length);
    if (id === "written") return String(writtenQuestions.length);
    if (id === "glossary") return String(glossary.length);
    if (id === "revision") return String(m.revisionMarked);
    if (id === "diagram") return String(inItems.filter((i) => i.diagram).length);
    return "";
  }

  function renderNav() {
    const wrap = $("#navList");
    wrap.innerHTML = NAV.map((n) => {
      if (n.group) return '<div class="nav-group-label">' + n.group + "</div>";
      const c = navCount(n.id);
      return '<button class="nav-item" data-view="' + n.view + '" data-nav="' + n.id + '">' +
        ico(n.icon) + '<span style="flex:1">' + n.label + "</span>" +
        (c ? '<span class="nav-count">' + c + "</span>" : "") + "</button>";
    }).join("");
    $$(".nav-item", wrap).forEach((b) => b.addEventListener("click", () => { showView(b.dataset.view); closeMobile(); }));
  }

  let currentView = "dashboardView";
  function showView(view) {
    currentView = view;
    $$(".view").forEach((v) => v.classList.toggle("active", v.id === view));
    $$(".nav-item").forEach((b) => b.classList.toggle("active", b.dataset.view === view));
    $(".content").scrollTop = 0;
    window.scrollTo(0, 0);
    renderView(view);
  }

  function renderView(view) {
    switch (view) {
      case "dashboardView": renderDashboard(); break;
      case "scopeView": renderScope(); break;
      case "studyView": renderStudy(); break;
      case "mcqView": renderMCQ(); break;
      case "scenarioView": renderWritten(); break;
      case "diagramView": renderDiagram(); break;
      case "revisionView": renderRevision(); break;
      case "timerView": renderTimer(); break;
      case "notesView": renderNotes(); break;
      case "glossaryView": renderGlossary(); break;
      case "searchView": break;
    }
  }

  function pageHead(eyebrow, title, desc) {
    return '<div class="page-head"><div class="page-eyebrow">' + eyebrow + '</div>' +
      '<h1 class="page-title">' + title + '</h1>' +
      (desc ? '<p class="page-desc">' + desc + "</p>" : "") + "</div>";
  }

  /* ---------------- Study Next recommendation ---------------- */
  function studyNext(limit) {
    const ranked = inItems.map((it) => {
      const s = T(it.id);
      let score = 0, reason = "";
      if (s.status !== "completed" && it.priority === "high") { score = 100; reason = "High priority, not done yet"; }
      else if (s.status !== "completed" && it.difficulty === "Hard") { score = 80; reason = "Difficult topic, not done yet"; }
      else if (s.revision) { score = 70; reason = "You marked this for revision"; }
      else if (s.status === "in-progress") { score = 60; reason = "In progress, finish it off"; }
      else if (s.status !== "completed" && it.examLikely) { score = 50; reason = "Likely to appear in the exam"; }
      else if (s.status !== "completed") { score = 30; reason = "Still remaining"; }
      return { it, score, reason };
    }).filter((r) => r.score > 0).sort((a, b) => b.score - a.score);
    return ranked.slice(0, limit || 5);
  }

  /* ---------------- Dashboard ---------------- */
  function renderDashboard() {
    const m = metrics();
    const next = studyNext(5);
    const examLikelyCount = inItems.filter((i) => i.examLikely).length;

    const stat = (label, icon, value, sub) =>
      '<div class="card"><div class="stat"><div class="label">' + ico(icon) + label + "</div>" +
      '<div class="value">' + value + "</div>" + (sub ? '<div class="sub">' + sub + "</div>" : "") + "</div></div>";

    const rb = (label, weight, pct) =>
      '<div class="rb-row"><div class="rb-label">' + label + ' <small>(' + weight + '%)</small></div>' +
      "<div>" + Math.round(pct * 100) + "%</div>" +
      '<div class="rb-bar"><span style="width:' + (pct * 100) + '%"></span></div></div>';

    const nextHTML = next.length
      ? next.map((r, i) =>
        '<div class="next-item" data-goto="' + r.it.sectionId + '" data-topic="' + r.it.id + '">' +
        '<div class="next-rank">' + (i + 1) + "</div>" +
        '<div class="next-main"><div class="t">' + esc(r.it.title) + '</div><div class="r">' + r.reason + " &middot; " + r.it.section + "</div></div>" +
        ico("chev") + "</div>").join("")
      : '<div class="empty">' + ico("check") + "<div>All in-syllabus topics are complete. Great work.</div></div>";

    $("#dashboardView").innerHTML =
      pageHead("CSC-335 &middot; Sania Khalid", "Exam Readiness Dashboard",
        "Study smarter, track your progress, revise faster, and finish every in-syllabus topic before the final.") +

      '<div class="grid grid-2" style="margin-bottom:16px">' +
        '<div class="card readiness-card">' + ringSVG(m.readiness, "Readiness") +
          '<div class="readiness-breakdown">' +
            rb("Topic completion", 40, m.pTopics) +
            rb("Revision completion", 25, m.pRev) +
            rb("Practice attempted", 20, m.pPrac) +
            rb("High-priority done", 15, m.pHigh) +
          "</div>" +
        "</div>" +
        '<div class="card"><div class="stat"><div class="label">' + ico("target") + 'Syllabus Coverage</div>' +
          '<div class="value">' + m.coverage + '%</div>' +
          '<div class="sub">' + inItems.length + " of " + allItems.length + " topics are in the final exam scope</div>" +
          '<div class="bar accent" style="margin-top:12px"><span style="width:' + m.coverage + '%"></span></div>' +
          '<div class="sub" style="margin-top:10px">Overall progress: <b>' + (m.totalT ? Math.round(m.completed / m.totalT * 100) : 0) + "%</b></div>" +
          '<div class="bar done" style="margin-top:6px"><span style="width:' + (m.totalT ? m.completed / m.totalT * 100 : 0) + '%"></span></div>' +
        "</div></div>" +
      "</div>" +

      '<div class="grid grid-4" style="margin-bottom:16px">' +
        stat("Completed", "check", m.completed, "of " + m.totalT + " topics") +
        stat("Remaining", "book", m.remaining, m.inprog + " in progress") +
        stat("For Revision", "bookmark", m.revisionMarked, "marked by you") +
        stat("Practice Done", "list", m.attempted, "of " + m.totalQuestions + " questions") +
      "</div>" +

      '<div class="grid grid-2">' +
        '<div class="card"><div class="label" style="margin-bottom:6px;display:flex;align-items:center;gap:7px;font-weight:700;font-size:13px">' + ico("star") + "Study Next</div>" +
          '<div class="sub" style="margin-bottom:6px">Recommended order based on priority, difficulty and revision.</div>' + nextHTML + "</div>" +
        '<div class="card"><div class="label" style="margin-bottom:10px;display:flex;align-items:center;gap:7px;font-weight:700;font-size:13px">' + ico("scope") + "Topics in the Finals</div>" +
          '<div class="grid grid-2" style="gap:12px">' +
            '<div class="stat"><div class="value" style="font-size:24px">' + inItems.filter((i) => i.priority === "high").length + '</div><div class="sub">High priority</div></div>' +
            '<div class="stat"><div class="value" style="font-size:24px">' + examLikelyCount + '</div><div class="sub">Exam likely</div></div>' +
            '<div class="stat"><div class="value" style="font-size:24px">' + inMcqs.length + '</div><div class="sub">MCQs in scope</div></div>' +
            '<div class="stat"><div class="value" style="font-size:24px">' + inWritten.length + '</div><div class="sub">Written Qs in scope</div></div>' +
          "</div>" +
          '<div class="section-note" style="margin-top:14px">3 topics are out of syllabus and are excluded from your readiness score: A/B Testing, Wizard of Oz, and Micro-Usability Testing.</div>' +
        "</div>" +
      "</div>";

    $$("[data-goto]", $("#dashboardView")).forEach((el) => el.addEventListener("click", () => {
      state.open[el.dataset.goto] = true; save();
      showView("studyView");
      setTimeout(() => {
        const node = $('[data-section="' + el.dataset.goto + '"]');
        if (node) node.scrollIntoView({ behavior: "smooth", block: "start" });
      }, 60);
    }));
  }

  /* ---------------- Exam Scope ---------------- */
  function renderScope() {
    const m = metrics();
    const inc = SYLLABUS.included.map((x) => '<li>' + ico("check") + esc(x) + "</li>").join("") +
      studyData.filter((s) => s.scope === "in").map((s) => '<li>' + ico("check") + esc(s.section) + "</li>").join("");
    const exc = SYLLABUS.excluded.map((x) => '<li>' + ico("x") + esc(x) + "</li>").join("");

    $("#scopeView").innerHTML =
      pageHead("Instructor: Sania Khalid", "Exam Scope &amp; Syllabus Coverage",
        "What the final exam covers and what is left out. Out-of-syllabus topics are excluded from your readiness score, revision mode and recommendations.") +

      '<div class="card" style="margin-bottom:16px"><div class="label" style="font-weight:700;font-size:13px;margin-bottom:10px;display:flex;gap:7px;align-items:center">' + ico("target") + "Syllabus Coverage Tracker</div>" +
        '<div style="display:flex;justify-content:space-between;font-size:13px;margin-bottom:6px"><span>' + inItems.length + " topics in scope</span><span><b>" + m.coverage + "%</b> of all material</span></div>" +
        '<div class="bar accent"><span style="width:' + m.coverage + '%"></span></div></div>' +

      '<div class="scope-grid">' +
        '<div class="card scope-col"><h4>' + ico("check") + "Included in the Final</h4><ul class=\"scope-list inc\">" + inc + "</ul></div>" +
        '<div class="card scope-col"><h4>' + ico("x") + "Excluded (Optional Reading)</h4><ul class=\"scope-list exc\">" + exc +
          '<li style="border:none;color:var(--text-muted);font-size:12px;margin-top:6px">These appear in the study guide and MCQ bank but are clearly labelled and never counted in your score.</li></ul></div>' +
      "</div>";
  }

  /* ---------------- Study Guide ---------------- */
  const FILTERS = [
    ["all", "All"], ["completed", "Completed"], ["remaining", "Remaining"], ["in-progress", "In Progress"],
    ["revision", "Marked for Revision"], ["high", "High Priority"], ["difficult", "Difficult"], ["diagram", "Diagram"]
  ];

  function topicMatchesFilter(it) {
    const s = T(it.id), f = state.filter;
    switch (f) {
      case "completed": return s.status === "completed";
      case "remaining": return s.status !== "completed";
      case "in-progress": return s.status === "in-progress";
      case "revision": return s.revision;
      case "high": return it.priority === "high";
      case "difficult": return it.difficulty === "Hard";
      case "diagram": return !!it.diagram;
      default: return true;
    }
  }

  function topicHTML(it) {
    const s = T(it.id);
    const cls = "topic" + (s.status === "completed" ? " done" : s.status === "in-progress" ? " prog" : "");
    return '<div class="' + cls + '" data-topic="' + it.id + '">' +
      '<div class="topic-head">' +
        '<button class="topic-check" data-act="cycle" title="Click to change status">' + (s.status === "completed" ? ico("check") : "") + "</button>" +
        '<div class="topic-main" data-act="expand">' +
          '<div class="topic-title">' + esc(it.title) + "</div>" +
          '<div class="topic-tags tags">' + tagsFor(it) + statusPill(s.status) + "</div>" +
        "</div>" +
      "</div>" +
      '<div class="topic-body">' + it.content +
        '<div class="topic-actions">' +
          '<button class="btn tiny" data-act="reviewed">' + ico("eye") + (s.reviewed ? "Reviewed" : "Mark reviewed") + "</button>" +
          '<button class="btn tiny ' + (s.revision ? "active-toggle" : "") + '" data-act="revision">' + ico("bookmark") + (s.revision ? "For revision" : "Mark for revision") + "</button>" +
        "</div>" +
      "</div>" +
    "</div>";
  }

  function sectionHTML(sec) {
    const items = sec.items;
    const visible = items.filter(topicMatchesFilter);
    if (state.filter !== "all" && visible.length === 0) return "";
    const open = !!state.open[sec.id];
    const inScopeItems = items.filter((i) => i.scope === "in");
    const done = inScopeItems.filter((i) => T(i.id).status === "completed").length;
    const frac = inScopeItems.length ? done + "/" + inScopeItems.length : "optional";
    const pct = inScopeItems.length ? done / inScopeItems.length * 100 : 0;
    const outCls = sec.scope === "out" ? " out-of-scope" : "";

    return '<div class="section' + (open ? " open" : "") + outCls + '" data-section="' + sec.id + '">' +
      '<div class="section-head" data-act="toggle">' +
        '<span class="sec-chev">' + ico("chev") + "</span>" +
        ico(sec.icon) +
        '<span class="sec-title">' + esc(sec.section) + (sec.scope === "out" ? ' <span class="tag out" style="vertical-align:middle">Out of Syllabus</span>' : "") + "</span>" +
        '<div class="sec-meta"><span class="sec-frac">' + frac + '</span><div class="bar sec-minibar"><span style="width:' + pct + '%"></span></div></div>' +
      "</div>" +
      '<div class="section-body">' +
        '<div class="section-note">' + esc(sec.blurb) + "</div>" +
        (sec.scope === "in" ? '<div class="sec-actions"><button class="btn tiny" data-act="all-done">' + ico("check") + 'Mark all done</button>' +
          '<button class="btn tiny ghost" data-act="reset-sec">' + ico("refresh") + "Reset section</button></div>" : "") +
        visible.map(topicHTML).join("") +
      "</div>" +
    "</div>";
  }

  function renderStudy() {
    const chips = FILTERS.map(([k, label]) =>
      '<button class="chip ' + (state.filter === k ? "active" : "") + '" data-filter="' + k + '">' + label + "</button>").join("");

    $("#studyView").innerHTML =
      pageHead("Study Guide", "All Topics",
        "Read each topic, then click the circle to move it from Not Started to In Progress to Completed. Use the tags and filters to focus your time.") +
      '<div class="toolbar">' + chips + "</div>" +
      '<div id="sectionList">' + studyData.map(sectionHTML).join("") + "</div>";

    $$("[data-filter]", $("#studyView")).forEach((c) => c.addEventListener("click", () => { state.filter = c.dataset.filter; save(); renderStudy(); }));
    bindSectionEvents($("#studyView"));
  }

  function bindSectionEvents(root) {
    $$(".section", root).forEach((secEl) => {
      const secId = secEl.dataset.section;
      const head = $(".section-head", secEl);
      if (head) head.addEventListener("click", (e) => {
        if (e.target.closest("[data-act='all-done']") || e.target.closest("[data-act='reset-sec']")) return;
        state.open[secId] = !state.open[secId]; save(); secEl.classList.toggle("open");
      });
      const allBtn = $("[data-act='all-done']", secEl);
      if (allBtn) allBtn.addEventListener("click", (e) => {
        e.stopPropagation();
        studyData.find((s) => s.id === secId).items.forEach((it) => { if (it.scope === "in") T(it.id).status = "completed"; });
        save(); toast("Section marked complete"); renderView(currentView); refreshChrome();
      });
      const resetBtn = $("[data-act='reset-sec']", secEl);
      if (resetBtn) resetBtn.addEventListener("click", (e) => {
        e.stopPropagation();
        studyData.find((s) => s.id === secId).items.forEach((it) => { const t = T(it.id); t.status = "not-started"; t.reviewed = false; });
        save(); toast("Section reset"); renderView(currentView); refreshChrome();
      });
    });

    $$(".topic", root).forEach((tp) => {
      const id = tp.dataset.topic;
      const check = $("[data-act='cycle']", tp);
      if (check) check.addEventListener("click", (e) => {
        e.stopPropagation();
        const t = T(id);
        t.status = t.status === "not-started" ? "in-progress" : t.status === "in-progress" ? "completed" : "not-started";
        save(); renderView(currentView); refreshChrome();
      });
      const main = $("[data-act='expand']", tp);
      if (main) main.addEventListener("click", () => tp.classList.toggle("expanded"));
      const rev = $("[data-act='reviewed']", tp);
      if (rev) rev.addEventListener("click", (e) => { e.stopPropagation(); const t = T(id); t.reviewed = !t.reviewed; save(); toast(t.reviewed ? "Marked reviewed" : "Review removed"); keepOpenRerender(tp); });
      const rv = $("[data-act='revision']", tp);
      if (rv) rv.addEventListener("click", (e) => { e.stopPropagation(); const t = T(id); t.revision = !t.revision; save(); toast(t.revision ? "Added to revision" : "Removed from revision"); keepOpenRerender(tp); });
    });
  }

  // re-render current view but keep the clicked topic expanded
  function keepOpenRerender(topicEl) {
    const id = topicEl.dataset.topic;
    renderView(currentView); refreshChrome();
    const again = $('.topic[data-topic="' + id + '"]');
    if (again) again.classList.add("expanded");
  }

  /* ---------------- MCQ ---------------- */
  function renderMCQ() {
    const diffs = ["All", "Very Easy", "Easy", "Medium", "Hard", "Very Hard", "Nightmare"];
    const chips = diffs.map((d) => '<button class="chip ' + (state.mcqDiff === d ? "active" : "") + '" data-diff="' + d + '">' + d + "</button>").join("");
    const list = mcqBank.filter((q) => state.mcqDiff === "All" || q.difficulty === state.mcqDiff);

    $("#mcqView").innerHTML =
      pageHead("Practice &middot; " + mcqBank.length + " MCQs", "Multiple Choice Questions",
        "Tap an option to check it. Out-of-syllabus questions are labelled and never count toward your readiness score.") +
      '<div class="toolbar">' + chips +
        '<button class="btn tiny ' + (state.mcqShowAns ? "done-toggle" : "") + '" id="toggleAns">' + ico("eye") + (state.mcqShowAns ? "Hiding answers off" : "Show all answers") + "</button>" +
      "</div>" +
      '<div id="mcqList">' + list.map(mcqCard).join("") + "</div>";

    $$("[data-diff]", $("#mcqView")).forEach((c) => c.addEventListener("click", () => { state.mcqDiff = c.dataset.diff; save(); renderMCQ(); }));
    $("#toggleAns").addEventListener("click", () => { state.mcqShowAns = !state.mcqShowAns; save(); renderMCQ(); });
    bindMCQ($("#mcqView"));
  }

  function mcqCard(q) {
    const s = Q(q.id);
    const keys = ["A", "B", "C", "D"];
    const reveal = state.mcqShowAns || s.attempted;
    const opts = q.options.map((o, i) => {
      const k = keys[i];
      let cls = "opt";
      if (reveal && k === q.answer) cls += " correct";
      if (reveal && s.lastCorrect === false && s.picked === k && k !== q.answer) cls += " wrong";
      return '<button class="' + cls + '" data-pick="' + k + '"><span class="opt-key">' + k + '</span><span>' + esc(o) + "</span></button>";
    }).join("");
    return '<div class="q-card" data-mcq="' + q.id + '">' +
      '<div class="q-top"><span class="q-num">Q' + q.id.replace("mcq", "") + "</span>" +
        '<span class="q-text">' + esc(q.q) + "</span></div>" +
      '<div class="q-opts">' + opts + "</div>" +
      '<div class="q-foot">' +
        '<span class="tag diff">' + q.difficulty + "</span>" +
        '<span class="tag def">' + esc(q.topic) + "</span>" +
        (q.scope === "out" ? '<span class="tag out">Out of Syllabus</span>' : "") +
        (reveal ? '<span class="tag exam">Answer: ' + q.answer + "</span>" : "") +
        '<button class="btn tiny ' + (s.revision ? "active-toggle" : "") + '" data-act="rev">' + ico("bookmark") + (s.revision ? "For revision" : "Revise") + "</button>" +
      "</div></div>";
  }

  function bindMCQ(root) {
    $$(".q-card", root).forEach((card) => {
      const id = card.dataset.mcq;
      const q = mcqBank.find((x) => x.id === id);
      $$("[data-pick]", card).forEach((opt) => opt.addEventListener("click", () => {
        const s = Q(id); s.attempted = true; s.picked = opt.dataset.pick; s.lastCorrect = opt.dataset.pick === q.answer;
        save(); toast(s.lastCorrect ? "Correct" : "Answer is " + q.answer); renderMCQ(); refreshChrome();
      }));
      const rev = $("[data-act='rev']", card);
      if (rev) rev.addEventListener("click", () => { const s = Q(id); s.revision = !s.revision; save(); renderMCQ(); });
    });
  }

  /* ---------------- Written questions ---------------- */
  const WTYPES = [
    ["scenario", "Scenario"], ["conceptual", "Conceptual"], ["diagram", "Diagram"],
    ["design-eval", "Design Evaluation"], ["case-study", "Case Study"], ["long", "Long Questions"]
  ];

  function renderWritten() {
    const tabs = WTYPES.map(([k, label]) => {
      const n = writtenQuestions.filter((q) => q.type === k).length;
      return '<button class="tab ' + (state.writtenTab === k ? "active" : "") + '" data-tab="' + k + '">' + label + " (" + n + ")</button>";
    }).join("");
    const list = writtenQuestions.filter((q) => q.type === state.writtenTab);

    $("#scenarioView").innerHTML =
      pageHead("Practice &middot; Written", "Scenario &amp; Written Questions",
        "Past-paper and predicted questions with model answers in simple English. Try to answer first, then reveal the model answer.") +
      '<div class="tabs">' + tabs + "</div>" +
      '<div id="wList">' + (list.length ? list.map(writtenCard).join("") : '<div class="empty">' + ico("book") + "<div>No questions in this group.</div></div>") + "</div>";

    $$("[data-tab]", $("#scenarioView")).forEach((t) => t.addEventListener("click", () => { state.writtenTab = t.dataset.tab; save(); renderWritten(); }));
    bindWritten($("#scenarioView"));
  }

  function writtenCard(q) {
    const s = W(q.id);
    return '<div class="q-card" data-w="' + q.id + '">' +
      '<div class="q-top"><span class="q-num">' + q.marks + "m</span>" +
        '<span class="q-text">' + esc(q.prompt) + "</span></div>" +
      '<div class="tags" style="margin:4px 0 2px">' + (q.tags || []).map((t) => '<span class="tag def">' + esc(t) + "</span>").join("") + "</div>" +
      '<div class="q-answer" id="ans-' + q.id + '"><h6>Model Answer</h6>' + q.answer + "</div>" +
      '<div class="q-foot">' +
        '<button class="btn tiny" data-act="show">' + ico("eye") + "Show answer</button>" +
        '<button class="btn tiny ' + (s.practiced ? "active-toggle" : "") + '" data-act="practiced">' + ico("check") + (s.practiced ? "Practiced" : "Mark practiced") + "</button>" +
        '<button class="btn tiny ' + (s.mastered ? "done-toggle" : "") + '" data-act="mastered">' + ico("star") + (s.mastered ? "Mastered" : "Mark mastered") + "</button>" +
        '<button class="btn tiny ' + (s.revision ? "active-toggle" : "") + '" data-act="rev">' + ico("bookmark") + (s.revision ? "For revision" : "Revise") + "</button>" +
      "</div></div>";
  }

  function bindWritten(root) {
    $$(".q-card", root).forEach((card) => {
      const id = card.dataset.w;
      const show = $("[data-act='show']", card);
      if (show) show.addEventListener("click", () => {
        const a = $("#ans-" + id), open = a.classList.toggle("show");
        show.innerHTML = ico("eye") + (open ? "Hide answer" : "Show answer");
      });
      const map = { practiced: "practiced", mastered: "mastered", rev: "revision" };
      ["practiced", "mastered", "rev"].forEach((act) => {
        const b = $("[data-act='" + act + "']", card);
        if (b) b.addEventListener("click", () => { const s = W(id); const key = map[act]; s[key] = !s[key]; save(); renderWritten(); refreshChrome(); });
      });
    });
  }

  /* ---------------- Diagram Practice ---------------- */
  function renderDiagram() {
    const diagItems = inItems.filter((i) => i.diagram);
    const diagQs = inWritten.filter((q) => q.type === "diagram");

    $("#diagramView").innerHTML =
      pageHead("Practice &middot; Diagrams", "Diagram Practice",
        "Topics you should be able to draw and label from memory, plus diagram-based questions. Practise sketching each on paper.") +
      '<div class="card" style="margin-bottom:16px"><div class="label" style="font-weight:700;font-size:13px;margin-bottom:6px">Draw these from memory</div>' +
        '<div class="tags">' + diagItems.map((i) => '<span class="tag def" data-jump="' + i.sectionId + '">' + esc(i.title) + "</span>").join("") + "</div></div>" +
      '<div id="wList">' + diagQs.map(writtenCard).join("") + "</div>";

    $$("[data-jump]", $("#diagramView")).forEach((t) => t.addEventListener("click", () => { state.open[t.dataset.jump] = true; save(); showView("studyView"); }));
    bindWritten($("#diagramView"));
  }

  /* ---------------- Revision Mode ---------------- */
  function renderRevision() {
    const markedTopics = inItems.filter((i) => T(i.id).revision);
    const highRemaining = inItems.filter((i) => i.priority === "high" && T(i.id).status !== "completed");
    const remaining = inItems.filter((i) => T(i.id).status !== "completed");
    const examQs = inWritten.filter((q) => (q.tags || []).indexOf("High Priority") > -1);
    const revQs = inWritten.filter((q) => W(q.id).revision).concat(inMcqs.filter((q) => Q(q.id).revision).map((q) => q));
    const keyDefs = glossary.slice(0, 14);

    const topicChips = (arr) => arr.length
      ? '<div class="tags">' + arr.map((i) => '<span class="tag ' + (T(i.id).status === "completed" ? "exam" : "high") + '" data-jump="' + i.sectionId + '">' + esc(i.title) + "</span>").join("") + "</div>"
      : '<div class="sub" style="color:var(--text-muted)">Nothing here right now.</div>';

    const block = (title, icon, body) =>
      '<div class="card" style="margin-bottom:14px"><div class="label" style="font-weight:700;font-size:13px;margin-bottom:10px;display:flex;gap:7px;align-items:center">' + ico(icon) + title + "</div>" + body + "</div>";

    $("#revisionView").innerHTML =
      pageHead("Last-Minute Revision", "HCI Finals Revision Mode",
        "Only in-syllabus material: high-priority topics, items you marked, remaining topics, key definitions and exam-likely questions.") +
      block("High-priority topics still to finish", "target", topicChips(highRemaining)) +
      block("Marked for revision", "bookmark", topicChips(markedTopics)) +
      block("Topics still remaining", "book", topicChips(remaining)) +
      block("Key definitions to memorise", "glossary",
        keyDefs.map((g) => '<div style="padding:7px 0;border-bottom:1px solid var(--border-soft)"><b style="font-size:13.5px">' + esc(g.term) + "</b><div class=\"sub\">" + esc(g.meaning) + "</div></div>").join("")) +
      block("Exam-likely written questions", "scenario",
        examQs.slice(0, 8).map((q) => '<div class="next-item" data-wgo="' + q.type + '"><div class="next-rank">' + q.marks + 'm</div><div class="next-main"><div class="t" style="font-weight:600">' + esc(q.prompt.slice(0, 90)) + "...</div><div class=\"r\">" + q.type + "</div></div></div>").join("")) +
      (revQs.length ? block("Questions you marked for revision", "refresh",
        revQs.map((q) => '<div class="sub" style="padding:5px 0;border-bottom:1px solid var(--border-soft)">' + esc(stripHTML(q.q || q.prompt).slice(0, 110)) + "...</div>").join("")) : "");

    $$("[data-jump]", $("#revisionView")).forEach((t) => t.addEventListener("click", () => { state.open[t.dataset.jump] = true; save(); showView("studyView"); }));
    $$("[data-wgo]", $("#revisionView")).forEach((t) => t.addEventListener("click", () => { state.writtenTab = t.dataset.wgo; save(); showView("scenarioView"); }));
  }

  /* ---------------- Focus Timer ---------------- */
  const timer = { total: 25 * 60, left: 25 * 60, running: false, iv: null };
  const TC = 565.48; // 2*pi*90

  function fmt(s) { const m = Math.floor(s / 60), x = s % 60; return (m < 10 ? "0" : "") + m + ":" + (x < 10 ? "0" : "") + x; }

  function renderTimer() {
    const off = TC * (1 - timer.left / timer.total);
    $("#timerView").innerHTML =
      pageHead("Tools", "Focus Timer", "A simple 25-minute focus timer for one study sprint. Start, take a topic, and work until the ring empties.") +
      '<div class="card timer-box" style="max-width:420px;margin:0 auto">' +
        '<div class="timer-ring"><svg width="200" height="200" viewBox="0 0 200 200">' +
          '<circle class="t-track" cx="100" cy="100" r="90"></circle>' +
          '<circle class="t-fill" id="tFill" cx="100" cy="100" r="90" stroke-dasharray="' + TC + '" stroke-dashoffset="' + off + '"></circle></svg>' +
          '<div class="t-center"><div class="timer-display" style="font-size:34px" id="tText">' + fmt(timer.left) + "</div></div></div>" +
        '<div class="timer-controls">' +
          '<button class="btn primary" id="tStart">' + ico(timer.running ? "pause" : "play") + (timer.running ? "Pause" : "Start") + "</button>" +
          '<button class="btn" id="tReset">' + ico("refresh") + "Reset</button>" +
        "</div></div>";
    $("#tStart").addEventListener("click", toggleTimer);
    $("#tReset").addEventListener("click", resetTimer);
  }

  function tickUI() {
    const tText = $("#tText"); if (tText) tText.textContent = fmt(timer.left);
    const tFill = $("#tFill"); if (tFill) tFill.setAttribute("stroke-dashoffset", TC * (1 - timer.left / timer.total));
    const mini = $("#miniTimer");
    mini.innerHTML = timer.running ? '<span class="mono" style="font-size:12px;font-weight:700">' + fmt(timer.left) + "</span>" : ico("clock");
  }
  function toggleTimer() {
    timer.running = !timer.running;
    if (timer.running) {
      timer.iv = setInterval(() => {
        timer.left--; if (timer.left <= 0) { timer.left = 0; stopTimer(); toast("Time is up. Take a short break."); }
        tickUI();
      }, 1000);
    } else clearInterval(timer.iv);
    if (currentView === "timerView") renderTimer();
    tickUI();
  }
  function stopTimer() { timer.running = false; clearInterval(timer.iv); if (currentView === "timerView") renderTimer(); tickUI(); }
  function resetTimer() { stopTimer(); timer.left = timer.total; if (currentView === "timerView") renderTimer(); tickUI(); }

  /* ---------------- Notes ---------------- */
  function renderNotes() {
    $("#notesView").innerHTML =
      pageHead("Tools", "My Notes", "Quick notes saved in your browser. Use it for things to revise, questions to ask, or steps to redo.") +
      '<textarea class="notes-area" id="notesArea" placeholder="Type anything you want to remember...">' + esc(state.notes) + "</textarea>" +
      '<div class="sub" style="margin-top:8px;color:var(--text-muted)">Saved automatically as you type.</div>';
    const area = $("#notesArea");
    area.addEventListener("input", () => { state.notes = area.value; save(); });
  }

  /* ---------------- Glossary ---------------- */
  function renderGlossary(query) {
    const q = (query || "").toLowerCase();
    const list = glossary.filter((g) => !q || g.term.toLowerCase().includes(q) || g.meaning.toLowerCase().includes(q));
    $("#glossaryView").innerHTML =
      pageHead("Appendix &middot; " + glossary.length + " terms", "Glossary",
        "Important HCI terms in simple English, with why each one matters.") +
      '<div class="toolbar"><div class="search-wrap" style="max-width:320px">' + '<span class="s-ico">' + ico("search") + "</span>" +
        '<input type="text" id="glossSearch" placeholder="Filter terms..." value="' + esc(query || "") + '" /></div></div>' +
      '<div id="glossList">' + (list.length ? list.map((g) =>
        '<div class="gloss-item"><div class="gloss-term">' + esc(g.term) + '</div><div class="gloss-mean">' + esc(g.meaning) + '</div><div class="gloss-why"><b>Why it matters:</b> ' + esc(g.why) + "</div></div>").join("")
        : '<div class="empty">' + ico("search") + "<div>No terms match.</div></div>") + "</div>";
    const gs = $("#glossSearch");
    gs.addEventListener("input", () => { const v = gs.value; renderGlossary(v); const el = $("#glossSearch"); el.focus(); el.setSelectionRange(v.length, v.length); });
  }

  /* ---------------- Global search ---------------- */
  function globalSearch(query) {
    const q = query.trim().toLowerCase();
    if (!q) { showView("dashboardView"); return; }
    const res = [];
    inItems.concat(allItems.filter((i) => i.scope === "out")).forEach((it) => {
      if (it.title.toLowerCase().includes(q) || stripHTML(it.content).toLowerCase().includes(q))
        res.push({ type: "Topic", title: it.title, snip: stripHTML(it.content).slice(0, 120), go: () => { state.open[it.sectionId] = true; save(); showView("studyView"); } });
    });
    mcqBank.forEach((m) => { if (m.q.toLowerCase().includes(q)) res.push({ type: "MCQ &middot; " + m.difficulty, title: m.q, snip: "Topic: " + m.topic, go: () => { state.mcqDiff = "All"; save(); showView("mcqView"); } }); });
    writtenQuestions.forEach((w) => { if (w.prompt.toLowerCase().includes(q)) res.push({ type: w.type, title: w.prompt.slice(0, 80) + "...", snip: w.marks + " marks", go: () => { state.writtenTab = w.type; save(); showView("scenarioView"); } }); });
    glossary.forEach((g) => { if (g.term.toLowerCase().includes(q) || g.meaning.toLowerCase().includes(q)) res.push({ type: "Glossary", title: g.term, snip: g.meaning, go: () => showView("glossaryView") }); });

    $("#searchView").innerHTML =
      pageHead("Search", "Results for &ldquo;" + esc(query) + "&rdquo;", res.length + " match" + (res.length === 1 ? "" : "es") + " across topics, questions and glossary.") +
      (res.length ? res.slice(0, 40).map((r, i) =>
        '<div class="search-result" data-i="' + i + '"><div class="sr-type">' + r.type + '</div><div class="sr-title">' + esc(r.title) + '</div><div class="sr-snip">' + esc(r.snip) + "</div></div>").join("")
        : '<div class="empty">' + ico("search") + "<div>Nothing found. Try a different word.</div></div>");
    showView("searchView");
    $$(".search-result", $("#searchView")).forEach((el) => el.addEventListener("click", () => res[+el.dataset.i].go()));
  }

  /* ---------------- export / import / reset ---------------- */
  function exportJSON() {
    const blob = new Blob([JSON.stringify(state, null, 2)], { type: "application/json" });
    const a = document.createElement("a");
    a.href = URL.createObjectURL(blob);
    a.download = "hci-study-progress.json";
    a.click(); URL.revokeObjectURL(a.href); toast("Progress exported");
  }
  function importJSON(file) {
    const r = new FileReader();
    r.onload = () => {
      try { state = Object.assign(defaultState(), JSON.parse(r.result)); save(); applyTheme(); renderNav(); renderView(currentView); refreshChrome(); toast("Progress loaded"); }
      catch (e) { toast("That file could not be read"); }
    };
    r.readAsText(file);
  }
  function resetAll() {
    if (!confirm("Clear all progress, notes and marks? This cannot be undone.")) return;
    state = defaultState(); save(); applyTheme(); renderNav(); showView("dashboardView"); refreshChrome(); toast("Everything reset");
  }

  /* ---------------- theme & chrome ---------------- */
  function applyTheme() {
    document.documentElement.setAttribute("data-theme", state.theme);
    const tt = $("#themeToggle");
    if (tt) tt.innerHTML = state.theme === "dark" ? ico("sun") : ico("moon");
  }
  function refreshChrome() { renderNav(); $$(".nav-item").forEach((b) => b.classList.toggle("active", b.dataset.view === currentView)); }

  function openMobile() { $("#sidebar").classList.add("open"); $("#overlay").classList.add("show"); }
  function closeMobile() { $("#sidebar").classList.remove("open"); $("#overlay").classList.remove("show"); }

  /* ---------------- init ---------------- */
  function init() {
    load();
    // static chrome icons
    $("#brandMark").innerHTML = ico("brain");
    $("#searchIco").innerHTML = ico("search");
    $("#menuBtn").innerHTML = ico("menu");
    $("#exportBtn").innerHTML = ico("download") + "Export";
    $("#importBtn").innerHTML = ico("upload") + "Import";
    $("#resetBtn").innerHTML = ico("trash") + "Reset";
    $("#exportBtn").className = "btn tiny ghost";
    $("#importBtn").className = "btn tiny ghost";
    $("#resetBtn").className = "btn tiny ghost";
    applyTheme();
    tickUI();
    renderNav();
    showView("dashboardView");

    // events
    $("#themeToggle").addEventListener("click", () => { state.theme = state.theme === "dark" ? "light" : "dark"; save(); applyTheme(); });
    $("#miniTimer").addEventListener("click", () => showView("timerView"));
    $("#menuBtn").addEventListener("click", openMobile);
    $("#overlay").addEventListener("click", closeMobile);
    $("#exportBtn").addEventListener("click", exportJSON);
    $("#importBtn").addEventListener("click", () => $("#importFile").click());
    $("#importFile").addEventListener("change", (e) => { if (e.target.files[0]) importJSON(e.target.files[0]); });
    $("#resetBtn").addEventListener("click", resetAll);

    let searchDebounce;
    $("#globalSearch").addEventListener("input", (e) => {
      clearTimeout(searchDebounce);
      const v = e.target.value;
      searchDebounce = setTimeout(() => { if (v.trim()) globalSearch(v); else if (currentView === "searchView") showView("dashboardView"); }, 220);
    });
  }

  if (document.readyState === "loading") document.addEventListener("DOMContentLoaded", init);
  else init();
})();
