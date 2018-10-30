#ifndef SEASON_H
#define SEASON_H 42

#include "simlib.h"

#define M_HOURS(val) (val*60)
#define M_DAYS(val) (val*1440)
#define M_YEARS(val) (val*365*1440)

extern Queue WorkingHours_Q;
extern Queue TillageTime_Q;
extern Queue SeedingTime_Q;
extern Queue Wait4Tillage_Q;
extern Queue Wait4Seeding_Q;

class TimeStart : public Process
{
private:
	Queue & m_Queue;
	Queue & m_Waiting;
public:
	TimeStart(Queue & q, Queue & waitq) : m_Queue(q), m_Waiting(waitq) {};
	~TimeStart() {};

	void Behavior();
};

class TimeEnd : public Process
{
private:
	Queue & m_Queue;
public:
	TimeEnd(Queue & q) : m_Queue(q) {};
	~TimeEnd() {};

	void Behavior();
};

class SeasonManager : public Process {
public:
	SeasonManager() {};
	~SeasonManager() {};

	void Behavior();
};

class DayCycleManager : public Event {
public:
	DayCycleManager() {};
	~DayCycleManager() {};
	void Behavior();
};

#endif