#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//there is some ambiguity in the order of the print statements appearing in the console.
void *thread_func(void *args){
    for(int i = 0; i < 5; i++){
        printf("I am a Custom Thread Function Created By user.\n");
        sleep(1);//sleep thread for 1 second
    }
    pthread_exit(0);
}

int main(int argc, char* args[]){

    printf("This program would create threads\n");

    pthread_t thread;
    int err = pthread_create(&thread, NULL, thread_func, NULL); // create thread
    if (!err){ /*check whether the thread creation was successful*/
        printf("Custom thread created Successfully\n");
        for(int i = 0; i < 5; i++){
            printf("I am the process thread created by the compiler by default.\n");
            sleep(1);//sleep main process thread for 1 second
        }
        
        pthread_join(thread, NULL);//wait for thread execution to finish
    }

    return 0;    
}