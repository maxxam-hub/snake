#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Snode{
    struct Snode *back;
    int x;
    int y;
};

void generateCoordsApple(int *xApple, int *yApple);
void initSnakeNode(struct Snode *sNode, int x, int y);
void initSnake(struct Snode *prevNode, int length);
void moveHeadSnake(struct Snode *startNode, int dx, int dy);
void fillArraySnake(struct Snode *startNode, int **arr);
int** initField(int height, int width);
void freeField(int **arr, int height);

int main() {
    srand(time(NULL));
    int k = 0;
    printf("0");
    int **field = initField(25, 25);
    printf("1");
    int x = 0, y = 0;
    int xApple = 0, yApple = 0;
    struct Snode *sHead = malloc(sizeof(struct Snode)); 
    
    printf("Choose coordinats of the beginning from 0 to 24\n");
    scanf("%d %d", &x, &y);

    generateCoordsApple(&xApple, &yApple);
    printf("3");
    initSnakeNode(sHead, x, y);
    printf("4");
    initSnake(sHead, 5);
    printf("5");
    int isAppleOnField = 0;
    
    fillArraySnake(sHead, field);
    char key = '$';
    while (key != 'q') {

        key = getchar();

        if (key == 'a') moveHeadSnake(sHead, -1, 0);
        else if (key == 'w') moveHeadSnake(sHead, 0, -1);
        else if (key == 's') moveHeadSnake(sHead, 0, 1);
        else if (key == 'd') moveHeadSnake(sHead, 1, 0);
        else moveHeadSnake(sHead, 0, 0);
        
        fillArraySnake(sHead, field);

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
    free(field);
    return 0;
}

void generateCoordsApple(int *xApple, int *yApple) {
    *xApple = rand() % 25;
    *yApple = rand() % 25;
}

void initSnakeNode(struct Snode *sNode, int x, int y) {
    sNode->x = x;
    sNode->y = y;
    sNode->back = NULL;
}

void initSnake(struct Snode *sHead, int length) {
    struct Snode *current = sHead;

    for (int i = 1; i < length + 1; i++) {
        struct Snode *nextNode = malloc(sizeof(struct Snode));
        initSnakeNode(nextNode, sHead->x, sHead->y + i);

        current->back = nextNode;
        current = nextNode;
    }
}

void moveHeadSnake(struct Snode *head, int dx, int dy) {
    int prevX = head->x;
    int prevY = head->y;

    head->x += dx;
    head->y += dy;

    struct Snode *current = head->back;

    while (current != NULL) {
        int tempX = current->x;
        int tempY = current->y;

        current->x = prevX;
        current->y = prevY;

        prevX = tempX;
        prevY = tempY;

        current = current->back;
    }
}

void fillArraySnake(struct Snode *startNode, int **arr) {
    while (startNode->back != NULL) {
        struct Snode *tempNode = startNode;
        arr[startNode->y][startNode->x] = 1;
        startNode = tempNode->back;
    }
}

int** initField(int height, int width) {
    int **arr = calloc(height, sizeof(int*));
    for (int i = 0; i < height; i++) {
        arr[i] = calloc(width, sizeof(int));
    }
    return arr;
}

void freeField(int **arr, int height) {
    for (int i = 0; i < height; i++) {
        free(arr[i]);
    }
    free(arr);
}