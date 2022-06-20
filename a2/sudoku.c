#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int row;
    int column;
    int (** puzzle);
} parameters;

int main(int argc, char *arge[]) {

    void *check_column(void *param);
    void *check_row(void *param);
    void *check_grid(void *param);
    
    int** puzzle = malloc(10*sizeof(int*));
    for(int i = 0; i < 10; i++)
        puzzle[i] = malloc(10*sizeof(int));

    FILE *file;
    file = fopen("sample1_in.txt", "r");
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(!fscanf(file, "%d", &puzzle[i][j])){
                break;
            }
            //printf("%d\n", puzzle[i][j]);
        }
    }
    fclose(file);

    printf("Sudoku Puzzle is: \n");
    for(int i = 1; i < 10; i++){
        for(int j = 1; j < 10; j++){
            printf("%d ",puzzle[i][j]);
        }
        printf("\n");
    }
    
    parameters *data = (parameters *) malloc(sizeof(parameters));
    data->row = 1;
    data->column = 1;
    data->puzzle = puzzle;

    //

    parameters *data_grid1_1 = (parameters *) malloc(sizeof(parameters));
    data_grid1_1->row = 1;
    data_grid1_1->column = 1;
    data_grid1_1->puzzle = puzzle;

    parameters *data_grid1_2 = (parameters *) malloc(sizeof(parameters));
    data_grid1_2->row = 1;
    data_grid1_2->column = 4;
    data_grid1_2->puzzle = puzzle;

    parameters *data_grid1_3 = (parameters *) malloc(sizeof(parameters));
    data_grid1_3->row = 1;
    data_grid1_3->column = 7;
    data_grid1_3->puzzle = puzzle;

    //

    parameters *data_grid2_1 = (parameters *) malloc(sizeof(parameters));
    data_grid2_1->row = 4;
    data_grid2_1->column = 1;
    data_grid2_1->puzzle = puzzle;

    parameters *data_grid2_2 = (parameters *) malloc(sizeof(parameters));
    data_grid2_2->row = 4;
    data_grid2_2->column = 4;
    data_grid2_2->puzzle = puzzle;

    parameters *data_grid2_3 = (parameters *) malloc(sizeof(parameters));
    data_grid2_3->row = 4;
    data_grid2_3->column = 7;
    data_grid2_3->puzzle = puzzle;

    //

    parameters *data_grid3_1 = (parameters *) malloc(sizeof(parameters));
    data_grid3_1->row = 7;
    data_grid3_1->column = 1;
    data_grid3_1->puzzle = puzzle;

    parameters *data_grid3_2 = (parameters *) malloc(sizeof(parameters));
    data_grid3_2->row = 7;
    data_grid3_2->column = 4;
    data_grid3_2->puzzle = puzzle;

    parameters *data_grid3_3 = (parameters *) malloc(sizeof(parameters));
    data_grid3_3->row = 7;
    data_grid3_3->column = 7;
    data_grid3_3->puzzle = puzzle;

    void * c_cols;
    void * c_rows;
    void * c_grid1_1;
    void * c_grid1_2;
    void * c_grid1_3;
    void * c_grid2_1;
    void * c_grid2_2;
    void * c_grid2_3;
    void * c_grid3_1;
    void * c_grid3_2;
    void * c_grid3_3;

    pthread_t t_row, t_col, t_grid1_1, t_grid1_2,t_grid1_3,
                            t_grid2_1, t_grid2_2,t_grid2_3,
                            t_grid3_1, t_grid3_2,t_grid3_3;

    int flag = 0;

    //col
    pthread_create(&t_col, NULL, check_column, (void *) data);
    //row
    pthread_create(&t_row, NULL, check_row, (void *) data);
    //grind1
    pthread_create(&t_grid1_1, NULL, check_grid, (void *) data_grid1_1);
    pthread_create(&t_grid1_2, NULL, check_grid, (void *) data_grid1_2);
    pthread_create(&t_grid1_3, NULL, check_grid, (void *) data_grid1_3);
    //grind2
    pthread_create(&t_grid2_1, NULL, check_grid, (void *) data_grid2_1);
    pthread_create(&t_grid2_2, NULL, check_grid, (void *) data_grid2_2);
    pthread_create(&t_grid2_3, NULL, check_grid, (void *) data_grid2_3);
    //grind3
    pthread_create(&t_grid3_1, NULL, check_grid, (void *) data_grid3_1);
    pthread_create(&t_grid3_2, NULL, check_grid, (void *) data_grid3_2);
    pthread_create(&t_grid3_3, NULL, check_grid, (void *) data_grid3_3);

    pthread_join(t_col,&c_cols);
    pthread_join(t_row,&c_rows);

    pthread_join(t_grid1_1,&c_grid1_1);
    pthread_join(t_grid1_2,&c_grid1_2);
    pthread_join(t_grid1_3,&c_grid1_3);

    pthread_join(t_grid2_1,&c_grid2_1);
    pthread_join(t_grid2_2,&c_grid2_2);
    pthread_join(t_grid2_3,&c_grid2_3);

    pthread_join(t_grid3_1,&c_grid3_1);
    pthread_join(t_grid3_2,&c_grid3_2);
    pthread_join(t_grid3_3,&c_grid3_3);
    
    if ((int)(intptr_t)c_cols+(int)(intptr_t)c_rows+
        (int)(intptr_t)c_grid1_1+(int)(intptr_t)c_grid1_2+(int)(intptr_t)c_grid1_3+
        (int)(intptr_t)c_grid2_1+(int)(intptr_t)c_grid2_2+(int)(intptr_t)c_grid2_3+
        (int)(intptr_t)c_grid3_1+(int)(intptr_t)c_grid3_2+(int)(intptr_t)c_grid3_3 != 0) flag = 1;
    
    if (flag == 0) printf("Sudoku Puzzle is Valid.\n");
    else printf("Sudoku Puzzle is Not Valid.\n");
}

