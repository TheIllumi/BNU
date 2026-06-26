# HCI & Computer Graphics -- Lecture 11

---

## Heuristics

---

## Nielsen's 10 Usability Heuristics

Broad rules of thumb for evaluating UI designs -- not strict guidelines but heuristics. Most widely cited usability framework in HCI.

### H1: Visibility of System Status

Always keep users informed about what is going on through appropriate feedback within a reasonable time.

**Example:** A progress bar during file upload; "Step 3 of 5" in a wizard.

### H2: Match Between System and Real World

Use words, phrases, and concepts familiar to the user. Follow real-world conventions and make information appear in a natural, logical order.

**Example:** A trash can icon for deletion; a shopping cart metaphor in e-commerce.

### H3: User Control and Freedom

Users often choose functions by mistake. Provide clearly marked "emergency exits", undo and redo, so they can leave unwanted states without extended dialogue.

**Example:** Undo in Gmail after sending; a visible Cancel button in multi-step forms.

### H4: Consistency and Standards

Users should not have to wonder whether different words, situations, or actions mean the same thing. Follow platform and industry conventions.

**Example:** Blue underlined text signals a link; Ctrl+Z means undo across applications.

### H5: Error Prevention

Better than good error messages is a careful design that prevents the problem from occurring. Eliminate error-prone conditions or present confirmation options.

**Example:** Graying out unavailable dates; "Are you sure?" before deleting.

### H6: Recognition Rather Than Recall

Minimize the user's memory load by making objects, actions, and options visible. Instructions should be visible or easily retrievable.

**Example:** Dropdown menus showing all options; recently visited files list.

### H7: Flexibility and Efficiency of Use

Accelerators, unseen by novice users, may speed up interaction for experts. Allow users to tailor frequent actions.

**Example:** Keyboard shortcuts; autocomplete; power-user modes.

### H8: Aesthetic and Minimalist Design

Dialogues should not contain irrelevant or rarely needed information. Every extra unit of information competes with relevant information and diminishes its relative visibility.

**Example:** Google's homepage; Apple's product pages.

### H9: Help Users Recognize, Diagnose, and Recover from Errors

Error messages should be in plain language (no codes), precisely indicate the problem, and constructively suggest a solution.

**Example:** "Incorrect password. Try again or reset it." -- not "Error 403."

### H10: Help and Documentation

Even though it is better if the system can be used without documentation, help may still be necessary. It should be easy to search, focused on the user's task, and list concrete steps.

**Example:** Contextual tooltips, inline help text, searchable FAQs.

---

## Shneiderman's 8 Golden Rules

Published in: 1986. These are actionable design rules rather than evaluation criteria. Especially relevant for interactive system design.

### R1: Strive for Consistency

Consistent sequences of actions in similar situations; identical terminology in menus, prompts, and help screens; consistent commands throughout.

**Example:** The same color for all primary action buttons across the entire application.

### R2: Seek Universal Usability

Recognize the needs of diverse users -- novices to experts, different ages and disabilities. Design for plasticity and provide a range of features for different user groups.

**Example:** Font size controls, keyboard navigation support, alt text for all images.

### R3: Offer Informative Feedback

For every operator action, there should be system feedback. Frequent or minor actions may have modest feedback; infrequent or major actions warrant more substantial feedback.

**Example:** A "Saved!" toast notification after a form submission.

### R4: Design Dialogs to Yield Closure

Sequences of actions should be organized into groups with a beginning, middle, and end. Informative feedback at completion gives a sense of accomplishment and signals the next move.

**Example:** E-commerce checkout ending with an "Order confirmed!" confirmation page.

### R5: Prevent Errors

Design the system so users cannot make serious errors. If an error is made, the system should detect it and offer simple, constructive instructions for recovery.

**Example:** Disabling the Submit button until all required fields are filled.

### R6: Permit Easy Reversal of Actions

Actions should be reversible wherever possible. This relieves anxiety -- users know they can reverse mistakes -- and encourages exploration of unfamiliar options.

**Example:** Multi-level undo in Photoshop; "Undo send" (30-second window) in Gmail.

### R7: Keep Users in Control

Experienced users want to feel in charge of the interface and that it responds to their actions. Surprising or unclear behaviors cause discomfort and reluctance to continue.

**Example:** Letting users choose notification frequency; optional manual save.

### R8: Reduce Short-Term Memory Load

The limitation of human short-term memory requires that displays be kept simple, multiple-page displays be consolidated, and sufficient training be provided for complex sequences.

