// ЗМЕЙКА

#include <iostream>
#include <conio.h>

bool gameOver; // отслеживание проигрыша
const int width = 40; // шиирина поля игры
const int height = 20; // выоста поля игры
int x, y, fruitX, fruitY, score; // х и у - координаты змейки
int tailX[100], tailY[100];
int nTail; // число съеденых фруктов
enum eDirection
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};  eDirection dir;

void Setup() // настройка всех параметров
{
	gameOver = false; // изначально мы не проиграли

	dir = STOP; // изначально наша змейка не двигается

	x = width / 2 - 1; // змейка изначально в середине карты
	y = height / 2 - 1;

	fruitX = rand() % width;
	fruitY = rand() % height;

	score = 0;
}
void Draw() // отирсовка карты
{
	system("cls"); // терминал для отчистки

	for (int i = 0; i < width + 1; i++) 
		std::cout << "*";

	std::cout << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) // если первый элемент
				std::cout << "*";
			if (i == y && j == x) // x и y координаты змейки
				std::cout << "O";
			else
				if (i == fruitY && j == fruitX)
					std::cout << "F"; // это фрукт
				else
				{
					bool print = false;
					for (int k = 0; k < nTail; k++)
					{
						if (tailX[k] == j && tailY[k] == i)
						{
							print = true;
							std::cout << "o";
						}
					}

					if (!print)
						std::cout << " ";
				}
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width + 1; i++)
		std::cout << "*";
	std::cout << std::endl;

	std::cout << "SCORE: " << score;
}
void Input() // отслеживания нажатий от пользователя
{
	if (_kbhit()) { // если пользователь нажал на кнопку
		switch (_getch()) { // какую клавишу нажал
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true; // завершение игры
			break;
		}
	}
}
void Logic() // логика игры
{
	int prevX = tailX[0]; // первые координаты хвоста 
	int prevY = tailY[0];
	int prev2X , prev2Y; // следующий элемент координаты хвоста
	tailX[0] = x;
	tailX[0] = x;
	tailY[0] = y;
	  for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
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

	//if (x > width || x < 0 || y > height || y < 0) // если врезались в стенку
		//gameOver = true;

	if (x >= width - 1) // выход ща пределы поля
		x = 0;
	else
		if (x < 0)
			x = width - 2;

	if (y >= height) // выход ща пределы поля
		y = 0;
	else
		if (y < 0)
			y = height - 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main()
{
	Setup();
	while (!gameOver) // пока игра не завершена
	{
		Draw();
		Input();
		Logic();
	}
}