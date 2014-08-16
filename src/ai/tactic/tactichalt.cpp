#include "tactichalt.h"

TacticHalt::TacticHalt(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticHalt", worldmodel, parent)
{
}

RobotCommand TacticHalt::getCommand()
{
}
