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

	//Total number of employees shortage
	int shortage = 0;


	return 0;
}

void fulfillRequest(int holidayRequest[][], int workingTime[][], int requestNum)
{

}