// This version only pick shift that covers time slots with the highest total needs

#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int findBestShift(int day, int shiftNum, int needs[][24], int shift[][24]);
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
	for (int i = 0; i < workers; i++) {
		for (int j = 0; j < days; j++) {
			if (workTime[i][j] != 0) {
				workTime[i][j] = findBestShift(j, shiftNum, needs, shift);
				subtract(workTime[i][j], j, shift, needs, workingMember);
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
int findBestShift(int day, int shiftNum, int needs[][24], int shift[][24])
{
	double total = 0, best = -1;
	double highestTotal = -1, shiftCount = 0;
	for (int i = 1; i <= shiftNum; i++) {
		for (int j = 0; j < 24; j++) {
			if (shift[i][j] == 1) {
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