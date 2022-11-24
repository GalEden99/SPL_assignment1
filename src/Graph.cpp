#include "Graph.h"
#include "Agent.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

void Graph::addOffer(int selectedPartyId, Agent& newAgentOffer){
    // add the offer to the party's offers vector
    mVertices[selectedPartyId].addOffer(newAgentOffer);
    
}

void Graph :: partiesStep(Simulation &sim){
    int size = mVertices.size();
    for (int i=0; i<size; i++){
        mVertices[i].step(sim);
    }
}