#pragma once
#include "Agent.h"


using std::vector;

class Party;
class Simulation;

class SelectionPolicy {
    public:
        SelectionPolicy()=default;
        virtual Party* Select(int agentPartyId, vector<Party> &mRelevantParties, Simulation &sim)=0;
        virtual SelectionPolicy* clone()=0;
        virtual ~SelectionPolicy()=default;
 };

class MandatesSelectionPolicy: public SelectionPolicy{ 
    public:
        virtual Party* Select(int agentPartyId, vector<Party> &mRelevantParties, Simulation &sim);
        virtual MandatesSelectionPolicy* clone();
        virtual ~MandatesSelectionPolicy() = default;
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    public:
        virtual Party* Select(int agentPartyId, vector<Party> &mRelevantParties, Simulation &sim);
        virtual EdgeWeightSelectionPolicy* clone();
        virtual ~EdgeWeightSelectionPolicy() = default;
 };