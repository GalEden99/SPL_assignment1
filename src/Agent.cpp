#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"
#include "Party.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : 
mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), mRelevantParties(0)
{
    // You can change the implementation of the constructor, but not the signature!
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    
    // building the mRelevantParties parties' vector to make an offer to
    int numParties = sim.getGraph().getNumVertices();
    
    for (int i=0; i<numParties; i++){
        // checking if i is a neighbor
        if (sim.getGraph().getEdgeWeight(mPartyId, i) != 0) {
            
            Party checkedParty = sim.getParty(i);

            // checking if i status is Waiting
            if (checkedParty.getState() == Waiting){

                // add to mRelevantParties
                mRelevantParties.push_back(checkedParty);
            }
            
            // checking if i status is CollectingOffers
            else if (checkedParty.getState() == CollectingOffers)
            {   

                if (!checkedParty.checkOffers(checkedParty, mPartyId)){ //checkOffers לממש את 
                    
                    // add to mRelevantParties
                    mRelevantParties.push_back(checkedParty);

                }
            }

        }
    }
    
    // activing selection polity and getting the selected party
    Party *selectedParty = mSelectionPolicy->Select(mPartyId, mRelevantParties, sim);

    // adding our agent to the offers vectors of the selected party
    selectedParty->addOffer(*this);


}
