#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* args[]){
    system("echo All Processes:");
    system("ps -l");
    system("echo Zombie Child Process:");
    system("ps -l|grep -w  Z|tr -s ''|cut -d '' -f 5 > ps.out");

    FILE* fp = fopen("ps.out", "r");
    if(fp != NULL){
        char buffer[100];
        fgets(buffer, sizeof buffer, fp);
        
        //12,13,14


        char * ppidstring = strtok(buffer, " ");
        ppidstring = strtok(NULL, " ");
        ppidstring = strtok(NULL, " ");
        ppidstring = strtok(NULL, " ");
        ppidstring = strtok(NULL, " ");//get ppid

        printf("Extracted ppid: %s\n", ppidstring);

        char command[80] = "kill -9 ";

        strcat(command, ppidstring);

        printf("%s\n", command);

        system(command);

        system("echo All Processes:");
        system("ps -l");
    } else {
        printf("There was an issue reading the result of the command!");
    }
}