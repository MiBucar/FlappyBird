#include <Data.h>

Data::Data()
{
	mFile[obj::HIGH_SCORE].open("data//HighScore.txt");
	if (!mFile[obj::HIGH_SCORE].is_open()) {
		std::cout << "isnt opened";
	}
}
