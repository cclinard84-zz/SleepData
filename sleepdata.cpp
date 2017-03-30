//
// Name: Christopher Clinard
// Date: 1/30/2016
// Description: This program reads in sleep data from a user 
//				designated file and prints requested data to 
//				the screen. 
//

#include <iostream>
#include "lab1copy.h"
using namespace std;

/* openFile: Opens file given from user input
*  Parameters:
*	input: ifstream name
*	inputFile: string name determined by user input for the file
*  Precondition: None
*  Postcondition: input and inputFile have been named
*  passed by reference.
*  Returns: Nothing
*/
void openFile( ifstream &input, string &inputFile ){
	cout << "Enter the input file name: ";
	cin >> inputFile;
	input.open(inputFile.c_str());
}

/* checkFileFail: Check to see if the file exists and if it is empty
*  Parameters:
*	      input: ifstream name
*	      inputFile: string name for the file
*  Precondition: If file does not exist or empty the program displays
*		 an error message and exits. If file exists and is valid 
*		 returns file to main.
*/
void checkFileFail( ifstream &input, string inputFile){
	
	char c;

	if (input.fail( )){
		cout << "The file " << inputFile << " does not exist.\n";
		openFile(input, inputFile);
	}
}

/* readFile: Reads file and puts data into the structure
*  Parameters:
*	      sleepInfo data: structure to hold data for last name, 
*	      first name, date, sleep start and end times.
*	      input: ifstream name
*  Precondition: File exists, is valid, and has opened successfully
*  Postcondition: structures for counties, povertyRates, and perCapitaSalary are filled to i 
*  Returns: count of counties and their respective data.
*/
int readFile(sleepInfo data[], ifstream& input){
	int i = 0;	
	getline(input, data[i].lastName);
	while(!input.eof() && i < 10){
		input >> data[i].firstName;
		input >> data[i].date;
		input >> data[i].startTime;
		input >> data[i].endTime;
		i++;
		if(i <= 10)
			input >> data[i].lastName;
		else
		{
			return i;	
		}
	}
	return i;
}

/* toLowerLast: Lower cases all characters in lastname 
* Parameters:
*	      sleepInfo data: structure to hold data
* Precondition: sleepInfo structure has been filled with data 
* Postcondition: all characters in each last name have been lowercased. 
* Returns: Nothing
*/
void toLowerLast(sleepInfo data[]){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			data[i].lastName[j] = tolower(data[i].lastName[j]);
		}
	}
}

/* toLowerLast: Lower cases all characters in firstname
* Parameters:
*             sleepInfo data: structure to hold data 
* Precondition: sleepInfo structure has been filled with data 
* Postcondition: all characters in each first name have been lowercased.  
* Returns: Nothing
*/
void toLowerFirst(sleepInfo data[]){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			data[i].firstName[j] = tolower(data[i].firstName[j]);
		}
	}
}
/* convertNumbers: Converts all time strings from strings to integers
*  Parameters: 
* 		SleepInfo data: structure to hold data 
*  Precondition: sleepInfo structure has been filled with data
*  Postcondition: all characters have been converted from char to int
*  Returns: Nothing
*/
void convertNumbers(sleepInfo data[], int count){
	int i;
	for(i = 0; i < count; i++){
		sscanf(data[i].startTime.c_str(), "%d:%d", &data[i].startHr, &data[i].startMn);
		sscanf(data[i].endTime.c_str(), "%d:%d", &data[i].endHr, &data[i].endMn);
	}
}

/* totalSleepMin: calculates total sleep minutes for each data entry
*  Parameters:
*  		sleepInfo data: structure to hold sleep data
*  Precondition: sleep times have been converted from char to integers
*  Postcondition: total sleep minutes have been calculated
*  Returns: Nothing
*/
void totalSleepMin(sleepInfo data[], int count){
	for(int i= 0; i < count; i++){
		if(data[i].startMn > data[i].endMn){
			data[i].totalMn = ((data[i].endMn + 60) - data[i].startMn);
		}
		else{
			data[i].totalMn = (data[i].endMn - data[i].startMn);
		}
	}
}

