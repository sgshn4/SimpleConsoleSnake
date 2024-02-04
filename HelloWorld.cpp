// HelloWorld.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

bool gameOver;

const int width = 20;
const int height = 20;
const int fps = 5;
const float updateRate = 1000 / fps;

int x;
int y;
int fruitX;
int fruitY;
int score;
int tailX[100];
int tailY[100];
int ntail;


enum eDirection {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

eDirection dir;

void fruitRandomizePosition() {
    fruitX = rand() % width;
    fruitY = rand() % height;
}

void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitRandomizePosition();
    score = 0;
}

void draw() {
    system("cls"); //for Windows
    
    cout << "Score: " << score << endl;
    for (int i = 0; i <= width; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width - 1) cout << "#";
            //game display here
            if (i == y && j == x) cout << "0";
            else if (i == fruitY && j == fruitX) cout << "f";
            else {
                bool print = false;
                for (int k = 0; k < ntail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i <= width; i++) cout << "#";

}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X;
    int prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < ntail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    if (x > width || x < 0 || y < 0 || y > height) gameOver = true; //check wall collision
    if (x == fruitX && y == fruitY) {
        score += 1;
        fruitRandomizePosition();
        ntail++;
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(updateRate);
    }
    return 0;
}
