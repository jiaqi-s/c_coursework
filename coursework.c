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
    int direction = rand() % 8;
    if (direction == 0 && *a != 0) {// north
        *a = *a - 1; 
    } else if (direction == 1 && *a != 0) {//north east
        *a = *a - 1;
        *b = *b + 1; 
    } else if (direction == 2 && *b != 8) {//east
        *b = *b + 1; 
    } else if (direction == 3 && *a != 8) {//south east
        *a = *a + 1;
        *b = *b + 1; 
    } else if (direction == 4 && *a != 8) {//south
        *a = *a + 1;
    } else if (direction == 5 && *a != 8) {//south west
        *a = *a + 1;
        *b = *b - 1; 
    } else if (direction == 6 && *b != 0) {//west
        *b = *b - 1; 
    } else if (direction == 7 && *a != 0) {//north west
        *a = *a - 1;
        *b = *b - 1; 

    }else if( direction ==3 && *a ==8 && *b != 8) {//south east at edge
        *b = *b + 1;
    }else if( direction ==4 && *a ==8) {//south at edge
        *b = *b;
        *a = *a;
    }else if( direction ==5 && *a ==8 && *b != 0) {//south west at edge
        *b = *b - 1;

    }else if( direction ==1 && *a ==8 && *b != 8) {//north east at edge
        *b = *b + 1;
    }else if( direction ==0 && *a ==8 ) {//north at edge
        *b = *b;
        *a = *a;
    }else if( direction ==7 && *a ==8 && *b!= 0) {//north west at edge
        *b = *b - 1;
    }else{//at four edges of the map
        *a=*a;
        *b=*b;
    }
}


int determination(char (*array)[9][9],int *a,int *b){//determine the state of cells

    if ((*array)[*a][*b]=='V'|| (*array)[*a][*b]=='W'|| (*array)[*a][*b]=='D'){
        return -1;
    }else if ((*array)[*a][*b]=='B')
    {
        return 1;
    }else if ((*array)[*a][*b]=='L')
    {
        return 0;
    }else{
        return -2;
    }
}

//main
int main(void) {
    srand(123456); 
    //definemap
    FILE *file;
    file = fopen("island_map.txt", "r");//open file for read
    if (file == NULL) {
        printf("Error!");  //when nothing in file
        exit(1);
    }
  
    int i = 0, j = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {  
        if (c == ' ' || c == '\n') {//skip space and \n
            continue;
        }
        if (j < 9) {
            map[i][j] = c;//store island_map.txt in map array
            j++;
        }
        if (j == 9) {
            i++;
            j = 0;
            if (i > 9) {
                printf("Error!");//when map is bigger than 9x9
                exit(1);
            }
        }
    }
    fclose(file);

    for (int p=0;p<9;p++){
        for(int o=0;o<9;o++){
            for (int i=0;i<1000;i++){//for each cell random 1000 times
                int human_x= p;
                int human_y= o;
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
                    if (result == -2){
                        printf("Error!");//when out of 9x9
                        exit(1);
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
            double p=(s/1000)*100;
            probability[i][j]=p;

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