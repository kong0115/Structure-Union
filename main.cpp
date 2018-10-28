//	CS 1337.003  Project2  <sxk170832>	<Siang Swee Kong>

#include <iostream>   //preprocessor directive,in order to read or write to the standard input/output streams
#include <string>       //to use the string class, I need to include the header file

using namespace std; // declares that the program will be accessing entities whose names are part of the namespace called std

const int maxPatient = 500;  // a constant variable that represent the size of the array, 500 is a reasonable size for the array

enum DataType { VITAL, ACTIVITY };  //enumerated data type that consists of enumerators which represent integer constants, VITAL represent 0, ACTIVITY represent 1

struct VitalInfo  // a structure that consists patient vital information (abstract data type)
{
	float temperature;     // to store temperature
	unsigned int systolicPressure; // to store systolicPressure
	unsigned int diastolicPressure; //to store diastolicPressure
};

struct ActivityInfo // a structure that consists patient activity information
{
	unsigned int stepCount;   //to store step count
	unsigned int sleepHours;  //to store sleep hours
};


union VitalInfoOrActivityInfo  // a union of structure that can store either vital OR activity
{
	VitalInfo vital;
	ActivityInfo activity;
};

struct HealthInfo //a structure that consists of a union and a flag variable
{
	VitalInfoOrActivityInfo vitalOrActivity;
	DataType whatTypeOfDataAmIStoring;//to identify what type of data am I storing, either vital info or activity info
};

//function prototype
float findMaxTemp(HealthInfo[], int);
float findMinTemp(HealthInfo[], int);
unsigned int findMaxSP(HealthInfo[], int count);
unsigned int findMinSP(HealthInfo[], int count);
unsigned int findMaxDP(HealthInfo[], int count);
unsigned int findMinDP(HealthInfo[], int count);
unsigned int findTotalStep(HealthInfo[], int count);
unsigned int findTotalHours(HealthInfo[], int count);
void printInfo(int, float, float, unsigned int, unsigned int, unsigned int, unsigned int, int, unsigned int, unsigned int);

