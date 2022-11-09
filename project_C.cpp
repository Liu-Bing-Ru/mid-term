#include <iostream>
using namespace std;

int main() 
{
	int pNum = 0, dayNum = 0, sNum = 0, L = 0, w1 = 0, w2 = 0, R = 0;
	int shift[50][50] = {0}, dayNeed[50][50] = {0}, dayEmployee[50][50] = {0}, pShift[100][50] = {0}, lack = 0, rest[10][50] = {0};
	
	cin >> pNum >> dayNum >> sNum >> L >> w1 >> w2 >> R;
	
	for (int i = 0; i <= sNum; i ++)
		for (int j = 0; j < 24; j ++)
			cin >> shift[i][j];
			
	for (int i = 0; i < dayNum; i ++)
		for (int j = 0; j < 24; j ++)
			cin >> dayNeed[i][j];
	
	for (int i = 0; i < 7; i ++)
		for (int j = 0; j < dayNum; j ++)
			rest[i][j] = 0;
	
	for (int i = 0; i < pNum; i ++)
		for (int j = 0; j < dayNum; j ++)
			pShift[i][j] = -1;
			
	//////////////////////////////////////////////////////////////////
	
	for (int i = 0; i < 7; i ++)
	{
		if (i != 6)
		{
			for (int j = i; j < dayNum; j = j + 7)
				rest[i][j] = 1;		
		}
		
		if (i == 6)
		{
			for (int k = 0; k < dayNum; k = k + 7)
				rest[i][k + 6] = 1;	
		}
	}
			
	
	
	//////////////////////////////////////////////////////////////////////////////////
	
	for (int i = 0; i < pNum; i ++)
	{
		for (int j = 0; j < dayNum; j ++)
		{
			int k = i % 7;
			if (rest[k][j] == 1)
				{
					pShift[i][j] = 0;
				}		
		}
	}
	
	int countRest[100] = {0};
	for (int i = 0; i < pNum; i ++)
	{
		for (int j = 0; j < dayNum; j ++)
		{
			if (pShift[i][j] == 0)
				{
					countRest[i] = countRest[i] + 1;
				}		
		}
			
		
	}
	
	//膥尿逼ヰ安ヰ安ぱ计才L 

	for (int i = 0; i < pNum; i ++)
	{
		
		if (countRest[i] < L)
		{
			int sum = 0;
			while(sum < L - countRest[i])
			{
				for (int j = 0; j < dayNum; j ++)
				{
					if (pShift[i][j] != 0)
					{
						pShift[i][j] = 0;
					}
					
					sum = sum + 1;
					
					if (sum == L - countRest[i] + 1)
					{
						break;
					}
				}
				
				
			}
		}

	}
	
	int k = 0;
	int blankspace = 0;
	for (int i = 0; i < dayNum; i ++)
	{                             
		for (int j = 0; j < pNum; j ++)
		{
			if (pShift[j][i] != 0)
			{                                                                                            
				blankspace = blankspace + 1;
				k = blankspace % sNum;
	
				if (k != 0)
				{
						pShift[j][i] = k;
				}
				
				if (k == 0)
				{
						pShift[j][i] = sNum;
				}
			}
		}
	}

////////////////////////////////////////////////////////////////////////////////////	
	

	
	for (int i = 0; i < pNum; i ++)
		for (int j = 0; j < dayNum; j ++)
		{
			if (j == dayNum - 1)
			{
				cout << pShift[i][j] << '\n';
			}
			
			else
			{
				cout << pShift[i][j] << ",";
			}
		}
	

	

	
	return 0;
}
