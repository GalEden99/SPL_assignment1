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


// move assignment cunstractor
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

// copy assignment cunstractor
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

                if (!checkedParty.checkOffers(mPartyId, mCoalitionId, sim)){ // if the party didn't get an offer from another agent from the same party
                    
                    // add to mRelevantParties
                    mRelevantParties.push_back(checkedParty);

                }
            }

        }
    }
    
    // activing selection polity and getting the selected party
    int selectedPartyId = mSelectionPolicy->Select(mPartyId, mRelevantParties, sim);

    // // if there is a selected party ??? לא מתעדכן 
    // if (selectedPartId > -1){
    //     Party selectedParty = sim.getParty(selectedPartId);
    //     if (selectedParty.getState() == Waiting){

    //         selectedPartId->setState(CollectingOffers);
    //     }
    // }

    // adding our agent to the offers vectors of the selected party (if there is one)
    if (selectedPartyId > -1){
        sim.addOffer(selectedPartyId, *this);
    }

}



// this function cant return a party, only the id of the party 
int MandatesSelectionPolicy::Select(int agentPartyId, vector<Party> &mRelevantParties, Simulation &sim){
    int maxMandates = -1;
    Party *maxMandatesParty = 0; 
    int tempSize = mRelevantParties.size();
    for (int i=0; i<tempSize; i++){
    
        if (maxMandates<mRelevantParties[i].getMandates()){
            maxMandates = mRelevantParties[i].getMandates();
            maxMandatesParty = &mRelevantParties[i];
        }
    }

    if (maxMandatesParty != 0){
        return maxMandatesParty->getId();
    }
    else{
        return -1; // no party was selected
    }
    //return maxMandatesParty; // return a ptr to the party with max num of mandates 
}


// this function cant return a party, only the id of the party
int EdgeWeightSelectionPolicy::Select(int agentPartyId, vector<Party> &mRelevantParties, Simulation &sim){
        int maxEdgeWeight = -1;
        Party *maxEdgeWeightParty = 0;
        int tempSize =  mRelevantParties.size();
        for (int i=0; i<tempSize; i++){
            
            int currPartyId = mRelevantParties[i].getId();
            int currWeight = sim.getGraph().getEdgeWeight(agentPartyId, currPartyId);

            if (maxEdgeWeight<currWeight){
                maxEdgeWeight = currWeight;
                maxEdgeWeightParty = &mRelevantParties[i];
        }
    }

    if (maxEdgeWeightParty != 0){
        return maxEdgeWeightParty->getId();
    }
    else{
        return -1; // no party was selected
    }
    //return maxEdgeWeightParty; // return a ptr to the party with max Edge Weight
}



EdgeWeightSelectionPolicy * EdgeWeightSelectionPolicy:: clone(){
    return new EdgeWeightSelectionPolicy;
}

MandatesSelectionPolicy * MandatesSelectionPolicy:: clone(){
    return new MandatesSelectionPolicy;
}