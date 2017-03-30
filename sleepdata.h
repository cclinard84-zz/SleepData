#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;

struct sleepInfo{
        string lastName;
        string firstName;
        string date;
	string startTime;
	string endTime;
	int startHr;
	int startMn;
	int endHr;
	int endMn;
	int nightTotal;
	int totalMn;
	int totalHr;
	int sleepTotal;
	int personSleepTotal;
};

void openFile(ifstream&, string&);
void checkFileFail(ifstream&, string);
int readFile(sleepInfo data[], ifstream&);
void toLowerLast(sleepInfo data[]);
void toLowerFirst(sleepInfo data[]);
void convertNumbers(sleepInfo data[], int);
void totalSleepMin(sleepInfo data[], int);
void totalSleepHr(sleepInfo data[], int);
void totalSleep(sleepInfo data[], int);
void sortTime(sleepInfo data[], int);
int menu();
string whatName(sleepInfo data[], int);
int longTime(sleepInfo data[], string, int);
int shortTime(sleepInfo data[], string, int);
int addTime(sleepInfo data[], string, int);
void searchName(sleepInfo data[], string, int, int, int, int);
void searchShort(sleepInfo data[]);
void searchLong(sleepInfo data[]);
int whatNumber(sleepInfo data[], int, int);