/* totalSleepHr: calculates total sleep in hours to minutes
*  Parameters: 
*  		sleepInfo data: structure to hold sleep data
*  Precondition: sleep times have been converted from char to integers
*  Postcondition: total sleep hours have been converted to minutes
*  Returns: Nothing
*/
void totalSleepHr(sleepInfo data[], int count){
	for(int i = 0; i < count; i ++){
		if(data[i].startHr > data[i].endHr){
			data[i].totalHr = ((data[i].endHr + 24) - data[i].startHr);
		}
		else{
			data[i].totalHr = (data[i].endHr - data[i].startHr);
		}
	}
}

/* totalSleep: calculates total sleep for the night in minutes 
*  Parameters: 
*  		sleepInfo data: structure to hold sleep data
*  Precondition: sleep times have been converted from char to int and
*		 sleep times converted to minutes
*  Postcondition: total sleep hours and minutes converted to total minutes
*  Returns: Nothing
*/

void totalSleep(sleepInfo data[], int count){
	for(int i = 0; i < count; i++){
		data[i].nightTotal = ((data[i].totalHr * 60) + data[i].totalMn);
	}
}

/* sortTime: sorts sleep times from shortest to longest
*  Parameters:
*  		sleepInfo data: structure to hold sleep data
*  Precondition: sleep times have been converted to minutes
*  Postcondition: sleep times sorted from shortest to longest
*  Returns: Nothing
*/

void sortTime(sleepInfo data[], int count){
	int minIndex, i, top;
        sleepInfo temp;

        for(top = 0; top < count-1; top++){
                minIndex = top;
                for(i = top+1; i < count; i++){
                        if(data[minIndex].nightTotal > data[i].nightTotal)
                                minIndex = i;
                }
                temp = data[minIndex];
                data[minIndex] = data[top];
                data[top] = temp;
        }
}

/* Menu: Provides user prompt for choices
*  Parameters: None
*  Precondition: User has input a correct file name
*  Postcondition: User has made a choice
*  Returns: i which represents the users choice
*/
int menu(){
	cout << "What data would you like to review?" << endl
	     << "Press 1 to search by last name." << endl
	     << "Press 2 to see longest sleep time." << endl
	     << "Press 3 to see shortest sleep time." << endl
  	     << "Press 0 to exit the program." << endl;
	int i;
	cin >> i;
	return i;
}

/* whatName: Requests the name the user wants to search for then
*	     lowercases the entire name.  
*  Parameters:
*		sleepInfo data: structure to hold sleep data
*		menuSelect: users menu selection
*  Precondition: User has selected option 1 or 0
*  Postcondition: User has input a name
*  Returns: A string representing the first and last name the user is searching for
*/
string whatName(sleepInfo data[], int menuSelect){
	if(menuSelect == 0){
		exit(1);
	}
	else if (menuSelect == 1){
		cout << "Please input the first and last name" << endl;
		cout << "of the person you want to search for: ";
		string lastName, firstName;
		cin >> firstName >> lastName;
		cout << endl;
		for(int i = 0; i < 30; i++){
                	firstName[i] = tolower(firstName[i]);
                        lastName[i] = tolower(lastName[i]);
		}
		return (firstName + lastName);
	}
}

/* longTime: Determines longest sleep time of the searched person
*  Parameters: 
*		sleepInfo data: structure to hold sleep data
*  		searchedPerson: The person the user is searching for
*  Precondition: sleepInfo structure has been filled with data
*  Postcondition: found the longest sleep time of the person that was searched for
*  Returns: An integer of the longest sleep time
*/

int longTime(sleepInfo data[], string searchedPerson, int count){
	int longMinute = 0;
	for(int i = 0; i < count; i++){
		if(searchedPerson != (data[i].firstName + data[i].lastName)){
		
		}
		else if(searchedPerson == (data[i].firstName + data[i].lastName) && longMinute < data[i].nightTotal){
			longMinute = data[i].nightTotal;
		}
	}
	return longMinute;
}

