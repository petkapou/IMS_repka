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
/*Facility butisanCompleteTime_F("Time for Butisan Complete");
Facility stratosUltraTime_F("Time for Stratos Ultra");
Facility caryxTime_F("Time for Caryx");
Facility pictorTime_F("Time for Pictor");
Facility efilorTime_F("Time for Efilor");

Facility eurofertilTopTime_F("Time for Eurofertil Top 49 NPS");
Facility fertiactylStarter0Time_F("Time for Fertiactyl Starter");
Facility fertiactylStarter1Time_F("Time for Fertiactyl Starter (second run)");
Facility fertileaderGold0Time_F("Time for Fertileader Gold");
Facility fertileaderGold1Time_F("Time for Fertileader Gold (second run)");
Facility fertileaderVitalTime_F("Time for Fertileader Vital");*/

Stat usedLandStat("Used land");
Stat butisanCompleteStat("Applied spray Butisan Complete");
Stat stratosUltraStat("Applied spray Stratos Ultra");
Stat caryxStat("Applied spray Caryx");
Stat pictorStat("Applied spray Pictor");
Stat efilorStat("Applied spray Efilor");
Stat harvestedLandStat("Harvested land");
Stat profitStat("Profit in tons");
Stat eurofertilTopStat("Applied fertilizer Eurofertil Top 49 NPS");
Stat fertiactylStarterStat("Applied fertilizer Fertiactyl Starter");
Stat fertileaderGoldStat("Applied fertilizer Fertileader Gold");
Stat fertileaderVitalStat("Applied fertilizer Fertileader Vital");

Stat fuelStat("Fuel consumption");
Stat waterStat("Water consumption");
Stat expensesStat("Expenses (czech crowns)");


Store tractors_S("Tractors", 0);
Store seedingMachines_S("Seeding Mechines", 0);
Store sprayers_S("Sprayers", 0);
Store fertilizerSpreaders_S("Fertilizers Spreaders", 0);
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
  RandomSeed(time(NULL));
  Parser(CONFIG_FILE, &config);
  tractors_S.SetCapacity(config.GetTractorCount());
  seedingMachines_S.SetCapacity(config.GetSeedingMachineCount());
  sprayers_S.SetCapacity(config.GetSprayerCount());
  fertilizerSpreaders_S.SetCapacity(config.GetFertilizerSpreaderCount());
  harvestMachines_S.SetCapacity(config.GetHarvestMachineCount());

  Init(0, M_YEARS(1));
  (new Generator)->Activate();
  Run();
  usedLandStat.Output();
  butisanCompleteStat.Output();
  stratosUltraStat.Output();
  caryxStat.Output();
  pictorStat.Output();
  efilorStat.Output();
  eurofertilTopStat.Output();
  fertiactylStarterStat.Output();
  fertileaderGoldStat.Output();
  fertileaderVitalStat.Output();
  harvestedLandStat.Output();
  waterStat.Output();
  expensesStat.Output();
  profitStat.Output();
  SIMLIB_statistics.Output();   // Print simulator internal statistics
}
