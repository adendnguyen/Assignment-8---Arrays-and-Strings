//
// Name: Aden Nguyen
// Date: 06/22/26
// Course: COSC 1437 C++ Programming Fundamentals II
// Desc: Chapter 8 Lab - Manages grade data for up to 10 students
//       across 4 test scores using arrays and cArrays


#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 10;
const int NUM_TESTS = 4;



void readRoster(char names[][31], int scores[][NUM_TESTS], int &count)
{
    int numStudents = 0;
    do
    {
        cout << "Enter the number of students (1-10) >> ";
        cin >> numStudents;
    
    }
    while(numStudents < 1 || numStudents > MAX_STUDENTS);
    cin.ignore();
    for (int i = 0; i < numStudents; i++)
    {
        cout << "Enter student name >> ";
        cin.getline(names[i], 31);

        for (int j = 0; j < NUM_TESTS; j++)
        {
            cout << "Enter test scores (0-100) >> ";
            cin >> scores[i][j];
        }
         cin.ignore();
    }

    count = numStudents;
}
void calcAverages(const int scores[][NUM_TESTS], double averages[], char grades[], int count)
{
    for (int i = 0; i < count; i++)
    {
        double total = 0;
        for (int j = 0; j < NUM_TESTS; j++)
        {
            total += scores[i][j];
        }

        averages[i] = total / NUM_TESTS;

        if (averages[i] >= 90)
            grades[i] = 'A';
        else if (averages[i] >= 80)
            grades[i] = 'B';
        else if (averages[i] >= 70)
            grades[i] = 'C';
        else if (averages[i] >= 60)
            grades[i] = 'D';
        else
            grades[i] = 'F';
    }
}
void sortRoster(char names[][31], int scores[][NUM_TESTS], double averages[], char grades[], int count)
{
    int smallest;
    for(int i =0; i < count -1; i++)
    {
        smallest = i;
        for(int j = i + 1; j < count;j++)
        {
            if(strcmp(names[j],names[smallest]) < 0)
            {
                smallest = j;
            }
            
        }
        if(smallest != i)
        {
            char temp[31];
            strcpy(temp, names[i]);
            strcpy(names[i], names[smallest]);
            strcpy(names[smallest],temp);
            
            char tempGrade = grades[i];
            grades[i] = grades[smallest];
            grades[smallest] = tempGrade;

            double tempAverage = averages[i];
            averages[i] = averages[smallest];
            averages[smallest] = tempAverage;

            for(int j =0; j < NUM_TESTS; j++)
            {
                int tempScore = scores[i][j];
                scores[i][j] = scores[smallest][j];
                scores[smallest][j] = tempScore;
            }


        }
    }
}
int searchRoster(const char names[][31], int count, const char target[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(names[i], target) == 0)
        {
            return i;
        }
    }
    return -1;
}
void printRoster(const char names[][31], const int scores[][NUM_TESTS], const double averages[], const char grades[], int count)
{
    cout << fixed << setprecision(2);
    cout << "======================= STUDENT ROSTER =======================\n";

cout << left << setw(20) << "Student Name"
     << setw(20) << "Test Scores"
     << right << setw(15) << "Average"
     << setw(10) << "Grade"
     << endl;

for (int i = 0; i < count; i++)
{
    cout << left << setw(20) << names[i];

   
    for (int j = 0; j < NUM_TESTS; j++)
    {
        cout << right << setw(4) << scores[i][j] << "%";
    }

    cout << fixed << setprecision(2);

    cout << right << setw(15) << averages[i] << "%"
         << setw(10) << grades[i]
         << endl;
}
}
void printStats(const double averages[], int count)
{
    cout << fixed << setprecision(2);
    double localAverages[count];

    //copies the data into a local array
    for(int i =0; i < count;i++)
    {
        localAverages[i] = averages[i];
    }
    double highscore = localAverages[0], lowscore = localAverages[0], classAverage = 0.0, total = 0.0;
    for(auto average: localAverages)
    {
        total += average;
        if(average > highscore)
            highscore = average;
        if (average < lowscore)
            lowscore = average;
    }
    classAverage = total/count;

    cout << "======================= Class Statistics =======================" << endl;
    cout<< "High Score: " << highscore << "%" << endl;
    cout << "Low Score: " << lowscore << "%" << endl;
    cout << "Class Average: " << classAverage << "%" << endl;

}

