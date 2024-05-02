#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//movemnt
void movement(int *a, int *b) {
    int direction = rand() % 8+0; // 生成0到7之间的随机数
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