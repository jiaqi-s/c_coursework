#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//determination 
int determination(char (*array)[9][9],int *a,int *b){

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
