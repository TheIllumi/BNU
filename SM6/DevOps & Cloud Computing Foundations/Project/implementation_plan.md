# Foreman Kanban Task Board — Project Execution Plan
**Saad's Frontend Implementation Blueprint & Source of Truth**

This document serves as the absolute Source of Truth for Saad's frontend work on the **Foreman Kanban Task Board** project. It outlines the project's architecture, Git workflow, detailed roadmap, feature-by-feature specifications, risks, and a step-by-step action plan. It is structured to allow future AI agents or developers to execute implementation tasks incrementally.

---

## Implementation Status Tracker

All identified frontend tasks are categorized below. As development progresses, tasks will move through these categories:

### 🔴 Not Started
* **F1: Enhanced Manager Review Queue** [Branch: `feature/frontend/review-queue`]
  - [ ] Add `filterEmployee` and `filterComplexity` dropdowns to `InspectionQueue.jsx`.
  - [ ] Implement client-side filtering logic for the queue.
  - [ ] Add expandable detail panel for each task in the queue.
  - [ ] Integrate B1's revision history and B4's audit trail fetching in the detail panel.
  - [ ] Implement "Confirm All" batch action button with API parallel calls.
  - [ ] Update index.css with queue enhancement styling.
* **F2: Employee Workload View** [Branch: `feature/frontend/workload-view`]
  - [ ] Create `WorkloadView.jsx` component.
  - [ ] Implement client-side complexity bucket grouping logic.
  - [ ] Create progress bar calculations and layout for each bucket.
  - [ ] Add Toggle switch ("Board View" / "Workload View") to `EmployeeDashboard.jsx`.
  - [ ] Style the workload view columns and progress bars in `index.css`.
* **F3: Drag-and-Drop Board** [Branch: `feature/frontend/drag-drop`]
  - [ ] Add HTML5 drag attributes and handlers to `TicketCard.jsx`.
  - [ ] Add drag enter/leave/over/drop listeners to `BoardColumn.jsx`.
  - [ ] Add `.drag-over` valid target indicator styling in `index.css`.
  - [ ] Implement `onDrop` handlers in `EmployeeDashboard.jsx` and `ManagerDashboard.jsx`.
  - [ ] Integrate API status machine actions into drop event handlers (start, submit, confirm, reject).
  - [ ] Add API error toast rollback handling.
* **F4: Dark/Light Theme Toggle** [Branch: `feature/frontend/dark-mode`]
  - [ ] Create theme utility helper functions in `theme.js`.
  - [ ] Restructure `index.css` to support CSS variables for dark and light theme tokens.
  - [ ] Add theme toggle button to `Topbar.jsx`.
  - [ ] Add theme initialization in `App.jsx`.
* **F5: Notification Bell** [Branch: `feature/frontend/notifications`]
  - [ ] Create `NotificationBell.jsx` component.
  - [ ] Implement client-side task polling with 10s interval.
  - [ ] Add task state change comparison logic (new assignment, review submitted, approved, rejected).
  - [ ] Store notification states in local state/memory with read status.
  - [ ] Render bell dropdown with unread badge and "Mark all as read" button in `Topbar.jsx`.
  - [ ] Style the notification bell and badge in `index.css`.

### 🟡 In Progress
* *None*

### 🔵 Blocked
* *None*

### 🟢 Ready for Review
* *None*

### ✅ Completed
* *None (Initial Setup Verified)*

---

## 1. Executive Summary

**Foreman** is an industrial-themed Kanban task board designed for teams that require an explicit, formal sign-off process before a job is marked completed. Unlike standard Kanban boards where any user can drag cards freely, Foreman enforces a **Pull Request review-and-merge workflow** for real-world physical and technical tasks.

### Core Workflow:
1. **Managers** open "Work Orders" (Tasks), specify their complexity (Low/Medium/High), and assign them to an **Employee**.
2. **Employees** see only their assigned work. They move tasks to `in_progress` ("Start Job") and then to `submitted_for_review` ("Submit for Inspection").
3. **Managers** review the submitted tasks in a centralized "Inspection Queue". They either **Confirm** (sign off, moving it to `done`) or **Send Back** (reject, returning it to `in_progress` with mandatory revision feedback).
4. No task can enter the `done` state without a manager's explicit seal of approval.

---

## 2. Project Architecture

The Foreman codebase is split into an independent client-server structure:

