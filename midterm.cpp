#include <iostrsam>
using namespace std;


void fulfillRequest(holidayRequest[][], workingTime[][], int requestNum);
int main()
{
	//inputs
	(workers --> total number of employees)
	(days --> total number of days)
	(shiftNum --> total number of shift types)
	(holidays --> total number of holidays in a month)
	(w1, w2)
	(requestNum --> number of holiday requests)

	(shift --> 2D array (shiftNum + 1)x24, type of shifts)
	(needs --> 2D array (days x 24), number of employees needed each shift)
	(holidayRequest --> 2D array (2 x requestNum), employee ID & day of holiday request)

	//Employees' holiday schedule
	(int workTime[100][24] = {0} --> shift type of every employee)
	(int workingMember[31][24] = {0} --> number of employees in each shift)
	(distribute holidays to employees to meet "1 holiday in every 7 days" rerquirement)
	fulfillRequest(holidayRequest[], workingTime[], requestNum) --> void function, Fulfill "L holidays" requirement

	//Shift scheduling
	(2 ways, write individually first)
	for (int i = 0; i < days; i++) {
		int employee = 0;
		while (employee < workers - 1) {
			// Find 2 time slots with highest needs
			int highestShift[2] = {0};
			highestNeedTime(int needs[][24], int day, int highestShift[]);

			// Find shift type(s) that has those 2 time slots
			int resultShift[100] = {0};
			findShifts(i, shiftNum, shift, highestShift, 2, resultShift);

			// Assign the time slots to current employee
			for (int j = 1; j < resultShift[0] + 1; j++) {
				workTime[employee][day] = resultShift[j];
				// Subtract needs
				subtract(workTime[employee][day], i, shift, needs);
				employee++;
				if (employee == workers - 1)
					break;
			}
		}
	}



	//Total number of employees shortage
	int shortage = 0;


	return 0;
}

void fulfillRequest(int holidayRequest[][], int workingTime[][], int requestNum)
{

}

void highestNeedTime(int needs[][24], int day, int shift[])
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
	shift[0] = shiftMax1;
	shift[1] = shiftMax2;
}

void findShifts(int day, int shiftNum, int shift[][24], int highestShift[], int highestShiftNum, int resultShift[])
{
	for (int i = 0; i < shiftNum; i++) {
		bool fulfill = true;
		for (int j = 0; j < highestShiftNum; j++) {
			if (shift[day][highestShift[j]] != 1)
				fulfill = false;
		}
		if (fulfill == true) {
			resultShift[0] = 1; // Record number of shift that consist of the 2 shifts with highest needed employees
			resultShift[1] = i;
		}
		else if (fulfill == false) {
			for (int j = 0; j < highestShiftNum; j++) {
				int index = 0;
				if (shift[day][highestShift[j]] != 1) {
					index++;
					resultShift[index] = i;
				}
			}
			resultShift[0] = index;
		}
	}
}

void subtract(int shift_type, int day, int timetable[][100], int needs[][100])
{
	for (int i = 0; i < 24; i++) {
		if (needs[day][i] > 0) {
			if (shift_type > 0)
				needs[day][i]-= timetable[shift_type - 1][i];
		}
	}
}




