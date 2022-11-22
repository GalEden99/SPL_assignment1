#pragma once

#include <vector>
#include "Graph.h"

#include <string>

using std::string;
using std::vector;

class Agent;


class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    vector<Agent> GetAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
    vector<int> getCoalitionSize();
    void addAgent(Agent newAgent);
    void updateCoalitionSize(int CoalitionId, int mMandates);




private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<int> mCoalitionSize={};
};
