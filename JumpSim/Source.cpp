#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <conio.h>
#include <Windows.h>

class Jump
{
public:
	enum EDirection{STOP = 0, UP};

	void Setup()
	{
		end = false;
		dir = STOP;
		velocityY = 0.0;
		positionY = GROUND_Y;
		isOnGround = true;
	}

	void Draw() const
	{
		system("cls");

		int screenHeight = 25;
		for (int i = 0; i < screenHeight; i++)
		{
			if (i == static_cast<int>(positionY))
				std::cout << "   0" << std::endl;
			else
				std::cout << std::endl;
		}

		std::cout << "Y: " << positionY << " | VelocityY: " << velocityY << std::endl;
		std::cout << "[W] jump | [X] exit" << std::endl;
	}

	void Input()
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
				if (isOnGround)
				{
					dir = UP;
					isOnGround = false;
					velocityY = JUMP_VELOCITY;
				}
				break;
			case 'x':
				end = true;
				break;
			}
		}
	}

	void Logic(double deltaTime)
	{
		if (!isOnGround)
		{
			velocityY -= GRAVITY * deltaTime;
			positionY -= velocityY * deltaTime;

			if (positionY >= GROUND_Y)
			{
				positionY = GROUND_Y;
				velocityY = 0.0;
				isOnGround = true;
				dir = STOP;
			}
		}
	}

	bool isGameOver() const { return end; }

private:
	bool end = false;
	EDirection dir = STOP;

	const double GRAVITY = 9.8;
	const double JUMP_VELOCITY = 15.0;
	const double GROUND_Y = 24.0;

	double velocityY = 0.0;
	double positionY = 0.0;
	bool isOnGround = true;
};

int main()
{
	Jump game;
	game.Setup();
	const double deltaTime = 0.16;

	while (!game.isGameOver())
	{
		game.Draw();
		game.Input();
		game.Logic(deltaTime);
		Sleep(16);
	}
	return 0;
}


