#include "playmission2.h"

PlayMission2::PlayMission2(WorldModel *worldmodel, QObject *parent) :
    Play("PlayMission2", worldmodel, parent)
{
   tConfront = new TacticConfront(wm);
}

int PlayMission2::enterCondition()
{
    if(wm->mission == 2)
        return 100000;
    else
        return 0;
}

void PlayMission2::execute()
{
    tactics[3] = tConfront;
    return ;

}
