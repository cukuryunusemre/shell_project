#include "model.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "view.h"

#define errExit(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

static ShmBuf *shmp = NULL;

void ensure_shm_initialized() {
    if (!shmp)
        shmp = buf_init();
}

ShmBuf* buf_init() {
    int fd = shm_open(SHARED_FILE_PATH, O_CREAT | O_RDWR, 0600);
    if (fd < 0) errExit("shm_open failed");

    // BU ÖNEMLİ: toplam boyut = struct + buffer
    size_t total_size = sizeof(ShmBuf) + BUF_SIZE;

    if (ftruncate(fd, total_size) == -1) errExit("ftruncate failed");

    ShmBuf *ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) errExit("mmap failed");

    ptr->fd = fd;
    sem_init(&ptr->sem, 1, 1);

    return ptr;
}



void buf_close(ShmBuf *shmp) {
    sem_destroy(&shmp->sem);
    close(shmp->fd);
    shm_unlink(SHARED_FILE_PATH);
}

void execute_command(char *command) {
    pid_t pid;
    char *args[64];
    char *token;
    int arg_count = 0;

    token = strtok(command, " \n");
    while (token != NULL && arg_count < 63) {
        args[arg_count++] = token;
        token = strtok(NULL, " \n");
    }
    args[arg_count] = NULL;

    int pipefd[2];
    pipe(pipefd);

    pid = fork();

    if (pid == 0) {
        // Child
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        execvp(args[0], args);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent
        close(pipefd[1]);
        char buffer[1024];
        ssize_t n;

        while ((n = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';
            append_text_to_view(buffer);  // ✅ GUI’ye basar
        }
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
    } else {
        perror("fork failed");
    }
}

void send_message(const char *msg) {
    ensure_shm_initialized();
    sem_wait(&shmp->sem);

    strncpy(shmp->msgbuf, msg, BUF_SIZE - 1);
    shmp->msgbuf[BUF_SIZE - 1] = '\0';
    shmp->cnt = strlen(shmp->msgbuf);

    sem_post(&shmp->sem);
}


char* read_messages() {
    ensure_shm_initialized();
    sem_wait(&shmp->sem);

    static char buffer[BUF_SIZE];
    strncpy(buffer, shmp->msgbuf, BUF_SIZE - 1);
    buffer[BUF_SIZE - 1] = '\0';

    sem_post(&shmp->sem);
    return buffer;
}


