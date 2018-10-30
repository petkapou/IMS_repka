#include "season.h"


void TimeStart::Behavior() {
  m_Queue.Insert(this);
  if (!m_Waiting.Empty())
  {
    for (auto it = m_Waiting.begin(); it != m_Waiting.end(); ++it)
    {
      m_Waiting.Get(it)->Activate();
    }
  }

  Passivate();
}


void TimeEnd::Behavior() {
  if (!m_Queue.Empty())
  {
    for (auto it = m_Queue.begin(); it != m_Queue.end(); ++it)
    {
      m_Queue.Get(it)->Activate();
    }
  }
}


void SeasonManager::Behavior() {
  //TODO
  (new TimeStart(TillageTime_Q, Wait4Tillage_Q))->Activate();   //We can till ground 2 days before seeding
  (new TimeStart(SeedingTime_Q, Wait4Seeding_Q))->Activate(Time + M_DAYS(2));
  (new TimeEnd(TillageTime_Q))->Activate(Time + M_DAYS(5));     //  Stop seeding and
  (new TimeEnd(SeedingTime_Q))->Activate(Time + M_DAYS(5));     //  tillage at same time
  Activate(Time + M_YEARS(1)); //repeat every year
}

void DayCycleManager::Behavior() {
  //TODO
  (new TimeStart(WorkingHours_Q, Wait4Tillage_Q))->Activate();
  (new TimeStart(WorkingHours_Q, Wait4Seeding_Q))->Activate();
  (new TimeEnd(WorkingHours_Q))->Activate(Time + M_HOURS(8));
  Activate(Time + M_DAYS(1));
}