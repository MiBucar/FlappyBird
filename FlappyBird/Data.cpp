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

void Data::AddScore(int score)
{
	mFileO[SCORES].open("Data//Scores.txt", std::ios::app);
	mFileO[SCORES] << score << "\n";
	mFileO[SCORES].close();
}

std::vector<int> Data::GetTopFiveScores()
{
	mFileI[SCORES].open("Data//Scores.txt");

	std::string line;
	std::vector<int> arr;

	while (std::getline(mFileI[SCORES], line)) {
		int num;
		std::stringstream ss;
		ss << line;
		ss >> num;
		arr.push_back(num);
	}

	QuickSort(arr, 0, arr.size() - 1);
	
	mFileI[SCORES].close();
	return arr;
}

void Data::Swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int Data::Partition(std::vector<int>& array, int low, int high)
{
	int pivot = array[high];
	int i = (low - 1);
	for (int j = low; j < high; j++) {
		if (array[j] <= pivot) {
			i++;
			Swap(&array[i], &array[j]);
		}
	}
	Swap(&array[i + 1], &array[high]);
	return (i + 1);
}

void Data::QuickSort(std::vector<int>& array, int low, int high)
{
	if (low < high) {
		int pi = Partition(array, low, high);
		QuickSort(array, low, pi - 1);
		QuickSort(array, pi + 1, high);
	}
}
