#include "SelectionPolicy.h"
#include "Party.h"
#include "Simulation.h"

Party* MandatesSelectionPolicy::Select(int agentPartyId, vector<Party> &mRelevantParties, Simulation &sim){
    int maxMandates = -1;
    Party *maxMandatesParty = 0; 
    for (int i=0; i<mRelevantParties.size(); i++){
    
        if (maxMandates<mRelevantParties[i].getMandates()){
            maxMandates = mRelevantParties[i].getMandates();
            maxMandatesParty = &mRelevantParties[i];
        }
    }
    return maxMandatesParty; // return a ptr to the party with max num of mandates 
}



Party* EdgeWeightSelectionPolicy::Select(int agentPartyId, vector<Party> &mRelevantParties, Simulation &sim){
        int maxEdgeWeight = -1;
        Party *maxEdgeWeightParty = 0; 
        for (int i=0; i<mRelevantParties.size(); i++){
            
            int currPartyId = mRelevantParties[i].getId();
            int currWeight = sim.getGraph().getEdgeWeight(agentPartyId, currPartyId);

            if (maxEdgeWeight<currWeight){
                maxEdgeWeight = currWeight;
                maxEdgeWeightParty = &mRelevantParties[i];
        }
    }
    return maxEdgeWeightParty; // return a ptr to the party with max Edge Weight
}

