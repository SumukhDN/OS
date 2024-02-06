//Implement using shmat and shmget

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
        execlp("./fib", "fib", argv[1], NULL);
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
    int k = 2, n1, n2, n3;
    void *ptr;
    int shmid = shmget((key_t)1122, 4096, 0666);
    ptr = shmat(shmid, NULL, 0666);
    printf("CHILD:\n");
    int i = atoi(argv[1]);
    n1 = 0;
    n2 = 1;
    sprintf(ptr, "%d ", n1);
    ptr += strlen(ptr);
    printf("%d ", n1);
    sprintf(ptr, "%d ", n2);
    ptr += strlen(ptr);
    printf("%d ", n2);
    while (k != i)
    {
        n3 = n1 + n2;
        sprintf(ptr, "%d ", n3);
        printf("%d ", n3);
        n1 = n2;
        n2 = n3;
        ptr += strlen(ptr);
        k++;
    }
    shmctl(shmid, IPC_RMID, NULL);
}
