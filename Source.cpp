#include <iostream>
#include <thread>
#include <fstream>
#include <ctime>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"


using namespace std;

void makeMeal1() {
    cout << "Making meal #1\n";
}

void makeMeal2() {
    cout << "making meal #2\n";
}

void makeMeat3() {
    cout << "making meal #3\n";
}

void openFile(ifstream& fileToOpen)
{
		cout << "Opening file\n";

		if (!fileToOpen.is_open()) {
			cout << "Error opening file\n";
			return;
		}
		cout << GREEN << "File opened successfully\n" << RESET;
}

string generateData() {
	int randomLength = rand() % 100 + 1;  
	string randomString;


	for (int i = 0; i < randomLength; ++i) {
		char randomChar = 'a' + rand() % 26;  
		randomString += randomChar;  
	}

	return randomString;
}


void pushDataToFile(const string& fileName)
{
	ofstream file(fileName, ios::app);
	if (!file) {
		cout << "Error opening file for writing\n";
		return;
	}
	cout << "Pushing data to file\n";
	string data = generateData();
	file << data << "\n";
	cout << "Data pushed to file\n";
}

int main() {
	srand(static_cast<unsigned int>(time(0)));


    thread make1(makeMeal1);
    thread make2(makeMeal2);
    thread make3(makeMeat3);

	make1.join();
	make2.join();
	make3.join();


    cout << "All meals have been made\n";
	string myFileName = "fileFlow.txt";
	ifstream myFile(myFileName);
	thread openThread(openFile, ref(myFile));

	thread pushThread(pushDataToFile, myFileName);

	openThread.join();
	pushThread.join();

	cout << "All data has been pushed to file\n";
	cout << "Closing file\n";
	myFile.close();

    return 0;
}