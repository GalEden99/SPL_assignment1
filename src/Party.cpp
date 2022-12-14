#include "Party.h"
#include "Agent.h"
#include "JoinPolicy.h"
#include "Simulation.h"


//~~~~~~~~~~~~Rule of 5~~~~~~~~~~~ 

//cunstractor
Party::Party(int id, string name, int mandates, JoinPolicy *jp) :
 mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting){}

// copy cunstractor
Party::Party(const Party &other ):mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState){
        mIteration=other.mIteration;
        //deep copy of vector
        int OtherSize = other.mOffers.size();
        for(int i = 0; i<OtherSize;i++){
            mOffers.push_back(other.mOffers[i]);
        }
        
}

// move cunstractor
Party::Party(Party &&other):mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState){
    mIteration = other.mIteration;
    mOffers = other.mOffers;
    other.mJoinPolicy = nullptr;
}

// move assignment 
Party &Party :: operator=(Party &&other){
   if(mJoinPolicy){delete mJoinPolicy;}
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mJoinPolicy = other.mJoinPolicy;
    mState = other.mState;
    mIteration = other.mIteration;
    mOffers = other.mOffers;

    other.mJoinPolicy=nullptr;
    return *this;
}

// copy assignment 
Party &Party :: operator=(const Party &other){
    if(this!=&other){
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mJoinPolicy = other.mJoinPolicy->clone();
        mState = other.mState;
        mIteration = other.mIteration;

        int offersSize = other.mOffers.size();
        for(int i = 0; i<offersSize;i++){
            mOffers.push_back(other.mOffers[i]);   
        }
    }
    return *this;
}

//distractor
Party:: ~Party(){
    if(mJoinPolicy){
        delete mJoinPolicy;
        mJoinPolicy = nullptr;
        }
}


//~~~~~~~~~~~~~~ regular Functions
State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

const vector<int> Party::getOffers() const{
    return mOffers;
}

int Party::getId() const {
    return mId;
}

JoinPolicy* Party::getJoinPolicy() const {
    return mJoinPolicy;
}

void Party::addOffer(Agent &newAgentOffer, Simulation &sim){
   
    if(mState == Waiting){
        mState = CollectingOffers;
        mIteration+=1;
    }

    // add the offer to the party's offers vector
    if (!sim.checkOffers(newAgentOffer.getCoalitionId(), mOffers)){
        mOffers.push_back(newAgentOffer.getId()); 
    } 
    
}

bool Party::checkOffers( int coalitionId, vector<int> mOffers, Simulation &sim) const
{
    return sim.checkOffers(coalitionId, mOffers);
}

void Party::step(Simulation &s)
{
    // Check if the status is collectingOffers and update the itaeration timer
    if (getState() == CollectingOffers){
        if (mIteration<3){
            mIteration = mIteration+1; 
        } else {
            // iteration = 3, apply JoinPolicy
            int choosenAgent = mJoinPolicy->Join(mOffers, s);

            // set state to Joined
            setState(Joined);

            // clone agent
            Agent newAgent(s.getAgent(choosenAgent));

            newAgent.setId(s.getAgents().size());
            newAgent.setPartyId(mId);
            newAgent.clearReleventParties();

            //add mandates to mCoalitionSize
            s.updateCoalitionSize(newAgent.getCoalitionId(), mMandates);

            //add to agents vector in the simulation
            s.addAgent(newAgent);

        }
    } 
 }

int MandatesJoinPolicy::Join(vector<int> &mOffers, Simulation &sim){
    int bestOfferAgent = -1;
    int maxMandates = 0;
    int tempSize = mOffers.size();
    for (int i=0; i<tempSize; i++){
        if (maxMandates<sim.getCoalitionSize()[i]){
            maxMandates = sim.getCoalitionSize()[i];
            bestOfferAgent = mOffers[i];
        }
    }
    return bestOfferAgent;
}

int LastOfferJoinPolicy::Join(vector<int> &mOffers, Simulation &sim){
    int lastOfferAgent = mOffers[mOffers.size()-1];
    return lastOfferAgent;
}

MandatesJoinPolicy * MandatesJoinPolicy:: clone(){
    return new MandatesJoinPolicy;
}

LastOfferJoinPolicy * LastOfferJoinPolicy:: clone(){
    return new LastOfferJoinPolicy;
}
