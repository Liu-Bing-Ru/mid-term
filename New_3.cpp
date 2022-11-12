// This version pick shift that covers time slots with the highest total needs for each normal and night shift
// Give night shift only if have no night shift in the past six work days

#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

struct Type_shift {
  int isnight;
  int isnormal;
};

int findBestShift(int day, int shiftNum, int needs[][24], int shift[][24], int rem[]);
void divideShift(int shiftNum, int shift[][24], int remnormal[], int remnight[], int totalShift[], Type_shift array[31]);
int totalNeeds(int shift_type, int day, int shift[][24], int needs[][24]);
int checkNightNum(int worker, int day, int workNight[][31]);
void fulfillRequest(int holidayRequest[][3100], int workTime[][31], int restDays[], int requestNum, int workers, int days);
void fulfillRemainingHoliday(int workTime[][31], int restDays[], int holidays, int workers, int days);
void subtract(int shift_type, int day, int shift[][24], int needs[][24], int workingMember[][24]);
int main()
{
	//inputs
	int workers = -1, days = -1, shiftNum = -1, holidays = -1, w1 = -1, w2 = -1, requestNum = -1;
	int shift[31][24] = {0}, needs[31][24] = {0}, holidayRequest[2][3100] = {0};

	cin >> workers >> days >> shiftNum >> holidays >> w1 >> w2 >> requestNum;
	for (int i = 1; i <= shiftNum; i ++) {
		for (int j = 0; j < 24; j ++)
			cin >> shift[i][j];
	}
	for (int j = 0; j < 24; j ++)
		cin >> shift[0][j];
	for (int i = 0; i < days; i ++) {
		for (int j = 0; j < 24; j ++)
			cin >> needs[i][j];
	}
	for (int i = 0; i < 2; i ++) {
		for (int j = 0; j < requestNum; j ++)
			cin >> holidayRequest[i][j];
	}

	//Employees' holiday schedule
	int workTime[100][31] = {0}, workingMember[31][24] = {0}, restDays[100] = {0};
	for (int i = 0; i < workers; i ++) {
		for (int j = 0; j < days; j ++)
			workTime[i][j] = -1;
	}

	fulfillRequest(holidayRequest, workTime, restDays, requestNum, workers, days);
	fulfillRemainingHoliday(workTime, restDays, holidays, workers, days);

	//Shift scheduling
	int remnight[31] = {0}, remnormal[31] = {0}; // {0, 2, 4, 5,...} starts from index 1
	int totalShift[2] = {0}, workNight[100][31] = {0};
	// totalShift[0] record number of normal shifts, totalShift[1] night shifts
	// workNight array records night shift worked by each employee in each day, in the form of 0 and 1
	Type_shift array[31];

	divideShift(shiftNum, shift, remnormal, remnight, totalShift, array);

	// Helper array to match the findBestShift needed inputs
	int integers[31] = {0};
	for (int i = 0; i <= shiftNum; i++)
		integers[i] = i;

	for (int i = 0; i < workers; i++) {
		for (int j = 0; j < days; j++) {
			if (workTime[i][j] != 0) {
				int curShift = findBestShift(j, shiftNum, needs, shift, integers);
				if (array[curShift].isnormal == 1) {
					workTime[i][j] = curShift;
					subtract(workTime[i][j], j, shift, needs, workingMember);
				}
				else if (array[curShift].isnight == 1) {
					// Find the total number of needs covered by each best normal and best night shift
					int bestNormal = findBestShift(j, totalShift[0], needs, shift, remnormal);
					int bestNight = findBestShift(j, totalShift[1], needs, shift, remnight);
					int bestNormalTotal = totalNeeds(bestNormal, j, shift, needs);
					int bestNightTotal = totalNeeds(bestNight, j, shift, needs);

					//cout << "NightNightNightNightNightNightNightNight" << "\n";
					//cout << "BestNormalTotal: " << bestNormalTotal << "\n";
					//cout << "BestNightTotal: " << bestNightTotal << "\n\n";

					// Check whether this employee has worked night shift in the past 6 days
					if (checkNightNum(i, j, workNight) == 0) {
						workTime[i][j] = curShift;
						workNight[i][j] = 1;
						subtract(workTime[i][j], j, shift, needs, workingMember);
					}
					else {
						if ((bestNightTotal - bestNormalTotal) > w2) {
							workTime[i][j] = curShift;
							workNight[i][j] = 1;
						}
						else {
							//cout << "\n\nWOWOWOWOWOWOWOWOWOWOWOWOWOWOW\n\n";
							workTime[i][j] = bestNormal;
						}
						subtract(workTime[i][j], j, shift, needs, workingMember);
					}
				}
				//subtract(workTime[i][j], j, shift, needs, workingMember); // Subtract time worked from the corresponding needs
			}
		}
	}
	



	// Print out result
	for (int i = 0; i < workers; i ++) {
		for (int j = 0; j < days; j ++) {
			if (j == days - 1)
				cout << workTime[i][j] << "\n";
			else
				cout << workTime[i][j] << ",";
		}
	}


	return 0;
}