int main()
{
	string choice;  // a variable to store the user's desired action
	int count = 0;  // a variable to store the number of elements in the array
	int numVitalInfo = 0; // a variable to store the number of vital information
	int numActivityInfo = 0;  // a variable to store the number of activity information
	string a;
	HealthInfo patientInfo[maxPatient]; //create an array of structure with size of maxPatient


	do {
		cout << "Please enter the number for the desired action (1, 2, 3) :" << endl;
		cout << "   1 - Enter some patient vital information" << endl;
		cout << "   2 - Enter some patient activity information" << endl;
		cout << "   3 - Print summary information on the patient information and exit the program" << endl;
		cin >> choice; //ask the user for input

		float tempTemperature; //temporary variable to check input validation for temperature
		int tempSystolicPressure; //temporary variable to check input validation for systolic pressure
		int tempDiastolicPressure; //temporary variable to check input validation for diastolic pressure
		int tempStepCount; //temporary variable to check input validation for step count
		int tempSleepHours; //temporary variable to check input validation for sleep hours

		if (choice == "1") //if the user enter 1, then ask for the patient vital information
		{
			numVitalInfo++;       //increment the number of vital info by 1, to keep track the number of vital information
			patientInfo[count].whatTypeOfDataAmIStoring = VITAL; // a flag variable, use to determine the data that I am storing is the vital information

			cout << "Enter the temperature: "; //ask user for temperature
			cin >> tempTemperature;  //store the user input in temporary temperature variable
			while (!cin) // it will keep looping if the user enter invalid input
			{
				cout << "Please enter an floating number" << endl; //ask the user to enter a valid input for temperature
				cout << "Enter the temperature: ";
				cin.clear();     //use to clear the flag
				cin.ignore(100, '\n'); //will ignore invalid input for 100 characters or until the enter key hit
				cin >> tempTemperature; //store the user input in temporary temperature variable
			}
			patientInfo[count].vitalOrActivity.vital.temperature = tempTemperature; //assign the value of the tempTemperature to the temperature variable in the array.

			cout << "Enter the systolic pressure: "; //ask user for systolic pressure
			cin >> tempSystolicPressure; //store the user input in temporary variable
			while (tempSystolicPressure < 0 || !cin)  //it will keep looping if the user enter invalid input or negative numbers
			{
				cout << "Please enter an integral unsigned number" << endl; //ask the user to enter a valid input for systolic pressure
				cout << "Enter the systolicPressure: ";
				cin.clear();   //use to clear the flag
				cin.ignore(100, '\n'); //will ignore invalid input for 100 characters or until the enter key hit
				cin >> tempSystolicPressure; //store the user input in temporary systolic pressure variable
			}
			patientInfo[count].vitalOrActivity.vital.systolicPressure = tempSystolicPressure;//assign the value of the tempSystolicPressure to the systolic pressure variable in the array.
			getline(cin, a); //to avoid the program skip the next cin statement

			cout << "Enter the diastolic pressure: ";
			cin >> tempDiastolicPressure;
			while (tempDiastolicPressure < 0 || !cin)
			{
				cout << "Please enter an integral unsigned number" << endl;
				cout << "Enter the diastolicPressure: ";
				cin.clear();
				cin.ignore(100, '\n');
				cin >> tempDiastolicPressure;
			}
			patientInfo[count].vitalOrActivity.vital.diastolicPressure = tempDiastolicPressure;
			getline(cin, a);
			count++; //increment count variable by 1, use to keep track of how many elements in the array, also used as a subscript for the array
		}

		else if (choice == "2")  //if the user enter 2, then ask for the patient activity information
		{
			numActivityInfo++; //increment the number of vital info by 1, to keep track the number of activity information
			patientInfo[count].whatTypeOfDataAmIStoring = ACTIVITY; // a flag variable, use to determine the data that I am storing is the activity information

			cout << "Enter the step count: "; // ask user for step count
			cin >> tempStepCount; //store the user input in temporary variable
			while (tempStepCount < 0 || !cin) //it will keep looping if the user enter invalid input or negative numbers
			{
				cout << "Please enter an integral unsigned number" << endl;//ask the user to enter a valid input for step count
				cout << "Enter the step count: ";
				cin.clear();//use to clear the flag
				cin.ignore(100, '\n'); //will ignore invalid input for 100 characters or until the enter key hit
				cin >> tempStepCount;//store the user input in temporary step count variable
			}
			patientInfo[count].vitalOrActivity.activity.stepCount = tempStepCount;//assign the value of the tempStepCount to the step count variable in the array.
			getline(cin, a);//to avoid the program skip the next cin statement

			cout << "Enter the sleep hours: ";  //ask user for sleep hours
			cin >> tempSleepHours;  //store the user input in temporary variable
			while (tempSleepHours < 0 || !cin) //it will keep looping if the user enter invalid input or negative numbers
			{
				cout << "Please enter an integral unsigned number" << endl;//ask the user to enter a valid input for sleep hours
				cout << "Enter the sleep hours: ";
				cin.clear();   //use to clear the flag
				cin.ignore(100, '\n');//will ignore invalid input for 100 characters or until the enter key hit
				cin >> tempSleepHours;//store the user input in temporary sleep hours variable
			}
			patientInfo[count].vitalOrActivity.activity.sleepHours = tempSleepHours;//assign the value of the tempSleepHours to the sleep hours variable in the array.
			getline(cin, a);//to avoid the program skip the next cin statement
			count++;//increment count variable by 1, use to keep track of how many elements in the array, also used as a subscript for the array
		}

		else //if the user enter anything that is not 1, 2, or 3 for desired actions
			cout << "Please enter 1, 2, or 3 \n" << endl;  //ask the user for desired action again


	} while (choice != "3"); //the loop will stop if the user enter 3 for desired action


	float maxTemp = findMaxTemp(patientInfo, count); //pass in the array and number of elements to the findMaxTemp function, and assign the return value to maxTemp
	float minTemp = findMinTemp(patientInfo, count);//pass in the array and number of elements to the findMinTemp function, and assign the return value to minTemp
	unsigned int maxSP = findMaxSP(patientInfo, count);//pass in the array and number of elements to the findMaxSP function, and assign the return value to maxSP
	unsigned int minSP = findMinSP(patientInfo, count);//pass in the array and number of elements to the findMinSP function, and assign the return value to minSP
	unsigned int maxDP = findMaxDP(patientInfo, count);//pass in the array and number of elements to the findMaxDP function, and assign the return value to maxDP
	unsigned int minDP = findMinDP(patientInfo, count);//pass in the array and number of elements to the findMinDP function, and assign the return value to minDP
	unsigned int totalStep = findTotalStep(patientInfo, count);//pass in the array and number of elements to the findTotalStep function, and assign the return value to totalStep
	unsigned int totalHours = findTotalHours(patientInfo, count);//pass in the array and number of elements to the findTotalHours function, and assign the return value to totalHours

	printInfo(numVitalInfo, maxTemp, minTemp, maxSP, minSP, maxDP, minDP, numActivityInfo, totalStep, totalHours);

	system("pause");
	return 0;
}


