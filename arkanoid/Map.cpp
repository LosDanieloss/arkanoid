#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	lvlList = { "lvl1"};
	lvlMap.clear();
	currentMap = 0;
	blockToDestroy = 0;
	dashLength = 0;
	dashX = -1;
	ballX = -1;
	ballY = -1;
	dx = 0;
	dy = -1;

	readMap();
}


Map::~Map()
{
}

void Map::readMap(){
	std::ifstream inFile;
	inFile.open(lvlList[currentMap] + ".txt");
	std::string readed;
	while (inFile >> readed){
		lvlMap.push_back(readed);
	}
	prepareMapBeforeUse();
}

void Map::prepareMapBeforeUse(){
	for (int i = 0; i < lvlMap.size(); i++){
		for (int j = 0; j < lvlMap[i].length(); j++){
			if (lvlMap[i][j] == '_')
				lvlMap[i][j] = ' ';
			if (lvlMap[i][j] == '='){
				if (dashX == -1)
					dashX = j;
				dashLength++;
			}
			if (lvlMap[i][j] == 'o'){
				ballX = j;
				ballY = i;
			}
			if (lvlMap[i][j] == 'x')
				blockToDestroy++;
		}
	}
}

std::string Map::draw(){
	std::string toReturn = "";
	for (int i = 0; i < lvlMap.size(); i++){
		toReturn.append(lvlMap[i] + "\n");
	}
	return toReturn;
}

bool Map::dashToLeft(){
	int y = lvlMap.size() - 1;
	if (lvlMap[y][dashX - 1] != '|'){
		lvlMap[y][dashX - 1] = '=';
		lvlMap[y][dashX + dashLength - 1] = ' ';
		dashX--;
		return true;
	}
	return false;
}

bool Map::dashToRight(){
	int y = lvlMap.size() - 1;
	int x = dashX + dashLength - 1;
	if (lvlMap[y][x + 1] != '|'){
		lvlMap[y][x + 1] = '=';
		lvlMap[y][dashX] = ' ';
		dashX++;
		return true;
	}
	return false;
}

int Map::moveBall(){
	int tmp = 0;
	if (bounceOnBrick(ballX + dx, ballY + dy))
		tmp = 100;
	bounceOnTop(ballX + dx, ballY + dy);
	bounceOnVertical(ballX + dx, ballY + dy);
	if (ballY + dy == (lvlMap.size() - 1) && !bounceOnDash(ballX + dx, ballY + dy)){
		// ball out of play field
		tmp = -50;
	}
	else{
		lvlMap[ballY][ballX] = ' ';
		ballX += dx;
		ballY += dy;
		lvlMap[ballY][ballX] = 'o';
	}

	return tmp;
}

bool Map::bounceOnVertical(int x, int y){
	if (lvlMap[y][x] == '|'){
		dx *= (-1);
		return true;
	}
	return false;
}

bool Map::bounceOnTop(int x, int y){
	if (lvlMap[y][x] == '-'){
		dy *= (-1);
		return true;
	}
	else if (lvlMap[y][x] == '+'){
		dx *= (-1);
		dy *= (-1);
		return true;
	}
	return false;
}

bool Map::bounceOnDash(int x, int y){
	if (lvlMap[y][x] == '='){
		if (ballX + dx == dashX){
			dx = -1;
		}
		else if (ballX + dx == dashX + 1){
			dx = 0;
		}
		else if (ballX + dx == dashX + dashLength - 1){
			dx = 1;
		}
		dy *= (-1);
		return true;
	}
	return false;
}

bool Map::bounceOnBrick(int x, int y){
	if (lvlMap[y][x] == 'x'){
		if (lvlMap[y + (dy * (-1))][x] == ' '){
			dy *= (-1);
		}
		else if (lvlMap[y][x + (dx * (-1))] == ' '){
			dx *= (-1);
		}
		else{
		dx *= (-1);
		dy *= (-1);
		}
		lvlMap[y][x] = ' ';
		return true;
	}
	return false;
}