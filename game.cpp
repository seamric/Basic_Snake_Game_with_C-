#include"game.h"
#include<conio.h>
#include<Windows.h>
game::game()
	:height(20),width(50),headx(width/2),heady(height/2),gameover(false),score(0),speed(200)
{
	fruitx = rand() % width;
	fruity = rand() % height;
	dir = stop;
}
void game::draw()
{
	system("cls");
	std::cout << std::endl;
	for (int i = 0; i < width; i++)
		std::cout << "#";
	std::cout << std::endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((j == 0) || (j == width - 1))
				std::cout << "#";
			else if ((j == headx) && (i == heady))
			{
				std::cout << "O";
			}
			else if ((j == fruitx) && (i == fruity))
			{
				std::cout << "+";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < score; k++)
				{
					if ((j == tailx[k]) && (i == taily[k]))
					{
						std::cout << "o";
						print = true;
					}
				}
				if (!print)
					std::cout << " ";

			}
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < width; i++)
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "Score = " << score;

}
void game::input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = up;
			break;
		case 's':
			dir = down;
			break;
		case 'a':
			dir = left;
			break;
		case 'd':
			dir = right;
			break;
		}
	}
}
void game::logic()
{
	unsigned int prevx, prevy;
	prevx = tailx[0];
	prevy = taily[0];
	tailx[0] = headx;
	taily[0] = heady;
	
	for (int i = 1; i < score; i++)
	{
		tailx[i] += prevx;	
		taily[i] += prevy;
		prevx = tailx[i] - prevx;
		prevy = taily[i] - prevy;
		tailx[i] -= prevx;

		taily[i] -= prevy;
	}
	switch (dir)
	{
	case up:
		heady--;
		break;
	case down:
		heady++;
		break;
	case left:
		headx--;
		break;
	case right:
		headx++;
		break;
	}
	if ((headx < 0) || (headx > width) || (heady < 0) || (heady > height))  // wall collision
		gameover = true;
	for (int i = 0; i < score; i++)
	{
		if ((headx == tailx[i]) && (heady == taily[i]))
			gameover = true;
	}
	if ((headx == fruitx) && (heady == fruity)) // score increment
	{
		if (speed > 0) // speed increment
		{
			speed -= 5;
		}
		score++;
		fruitx = rand() % width;
		fruity = rand() % height;
	}
}
void game::run()
{
	
	while (!gameover)
	{
		draw();
		input();
		logic();
		Sleep(speed);
	}
}