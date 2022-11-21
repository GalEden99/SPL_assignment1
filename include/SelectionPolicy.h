#pragma once
#include "Party.h"

class SelectionPolicy {
    public:
        SelectionPolicy()=default;
        virtual Party* Select(int agentPartyId, vector<Party> &mRelevantParties, Simulation &sim)=0;
        virtual ~SelectionPolicy()=0;
 };

class MandatesSelectionPolicy: public SelectionPolicy{ 
    public:
        virtual Party* Select(int agentPartyId, vector<Party> &mRelevantParties, Simulation &sim);
        virtual ~MandatesSelectionPolicy() = default;
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    public:
        virtual Party* Select(int agentPartyId, vector<Party> &mRelevantParties, Simulation &sim);
        virtual ~EdgeWeightSelectionPolicy() = default;
 };