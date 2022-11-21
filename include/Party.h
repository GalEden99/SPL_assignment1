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
    const vector<Agent> getmOffers() const;
    bool checkOffers(int partyId) const;


private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;

    int mIteration;
    vector<Agent> mOffers;
};
