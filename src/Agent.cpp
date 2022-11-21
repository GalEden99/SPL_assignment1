#include "Agent.h"
#include "Simulation.h"

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
    
    int numParties = sim.getGraph().getNumVertices();
    
    for (int i=0; i<numParties; i++){
        // checking if i is a neighbor
        if (sim.getGraph().getEdgeWeight(mPartyId, i) != 0) {

            // checking if i status is Waiting
            if (sim.getParty(i).getState() == Waiting){

                // add to mRelevantParties
                mRelevantParties.push_back(sim.getParty(i));
            }
            
            // checking if i status is CollectingOffers
            else if (sim.getParty(i).getState() == CollectingOffers)
            {

                if (!sim.getParty(i).checkOffers(this)){

                    // add to mRelevantParties
                    mRelevantParties.push_back(sim.getParty(i));

                }
            }

        }
    }
}
