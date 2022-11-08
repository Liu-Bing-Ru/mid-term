#include <iostream> 
#include<cstring>
#include<cctype>
using namespace std;


int main()
{

	int workers = 0, days = 0 , shiftNum = 0, holidays = 0, w1 = 0, w2 = 0, requestNum = 0;
	int shift[50][50] = {0}, needs[50][50] = {0}, holidayRequest[5][100] = {0};
	
	int workTime[100][50] = {0}, workingMember[50][50] = {0}; 
	
	int rest[50][50] = {0}, restShift[100] = {0};
	
	cin >> workers >> days >> shiftNum >> holidays >> w1 >> w2 >> requestNum;
	
	for (int i = 0; i <= shiftNum; i ++)
		for (int j = 0; j < 24; j ++)
			cin >> shift[i][j];
	
	for (int i = 0; i <= days; i ++)
		for (int j = 0; j < 24; j ++)
			cin >> needs[i][j];

	for (int i = 0; i < 2; i ++)
		for (int j = 0; j < holidays; j ++)
			cin >> holidayRequest[i][j];
			

			
	for (int i = 0; i < 7; i ++)
		for (int j = 0; j < days; j ++)
			rest[i][j] = 0;


	for (int i = 0; i < 7; i ++)
	{
		if (i != 6)
		{
			for (int j = i; j < days; j = j + 7)
				rest[i][j] = 1;		
		}
		
		if (i == 6)
		{
			for (int k = 0; k < days; k = k + 7)
				rest[i][k + 6] = 1;	
		}
	}
	
	
	for (int i = 0; i < workers; i ++)
	{
		for (int j = 0; j < days; j ++)
		{
			int k = i % 7;
			if (rest[k][j] == 1)
			{
				workTime[i][j] = shiftNum;
			}		
		}
	}
	
	//¦³°ÝÃD 
	for (int j = 0; j < requestNum; j ++)
	{
		workTime[holidayRequest[0][j] - 1][holidayRequest[1][j] - 1] = shiftNum;
	}
	
	for (int i = 0; i < workers; i ++)
		for (int j = 0; j < days; j ++)
		{
			if (j == days - 1)
			{
				cout << workTime[i][j] << '\n';
			}
			
			else
			{
				cout << workTime[i][j] << " ";
			}
		
		}

	return 0;
}

