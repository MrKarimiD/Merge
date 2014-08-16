#include "playstop.h"

PlayStop::PlayStop(WorldModel *worldmodel, QObject *parent) :
    Play("PlayStop", worldmodel, parent)
{

}

int PlayStop::enterCondition()
{
    if(wm->gs == STATE_Stop)
        return 100;
    else if(wm->cmgs.canMove() && wm->cmgs.gameOn()==false && wm->cmgs.allowedNearBall()==false)
        return 10;
    else
        return 0;
}

void PlayStop::execute()
{

}
