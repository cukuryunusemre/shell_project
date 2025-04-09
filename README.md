Sytstem Programming Project-1

Yunus Emre Çukur
Hasan Özgür Özdemir
Sefa Taşdemir


# GTK Tabanlı Çoklu Shell Uygulaması – System Programming Project

Bu proje, sistem programlamanın temel konularını (process yönetimi, IPC, shared memory, semaphore) grafik arayüz (GUI) ile birleştirerek birden fazla shell çalıştırmayı amaçlar.

---

## 🎯 Amaç (Objective)

- Shell komutlarını çalıştırabilen bir terminal arayüzü oluşturmak (örnek: `ls`, `cat`, `pwd`)
- @msg komutu ile shared memory üzerinden shell'ler arası mesajlaşma
- GTK ile kullanıcı dostu arayüz oluşturmak
- Tüm yapıyı MVC (Model-View-Controller) tasarım deseni ile yazmak

---

## 🧱 Kullanılan Teknolojiler

- `C` dili
- `GTK 3` (GUI için)
- `fork()`, `execvp()`, `pipe()`, `waitpid()` (Process yönetimi)
- `shm_open()`, `mmap()` (POSIX Shared Memory)
- `sem_t` (POSIX Semaphore)
- `Makefile` ile derleme kolaylığı

---

