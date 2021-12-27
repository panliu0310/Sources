#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd, fd2;

    // ref: https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
    char *buffer = (char *) calloc(50, sizeof(char));
    // read the file from input.txt
    fd = open("input.txt", O_RDONLY | O_CREAT);
    read(fd, buffer, 50);
    // printf("buffer:\n%s\n", buffer);
    // now the data is stored in buffer

    // ref: http://www.cplusplus.com/reference/cstdio/sscanf/
    // use sscanf to convert txt to integer array
    int i[10];
    sscanf(buffer, "%d %d %d %d %d %d %d %d %d %d", 
	&i[0], &i[1], &i[2], &i[3], &i[4], &i[5], &i[6], &i[7], &i[8], &i[9]);
    
    // each value added by 1
    for (int counter = 0; counter < 10; counter++) {
        i[counter]++;
    }
    
    // ref: http://www.cplusplus.com/reference/cstdio/sprintf/
    // use sprintf to convert integer to char array
    char buffer2[50];
    int n;
    n = sprintf(buffer2, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", 
	i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9]);
    close(fd);

    // write the file to output.txt

    // first count the number of character we will write
    // otherwise the file format of txt will get bugged
    
    // we count the number of character
    int size = 0;
    while ((buffer2[size + 1] >= 48 && buffer2[size + 1] <= 57) || buffer2[size + 1] == 10) {
        size++;
    }

    // write the file to output.txt
    fd2 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
    write(fd2, buffer2, size);
    close(fd2);

    return(0);
}