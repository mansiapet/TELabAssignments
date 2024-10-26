//============================================================================
// Name        : B3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

void printAllocation(const vector<int>& ProcessTime, const vector<int>& AllowedTime) {
    cout << "\nProcess No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < ProcessTime.size(); i++) {
        cout << " " << i + 1 << "\t\t" << ProcessTime[i] << "\t\t";
        if (AllowedTime[i] != -1)
            cout << AllowedTime[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

void FirstFit(vector<int> BlockTime, const vector<int>& ProcessTime) {
    vector<int> AllowedTime(ProcessTime.size(), -1);
    int m = BlockTime.size();
    for (int i = 0; i < ProcessTime.size(); i++) {
        for (int j = 0; j < m; j++) {
            if (BlockTime[j] >= ProcessTime[i]) {
                AllowedTime[i] = j;
                BlockTime[j] -= ProcessTime[i];
                break;
            }
        }
    }
    printAllocation(ProcessTime, AllowedTime);
}

void BestFit(vector<int> BlockTime, const vector<int>& ProcessTime) {
    vector<int> AllowedTime(ProcessTime.size(), -1);
    int m = BlockTime.size();
    for (int i = 0; i < ProcessTime.size(); i++) {
        int bestIdx = -1;
        int minSize = numeric_limits<int>::max();
        for (int j = 0; j < m; j++) {
            if (BlockTime[j] >= ProcessTime[i] && BlockTime[j] < minSize) {
                minSize = BlockTime[j];
                bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            AllowedTime[i] = bestIdx;
            BlockTime[bestIdx] -= ProcessTime[i];
        }
    }
    printAllocation(ProcessTime, AllowedTime);
}

void WorstFit(vector<int> BlockTime, const vector<int>& ProcessTime) {
    vector<int> AllowedTime(ProcessTime.size(), -1);
    int m = BlockTime.size();
    for (int i = 0; i < ProcessTime.size(); i++) {
        int worstIdx = -1;
        int maxSize = numeric_limits<int>::min();
        for (int j = 0; j < m; j++) {
            if (BlockTime[j] >= ProcessTime[i] && BlockTime[j] > maxSize) {
                maxSize = BlockTime[j];
                worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            AllowedTime[i] = worstIdx;
            BlockTime[worstIdx] -= ProcessTime[i];
        }
    }
    printAllocation(ProcessTime, AllowedTime);
}

void NextFit(vector<int> BlockTime, const vector<int>& ProcessTime) {
    vector<int> AllowedTime(ProcessTime.size(), -1);
    int m = BlockTime.size();
    int j = 0;
    for (int i = 0; i < ProcessTime.size(); i++) {
        while (true) {
            if (BlockTime[j] >= ProcessTime[i]) {
                AllowedTime[i] = j;
                BlockTime[j] -= ProcessTime[i];
                break;
            }
            j = (j + 1) % m;
            if (j == 0) break;
        }
    }
    printAllocation(ProcessTime, AllowedTime);
}

int main() {
    int numBlocks, numProcesses;

    cout << "Enter the number of memory blocks: ";
    cin >> numBlocks;
    vector<int> BlockTime(numBlocks);
    cout << "Enter the sizes of the memory blocks: ";
    for (int i = 0; i < numBlocks; i++) {
        cin >> BlockTime[i];
    }

    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    vector<int> ProcessTime(numProcesses);
    cout << "Enter the sizes of the processes: ";
    for (int i = 0; i < numProcesses; i++) {
        cin >> ProcessTime[i];
    }

    int choice;

    do {
        cout << "\nMemory Placement Algorithm:\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Next Fit\n";
        cout << "4. Worst Fit\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                FirstFit(BlockTime, ProcessTime);
                break;
            case 2:
                BestFit(BlockTime, ProcessTime);
                break;
            case 3:
                NextFit(BlockTime, ProcessTime);
                break;
            case 4:
                WorstFit(BlockTime, ProcessTime);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter again.\n";
        }
    } while (choice != 0);

    return 0;
}
