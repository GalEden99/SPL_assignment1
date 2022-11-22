#pragma once
#include "Agent.h"

class JoinPolicy {
    public:
        JoinPolicy()=default;
        virtual Agent* Join(vector<Agent> &mOffers, Simulation &sim) =0;
        virtual JoinPolicy * clone()=0;
        virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual Agent* Join(vector<Agent> &mOffers, Simulation &sim);
        virtual MandatesJoinPolicy *clone();
        virtual ~MandatesJoinPolicy() = default;
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual Agent* Join(vector<Agent> &mOffers, Simulation &sim);
        virtual LastOfferJoinPolicy * clone();
        virtual ~LastOfferJoinPolicy() = default;  
};