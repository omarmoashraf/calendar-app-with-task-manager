#include <bits/stdc++.h>
using namespace std;

// Function declarations
void PrintMonth(int year, int month, map<int, string> tasks);
void PrintMonthTitle(int year, int month);
void PrintMonthName(int month);
void PrintMonthBody(int year, int month, map<int, string> tasks);
int GetStartDay(int year, int month);
int GetTotalNumberOfDays(int year, int month);
int GetTotalNumberOfDaysInMonth(int year, int month);
bool IsLeapYear(int year);

int main() {
    int year, month;
    map<int, string> tasks;

    cout << "Enter Year: " << endl;
    cin >> year;
    while (year < 1900) {
        cout << "Invalid Input. Enter Year >= 1900: ";
        cin >> year;
    }

    cout << "Enter Month (1-12): " << endl;
    cin >> month;
    while (month < 1 || month > 12) {
        cout << "Invalid Input. Enter Month (1-12): ";
        cin >> month;
    }

    // Add tasks
    char choice;
    cout << "Do you want to add tasks for this month? (y/n): ";
    cin >> choice;
    while (choice == 'y') {
        int day;
        string task;
        cout << "Enter day: ";
        cin >> day;
        int maxDay = GetTotalNumberOfDaysInMonth(year, month);
        while (day < 1 || day > maxDay) {
            cout << "Invalid Input. Enter day (1-" << maxDay << "): ";
            cin >> day;
        }

        cin.ignore(); // to ignore newline
        cout << "Enter task: ";
        getline(cin, task);
        tasks[day] = task;

        cout << "Add another task? (y/n): ";
        cin >> choice;
    }

    // Print calendar
    PrintMonth(year, month, tasks);

    // Print task list
    if (!tasks.empty()) {
        cout << "\nTasks:\n";
        for (auto p : tasks) {
            cout << "Day " << p.first << ": " << p.second << endl;
        }
    }

    return 0;
}

void PrintMonth(int year, int month, map<int, string> tasks) {
    PrintMonthTitle(year, month);
    PrintMonthBody(year, month, tasks);
}

void PrintMonthTitle(int year, int month) {
    PrintMonthName(month);
    cout << year << endl;
    cout << "----------------------------" << endl;
    cout << " Sun Mon Tue Wed Thu Fri Sat" << endl;
}

void PrintMonthName(int month) {
    string names[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    cout << names[month] << endl;
}

void PrintMonthBody(int year, int month, map<int, string> tasks) {
    int startDay = GetStartDay(year, month);
    int numberOfDays = GetTotalNumberOfDaysInMonth(year, month);

    for (int i = 0; i < startDay; i++) {
        cout << "    ";
    }
    for (int i = 1; i <= numberOfDays; i++) {
        if (tasks.count(i)) {
            cout << setw(2) << i << "*";
        } else {
            cout << setw(3) << i;
        }
        if ((i + startDay) % 7 == 0) cout << endl;
    }
    cout << endl;
}

int GetStartDay(int year, int month) {
    int Startday = 1; // 1/1/1900 was a Monday, i.e., index 1
    int totalDays = GetTotalNumberOfDays(year, month);
    return (totalDays + Startday) % 7;
}

int GetTotalNumberOfDays(int year, int month) {
    int totalDays = 0;
    for (int i = 1900; i < year; i++) {
        totalDays += IsLeapYear(i) ? 366 : 365;
    }
    for (int i = 1; i < month; i++) {
        totalDays += GetTotalNumberOfDaysInMonth(year, i);
    }
    return totalDays;
}

int GetTotalNumberOfDaysInMonth(int year, int month) {
    if (month == 2)
        return IsLeapYear(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    return 31;
}

bool IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