// Holiday minimum once a week (employee 0 will rest on day 1, 8, 15...; employee 1 rest on day 2, 9, 16,...)
// After that, fulfill all holidays based on request
void fulfillRequest(int holidayRequest[][3100], int workTime[][31], int restDays[], int requestNum, int workers, int days)
{
	for (int i = 0; i < workers; i ++)
	{
		for (int j = i % 7; j < days; j = j + 7) {
			workTime[i][j] = 0;
			restDays[i]++;
		}
	}

	for (int i = 0; i < requestNum; i ++) {
		if (workTime[holidayRequest[0][i] - 1][holidayRequest[1][i] - 1] != 0) {
			workTime[holidayRequest[0][i] - 1][holidayRequest[1][i] - 1] = 0;
			restDays[holidayRequest[0][i] - 1]++;
		}
	}
}

// Fulfill every employee's holiday number to L using random number XDD
void fulfillRemainingHoliday(int workTime[][31], int restDays[], int holidays, int workers, int days)
{
	for (int i = 0; i < workers; i++) {
		srand(time(0));
		while (restDays[i] < holidays) {
			int randomNum = rand() % days;
			if (workTime[i][randomNum] != 0) {
				workTime[i][randomNum] = 0;
				restDays[i]++;
			}
		}
	}
}

// Find the best shift that covers time slots with the highest total number of needs
int findBestShift(int day, int shiftNum, int needs[][24], int shift[][24], int rem[])
{
	double total = 0, best = -1;
	double highestTotal = -1, shiftCount = 0;
	for (int i = 1; i <= shiftNum; i++) {
		for (int j = 0; j < 24; j++) {
			if (shift[rem[i]][j] == 1) {
				total += needs[day][j];
				shiftCount++;
			}
		}

		if (total > highestTotal) {
			highestTotal = total;
			best = i;
		}
	}
	return best;
}
int totalNeeds(int shift_type, int day, int shift[][24], int needs[][24])
{
	int total = 0;
	for (int i = 0; i < 24; i++) {
		if (shift[shift_type][i] == 1)
			total += needs[day][i];
	}
	return total;
}

int checkNightNum(int worker, int day, int workNight[][31])
{
	int start = (day - 6 >= 0) ? (day - 6) : 0;
	int sum = 0;
	for (int i = start; i < day; i++)
		sum += workNight[worker][i];

	return sum;
}


// Subtract the number of employees needed from needs array every time a shift type is given to employee
void subtract(int shift_type, int day, int shift[][24], int needs[][24], int workingMember[][24])
{
	for (int i = 0; i < 24; i++) {
		if (needs[day][i] > 0) {
			if (shift_type > 0) {
				needs[day][i] -= shift[shift_type][i];
				workingMember[day][i] += shift[shift_type][i];
			}
		}
	}
}


// Find the shiftNum and number of shifts of each normal and night shift
void divideShift(int shiftNum, int shift[][24], int remnormal[], int remnight[], int totalShift[], Type_shift array[31])
{
		int nightN = 0, normalN = 0;
		for (int i = 1; i <= shiftNum; i++) {
			for (int j = 0; j < 24; j++) {
				if (j >= 18 and shift[i][j] == 1)
        	array[i].isnight = 1;
    	}
  	}
  	for (int i = 1; i <= shiftNum; i++) {
    	if (array[i].isnight != 1) {
      		array[i].isnormal = 1;
      		normalN++;
      		remnormal[normalN] = i;
    	}
  	}

  	nightN = shiftNum - normalN;

  	int k = 0;
  	for (int i = 1; i <= shiftNum; i++) {
    	if (array[i].isnight == 1) {
    		k++;
      		remnight[k] = i;
    	}
  	}

  	totalShift[0] = normalN;
  	totalShift[1] = k;
}