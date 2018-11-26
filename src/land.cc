#include "land.h"
#include "season.h"

FertileLand::FertileLand() : profit(200.0), seedingTimeout(NULL){

}

void FertileLand::Behavior(){
  seedingTime_F.Seize(this);
  seedingTime_F.Release(this);
  seedingTimeout = new Timeout(this, config.GetSeedingDuration());
  Enter(seedingMachines_S, 1);
   delete seedingTimeout;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  Wait(Uniform(7, 13));
  Leave(seedingMachines_S, 1);
  usedLandStat(1);

  //Sprays

  (new ButisanComplete(this))->Activate();
  (new StratosUltra(this))->Activate();
  (new Caryx(this))->Activate();
  (new Efilor(this))->Activate();
  (new Pictor(this))->Activate();

  harvestTime_F.Seize(this);
  harvestTime_F.Release(this);
  (new FinalStage(profit))->Activate();
}

void FertileLand::MultProfit(double val){
  profit = profit * val;
}

void FertileLand::TimeoutFunc(){
  usedLandStat(0);
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

ButisanComplete::ButisanComplete(FertileLand *id) : parent_m(id){

}

void ButisanComplete::Behavior() {
  butisanCompleteTime_F.Seize(this);
  butisanCompleteTime_F.Release(this);
  sprayTimeout = new Timeout(this, BUTISAN_COMPLETE_DURATION);
  Enter(sprayers_S, 1);
  delete sprayTimeout;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  butisanCompleteStat(1);
}

void ButisanComplete::TimeoutFunc() {
  butisanCompleteStat(0);
  parent_m->MultProfit(Uniform(0.4, 1));
  Cancel();
}

StratosUltra::StratosUltra(FertileLand *id) : parent_m(id){

}

void StratosUltra::Behavior() {
  stratosUltraTime_F.Seize(this);
  stratosUltraTime_F.Release(this);
  sprayTimeout = new Timeout(this, STRATOS_ULTRA_DURATION);
  Enter(sprayers_S, 1);
  delete sprayTimeout;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  stratosUltraStat(1);
}

void StratosUltra::TimeoutFunc() {
  stratosUltraStat(0);
  parent_m->MultProfit(Uniform(0.4, 1));
  Cancel();
}

Caryx::Caryx(FertileLand *id) : parent_m(id){

}

void Caryx::Behavior() {
  caryxTime_F.Seize(this);
  caryxTime_F.Release(this);
  sprayTimeout = new Timeout(this, CARYX_DURATION);
  Enter(sprayers_S, 1);
  delete sprayTimeout;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  caryxStat(1);
}

void Caryx::TimeoutFunc() {
  caryxStat(0);
  parent_m->MultProfit(Uniform(0.4, 1));
  Cancel();
}

Efilor::Efilor(FertileLand *id) : parent_m(id){

}

void Efilor::Behavior() {
  efilorTime_F.Seize(this);
  efilorTime_F.Release(this);
  sprayTimeout = new Timeout(this, EFILOR_DURATION);
  Enter(sprayers_S, 1);
  delete sprayTimeout;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  efilorStat(1);
}

void Efilor::TimeoutFunc() {
  efilorStat(0);
  parent_m->MultProfit(Uniform(0.4, 1));
  Cancel();
}

Pictor::Pictor(FertileLand *id) : parent_m(id){

}

void Pictor::Behavior() {
  pictorTime_F.Seize(this);
  pictorTime_F.Release(this);
  sprayTimeout = new Timeout(this, PICTOR_DURATION);
  Enter(sprayers_S, 1);
  delete sprayTimeout;
  workingHours_F.Seize(this);
  workingHours_F.Release(this);
  Wait(Uniform(M_MINUTES(5), M_MINUTES(10)));
  Leave(sprayers_S, 1);
  pictorStat(1);
}

void Pictor::TimeoutFunc() {
  pictorStat(0);
  parent_m->MultProfit(Uniform(0.4, 1));
  Cancel();
}