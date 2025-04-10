# GTK-Based Multiple Shell Application

This project aims to combine the fundamental concepts of system programming (process management, IPC, shared memory, semaphore) with a graphical user interface (GUI) to run multiple shells.

---

## 🎯 Objective

- Create a terminal interface capable of executing shell commands (e.g., `ls`, `cat`, `pwd`)
- Use the `@msg` command for inter-shell messaging via shared memory
- Create a user-friendly interface using GTK
- Implement the entire structure using the MVC (Model-View-Controller) design pattern

---

## 🧱 Technologies Used

- `C` language
- `GTK 3` (for GUI)
- `fork()`, `execvp()`, `pipe()`, `waitpid()` (Process management)
- `shm_open()`, `mmap()` (POSIX Shared Memory)
- `sem_t` (POSIX Semaphore)
- Compilation convenience with `Makefile`
