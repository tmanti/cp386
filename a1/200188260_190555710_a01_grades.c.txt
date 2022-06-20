#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int students = 10;
const int assignemnts = 6; 
const int GTA_count = 3;
const int TA_count = 2;

void TA(int assignment_num, int* assginment){
    float sum = 0;
    for(int i = 0; i < students; i++){
        sum += *(assginment+i);
    }

    printf("Assignment %d - Average = %f\n", assignment_num+1, sum/(float)students);
}

void GTA(int chapter, int** grades){
    pid_t TA_pids[TA_count];
    for(int i = 0; i < TA_count; i++){
        if((TA_pids[i] = fork()) == -1)
            return;//error
        
        if(TA_pids[i] == 0){
            TA(chapter*2+i, grades[chapter*2+i]);
            break;
        }
        wait(NULL);
    }
}

int main(int argc, char* args[]){

    int** grades = malloc(assignemnts*sizeof(int*));
    for(int i =0; i<students; i++)
        grades[i] = malloc(students*sizeof(int));
    
    FILE *file;
    file = fopen("sample_in_grades.txt", "r");
    for(int i =0; i<students; i++){
        for(int j = 0; j<assignemnts; j++){
            if(!fscanf(file, "%d", &grades[j][i])){
                break;
            }
            //printf("%d\n", grades[i][j]);
        }
    }
    fclose(file);

    pid_t GTA_pids[GTA_count];

    for(int i = 0; i < GTA_count; i++){
        if((GTA_pids[i] = fork()) == -1)
            return(1);//error
        
        if(GTA_pids[i] == 0){
            GTA(i, grades);
            break;
        }
        wait(NULL);
    }
}

