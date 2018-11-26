#include "season.h"


void SeasonCycle::Behavior() {
  (new SeedingCycle)->Activate();
  (new HarvestCycle)->Activate();
  (new ButisanCompleteCycle)->Activate();
  (new StratosUltraCycle)->Activate();
  (new CaryxCycle)->Activate();
  (new PictorCycle)->Activate();
  (new EfilorCycle)->Activate();
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

void ButisanCompleteCycle::Behavior() {
  butisanCompleteTime_F.Seize(this, 1);
  while (42){
    Wait(BUTISAN_COMPLETE_TIME_START);
    butisanCompleteTime_F.Release(this);
    Wait(BUTISAN_COMPLETE_DURATION);
    butisanCompleteTime_F.Seize(this, 1);
    double restTime = M_YEARS(1) - BUTISAN_COMPLETE_TIME_START - BUTISAN_COMPLETE_DURATION;
    Wait(restTime);
  }
}

void StratosUltraCycle::Behavior() {
  stratosUltraTime_F.Seize(this, 1);
  while (42){
    Wait(STRATOS_ULTRA_TIME_START);
    stratosUltraTime_F.Release(this);
    Wait(STRATOS_ULTRA_DURATION);
    stratosUltraTime_F.Seize(this, 1);
    double restTime = M_YEARS(1) - STRATOS_ULTRA_TIME_START - STRATOS_ULTRA_DURATION;
    Wait(restTime);
  }
}

void CaryxCycle::Behavior() {
  caryxTime_F.Seize(this, 1);
  while (42){
    Wait(CARYX_TIME_START);
    caryxTime_F.Release(this);
    Wait(CARYX_DURATION);
    caryxTime_F.Seize(this, 1);
    double restTime = M_YEARS(1) - CARYX_TIME_START - CARYX_DURATION;
    Wait(restTime);
  }
}

void PictorCycle::Behavior() {
  pictorTime_F.Seize(this, 1);
  while (42){
    Wait(PICTOR_TIME_START);
    pictorTime_F.Release(this);
    Wait(PICTOR_DURATION);
    pictorTime_F.Seize(this, 1);
    double restTime = M_YEARS(1) - PICTOR_TIME_START - PICTOR_DURATION;
    Wait(restTime);
  }
}

void EfilorCycle::Behavior() {
  efilorTime_F.Seize(this, 1);
  while (42){
    Wait(EFILOR_TIME_START);
    efilorTime_F.Release(this);
    Wait(EFILOR_DURATION);
    efilorTime_F.Seize(this, 1);
    double restTime = M_YEARS(1) - EFILOR_TIME_START - EFILOR_DURATION;
    Wait(restTime);
  }
}
