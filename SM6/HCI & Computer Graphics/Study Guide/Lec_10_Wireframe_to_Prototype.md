# CSC-335: HCI & Computer Graphics
## Lecture 10: From Wireframe to Prototype

---

## What is a Prototype?

A representation of a design made before the final solution exists.

---

## Why Prototype?

- You often don't know exactly how the system should work.
- Engineering and software development are expensive and time-consuming.
- Maximizes the number of times you get to revise and refine your design before committing to code.
- Each prototype is intended to answer one or more questions to help designers make decisions needed to advance their design.
- Prototyping enables testing of and receiving feedback on:
  - Overall design concept
  - Functionality of different components of a system
  - User interactions
  - Layouts
  - Fine-grain design details like fonts and color schemes

---

## Types of Prototypes

- **Physical Prototypes**
  - Function
  - Form
- **Service Prototypes**
  - Person-to-Person
  - Person-to-Technology
- **Environment Prototypes**

---

## Wireframes

A visual representation of screens of an interactive application that shows layout, types of information that are displayed, and elements of pointer-based navigation.

### Questions Wireframes Can Answer

- Do screens capture right chunks of system functionality?
- Are the components of a wireframe the right things to have on a single screen?
- Does the screen capture the right way those components should be presented to the user?
- Does the overall layout of components make sense?
- Do screens provide the right navigational elements?
- Would it be useful for users to receive a message with their progress and information about the day every morning?
- Is this the right information to present?
- Is the order of the information correct?
- Are these the right response options for step goal?
- How would a user finish interacting with this message?

### Questions Wireframes Do NOT Answer

- How should content be ordered? (e.g., results in a list)
- How does the user transition among multiple screens? (navigation often underspecified)
- What is the right visual design for the screen?
- What non-visual output is the system producing?

### How to Wireframe?

Wireframes can be created using several approaches:

- Hand-drawn sketches (pen and paper)
- Digital tools such as Figma, Balsamiq
- Purpose-specific tools for desktop apps, mobile apps, and web apps

### When to Create Wireframes?

- When the designer understands a chunk of functionality and wants to get feedback.
- When there are several ways something can be presented to users, and the designer needs to choose among them.
- When developers need to start planning the system backend.

---

## Wireframe vs. Low-Fi Prototype

| Property | Wireframe | Low-Fi Prototype |
|---|---|---|
| Fidelity | Very low | Low |
| Interactivity | None | Basic (clickable) |
| Purpose | Layout & structure | Flow & usability testing |
| Output | Static document | Clickable model |
| Tools | Figma, Balsamiq, pen & paper | Figma, Marvel, InVision |

---

## Low-Fidelity Interactive Prototypes

A representation of a design, made with lightweight tools and materials, that enables early testing of concepts, layouts, and user interactions.

Lo-fi prototyping maximizes the number of times designers get to revise and refine their design before it is committed to code.

### How to Prototype

- Start with wireframes for each screen of the task sequences you want to prototype.
- Create system responses (pop-ups, progress bars, etc.) that correspond to each action the user can do in the wireframes.
- Create dummy content (text, images, etc.) that would result from user actions (e.g., filling in the password).
- Try to ensure each user action transitions the prototype into a state that the prototype can support.
- Lo-Fi prototypes should support full task sequences.
- Transitions can often be effectively represented with very simple tools (e.g., cutouts, unfolding paper, etc.).

### Make it "Runnable"

Result: a representation of the design that can be "run" to provide stakeholders with an experience of how the system would behave.

### Summary of Lo-Fi Prototypes

- Lo-fi prototypes are cheap, disposable ways to interactively test early design ideas.
- Low fidelity focuses users on design concepts and interaction rather than minor design details.
- Repeated prototyping and testing enables rapid iteration and refinement of the design.

---

## Testing Lo-Fi Prototypes

### Step 1: Select Users

- If feasible, test the prototype with members of the target audience the system is intended to support.
- If target users are difficult to find, identify their important skills/context and find proxy users.
- Avoid users who would not give honest feedback.

### Step 2: Identify Testing Tasks

- Develop tasks that users should be able to accomplish using the prototype.
- Ensure the prototype supports these tasks fully.
- Create fake but realistic data to populate the prototype as the user moves through tasks.
- Ensure that the prototype can transition between tasks.

### Step 3: Find Testing Staff

- **Facilitator:** Interacts with users and provides instructions.
- **Computer:** Changes state of the prototype in response to user actions.
- **Observer:** Takes notes about user reactions and their feedback.

### Step 4: Conduct Test

- Ask users to complete each test task.
- Provide only clarification feedback; allow users to try to figure out how to do the tasks.
- Note where they get stuck, what confuses them, and if they can't transition between states.
- Discuss their experiences with using the prototype.

### Step 5: Evaluate and Use Test Results

- Identify common problems users experienced.
- Identify useful user suggestions for prototype improvement.
- Determine if any aspect of the prototype is sufficiently flawed that it needs to be completely rethought.
- Decide how to revise the prototype to account for feedback.
- Create new wireframes with revised functionality.

### Tips for Testing

- Basic usability problems (e.g., navigation) are often found after 1-2 testers.
- Revise the prototype before enrolling more testers.
- Often useful to give users time to just explore the prototype to familiarize themselves with it before starting test tasks.
- In post-test interview, get feedback both on the design concept and specific usability issues the user encountered.
- Create and test a new prototype as soon as the design has sufficiently changed.

---

## Classwork

Search up "Wizard of OZ" Prototypes.

---

## Mid-High Fidelity Prototypes

Mid-to-high fidelity prototypes are closer to the final product in look, feel, and interaction. They reflect more refined design decisions and are used for detailed usability testing and stakeholder demonstrations.

---

## Hi-Fi Prototypes

Prototypes that accurately reflect mature design and can be used as part of the system specification to guide implementation.

---

## Prototype Fidelity Comparison

| Type | Advantages | Disadvantages |
|---|---|---|
| **Low-fidelity prototype** | Lower development cost; Evaluates multiple design concepts; Useful communication device; Addresses screen layout issues; Useful for identifying market requirements; Proof of concept | Limited error checking; Poor detailed specification to code to; Facilitator-driven; Limited utility after requirements established; Limited usefulness for usability tests; Navigational and flow limitations |
| **High-fidelity prototype** | Complete functionality; Fully interactive; User-driven; Clearly defines navigational scheme; Use for exploration and test; Look and feel of final product; Serves as a living specification; Marketing and sales tool | More resource-intensive to develop; Time-consuming to create; Inefficient for proof-of-concept designs; Not effective for requirements gathering |

---

## Popular Prototyping Software

- Proto.io (http://proto.io)
- InVision (http://invisionapp.com)
- Marvel (http://marvelapp.com)
- JustinMind (http://justinmind.com)
- Framer (http://framer.com)
- Axure
- Sketch
- Adobe XD
- Adobe Illustrator
