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
	std::vector<size_t>& shiftsScheduled,
	size_t day,
	size_t slot);

bool isValid(
	const AvailabilityMatrix& avail,
	const size_t maxShifts,
	const DailySchedule& sched,
	const std::vector<size_t>& shiftsScheduled,
	size_t day,
	size_t slot,
	Worker_T worker
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

		sched.resize(n, std::vector<Worker_T>(dailyNeed, INVALID_ID));

		std::vector<size_t> shiftsScheduled(k, 0);

		return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsScheduled, 0, 0);
}

bool scheduleHelper(
	const AvailabilityMatrix& avail,
	const size_t dailyNeed,
	const size_t maxShifts,
	DailySchedule& sched,
	std::vector<size_t>& shiftsScheduled,
	size_t day,
	size_t slot)
	{
		size_t numDays = avail.size();
		size_t numWorkers = avail[0].size();

		if(day >= numDays){
			return true;
		}

		if(slot >= dailyNeed){
			return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsScheduled, day + 1, 0);
		}

		for(Worker_T worker = 0; worker < numWorkers; worker++){
			bool valid = true;
			if(!avail[day][worker]) continue;
			if(shiftsScheduled[worker] >= maxShifts) continue;

			for(size_t s = 0; s < slot; s++){
				if(sched[day][s] == worker){
					valid = false;
				}
			}
			if(!valid) continue;


				sched[day][slot] = worker;
				shiftsScheduled[worker]++;

				if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsScheduled, day, slot + 1)) {
					return true;
				}

				sched[day][slot] = INVALID_ID;
				shiftsScheduled[worker]--;
		}
		return false;
	}

