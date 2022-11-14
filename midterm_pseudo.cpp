#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

// Label each type of shift with normal or night
struct Type_shift {
  int isnight;
  int isnormal;
};


int findBestShift();
void divideShift();
int totalNeeds();
int checkNightNum();
void fulfillRequest();
void fulfillRemainingHoliday();
void subtract();


int main()
{
  // All inputs with the holiday shift in index 0 of shift[31]
  int workers = -1, days = -1, shiftNum = -1, holidays = -1, w1 = -1, w2 = -1, requestNum = -1;
  int shift[31][24] = {0}, needs[31][24] = {0}, holidayRequest[2][3100] = {0};
  cin >> workers >> days >> shiftNum >> holidays >> w1 >> w2 >> requestNum;

  for (record all shift types in shift[] with holiday shift in index 0) {
    cin >> ...;
  }
  for (record all needs of each day & time slots) {
    cin >> ...;
  }
  for (record all the employee IDs & holiday request day in 2D array holidayRequest) {
    cin >> ...;
  }

  //Array to record the shift type of each employee in each day
  int workTime[100][31] = {0}, workingMember[31][24] = {0}, restDays[100] = {0};
  for (fill the workTime array with -1) {
  }

  // Helper array to match the findBestShift needed inputs
  int integers[31] = {0}; // integers[] = {0, 1, 2, 3, ...}
  for (int i = 1; i <= shiftNum; i++)
    integers[i] = i;




  // **** Distribute weekly holidays and fulfill parts of their holiday request (decide based on w1) **** //

  fulfillRequest(holidayRequest, workTime, restDays, needs, shift, requestNum,
    workers, days, holidays, shiftNum, integers, w1);
    // Distribute once a week holiday to every employee, ditribute the request only if required holidays
    // are not yet reached OR the benefit of fulfill request is greater than penalty of missing request(w1)
  fulfillRemainingHoliday(workTime, restDays, holidays, workers, days);
    // Fulfill holidays until the required amount such that there'll be no 1 full day where all employees are not working




  // ****Shift scheduling**** //

  int remnight[31] = {0}, remnormal[31] = {0}; // {0, 2, 4, 5,...} --> starts from index 1
  int totalShift[2] = {0}, workNight[100][31] = {0};
    // totalShift[0] record number of normal shifts, totalShift[1] night shifts
    // workNight array records night shift worked by each employee in each day, in the form of 0 and 1
  Type_shift array[31]; // Record whether a shift is normal or containing night shifts
  divideShift(shiftNum, shift, remnormal, remnight, totalShift, array);
    // Divide shift into normal and night shifts and record them in 2 different arrays


  // Distribute shift type to each employee for each day
  for (every worker) {
    for (every day) {
      if (not on holiday) {
        int curShift = findBestShift(...); //find the shift that covers the time slots with highest total needs
        if (curShift is a normal shift)
          assign to current workTime;
      
        else if (curShift contains night shift) {
          int bestNormal = findBestShift(...);

          int bestNormalTotal = 0, curTotal = 0;
          // Records the number of needs fulfilled by the bestNormal and curShift shift
          for (find bestNormalTotal);
          for (find curTotal);

          // Check whether this employee has worked night shift in the past 6 days
          if (employee has no night shift in the past 6 days)
            assign the curShift;
          else {
            // Compare the difference of number of needs fulfilled by bestNormal and curShift (reflects the extra benefits)
            // with the penalty of extra night shift(w2)
            if (difference > w2)
              assign night shift;
            else
              assign normal shift;
          }
        }
        // After the chosen shift is assign to this employee on this day,
        // subtract the needs fulfilled by this shift from the needs array
        subtract(...); // This void function will reduce the number of needs according to the shfit chosen



        // ***** This loop will continue repeat for every employee and day until all are assigned with 1 type of shift ***** //
      }
    }
  }

  // **** Print out the resulting workTime **** //

  return 0;
}


// ******************************************************************************* //
// ******************************** ALL FUNCTIONS ******************************** //
// ******************************************************************************* //


// Find the best shift that covers time slots with the highest total number of needs
int findBestShift(int day, int shiftNum, int needs[][24], int shift[][24], int rem[])
{
  int best = -1, highestTotal = -1;
  for (int i = 1; i <= shiftNum; i++) {
    int total = 0;
    for (int j = 0; j < 24; j++) {
      if (shift[rem[i]][j] == 1)
        total += needs[day][j];
    }

    if (total > highestTotal) {
      highestTotal = total;
      best = rem[i];
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

// Holiday minimum once a week (employee 0 will rest on day 1, 8, 15...; employee 1 rest on day 2, 9, 16,...)
// After that, fulfill all holidays based on request
// If the number of holidays of certain employee has reached L, decide whether or not to fulfill request by weighing the benefit and penalty
void fulfillRequest(int holidayRequest[][3100], int workTime[][31], int restDays[], int needs[][24], int shift[][24], int requestNum, int workers, int days, int holidays, int shiftNum, int integers[], int w1)
{
  for (int i = 0; i < workers; i ++)
  {
    for (int j = i % 7; j < days; j = j + 7) {
      workTime[i][j] = 0;
      restDays[i]++;
    }
  }

  for (int i = 0; i < requestNum; i ++) {
    if (restDays[holidayRequest[0][i] - 1] < holidays and workTime[holidayRequest[0][i] - 1][holidayRequest[1][i] - 1] != 0) {
      workTime[holidayRequest[0][i] - 1][holidayRequest[1][i] - 1] = 0;
      restDays[holidayRequest[0][i] - 1]++;
    }
    else if (restDays[holidayRequest[0][i] - 1] >= holidays and workTime[holidayRequest[0][i] - 1][holidayRequest[1][i] - 1] != 0) {
      int bestShiftChoice = findBestShift(holidayRequest[1][i] - 1, shiftNum, needs, shift, integers);
      int bestTotal = 0;
      for (int j = 0; j < 24; j++) {
        if (needs[bestShiftChoice][j] > 0)
          bestTotal += shift[bestShiftChoice][j];
      }
      if (bestTotal < w1) {
        workTime[holidayRequest[0][i] - 1][holidayRequest[1][i] - 1] = 0;
        restDays[holidayRequest[0][i] - 1]++;
      }
    }
  }
}

void fulfillRemainingHoliday(int workTime[][31], int restDays[], int holidays, int workers, int days)
{
  for (int i = 0; i < workers; i++) {
    int dayNum = 6 * i;
    while (restDays[i] < holidays) {
      dayNum = dayNum % days;
      if (workTime[i][dayNum] != 0) {
        workTime[i][dayNum] = 0;
        restDays[i]++;
      }
      dayNum++;
    }
  }
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
  totalShift[1] = nightN;
}