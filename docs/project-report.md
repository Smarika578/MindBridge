# MindBridge Project Report

## 1. Introduction

MindBridge is an offline mental wellness companion developed as a Linux-based C++ desktop application.

The project combines a graphical user interface with Linux system-level programming through a custom character-device kernel module.

## 2. Problem Statement

Many modern applications depend on internet connectivity and external services.

MindBridge explores an offline-first approach where basic wellness features such as mood tracking, journaling, breathing guidance and supportive rule-based conversation work locally.

## 3. Objectives

- Develop a Linux desktop application using C++.
- Provide an offline user interface.
- Implement local mood tracking.
- Implement local journaling.
- Provide guided breathing.
- Develop a custom Linux character-device kernel module.
- Demonstrate user-space and kernel-space communication.

## 4. Technologies

- C++
- C
- Linux
- SFML
- Linux Kernel Modules
- Character Device
- Git and GitHub

## 5. Features

### Chat
Provides predefined supportive responses based on user input.

### Mood Tracking
Allows the user to select Happy, Calm or Sad.

### Journal
Allows users to store journal entries locally.

### Breathing
Provides a simple guided breathing exercise.

### Linux Driver
The application communicates with `/dev/mindbridge`.

## 6. Architecture

```text
User
 |
 v
MindBridge GUI
 |
 v
C++ Application
 |
 v
/dev/mindbridge
 |
 v
Linux Character Device Driver
 |
 v
Linux Kernel
