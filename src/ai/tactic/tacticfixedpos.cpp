#include "tacticfixedpos.h"

TacticFixedPos::TacticFixedPos(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticFixedPos", worldmodel, parent)
{
}

RobotCommand TacticFixedPos::getCommand()
{
}

