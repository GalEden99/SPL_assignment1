// #include "JoinPolicy.h"
// #include "Agent.h"
// #include "Simulation.h"
// #include "Party.h"

// Agent* MandatesJoinPolicy::Join(vector<Agent> &mOffers, Simulation &sim){
//     Agent *bestOfferAgent = 0;
//     int maxMandates = 0;
//     for (int i=0; i<mOffers.size(); i++){
//         if (maxMandates<sim.getCoalitionSize()[i]){
//             maxMandates = sim.getCoalitionSize()[i];
//             bestOfferAgent = &mOffers[i];
//         }
//     }
//     return bestOfferAgent;
// }


// Agent* LastOfferJoinPolicy::Join(vector<Agent> &mOffers, Simulation &sim){
//     Agent *lastOfferAgent = &mOffers[mOffers.size()-1];
//     return lastOfferAgent;
// }

// LastOfferJoinPolicy * LastOfferJoinPolicy:: clone(){
//     return new LastOfferJoinPolicy(*this);
// }

// MandatesJoinPolicy * MandatesJoinPolicy:: clone(){
//     return new MandatesJoinPolicy(*this);
// }