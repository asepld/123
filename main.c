#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>

#define WIDTH 640
#define HEIGHT 480

int rocketX, rocketY; // ���������� ������
int obstacleX, obstacleY; // ���������� �����������

void drawRocket() {
    setcolor(WHITE); // ������������� ���� ����� ������
    line(rocketX, rocketY, rocketX + 20, rocketY + 40); // ������ ������ ����� ������
    line(rocketX + 20, rocketY + 40, rocketX + 40, rocketY); // ������ ������ ����� ������
}

void drawObstacle() {
    setcolor(RED); // ������������� ���� �����������
    rectangle(obstacleX, obstacleY, obstacleX + 40, obstacleY + 40); // ������ �����������
}

void clearScreen() {
    cleardevice(); // ������� �����
}

void updateRocket() {
    if (rocketY > 0) { // ���� ������ �� �������� ������� ������� ������, ���������� �� �����
        rocketY -= 10;
    }
}

void updateObstacle() {
    if (obstacleX > -40) { // ���� ����������� ��� �� �������� ����� ������� ������, ���������� ��� �����
        obstacleX -= 5;
    } else { // ���� ����������� �������� ����� ������� ������, ���������� ����� ���������� ��� ����
        obstacleX = WIDTH;
        obstacleY = rand() % (HEIGHT - 40); // ����������� �� ������ ���������� �� ������� � ������ �������� ������
    }
}

int checkCollision() {
    if ((rocketX + 20 >= obstacleX && rocketX <= obstacleX + 40) && (rocketY + 40 >= obstacleY && rocketY <= obstacleY + 40)) { // ���� ���������� ������ � ����������� ������������, ������, ��������� ������������
        return 1;
    }
    return 0;
}

int main() {
    int gd = DETECT, gm; // �������������� ����������� �����
    initgraph(&gd, &gm, ""); // ��������� ����������� ����

    srand(time(NULL)); // �������������� ��������� ��������� �����

    rocketX = WIDTH / 2 - 20; // ��������� ���������� ������
    rocketY = HEIGHT - 80;
    obstacleX = WIDTH;
    obstacleY = rand() % (HEIGHT - 40);

    while (1) { // �������� ���� ����
        clearScreen(); // ������� �����

        drawRocket(); // ���
    drawObstacle(); // ������ �����������

    if (checkCollision()) { // ��������� ������������
        printf("Game Over"); // ������� ��������� � ����� ����
        break; // ������� �� �����
    } else {
        if (kbhit()) { // ���� ����� ����� �� �������
            switch (getch()) { // �������� ��� �������
                case 'w': // ���� ������ ������� w, ���������� ������ �����
                    updateRocket();
                    break;
                case 's': // ���� ������ ������� s, ���������� ������ ����
                    if (rocketY < HEIGHT - 40) { // ������ �� ������ ���������� �� ������ ������� ������
                        rocketY += 10;
                    }
                    break;
                case 'q': // ���� ������ ������� q, ������� �� ����
                    exit(0);
            }
        } else { // ���� ����� �� ����� �� �������, ���������� ������ ����
            if (rocketY < HEIGHT - 40) { // ������ �� ������ ���������� �� ������ ������� ������
                rocketY += 5;
            }
        }
    }

    updateObstacle(); // ���������� �����������

    delay(50); // ��������� ���� ��� �������� ������
}

getch(); // ����, ���� ����� ������ ����� �������

closegraph(); // ��������� ����������� ����

return 0;
