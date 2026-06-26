# CSC-335: HCI & Computer Graphics
## Lecture 2: Human Cognition in HCI

---

## Introduction

**Why do smart people still press the wrong button in apps?**

**Why do users blame themselves instead of bad design?**

Most user errors are **design problems**, not intelligence problems.

---

## Design Must Match How Humans

Design must align with the way humans naturally:

- Perceive
- Attend
- Remember
- Decide
- Act
- Evaluate

---

## 01 Perception

**Definition:** How humans interpret sensory input.

- Perception is NOT the same as seeing.
- Context comes into play.
- We do not see reality — we see **interpreted reality**.

### Key Perception Principles

#### 1. Pattern Recognition

- Humans recognize patterns faster than reading text.
- Icons are recognized faster than labels.
- Logos are recognized faster than names.

#### 2. Gestalt Principles

Humans group visually by:

- **Proximity** — elements that are close together are perceived as a group.
- **Similarity** — elements that look alike are perceived as related.
- **Closure** — the mind fills in gaps to perceive a complete shape.
- **Continuation** — the eye follows paths, lines, or curves.
- **Figure/Ground** — the mind separates a foreground element from the background.
- **Pragnanz** — complex images are reduced to the simplest possible form.

#### 3. Contrast & Visibility

- Gray text on gray background vs. high contrast.
- Tiny clickable links are a visibility problem.
- Visual hierarchy must be established.
- Clear affordances are necessary so users know what is interactive.

---

## 02 Memory

### Types of Memory

#### Short-Term / Working Memory

- Capacity: approximately 4 to 7 items.
- Duration: seconds.
- Easily overloaded.

#### Long-Term Memory

- Stores: Knowledge, Skills, Habits.
- Persistent, not easily lost.

#### Recognition

- Identifying something when it is presented.
- Examples in UI: choose from a menu, select an icon, pick from a list.
- Easier for users than recall.

#### Recall

- Retrieving information from memory without external cues.
- Examples: type a command, remember syntax, memorize steps.
- Harder for users — requires more cognitive effort.

### Discussion: Why are command-line interfaces harder for beginners?

**Answer:** Recall burden, syntax memory requirements, no recognition support.

### Discussion: Which is the better option?

- Enter error code manually (requires recall)
- Select error type from a list (requires recognition)

**Better option:** Selecting from a list — it leverages recognition over recall.

---

## 03 Attention

**Core idea:** Humans have limited cognitive focus. They cannot process everything — they filter.

### Types of Attention

#### Selective Attention

- Focus on one thing at a time.
- Example: reading text while ignoring background ads.

#### Divided Attention

- Multitasking leads to performance drops.
- Examples:
  - Driving while texting.
  - Coding while chatting.

### Discussion: Design Implications of Attention

Bad design examples that violate attention principles:

- Too many popups.
- Multiple competing alerts.
- Simultaneous animations.

---

## 04 Cognitive Load

**Definition:** The total mental effort required to complete a task.

### Types of Cognitive Load

#### Intrinsic Load

- Comes from the task complexity itself.
- Example: learning recursion.
- Cannot be eliminated — it is inherent to the task.

#### Extraneous Load

- Added by bad design.
- Examples: confusing layout, poor labeling.
- This is the load designers are responsible for reducing.

### Discussion: Why do checkout flows use multiple pages instead of one long form?

**Answer:** To reduce cognitive load. Breaking a complex task into smaller steps reduces the amount of information held in working memory at once, making the process feel manageable and reducing errors.

---

## Mental Models vs System Models

### Definitions

- **Mental Model:** The user's internal understanding of how a system works.
- **System Model:** The actual internal logic of the system.

### When They Do Not Match — Errors Occur

**Example 1:**
- User thinks: Trash deletes permanently.
- System behavior: Moves to recycle bin.

**Example 2:**
- User drags a file out of a folder expecting to copy it.
- System moves it instead.

### Discussion: Why was the desktop metaphor so successful historically?

**Answer:** Because the desktop metaphor (files, folders, trash can) aligned directly with users' pre-existing mental models from physical office environments. It required no new mental model — users mapped familiar real-world concepts onto the digital interface.

---

## 05 Error Patterns

### Types of Errors

#### Slips (Execution Errors)

- The user intends the correct action but executes the wrong one due to attention failure.
- Examples:
  - Clicking Delete instead of Save.
  - Typo while typing a password.

#### Mistakes (Decision Errors)

- A wrong plan is chosen due to a wrong mental model.
- Examples:
  - Choosing the wrong menu option.
  - Misunderstanding an icon's meaning.
- Cause: mismatch between the user's mental model and the system model.

#### Lapses (Memory Errors)

- Forgetting a step in a sequence.
- Examples:
  - Forgetting to attach a file.
  - Skipping a required field.

### Discussion Questions

