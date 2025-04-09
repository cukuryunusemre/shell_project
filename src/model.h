#ifndef MODEL_H
#define MODEL_H

#include <semaphore.h>
#include <sys/types.h>

#define BUF_SIZE 4096
#define SHARED_FILE_PATH "mymsgbuf"

typedef struct {
    sem_t sem;
    size_t cnt;
    int fd;
    char msgbuf[];
} ShmBuf;

// Paylaşımlı bellek
ShmBuf* buf_init();
void buf_close(ShmBuf *shmp);

// Komut çalıştırma
void execute_command(char *command);

// Mesaj gönderme/okuma
void send_message(const char *msg);
char* read_messages();

#endif

