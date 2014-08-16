#include "playpenaltyour.h"

PlayPenaltyOur::PlayPenaltyOur(WorldModel *worldmodel, QObject *parent) :
    Play("PlayPenaltyOur", worldmodel, parent)
{
}

int PlayPenaltyOur::enterCondition()
{
    if(wm->cmgs.ourPenaltyKick())
        return 100;
    else
        return 0;
}

void PlayPenaltyOur::execute()
{

}
