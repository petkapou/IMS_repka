#ifndef LAND_H
#define LAND_H 42

#include "simlib.h"
#include "parser.h"

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
	bool checkpoint0, checkpoint1;
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
	bool checkpoint;
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class StratosUltra : public TimeoutInterface {
public:
	StratosUltra(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	bool checkpoint;
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class Caryx : public TimeoutInterface {
public:
	Caryx(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	bool checkpoint;
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class Efilor : public TimeoutInterface {
public:
	Efilor(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	bool checkpoint;
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class Pictor : public TimeoutInterface {
public:
	Pictor(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	bool checkpoint;
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class EurofertilTop : public TimeoutInterface {
public:
	EurofertilTop(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	bool checkpointTractor, checkpointSpreader;
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class FertiactylStarter : public TimeoutInterface {
public:
	FertiactylStarter(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	bool checkpointSprayer;
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class FertileaderGold : public TimeoutInterface {
public:
	FertileaderGold(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	bool checkpointSprayer;
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};

class FertileaderVital : public TimeoutInterface {
public:
	FertileaderVital(FertileLand *id);
	void Behavior();
	void TimeoutFunc();
private:
	bool checkpointSprayer;
	FertileLand * parent_m;
	class Timeout * sprayTimeout;
};
#endif