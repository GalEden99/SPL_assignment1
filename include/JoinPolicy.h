#pragma once
#include "Party.h"
#include "Agent.h"
#include "Simulation.h"

class JoinPolicy {
    public:
        JoinPolicy()=default;
        virtual const Agent* Join(vector<Agent> &mOffers, Simulation &sim) const =0;
        virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual const Agent* Join(vector<Agent> &mOffers, Simulation &sim) const;
        virtual ~MandatesJoinPolicy() = default;
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual Agent* Join(vector<Agent> &mOffers, Simulation &sim);
        virtual ~LastOfferJoinPolicy() = default;  
};