float findMaxTemp(HealthInfo patientInfo[], int count) //a function to find the maximum temperature that accepts the array of structure and the number of elements from the main function
{
	float maxTemp = 0; //set the initial maximum temperature to a extreme low value
	for (int index = 0; index < count; index++)
	{
		if (patientInfo[index].whatTypeOfDataAmIStoring == VITAL) //only look for the structure that contains vital information, but not all the elements in the array
		{
			if (patientInfo[index].vitalOrActivity.vital.temperature > maxTemp) //if the temperature is higher than the maxTemp
				maxTemp = patientInfo[index].vitalOrActivity.vital.temperature; //replace the value of maxTemp with higher value
		}
	}
	return maxTemp; //return the maxTemp to the main function as a floating number
}


float findMinTemp(HealthInfo patientInfo[], int count) //a function to find the minimum temperature that accepts the array of structure and the number of elements from the main function
{
	float minTemp = 1000; //set the initial minimum temperature to a extreme high value
	for (int index = 0; index < count; index++)
	{
		if (patientInfo[index].whatTypeOfDataAmIStoring == VITAL) //only look for the structure that contains vital information, but not all the elements in the array
		{
			if (patientInfo[index].vitalOrActivity.vital.temperature < minTemp)//if the temperature is lower than the minTemp
				minTemp = patientInfo[index].vitalOrActivity.vital.temperature;//replace the value of minTemp with lower value
		}
	}
	return minTemp;//return the minTemp to the main function as a floating number
}

unsigned int findMaxSP(HealthInfo patientInfo[], int count)//a function to find the maximum systolic pressure
{
	unsigned int maxSP = 0; //set the initial maximum systolic pressure to a extreme low value
	for (int index = 0; index < count; index++)
	{
		if (patientInfo[index].whatTypeOfDataAmIStoring == VITAL)//only look for the structure that contains vital information, but not all the elements in the array
		{
			if (patientInfo[index].vitalOrActivity.vital.systolicPressure > maxSP) //if the systolic pressure is higher than the maxSP
				maxSP = patientInfo[index].vitalOrActivity.vital.systolicPressure; //replace the value of maxSP with higher value
		}
	}
	return maxSP;//return the maxSP to the main function as an unsigned int number
}

unsigned int findMinSP(HealthInfo patientInfo[], int count)//a function to find the minimum systolic pressure
{
	unsigned int minSP = 1000;//set the initial minimum systolic pressure to a extreme high value
	for (int index = 0; index < count; index++)
	{
		if (patientInfo[index].whatTypeOfDataAmIStoring == VITAL)//only look for the structure that contains vital information, but not all the elements in the array
		{
			if (patientInfo[index].vitalOrActivity.vital.systolicPressure < minSP)//if the systolic pressure is lower than the minSP
				minSP = patientInfo[index].vitalOrActivity.vital.systolicPressure;//replace the value of minSP with lower value
		}
	}
	return minSP;//return the minSP to the main function as an unsigned int number
}



