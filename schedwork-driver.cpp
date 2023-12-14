// main() program to test your schedule function.
// Feel free to modify this program in any way you need for testing.
// It will not be graded. 
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "schedwork.h"

using namespace std;

void printSchedule(const DailySchedule& sched);

int main() {
    AvailabilityMatrix avail = {
        {true, true, true, true},
        {true, false, true, false},
        {true, true, false, true},
        {true, false, false, true}
    };

    DailySchedule sched;
    bool solutionFound = schedule(avail, 2, 2, sched);

    if (solutionFound) {
        for (size_t i = 0; i < sched.size(); ++i) {
            cout << "Day " << i << ": ";
            for (size_t j = 0; j < sched[i].size(); ++j) {
                cout << sched[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution found!" << endl;
    }

    return 0;
}