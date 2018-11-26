#ifndef LAND_H
#define LAND_H 42

#include "simlib.h"
#include "parser.h"

extern Store seedingMachines_S;
extern Store sprayers_S;
extern Store harvestMachines_S;

extern Stat usedLandStat;
extern Stat butisanCompleteStat;
extern Stat stratosUltraStat;
extern Stat caryxStat;
extern Stat pictorStat;
extern Stat efilorStat;
extern Stat harvestedLandStat;
extern Stat profitStat;

/*class WeedTimeoutInterface : public Event {
	Process *Id;
public:
	WeedTimeoutInterface(Process *id, double dt);
	void Behavior();
};*/

class TimeoutInterface : public Process {
public:
	TimeoutInterface();
	void Behavior();
	virtual void TimeoutFunc();
};

class Timeout : public Process {
public:
	Timeout(TimeoutInterface * id, double timeout);
	void Behavior();

private:
	TimeoutInterface * id_m;
};

class FertileLand : public TimeoutInterface {
public:
	FertileLand();
	void Behavior();
	void MultProfit(double val);
	void TimeoutFunc();
private:
	double profit;
	class Timeout * seedingTimeout;
};

class FinalStage : public TimeoutInterface {
public:
	FinalStage(double profit);
	void Behavior();
	void TimeoutFunc();
private:
	double profit_m;
	class Timeout * harvestTimeout;
};



class ButisanComplete : public TimeoutInterface {
public:
	ButisanComplete(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class StratosUltra : public TimeoutInterface {
public:
	StratosUltra(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class Caryx : public TimeoutInterface {
public:
	Caryx(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class Efilor : public TimeoutInterface {
public:
	Efilor(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class Pictor : public TimeoutInterface {
public:
	Pictor(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};
#endif