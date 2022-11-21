#pragma once
#include "Party.h"
#include "Agent.h"

class JoinPolicy {
    public:
        JoinPolicy();
        virtual Agent Join();
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        MandatesJoinPolicy();
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        LastOfferJoinPolicy();
};