# Frontend Presentation Guide & Project Handover Document
**Developer: Saad (Senior Frontend Engineer) · Project: Foreman Kanban Task Board**

This document serves as your personal script/guide for your video presentation to Ismail (PR Manager/DevOps) and Ibrahim (Backend Engineer), as well as a comprehensive technical handover report that Ismail can use to review, merge, and continue the project.

---

## Part 1: Video Presentation & Demo Guide

Use this section as a script or checklist while recording your demo video.

### 1. Introduction (0:00 - 0:30)
* **What to say**:
  > "Hi everyone, Saad here. Today, I'm excited to walk you through the completed frontend implementation of the Foreman Kanban Task Board. I've finished all five assigned feature increments (F1 to F5). The frontend codebase has been fully refactored, the styling system is optimized, and I've verified that the production bundle compiles and lints 100% cleanly. Let's look at the features."
* **Onscreen Visual**: Show the login screen of the Foreman application on `localhost:5173`. Toggle between "Clock In" (Login) and "New Hire" (Signup) tabs.

---

### 2. Feature [F4] Dark/Light Theme Toggle (0:30 - 1:15)
* **What to say**:
  > "First, let's look at our styling system. I refactored the design system in `index.css` to use CSS custom variables. We now have a Dark theme by default, and a new high-contrast Light theme styled for an industrial workshop look. The theme switch is in the Topbar, and it uses localStorage to persist the user's choice across sessions."
* **Onscreen Visual**: Click the Sun/Moon icon in the Topbar. Show the interface transition smoothly between the dark charcoal panel look and the manila-paper concrete light look. Refresh the browser to show that the theme selection persists.

---

### 3. Feature [F2] Employee Workload View (1:15 - 2:00)
* **What to say**:
  > "Now, let's clock in as an employee. Normally, employees see their board grouped by columns representing task stages. I've added a new Workload View. When toggled, the board client-side groups tasks into Low, Medium, and High complexity columns. Each column includes a custom progress bar displaying the completion rate of that specific complexity bucket based on the 'Done' task count. This lets employees see at a glance where their effort is concentrated."
* **Onscreen Visual**: Switch layout view from "Board View" to "Workload View". Point out the progress bars and show how the cards are categorized under "Low Complexity", "Medium Complexity", and "High Complexity" headers.

---

### 4. Feature [F3] Drag-and-Drop Board Interactions (2:00 - 3:00)
* **What to say**:
  > "Next is the drag-and-drop board interaction. Rather than relying on simple button clicks, users can now drag ticket cards between lanes. Dropping a card triggers the correct API endpoint behind the scenes—such as starting a job or submitting it for review. Most importantly, it enforces our role-based status machine. If an employee tries to perform an illegal drop—like dragging a card straight to Done—it snaps back, and a rollback toast notifies them of the error. When a Manager drags a task from 'For Inspection' back to 'In Progress', it triggers a feedback dialog prompting them to write revision notes."
* **Onscreen Visual**: Drag an employee card from *To Do* to *In Progress* (shows success toast). Then drag a card from *To Do* to *Signed Off* to show the visual snap-back and the error toast. Log in as a manager, drag a card from *For Inspection* to *In Progress*, and show the prompt asking for reject reason notes.

---

### 5. Feature [F1] Enhanced Manager Review Queue (3:00 - 4:00)
* **What to say**:
  > "Now let's check the Manager Dashboard. The manager's Inspection Queue has been turned into a real inbox. I've added filters for Crew member and Complexity levels. Clicking a card expands a detailed preview panel showing the description and past rejection history, which integrates with Ibrahim's backend history endpoint. Lastly, I added a 'Confirm All' button that lets managers sign off all currently filtered submissions in parallel."
* **Onscreen Visual**: Log in as a Manager. Select an employee from the dropdown, then select a complexity level to show the list filtering. Click a card to expand the details pane showing description and revision history logs. Click the "Confirm All" button to clear the filtered list (shows success toast).

---

### 6. Feature [F5] Notification Bell Widget (4:00 - 5:00)
* **What to say**:
  > "Finally, we have the Notification Bell. To prevent users from having to refresh, the bell component polls the task API every 10 seconds. It compares task states and pushes instant alert logs—like new assignments for employees, or new incoming submissions for managers. These notifications are saved per-user in localStorage so they persist across reloads, and you can mark them read or clear them at any time."
* **Onscreen Visual**: Point to the bell badge glowing amber in the Topbar. Click the bell to open the notification list, show the unread dots, click "Mark all read" (badge clears), and click "Clear" to empty the tray.

---

### 7. Conclusion & Quality Handover (5:00 - End)
* **What to say**:
  > "The code is fully pushed to my remote fork, and I've opened a PR into develop. The codebase builds and lints cleanly with zero warnings, making it safe for integration. Thanks! Let me know if you have any questions."

---

## Part 2: Technical Handover Blueprint (For Ismail)

This section details the file changes and components to assist Ismail with his PR review and code integration.

