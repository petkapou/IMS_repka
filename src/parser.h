/*
 *		IMS project 2018 repka
 *
 *	author: Erik Kelemen(xkelem01)
 *	author: Petr Kapoun(xkoapou04)
 *	
 */

#ifndef H_PARSER
#define H_PARSER 42

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <functional>

#define CONFIG_FILE "settings.conf"

#define M_MINUTES(val) (val)
#define M_HOURS(val) (val*60.)
#define M_DAYS(val) (val*1440.)
#define M_YEARS(val) (val*365.*1440.)

#define DEF_WORKINGHOURSTIME M_HOURS(8)
#define DEF_WORKINGDAYSCOUNT 5
#define DEF_MORNINGTIME M_HOURS(8)
#define DEF_AVERAGEPROFIT 2.5
#define DEF_SEEDINGMACHINECOUNT 3
#define DEF_TRACTORCOUNT 3
#define DEF_SPRAYERCOUNT 1
#define DEF_FERTILIZERSPREADERCOUNT 1
#define DEF_HARVESTMACHINECOUNT 3
#define DEF_FERTILELANDCOUNT 1000
#define DEF_SEEDINGTIMESTART M_DAYS(0)
#define DEF_SEEDINGDURATION M_DAYS(5)
#define DEF_HARVESTTIMESTART M_DAYS(69)
#define DEF_HARVESTDURATION M_DAYS(5)
#define WEEK_DAY_COUNT 7

//SPRAYS

#define BUTISAN_COMPLETE_TIME_START M_DAYS(0)	//Butisan Complete
#define BUTISAN_COMPLETE_DURATION M_DAYS(11)

#define STRATOS_ULTRA_TIME_START M_DAYS(11)	//Stratos Ultra
#define STRATOS_ULTRA_DURATION M_DAYS(40)

#define CARYX_TIME_START M_DAYS(13)	//Caryx
#define CARYX_DURATION M_DAYS(6)

#define EFILOR_TIME_START M_DAYS(32)	//Efilor
#define EFILOR_DURATION M_DAYS(25)

#define PICTOR_TIME_START M_DAYS(57)	//Pictor
#define PICTOR_DURATION M_DAYS(12)

#define VAZTAK_ACTIVE_TIME_START M_DAYS(32)		//Vaztak Active
#define VAZTAK_ACTIVE_DURATION M_DAYS(11)

//FERTILIZERS

#define EUROFERTIL_TOP_TIME_START M_DAYS(0)		//Eurofertyl Top
#define EUROFERTIL_TOP_DURATION M_DAYS(9)

#define FERTIACTYL_STARTER_TIME_START M_DAYS(13)		//Fertiactyl Starter
#define FERTIACTYL_STARTER_DURATION M_DAYS(14)

#define FERTILEADER_GOLD_TIME_START M_DAYS(15)		//Fertileader Gold
#define FERTILEADER_GOLD_DURATION M_DAYS(14)

#define FERTILEADER_VITAL_TIME_START M_DAYS(32)		//Fertileader Vital
#define FERTILEADER_VITAL_DURATION M_DAYS(14)




class ConfData
{
public:
	ConfData();
	~ConfData();

	void SetWorkingDaysCount(double workingDaysCount);
	double GetWorkingDaysCount();

	void SetWorkingHoursTime(double workingHoursTime);
	double GetWorkingHoursTime();

	void SetMorningTime(double morningTime);
	double GetMorningTime();

	void SetAverageProfit(double averageProfit);
	double GetAverageProfit();

	void SetTractorCount(double tractorCount);
	int GetTractorCount();

	void SetSeedingMachineCount(double seedingMachineCount);
	int GetSeedingMachineCount();

	void SetSprayerCount(double sprayerCount);
	int GetSprayerCount();

	void SetFertilizerSpreaderCount(double fertilizerSpreaderCount);
	int GetFertilizerSpreaderCount();

	void SetHarvestMachineCount(double harvestMachineCount);
	int GetHarvestMachineCount();

	void SetFertileLandCount(double fertileLandCount);
	int GetFertileLandCount();

	void SetSeedingTimeStart(double seedingTimeStart);
	double GetSeedingTimeStart();

	void SetSeedingDuration(double seedingDuration);
	double GetSeedingDuration();

	void SetHarvestTimeStart(double harvestTimeStart);
	double GetHarvestTimeStart();

	void SetHarvestDuration(double harvestDuration);
	double GetHarvestDuration();

private:
	double workingHoursTime_m;
	double workingDaysCount_m;
	double morningTime_m;
	double averageProfit_m;
	int tractorCount_m;
	int seedingMachineCount_m;
	int sprayerCount_m;
	int fertilizerSpreaderCount_m;
	int harvestMachineCount_m;
	int fertileLandCount_m;
	double seedingTimeStart_m;
	double seedingDuration_m;
	double harvestTimeStart_m;
	double harvestDuration_m;
};

class Parser
{
public:
	Parser(std::string filePath, ConfData * confData);
	~Parser();

private:
	uint32_t TokenToNumb(std::string token);
	void Semantics(std::string token1, std::string token2);
	std::ifstream confFile;
	ConfData * confData_m;
	std::map<std::string, std::function<void (int)>> semantics;
};
#endif