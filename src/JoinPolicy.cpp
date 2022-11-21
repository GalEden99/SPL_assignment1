#include "JoinPolicy.h"
#include "Agent.h"
#include "Simulation.h"
#include "Party.h"

const Agent* MandatesJoinPolicy::Join(vector<Agent> &mOffers, Simulation &sim) const{
    int maxMandates = -1;
    Agent *maxMandatesAgent = 0;


    for (int i=0; i<mOffers.size(); i++){

        int currPartyId = mOffers[i].getPartyId();
        Party currParty = sim.getParty(currPartyId); // לבדוק האם רפרנס

        // להוסיף קלאס של קואליציה ולעדכן בו את כמות המנדטים הכוללת ולפי זה לבחור את הסוכן הרלוונטי מחר 

        if (maxMandates<currParty.getMandates()){
            maxMandates = currParty.getMandates();
            maxMandatesAgent = &mOffers[i];
        }
    }

    return maxMandatesAgent;

}


Agent* LastOfferJoinPolicy::Join(vector<Agent> &mOffers, Simulation &sim){
    
}