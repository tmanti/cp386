#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>


const char *name = "process_management";
const int SIZE = 4096;
const int COMMAND_LINES = 5;
const int MAX_COMMAND_SIZE = 50;

const char *commands = "sample_in_process.txt";

void writeOutput(char *command, char *output){
    FILE *fp;
    fp = fopen("output.txt", "a");
    fprintf(fp, "The output of: %s : is\n", command);
	fprintf(fp, ">>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<\n", output);
    fclose(fp);
}

void command_read(){

    int shm_fd = shm_open(name, O_RDWR, 0666);
    if(shm_fd == -1){
        printf("Shared memory in child failed!");
        exit(1);
    }

    ftruncate(shm_fd, SIZE); // truncate to size of shared mem segment

    char *shm_base = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(shm_base == MAP_FAILED){
        printf("Map in child failed!");
        exit(1);
    }

    char *ptr = shm_base;

    FILE *fp;
    fp = fopen("sample_in_process.txt", "r");
    //printf("hello from child\n");
    char *line = NULL;
    size_t len = 0;
    while(getline(&line, &len, fp) != -1){
        //printf("read: %s", line);
        ptr+=sprintf(ptr, "%s", line);
    }
    ptr+=sprintf(ptr, "\n");
}

int main(int argc, char* args[]){
    int shm_fd = shm_open(name, O_CREAT | O_RDONLY, 0666); //filedescriptor creation
    if(shm_fd == -1){
        printf("Shared memory failed!");
        exit(1);
    }

    ftruncate(shm_fd, SIZE); // truncate to size of shared mem segment

    char *shm_base = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); //base address from mmap()
    if(shm_base == MAP_FAILED){
        printf("Map failed!");
        exit(1);
    }

    // can be written to now
    //printf("hello from parent\n");
    pid_t pid = fork();
    if(pid == 0){
        command_read();
        exit(0);
    } else {
        wait(NULL);
    }

    char *ptr=shm_base;
    char **commands = malloc(COMMAND_LINES * sizeof(char *));
    if(commands != NULL){
        for(int i = 0; i < COMMAND_LINES; i++){
            commands[i] = malloc(MAX_COMMAND_SIZE*sizeof(char));
            sscanf(ptr, "%[^\n]s", commands[i]);
            //printf("%s\n", commands[i]);
            ptr+=(strlen(commands[i])+1)*sizeof(char);
        }
    } else {
        printf("malloc error");
    }
}