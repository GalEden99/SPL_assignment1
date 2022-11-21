#pragma once
#include "Party.h"
#include "Agent.h"

class JoinPolicy {
    public:
        JoinPolicy()=default;
        virtual Agent Join()=0;
        virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual Agent Join();
        virtual ~MandatesJoinPolicy() = default;

};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual Agent Join();
        virtual ~LastOfferJoinPolicy() = default;
        

        
};