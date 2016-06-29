#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define NUM_THREADS
#define NUM_MESSAGES
#define MESSAGE_LEN

typedef struct identifier Identifier;
void *write_msg(void* identifier);

int main() {
    // Abrindo a pipe nomeada onde as threads vão escrever
    int fd = open("namedPipe", O_WRONLY);
    printf("Descritor do pipe: %d", fd);

    // Criando as threads escritoras
    pthread_t *writer;
    writer = (pthread*) calloc(NUM_THREADS, sizeof(pthread));
    
    Identifier id;
    int i;
    
    for(i = 0; i < NUM_THREADS; i++) {
        id.fd = fd;
        id.num_thread = i;
        printf("writer%d: %d\n", i, pthread_create(&writer[i], NULL, write_msg, &id));
    }
    
    free(writer);
    return 0;
}

struct identifier {
    int fd, num_thread;
};

void *writeMsg(void* identifier) {

    Identifier *id = (Identifier*) identifier;
    char msg[MESSAGE_LEN];
    int i, fd = id->fd, num_thread = id->num_thread;
    
    for(i = 0; i < NUM_MESSAGES; i++) {
        sprintf(msg, "%d-MSG-%.3d", num_thread, i);
        write(fd, msg, MESSAGE_LEN);
        sched_yield(1);
    }
}