/* shortTime: Determines shortest sleep time of the searched person
*  Parameters:
*		sleepInfo data: structure to hold sleep data
*  		searchedPerson: The person the user is requesting data for
*  Precondition: sleepInfo structure has been filled with data
*  Postcondition: found the shortest sleep time of the person that was searched for
*  Returns: an integer of the shortest sleep time
*/
int shortTime(sleepInfo data[], string searchedPerson, int count){
	int shortMinute = 1000000;
	for(int i = 0; i < count; i++){
                if(searchedPerson != (data[i].firstName + data[i].lastName)){

                }
                else if(searchedPerson == (data[i].firstName + data[i].lastName) && shortMinute > data[i].nightTotal){
                        shortMinute = data[i].nightTotal;
                }
        }
        return shortMinute;
}

/* addTime: adds the sleep time for each entry that the searchedPerson is listed
*  Parameters:
*		sleepInfo data: structure to hold sleep data
*  		searchedPerson: The person the user is requesting data for
*  Precondition: sleepInfo structure has been filled with data
*  Postcondition: total sleep time added for each entry of searched person
*  Returns: Data for total time slept by the requested searched person
*/
int addTime(sleepInfo data[], string searchedPerson, int count){
	int time = 0;
	for(int i = 0; i < count;){
		if(searchedPerson != (data[i].firstName + data[i].lastName)){
			i++;
		}
		else if( searchedPerson == (data[i].firstName + data[i].lastName)){
			time += data[i].nightTotal;
			i++;
		}
	}
	return time;
}

/* searchName: Returns data for the person
*  Parameters:
*  		sleepInfo data: structure used to store sleep data 
*		searchedPerson: the person the user is requesting data for
*		time: total time slept by requested person
*		longMinutes: longest sleep time in minutes by requested person
*		shortMinutes: shortest time slept in miutes by requested person
*  Precondition: sleepInfo structure has been filled with data
*  Postcondition: Prints info to the screen
*  Returns: Nothing
*/
void searchName(sleepInfo data[], string searchedPerson, int count, int time, int longMinutes, int shortMinutes){
	for(int i = 0; i < count;){
		if ((data[i].firstName + data[i].lastName) != searchedPerson){
			i++;
		}
		else if((data[i].firstName + data[i].lastName) == searchedPerson){
			cout << data[i].firstName << " " << data[i].lastName;
			cout << endl;
			cout << "Total sleep time for this person is " << time; 
			cout << " minute(s)." << endl;
			cout << "Longest sleep time for this person was "; 
			cout << longMinutes << " minute(s)." << endl;
			cout << "Shortest sleep time for this person was ";
			cout << shortMinutes << " minute(s)." << endl;
			break;
		}
	}
}		

/* searchShort: displays shortest sleep time and date
*  Parameters:
*  		sleepInfo data: structure used to store sleep data
*  Precondition: sleepInfo structure has been filled
*  Postcondition: Displays shortest sleep time and date
*  Returns: Nothing
*/
void searchShort(sleepInfo data[]){
	cout << "The shortest sleep time is " << data[0].nightTotal; 
	cout << " minutes total on ";
	cout << data[0].date << "." << endl;
}

/* searchLong: Displays longest sleep time and date
*  Parameters:
*  		sleepInfo data: structure used to store sleep data
*  Precondition: sleepInfo structure has been filled
*  Postcondition: Displays longest sleep time and date
*  Returns: Nothing
*/
void searchLong(sleepInfo data[]){
	cout << "The longest sleep time is " << data[9].nightTotal;
	cout << " minutes total on ";
	cout << data[9].date << "." << endl;
}

/* whatNumber: Menu selection for shortest and longest sleep time
*  Parameters:
*  		sleepInfo data: structure used to store sleep data
*  Precondition: User has requested one of two choices
*  Postcondition: calls searchLong or searchShort function depending on choice
*  Returns: nothing
*/
int whatNumber(sleepInfo data[], int menuSelect, int count){
        if(menuSelect == 2){
                searchLong(data);
        }
        else if(menuSelect == 3){
                searchShort(data);
        }
}