```mermaid
graph TD
    subgraph Frontend [Saad's Track: React + Vite Client]
        App[App.jsx] --> Topbar[Topbar.jsx]
        App --> Auth[AuthScreen.jsx]
        App --> EDash[EmployeeDashboard.jsx]
        App --> MDash[ManagerDashboard.jsx]
        EDash --> BoardColE[BoardColumn.jsx]
        MDash --> BoardColM[BoardColumn.jsx]
        MDash --> Queue[InspectionQueue.jsx]
        Queue --> RejectPanel[RejectPanel.jsx]
        BoardColE --> TicketCard[TicketCard.jsx]
        BoardColM --> TicketCard
        ThemeUtils[theme.js] -.-> App
        APIUtils[api.js Axios] -.-> App
    end

    subgraph Backend [Ibrahim's Track: FastAPI Server]
        FastAPI[app.main:app] --> AuthRouter[auth_routes.py]
        FastAPI --> TaskRouter[task_routes.py]
        FastAPI --> AnalyticsRouter[analytics_routes.py]
        FastAPI --> AuditRouter[audit_routes.py]
        TaskRouter --> StatusMachine[status_machine.py]
    end

    subgraph Database & Cloud
        AuthRouter --> Firebase[Firebase Auth]
        TaskRouter --> Mongo[MongoDB Atlas]
        AuditRouter --> Mongo
    end

    APIUtils -- HTTPS / CORS --> FastAPI
    APIUtils -- Bearer Token --> Firebase
```

### Architectural Specifications:
* **Frontend**: Built with **React 19**, **Vite**, and **Axios**. State is managed in React Context (`AuthContext.jsx`) and local component state. Styling uses **Vanilla CSS** (`index.css`) designed with an industrial aesthetic (Oswald and Inter fonts, dark metal panels, amber highlights, and physical-paper card textures).
* **Backend**: **FastAPI** (Python 3.10+) serving a REST API. Enforces the status machine transitions using a dedicated validation library.
* **Database**: **MongoDB Atlas** storing tasks, users, and audit logs.
* **Authentication**: **Firebase Web SDK** on the client, verified using **Firebase Admin SDK** on the backend.
* **Deployment**: Frontend is hosted on Vercel; Backend is hosted on Render.
* **Containerization**: `Dockerfile` is provided for both frontend and backend for local Kubernetes (`minikube`) and Docker Compose development.

---

## 3. My Responsibilities (Saad)

As the **Senior Frontend Engineer**, Saad is responsible for all code under the `frontend/` directory.

### Key Deliverables:
1. **Feature Implementation**: Complete increments F1 through F5 on separate branches.
2. **Design Integrity**: Maintain the industrial/workshop visual language (pin-board metaphor, rivet details, stamp-style animations) in both dark and light modes.
3. **Local Docker/K8s Testing**: Build the frontend Docker image (`foreman-frontend:dev`) and run it locally. Verify it inside the local `minikube` cluster before submitting pull requests.
4. **Integration Coordination**: Coordinate with Ibrahim (Backend) to consume new endpoints (e.g. revision history, audit trail) as they are deployed.

### Feature Dependencies:
* **F1 Details Section**: Depends on Ibrahim completing backend feature **B1** (`GET /api/tasks/{task_id}/history`) and **B4** (`GET /api/tasks/{task_id}/audit`). If backend endpoints are not ready, Saad must mock this data or fall back to client-side task data until B1/B4 are integrated.
* **F3 Drag-and-Drop Operations**: Relies on existing backend endpoints `/start`, `/submit`, and `/review`. No backend changes required.
* **F5 Polling / Task Detection**: Relies on the existing `GET /api/tasks` endpoint.

---

## 4. Git Workflow

We adhere to a strict integration model. **Only Ismail (PR Manager) merges code into `develop` and `main`.**

### Branch Hierarchy:
```
main (Production Release)
  ▲
  │ (Ismail Merges Only)
  ▼
develop (Integration Branch)
  ▲
  ├── feature/frontend/review-queue (F1)
  ├── feature/frontend/workload-view (F2)
  ├── feature/frontend/drag-drop (F3)
  ├── feature/frontend/dark-mode (F4)
  └── feature/frontend/notifications (F5)
```

### Git Rules:
1. **Branch Naming**: Feature branches must be named exactly `feature/frontend/<feature-name>`.
2. **Base Branch**: Always branch off `develop`. Always pull the latest `develop` branch before coding.
3. **Commits**: Split work into multiple logical, atomic commits. Avoid monolithic "completed feature" commits.
4. **No Direct Merges**: Do not merge your own branch. Open a Pull Request (PR) from your branch to `develop`.

