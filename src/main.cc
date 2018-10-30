////////////////////////////////////////////////////////////////////////////
// Model Repka_kelemen_kapoun_2018                SIMLIB/C++
//
// Simple model of TODO
//

#include "simlib.h"
#include "season.h"

#define FERTILE_LAND 50
#define WORKING_HOURS M_HOURS(8)
#define TRACTOR_SPEED (Exponential(M_HOURS(1)))

// Global objects
Queue WorkingHours_Q("Working Time");
Queue TillageTime_Q("Tillage Time");
Queue SeedingTime_Q("Seeding Time");
Queue Wait4Tillage_Q("Tillage Queue");
Queue Wait4Seeding_Q("Seeding Queue");
Store Tractors("Tractors", 3);

class Plant1stStage : public Process {
public:
  void Behavior() {
    Print(" Plant! \n");
  }
};

class TilledLand : public Process {
public:
  void Behavior() {
    while (42)
    {
      if (!SeedingTime_Q.Empty() && !Tractors.Full() && !WorkingHours_Q.Empty())
      {
        Enter(Tractors, 1);
        Wait(TRACTOR_SPEED);
        Leave(Tractors, 1);
        if (!SeedingTime_Q.Empty()) //Everything correct
        {
          //(new TilledLand)->Activate(); //Go to next stage
          if (!Wait4Seeding_Q.Empty())
            Wait4Seeding_Q.GetFirst()->Activate();

          Wait(Exponential(M_DAYS(13)));
          if (Random() <= 0.01 )
            (new TilledLand)->Activate();  //Nothing growed from seeds
          else
            (new Plant1stStage)->Activate(); //Go to next stage
        }
        else    //did not make it in time
        {
          (new TilledLand)->Activate();
        }

        this->Cancel();
      }
      else
      {
        Wait4Seeding_Q.Insert(this);
        this->Passivate();
      }
    }
  }
};

class FertileLand : public Process {
public:
  void Behavior() {
    while (42)
    {
      if (!TillageTime_Q.Empty() && !Tractors.Full() && !WorkingHours_Q.Empty())
      {
        Enter(Tractors, 1);
        Wait(TRACTOR_SPEED);
        Leave(Tractors, 1);
        if (!TillageTime_Q.Empty()) //Everything correct
        {
          (new TilledLand)->Activate(); //Go to next stage
          if (!Wait4Tillage_Q.Empty())
            Wait4Tillage_Q.GetFirst()->Activate();
        }
        else    //did not make it in time
        {
          (new FertileLand)->Activate();
        }

        this->Cancel();
      }
      else
      {
        Wait4Tillage_Q.Insert(this);
        this->Passivate();
      }
    }
  }
};

class Generator : public Event {  // Generator of customers
  void Behavior() {               // - Generator behavior description
    for (int i = 0; i < FERTILE_LAND; ++i)
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
