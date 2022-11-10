#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;


void fulfillRequest(int holidayRequest[][3100], int workTime[][31], int restDays[], int requestNum, int workers, int days);
void fulfillRemainingHoliday(int workTime[][31], int restDays[], int holidays, int workers, int days);
void highestNeedTime(int needs[][24], int day, int shift[]);
void findShifts(int day, int shiftNum, int shift[][24], int highestShift[], int highestShiftNum, int resultShift[]);
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
	for (int i = 0; i < days; i++) {
		int employee = 0;
		while (employee < workers) {
			// Find 2 time slots with highest needs
			int highestShift[2] = {0};
			highestNeedTime(needs, i, highestShift);
			//cout << "shifts: " << highestShift[0] << ", " << highestShift[1] << "\n";

			// Find shift type(s) that has those 2 time slots
			// resultShift[0] is the number of type of shift that's needed to cover the 2 slots with highest needs
			// resultShift[1] and elements after this are the type of shifts that we need to give employees
			int resultShift[100] = {0};
			findShifts(i, shiftNum, shift, highestShift, 2, resultShift);
			//test// cout << "no of resultShift: " << resultShift[0] << "\n";
			//test// cout << "resultShift: " << resultShift[1] << "\n";

			// Assign the time slots to current employee
			for (int j = 1; j < resultShift[0] + 1; j++) {
				if (workTime[employee][i] == 0) {
					employee++;
					break;
				}
				else if (workTime[employee][i] == -1) {
					workTime[employee][i] = resultShift[j];
					employee++;
					// Subtract needs
					subtract(resultShift[j], i, shift, needs, workingMember);
				}
				if (employee == workers)	
					break;
			}
			//test// cout << "employee: " << employee << "\n";
		}
		//test// cout << "\n\n****************************************\n\n";
	}

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

// Find the 2 shift in a day that needs the most number of employee
void highestNeedTime(int needs[][24], int day, int highestShift[])
{
	int needMax1 = 0, needMax2 = 0;
	int shiftMax1 = -1, shiftMax2 = -1;

	// Find 2 time slots with highest needs
	for (int i = 0; i < 24; i++) {
		if (needs[day][i] > needMax1) {
			needMax1 = needs[day][i];
			shiftMax1 = i;
		}
		else if (needs[day][i] > needMax2) {
			needMax2 = needs[day][i];
			shiftMax2 = i;
		}
	}
	highestShift[0] = shiftMax1;
	highestShift[1] = shiftMax2;
}

// Find 1 or 2 shift that includes the 2 shifts gotten from highestNeedTime function
// Save the number of shifts and the type of shifts in an array
void findShifts(int day, int shiftNum, int shift[][24], int highestShift[], int highestShiftNum, int resultShift[])
{
	for (int i = 0; i <= shiftNum; i++) {
		bool fulfill = true;
		for (int j = 0; j < highestShiftNum; j++) {
			if (shift[i][highestShift[j]] != 1)
				fulfill = false;
		}
		if (fulfill == true) {
			resultShift[0] = 1; // Record number of shift that consist of the 2 shifts with highest needed employees
			resultShift[1] = i;
			break;
		}
		else if (fulfill == false) {
			int index = 0;
			for (int j = 0; j < highestShiftNum; j++) {
				if (shift[i][highestShift[j]] != 1) {
					index++;
					resultShift[index] = i;
					if (i < shiftNum)
						i++;
				}
			}
			resultShift[0] = index;
		}
	}
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