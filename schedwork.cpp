User
act as a software engineer  skilled in C++ and solve this problem for me:
Schedwork
Suppose a company needs to schedule d (which stands for needed) out of k (possible) workers (e.g. nurses at a hospital) per day given their availability over an n day period. The company requires exactly d workers (nurses) per day but does not allow any individual to work more than m (maxShifts) shifts over the n day period. Given d, m, and the k workers’ availability for each of the n days, write a backtracking search function to schedule the nurses, such that exactly d work on each of the n days and no one works more than m shifts.
The prototype for the function you will write is given below, along with some typedefs for the input and output data structures.
// type for the ID of a worker
typedef unsigned int Worker_T;
// n-by-k Matrix of each of the k workers' availability over an n-day period
typedef std::vector<std::vector<bool>> AvailabilityMatrix;
// n-by-d matrix with the d worker IDs who are scheduled 
// to work on each of the n days
typedef std::vector<std::vector<Worker_T> > DailySchedule;

/**
 * @brief Produces a work schedule given worker availability,
 *        the number of needed workers per day, and the maximum 
 *        shifts any single worker is allowed. Returns true if
 *        and the valid schedule if a solution exists, and false
 *        otherwise. 
 * 
 * @param [in]  avail n x k vector of vectors (i.e. matrix) of the availability
 *                    of the k workers for each of the n days
 * @param [in]  dailyNeed Number of workers needed per day (aka d)
 * @param [in]  maxShifts Maximum shifts any worker is allowed over 
 *                        the n day period (aka m)
 * @param [out] sched n x d vector of vectors indicating the d workers
 *                    who are scheduled to work on each of the n days
 * @return true if a solution exists; sched contains the solution
 * @return false if no solution exists; sched is undefined (can be anything)
 */
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
);
Explanation
The avail matrix is an n row by k column matrix of booleans. Each row represents one day of the schedule and each column is one worker’s availability to work on each day.
           W  W  W  W
           o  o  o  o
           r  r  r  r
           k  k  k  k
           e  e  e  e
           r  r  r  r
           0  1  2  3

           |  |  |  |
           |  |  |  |
           V  V  V  V

Day 0 -->  1  1  1  1
Day 1 -->  1  0  1  0
Day 2 -->  1  1  0  1
Day 3 -->  1  0  0  1
So we see in the avail matrix above that every worker is available to work on day 0 while only worker 0 and 2 are available on day 1, and so on.
You should produce a schedule solution that is an n by d matrix, where each row represents a day in the schedule and stores the d IDs of the workers who have been scheduled to work that day (each entry must thus be a value in the range 0 to k-1). So given the availability matrix above and inputs of m=2 and d=2, a valid schedule results would be:
1 2
0 2
1 3
0 3
The above indicates that on day 0 (top row), worker 1 and 2 will be scheduled. Then on day 1 (next row), worker 0 and 2 will be scheduled and so on. You can verify with the availability matrix that all workers are available on their scheduled days and no worker works more than m=2 shifts.
Testing
We have provided a "driver"/test program (schedwork-driver.cpp) where you can alter an availability matrix and values for d (dailyNeed) and m (maxShifts) and then call your algorithm and print the results.
Use schedwork-driver to do some sanity tests of your code before moving on to any of the tests from our grading suite.
Requirements and Assumptions
As always you may not change the signature of the primary function provided.
You MAY define helper functions in schedworker.cpp
You MUST use a recursive approach that follows the general backtracking structure presentedin class. Failure to use such a recursive approach will lead to a 0 on this part of the assignment.
You MAY use functions from the algorithm library such as std::find, if you desire.
The order in which you list the worker IDs in each row of the final schedule doesn’t matter (i.e. if Worker 1, 2, 3 is scheduled to work on a given day, then 3, 2, 1 is also acceptable).
Hints and Approach
Recall that a backtracking search algorithm is a recursive algorithm that is similar to generating all combinations, but skipping the recursion and moving on to another option if the current option violates any of the constraints. It is likely easiest to recurse over each place in the schedule (i.e. the 2D sched matrix). Each recursive call would be responsible for filling in one of the n*d schedule openings, ensuring the constraints of availability and the maximum number of shifts allowed for each worker is met. If you have already done a lab regarding backtracking search, it would likely be beneficial to look it over.

schedwork.cpp:


#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsCount, size_t day);


// Add your implementation of schedule() and other helper functions here

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched) {
    if (avail.empty() || avail[0].empty() || dailyNeed == 0 || maxShifts == 0) {
        return false;
    }

    size_t n = avail.size();     // Number of days
    size_t k = avail[0].size();  // Number of workers

    // Count of shifts assigned to each worker
    vector<size_t> shiftsCount(k, 0);

    // Initialize the schedule
    sched = DailySchedule(n, vector<Worker_T>(dailyNeed, INVALID_ID));

    // Start the recursive backtracking process from day 0
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsCount, 0);
}

bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsCount, size_t day) {
    size_t n = avail.size();
    size_t k = avail[0].size();

    if (day == n) {
        // All days have been scheduled, return true
        return true;
    }

    for (size_t i = 0; i < k; ++i) {
        if (avail[day][i] && shiftsCount[i] < maxShifts) {
            // Worker i is available and has not exceeded max shifts
            sched[day].push_back(i);
            shiftsCount[i]++;

            if (sched[day].size() == dailyNeed) {
                // Day is fully scheduled, move to the next day
                if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsCount, day + 1)) {
                    return true;
                }
            } else {
                // Try to fill the remaining slots of the current day
                if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsCount, day)) {
                    return true;
                }
            }

            // Backtrack: undo the assignment and try the next worker
            sched[day].pop_back();
            shiftsCount[i]--;
        }
    }

    return false;  // No valid schedule found for this path
}
