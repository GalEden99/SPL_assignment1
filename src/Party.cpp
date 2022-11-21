#include "Party.h"
#include "Agent.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) :
 mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mIteration(0), mOffers(0)
{
    // You can change the implementation of the constructor, but not the signature!
}

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

const vector<Agent> Party::getOffers() const{
    return mOffers;
}

int Party::getId() const {
    return mId;
}

void Party::addOffer(Agent &newAgentOffer){
    mOffers.push_back(newAgentOffer);
}

bool Party::checkOffers(Party checkedParty, int partyId) 
{
    
    for (int i=0; i<checkedParty.getOffers().size(); i++){
        //
    }
    return true;
    
}

void Party::step(Simulation &s)
{
    // Check if the status is collectingOffers and update the itaeration timer
    if (getState() == CollectingOffers){
        if (mIteration<3){
            mIteration = mIteration+1;
        } else {
            // iteration = 3, apply JoinPolicy
            Agent choosenAgent = mJoinPolicy->Join(); // נבחר לאיזה קואליציה להצטרף

            // set state to Joined
            setState(Joined);

           // ניצור שכפול של הסוכן ונוסיף לוקטור הסוכנים 

        }
    }

    
}
