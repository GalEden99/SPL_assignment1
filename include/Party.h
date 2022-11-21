#pragma once
#include <string>
#include "Agent.h"

using std::string;

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
    public:
        Party(int id, string name, int mandates, JoinPolicy *); 

        State getState() const;
        void setState(State state);
        int getMandates() const;
        void step(Simulation &s);
        const string &getName() const;
        const vector<Agent> getOffers() const;

        bool checkOffers(Party checkedParty, int partyId);
        int getId() const;
        void addOffer(Agent &newAgentOffer);



    private:
        int mId;
        string mName;
        int mMandates;
        JoinPolicy *mJoinPolicy;
        State mState;

        int mIteration;
        vector<Agent> mOffers;
};
