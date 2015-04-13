#pragma once

#include <string>
#include <vector>
#include <fstream>

class Map
{
private:
	std::vector<std::string> lvlList;
	std::vector<std::string> lvlMap;
	int currentMap;
	int blockToDestroy;
	int dashX, dashLength;
	int ballX, ballY;
	int dx, dy; // change of x & y of our ball 'o'

	void readMap();
	// change _ to :space:, count blockToDestroy, find startin' place of dash and count it length, find coordinates of ball
	void prepareMapBeforeUse(); 

	bool bounceOnVertical(int x, int y);
	bool bounceOnTop(int x, int y);
	bool bounceOnDash(int x, int y);
	bool bounceOnBrick(int x, int y);

public:
	Map();
	~Map();
	std::string draw();
	bool dashToLeft();
	bool dashToRight();
	int moveBall();
};

