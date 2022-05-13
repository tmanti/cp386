#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* args[]){
    int sleep_timer = 50;

    pid_t child_pid = fork();
  
    // Parent process 
    if (child_pid > 0){
        sleep(sleep_timer);
    }
    // Child process
    else
        exit(0);
  
    return 0;
}