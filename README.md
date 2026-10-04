# 🧠 MindBridge

### Offline Mental Wellness Companion with Linux System-Level Integration

<p align="center">

**A privacy-focused, offline-first C++ desktop application connected to a custom Linux character-device kernel module.**

</p>

---

## 🌿 About MindBridge

**MindBridge** is a Linux-based desktop application designed to provide a simple, private and distraction-free environment for basic mental wellness activities.

Unlike a typical student GUI project, MindBridge explores what happens **below the application layer**.

The project combines:

- 🎨 A C++ graphical desktop application
- 🐧 Linux system programming
- ⚙️ A custom character-device kernel module
- 🔄 User-space ↔ kernel-space communication
- 🔒 Local-first data handling
- 💬 Offline rule-based conversational support

The application does not depend on cloud services or external AI APIs for its core functionality.

> **MindBridge is an academic software prototype and is not intended to diagnose, treat, or replace professional mental-health care.**

---

# 💡 The Idea Behind MindBridge

Many applications focus only on building a user interface.

MindBridge takes a different approach:

> **Build the application — and understand the Linux system underneath it.**

The project was designed to connect a user-facing C++ application with a Linux kernel component.

When a user selects a mood, the application performs two operations:

```text
                 User selects mood
                         │
                         ▼
              ┌───────────────────┐
              │  MindBridge GUI    │
              │     C++ / SFML     │
              └─────────┬─────────┘
                        │
                Local storage
                        │
                        ▼
              ┌───────────────────┐
              │ /dev/mindbridge   │
              │ Character Device  │
              └─────────┬─────────┘
                        │
                        ▼
              ┌───────────────────┐
              │ Linux Kernel      │
              │ Module written C  │
              └───────────────────┘