void *check_column(void *param) {
    parameters * data = (parameters *) param;
    int strRow = data->row;
    int strCol = data->column;
    for (int i = strCol; i < 10; i++) {
        int dummy[10] = {0};
        for (int j = strRow; j < 10; j++) {
            int val = data->puzzle[j][i];
            if (dummy[val] == 1) {
                //printf("not sudoku\n");
                pthread_exit((void *) 1);
            }
            else {
                //printf("%d,in dummy\n",val);
                dummy[val] = 1;
            }
        }
        
    }
    //printf("return\n");
    pthread_exit((void *) 0);
}

void *check_row(void *param) {
    parameters * data = (parameters *) param;
    int strRow = data->row;
    int strCol = data->column;
    for (int i = strRow; i < 10; i++) {
        int dummy[10] = {0};
        for (int j = strCol; j < 10; j++) {
            int val = data->puzzle[i][j];
            if (dummy[val] == 1) {
                //printf("not sudoku\n");
                pthread_exit((void *) 1);
            }
            else {
                //printf("%d,in dummy\n",val);
                dummy[val] = 1;
            }
        }
        
    }
    //printf("return\n");
    pthread_exit((void *) 0);
}

void *check_grid(void *param) {
    parameters * data = (parameters *) param;
    int strRow = data->row;
    int strCol = data->column;
    int dummy[10] = {0};
    for (int i = strRow; i < strRow+3; i++) {
        for (int j = strCol; j < strCol+3; j++) {
            int val = data->puzzle[i][j];
            if (dummy[val] == 1) {
                //printf("not sudoku\n");
                pthread_exit((void *) 1);
            }
            else {
                //printf("%d,in dummy\n",val);                
                dummy[val] = 1;
            }
        }
        
    }
    //printf("return\n");
    pthread_exit((void *) 0);    

}

