#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int width = 20, height = 20, gameOver;
int x,y,fruitX,fruitY,score,flag;
int tailX[100], tailY[100];
int countTail = 0;
void setup()
{
    gameOver = 0;
    x = width/2;
    y = height/2;
    label1:
    fruitX = rand()%20;
    if (fruitX == 0)
    {
        goto label1;
    }
    label2:
    fruitY = rand()%20;
    if (fruitY == 0)
    {
        goto label2;
    }
    score = 0;
}
void draw()
{
    int i,j,k;
    system("cls");
    for ( i = 0; i < width; i++)
    {
        for ( j = 0; j < height; j++)
        {
            if (i == 0 || i == height-1 || j == 0 || j == width-1)
            {
                printf("#");
            }
            else
            {
                if(i == x && j == y)
                {
                    printf("O");
                }
                else if (i == fruitX && j == fruitY)
                {
                    printf("*");
                }
                else
                {
                    int ch = 0;
                    for ( k = 0; k < countTail; k++)
                    {
                        if (i == tailX[k] && j == tailY[k])
                        {
                            printf("o");
                            ch = 1;
                        }
                        
                    }
                    if (ch == 0)
                    {
                        printf(" ");
                    }
                    
                }
            }
        }
        printf("\n");
    }
    printf("\nSCORE : %d",score);
}
void input()
{
    if (kbhit())
    {
        switch (getch())
        {
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
        default:
            break;
        }
    }
    
}
void MakeLogic()
{
    int i;
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X,prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for ( i = 1; i < countTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (flag)
    {
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
    if (x < 0 || x > width || y < 0 || y > height)
    {
        gameOver = 1;
    }
    
}