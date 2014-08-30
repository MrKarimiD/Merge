#include "playmission3.h"

PlayMission3::PlayMission3(WorldModel *worldmodel, QObject *parent) :
    Play("PlayMission3", worldmodel, parent)
{
   tAttacker = new TacticPush2Goal(wm);
   tDefender = new TacticSharifDefence(wm);
}

int PlayMission3::enterCondition()
{
    if(wm->mission == 3)
        return 100000;
    else
        return 0;
}

void PlayMission3::execute()
{
    if(wm->isAttacker)
        tactics[0] = tAttacker;
    else
        tactics[0] = tDefender;
    return ;

}