**Example:** Showing previously entered data when users move forward in a multi-page form.

---

## Comparison: Nielsen vs Shneiderman

Rules R1, R3, R5, R6, and R8 map directly to Nielsen's H4, H1, H5, H3, and H6. The two frameworks reinforce each other. In practice, use them together for a comprehensive design and evaluation approach.

| | Nielsen's Heuristics | Shneiderman's Golden Rules |
|---|---|---|
| Count | 10 principles | 8 rules |
| Primary use | Evaluation (post-design) | Design (pre-implementation) |
| Scope | Broader and more abstract | More prescriptive and specific |
| Application | Used in heuristic evaluation sessions | Used as design guidelines during development |
| Focus | Emphasises user perception and experience | Emphasises system behaviour and responses |
| Publication | Published 1990, revised 1994 | Published 1986 (Designing the User Interface) |

### Class Activity

Evaluate your university's student portal using both frameworks simultaneously.

- List 2 violations per framework.
- Which framework was easier to apply?
- Why?

---

## Error Prevention Strategies

### Recap: Types of Errors

| Slips (automatic behaviour) | Mistakes (conscious decisions) |
|---|---|
| Correct intention, wrong action | Wrong intention, consistently executed |
| Capture errors -- habitual action takes over | Rule-based: wrong rule applied |
| Description errors -- right action, wrong object | Knowledge-based: lack of understanding |
| Mode errors -- right action in wrong mode | Much harder to detect and prevent |
| Example: typing old password after changing it | Example: choosing wrong date format (MM/DD vs DD/MM) |

Good design anticipates errors before they happen. Nielsen's H5 and Shneiderman's R5 both prioritize prevention over recovery.

### P1: Constrain Inputs

Limit what the user can enter to only valid options. Use input masks, date pickers, and dropdowns instead of free-text fields where possible.

**Example:** Phone number field that accepts only digits; a calendar widget instead of a typed date.

### P2: Inline Validation

Check input correctness as the user types or immediately on focus loss -- not after submission. Provide clear, positive guidance (not just "error").

**Example:** Password strength meter shown while typing; "Valid email" confirmation in green.

### P3: Confirmation for Destructive Actions

Before irreversible actions (delete, send, publish), ask for confirmation. Use friction proportional to consequence -- a modal for "delete all" is appropriate; one for "change font" is not.

**Example:** "Are you sure you want to delete this file? This cannot be undone."

### P4: Affordances and Mapping

Design controls so their appearance suggests their function (affordances) and their position/grouping matches expected behaviour (mapping). Good mapping reduces mode errors.

**Example:** A horizontal slider for volume control; a toggle switch with clear on/off state.

### P5: Make Modes Visible

Mode errors are dangerous. Always make the current mode explicit through visual indicators -- not just tooltips or status bars the user may miss.

**Example:** Caps Lock indicator on a login form; "You are in Edit Mode" banner in a CMS.

### P6: Undo and Graceful Recovery

When errors cannot be fully prevented, make recovery easy. Support multi-level undo, provide clear error messages with corrective actions, and never silently lose user data.

**Example:** Gmail's "Undo send"; autosave and version history in Google Docs.

---

## Feedback Mechanisms

Feedback closes the loop between user action and system response. Covered in Nielsen's H1 (visibility of system status) and Shneiderman's R3 (informative feedback). Effective feedback is timely, relevant, and proportional.

### Feedback by Response Time

| Feedback Type | Response Time | Use Case | Example |
|---|---|---|---|
| Immediate | 0-100ms | Button clicks, key presses | Button press animation, cursor change |
| Short-term | 100ms-1s | Search, simple queries | Results appearing, form validation |
| Long-term | 1s-10s | File upload, API calls | Progress bar, percentage counter |
| Background | >10s | Exports, large operations | Email notification, background task badge |

### Feedback Modalities

| Visual Feedback | Non-Visual Feedback |
|---|---|
| Color changes (red = error, green = success) | Auditory: sounds for completion, errors |
| Animations and micro-interactions | Haptic: vibration on mobile devices |
| Progress indicators and loaders | Verbal: screen reader announcements |
| Toast notifications and status badges | Systemic: email / push notifications |

### Proportionality

Feedback should be proportional to the importance of the action. A subtle color change for minor updates; a modal or full-screen confirmation for major events.

Over-notifying trains users to ignore alerts -- the "cry wolf" anti-pattern.

---

## Testing Methods

### Heuristic Evaluation

A usability inspection method where evaluators examine a UI and judge its compliance with recognized usability principles.

