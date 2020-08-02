#pragma once
#include<iostream>
class game
{
private:
	bool gameover;
	const unsigned int height, width;
	unsigned int headx, heady, fruitx, fruity, score, speed;
	unsigned int tailx[100], taily[100];
	enum direction { stop = 0, up, down, left, right };
	direction dir;
	void draw();
	void input();
	void logic();
public:
	game();
	void run();
};