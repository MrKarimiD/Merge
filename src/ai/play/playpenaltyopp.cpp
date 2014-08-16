#include "playpenaltyopp.h"

PlayPenaltyOpp::PlayPenaltyOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayPenaltyOpp", worldmodel, parent)
{
}

int PlayPenaltyOpp::enterCondition()
{
    if(wm->cmgs.theirPenaltyKick())
        return 100;
    else
        return 0;
}

void PlayPenaltyOpp::execute()
{
}
