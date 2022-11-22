#pragma once

#include <vector>
#include "Graph.h"


using std::vector;

class SelectionPolicy;
class Simulation;
class Party;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent() = default;
    Agent(const Agent &);
    Agent(Agent &&);
    Agent &operator=(Agent &&other);
    Agent &operator=(const Agent &other);
    ~Agent();

    int getPartyId() const;
    int getId() const;
    void step(Simulation &s);
    void setCoalitionId(int coalitionId);
    void setId(int newAgentId);
    void setPartyId(int newPartyId);
    int getCoalitionId()const ;


private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    vector<Party> mRelevantParties={};
    int mCoalitionId=-1;
};
