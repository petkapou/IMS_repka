////////////////////////////////////////////////////////////////////////////
// Model Repka_kelemen_kapoun_2018                SIMLIB/C++
//
// Simple model of TODO
//

#include "simlib.h"

#define M_HOURS(val) (val*60)
#define M_DAYS(val) (val*1440)
#define M_YEARS(val) (val*365*1440)

// Global objects
Queue TillageStart_Q("Tillage Start");
Queue TillageEnd_Q("Tillage End");
Store Tractors("Tractors", 3);

class FertileLand : public Process{
public:
  void Behavior() {
    //TODO
    if (!TillageStart_Q.Empty())
    {
      Enter(Tractors, 1);
      Wait(Exponential(3));
      Leave(Tractors, 1);
    }
  }
};

class TilledLand : public Process{
public:
  void Behavior() {
    //TODO
  }
};

class TillageTimeStart : public Process{
public:
  void Behavior() {
    if (TillageEnd_Q.Empty())
    {
      TillageStart_Q.Insert(this);
      Passivate();
    }
    else
    {
      TillageEnd_Q.GetFirst()->Activate();
    }
  }
};

class TillageTimeEnd : public Process{
public:
  void Behavior() {
    //TODO
    if (TillageStart_Q.Empty())
    {
      TillageEnd_Q.Insert(this);
      Passivate();
    }
    else
    {
      TillageStart_Q.GetFirst()->Activate();
    }
  }
};

class SeasonManager : public Event{
public:
  void Behavior() {
    //TODO
    Activate(Time+M_YEARS(1));  //repeat every year
    (new TillageTimeStart)->Activate();
  }
};

class DayCycleManager : public Event{
public:
  void Behavior() {
    //TODO
    Activate(Time+M_DAYS(1));
  }
};

class Generator : public Event {  // Generator of customers
  void Behavior() {               // - Generator behavior description
    for (int i = 0; i < 2000; ++i)
      (new FertileLand)->Activate();

    (new SeasonManager)->Activate();
    (new DayCycleManager)->Activate();
  }
};

int main() {                    // Experiment description
  //DebugON();
  //SetOutput("model.out");      // Write results to file
  Print(" REPKA \n");
  Init(0, M_YEARS(1));                 // Init simulator for time 0..1000
  (new Generator)->Activate();  // Create generator, activate at 0
  Run();                        // - Simulation run
  SIMLIB_statistics.Output();   // Print simulator internal statistics
}