### Example Command Sequence:
```bash
# Start a new feature
git checkout develop
git pull origin develop
git checkout -b feature/frontend/review-queue

# Work, test, lint...
git add -A
git commit -m "feat(frontend): add filter controls to review queue"

# Deploy & test locally in Docker
docker build -t foreman-frontend:dev ./frontend
docker compose up -d

# Push and open PR
git push origin feature/frontend/review-queue
```

---

## 5. Frontend Development Roadmap

```mermaid
gantt
    title Frontend Implementation Schedule
    dateFormat  YYYY-MM-DD
    section Phase 1: Core Queue & Alternate Views
    F1: Review Queue Filters & Details    :active, f1, 2026-06-22, 3d
    F2: Employee Workload Grouping        : f2, after f1, 2d
    section Phase 2: UX Improvements
    F3: Drag & Drop Card Transition       : f3, after f2, 3d
    F4: Theme Switcher & CSS Refactoring  : f4, after f3, 2d
    section Phase 3: Notifications & Polling
    F5: Notification Bell Component       : f5, after f4, 3d
    section Finalization
    Docker & K8s Verification            : after f5, 2d
    Regression Test & Demo prep          : 2d
```

### Phase 1: Core Queue & Alternate Views
* **F1 Objectives**: Expand the manager dashboard's capability to filter by crew member and complexity level, add collapsible details, and enable batch approval.
* **F2 Objectives**: Implement employee dashboard groupings to toggle between standard stage-based lanes and task complexity buckets.

### Phase 2: UX Improvements
* **F3 Objectives**: Implement HTML5 drag-and-drop mechanics to move cards between columns, complete with drop target borders and backend rejection fallback logic.
* **F4 Objectives**: Refactor global CSS to utilize semantic theme tokens; write dark/light theme stylesheet and theme switcher widget.

### Phase 3: Notifications & Polling
* **F5 Objectives**: Implement client-side periodic polling to compare task states and push local alerts inside a notification dropdown.

---

## 6. Detailed Feature Breakdown & Blueprints

---

### [F1] Enhanced Manager Review Queue
* **Purpose**: Enhance the manager's review panel to handle sorting/filtering, task audit histories, and batch completion to increase oversight efficiency.
* **User Flow**:
  1. Manager views the Inspection Queue.
  2. Selects an Employee or Complexity level from dropdown selectors.
  3. Clicking any task card in the queue expands the details panel downwards to display the description, assignee, and past rejection comments.
  4. Clicking "Confirm All" runs a batch approval on all currently filtered/visible tasks.
* **Technical Blueprint**:
  - Add state variables in `InspectionQueue.jsx`:
    ```javascript
    const [filterEmployee, setFilterEmployee] = useState('all');
    const [filterComplexity, setFilterComplexity] = useState('all');
    const [expandedTaskId, setExpandedTaskId] = useState(null);
    const [historyCache, setHistoryCache] = useState({}); // { taskId: [revisions] }
    ```
  - Fetch history data from B1's endpoint `GET /api/tasks/{task_id}/history` when `expandedTaskId` matches a task, caching it in `historyCache` to avoid duplicate requests.
  - Implement client-side filtering:
    ```javascript
    const filteredTasks = tasks.filter(task => {
      const matchEmp = filterEmployee === 'all' || task.assigned_to === filterEmployee;
      const matchComp = filterComplexity === 'all' || task.complexity.toString() === filterComplexity;
      return matchEmp && matchComp;
    });
    ```
  - **Confirm All Handler**:
    ```javascript
    async function handleConfirmAll() {
      const confirmPromises = filteredTasks.map(t => onConfirm(t.id));
      await Promise.all(confirmPromises);
    }
    ```
