#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    Snode back;
    int x;
    int y;
} Snode;

void fillArray(int height, int width, int arr[height][width]);
void generateCoordsApple(int *xApple, int *yApple);
void initSnakeNode(Snode *sNode, int x, int y);
void fillArraySnake(Snode *startNode, int **arr);

int main() {
    srand(time(NULL));
    int k = 0;
    int field[25][25];
    int x = 0, y = 0;
    int xApple = 0, yApple = 0;
    Snode *sHead; 
    generateCoordsApple(&xApple, &yApple);
    initSnakeNode(sHead, x, y);
    initSnake(sHead, 5);
    int isAppleOnField = 0;
    
    fillArray(25, 25, field);
    fillArraySnake(sHead, field);
    printf("Choose coordinats of the beginning from 0 to 24\n");
    scanf("%d %d", &x, &y);
    while (getchar()) {
        
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

void generateCoordsApple(int *xApple, int *yApple) {
    *xApple = rand() % 25;
    *yApple = rand() % 25;
}

void initSnakeNode(Snode *sNode, int x, int y) {
    sNode->x = x;
    sNode->y = y;
    sNode->back = NULL;
}

void putBackNode(Snode *sNode, Snode *backNode) {
    sNode->back = *backNode;
}

void initSnake(Snode *prevNode, int length) {
    Snode *newNode;
    prevNode->back = *newNode;
    for (int i = 0; i < length; i++) {
        newNode->x = prevNode->x;
        newNode->y = prevNode->y + 1;
        newNode->back = NULL;
        prevNode = newNode;
    }
}

void fillArraySnake(Snode *startNode, int **arr) {
    Snode *tempNode = startNode;
    Snode *backNode = startNode->back;
    while (tempNode->back != NULL) {
        arr[tempNode->x][tempNode->y] = 1;
        tempNode = backNode;
        backNode = tempNode->back;
    }
}