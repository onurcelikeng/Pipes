#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 100

int main(int argc, char * argv[])
{
    int fd[2];
    fd[0] = atoi(argv[1]);
    fd[1] = atoi(argv[2]);

    close(fd[WRITE_END]);
    
    char *data = malloc(sizeof(char) * BUFFER_SIZE);
    int i = 0;
    while(read(fd[READ_END], data, sizeof(char) * BUFFER_SIZE) != 0) //continue end of pipe
    {
        if(i != 0 && i % 24 == 0) 
        {
            char str;
            scanf("%c", &str);
            if(str == 'q') break;
        }

        printf("%s\n", data);
        i++;
    }

    close(fd[READ_END]);
    exit(0);
}