#include "season.h"

extern ConfData config;
extern Facility workingHours_F;

extern Facility seedingTime_F;
extern Facility harvestTime_F;

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
      workingHours_F.Release(this);
      Wait(config.GetWorkingHoursTime());
      workingHours_F.Seize(this, 1);
      double rest = M_DAYS(1) - config.GetMorningTime() - config.GetWorkingHoursTime();
      Wait(rest);
    }
    double restDays = WEEK_DAY_COUNT - config.GetWorkingDaysCount();
    Wait(M_DAYS(restDays));
  }
}

void SeedingCycle::Behavior() {
  seedingTime_F.Seize(this);
  while (42){
    Wait(config.GetSeedingTimeStart());
    seedingTime_F.Release(this);
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
    harvestTime_F.Release(this);
    Wait(config.GetHarvestDuration());
    harvestTime_F.Seize(this);
    double restTime = M_YEARS(1) - config.GetHarvestTimeStart() - config.GetHarvestDuration();
    Wait(restTime);
  }
}
