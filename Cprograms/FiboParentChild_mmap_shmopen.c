//Implement using shm_open and mmap

//parent
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>
int main(int argc, char *argv[])
{
    pid_t pid;
    const int SIZE = 4096;
    int shm_fd;
    void *ptr;
    if (argc < 2)
    {
        printf("Error: not passing N in command line\n");
        exit(0);
    }
    pid = fork();
    if (pid == 0)
    {
        execlp("./fib", "fib", argv[1], NULL);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("\nPARENT: child completed\n");

        shm_fd = shm_open("OS", O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        printf("Parent printing:\n");
        printf("%s ", (char *)ptr);
        shm_unlink("OS");
    }
}



//child
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int k = 2, n1, n2, n3;
    void *ptr;
    int shm_fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
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
}
