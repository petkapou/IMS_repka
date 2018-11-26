#include "parser.h"

ConfData::ConfData() : workingHoursTime_m(DEF_WORKINGHOURSTIME), workingDaysCount_m(DEF_WORKINGDAYSCOUNT), morningTime_m(DEF_MORNINGTIME),
					seedingMachineCount_m(DEF_SEEDINGMACHINECOUNT), sprayerCount_m(DEF_SPRAYERCOUNT), harvestMachineCount_m(DEF_HARVESTMACHINECOUNT),
					fertileLandCount_m(DEF_FERTILELANDCOUNT),
					seedingTimeStart_m(DEF_SEEDINGTIMESTART), seedingDuration_m(DEF_SEEDINGDURATION),
					harvestTimeStart_m(DEF_HARVESTTIMESTART), harvestDuration_m(DEF_HARVESTDURATION){

}

ConfData::~ConfData(){
	
}

void ConfData::SetWorkingDaysCount(double workingDaysCount){
	if (workingDaysCount <= WEEK_DAY_COUNT)
		workingDaysCount_m = workingDaysCount;
}

double ConfData::GetWorkingDaysCount(){
	return workingDaysCount_m;
}

void ConfData::SetWorkingHoursTime(double workingHoursTime){
	if (((workingHoursTime + morningTime_m) < M_DAYS(1)) && (workingHoursTime >= M_HOURS(1)))	// Work at least 1 hour and maximum whole day
		workingHoursTime_m = workingHoursTime;
}

double ConfData::GetWorkingHoursTime(){
	return workingHoursTime_m;
}

void ConfData::SetMorningTime(double morningTime){
	if ((morningTime + workingHoursTime_m) < M_DAYS(1))
		morningTime_m = morningTime;
	else
		std::cerr << "Conf file: Morning Time out of range" << std::endl;
}

double ConfData::GetMorningTime(){
	return morningTime_m;
}

void ConfData::SetSeedingMachineCount(double seedingMachineCount){
	if (seedingMachineCount > 0)
		seedingMachineCount_m = seedingMachineCount;
}

int ConfData::GetSeedingMachineCount(){
	return seedingMachineCount_m;
}

void ConfData::SetSprayerCount(double sprayerCount){
	if (sprayerCount > 0)
		sprayerCount_m = sprayerCount;
}

int ConfData::GetSprayerCount(){
	return sprayerCount_m;
}

void ConfData::SetHarvestMachineCount(double harvestMachineCount){
	if (harvestMachineCount > 0)
		harvestMachineCount_m = harvestMachineCount;
}

int ConfData::GetHarvestMachineCount(){
	return harvestMachineCount_m;
}

void ConfData::SetFertileLandCount(double fertileLandCount){
	if (fertileLandCount > 0)
		fertileLandCount_m = fertileLandCount;
}

int ConfData::GetFertileLandCount(){
	return fertileLandCount_m;
}

void ConfData::SetSeedingTimeStart(double seedingTimeStart){
	if (seedingTimeStart < M_YEARS(1))
		seedingTimeStart_m = seedingTimeStart;
}
double ConfData::GetSeedingTimeStart(){
	return seedingTimeStart_m;
}

void ConfData::SetSeedingDuration(double seedingDuration){
	if (seedingDuration < M_YEARS(1))
		seedingDuration_m = seedingDuration;
}
double ConfData::GetSeedingDuration(){
	return seedingDuration_m;
}

void ConfData::SetHarvestTimeStart(double harvestTimeStart){
	if ((harvestTimeStart > 0) && ((harvestDuration_m + harvestTimeStart) < M_YEARS(1)))
		harvestTimeStart_m = harvestTimeStart;
}
double ConfData::GetHarvestTimeStart(){
	return harvestTimeStart_m;
}

void ConfData::SetHarvestDuration(double harvestDuration){
	if ((harvestDuration > 0) && (harvestDuration < M_YEARS(1)))
		harvestDuration_m = harvestDuration;
}
double ConfData::GetHarvestDuration(){
	return harvestDuration_m;
}

Parser::Parser(std::string filePath, ConfData * confData) : confFile(std::ifstream(filePath)), confData_m(confData){
	semantics["WORKINGHOURSTIME"] = std::bind(&ConfData::SetWorkingHoursTime, confData_m, std::placeholders::_1);
	semantics["WORKINGDAYSCOUNT"] = std::bind(&ConfData::SetWorkingDaysCount, confData_m, std::placeholders::_1);
	semantics["MORNINGTIME"] = std::bind(&ConfData::SetMorningTime, confData_m, std::placeholders::_1);
	semantics["SEEDINGMACHINECOUNT"] = std::bind(&ConfData::SetSeedingMachineCount, confData_m, std::placeholders::_1);
	semantics["SPRAYERCOUNT"] = std::bind(&ConfData::SetSprayerCount, confData_m, std::placeholders::_1);
	semantics["HARVESTMACHINECOUNT"] = std::bind(&ConfData::SetHarvestMachineCount, confData_m, std::placeholders::_1);
	semantics["FERTILELANDCOUNT"] = std::bind(&ConfData::SetFertileLandCount, confData_m, std::placeholders::_1);
	semantics["SEEDINGDURATION"] = std::bind(&ConfData::SetSeedingDuration, confData_m, std::placeholders::_1);
	semantics["HARVESTDURATION"] = std::bind(&ConfData::SetHarvestDuration, confData_m, std::placeholders::_1);


	if (confFile)
	{
		std::string line;
		while (getline(confFile,line)){
			std::string delimiter = "//";
			std::string final = line.substr(0, line.find(delimiter));
			delimiter = "=";
			std::size_t found = final.find(delimiter);
			if (found!=std::string::npos){
				final.erase(remove_if(final.begin(), final.end(), isspace), final.end());
				std::transform(final.begin(), final.end(), final.begin(), [](char c){ return std::toupper(c); });
				std::string part0 = final.substr(0, final.find(delimiter));
				std::string part1 = final.substr(final.find(delimiter) + 1);
				try{
					int number = std::stod(part1);
					if (semantics.find(part0) != semantics.end()){
						semantics[part0](number);
					}
					else
						std::cerr << "unknown option ignored : " << part0 << std::endl;
				}
				catch(std::invalid_argument e){
					std::cerr << "invalid argument in conf file" << std::endl;
				}

				//std::cout << part0 << ':' << number << std::endl;
			}
		}
	}
}

Parser::~Parser(){
	if (confFile.is_open()){
		confFile.close();
	}
}