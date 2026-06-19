#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 10;
const int NUM_TESTS = 4;

char names[MAX_STUDENTS][31];
int scores[MAX_STUDENTS][NUM_TESTS];
double averages[MAX_STUDENTS];
char grades[MAX_STUDENTS];
char target[31];

int count = 0;

void readRoster(char names[][31], int scores[][NUM_TESTS], int &count)
{
    int numStudents;
    cout << "Enter the number of students (1-10) >> ";
    cin >> numStudents;
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
    cout << "======================= STUDENT ROSTER =======================" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << left << setw(21)<< "Name: " << right << setw(20) << names[i] << endl;
        cout << left << setw(20)<< "Test Scores: ";
        for (int j = 0; j < NUM_TESTS; j++)
        {
            cout << right << setw(20) << scores[i][j] << "% ";
        }
        cout << endl;
        cout << left << setw(20)<< "Test Average: " << right << setw(20)<< averages[i] << "%" << endl;
        cout << left << setw(21)<< "Grade: " <<  right << setw(20) << grades[i] << endl;
        cout << endl;
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
            cout << endl;
            cout << "Enter student name: ";
            cin.getline(target, 31);
            cout << "The index of the student you are looking for is " << searchRoster(names, count, target) << endl;
            break;
        case 5:
            printRoster(names, scores, averages, grades, count);
            break;
        case 6:
            printStats(averages, count);
            break;

        default:
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
    Enter test scores (0-100) >> 90
    Enter test scores (0-100) >> 92
    Enter test scores (0-100) >> 88
    Enter student name >> Susie
    Enter test scores (0-100) >> 85
    Enter test scores (0-100) >> 82
    Enter test scores (0-100) >> 79 
    Enter test scores (0-100) >> 91
    Enter student name >> Charles
    Enter test scores (0-100) >> 100
    Enter test scores (0-100) >> 96
    Enter test scores (0-100) >> 89
    Enter test scores (0-100) >> 92
    Enter student name >> James
    Enter test scores (0-100) >> 87
    Enter test scores (0-100) >> 74
    Enter test scores (0-100) >> 83
    Enter test scores (0-100) >> 78

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
    The index of the student you are looking for is 3

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
    Name:                                Jack
    Test Scores:                         100%                   90%                   92%                   88% 
    Test Average:                      92.50%
    Grade:                                  A

    Name:                               Susie
    Test Scores:                          85%                   82%                   79%                   91% 
    Test Average:                      84.25%
    Grade:                                  B

    Name:                             Charles
    Test Scores:                         100%                   96%                   89%                   92% 
    Test Average:                      94.25%
    Grade:                                  A

    Name:                               James
    Test Scores:                          87%                   74%                   83%                   78% 
    Test Average:                      80.50%
    Grade:                                  B


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
    Name:                             Charles
    Test Scores:                         100%                   96%                   89%                   92% 
    Test Average:                      94.25%
    Grade:                                  A

    Name:                                Jack
    Test Scores:                         100%                   90%                   92%                   88% 
    Test Average:                      92.50%
    Grade:                                  A

    Name:                               James
    Test Scores:                          87%                   74%                   83%                   78% 
    Test Average:                      80.50%
    Grade:                                  B

    Name:                               Susie
    Test Scores:                          85%                   82%                   79%                   91% 
    Test Average:                      84.25%
    Grade:                                  B


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
    High Score: 94.25%
    Low Score: 80.50%
    Class Average: 87.88%

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 7
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
    Enter choice: 1
    Enter the number of students (1-10) >> 3
    Enter student name >> Kevin
    Enter test scores (0-100) >> 50
    Enter test scores (0-100) >> 60
    Enter test scores (0-100) >> 70
    Enter test scores (0-100) >> 65
    Enter student name >> Brandon
    Enter test scores (0-100) >> 70
    Enter test scores (0-100) >> 71
    Enter test scores (0-100) >> 72
    Enter test scores (0-100) >> 73
    Enter student name >> Esteban
    Enter test scores (0-100) >> 80
    Enter test scores (0-100) >> 79
    Enter test scores (0-100) >> 78
    Enter test scores (0-100) >> 77

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
    The index of the student you are looking for is -1

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
    Name:                               Kevin
    Test Scores:                          50%                   60%                   70%                   65% 
    Test Average:                      61.25%
    Grade:                                  D

    Name:                             Brandon
    Test Scores:                          70%                   71%                   72%                   73% 
    Test Average:                      71.50%
    Grade:                                  C

    Name:                             Esteban
    Test Scores:                          80%                   79%                   78%                   77% 
    Test Average:                      78.50%
    Grade:                                  C


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
    Name:                             Brandon
    Test Scores:                          70%                   71%                   72%                   73% 
    Test Average:                      71.50%
    Grade:                                  C

    Name:                             Esteban
    Test Scores:                          80%                   79%                   78%                   77% 
    Test Average:                      78.50%
    Grade:                                  C

    Name:                               Kevin
    Test Scores:                          50%                   60%                   70%                   65% 
    Test Average:                      61.25%
    Grade:                                  D


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
    High Score: 78.50%
    Low Score: 61.25%
    Class Average: 70.42%

    ===== Roster Report Menu =====
    1. Load roster (enter data)
    2. Calculate averages and grades
    3. Sort roster alphabetically
    4. Search for a student
    5. Print roster
    6. Print class statistics
    7. Quit
    Enter choice: 7
*/
}