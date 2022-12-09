#include <Data.h>

Data::Data()
{
}

int Data::GetHighScore()
{
	int highScore = GetTopFiveScores().at(GetTopFiveScores().size() - 1);

	return highScore;
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

void Data::RestartScores()
{
	mFileO[SCORES].open("Data//Scores.txt");

	mFileO[SCORES] << "0\n" << "0\n" << "0\n" << "0\n" << "0\n";

	mFileO[SCORES].close();
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
