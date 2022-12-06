#pragma once
#include<fstream>
#include<Objects.h>
#include<iostream>
#include<string>

class Data
{
public:
	Data();

private:
	std::ofstream mFile[obj::EMPTYFILE];
	std::ifstream ifstream;
};

