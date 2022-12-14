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
	mFileO[FILESCORES].open("Data//Scores.txt", std::ios::app);
	mFileO[FILESCORES] << score << "\n";
	mFileO[FILESCORES].close();
}

std::vector<int> Data::GetTopFiveScores()
{
	mFileI[FILESCORES].open("Data//Scores.txt");

	std::string line;
	std::vector<int> arr;

	while (std::getline(mFileI[FILESCORES], line)) {
		int num;
		std::stringstream ss;
		ss << line;
		ss >> num;
		arr.push_back(num);
	}

	QuickSort(arr, 0, arr.size() - 1);
	
	mFileI[FILESCORES].close();
	return arr;
}

void Data::RestartScores()
{
	mFileO[FILESCORES].open("data//Scores.txt");

	mFileO[FILESCORES] << "0\n" << "0\n" << "0\n" << "0\n" << "0\n";

	mFileO[FILESCORES].close();
}

void Data::ChangeAudio(int lvl, int type)
{
	int currentLevel;

	if (type == TYPEMUSIC) {
		currentLevel = GetAudioLevel(TYPEMUSIC);
		mFileO[FILESAUDIO].open("data//MusicVolume.txt");
	}
	else if (type == TYPESOUND) {
		currentLevel = GetAudioLevel(TYPESOUND);
		mFileO[FILESAUDIO].open("data//SoundVolume.txt");
	}
	
	// INCREASE MUSIC
	if (lvl == 1) {
		if (currentLevel == 21) {
			mFileO[FILESAUDIO] << "Volume: " << 21 << "\n";
		}
		else {
			mFileO[FILESAUDIO] << "Volume: " << currentLevel +  3 << "\n";
		}
	}

	// DECREASE MUSIC
	else if (lvl == -1) {
		if (currentLevel == 0) {
			mFileO[FILESAUDIO] << "Volume: " << 0 << "\n";
		}
		else {
			mFileO[FILESAUDIO] << "Volume: " << currentLevel - 3 << "\n";
		}
	}

	mFileO[FILESAUDIO].close();
}

int Data::GetAudioLevel(int type)
{
	if (type == TYPEMUSIC) {
		mFileI[FILESAUDIO].open("data//MusicVolume.txt");
	}
	else if (type == TYPESOUND) {
		mFileI[FILESAUDIO].open("data//SoundVolume.txt");
	}

	std::string line;
	std::getline(mFileI[FILESAUDIO], line);

	std::size_t found = line.find_last_of(" ");
	std::string numLine = line.substr(found + 1);

	int num;
	std::stringstream ss;
	ss << numLine;
	ss >> num;

	mFileI[FILESAUDIO].close();
	return num;
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
