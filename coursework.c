//[studentID:11372044]
//[Jiaqi Sheng]

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//define
#define ROWS 9
#define COLS 9
char map[ROWS][COLS]={0};
double total[ROWS][COLS];
double success[ROWS][COLS];
double probability[ROWS][COLS];
double pathcount[ROWS][COLS];
double pathavg[ROWS][COLS];
double path[ROWS][COLS][1000];
double pathsd[ROWS][COLS];
int pcount[ROWS][COLS];

void movement(int *a, int *b) {
    int direction = rand() % 8+0; 
    if (direction == 0) {
        *a = *a - 1; 
    } else if (direction == 1) {
        *a = *a - 1;
        *b = *b + 1; 
    } else if (direction == 2) {
        *b = *b + 1; 
    } else if (direction == 3) {
        *a = *a + 1;
        *b = *b + 1; 
    } else if (direction == 4) {
        *a = *a + 1;
    } else if (direction == 5) {
        *a = *a + 1;
        *b = *b - 1; 
    } else if (direction == 6) {
        *b = *b - 1; 
    } else if (direction == 7) {
        *a = *a - 1;
        *b = *b - 1; 
    }
}


int determination(char (*array)[9][9],int *a,int *b){

    if ((*array)[*a][*b]=='V'|| (*array)[*a][*b]=='W'|| (*array)[*a][*b]=='D'){
        return -1;
    }else if ((*array)[*a][*b]=='B')
    {
        return 1;
    }else if ((*array)[*a][*b]=='L')//
    {
        return 0;
    }
}

//main
int main(void) {
    srand(time(NULL)); 
    //definemap
    FILE *file;
    file = fopen("island_map.txt", "r");
    if (file == NULL) {
        printf("Error!");  
        return 1;
    }
  
    int i = 0, j = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {  
        if (c == ' ' || c == '\n') {
            continue;
        }
        if (j < 9) {
            map[i][j] = c;
            j++;
        }
        if (j == 9) {
            i++;
            j = 0;
            if (i > 9) {
                printf("Error!");
                return 1;
            }
        }
    }
    fclose(file);

    for (int p=0;p<9;p++){
        for(int o=0;o<9;o++){
            for (int i=0;i<1000;i++){
                int human_x= p;
                int human_y= o;

                total[human_x][human_y]=total[human_x][human_y]+1;
                int original_x=human_x;
                int original_y=human_y;
                for (int i=0;i<11;){
                    int result = determination(&map, &human_x, &human_y);
                    if (result == 1){
                        path[original_x][original_y][pcount[original_x][original_y]]=i;
                        pcount[original_x][original_y]=pcount[original_x][original_y]+1;
                        success[original_x][original_y]=success[original_x][original_y]+1;
                        pathcount[original_x][original_y]=pathcount[original_x][original_y]+i;
                        break;
                    }
                    if (result == -1){
                        break;
                    }

                    if(i == 9){
                        break;
                    }
                    movement(&human_x,&human_y);
                    i++;
                }
            }
        }
    }
    //print map
    printf("Map:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", map[i][j]);
            if (j<8){
                printf(" ");
            }
        }
        printf("\n");
    }

    //probability of escape
    //1.calculation
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            double s =success[i][j];
            double t =total[i][j];
            if (t!=0){
                double p=(s/t)*100;
                probability[i][j]=p;
            }
        }
    }
    //2.print
    printf("\nProbability of escape:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%6.2lf", probability[i][j]);
            if (j<8){
                printf(" ");
            }
        }
        printf("\n");
    }

    //mean path length
    //1.calculation
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            double p =pathcount[i][j];
            double s =success[i][j];
            if (s!=0){
                double m=(p/s);
                pathavg[i][j]=m;
            }
        }
    }
    //2.print
    printf("\nMean path length:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%0.2lf", pathavg[i][j] );
            if (j<8){
                printf(" ");
            }
        }
        printf("\n");
    }

    //standard deviation
    //1.calculation
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            double p=0;
            for(int z=0;z<pcount[i][j];z++){
                double cha =path[i][j][z]-pathavg[i][j];
                p= cha*cha + p;
            }
            double s =success[i][j];
            if (s!=0){
                double sd=sqrt(p/s);
                pathsd[i][j]=sd;
            }
        }
    }
    //2.print
    printf("\nStandard deviation of path length:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%0.2lf", pathsd[i][j]);
            if (j<8){
                printf(" ");
            }
        } 
        printf("\n");
    }

    return 0;

}