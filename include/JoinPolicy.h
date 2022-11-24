#pragma once
#include "Agent.h"

class JoinPolicy {
    public:
        JoinPolicy()=default;
        virtual int Join(vector<int> &mOffers, Simulation &sim) =0;
        virtual JoinPolicy * clone()=0;
        virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual int Join(vector<int> &mOffers, Simulation &sim);
        virtual MandatesJoinPolicy *clone();
        virtual ~MandatesJoinPolicy() = default;
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual int Join(vector<int> &mOffers, Simulation &sim);
        virtual LastOfferJoinPolicy * clone();
        virtual ~LastOfferJoinPolicy() = default;  
};