int main()
{
    char names[MAX_STUDENTS][31];
    int scores[MAX_STUDENTS][NUM_TESTS];
    double averages[MAX_STUDENTS];
    char grades[MAX_STUDENTS];
    char target[31];

    int count = 0;

    int option = 0;
    do
    {
            cout << "===== Roster Report Menu =====" << endl;
            cout << "1. Load roster (enter data)" << endl;
            cout << "2. Calculate averages and grades" << endl;
            cout << "3. Sort roster alphabetically" << endl;
            cout << "4. Search for a student" << endl;
            cout << "5. Print roster" << endl;
            cout << "6. Print class statistics" << endl;
            cout << "7. Quit" << endl;
            cout << "Enter choice: ";
            cin >> option;
            cin.clear();
            cin.ignore();
        

        switch (option)
        {
        case 1:
            readRoster(names, scores, count);
            break;
        case 2:
            calcAverages(scores, averages, grades, count);
            break;
        case 3:
            sortRoster(names, scores, averages, grades, count);
            break;
        case 4:
        {
            cout << endl;
            cout << "Enter student name: ";
            cin.getline(target, 31);
            int stuidx = searchRoster(names, count, target);
            if(stuidx != -1)
            {
                cout << "FOUND: The index of the student you are looking for is " << stuidx << endl;
            }
            else
            {
                cout << "STUDENT NOT FOUND"  << endl;
            }
            
            break;
        }
        case 5:
            printRoster(names, scores, averages, grades, count);
            break;
        case 6:
            if (count >0)
                printStats(averages, count);
            break;
        case 7:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
        }
        cout << endl;

    } while (option != 7);

    return 0;

/*Test Run #1  
   ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 1
    Enter the number of students (1-10) >> 4
    Enter student name >> Jack
    Enter test scores (0-100) >> 100
    Enter test scores (0-100) >> 100
    Enter test scores (0-100) >> 100
    Enter test scores (0-100) >> 100
    Enter student name >> Susie
    Enter test scores (0-100) >> 90
    Enter test scores (0-100) >> 90
    Enter test scores (0-100) >> 90
    Enter test scores (0-100) >> 90
    Enter student name >> Charles
    Enter test scores (0-100) >> 80
    Enter test scores (0-100) >> 80
    Enter test scores (0-100) >> 80
    Enter test scores (0-100) >> 80
    Enter student name >> James
    Enter test scores (0-100) >> 70
    Enter test scores (0-100) >> 70
    Enter test scores (0-100) >> 70
    Enter test scores (0-100) >> 70

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 2

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 4

    Enter student name: James
    FOUND: The index of the student you are looking for is 3

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 5
    ======================= STUDENT ROSTER =======================
    Student Name        Test Scores                 Average     Grade
    Jack                 100% 100% 100% 100%         100.00%         A
    Susie                 90%  90%  90%  90%          90.00%         A
    Charles               80%  80%  80%  80%          80.00%         B
    James                 70%  70%  70%  70%          70.00%         C

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 3

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 5
    ======================= STUDENT ROSTER =======================
    Student Name        Test Scores                 Average     Grade
    Charles               80%  80%  80%  80%          80.00%         B
    Jack                 100% 100% 100% 100%         100.00%         A
    James                 70%  70%  70%  70%          70.00%         C
    Susie                 90%  90%  90%  90%          90.00%         A

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 6
    ======================= Class Statistics =======================
    High Score: 100.00%
    Low Score: 70.00%
    Class Average: 85.00%

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 7
    Goodbye!
*/

/*Test Run #2
    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: No
    Invalid Input

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: Invalid Input

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 6

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 1
    Enter the number of students (1-10) >> 3
    Enter student name >> Kevin
    Enter test scores (0-100) >> 50
    Enter test scores (0-100) >> 60
    Enter test scores (0-100) >> 70
    Enter test scores (0-100) >> 80
    Enter student name >> Brandon
    Enter test scores (0-100) >> 70
    Enter test scores (0-100) >> 71
    Enter test scores (0-100) >> 72
    Enter test scores (0-100) >> 73
    Enter student name >> Esteban
    Enter test scores (0-100) >> 50
    Enter test scores (0-100) >> 50
    Enter test scores (0-100) >> 50
    Enter test scores (0-100) >> 50

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 2

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 4

    Enter student name: Bob
    STUDENT NOT FOUND

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 5
    ======================= STUDENT ROSTER =======================
    Student Name        Test Scores                 Average     Grade
    Kevin                 50%  60%  70%  80%          65.00%         D
    Brandon               70%  71%  72%  73%          71.50%         C
    Esteban               50%  50%  50%  50%          50.00%         F

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 3

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 5
    ======================= STUDENT ROSTER =======================
    Student Name        Test Scores                 Average     Grade
    Brandon               70%  71%  72%  73%          71.50%         C
    Esteban               50%  50%  50%  50%          50.00%         F
    Kevin                 50%  60%  70%  80%          65.00%         D

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 6
    ======================= Class Statistics =======================
    High Score: 71.50%
    Low Score: 50.00%
    Class Average: 62.17%

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 7
    Goodbye!
*/
}