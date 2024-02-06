//Implement usinh shmat and shmget

//child
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/mman.h>
void main(int argc, char *argv[])
{
    int i;
    void *ptr;
    int shmid = shmget((key_t)1122, 4096, 0666);
    ptr = shmat(shmid, NULL, 0666);
    printf("CHILD:\n");
    int n = atoi(argv[1]);
    for (i = 1; i < 2 * n + 1; i += 2)
    {
        sprintf(ptr, "%d ", i);
        printf("%d ", i);
        ptr += strlen(ptr);
    }
    shmctl(shmid, IPC_RMID, NULL);
}



//parent

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
void main(int argc, char *argv[])
{
    pid_t pid;
    const int SIZE = 4096;
    int shmid;
    void *ptr;
    if (argc < 2)
    {
        printf("Error: not passing N in command line\n");
        exit(0);
    }
    pid = fork();
    shmid = shmget((key_t)1122, 4096, 0666 | IPC_CREAT);
    ptr = shmat(shmid, NULL, 0666);
    if (pid == 0)
    {
        execlp("./odd", "odd", argv[1], NULL);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("\nPARENT: child completed\n");
        printf("Parent printing:\n");
        printf("%s ", (char *)ptr);
        shmdt(ptr);
    }
}
