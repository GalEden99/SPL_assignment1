#include "Simulation.h"
#include "Agent.h"
#include "Graph.h"


Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
    // creating a vector of coalition sizes and updateing the agents' coalition number
    int tempSize = mAgents.size();
    for (int i=0; i<tempSize; i++){
        mAgents[i].setCoalitionId(i);
        //
        int currAgentPartyId = mAgents[i].getPartyId();
        Party currAgentParty = mGraph.getParty(currAgentPartyId);
        int newMandates = currAgentParty.getMandates();
        mCoalitionSize.push_back(newMandates);
    }

}

void Simulation::step()
{
    auto &temp = *this;

    // apply Party::step() for each party through the graph
    mGraph.partiesStep(temp);

    // apply Agent::step() for each agent in mAgents
    int tempSize = mAgents.size();
    for (int i=0; i<tempSize; i++){
        // Agent currAgent = mAgents[i];
        // currAgent.step(*this);
        mAgents[i].step(temp);
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
    // return mAgents.size() == mGraph.getNumVertices();
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

const Agent& Simulation::getAgent(int agentId)
{
    return mAgents[agentId];
}


const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

void Simulation::addAgent(Agent newAgent){
    mAgents.push_back(newAgent);
}

void Simulation::updateCoalitionSize(int coalitionId, int mMandates){
    // getCoalitionSize()[coalitionId] =+ mMandates;
    mCoalitionSize[coalitionId] += mMandates;
}

vector<int> Simulation::getCoalitionSize(){
    return mCoalitionSize;
}

void Simulation::addOffer(int selectedPartyId, Agent& newAgentOffer){
    // add the offer to the party's offers vector
    mGraph.addOffer(selectedPartyId, newAgentOffer, *this);
}

bool Simulation::checkOffers(int coalitionId, vector<int> mOffers) //נקבל את ( int coalitionId, mOffers={agentId1, ...})
{
    // נעבור על כל הסוכנים ונבדוק האם אחד מהם מאותה קואליציה כמו קואלישין ID 
    int tempSize = mOffers.size();
    for (int i=0; i<tempSize; i++){
        int currAgentId = mOffers[i];
        if (getAgent(currAgentId).getCoalitionId() == coalitionId){ //
            return true; //already been offered 
        }
    }
    return false; //not been offered yet

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
    return partiesByCoalition; // ?
}
