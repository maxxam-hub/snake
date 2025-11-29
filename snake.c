#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Snode{
    struct Snode *back;
    int x;
    int y;
};

void generateCoordsApple(int *xApple, int *yApple, int **field, int *flag);
void initSnakeNode(struct Snode *sNode, int x, int y);
void initSnake(struct Snode *prevNode, int length);
void moveHeadSnake(struct Snode *startNode, int dx, int dy);
void fillArraySnake(struct Snode *startNode, int **arr);
void fillFieldByZero(int **field, int height, int width);
int** initField(int height, int width);
void freeField(int **arr, int height);

int main() {
    srand(time(NULL));
    int **field = initField(25, 25);
    int x = 0, y = 0;
    int xApple = 0, yApple = 0, isAppleOnField = 0;
    int curDx = 0, curDy = 1, newDx = 10, newDy = 10;
    char key = '$';
    struct Snode *sHead = malloc(sizeof(struct Snode)); 
    
    printf("Choose coordinats of the beginning from 0 to 24\n");
    scanf("%d %d", &x, &y);

    initSnakeNode(sHead, x, y);
    initSnake(sHead, 3);
    fillArraySnake(sHead, field);

    while (key != 'q') {

        key = getchar();

        if (key == 'a') {
            newDx = 0;
            newDy = -1;
        }
        else if (key == 'w') {
            newDx = -1;
            newDy = 0;
        }
        else if (key == 's') {
            newDx = 1;
            newDy = 0;
        }
        else if (key == 'd') {
            newDx = 0;
            newDy = 1;
        } else {
            newDx = curDx;
            newDy = curDy;
        }

        if ((curDx == -newDx && curDy == 0) || (curDy == -newDy && curDx == 0)) {
            printf("GAME OVER");
            break;
        } else {
            curDx = newDx;
            curDy = newDy;
            moveHeadSnake(sHead, curDx, curDy);
        }

        fillArraySnake(sHead, field);

        if (isAppleOnField == 0) generateCoordsApple(&xApple, &yApple, field, &isAppleOnField);
        
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                if (field[i][j] == 1) {
                    printf("o");
                } else if (i == xApple && j == yApple && isAppleOnField == 1) {
                    printf("*");
                } else if (i == 0 || j == 0 || i == 24 || j == 24) {
                    if (i == 0 || i == 24) printf("-");
                    if ((j == 0 || j == 24) && i != 0 && i != 24) printf("|");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
        //printf("\033[H\033[J");
        printf("\n");
    }
    freeField(field, 25);
    return 0;
}

void generateCoordsApple(int *xApple, int *yApple, int **field, int *flag) {
    do {
        *xApple = 1 + rand() % 23;
        *yApple = 1 + rand() % 23;
        if (*flag == 0) *flag = 1;
    } while (field[*xApple][*yApple] != 0);
}

void initSnakeNode(struct Snode *sNode, int x, int y) {
    sNode->x = x;
    sNode->y = y;
    sNode->back = NULL;
}

void initSnake(struct Snode *sHead, int length) {
    struct Snode *current = sHead;

    for (int i = 1; i < length; i++) {
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

    if (head->x == 0) head->x = 23;
    else if (head->x == 24) head->x = 1;
    else if (head->y == 0) head->y = 23;
    else if (head->y == 24) head->y = 1;

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
    fillFieldByZero(arr, 25, 25);
    while (startNode != NULL) {
        arr[startNode->x][startNode->y] = 1;
        startNode = startNode->back;
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

void fillFieldByZero(int **field, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            field[i][j] = 0;
        }
    }
}