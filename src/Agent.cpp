#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"
#include "Party.h"


//~~~~~~~~~~~~Rule of 5~~~~~~~~~~~ 

//cunstractor
Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : 
mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy){}

// copy cunstractor
Agent::Agent(const Agent &other):mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy){
        mCoalitionId = other.mCoalitionId;
        //deep copy of vector
        int OtherSize = other.mRelevantParties.size();
        for(int i = 0; i<OtherSize;i++){
            mRelevantParties.push_back(other.mRelevantParties[i]);
        }
        mSelectionPolicy = other.mSelectionPolicy->clone();
        
}

// move cunstractor
Agent::Agent(Agent &&other):mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy){
    mCoalitionId = other.mCoalitionId;
    mRelevantParties = other.mRelevantParties;
    other.mSelectionPolicy = nullptr;
}


// move assignment 
Agent &Agent :: operator=(Agent &&other){
   if(mSelectionPolicy){delete mSelectionPolicy;}
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    *mSelectionPolicy = *other.mSelectionPolicy;
    mRelevantParties = other.mRelevantParties;
    mCoalitionId = other.mCoalitionId;
  
    other.mSelectionPolicy=nullptr;
    return *this;
}

// copy assignment 
Agent &Agent :: operator=(const Agent &other){
    if(this!=&other){
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mSelectionPolicy = other.mSelectionPolicy->clone();
        mRelevantParties = other.mRelevantParties;
        mCoalitionId = other.mCoalitionId;

        int relevantPartiesSize = other.mRelevantParties.size();
        for(int i = 0; i<relevantPartiesSize;i++){
            mRelevantParties.push_back(other.mRelevantParties[i]);   
        }
    }
    return *this;
}

//distractor
Agent::~Agent(){
    if(mSelectionPolicy){
        delete mSelectionPolicy;
        mSelectionPolicy = nullptr;
        }
}


int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::setCoalitionId(int coalitionId)
{
    mCoalitionId = coalitionId;
}

void Agent::setId(int newAgentId){
    mAgentId = newAgentId;
}

void Agent::setPartyId(int newPartyId){
    mPartyId = newPartyId;
}

int Agent::getCoalitionId() const{
    return mCoalitionId;
}

void Agent::clearReleventParties(){
    mRelevantParties = {};
}

void Agent::step(Simulation &sim)
{
    // building the mRelevantParties parties' vector to make an offer to
    int numParties = sim.getGraph().getNumVertices();
    
    for (int i=0; i<numParties; i++){
            // checking if i is a neighbor of the agent's party
            const Party &checkedParty = sim.getParty(i);
            switch (checkedParty.getState())
            {
            case Joined:
                break;
            case Waiting:
                if (sim.getGraph().getEdgeWeight(mPartyId, i) != 0) {
                    mRelevantParties.push_back(i);
                }
                break;
            case CollectingOffers:

                 if (sim.getGraph().getEdgeWeight(mPartyId, i) != 0) {
                    if(!checkedParty.checkOffers(mCoalitionId, checkedParty.getOffers(), sim)){
                        mRelevantParties.push_back(i);
                    }
                }
                break;
            }
        }
    
    // activing selection polity and getting the selected party
    int selectedPartyId = mSelectionPolicy->Select(mPartyId, mRelevantParties, sim);

    // addng our agent to the offers vectors of the selected party (if there is one)
    if (selectedPartyId > -1){
        sim.addOffer(selectedPartyId, *this);
    }

    // clearing the mRelevantParties vector for the next step
    mRelevantParties = {};
}



// this function cant return a party, only the id of the party 
int MandatesSelectionPolicy::Select(int agentPartyId, vector<int> &mRelevantParties, Simulation &sim){
    int maxMandates = -1;
    int maxMandatesPartyId = -1; 
    int tempSize = mRelevantParties.size();
    for (int i=0; i<tempSize; i++){
        int tempMandates = sim.getParty(mRelevantParties[i]).getMandates();
        if (maxMandates<tempMandates){
            maxMandates = tempMandates;
            maxMandatesPartyId = mRelevantParties[i];
        }
    }

    return maxMandatesPartyId;
}


// this function cant return a party, only the id of the party 
int EdgeWeightSelectionPolicy::Select(int agentPartyId, vector<int> &mRelevantParties, Simulation &sim){
    int maxEdgeWeight = -1;
    int selectedPartyId = -1;
    int tempSize =  mRelevantParties.size();
    for (int i=0; i<tempSize; i++){
        int currWeight = sim.getGraph().getEdgeWeight(agentPartyId, mRelevantParties[i]);

        if (maxEdgeWeight<currWeight){
            maxEdgeWeight = currWeight;
            selectedPartyId = mRelevantParties[i];
        }
    }
    return selectedPartyId; 
}



EdgeWeightSelectionPolicy * EdgeWeightSelectionPolicy:: clone(){
    return new EdgeWeightSelectionPolicy;
}

MandatesSelectionPolicy * MandatesSelectionPolicy:: clone(){
    return new MandatesSelectionPolicy;
}