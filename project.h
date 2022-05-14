#ifndef PROJECT2_PROJECT_H
#define PROJECT2_PROJECT_H

#include <iostream>
#include <ctime>
#include <iomanip>
#include <queue>
#include <vector>
#include <utility>
#include<bits/stdc++.h>

using namespace std;

class Project {
private:
    int size;
public:
    int getSize() {
        return this->size;
    }

    float getRandom() {
        float num = 0;
        num = ((rand() % 999) + 1) / 10.0;
        return num;
    }

    Project(int size) {
        this->size = size;
        srand(time(NULL));
    }

    bool isinSet(vector<int> set, int num) {
        for (auto &feature: set) {
            if (num == feature) {
                return true;
            }
        }
        return false;
    }

    vector<pair<float, vector<int>>> exploreForward(vector<int> set) {
        vector<pair<float, vector<int>>> sets;
        vector<int> curSet;
        for (int i = 0; i < this->getSize(); i++) {
            float temp = getRandom();
            vector<int> curSet = set;
            if (!isinSet(curSet, i + 1)) {
                curSet.push_back(i + 1);
                sets.push_back(make_pair(temp, curSet));
            }
        }
        return sets;
    }

    vector<pair<float, vector<int>>> exploreBackward(vector<int> set) {
        vector<pair<float, vector<int>>> sets;
        vector<int> curSet;
        for (int i = 0; i < set.size(); i++) {
            float temp = getRandom();
            vector<int> curSet = set;
            if (isinSet(curSet, i + 1)) {
                curSet.erase(curSet.begin() + i);
                sets.push_back(make_pair(temp, curSet));
            }
        }
        return sets;
    }

    void display(pair<float, vector<int>> set) {
        cout << "Using feature(s) { ";
        for (int i = 0; i < set.second.size(); i++) {
            cout << set.second[i];
            if (i != set.second.size() - 1) cout << ", ";
        }
        cout << " } accuracy is " << set.first << "%" << endl;
    }

    void printLocalMax(pair<float, vector<int>> localMax) {
        cout << endl;
        cout << "Feature set { ";
        for (int i = 0; i < localMax.second.size(); i++) {
            cout << localMax.second[i];
            if (i != localMax.second.size() - 1) cout << ", ";
        }
        cout << " }, was best, accuracy is " << localMax.first << "%" << endl << endl;
    }

    void printGlobalMax(pair<float, vector<int>> globalMax) {
        cout << "Finised search!! The best feature subset is  { ";
        for (int i = 0; i < globalMax.second.size(); i++) {
            cout << globalMax.second[i];
            if (i != globalMax.second.size() - 1) cout << ", ";
        }
        cout << " }, which has an accuracy of " << globalMax.first << "%" << endl << endl;
    }

    void forward_selection() {
        vector<float> accuracy;
        vector<pair<float, vector<int>>> sets;
        vector<int> set;
        pair<float, vector<int>> maxAccuracy;
        maxAccuracy.first = -2;
        for (int i = 0; i < this->getSize(); i++) {
            float currAccuracy = -1;
            sets = exploreForward(set);
            for (auto expanded: sets) {
                // display set with accuracy here
                display(expanded);
                if (expanded.first > currAccuracy) {
                    currAccuracy = expanded.first;
                    set = expanded.second;
                }
            }
            // print local max
            printLocalMax(make_pair(currAccuracy, set));
            if (currAccuracy > maxAccuracy.first) {
                maxAccuracy.first = currAccuracy;
                maxAccuracy.second = set;
            } else {
                cout << "(Warning, Accuracy has decreased!)" << endl << endl;
                break;
            }

        }
        // print globalmax
        printGlobalMax(maxAccuracy);
    }

    void backward_elimination() {
        vector<float> accuracy;
        vector<pair<float, vector<int>>> sets;
        vector<int> set;
        for (int i = 0; i < getSize(); i++) {
            set.push_back(i + 1);
        }
        pair<float, vector<int>> maxAccuracy;
        maxAccuracy.first = -2;
        for (int i = 0; i < this->getSize(); i++) {
            float currAccuracy = -1;
            sets = exploreBackward(set);
            for (auto expanded: sets) {
                // display set with accuracy here
                display(expanded);
                if (expanded.first > currAccuracy) {
                    currAccuracy = expanded.first;
                    set = expanded.second;
                }
            }
            // print local max
            printLocalMax(make_pair(currAccuracy, set));
            if (currAccuracy > maxAccuracy.first) {
                maxAccuracy.first = currAccuracy;
                maxAccuracy.second = set;
            } else {
                cout << "(Warning, Accuracy has decreased!)" << endl << endl;
                break;
            }
        }
        // print globalmax
        printGlobalMax(maxAccuracy);
    }

    void search(int choice, int num) {
        if (choice == 1) {
            cout << "Using no features and \"random\" evaluation, I get an accuracy of " << getRandom() << "%" << endl
                 << endl;
            cout << "Beginning search." << endl << endl;
            forward_selection();
        } else if (choice == 2) {
            cout << "Using ALL features { ";
            for (int i = 0; i < num; i++) {
                cout << i + 1;
                if (i != num - 1) cout << ", ";
            }
            cout << " } and \"random\" evaluation, I get an accuracy of " << getRandom() << "%" << endl << endl;
            cout << "Beginning search." << endl << endl;
            backward_elimination();
        } else if (choice == 3) {
            cout << "To be Implemented!" << endl;
        } else {
            cout << "Error! Not a correct selection from options" << endl;
        }
    }
};

#endif