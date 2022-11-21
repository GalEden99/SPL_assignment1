#pragma once

#include <vector>
#include "Graph.h"
#include "Party.h"

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;

    vector<Party> mRelevantParties;
};
