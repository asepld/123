#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>

#define WIDTH 640
#define HEIGHT 480

int rocketX, rocketY; // координаты ракеты
int obstacleX, obstacleY; // координаты препятствия

void drawRocket() {
    setcolor(WHITE); // устанавливаем цвет линий ракеты
    line(rocketX, rocketY, rocketX + 20, rocketY + 40); // рисуем первую линию ракеты
    line(rocketX + 20, rocketY + 40, rocketX + 40, rocketY); // рисуем вторую линию ракеты
}

void drawObstacle() {
    setcolor(RED); // устанавливаем цвет препятствия
    rectangle(obstacleX, obstacleY, obstacleX + 40, obstacleY + 40); // рисуем препятствие
}

void clearScreen() {
    cleardevice(); // очищаем экран
}

void updateRocket() {
    if (rocketY > 0) { // если ракета не достигла верхней границы экрана, перемещаем ее вверх
        rocketY -= 10;
    }
}

void updateObstacle() {
    if (obstacleX > -40) { // если препятствие еще не достигло левой границы экрана, перемещаем его влево
        obstacleX -= 5;
    } else { // если препятствие достигло левой границы экрана, генерируем новые координаты для него
        obstacleX = WIDTH;
        obstacleY = rand() % (HEIGHT - 40); // препятствие не должно находиться на верхней и нижней границах экрана
    }
}

int checkCollision() {
    if ((rocketX + 20 >= obstacleX && rocketX <= obstacleX + 40) && (rocketY + 40 >= obstacleY && rocketY <= obstacleY + 40)) { // если координаты ракеты и препятствия пересекаются, значит, произошло столкновение
        return 1;
    }
    return 0;
}

int main() {
    int gd = DETECT, gm; // инициализируем графический режим
    initgraph(&gd, &gm, ""); // открываем графическое окно

    srand(time(NULL)); // инициализируем генератор случайных чисел

    rocketX = WIDTH / 2 - 20; // начальные координаты ракеты
    rocketY = HEIGHT - 80;
    obstacleX = WIDTH;
    obstacleY = rand() % (HEIGHT - 40);

    while (1) { // основной цикл игры
        clearScreen(); // очищаем экран

        drawRocket(); // рис
    drawObstacle(); // рисуем препятствие

    if (checkCollision()) { // проверяем столкновение
        printf("Game Over"); // выводим сообщение о конце игры
        break; // выходим из цикла
    } else {
        if (kbhit()) { // если игрок нажал на клавишу
            switch (getch()) { // получаем код клавиши
                case 'w': // если нажата клавиша w, перемещаем ракету вверх
                    updateRocket();
                    break;
                case 's': // если нажата клавиша s, перемещаем ракету вниз
                    if (rocketY < HEIGHT - 40) { // ракета не должна находиться на нижней границе экрана
                        rocketY += 10;
                    }
                    break;
                case 'q': // если нажата клавиша q, выходим из игры
                    exit(0);
            }
        } else { // если игрок не нажал на клавишу, перемещаем ракету вниз
            if (rocketY < HEIGHT - 40) { // ракета не должна находиться на нижней границе экрана
                rocketY += 5;
            }
        }
    }

    updateObstacle(); // перемещаем препятствие

    delay(50); // замедляем игру для удобства игрока
}

getch(); // ждем, пока игрок нажмет любую клавишу

closegraph(); // закрываем графическое окно

return 0;
