////////////////////////////////////////////////////////////////////////////
// Model Repka_kelemen_kapoun_2018                SIMLIB/C++
//
// Simple model of TODO
//


#include "simlib.h"
#include "parser.h"
#include "season.h"
#include "land.h"

#include <ctime>

ConfData config;
// Global objects
Facility workingHours_F("Working Hours");
Facility seedingTime_F("Seeding Time");
Facility harvestTime_F("Harvest Time");
Facility butisanCompleteTime_F("Time for Butisan Complete");
Facility stratosUltraTime_F("Time for Stratos Ultra");
Facility caryxTime_F("Time for Caryx");
Facility pictorTime_F("Time for Pictor");
Facility efilorTime_F("Time for Efilor");

Stat usedLandStat("Used land");
Stat butisanCompleteStat("Applied spray Butisan Complete");
Stat stratosUltraStat("Applied spray Stratos Ultra");
Stat caryxStat("Applied spray Caryx");
Stat pictorStat("Applied spray Pictor");
Stat efilorStat("Applied spray Efilor");
Stat harvestedLandStat("Harvested land");
Stat profitStat("Profit in liters");



Store seedingMachines_S("Seeding Mechines", 0);
Store sprayers_S("Sprayers", 0);
Store harvestMachines_S("Harvest Machines", 0);

class Generator : public Event {
  void Behavior() {
    for (int i = 0; i < config.GetFertileLandCount(); ++i)
      (new FertileLand)->Activate();

    (new WeekCycle)->Activate();
    (new SeasonCycle)->Activate();
  }
};

int main() {
  //DebugON();
  //SetOutput("model.out");      // Write results to file
  RandomSeed(clock());
  Parser(CONFIG_FILE, &config);
  seedingMachines_S.SetCapacity(config.GetSeedingMachineCount());
  sprayers_S.SetCapacity(config.GetSprayerCount());
  harvestMachines_S.SetCapacity(config.GetHarvestMachineCount());
  //Print(" REPKA \n");
  Init(0, M_YEARS(1));                 // Init simulator for time 0..1000
  (new Generator)->Activate();  // Create generator, activate at 0
  Run();                        // - Simulation run
  usedLandStat.Output();
  butisanCompleteStat.Output();
  stratosUltraStat.Output();
  caryxStat.Output();
  pictorStat.Output();
  efilorStat.Output();
  harvestedLandStat.Output();
  profitStat.Output();
  SIMLIB_statistics.Output();   // Print simulator internal statistics
}
