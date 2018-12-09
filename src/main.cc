/*
 *    IMS project 2018 repka
 *
 *  author: Erik Kelemen(xkelem01)
 *  author: Petr Kapoun(xkoapou04)
 *  
 */

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

Stat usedLandStat("Used land");
Stat butisanCompleteStat("Applied spray Butisan Complete");
Stat stratosUltraStat("Applied spray Stratos Ultra");
Stat caryxStat("Applied spray Caryx");
Stat pictorStat("Applied spray Pictor");
Stat efilorStat("Applied spray Efilor");
Stat vaztakActiveStat("Applied spray Vaztak Active");
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
  SetOutput("model.out");      // Write results to file
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
  Print("STATISTICS: \n");
  Print("Seeded %.2f%, from %d hectars\n", usedLandStat.MeanValue()*100, config.GetFertileLandCount());

  Print("\nSPRAYS: \n");

  Print("Spray Butisan Complete success: %.2f%\n", butisanCompleteStat.MeanValue()*100);
  Print("Spray Stratos Ultra success: %.2f%\n", stratosUltraStat.MeanValue()*100);
  Print("Spray Caryx success: %.2f%\n", caryxStat.MeanValue()*100);
  Print("Spray Pictor success: %.2f%\n", pictorStat.MeanValue()*100);
  Print("Spray Vaztak Active success: %.2f%\n", vaztakActiveStat.MeanValue()*100);

  Print("\nFERTILIZERS: \n");
  Print("Fertilizer Eurofertil Top success: %.2f%\n", eurofertilTopStat.MeanValue()*100);
  Print("Fertilizer Fertiactyl Starter success: %.2f%\n", fertiactylStarterStat.MeanValue()*100);
  Print("Fertilizer Fertileader Gold success: %.2f%\n", fertileaderGoldStat.MeanValue()*100);
  Print("Fertilizer Fertileader Vital success: %.2f%\n\n", fertileaderVitalStat.MeanValue()*100);

  Print("Harvested %.2f%, %.0f hectars\n", harvestedLandStat.MeanValue()*100, harvestedLandStat.Sum());

  Print("Water consumption: %.2f liters\n", waterStat.Sum());
  Print("Fuel consumption: %.2f liters\n", fuelStat.Sum());
  Print("Expenses for sprays and fertilizers: %.2f czech crowns\n", expensesStat.Sum());
  Print("Profit: %.2f tons\n", profitStat.Sum());
  
  SIMLIB_statistics.Output();   // Print simulator internal statistics
}
