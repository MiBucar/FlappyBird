#include <Data.h>

Data::Data()
{
}

void Data::SetHighScore(int highScore)
{
	mFileO[HIGH_SCORE].open("data//HighScore.txt");

	if (!mFileO[HIGH_SCORE].is_open()) std::cout << "Couldn't open HighScore.txt: O";

	mFileO[HIGH_SCORE] << "High score: " << highScore;

	mFileO[HIGH_SCORE].close();
}

int Data::GetHighScore()
{
	mFileI[HIGH_SCORE].open("data//HighScore.txt");

	if (!mFileI[HIGH_SCORE].is_open()) std::cout << "Couldn't open HighScore.txt: I";

	std::string line;
	std::getline(mFileI[HIGH_SCORE], line);

	std::size_t found = line.find_last_of(" ");
	std::string numLine = line.substr(found + 1);

	int num;
	std::stringstream ss;
	ss << numLine;
	ss >> num;

	mFileI[HIGH_SCORE].close();

	return num;
}