**If many users keep making the same mistake, who is wrong?**

The design is wrong. When a mistake is repeated across many users, it is a systemic design problem, not a user failure.

**How can we prevent slips, mistakes, and lapses?**

- Prevent slips: Separate dangerous actions (e.g., Delete vs Save), confirmation dialogs.
- Prevent mistakes: Align interface with user mental models, use clear labels and icons.
- Prevent lapses: Use reminders, progress indicators, checklists, required field validation.

**Why is "Undo" one of the most powerful UI features?**

Because it recovers from all three types of errors — slips, mistakes, and lapses — without penalty. It lowers the cost of mistakes and encourages exploration, reducing anxiety about irreversible actions.

---

## Norman's Action Cycle

**Core insight:** Every UI interaction follows a psychological process — whether designers realize it or not. If design does not account for these steps, users get confused.

### The 7 Stages

1. **Form goal** — The user decides what they want to achieve.
2. **Form intention** — The user decides to act.
3. **Specify action** — The user determines what action to take.
4. **Execute action** — The user performs the action.
5. **Perceive system state** — The user observes what happened.
6. **Interpret system state** — The user understands what the system did.
7. **Evaluate outcome** — The user compares the result to the original goal.

**Key point:** Every usability problem happens at one of these steps. Not randomly — at a specific cognitive breakdown point.

### Why This Model Matters

**With it, designers can:**
- Diagnose usability problems systematically.
- Identify where cognition breaks.
- Justify design changes scientifically.
- Design intentionally instead of randomly.

**Without it, design is:**
- Based on aesthetics only.
- Based on personal opinion.
- Based on guesswork.

It answers:
- Why do users struggle?
- Where does the breakdown occur?
- What needs to be fixed?

---

## Gulf of Execution and Gulf of Evaluation

### Gulf of Execution

- The gap between what the user wants to do and what the system allows them to do.
- Problem: The "Where is the Button?" Problem — the user cannot find the button.
- Norman's 7 stages affected: Form intention, Specify action, Execute action.

### Gulf of Evaluation

- The gap between the system's output and the user's understanding of it.
- Problem: The "I Clicked It But Nothing Happened" Problem — the user is not sure if an action took place.
- Norman's 7 stages affected: Perceive system state, Interpret system state, Evaluate outcome.

**Solution:** Reduce both gulfs with clear controls and clear feedback.

### Discussion: Which is worse — a hard-to-find button or unclear feedback?

- A hard-to-find button (Gulf of Execution) prevents the task from starting.
- Unclear feedback (Gulf of Evaluation) can cause repeated actions, data duplication, or anxiety.
- Both are serious — unclear feedback is often argued to be worse because users may take irreversible actions a second time, believing the first one did not register.

---

## Activity: Applying Norman's Model

**Task:** Translate "ordering food online" to Norman's 7 stages.

**Identify which stage each problem occurs at:**

- Can't find restaurant — Stage 3 (Specify action) / Stage 4 (Execute action) — Gulf of Execution.
- Payment error unclear — Stage 6 (Interpret system state) — Gulf of Evaluation.
- No confirmation message — Stage 5/6 (Perceive/Interpret system state) — Gulf of Evaluation.

---

## Activity: Case Study

**Choose one of the following apps and produce the given deliverables:**

- ATM
- Food delivery app
- University LMS
- Ride-hailing app

**Deliverables:**

1. User mental model diagram.
2. System model diagram.
3. Mismatch points between the two.
4. Redesign suggestion to close the gap.

---

## Activity: Diagnose Interface Issues Using Cognition

**Diagnose interface problems using the following lenses:**

- Perception
- Attention
- Memory
- Cognitive load
- Error patterns
- Norman's gulfs
- Mental model mismatch

---

## Accessibility Audit Checklist

### Visual

- Contrast OK?
- Text scalable?

### Keyboard

- Fully navigable?

### Screen Reader

- Labels present on all elements?

### Forms

- Errors clear and descriptive?

### Color Use

- Are color-only signals used (inaccessible without color vision)?

### Motion

- Excessive animation present?

---

## Summary

Every UI interaction follows a psychological process. The key cognitive factors that must be designed for are:

1. **Perception** — Match what users interpret, not just what is visible. Use pattern recognition, Gestalt principles, and high contrast.
2. **Memory** — Prefer recognition over recall. Reduce working memory load.
3. **Attention** — Respect limited focus. Avoid competing stimuli.
4. **Cognitive load** — Reduce extraneous load through clear design. Intrinsic load is unavoidable.
5. **Mental models** — Align the system model with what users expect.
6. **Error patterns** — Design to prevent slips, mistakes, and lapses. Always provide undo.
7. **Norman's Action Cycle** — Every usability problem maps to a specific cognitive breakdown point in the 7 stages. Reduce the Gulf of Execution and the Gulf of Evaluation.
