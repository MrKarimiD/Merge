#include "playtest2.h"

PlayTest2::PlayTest2(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest2", worldmodel, parent)
{

}

int PlayTest2::enterCondition()
{
    return 0;
}

void PlayTest2::execute()
{

}

