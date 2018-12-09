#include "land.h"
#include "season.h"

extern ConfData config;
extern Facility workingHours_F;

extern Facility seedingTime_F;
extern Facility harvestTime_F;

extern Store tractors_S;
extern Store seedingMachines_S;
extern Store sprayers_S;
extern Store fertilizerSpreaders_S;
extern Store harvestMachines_S;

extern Stat usedLandStat;
extern Stat butisanCompleteStat;
extern Stat stratosUltraStat;
extern Stat caryxStat;
extern Stat pictorStat;
extern Stat efilorStat;
extern Stat harvestedLandStat;
extern Stat profitStat;
extern Stat eurofertilTopStat;
extern Stat fertiactylStarterStat;
extern Stat fertileaderGoldStat;
extern Stat fertileaderVitalStat;

extern Stat fuelStat;
extern Stat waterStat;
extern Stat expensesStat;

FertileLand::FertileLand() : profit(config.GetAverageProfit()), seedingTimeout(NULL), checkpoint0(false), checkpoint1(false){

}

void FertileLand::Behavior(){
  seedingTime_F.Seize(this);
  seedingTime_F.Release(this);
  seedingTimeout = new Timeout(this, config.GetSeedingDuration());
  Enter(tractors_S, 1);
  checkpoint0 = true;
  Enter(seedingMachines_S, 1);
  checkpoint1 = true;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  delete seedingTimeout;
  Wait(Uniform(7, 13));
  Leave(seedingMachines_S, 1);
  Leave(tractors_S, 1);
  usedLandStat(1);

  //Sprays

  (new ButisanComplete(this))->Activate(Time + BUTISAN_COMPLETE_TIME_START);
  (new StratosUltra(this))->Activate(Time + STRATOS_ULTRA_TIME_START);
  (new Caryx(this))->Activate(Time + CARYX_TIME_START);
  (new Efilor(this))->Activate(Time + EFILOR_TIME_START);
  (new Pictor(this))->Activate(Time + PICTOR_TIME_START);

  //Fertilizers

  (new EurofertilTop(this))->Activate(Time + EUROFERTIL_TOP_TIME_START);
  for (int i = FERTIACTYL_STARTER_TIME_START; i < (DEF_HARVESTTIMESTART - M_DAYS(21)); i+= FERTIACTYL_STARTER_DURATION)
  {
    (new FertiactylStarter(this))->Activate(Time + i);
  }

  for (int i = FERTILEADER_GOLD_TIME_START; i < (DEF_HARVESTTIMESTART - M_DAYS(21)); i+= FERTILEADER_GOLD_DURATION)
  {
    (new FertileaderGold(this))->Activate(Time + i);
  }
  (new FertileaderVital(this))->Activate(Time + FERTILEADER_VITAL_TIME_START);

  harvestTime_F.Seize(this);    //wait for harvest to start
  harvestTime_F.Release(this);
  (new FinalStage(profit))->Activate();
}

void FertileLand::MultProfit(double val){
  profit = profit * val;
}

void FertileLand::TimeoutFunc(){
  usedLandStat(0);

  if (checkpoint0)
    Leave(tractors_S, 1);

  if (checkpoint1)
    Leave(seedingMachines_S, 1);

  (new FertileLand)->Activate();
  Cancel();
}

FinalStage::FinalStage(double profit) : profit_m(profit), harvestTimeout(NULL){

}

void FinalStage::Behavior(){
  harvestTimeout = new Timeout(this, config.GetHarvestDuration());
  Enter(harvestMachines_S, 1);
  delete harvestTimeout;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  Wait(Exponential(6));
  Leave(harvestMachines_S, 1);
  harvestedLandStat(1);
  profitStat(profit_m);
}

void FinalStage::TimeoutFunc(){
  harvestedLandStat(0);
  (new FertileLand)->Activate();
  Cancel();
}

TimeoutInterface::TimeoutInterface(){
  Activate();
}
void TimeoutInterface::Behavior() {

}

void TimeoutInterface::TimeoutFunc() {
  
}

Timeout::Timeout(TimeoutInterface*id, double timeout) : id_m(id) {
  Activate(Time + timeout);
}

void Timeout::Behavior() {
  id_m->TimeoutFunc();
  Cancel();
}

ButisanComplete::ButisanComplete(FertileLand *id) : checkpoint(false), parent_m(id){

}

void ButisanComplete::Behavior() {
  sprayTimeout = new Timeout(this, BUTISAN_COMPLETE_DURATION);
  Enter(sprayers_S, 1);
  checkpoint = true;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  delete sprayTimeout;
  if (Random() <= 0.1)  //select only infested hectars
  {
    waterStat(Uniform(100, 400)); //consume 100-400 l of water
    expensesStat(2032);           //2 l of spray per hectar(one costs 1016)
    Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  }
  Leave(sprayers_S, 1);
  butisanCompleteStat(1);
}

void ButisanComplete::TimeoutFunc() {
  butisanCompleteStat(0);
  if (checkpoint)
    Leave(sprayers_S, 1);
  
  if (Random() <= 0.1)  //not every missed hectar is infected
    parent_m->MultProfit(Uniform(0.4, 1));    //weed can destroy up to 60 percent of crop

  Cancel();
}

StratosUltra::StratosUltra(FertileLand *id) : checkpoint(false), parent_m(id){

}

void StratosUltra::Behavior() {
  sprayTimeout = new Timeout(this, STRATOS_ULTRA_DURATION);
  Enter(sprayers_S, 1);
  checkpoint = true;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  delete sprayTimeout;
  if (Random() <= 0.1)  //select only infested hectars
  {
    waterStat(Uniform(500, 600)); //consume 100-400 l of water
    expensesStat(6990);           //cost with addition Dash HC
    Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  }
  Leave(sprayers_S, 1);
  stratosUltraStat(1);
}

