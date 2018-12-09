#ifndef SEASON_H
#define SEASON_H 42

#include "simlib.h"
#include "parser.h"

class SeasonCycle : public Process {
public:
	SeasonCycle() {};
	~SeasonCycle() {};

	void Behavior();
};

class WeekCycle : public Process {
public:
	WeekCycle() {};
	~WeekCycle() {};
	void Behavior();
};

class SeedingCycle : public Process {
public:
	SeedingCycle() {};
	~SeedingCycle() {};

	void Behavior();
};

class HarvestCycle : public Process {
public:
	HarvestCycle() {};
	~HarvestCycle() {};

	void Behavior();
};


#endif