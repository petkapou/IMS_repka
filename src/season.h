#ifndef SEASON_H
#define SEASON_H 42

#include "simlib.h"
#include "parser.h"

extern ConfData config;
extern Facility workingHours_F;

extern Facility butisanCompleteTime_F;
extern Facility stratosUltraTime_F;
extern Facility caryxTime_F;
extern Facility pictorTime_F;
extern Facility efilorTime_F;

extern Facility seedingTime_F;
extern Facility harvestTime_F;
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

class ButisanCompleteCycle : public Process {
public:
	ButisanCompleteCycle() {};
	~ButisanCompleteCycle() {};

	void Behavior();
};

class StratosUltraCycle : public Process {
public:
	StratosUltraCycle() {};
	~StratosUltraCycle() {};

	void Behavior();
};

class CaryxCycle : public Process {
public:
	CaryxCycle() {};
	~CaryxCycle() {};

	void Behavior();
};

class EfilorCycle : public Process {
public:
	EfilorCycle() {};
	~EfilorCycle() {};

	void Behavior();
};

class PictorCycle : public Process {
public:
	PictorCycle() {};
	~PictorCycle() {};

	void Behavior();
};

#endif