unsigned int findMaxDP(HealthInfo patientInfo[], int count)//a function to find the maximum diastolic pressure
{
	unsigned int maxDP = 0;//set the initial maximum diastolic pressure to a extreme low value
	for (int index = 0; index < count; index++)
	{
		if (patientInfo[index].whatTypeOfDataAmIStoring == VITAL)//only look for the structure that contains vital information, but not all the elements in the array
		{
			if (patientInfo[index].vitalOrActivity.vital.diastolicPressure > maxDP)//if the diastolic pressure is higher than the maxDP
				maxDP = patientInfo[index].vitalOrActivity.vital.diastolicPressure;//replace the value of maxDP with higher value
		}
	}
	return maxDP; //return the maxDP to the main function as an unsigned int number
}

unsigned int findMinDP(HealthInfo patientInfo[], int count)//a function to find the minimum diastolic pressure
{
	unsigned int minDP = 1000;//set the initial minimum diastolic pressure to a extreme high value
	for (int index = 0; index < count; index++)
	{
		if (patientInfo[index].whatTypeOfDataAmIStoring == VITAL)//only look for the structure that contains vital information, but not all the elements in the array
		{
			if (patientInfo[index].vitalOrActivity.vital.diastolicPressure < minDP)//if the diastolic pressure is lower than the minDP
				minDP = patientInfo[index].vitalOrActivity.vital.diastolicPressure;//replace the value of minDP with lower value
		}
	}
	return minDP; //return the minDP to the main function as an unsigned int number
}

unsigned int findTotalStep(HealthInfo patientInfo[], int count)//a function to calculate the total step count
{
	unsigned int totalStep = 0; //set the initial total step to 0
	for (int index = 0; index < count; index++)
	{
		if (patientInfo[index].whatTypeOfDataAmIStoring == ACTIVITY)//only look for the structure that contains activity information, but not all the elements in the array
		{
			totalStep += patientInfo[index].vitalOrActivity.activity.stepCount; //add all the step count
		}
	}
	return totalStep; //return the totalStep to the main function as an unsigned int number
}

unsigned int findTotalHours(HealthInfo patientInfo[], int count)//a function to calculate the total sleep hours
{
	unsigned int totalHours = 0; //set the initial total hours to 0
	for (int index = 0; index < count; index++)
	{
		if (patientInfo[index].whatTypeOfDataAmIStoring == ACTIVITY) //only look for the structure that contains activity information, but not all the elements in the array
		{
			totalHours += patientInfo[index].vitalOrActivity.activity.sleepHours;//add all the sleep hours
		}
	}
	return totalHours;//return the totalHours to the main function as an unsigned int number
}

void printInfo(int numVitalInfo, float maxTemp, float minTemp, unsigned int maxSP, unsigned int minSP, unsigned int maxDP, unsigned int minDP, int numActivityInfo, unsigned int totalStep, unsigned int totalHours)
//a function to print summary information on the patient information

{
	cout << "Number of patient vital information records: " << numVitalInfo << endl;
	cout << "Maximum temperature: " << maxTemp << endl;
	cout << "Minimum temperature: " << minTemp << endl;
	cout << "Maximum systolic pressure: " << maxSP << endl;
	cout << "Minimum systolic pressure: " << minSP << endl;
	cout << "Maximum diastolic pressure: " << maxDP << endl;
	cout << "Minimum diastolic pressure: " << minDP << endl;
	cout << endl;

	cout << "Number of patient activity information records: " << numActivityInfo << endl;
	cout << "Total step count: " << totalStep << endl;
	cout << "Total sleep hours: " << totalHours << endl;
}


