#include <iostream>
#include <ctime>
#include "project.h"

using namespace std;

int main() {
    int numFeat, choice = 0;

    cout << "Welcome to Dhruv Parmar's Feature Selection Algorithm." << endl;
    cout << "Please enter total number of features:" << endl;
    cin >> numFeat;
    Project project = Project(numFeat);
    cout << endl;
    cout << "Type the number of the algorithm you want to run." << endl;
    cout << "1. Forward Selection" << endl;
    cout << "2. Backward Elimination" << endl;
    cout << "3. Dhruv's Special Algorithm" << endl;
    cin >> choice;
    cout << endl;
    project.search(choice, numFeat);
    return 0;
}