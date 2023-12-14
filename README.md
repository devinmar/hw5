4. Wordle Assistant
Problem 4. Wordle 

Overview
This program assists players of a Wordle-like game. It generates potential guesses based on partial information from previous attempts. It uses a combination of fixed (green) and floating (yellow) letters to filter English words that meet specific criteria.

Functionality
Input:
Length of the word.
Fixed letters (green) in their correct positions.
Floating letters (yellow) that must appear somewhere in the word.
Output:
All possible English words matching the criteria.
Implementation
Function Signature:
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict);

Constraints:
Recursive approach for generating word combinations.
Up to 5 loops allowed in total implementation.
A provided std::set<std::string> dictionary is used for word validation.
Usage
Example:
./wordle-driver -i-- dn


Problem 6. Schedwork

Overview
This program schedules a specific number of workers (e.g., nurses) per day, considering their availability and maximum shift constraints.

Functionality
Input:
Workers' availability over an n-day period.
Daily worker requirement (d).
Maximum shifts per worker (m).
Output:
Daily work schedule, ensuring no worker exceeds their maximum shifts.
Implementation
Function Signature:
bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched);

Constraints:
Recursive backtracking search algorithm.
Maximum shift limit enforcement.
Usage of algorithm library functions is allowed.
Usage
Example:
Alter AvailabilityMatrix and dailyNeed, maxShifts in schedwork-driver.cpp.
Run the driver program to generate the schedule.
Testing
Both programs come with driver/test programs for initial testing. Additional tests may be conducted post-submission. Ensure adherence to the specified function signatures and constraints.