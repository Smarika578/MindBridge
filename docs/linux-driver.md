# ⚙️ MindBridge Linux Character Device Driver

> **A lightweight bridge between the MindBridge C++ application and the Linux kernel.**

## 🔹 Overview

MindBridge includes a custom Linux **character-device kernel module** written in C.

It exposes a virtual device:

```text
/dev/mindbridge

The C++ application writes selected mood information to this device, demonstrating user-space ↔ kernel-space communication
┌──────────────┐
│ MindBridge   │
│ C++ / SFML   │
└──────┬───────┘
       │ write()
       ▼
┌──────────────┐
│ /dev/        │
│ mindbridge   │
└──────┬───────┘
       ▼
┌──────────────┐
│ Linux Kernel │
│ Module       │
└──────┬───────┘
       ▼
┌──────────────┐
│ Kernel       │
│ Buffer       │
└──────────────┘
🔹 Why a Character Device?

A character device provides a simple stream-based interface between user applications and kernel components.

For MindBridge, it provides a practical way to demonstrate how a normal C++ application can communicate with Linux kernel space.

| Operation                   | Purpose                                  |
| --------------------------- | ---------------------------------------- |
| `write()`                   | Receives mood data from the application  |
| `read()`                    | Returns stored data                      |
| `copy_from_user()`          | Safely transfers data into kernel space  |
| `simple_read_from_buffer()` | Transfers kernel data back to user space |
| `mutex`                     | Protects the shared kernel buffer        |


🔹 Application → Kernel Flow

When the user selects a mood such as Calm:

User selects mood
       ↓
C++ / SFML application
       ↓
/dev/mindbridge
       ↓
mb_write()
       ↓
copy_from_user()
       ↓
Kernel buffer






🔹 Module Lifecycle
Load
make
sudo insmod mindbridge.ko
insmod
  ↓
module_init()
  ↓
misc_register()
  ↓
/dev/mindbridge
Remove
sudo rmmod mindbridge
rmmod
  ↓
module_exit()
  ↓
misc_deregister()
  ↓




🔹 Manual Testing

Write data:

echo "Mood: Calm" | sudo tee /dev/mindbridge

Read data:

sudo cat /dev/mindbridge

Expected:

Mood: Calm



🔹 Linux Concepts Demonstrated
Linux Kernel Modules
Character Devices
/dev device interface
User Space vs Kernel Space
File Operations
copy_from_user()
Kernel Buffer Management
Mutex Synchronization
Module Initialization & Cleanup
insmod / rmmod
User-space / kernel-space communication




🔹 Design Choice

The driver is a virtual character device, not a physical hardware driver.

This keeps the implementation lightweight while demonstrating genuine Linux system-programming concepts and providing a clear communication path between the MindBridge application and the kernel.
