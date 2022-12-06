#pragma once
#include<fstream>
#include<Objects.h>
#include<iostream>
#include<string>
#include<sstream>
using namespace obj;

class Data
{
public:
	Data();
	void SetHighScore(int highScore);
	int GetHighScore();

private:
	std::ofstream mFileO[EMPTYFILE];
	std::ifstream mFileI[EMPTYFILE];
};

