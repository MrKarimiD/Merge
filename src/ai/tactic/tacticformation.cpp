#include "tacticformation.h"

TacticFormation::TacticFormation(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticFormation", worldmodel, parent)
{
}

RobotCommand TacticFormation::getCommand()
{
}
