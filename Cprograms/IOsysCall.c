/*
Perform following tasks using I/O system calls
1)Reading first 10 characters from file 
2)Skipping 5 characters from current position of file
3)Going to 5th last character in the file
4)Goinh to 3rd character in the file
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
void main()
{
    char filename[100], buffer[100];
    int fd, n;
    printf("\nEnter filename: ");
    scanf("%s", filename);
    fd = open(filename, O_RDONLY);
    printf("\nreading 10 characters from the file\n");
    n = read(fd, buffer, 10);
    write(0, buffer, n);
    printf("\nSkipping 5th character from the file\n");
    lseek(fd, 5, SEEK_CUR);
    n = read(fd, buffer, 10);
    write(0, buffer, n);
    printf("\ngoing to last 5th character in the file\n");
    lseek(fd, -5, SEEK_END);
    n = read(fd, buffer, 5);
    write(0, buffer, n);
    printf("\nGoing to the 3rd character in the file\n");
    lseek(fd, 3, SEEK_SET);
    n = read(fd, buffer, 10);
    write(0, buffer, n);
}
