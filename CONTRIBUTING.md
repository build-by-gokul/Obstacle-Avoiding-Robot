# Contributing to Obstacle-Avoiding Robot Car

Thank you for your interest in contributing to this project! This guide will help you get started.

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How Can I Contribute?](#how-can-i-contribute)
- [Getting Started](#getting-started)
- [Coding Guidelines](#coding-guidelines)
- [Submitting Changes](#submitting-changes)
- [Reporting Issues](#reporting-issues)

## Code of Conduct

This project is an academic/educational project. Please be respectful, constructive, and supportive in all interactions.

## How Can I Contribute?

### 🐛 Report Bugs
- Open an issue describing the bug
- Include steps to reproduce
- Mention your Arduino IDE version and board type

### 💡 Suggest Enhancements
- Open an issue with the tag `enhancement`
- Describe the proposed feature and its benefit
- If possible, include a rough implementation idea

### 🔧 Submit Code Changes
- Fork the repository
- Create a feature branch
- Make your changes
- Submit a pull request

### 📖 Improve Documentation
- Fix typos or unclear instructions
- Add diagrams or photographs
- Improve wiring guides or troubleshooting steps

## Getting Started

1. **Fork** the repository on GitHub
2. **Clone** your fork locally:
   ```bash
   git clone https://github.com/YOUR-USERNAME/Obstacle-Avoiding-Robot.git
   ```
3. **Create a branch** for your changes:
   ```bash
   git checkout -b feature/your-feature-name
   ```
4. **Make your changes** and test them
5. **Commit** with a clear message:
   ```bash
   git commit -m "Add: brief description of your change"
   ```
6. **Push** to your fork:
   ```bash
   git push origin feature/your-feature-name
   ```
7. **Open a Pull Request** on GitHub

## Coding Guidelines

### Arduino Code
- Use meaningful variable and function names
- Add comments explaining the **why**, not just the **what**
- Keep pin definitions centralized at the top of the file
- Use `const` for values that should not change
- Use `F()` macro for serial print strings to save RAM
- Test your code compiles before submitting (verify in Arduino IDE)

### Documentation
- Use clear, beginner-friendly language
- Follow existing Markdown formatting conventions
- Use tables for structured data (pin mappings, test results)
- Include diagrams where helpful

## Submitting Changes

### Pull Request Process
1. Ensure your code compiles without errors
2. Update documentation if your changes affect it
3. Describe what your PR does and why
4. Reference any related issues (e.g., "Fixes #12")

### Commit Message Format
```
Type: Brief description

Detailed explanation if needed.
```

Types: `Add`, `Fix`, `Update`, `Remove`, `Refactor`, `Docs`

## Reporting Issues

When reporting an issue, please include:
- **Description**: What happened?
- **Expected behavior**: What should have happened?
- **Steps to reproduce**: How can we recreate the issue?
- **Environment**: Arduino IDE version, OS, board type
- **Screenshots**: If applicable

---

Thank you for helping improve this project! 🤖
