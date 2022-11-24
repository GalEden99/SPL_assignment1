#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class JoinPolicy;
class Simulation;
class Agent;

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
        Party() = default;
        Party(const Party &);
        Party(Party &&);
        Party &operator=(Party &&other);
        Party &operator=(const Party &other);
        ~Party();

        State getState() const;
        void setState(State state);
        int getMandates() const;
        void step(Simulation &s);
        const string &getName() const;
        const vector<int> getOffers() const;
        bool checkOffers( int coalitionId, vector<int> mOffers, Simulation &sim) const;
        int getId() const;
        void addOffer(Agent &newAgentOffer, Simulation &sim);
        JoinPolicy *getJoinPolicy() const;
        

    private:
        int mId;
        string mName;
        int mMandates;
        JoinPolicy *mJoinPolicy;
        State mState;
        int mIteration=0;
        vector<int> mOffers={};
};