void StratosUltra::TimeoutFunc() {
  stratosUltraStat(0);
  if (checkpoint)
    Leave(sprayers_S, 1);
  
  if (Random() <= 0.1)
    parent_m->MultProfit(Uniform(0.4, 1));

  Cancel();
}

Caryx::Caryx(FertileLand *id) : checkpoint(false), parent_m(id){

}

void Caryx::Behavior() {
  sprayTimeout = new Timeout(this, CARYX_DURATION);
  Enter(sprayers_S, 1);
  checkpoint = true;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  delete sprayTimeout;
  waterStat(Uniform(150, 400));
  expensesStat(Uniform(757,1009));
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  parent_m->MultProfit(Uniform(1.1, 1.4));  //10 to 40 percent increase
  caryxStat(1);
}

void Caryx::TimeoutFunc() {
  caryxStat(0);
  if (checkpoint)
    Leave(sprayers_S, 1);
  
  parent_m->MultProfit(Uniform(0.8, 1));  //Spray Caryx also provides protection
  Cancel();
}

Efilor::Efilor(FertileLand *id) : checkpoint(false), parent_m(id){

}

void Efilor::Behavior() {
  sprayTimeout = new Timeout(this, EFILOR_DURATION);
  Enter(sprayers_S, 1);
  checkpoint = true;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  delete sprayTimeout;
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  parent_m->MultProfit(Uniform(1, 1.2));  //increases bloom, and stem spread. Enlargering siliques.
  efilorStat(1);
}

void Efilor::TimeoutFunc() {
  efilorStat(0);
  if (checkpoint)
    Leave(sprayers_S, 1);
  
  parent_m->MultProfit(Uniform(0.8, 1));
  Cancel();
}

Pictor::Pictor(FertileLand *id) : checkpoint(false), parent_m(id){

}

void Pictor::Behavior() {
  sprayTimeout = new Timeout(this, PICTOR_DURATION);
  Enter(sprayers_S, 1);
  checkpoint = true;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  delete sprayTimeout;
  expensesStat(1640);
  waterStat(Uniform(200, 400));
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  pictorStat(1);
}

void Pictor::TimeoutFunc() {
  pictorStat(0);
  if (checkpoint)
    Leave(sprayers_S, 1);

  parent_m->MultProfit(Uniform(0.7, 1));    //up to 30 percent loss
  Cancel();
}

EurofertilTop::EurofertilTop(FertileLand *id) : checkpointTractor(false), checkpointSpreader(false), parent_m(id){

}

void EurofertilTop::Behavior() {
  sprayTimeout = new Timeout(this, EUROFERTIL_TOP_DURATION);
  Enter(tractors_S, 1);
  checkpointTractor = true;
  Enter(fertilizerSpreaders_S, 1);
  checkpointSpreader = true;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  delete sprayTimeout;
  expensesStat(Uniform(2182.5, 3637.5));
  fuelStat(Exponential(1.374074074));
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(fertilizerSpreaders_S, 1);
  Leave(tractors_S, 1);
  eurofertilTopStat(1);
}

void EurofertilTop::TimeoutFunc() {
  eurofertilTopStat(0);
  if (checkpointSpreader)
    Leave(fertilizerSpreaders_S, 1);

  if (checkpointTractor)
    Leave(tractors_S, 1);

  parent_m->MultProfit(Uniform(1, 1.3));
  Cancel();
}

FertiactylStarter::FertiactylStarter(FertileLand *id) : checkpointSprayer(false), parent_m(id){

}

void FertiactylStarter::Behavior() {
  sprayTimeout = new Timeout(this, FERTIACTYL_STARTER_DURATION);
  Enter(sprayers_S, 1);
  checkpointSprayer = true;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  delete sprayTimeout;
  expensesStat(374.4);
  waterStat(Uniform(150,500));
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  fertiactylStarterStat(1);
}

void FertiactylStarter::TimeoutFunc() {
  fertiactylStarterStat(0);
  if (checkpointSprayer)
    Leave(sprayers_S, 1);

  parent_m->MultProfit(Uniform(1, 1.2));
  Cancel();
}

FertileaderGold::FertileaderGold(FertileLand *id) : checkpointSprayer(false), parent_m(id){

}

void FertileaderGold::Behavior() {
  sprayTimeout = new Timeout(this, FERTILEADER_GOLD_DURATION);
  Enter(sprayers_S, 1);
  checkpointSprayer = true;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  delete sprayTimeout;
  expensesStat(1278.648);
  waterStat(Uniform(150,500));
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  fertileaderGoldStat(1);
}

void FertileaderGold::TimeoutFunc() {
  fertileaderGoldStat(0);
  if (checkpointSprayer)
    Leave(sprayers_S, 1);

  parent_m->MultProfit(Uniform(1, 1.2));
  Cancel();
}

FertileaderVital::FertileaderVital(FertileLand *id) : checkpointSprayer(false), parent_m(id){

}

void FertileaderVital::Behavior() {
  sprayTimeout = new Timeout(this, FERTILEADER_VITAL_DURATION);
  Enter(sprayers_S, 1);
  checkpointSprayer = true;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  delete sprayTimeout;
  expensesStat(1651.2);
  waterStat(Uniform(150,500));
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  fertileaderVitalStat(1);
}

void FertileaderVital::TimeoutFunc() {
  fertileaderVitalStat(0);
  if (checkpointSprayer)
    Leave(sprayers_S, 1);

  parent_m->MultProfit(Uniform(1, 1.2));
  Cancel();
}