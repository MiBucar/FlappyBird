#pragma once
#include<fstream>
#include<Objects.h>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace obj;

class Data
{
public:
	Data();
	void SetHighScore(int highScore);
	void AddScore(int score);
	int GetHighScore();
	std::vector<int> GetTopFiveScores();

private:
	void Swap(int* a, int* b);
	int Partition(std::vector<int>& array, int low, int high);
	void QuickSort(std::vector<int>& array, int low, int high);
	std::ofstream mFileO[EMPTYFILE];
	std::ifstream mFileI[EMPTYFILE];

	std::ifstream test;
};

