#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftsWorked,
    size_t day,
    size_t slot
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

    size_t n = avail.size();
    size_t k = avail[0].size();

    sched.clear();
    for(size_t i =0; i<n; ++i){
        vector<Worker_T> daySchedule;
        for(size_t j =0; j < dailyNeed; ++j){
            daySchedule.push_back(INVALID_ID);
        }
        sched.push_back(daySchedule);
    }

    vector<size_t> shiftsWorked(k, 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, 0, 0);

}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftsWorked,
    size_t day,
    size_t slot)
{
    if(day == sched.size()){
        return true;
    }

    if(slot == dailyNeed){
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, day + 1, 0);
    }

    for(size_t worker = 0; worker < avail[0].size(); ++worker){
        if(avail[day][worker] && shiftsWorked[worker] < maxShifts &&
            find(sched[day].begin(), sched[day].end(), worker) == sched[day].end())
        {
        
            sched[day][slot] = worker;
            shiftsWorked[worker]++;

            if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, day, slot + 1)){
                return true; 
            }

            sched[day][slot] = INVALID_ID;
            shiftsWorked[worker]--;
        }
    }
    return false;
}