* **Required Files**:
  - [InspectionQueue.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/components/InspectionQueue.jsx)
  - [index.css](file:///d:/GitHub/foreman-kanban/frontend/src/index.css)
* **Testing Requirements**:
  - Verify that selecting employee "A" hides employee "B"'s cards.
  - Verify expanding a card loads the revisions list.
  - Verify clicking "Confirm All" triggers calls for all visible cards and refetches the list.
* **Git Branch**: `feature/frontend/review-queue`
* **Parent Branch**: `develop`
* **Suggested Commit Breakdown**:
  1. `feat(frontend): add filter dropdowns and filter state to InspectionQueue`
  2. `feat(frontend): implement collapsible details panel and render assignee details`
  3. `feat(frontend): integrate task history endpoint in detail expansion`
  4. `feat(frontend): add Confirm All batch action with parallel promises`
  5. `style(frontend): style new review queue layout, filters, and animation transitions`
* **PR Template**:
  - **Title**: `Frontend: Enhanced Manager Review Queue`
  - **Description**:
    * Adds filter dropdowns (Employee, Complexity) to the review queue.
    * Adds an expandable details pane for each pending task.
    * Integrates task history fetching on card expand.
    * Adds a "Confirm All" button to approve all visible cards in bulk.

---

### [F2] Employee Workload View
* **Purpose**: Provide employees with a workload-oriented grouping of tasks by complexity level so they can prioritize their queue.
* **User Flow**:
  1. Employee clicks the "Workload View" toggle button on their dashboard.
  2. The board switches from 4 stage columns to 3 complexity columns (Low, Medium, High).
  3. Each complexity column features a header showing task totals, progress bars showing percent complete (`done` tasks / total tasks), and a stack of TicketCards.
  4. Employee can toggle back to "Board View" at any time.
* **Technical Blueprint**:
  - Introduce `viewMode` toggle state in `EmployeeDashboard.jsx`:
    ```javascript
    const [viewMode, setViewMode] = useState('board'); // 'board' | 'workload'
    ```
  - Create `WorkloadView.jsx` component:
    * Props: `tasks` (array), `onStart` (fn), `onSubmit` (fn).
    * Internal grouping:
      ```javascript
      const lowTasks = tasks.filter(t => t.complexity === 1);
      const medTasks = tasks.filter(t => t.complexity === 2);
      const highTasks = tasks.filter(t => t.complexity === 3);
      ```
    * Render layout with three `.workload-column` containers.
    * Progress bar calculation helper:
      ```javascript
      const calcProgress = (bucketTasks) => {
        if (!bucketTasks.length) return 0;
        const doneCount = bucketTasks.filter(t => t.stage === 'done').length;
        return Math.round((doneCount / bucketTasks.length) * 100);
      };
      ```
* **Required Files**:
  - [EmployeeDashboard.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/pages/EmployeeDashboard.jsx)
  - [WorkloadView.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/components/WorkloadView.jsx) (NEW)
  - [index.css](file:///d:/GitHub/foreman-kanban/frontend/src/index.css)
* **Testing Requirements**:
  - Verify switching the toggle swaps the visual panels instantly.
  - Verify progress bar calculates `0` for empty columns, and matches the mathematical ratio for occupied columns.
  - Confirm task operations ("Start Job", "Submit") work seamlessly within the workload grouping layout.
* **Git Branch**: `feature/frontend/workload-view`
* **Parent Branch**: `develop`
* **Suggested Commit Breakdown**:
  1. `feat(frontend): create WorkloadView component with complexity grouping`
  2. `feat(frontend): implement progress bar calculation per complexity lane`
  3. `feat(frontend): integrate view toggle state in EmployeeDashboard`
  4. `style(frontend): add styles for workload view layout, progress bars, and toggle`
* **PR Template**:
  - **Title**: `Frontend: Employee Workload View`
  - **Description**:
    * Adds dashboard toggle to switch between standard board and complexity workload view.
    * Introduces `WorkloadView` displaying tasks in Low/Medium/High columns.
    * Implements stage completion progress bars for each complexity bucket.

---

### [F3] Drag-and-Drop Board
* **Purpose**: Replace manual task movement buttons with a visual drag-and-drop mechanism across board columns, keeping role-based restrictions active.
* **User Flow**:
  1. User hovers their mouse over a ticket, clicks, and drags.
  2. Valid target columns highlight (amber boarder glow).
  3. User drops the ticket on a column.
  4. If transition is legal: card animates, moves to the column, and API success toast is shown.
  5. If transition is illegal: target column rejects the drop, card snaps back, and error toast flashes detailing the status machine rejection.
* **Technical Blueprint**:
  - **`TicketCard.jsx` changes**:
    * Add `draggable="true"` property.
    * Attach handlers:
      ```javascript
      const handleDragStart = (e) => {
        e.dataTransfer.setData('text/plain', JSON.stringify({ taskId: task.id, fromStage: task.stage }));
        e.currentTarget.classList.add('dragging');
      };
      const handleDragEnd = (e) => {
        e.currentTarget.classList.remove('dragging');
      };
      ```
  - **`BoardColumn.jsx` changes**:
    * Add listeners:
      ```javascript
      const handleDragOver = (e) => {
        e.preventDefault(); // Required to allow drop
      };
      const handleDragEnter = (e) => {
        e.currentTarget.classList.add('drag-over');
      };
      const handleDragLeave = (e) => {
        e.currentTarget.classList.remove('drag-over');
      };
      const handleDropEvent = (e) => {
        e.preventDefault();
        e.currentTarget.classList.remove('drag-over');
        const data = JSON.parse(e.dataTransfer.getData('text/plain'));
        onDropCard?.(data.taskId, data.fromStage, stage);
      };
      ```
  - **Dashboard/Page Callback Hookups**:
    * Employees:
      - Can move `todo` -> `in_progress` (calls `handleStart`)
      - Can move `in_progress` -> `submitted_for_review` (calls `handleSubmit`)
      - Other moves show: "Only managers can sign off or reject submissions."
    * Managers:
      - Can move `submitted_for_review` -> `done` (calls `handleConfirm`)
      - Can move `submitted_for_review` -> `in_progress` (triggers the `RejectPanel` inline textbox to capture revision feedback, then calls `handleReject`)
* **Required Files**:
  - [TicketCard.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/components/TicketCard.jsx)
  - [BoardColumn.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/components/BoardColumn.jsx)
  - [EmployeeDashboard.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/pages/EmployeeDashboard.jsx)
  - [ManagerDashboard.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/pages/ManagerDashboard.jsx)
  - [index.css](file:///d:/GitHub/foreman-kanban/frontend/src/index.css)
* **Testing Requirements**:
  - Verify dragging employee cards into different lanes updates database states correctly.
  - Verify illegal transitions (e.g. employee dragging from `todo` straight to `done`) trigger error toasts and revert state.
  - Test dragging cards on Manager dashboard into `in_progress` prompts for rejection reason.
* **Git Branch**: `feature/frontend/drag-drop`
* **Parent Branch**: `develop`
* **Suggested Commit Breakdown**:
  1. `feat(frontend): add dragStart and dragEnd events to TicketCard`
  2. `feat(frontend): add drop target handlers and drop callback to BoardColumn`
  3. `feat(frontend): integrate drag-and-drop routing in EmployeeDashboard`
  4. `feat(frontend): integrate drag-and-drop routing + reject dialog overlay in ManagerDashboard`
  5. `style(frontend): add drag-over styles and drag transparency animations`
* **PR Template**:
  - **Title**: `Frontend: Drag-and-Drop Kanban Board Interaction`
  - **Description**:
    * Implements HTML5 drag-and-drop for TicketCards.
    * Animates and highlights columns during drag-over states.
    * Hooks drop actions directly to existing FastAPI status endpoints.
    * Validates permissions client-side and surfaces error toast alerts on failures.

---

### [F4] Dark/Light Theme Toggle
* **Purpose**: Integrate theme switching functionality allowing the interface to toggle between the default Dark workshop theme and a Light workshop layout.
* **User Flow**:
  1. User looks at the navigation bar, sees a Sun/Moon theme button.
  2. Clicks button: interface slides colors from dark charcoal to a high-contrast industrial light theme (manila paper board, concrete backgrounds, steel accents).
  3. Choosing light mode is saved: reloading the page maintains light mode.
* **Technical Blueprint**:
  - Create `theme.js` utility helper file:
    ```javascript
    export const getStoredTheme = () => localStorage.getItem('theme') || 'dark';
    export const setStoredTheme = (theme) => {
      localStorage.setItem('theme', theme);
      document.documentElement.setAttribute('data-theme', theme);
    };
    export const initTheme = () => {
      const theme = getStoredTheme();
      document.documentElement.setAttribute('data-theme', theme);
    };
    ```
  - **Theme Variable Restructuring** in `index.css`:
    ```css
    :root {
      /* Dark Theme Tokens (Default) */
      --bg: #15130F;
      --bg-grid: #1B1812;
      --panel: #1E1B16;
      --panel-raised: #25211A;
      --hairline: #3A3528;
      --text: #ECE6D9;
      --text-muted: #9A9281;
      --paper: #FAF6EC;
      --ink: #2B2620;
      /* Constants */
      --amber: #E8A23D;
      --stamp-red: #C1432A;
      --stamp-green: #4C7A4C;
      --transition-speed: 0.25s ease;
    }
    
    [data-theme="light"] {
      /* Light Theme Tokens */
      --bg: #EAE5D9;
      --bg-grid: #DDD8CB;
      --panel: #DFD9CD;
      --panel-raised: #D5CEBF;
      --hairline: #B5AB96;
      --text: #1E1B16;
      --text-muted: #625B4E;
      --paper: #FDFBF7;
      --ink: #110F0C;
    }
    ```
  - Add smooth transitions on layout panels: `transition: background-color var(--transition-speed), color var(--transition-speed);`
  - In `Topbar.jsx`, add toggle icon:
    ```javascript
    const [theme, setTheme] = useState(getStoredTheme());
    const toggleTheme = () => {
      const nextTheme = theme === 'dark' ? 'light' : 'dark';
      setTheme(nextTheme);
      setStoredTheme(nextTheme);
    };
    ```
* **Required Files**:
  - [theme.js](file:///d:/GitHub/foreman-kanban/frontend/src/utils/theme.js) (NEW)
  - [index.css](file:///d:/GitHub/foreman-kanban/frontend/src/index.css)
  - [Topbar.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/components/Topbar.jsx)
  - [App.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/App.jsx)
* **Testing Requirements**:
  - Verify background color transitions smoothly when toggle is clicked.
  - Verify color contrast in light mode is high and matches WCAG guidelines.
  - Refresh browser in light mode to confirm state persists.
* **Git Branch**: `feature/frontend/dark-mode`
* **Parent Branch**: `develop`
* **Suggested Commit Breakdown**:
  1. `feat(frontend): create theme management utility with localstorage persistence`
  2. `style(frontend): rewrite index.css variables to utilize custom attributes`
  3. `feat(frontend): integrate data-theme initialize on application launch`
  4. `feat(frontend): build Topbar theme switcher button and link state`
  5. `style(frontend): add smooth transitions to layout and interactive elements`
* **PR Template**:
  - **Title**: `Frontend: Light/Dark Mode Custom Theme Toggle`
  - **Description**:
    * Restructured color system using CSS Custom Properties.
    * Added Light theme variant styled for industrial high contrast.
    * Introduced theme switcher button in Topbar header.
    * Implemented localStorage theme preference caching.

---

### [F5] Notification Bell
* **Purpose**: Keep team members updated on workflow actions in real-time through an inline notification tray and active polling checks.
* **User Flow**:
  1. User stays active on their dashboard.
  2. When another user changes a task state (e.g. manager confirms an employee's work order), the notification bell in the header glows amber and increments its badge.
  3. Clicking the bell lists notifications: "Work order #38290 approved by Manager".
  4. User clicks "Mark all as read" to clear notifications and reset badge.
* **Technical Blueprint**:
  - Create `NotificationBell.jsx` component:
    * Maintain notifications array:
      ```javascript
      const [notifications, setNotifications] = useState([]);
      const [isOpen, setIsOpen] = useState(false);
      const prevTasksRef = useRef([]);
      ```
    * Implement polling:
      ```javascript
      useEffect(() => {
        const interval = setInterval(async () => {
          try {
            const res = await api.get('/api/tasks');
            detectChanges(res.data);
          } catch(e) { console.error(e); }
        }, 10000); // 10s poll
        return () => clearInterval(interval);
      }, [currentUser]);
      ```
    * **State Difference Logic**:
      ```javascript
      const detectChanges = (newTasks) => {
        const prevTasks = prevTasksRef.current;
        if (!prevTasks.length) {
          prevTasksRef.current = newTasks;
          return;
        }
        
        const newAlerts = [];
        newTasks.forEach(task => {
          const oldTask = prevTasks.find(t => t.id === task.id);
          if (!oldTask) {
            // New Task created
            if (userProfile.role === 'employee' && task.assigned_to === userProfile.firebase_uid) {
              newAlerts.push({ id: task.id + '-new', text: `New Work Order assigned: "${task.title}"`, read: false });
            }
          } else if (oldTask.stage !== task.stage) {
            // Status change
            if (userProfile.role === 'employee' && task.assigned_to === userProfile.firebase_uid) {
              if (task.stage === 'done') {
                newAlerts.push({ id: task.id + '-done', text: `Work Order approved: "${task.title}"`, read: false });
              } else if (task.stage === 'in_progress' && task.is_rejected) {
                newAlerts.push({ id: task.id + '-rejected', text: `Work Order sent back: "${task.title}"`, read: false });
              }
            } else if (userProfile.role === 'manager' && task.stage === 'submitted_for_review') {
              newAlerts.push({ id: task.id + '-review', text: `New submission waiting inspection: "${task.title}"`, read: false });
            }
          }
        });
        
        if (newAlerts.length) {
          setNotifications(prev => [...newAlerts, ...prev]);
        }
        prevTasksRef.current = newTasks;
      };
      ```
* **Required Files**:
  - [NotificationBell.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/components/NotificationBell.jsx) (NEW)
  - [Topbar.jsx](file:///d:/GitHub/foreman-kanban/frontend/src/components/Topbar.jsx)
  - [index.css](file:///d:/GitHub/foreman-kanban/frontend/src/index.css)
* **Testing Requirements**:
  - Trigger mock task status changes and confirm notifications appear within 10 seconds.
  - Verify badge count matches the list count of unread objects.
  - Confirm bell dropdown doesn't overflow container bounds on mobile displays.
* **Git Branch**: `feature/frontend/notifications`
* **Parent Branch**: `develop`
* **Suggested Commit Breakdown**:
  1. `feat(frontend): create notification bell panel markup and base display states`
  2. `feat(frontend): write hook comparison logic to detect task changes`
  3. `feat(frontend): implement local state notification list array and badge`
  4. `feat(frontend): integrate bell widget next to logout in Topbar`
  5. `style(frontend): style unread badge glows, dropdown layouts, list items`
* **PR Template**:
  - **Title**: `Frontend: Notification Bell Notification Service`
  - **Description**:
    * Implements periodic REST API polling for task updates.
    * Compares current payload against previous states to filter out changes.
    * Displays notification drawer containing task event list.
    * Hooks amber indicator badges inside the main Topbar panel.

---

## 7. Commit Strategy

We commit work in small, incremental stages showing stable progression. Below is the reference blueprint showing Saad's commit log history across his feature branches:

```
─────────────────────────────────────────────────────────────────────────────
BRANCH: feature/frontend/review-queue
  commit 1: feat(frontend): add filter dropdowns and filter state to InspectionQueue
  commit 2: feat(frontend): implement collapsible details panel and render assignee details
  commit 3: feat(frontend): integrate task history endpoint in detail expansion
  commit 4: feat(frontend): add Confirm All batch action with parallel promises
  commit 5: style(frontend): style new review queue layout, filters, and animation transitions

BRANCH: feature/frontend/workload-view
  commit 6: feat(frontend): create WorkloadView component with complexity grouping
  commit 7: feat(frontend): implement progress bar calculation per complexity lane
  commit 8: feat(frontend): integrate view toggle state in EmployeeDashboard
  commit 9: style(frontend): add styles for workload view layout, progress bars, and toggle

BRANCH: feature/frontend/drag-drop
  commit 10: feat(frontend): add dragStart and dragEnd events to TicketCard
  commit 11: feat(frontend): add drop target handlers and drop callback to BoardColumn
  commit 12: feat(frontend): integrate drag-and-drop routing in EmployeeDashboard
  commit 13: feat(frontend): integrate drag-and-drop routing + reject dialog overlay in ManagerDashboard
  commit 14: style(frontend): add drag-over styles and drag transparency animations

BRANCH: feature/frontend/dark-mode
  commit 15: feat(frontend): create theme management utility with localstorage persistence
  commit 16: style(frontend): rewrite index.css variables to utilize custom attributes
  commit 17: feat(frontend): integrate data-theme initialize on application launch
  commit 18: feat(frontend): build Topbar theme switcher button and link state
  commit 19: style(frontend): add smooth transitions to layout and interactive elements

BRANCH: feature/frontend/notifications
  commit 20: feat(frontend): create notification bell panel markup and base display states
  commit 21: feat(frontend): write hook comparison logic to detect task changes
  commit 22: feat(frontend): implement local state notification list array and badge
  commit 23: feat(frontend): integrate bell widget next to logout in Topbar
  commit 24: style(frontend): style unread badge glows, dropdown layouts, list items
─────────────────────────────────────────────────────────────────────────────
```

---

## 8. Development Sequence

To avoid integration blockers, Saad should implement features in the following order:

1. **Setup Env & Docker (`develop` branch)**: Ensure the project runs locally via `npm run dev` and environment variables are loaded. Verify Docker build works for development dependencies.
2. **Feature 1 (Enhanced Manager Review Queue)**: Standard UI enhancement. Does not require advanced interactions. Builds familiarity with the workspace components.
3. **Feature 2 (Employee Workload View)**: Pure client-side refactoring of data. Safe, non-intrusive UI additions.
4. **Feature 4 (Dark/Light Theme Toggle)**: Restructures the entire global CSS variables. Doing this *before* drag-and-drop guarantees that color highlights (`.drag-over` states) are themed correctly.
5. **Feature 3 (Drag-and-Drop Board)**: Highly interactive. Relies on structured styles and themes already completed in Feature 4.
6. **Feature 5 (Notification Bell)**: Builds on top of all other status features. Polling captures updates from drag/drop events and reviews.

---

## 9. Risk Analysis

| Risk Area | Severity | Impact | Mitigation Strategy |
| :--- | :--- | :--- | :--- |
| **Backend Integration (B1/B4)** | Medium | F1 expansion details might fail to show history if Ibrahim's backend is not completed yet. | Saad will build dummy historical data inside the frontend component if the API returns 404, ensuring the UI remains operational. |
| **Theme Refactoring (F4)** | Medium | CSS restructure could break existing layouts. | Perform global layout regression tests after converting standard HEX values to CSS variable names. |
| **State Drag Rollbacks (F3)** | High | API failures on illegal drags might leave cards in wrong lanes (UI desync). | Implement an instant rollback operation. The card must snap back to its parent `fromStage` lane if the Axios request rejects. |
| **Network Polling Overhead (F5)** | Low | Polling `/api/tasks` every 10 seconds might strain the browser or mock server database connections. | Utilize a simple `useRef` to store previous counts. Throttle payload processing if data hasn't updated. |
| **Kubernetes Sync** | Low | Local pod out of sync with Docker updates. | Always rebuild and tag with explicit version identifiers (`foreman-frontend:dev`) before running `kubectl apply`. |

---

## 10. Questions for Team Leads

Saad should clarify the following items with leadership:
* **To Ismail (PR Manager)**:
  - Do we want theme selections saved to the user profile collection in MongoDB, or is `localStorage` sufficient?
  - Are we planning to support analytics views (B2 workload endpoints or B5 metrics) on the Manager Dashboard frontend in a later phase, or should we display a read-only analytics grid now?
* **To Backend Team (Ibrahim)**:
  - What is the exact payload structure returned by `GET /api/tasks/{task_id}/history`? Will it match `RevisionEntry` fields precisely?
  - Will the base `GET /api/tasks` endpoint eventually return the `revision_count` directly to prevent extra fetch overhead in F1?
* **To DevOps Team**:
  - Should the Dockerfile target container staging builds or use simple nginx reverse-proxy configurations? (Currently we see a `nginx.conf` in the project directories).

---

## 11. Final Action Plan

Execute these steps in order to start contributing:

### Step 1: Environment Setup
1. Clone the repository and checkout `develop`.
2. Move into the `frontend` folder: `cd frontend`.
3. Create file `.env` and paste the credentials provided in the Environment Setup Guide:
   ```env
   VITE_API_URL=http://localhost:8000
   VITE_FIREBASE_API_KEY=AIzaSyDuDfvIxAJQXvpRPf36--dN6OQpGhK9-QM
   VITE_FIREBASE_AUTH_DOMAIN=foreman-kanban.firebaseapp.com
   VITE_FIREBASE_PROJECT_ID=foreman-kanban
   VITE_FIREBASE_STORAGE_BUCKET=foreman-kanban.firebasestorage.app
   VITE_FIREBASE_MESSAGING_SENDER_ID=599549835519
   VITE_FIREBASE_APP_ID=1:599549835519:web:c4d55483745ae1ec7e74ca
   ```
4. Run `npm install` followed by `npm run dev`. Verify the login screen appears on `localhost:5173`.
5. Run node environment validation check:
   ```bash
   node -e "console.log('✅ API Key:', process.env.VITE_FIREBASE_API_KEY ? 'loaded' : 'NOT SET')"
   ```

### Step 2: Initialize Docker & Kubernetes Verification
1. Verify Docker is running.
2. Build the frontend image: `docker build -t foreman-frontend:dev ./frontend`.
3. Run container locally: `docker run -d -p 3000:80 foreman-frontend:dev`.
4. Ensure site loads correctly on `http://localhost:3000`.

### Step 3: Implement Feature F1 (Manager Review Queue)
1. Checkout the branch: `git checkout -b feature/frontend/review-queue`.
2. Edit `InspectionQueue.jsx` to introduce employee and complexity filter states.
3. Construct the collapsible details panel container.
4. Implement the fetch hook to call B1's history endpoint on expand.
5. Create the "Confirm All" handler.
6. Verify locally. Run linter: `npm run lint`.
7. Build container and check in minikube: `kubectl rollout restart deployment/frontend`.
8. Commit work incrementally, push branch, and open PR.
