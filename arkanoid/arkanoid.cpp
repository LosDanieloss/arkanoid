// arkanoid.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Map.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>

void prepareConsoleView(){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	// max chars is 45
	MoveWindow(console, r.left + 100, r.top, 500, 500, true);
}

int _tmain(int argc, _TCHAR* argv[])
{

	prepareConsoleView();

	HANDLE current = GetStdHandle(STD_OUTPUT_HANDLE);

	HANDLE buffer = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
		);

	HANDLE second = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
		);

	Map* mapa = new Map();

	bool play = true;
	bool first = true;
	int points = 0;
	unsigned long written = 0;
	COORD coordScreen = { 0, 0 };
	std::string draw = "";

	int moves = 0;

	std::cout << mapa->draw() << std::endl;
	std::cout << std::endl << "Press space to continue..." << std::endl;
	_getch();

	int cntr = 0;
	while (play){

		draw = "";

		if (_kbhit()){
			int key = _getch();
			if (key == 97 || key == 75){
				// left
				mapa->dashToLeft();
			}
			else if (key == 100 || key == 77){
				// right
				mapa->dashToRight();
			}
			else if (key == 27){
				// ESC to quite the game
				play = false;
			}
		}
		int tmp;
		if (cntr == 250){
			tmp = mapa->moveBall();
			if (tmp < 0)
				play = false;
			else
				points += tmp;
		}

		cntr++;
		cntr = cntr % 251;

		draw.append(mapa->draw());
		draw.append("\n\nPoints " + std::to_string(points));

		const char* nap = draw.c_str();
		if (first){
			SetConsoleCursorPosition(second, coordScreen);
			WriteConsoleA(second, nap, strlen(nap), &written, NULL);
			SetConsoleActiveScreenBuffer(second);
			first = false;
		}
		else{
			SetConsoleCursorPosition(buffer, coordScreen);
			WriteConsoleA(buffer, nap, strlen(nap), &written, NULL);
			SetConsoleActiveScreenBuffer(buffer);
			first = true;
		}

	}

	SetConsoleActiveScreenBuffer(current);
	system("cls");

	std::cout << "==============================================" << std::endl;
	std::cout << "================= END GAME ===================" << std::endl;
	std::cout << "==============================================" << std::endl;
	std::cout << "You get " + std::to_string(points) + " points in your last game." << std::endl;

	system("pause");
	return 0;
}

