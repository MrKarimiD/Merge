#include "playmission1.h"

PlayMission1::PlayMission1(WorldModel *worldmodel, QObject *parent) :
    Play("PlayMission1", worldmodel, parent)
{
   tTransfer = new TacticTransferObject(wm);
}

int PlayMission1::enterCondition()
{
    if(wm->mission == 1)
        return 100000;
    else
        return 0;
}

void PlayMission1::execute()
{
    tactics[3] = tTransfer;
    return ;

}
