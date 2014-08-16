#include "tacticblocker.h"

TacticBlocker::TacticBlocker(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticBlocker", worldmodel, parent)
{
}

RobotCommand TacticBlocker::getCommand()
{

}
