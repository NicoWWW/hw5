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
bool scheduleHelper(DailySchedule& sched, const AvailabilityMatrix& avail, const size_t maxShifts, const size_t dailyNeed);
bool overworkCheck(unsigned int& worker, DailySchedule& sched, const size_t maxShifts); 
Worker_T workerHelper(int& today, DailySchedule& sched); //function to select which worker to attempt to schedule


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

    sched.emplace_back();

    return scheduleHelper(sched, avail, maxShifts, dailyNeed);
}

bool scheduleHelper(DailySchedule& sched, const AvailabilityMatrix& avail, const size_t maxShifts, const size_t dailyNeed){
    unsigned int daysToSchedule = avail.size();
    unsigned int scheduledDays = sched.size();

    if(scheduledDays > daysToSchedule){
        sched.pop_back();
        return true;
    }

    int today = sched.size()-1;

    Worker_T currWorker = workerHelper(today, sched);

    while(currWorker<avail[today].size()){ 
			if(avail[today][currWorker] == 0 || overworkCheck(currWorker, sched, maxShifts) == true){ 
					currWorker++;
					continue;
			}

			sched[today].push_back(currWorker); 

			if(sched[today].size()==dailyNeed){
					sched.emplace_back();

					if(scheduleHelper(sched, avail, maxShifts, dailyNeed)==true){
							return true;
					}
					else{
							sched.pop_back();
					}
			}
			else if(scheduleHelper(sched, avail, maxShifts, dailyNeed)==true){
					return true;
			}
			sched[today].pop_back();
			currWorker++;
    }
    return false; 
}

bool overworkCheck(unsigned int& worker, DailySchedule& sched, const size_t maxShifts){
    int count = 0;
    for(unsigned int i=0; i<sched.size(); i++){
        for(unsigned int j=0; j<sched[i].size(); j++){
            if(sched[i][j]==worker){
                count++;
            }
        }
    }
    return count >= (int)maxShifts;
}

Worker_T workerHelper(int& today, DailySchedule& sched){
    if(sched[today].size()==0){
        return 0;
    }
    return sched[sched.size()-1].back()+1;
}