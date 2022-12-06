#include <Data.h>

Data::Data()
{
}

void Data::SetHighScore(int highScore)
{
	mFileO[HIGH_SCORE].open("data//HighScore.txt");

	if (!mFileO->is_open()) std::cout << "Couldn't open HighScore.txt";

	mFileO[HIGH_SCORE] << "High score: " << highScore;
}

int Data::GetHighScore()
{
	mFileI[HIGH_SCORE].open("data//HighScore.txt");

	if (!mFileI->is_open()) std::cout << "Couldn't open HighScore.txt";

	std::string line;
	std::getline(mFileI[HIGH_SCORE], line);

	int num;
	std::stringstream ss;
	ss << line.back();
	ss >> num;

	return num;
}