```
foreman-kanban/
├── frontend/
│   ├── .env                       ← Saad: Local environment credentials (Vite Firebase Web SDK)
│   ├── src/
│   │   ├── App.jsx                ← Topbar setup + calls initTheme() immediately to prevent flash
│   │   ├── utils/
│   │   │   └── theme.js           ← [NEW] Theme manager (localStorage wrapper)
│   │   ├── components/
│   │   │   ├── NotificationBell.jsx← [NEW] Background polling (10s), change checker, alert dropdown
│   │   │   ├── WorkloadView.jsx   ← [NEW] Groups employee tasks into complexity buckets
│   │   │   ├── InspectionQueue.jsx← Added dropdown selectors, card details expander, batch sign-offs
│   │   │   ├── BoardColumn.jsx    ← Added drop event listeners and drag target indicator states
│   │   │   ├── TicketCard.jsx     ← Draggable flags, computed stamped overlay status
│   │   │   └── Topbar.jsx         ← Swapped React imports, rendered Bell and Theme Toggle widgets
│   │   └── pages/
│   │       ├── EmployeeDashboard.jsx← Switch toggler and handleDropCard callback
│   │       └── ManagerDashboard.jsx  ← handleDropCard (with rejection dialog) callback
│   └── index.css                  ← CSS theme variables, transition timings, drag layouts
```

### 1. Global Themes & Layout Styles
* **File**: [index.css](file:///d:/GitHub/foreman-kanban/frontend/src/index.css)
* **Refactoring details**: 
  - Standard hex color codes in the root layout were replaced with CSS Custom Properties (`--bg`, `--panel`, `--hairline`, `--text`).
  - Dark variables are loaded by default.
  - Light theme variables are declared under the `[data-theme="light"]` attribute, switching elements to concrete-tinted backgrounds and dark charcoal text.
  - Smooth transitions (`0.25s ease`) were added across all layouts to eliminate flickering when switching themes.

### 2. State & Data Groups
* **File**: [WorkloadView.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/components/WorkloadView.jsx)
* **Refactoring details**:
  - Receives the employee's task array and runs client-side filters using complexity keys (`1`, `2`, `3`).
  - Dynamically calculates stage counts to render progress bars:
    $$\text{Progress \%} = \left( \frac{\text{Done Tasks}}{\text{Total Tasks in Bucket}} \right) \times 100$$
  - Reuses the existing `TicketCard` component inside each complexity lane.

### 3. Drag and Drop Engine
* **Files**: [TicketCard.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/components/TicketCard.jsx), [BoardColumn.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/components/BoardColumn.jsx)
* **Refactoring details**:
  - `TicketCard` sets drag data using `e.dataTransfer.setData('text/plain', ...)` and adds the `.is-dragging` class (lowering opacity to 0.35). Done tasks have `draggable={false}`.
  - `BoardColumn` listens to `dragover` (calls `preventDefault` to allow drop), `dragenter` (adds `.drag-over` dash highlights), `dragleave`, and `drop`.
  - On drop, the column extracts task data and triggers `onDropCard(taskId, fromStage, toStage)` in the dashboards.

---

## Part 3: Integration Blueprint (For Ibrahim)

Saad's frontend changes are integrated with Ibrahim's backend endpoints as follows:

### 1. Revision History Integration (`GET /api/tasks/{task_id}/history`)
* **Endpoint Consumer**: `InspectionQueue.jsx`
* **Trigger**: Clicking a card in the review queue toggles `expandedTaskId` and makes an asynchronous call to retrieve the history.
* **Payload Support**: The component parses both standard array envelopes and B1 schema objects containing `revisions` or `revision_history` fields to prevent data discrepancies:
  ```javascript
  const historyList = Array.isArray(res.data) 
    ? res.data 
    : (res.data.revisions || res.data.revision_history || []);
  ```
* **Fallback**: If Ibrahim's B1 backend branch is not merged or fails (returning a 404), the component catches the error and falls back to a clean *"No past rejections on this work order"* display.

### 2. Rejection Sign-off Integration (`POST /api/tasks/{task_id}/review` with action `reject`)
* **Endpoint Consumer**: `ManagerDashboard.jsx` (via drag-and-drop callback)
* **Trigger**: Dragging a task from the *For Inspection* column back into the *In Progress* column.
* **Flow**:
  1. The drag-drop handler triggers `window.prompt` requesting revision feedback.
  2. If feedback is provided, the card calls the reject endpoint.
  3. If the user cancels the prompt, the drop action is aborted and the card snaps back into place.

---

## Part 4: Quality & Compilation Audit

* **Linter Code Check (`npm run lint`)**:
  - **Result**: `Passed`
  - **Fixes**: Removed unused `React` imports, unused variable declarations, and dependencies warnings. Configured `/* eslint-disable react-refresh/only-export-components */` comments in the Context and Toast files to allow combined exports.
* **Vite Production Bundler Build (`npm run build`)**:
  - **Result**: `Passed`
  - **Asset Output**:
    - `dist/index.html` (0.79 kB)
    - `dist/assets/index.css` (19.72 kB)
    - `dist/assets/index.js` (377.55 kB)
    - **Build Time**: 201ms
