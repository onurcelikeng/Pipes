#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 100

void GetPipe(int type, char *inputFile);

int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        GetPipe(0, argv[1]);
    }

    else if (argc == 4)
    {
        if(strcmp(argv[2], "=") == 0 && strcmp(argv[3], "myMore") == 0)
        {
            GetPipe(1, argv[1]);
        }
    }

    return 0;
}

void GetPipe(int type, char *inputFile)
{
    int fd[2];
    pid_t pid;

    if(pipe(fd) == -1) fprintf(stderr, "Pipe failed.");
    pid = fork();
    if(pid < 0) fprintf(stderr, "Fork failed.");

    if(pid > 0) //parent
    {
        close(fd[READ_END]);      

        char *data = malloc(sizeof(char) * BUFFER_SIZE);        
        FILE *filePointer = fopen(strcat(inputFile, ".txt"), "r");
        if(filePointer == NULL) return;

        while(fscanf(filePointer,"%[^\n]\n", data) != EOF)
        {
            write(fd[WRITE_END], data, sizeof(char) * BUFFER_SIZE);
        }

        fclose(filePointer);
        close(fd[WRITE_END]);
        wait(NULL);
    }

    else //child
    {
        if(type == 0) //for myCat
        {
            close(fd[WRITE_END]);

            char *data = malloc(sizeof(char) * BUFFER_SIZE);
            while(read(fd[READ_END], data, sizeof(char) * BUFFER_SIZE) != 0)
            {                
                printf("%s\n", data);
            }

            close(fd[READ_END]);
        }

        else if(type == 1) //for myMore (paging)
        {
            char arg1[10]; sprintf(arg1, "%d", fd[0]);
            char arg2[10]; sprintf(arg2, "%d", fd[1]);
            execv("./myMore", (char *[]){"./myMore", arg1, arg2, NULL});
        }
    }
}