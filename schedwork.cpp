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

bool solve(
    const AvailabilityMatrix& ,
    const size_t ,
    const size_t ,
    DailySchedule& , 
    map<Worker_T, size_t>& ,
    size_t,
    Worker_T 
); 


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    int numDays = avail.size(); 
    for(int i = 0; i < numDays; i++) {
        sched.push_back({}); 
    }
    // workload[i] = number of days ith worker worked 
    map<Worker_T, size_t> workload;
    return solve(avail, dailyNeed, maxShifts, sched, workload, 0, 0); 
}

bool solve(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
    map<Worker_T, size_t>& workload,
    size_t day,
    Worker_T person
)
{
    // on the last day, no person left to select
    if (day == avail.size() - 1 && person == avail[0].size()) {
        // if daily need for last day is met return true, else false  
        if (sched[day].size() == dailyNeed) return true; 
        else return false; 
    }

    // no person left to select 
    if (person == avail[0].size()) {
        // if daily need for day is met start working on the next day, else return false
        if (sched[day].size() == dailyNeed) return solve(avail, dailyNeed, maxShifts, sched, workload, day + 1, 0); 
        else return false; 
    }

    bool ans; 

    // not selecting person 
    ans = solve(avail, dailyNeed, maxShifts, sched, workload, day, person + 1); 

    // if the answer is found, no need to further inspect the search tree
    if (ans) return true; 

    // checking whether person can be selected 
    // person has not worked for more than maxShifts days 
    // person is available to work on day 
    // there is still room for person to work on day
    if (workload[person] < maxShifts && avail[day][person] && sched[day].size() < dailyNeed) {
        // modify workload and sched accordingly 
        workload[person]++; 
        sched[day].push_back(person); 

        // selecting person 
        ans = solve(avail, dailyNeed, maxShifts, sched, workload, day, person + 1); 
        
        // if the answer is found, no need to further inspect the search tree
        if (ans) return true; 

        // undo the changes if they did not lead to a solution 
        workload[person]--; 
        sched[day].pop_back(); 
    }

    // if no solution was found, just return false 
    return false; 
}

