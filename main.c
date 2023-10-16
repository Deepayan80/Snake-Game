#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#endif

int width = 20, height = 20, gameOver;
int x, y, fruitX, fruitY, score, flag;
int tailX[100], tailY[100];
int countTail;

void setup() {
    gameOver = 0;
    x = width / 2;
    y = height / 2;
    countTail = 0; // Reset the length of the snake to 0
    srand(time(NULL));
    score = 0;

    // Generate the first fruit
    int validFruit = 0;
    while (!validFruit) {
        fruitX = rand() % width;
        fruitY = rand() % height;
        validFruit = 1;
        for (int i = 0; i < countTail; i++) {
            if (fruitX == tailX[i] && fruitY == tailY[i]) {
                validFruit = 0;
                break;
            }
        }
    }
}

void draw() {
    system("cls || clear");
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
                printf("#");
            else if (i == x && j == y)
                printf("O");
            else if (i == fruitX && j == fruitY)
                printf("*");
            else {
                int isTail = 0;
                for (int k = 0; k < countTail; k++) {
                    if (i == tailX[k] && j == tailY[k]) {
                        printf("o");
                        isTail = 1;
                    }
                }
                if (!isTail)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("SCORE : %d\n", score);
}

void input() {
#ifdef _WIN32
    if (_kbhit()) {
        switch (_getch()) {
#else
    if (kbhit()) {
        switch (getchar()) {
#endif
            case 'a':
                flag = 1;
                break;
            case 'd':
                flag = 2;
                break;
            case 'w':
                flag = 3;
                break;
            case 's':
                flag = 4;
                break;
            case 'x':
                gameOver = 1;
                break;
        }
    }
}

void MakeLogic() {
    int i;
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (i = 1; i < countTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (flag) {
        case 1:
            y--;
            break;
        case 2:
            y++;
            break;
        case 3:
            x--;
            break;
        case 4:
            x++;
            break;
        default:
            break;
    }
    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = 1;
    for (i = 0; i < countTail; i++) {
        if (x == tailX[i] && y == tailY[i])
            gameOver = 1;
    }
    if (x == fruitX && y == fruitY) {
        score += 10;
        countTail++;
        int validFruit = 0;
        while (!validFruit) {
            fruitX = rand() % width;
            fruitY = rand() % height;
            validFruit = 1;
            for (int i = 0; i < countTail; i++) {
                if (fruitX == tailX[i] && fruitY == tailY[i]) {
                    validFruit = 0;
                    break;
                }
            }
        }
    }
}

void delay(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

int main() {
    char c;
    do {
        setup();
        while (!gameOver) {
            draw();
            input();
            MakeLogic();
            delay(100);
        }
        printf("\nPress Y to play again: ");
        scanf(" %c", &c);
    } while (c == 'Y' || c == 'y');
    return 0;
}
