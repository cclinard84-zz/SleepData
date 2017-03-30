#include <iostream>
#include "sleepdata.h"
using namespace std;

int main(){
	int count, i, menuSelect, time, longMinutes, shortMinutes;
	sleepInfo data[10];
	string searchedPerson;
	int searchedSleepTime;
	string inputFile;
	ifstream input;

	openFile( input, inputFile);
	checkFileFail( input, inputFile);
	count = readFile( data, input);
	input.close( );
	toLowerLast(data);
	toLowerFirst(data);
	convertNumbers(data, count);
	totalSleepMin(data, count);
	totalSleepHr(data, count);
	totalSleep(data, count);
	sortTime(data, count);
	menuSelect = menu();

	if(menuSelect == 1){
		searchedPerson = whatName(data, menuSelect);
	}
	else if((menuSelect == 2) || (menuSelect == 3)){
		searchedSleepTime = whatNumber(data, menuSelect, count);
	}
	else if((menuSelect < 0) || (menuSelect > 3)){
		cout << "Restart the program and select a valid number." << endl;
		exit(1);
	}
	else{
		exit(1);
	}
	longMinutes = longTime(data, searchedPerson, count);
	shortMinutes = shortTime(data, searchedPerson, count);
	time = addTime(data, searchedPerson, count);
	searchName(data, searchedPerson, count, time, longMinutes, shortMinutes);
	return(0);
}