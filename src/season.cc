/*
 *    IMS project 2018 repka
 *
 *  author: Erik Kelemen(xkelem01)
 *  author: Petr Kapoun(xkoapou04)
 *  
 */

#include "season.h"

extern ConfData config;
extern Facility workingHours_F;

extern Facility seedingTime_F;
extern Facility harvestTime_F;


void SeasonCycle::Behavior() {
  (new SeedingCycle)->Activate();
  (new HarvestCycle)->Activate();
}

void WeekCycle::Behavior() {

  workingHours_F.Seize(this, 1);
  while (42)
  {
    for (int i = 0; i < config.GetWorkingDaysCount(); ++i)
    {
      Wait(config.GetMorningTime());
      workingHours_F.Release(this);       //let them work from now on
      Wait(config.GetWorkingHoursTime());
      workingHours_F.Seize(this, 1);      //stop working
      double rest = M_DAYS(1) - config.GetMorningTime() - config.GetWorkingHoursTime();
      Wait(rest);
    }
    double restDays = WEEK_DAY_COUNT - config.GetWorkingDaysCount();
    Wait(M_DAYS(restDays));     //Wait till end of the week
  }
}

void SeedingCycle::Behavior() {
  seedingTime_F.Seize(this);
  while (42){
    Wait(config.GetSeedingTimeStart());
    seedingTime_F.Release(this);      //let them seed from now on
    Wait(config.GetSeedingDuration());
    seedingTime_F.Seize(this);
    double restTime = M_YEARS(1) - config.GetSeedingTimeStart() - config.GetSeedingDuration();
    Wait(restTime);
  }
}

void HarvestCycle::Behavior() {
  harvestTime_F.Seize(this);
  while (42){
    Wait(config.GetHarvestTimeStart());
    harvestTime_F.Release(this);      //let them harvest from now on
    Wait(config.GetHarvestDuration());
    harvestTime_F.Seize(this);
    double restTime = M_YEARS(1) - config.GetHarvestTimeStart() - config.GetHarvestDuration();
    Wait(restTime);
  }
}
