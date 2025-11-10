#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillArray(int height, int width, int arr[height][width]);

int main() {
    srand(time(NULL));
    int k = 0;
    int field[25][25];
    int x = 0, y = 0; 
    int xApple = 0, yApple = 0; 
    
    fillArray(25, 25, field);
    printf("Choose coordinats of the beginning from 0 to 24\n");
    scanf("%d %d", &x, &y);
    field[x][y] = 1;
    while (getchar()) {
        xApple = rand() % 25;
        yApple = rand() % 25;
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                if (field[i][j] == 1) {
                    printf("o");
                } else if (i == xApple && j == yApple) {
                    printf("*");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("\033[H\033[J");
    }
    return 0;
}

void fillArray(int height, int width, int arr[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            arr[i][j] = 0;
        }
    }
}