- Developed in 1990
- A discount usability method: cheap, fast, and expert-driven -- not user-driven

**Process:**

1. Brief evaluators on the heuristics and the product's context (10-15 min).
2. Each evaluator independently inspects the interface alone (1-2 hours each).
3. Evaluators walk through the UI at least twice: first for overall flow, then for individual elements.
4. Each evaluator documents violations, citing the specific heuristic violated.
5. Evaluators aggregate results and rate severity (a facilitator may run a debrief session).
6. Prioritize fixes based on severity ratings and produce a written report.

**Nielsen's Severity Rating Scale** (3 to 5 evaluators are sufficient):

| Rating | Interpretation | Action |
|---|---|---|
| 0 | Not a usability problem at all | No action needed |
| 1 | Cosmetic problem only | Fix if extra time permits |
| 2 | Minor usability problem | Low priority -- plan for next iteration |
| 3 | Major usability problem | Important -- high priority fix |
| 4 | Usability catastrophe | Must fix before product release |

**Advantages vs Limitations:**

| Advantages | Limitations |
|---|---|
| Fast and inexpensive | Expert bias -- evaluators may miss real user issues |
| No users needed (useful early in design) | False positives (reported non-problems) |
| Can be done iteratively at any stage | Does not reveal unknown unknowns |
| Experts give structured, actionable feedback | Quality depends heavily on evaluator expertise |

---

### A/B Testing

A quantitative method where two versions of a design -- A (control) and B (variant) -- are shown to different groups of real users simultaneously. Statistical analysis determines which achieves the target metric better.

**The A/B Testing Process:**

1. **Define the hypothesis:** "Changing the CTA button from blue to orange will increase click-through rate by 10%."
2. **Identify the metric:** Click-through rate, conversion rate, session duration, bounce rate, etc.
3. **Calculate sample size:** Use a power analysis to ensure statistical validity (typically 80% power, a = 0.05).
4. **Randomly split users:** 50% see version A, 50% see version B. Random assignment is critical.
5. **Run the test simultaneously:** Never run A then B sequentially. Run until you reach the required sample size (typically 1-4 weeks).
6. **Analyze results:** (discussion for another subject).
7. **Ship or iterate:** If B wins significantly, ship it. If not significant, keep A or design a new variant.

**When to Use vs When NOT to Use A/B Testing:**

| When to Use | When NOT to Use |
|---|---|
| High-traffic product with enough users | Low traffic (insufficient sample size) |
| Testing incremental, specific changes | Major redesigns with too many variables |
| Measuring behavioural outcomes (clicks, sign-ups) | Qualitative questions ("why?", not "which?") |
| Data-driven team culture | Ethical concerns with exposing users to worse UX |

---

## Formative vs Summative Evaluation

> Michael Scriven (1967): "When the cook tastes the soup, that's formative; when the guests taste the soup, that's summative."

**Formative helps you improve. Summative helps you prove.**

| | Formative Evaluation | Summative Evaluation |
|---|---|---|
| Goal | "Improve while you build" | "Judge the final product" |
| Timing | During design and development | After design is complete |
| Purpose | Identify and fix problems | Measure performance vs benchmark |
| Scale | Small, iterative, qualitative focus | Larger, controlled, quantitative focus |
| Participants | 5-8 typical | 30-100+ typical |
| Methods | Think-aloud, heuristic eval, cognitive walkthrough, paper prototyping | Usability benchmark, A/B test, SUS survey, analytics review |
| Output | Insights and design changes | Metrics and go/no-go decisions |

### The Design-Evaluation Lifecycle

```
Concept
  --> Formative (paper prototype)
  --> Refine
  --> Formative (wireframe)
  --> Develop
  --> Formative (alpha)
  --> Launch
  --> Summative (benchmark)
  --> Iterate
```

### Method Reference Table

| Method | Purpose | When in Project | What You Get |
|---|---|---|---|
| Heuristic evaluation | Formative | Early/mid design | List of violations with severity ratings |
| Cognitive walkthrough | Formative | Prototype stage | Task-by-task failure analysis |
| Think-aloud testing | Formative | Any prototype stage | Qualitative insights and pain points |
| A/B testing | Summative | Live product | Statistical outcome per variant |
| SUS (System Usability Scale) | Summative | Post-launch | Usability score (0-100) |
| Benchmark usability test | Summative | Post-launch / comparative | Task completion rate, time, error count |
| Analytics review | Summative | Live product, ongoing | Drop-off rates, funnels, heatmaps |
