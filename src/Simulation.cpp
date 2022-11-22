#include "Simulation.h"
#include "Agent.h"
#include "Graph.h"


Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
    // creating a vector of coalition sizes and updateing the agents' coalition number
    int tempSize = mAgents.size();
    for (int i=0; i<tempSize; i++){
        mAgents[i].setCoalitionId(i);
        int cuurAgentPartyId = mAgents[i].getPartyId();
        mCoalitionSize[i] = graph.getParty(cuurAgentPartyId).getMandates();
    }
}

void Simulation::step()
{
    // apply Party::step() for each party in mGraph
    int tempSize = mGraph.getNumVertices();
    for (int i=0; i<tempSize; i++){
        Party currParty = mGraph.getParty(i);
        currParty.step(*this);
    }

    // apply Agent::step() for each agent in mAgents
    tempSize = mAgents.size();
    for (int i=0; i<tempSize; i++){
        Agent currAgent = mAgents[i];
        currAgent.step(*this);

    }

}

bool Simulation::shouldTerminate() const
{
    //checking if one of the coalitions has at least 61 mandates
    int tempSize = mCoalitionSize.size();
    for (int i=0; i<tempSize; i++){
        if (mCoalitionSize[i]>60){
            return true;
        }
    }

    //checking if all the parties joined a coalition 
    bool allJoined = true; 
    for (int i=0; i<getGraph().getNumVertices(); i++){
        if (getGraph().getParty(i).getState() != Joined ){
            allJoined = false;
        }
    }

    if (allJoined == true){
        return true;
    }

    return false;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}
vector<Agent> Simulation::GetAgents() const
{
    return mAgents;
}


const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

void Simulation::addAgent(Agent newAgent){
    GetAgents().push_back(newAgent);
}

void Simulation::updateCoalitionSize(int coalitionId, int mMandates){
    getCoalitionSize()[coalitionId] =+ mMandates;
}

vector<int> Simulation::getCoalitionSize(){
    return mCoalitionSize;
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> partiesByCoalition (mCoalitionSize.size(),vector<int>());
    int agentSize = mAgents.size();
    for(int i = 0; i<agentSize;i++){
        partiesByCoalition[mAgents[i].getCoalitionId()].push_back(mAgents[i].getPartyId());
    }
    return vector<vector<int>>();
}
