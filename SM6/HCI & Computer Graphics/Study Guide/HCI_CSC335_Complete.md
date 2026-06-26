# HCI & Computer Graphics (CSC-335) — Complete Study File

---

## Table of Contents

1. [UX Design Study Notes](#ux-design-study-notes)
2. [Reference Material (Quiz 3 & 4)](#reference-material-quiz-3--4)
3. [Mid Term Spring 2026](#mid-term-spring-2026)
4. [Quiz 1](#quiz-1)
5. [Quiz 2](#quiz-2)
6. [Quiz 2 & 3 (Bilal/Zara Scenarios)](#quiz-2--3-bilalzara-scenarios)
7. [Quiz 2 & 3 (Amna/Punjab Scenarios)](#quiz-2--3-amnapunjab-scenarios)
8. [Quiz 3 — May 22, 2026](#quiz-3--may-22-2026)
9. [Quiz 4 — May 22, 2026](#quiz-4--may-22-2026)

---

# UX Design Study Notes

## Topic 1 — Information Architecture (IA)

### What is Information Architecture?

Information Architecture (IA) is the process of organising, structuring, and labelling content in a product so users can easily navigate and find information. It acts like the "blueprint" or "skeleton" of a website/app.

**Good IA improves:**
- Findability
- Navigation
- User understanding
- Efficiency
- User satisfaction

**Bad IA causes:**
- Confusion
- Frustration
- Users getting lost
- Increased cognitive load

### 3 Key IA Models (NNgroup)

**1. Navigation Model**

The visible structure users interact with.

Examples: Menus, Navigation bars, Sidebars, Tabs, Links

Purpose: Helps users move around the product.

Example: Amazon categories menu.

**2. Taxonomy Model**

How content is grouped and categorised.

Examples: Product categories, Blog tags, File folders

Purpose: Makes information easier to understand and locate.

Example — Clothing website categories: Men, Women, Kids

**3. Full IA Structure**

The complete map of all screens/pages and their relationships.

Includes: Parent pages, Child pages, Connections between screens

Purpose: Helps designers understand the whole system structure.

### Core IA Principles

**1. Organisation** — Content should be logically arranged.

Example: Grouping settings into Privacy, Notifications, Account.

**2. Labelling** — Clear and familiar names for menus/buttons.

- Good: "Contact Us"
- Bad: "Connect Experience Portal"

**3. Navigation** — Users should always know where they are, where they can go, and how to return.

**4. Search** — Important for content-heavy platforms. Good search is fast, accurate, and has filters available.

### Common IA Patterns

**1. Hierarchical Structure**

Tree-like structure. Most common pattern.

Example: Home → Products → Electronics → Phones

**2. Sequential Structure**

Step-by-step flow.

Example: Checkout process.

**3. Matrix Structure**

Multiple navigation pathways.

Example: Netflix browsing by Genre, Trending, Search, or Recommendations.

**4. Organic Structure**

Free exploration with no fixed path.

Example: Art portfolio websites.

### Why IA Matters

Good IA reduces confusion, improves usability, helps users complete tasks faster, and supports accessibility.

---

## Topic 2 — Task Flow and User Flow

### Task Flow

**Definition:** A Task Flow shows the exact steps needed to complete ONE task.

Features: Linear, Simple, No branching, No personas.

Example — Steps to order food:
1. Open app
2. Select restaurant
3. Add items
4. Checkout
5. Payment

### User Flow

**Definition:** A User Flow maps how a specific user type moves through a product.

Features: Includes decisions, Multiple paths, Entry points, Exit points, User goals.

Example — If payment fails: Retry payment → Change method → Cancel order.

### Difference Between Task Flow and User Flow

| Task Flow | User Flow |
|-----------|-----------|
| Simple | Complex |
| One path | Multiple paths |
| No decisions | Includes decisions |
| Focus on task | Focus on user journey |

### Why Flows Matter

Flows help designers identify friction, detect unnecessary steps, improve usability, and plan interfaces before UI design.

---

## Topic 3 — Cognitive Load

**Definition:** Cognitive load is the amount of mental effort required to use a system.

Goal of UX: Reduce unnecessary mental effort.

### Types of Cognitive Load

**1. Intrinsic Load**

Natural difficulty of the task. Cannot fully remove it.

Example: Learning coding.

UX goal: Simplify and guide users.

**2. Extraneous Load**

Mental effort caused by poor design. This SHOULD be removed.

Examples: Cluttered screens, Confusing labels, Too many options, Inconsistent navigation.

**3. Germane Load**

Mental effort used for learning. Helpful cognitive effort.

Example: Learning how a dashboard works. Good UX supports this.

### Techniques to Reduce Cognitive Load

**Chunking** — Break information into smaller groups.

Example: Phone number formatting.

**Progressive Disclosure** — Show advanced info only when needed.

Example: "Advanced settings" dropdown.

**Familiar Patterns** — Use common UI conventions.

Example: Shopping cart icon.

**Minimise Choices** — Too many choices overwhelm users.

Related concept: Miller's Law (7±2 items).

---

## Topic 4 — Storyboarding and Wireframes

### Storyboards

**Definition:** Visual stories showing the user experience.

Helps understand: Context, Emotions, Problems, Goals.

### Types of Storyboards

**1. Big Picture Storyboard**

Focus: User emotions, Environment, Motivation.

Shows WHY users need the product.

**2. Close-Up Storyboard**

Focus: Screens, Interactions, Product usage.

Shows WHAT users do.

### 4 Elements of Storyboards

- **Character** — The user/persona.
- **Scene** — The environment/context.
- **Plot** — The sequence of actions.
- **Narrative** — Overall story/message.

### Wireframes

**Definition:** Simple layouts showing structure and functionality.

Wireframes focus on: Placement, Navigation, Layout, User flow.

NOT: Colours, Final visuals, Branding.

### Types of Wireframes

**Paper Wireframes** — Quick hand-drawn sketches. Cheap and fast.

**Digital Wireframes** — Created using tools like Figma, Adobe XD.

### UX Process Flow

Research → Personas → User Stories → Storyboards → Wireframes → Prototypes

---

## Topic 5 — Low-Fidelity Prototypes

**Definition:** A low-fidelity prototype is a simple interactive version of a product with minimal visual detail.

Purpose: Early testing and feedback.

### Types

**1. Paper Prototype**

Physical sketches. Interactions simulated manually.

**2. Digital Lo-Fi Prototype**

Clickable wireframes using software.

Example: Figma prototype links.

### Why Use Lo-Fi Prototypes?

- **Fast** — Quick to create.
- **Cheap** — Low cost.
- **Easy to Change** — No emotional attachment to designs.
- **Focus on Usability** — Users focus on functionality instead of visuals.

### Lo-Fi vs Hi-Fi

| Lo-Fi | Hi-Fi |
|-------|-------|
| Basic visuals | Real visuals |
| Wireframes | Final UI |
| Early testing | Final testing |
| Fast edits | More expensive |

---

## Topic 6 — Mental Models

**Definition:** Mental models are users' expectations about how something should work based on past experiences.

### Why Important?

Users compare your product with other apps, physical objects, and previous habits. Good UX matches expectations.

### Examples

**Desktop Metaphor** — Computer desktops mimic physical desks.

**Shopping Cart Icon** — Users expect it to store selected products.

**Jakob's Law** — Users spend most of their time on other websites. Therefore, they expect your website to work similarly.

### Mismatched Mental Models

When products behave unexpectedly: Confusion increases, Learning becomes harder, Users feel frustrated.

### Good UX Strategy

Either match existing mental models, or introduce new concepts gradually with onboarding.

---

## Topic 7 — Inclusive and Accessible Design

### Accessible Design

**Definition:** Designing products usable by people with disabilities.

Focus: Removing barriers.

Uses: WCAG guidelines.

Examples: Screen reader support, Keyboard navigation, Alt text.

### Inclusive Design

**Definition:** Designing for diverse human experiences from the start.

Considers: Age, Language, Culture, Gender, Economic status, Ability.

### Key Difference

| Accessibility | Inclusive Design |
|---------------|-----------------|
| Reactive | Proactive |
| Focus on disabilities | Focus on all diversity |
| Compliance-focused | Human-focused |

### Curb Cut Effect

Accessibility features often help everyone.

Example: Wheelchair ramps also help parents with strollers, cyclists, and delivery workers.

### Why Inclusive Design Matters

Benefits: Larger audience, Better usability, Ethical design, Better business outcomes.

---

## Topic 8 — Visual Design Principles

**1. Emphasis** — Makes important elements stand out.

Methods: Size, Colour, Contrast, Placement.

Example: CTA buttons.

**2. Hierarchy** — Shows importance order visually.

Methods: Font size, Weight, Position.

Example: Large headlines.

**3. Scale and Proportion** — Relative sizing of elements. Helps balance layouts and show importance.

**4. Unity** — Everything feels connected and consistent.

Achieved through: Consistent colours, Typography, Spacing.

**5. Variety** — Adds visual interest. Prevents boring layouts.

### Gestalt Principles

**Proximity** — Close items seem related.

**Similarity** — Similar items seem connected.

**Continuity** — Eyes naturally follow lines and paths.

**Closure** — People complete incomplete shapes mentally.

**Figure/Ground** — Distinguishing foreground from background.

---

## Topic 9 — Error State Design

**Definition:** Error states inform users when something goes wrong and help them recover.

### Principles of Good Error Design

**1. Be Specific**

- Good: "Password must be at least 8 characters."
- Bad: "Error occurred."

**2. Use Human Language** — Avoid technical jargon.

- Bad: "HTTP 403."
- Good: "You don't have permission to access this page."

**3. Offer a Solution** — Tell users what to do next.

Example: "Check your internet connection and retry."

**4. Timing Matters** — Inline validation should appear after users finish typing.

**5. Don't Rely Only on Colour** — Use icons, text, and labels. Accessibility matters.

### Types of Error States

- **Form Validation Errors** — Incorrect input.
- **Empty States** — No data available. Example: "No messages yet."
- **Network Errors** — Internet/connectivity issues.
- **Permission Errors** — User lacks access rights.
- **System Errors** — Backend/system crashes.

### Nielsen's Error Heuristics

Good errors should: help users recognise the problem, explain clearly, suggest recovery steps, and use plain language.

---

# Reference Material (Quiz 3 & 4)

| Sr. No. | Concept | Helpful Links |
|---------|---------|---------------|
| 1 | Information Architecture | https://www.youtube.com/watch?v=XfxR5m8zUO8 / https://www.youtube.com/watch?v=v39z0JPeIc8 |
| 2 | Task Flow and User Flows | https://www.youtube.com/watch?v=cGzIO4n03gY |
| 3 | Cognitive Load | Intrinsic, Extraneous, Germane |
| 4 | From Storyboarding to Wireframes | https://www.youtube.com/watch?v=WyXTT30YFjI |
| 5 | How to design a low fidelity prototype | https://www.youtube.com/watch?v=3F4mWr1cY-8 |
| 6 | Mental Models | How your user is used to getting the work done (other apps, sticky notes, writing in their journal, voice notes etc) and your design must match or bridge that model |
| 7 | Inclusive and accessible design | https://www.youtube.com/watch?v=hE83Qn-PTGA |
| 8 | Visual Design Principles | https://www.youtube.com/watch?v=yNDgFK2Jj1E |
| 9 | Error state design | — |

---

# Mid Term Spring 2026

**Subject:** HCI & Computer Graphics | **Section:** A, B, C | **Date:** 14th April 2026

**Course Code:** CSC-335 | **Marks:** 33 | **Semester:** 6th

**Examination:** Mid Term Spring-2025 Semester

**Instructor:** Hamna Anwar & Sania Khalid | **Time:** 1 hour

**Notes:**
1. External Source and Use of mobile-phones during the exam leads to Disciplinary Action.
2. Plagiarism or copying from others will result in disqualification from the exam.
3. There are total of 8 questions and 7 pages in this question paper.
4. Where required, write 1 to 2 sentence explanations, instead of long paragraphs. Failure to comply will result in marks deduction.
5. Answer all questions on the answer booklet.

| CLOs | Questions |
|------|-----------|
| CLO1: (C2: Understand) Explain fundamental principles of user-centered design | 2, 3 |
| CLO2: (C2: Understand) Identify accessibility & inclusivity as essential elements of HCI | 7, 8 |
| CLO3: (C4: Analyze) Analyze user feedback to refine interface prototypes | 5, 6 |
| CLO4: (C5: Design) Design interactive prototypes using modern HCI tools | 1, 4 |

---

### Q1 [4 marks]

A user is trying to send Rs. 5,000 and accidentally presses Cancel instead of Confirm.

**(a)** Classify this error as a slip, mistake, or lapse. [1 mark]

**(b)** Identify two design problems with how the two buttons are displayed. [1 mark]

**(c)** Redesign the buttons to overcome the two problems identified in part b. [2 marks]

> **UI context:** Easypaisa "Send Money Confirmation" screen showing Rs. 5,000 transfer to Ahmed Ali (0312-XXX4821), with two equally styled black buttons side by side — "Cancel" on the left, "Confirm" on the right.

---

### Q2 [3 marks]

Ayesha submits her HCI Research Paper. She later notices an error and clicks "Delete" expecting the file to be permanently removed. Instead, it disappears from "Submitted" and reappears under the "Drafts" tab.

**(a)** Identify Ayesha's mental model and the system model in this scenario. Write one sentence for each. [2 marks]

**(b)** Would you fix this with a label change or a design change? [1 mark]

> **UI context:** University Portal showing Student: Ayesha Khan, with Submitted/Drafts tabs. The HCI Research Paper — Final Draft (CS-402 Human Computer Interaction, March 28, 2026, 11:42 PM) shows "Submitted" status with Edit and Delete buttons.

---

### Q3 [2 marks]

Look at the BNU Contact Directory screen below.

**(a)** A student wants to call Sara Khan but she reads the wrong number. Name the Gestalt principle which is causing this mistake. [1 mark]

**(b)** The student wants to call Usman Tariq using the Quick Actions section. She cannot tell which items she can tap and which are just text. Name the Gestalt principle being violated and identify what is missing from the "Call" buttons that would have prevented this confusion. [1 mark]

> **UI context:** BNU Contact Directory listing Faculty — Department of Computer Science (Ahmed Ali, Sara Khan, Usman Tariq, Fatima Malik, Bilal Hassan) with phone numbers and names alternating without visual grouping. A Quick Actions section below lists the same names with "Call" text on the right — no button borders or visual affordance.

---

### Q4 [4 marks]

A user is placing an order on Daraz. Figure 4 shows the UI before pressing the "Place Order" button. Figure 5 shows the UI after pressing the "Place Order" button. Figure 6 shows the UI 5 seconds after pressing the "Place Order" button.

**(a)** Name the stage in the Norman's Action Cycle where a breakdown occurs and explain why in 1 to 2 sentences. [2 marks]

**(b)** Identify if this is a Gulf of Execution or Gulf of Evaluation problem. NO need to explain the answer. [1 mark]

**(c)** Suggest one design change that would resolve this issue. Show the redesigned UI. Do not explain the redesigned UI. [1 mark]

> **UI context:**
> - Figure 4 (Before): Daraz Order Summary — Delivery to Ahmed Khan, House 12 Street 5 Gulberg III Lahore. Items: Wireless Bluetooth Earbuds (Rs. 2,499) + Phone Case Transparent Slim Fit (Rs. 350). Subtotal Rs. 2,849, Delivery Fee Rs. 99, Total Rs. 2,948. Payment: Cash on Delivery. "Place Order" button visible.
> - Figure 5 (After pressing): Identical screen — no visible change.
> - Figure 6 (5 seconds after): Completely different Daraz home screen with Flash Sale timer (02:14:33), category icons, and "Recommended for You" products — no order confirmation shown.

---

### Q5 [6 marks]

Rozee.pk redesigns their mobile app. The new version is visually polished and loads faster than before. During post-launch research, the UX team interviews several users and gets the following responses:

- (i) "I didn't know Rozee had an app, I always just used the website."
- (ii) "I downloaded it but you have to link your LinkedIn before you can even browse jobs. I don't have LinkedIn so I just deleted it."
- (iii) "I use it every day but honestly the jobs it shows me are never in my field. I'm a graphic designer and it keeps suggesting call center jobs."
- (iv) "It's fine to use, I figured it out quickly enough."

**(a)** Three of these four responses reveal a UX problem. Identify which three using the Honeycomb facet. [3 marks]

**(b)** The fourth response suggests one Honeycomb facet is working well. Identify the facet, and explain what this tells the team about where to focus their redesign effort. [2 marks]

**(c)** The team decides to refine the app based on response ii. Suggest one specific change to the app that directly addresses this user's feedback. [1 mark]

---

### Q6 [4 marks]

A UX team at a Pakistani e-commerce company has survey data showing that 73% of users abandon their cart at the payment step. The CEO says: "We have our answer, fix the payment step." Only one word or one-line answers are required.

**(a)** What does the survey data tell the team? [1 mark]

**(b)** What critical information does the survey fail to provide? [1 mark]

The team conducts user interviews. The most commonly reported issue across participants is: "I didn't realize my session had timed out, I thought my card details were saved but I had to start over."

**(c)** What research method should the team use next to confirm this is a widespread problem? [1 mark]

**(d)** Based on this feedback, suggest one specific change to the checkout screen that directly addresses what users experienced. [1 mark]

---

### Q7 [4 marks]

A UX team is designing the ride request acceptance feature for an app similar to the inDrive app. To test it, they recruit 12 drivers through a university noticeboard, bring them into their office, seat them in their meeting room with a desk, and ask them to use the app on a phone mounted in a stand. The session runs at 2pm on a Tuesday. All participants complete every task. The product manager reviews the report and approves the design for release.

**(a)** Identify two context factors the team failed to account for. [1 mark]

**(b)** For each factor you identified, state one design decision that would have been made differently had it been considered during the research phase. [1 mark]

**(c)** The team celebrated their user testing by saying: "We recruited actual drivers." A colleague reviews the recruitment method and disagrees. What exactly is the colleague's concern? [1 mark]

**(d)** Some drivers who use ride-hailing apps use the phone one-handed due to a physical limitation. Identify one design change that would make the ride acceptance screen more inclusive for these users. [1 mark]

---

### Q8 [6 marks]

A university hires a design team to build a food ordering app for hospital patients. The team defines their user as anyone who wants to order food and spends three weeks making the app look modern and visually polished. They test it with 15 university students. All participants complete every task successfully and rate the app 4.8 out of 5.

The project manager presents the results to the hospital board and says: "The app looks great and scored 4.8, it's ready to ship."

**(a)** The project manager uses the 4.8 rating as evidence that the design works. Give two reasons why using the score as proof that the app is ready for hospital patients is wrong. [2 marks]

**(b)** If you are tasked to lead another team to work on the same problem, would you use the same approach as Team A? If not, mention two things you would have done. [2 marks]

**(c)** The stakeholder is impressed with the polished product produced by Team A and is inclined to select their design. What is the issue in the stakeholder's thinking? [1 mark]

**(d)** A hospital patient using this app may be elderly, have limited hand mobility, or be recovering from surgery. Identify one specific design decision the team should have made to ensure the app works for these users. [1 mark]

---

# Quiz 1

**Course:** HCI & Computer Graphics (CSC-335)

---

### Q1 [2 marks]

A product team at a Pakistani bank has been running their mobile banking app for 3 years. Usage data shows that 60% of users drop off during the fund transfer process. The team wants to redesign the transfer flow.

The project manager says: "We already know what the problem is — the steps are too many. Let's just redesign it."

**(a)** Should the team conduct a user needs assessment before redesigning? Justify your answer in 1 to 2 sentences. [1 mark]

**(b)** What specific question would a needs assessment help answer that the usage data cannot? [1 mark]

---

### Q2 [2 marks]

A UX researcher is designing an interview protocol to understand how students at a Pakistani university manage their academic workload. She writes the following core questions:

- "Do you find it hard to manage assignments?"
- "What is your favorite app for studying?"
- "Tell me about the last time you missed a deadline, what happened?"
- "Why don't students use the library more often?"

**(a)** Two of these questions are problematic. Identify them. [1 mark]

**(b)** Rewrite one of the problematic questions to make it a strong interview question. [1 mark]

---

### Q3 [4 marks]

Look at the checkout screen below. A user is trying to complete a purchase on Daraz for the first time.

**(a)** Identify one working memory violation on this screen and explain why it creates a problem for the user. [1 mark]

**(b)** Mention one element on this screen that relies on recall rather than recognition. Suggest a redesign that shifts it to recognition. [2 marks]

---

# Quiz 2

**Course:** HCI & Computer Graphics (CSC-335)

---

### Q1 [2 marks]

A startup is building a new app to help domestic workers in Lahore find household jobs. No such app currently exists for this specific audience. A developer on the team says: "We don't need user research — we can just launch and see what happens."

**(a)** Identify one thing a needs assessment would uncover that a post-launch analysis cannot. [1 mark]

**(b)** At what stage should the needs assessment be conducted? [1 mark]

---

### Q2 [2 marks]

A team is designing a research protocol to understand how freelancers in Pakistan manage their finances and invoicing. A junior researcher drafts the following questions:

- "Can you tell me about a time when a client delayed your payment, what did you do?"
- "Do you use any apps to track your income?"
- "What is your biggest financial challenge as a freelancer?"
- "Why do most freelancers avoid using formal banking?"

**(a)** Two of these questions are problematic. Identify them. [1 mark]

**(b)** Rewrite one of the problematic questions to make it a strong interview question. [1 mark]

---

### Q3 [3 marks]

Look at the university course registration screen below. A student is trying to register for her chosen courses.

**(a)** Using the Gestalt principle of proximity, specify one issue with how the "Register" buttons are displayed and explain what is wrong with it. [1 mark]

**(b)** Suggest one specific layout change that would use proximity correctly to fix this problem. Suggest a redesign for the UI. [2 marks]

---

# Quiz 2 & 3 (Bilal/Zara Scenarios)

---

### Q1 — Bilal Course Registration Scenario

Bilal is a first-year student using his university's online portal to register for next semester's courses. The registration screen displays all 90 available courses in a single scrollable list, sorted alphabetically by course code. Each entry shows six pieces of information (course code, full title, prerequisites, credit hours, instructor name, and available seats) all in the same font size and weight, with no visual grouping, no search bar, and no filter option. After 15 minutes of scrolling, Bilal accidentally selects CSC-401 (a 4th-year elective) instead of CSC-201 (a 2nd-year core course). The system registers him silently (no confirmation dialog, no warning, and no success or error message). He discovers the mistake a week later when his academic advisor flags it.

**(a)** Each course entry displays six pieces of information in identical font size and weight. Identify which type of cognitive load is primarily increased by this presentation style.

**(b)** Suggest one Information Architecture change to this screen that would help students like Bilal locate a relevant course significantly faster. State the change.

**(c)** Name one Visual Design Principle that, if applied to the information inside each course entry, would allow Bilal to instantly distinguish essential details from secondary details.

---

### Q2 — Zara Storyboarding Scenario

Zara is a UX designer hired to build a feature that lets university students request a Leave of Absence through a mobile app. She skips storyboarding and opens Figma directly. After three weeks she presents wireframes showing: a form with 12 fields, a submit button, and a confirmation screen. During review, a faculty member points out two issues: the form asks for information a student would not know off-hand (like their faculty member's staff ID), and there is no screen for what happens if the Dean rejects the request. Her manager says: "You should have storyboarded first."

**(a)** Name the two types of storyboard used in UX design. State in one sentence each which type would have helped Zara avoid each of the two problems identified in the review.

**(b)** A colleague says: "Storyboards are a waste of time. We can just build the wireframes and fix problems later." Give one specific cost or risk that this approach introduces, in one sentence.

---

# Quiz 2 & 3 (Amna/Punjab Scenarios)

---

### Q1 — Amna Hospital App Scenario

Amna is a 60-year-old patient recovering from hand surgery in a hospital. The hospital has installed a food-ordering app on bedside tablets that patients use to select their meals. To place an order, Amna must:
1. Tap a small hamburger-menu icon to open food categories
2. Scroll horizontally through a category strip
3. Long-press an item to add it to her tray
4. Tap a small floating button at the bottom-right corner to confirm

All interactive buttons are 18x18 px, the text contrast ratio is 2.8:1, and all usage instructions appear only as hover-tooltips. After tapping the confirm button, the screen returns silently to the home screen with no message. Amna assumes something went wrong and calls a nurse, who checks the kitchen system and confirms the order was placed successfully.

**(a)** Identify one specific interaction in this app that directly conflicts with Amna's mental model, and state it in one sentence.

**(b)** Identify two accessibility failures in this scenario. For each failure, name the accessibility principle being violated and suggest one specific design change that would fix it.

**(c)** Before building the ordering screen, the designer should have mapped a task flow. Write or draw a simplified task flow a patient should follow to complete a meal order. Your flow should contain no more than four steps and should be clear enough to guide a screen layout decision.

**(d)** After Amna taps the confirm button, the screen returns to the home screen with no message or feedback. Identify this as a specific type of error state design problem and propose one targeted design change that resolves it.

**(e)** The development team defends their testing by saying: "We tested it with 20 healthy university students and all tasks were completed successfully." Give one specific reason why this testing approach is invalid for evaluating this product.

---

### Q2 — Punjab Government Citizen Portal Scenario

The Punjab government launches a citizen services portal. The navigation bar has the following top-level labels: "Department of Excise & Taxation", "Transport Authority", "Board of Revenue", "Health Department", and "Education Department". Sana, a university student, needs to renew her driving license. She clicks "Transport Authority," finds a page with 47 links, scans for two minutes, gives up, and calls a helpline instead. A UX team is hired to fix the portal.

**(a)** The navigation is currently organized by government department. Name the alternative organizational principle the UX team should use instead, and explain in one sentence why it would make the portal easier for Sana to use.

**(b)** After restructuring the website, the team proposes these top-level labels: "Drive & Travel", "Land & Property", "Health & Family", "Schools & Colleges". Identify one strength and one weakness of this labelling approach, one sentence each.

**(c)** A developer argues: "We can fix discoverability by adding a search bar, IA restructuring is unnecessary." Give one specific reason why search alone does not replace good Information Architecture.

---

# Quiz 3 — May 22, 2026

**Course:** HCI & Computer Graphics (CSC-335) | **Total Marks:** 15

**Date:** May 22, 2026 | **Instructor:** Sania Khalid | **Time:** 15 Min

**Instructions:** Answer all questions. Write clearly and concisely. Marks are indicated for each question.

---

### Q1 [2 + 3 = 5 marks]

A social media app provides no visual feedback when a post fails to upload due to a poor internet connection. Unaware that anything has gone wrong, the user repeatedly taps the "Post" button. Once connectivity is restored, six identical duplicate posts appear all at once.

Name the error state design principle that is missing in this scenario, and propose a detailed solution that would prevent this experience from occurring.

---

### Q2 [2 + 3 = 5 marks]

A news app displays 14 stories on its homepage, all rendered in the same font size, the same font weight, and the same card size, with no visual distinction between them. Users report feeling overwhelmed and uncertain about where to begin reading.

Name the visual design principle that is absent in this layout, and explain how you would redesign the homepage to create a clearer, more guided reading experience.

---

### Q3 [5 marks]

A startup's designer insists on creating fully polished Figma prototypes, complete with brand colours, custom typography, and real images for every round of user testing, regardless of the stage of the project. The team is working under significant time and budget constraints. A senior UX designer recommends switching to paper prototypes for early-stage testing.

Drawing on your understanding of low-fidelity prototyping, explain the strategic advantages of this approach and justify why it is the more appropriate choice at this stage of the design process.

---

# Quiz 4 — May 22, 2026

**Course:** HCI & Computer Graphics (CSC-335) | **Total Marks:** 15

**Date:** May 22, 2026 | **Instructor:** Sania Khalid | **Time:** 15 Min

**Instructions:** Answer all questions. Write clearly and concisely. Marks are indicated for each question.

---

### Q1 [1 + 2 + 2 = 5 marks]

An e-commerce website buries its Returns Policy under "About Us > Company Info > Legal," three levels deep in the navigation. Despite having a generous and customer-friendly policy, the company continues to receive a high volume of complaints about returns.

Identify the specific Information Architecture problem this illustrates, explain why it creates a poor user experience, and suggest how the navigation structure could be improved to resolve it.

---

### Q2 [3 + 3 = 6 marks]

A design team is building the checkout flow for an online store. They propose displaying all three sign-in options — guest checkout, account login, and social sign-in — simultaneously on a single screen, each with equal visual prominence.

From a user flow perspective, explain the problem this approach creates and the design principle it violates. Then propose a structured solution that reduces friction and guides users more effectively through the checkout process.

---

### Q3 [4 marks]

A health and wellness app uses red icons to indicate an "at risk" status and green icons to indicate a "healthy" status across all its dashboards. A user with red-green colour blindness reports that they are completely unable to distinguish between the two states.

Identify the accessibility principle that was overlooked in this design, and propose a concrete, multi-layered fix that would make the feature accessible to all users.
