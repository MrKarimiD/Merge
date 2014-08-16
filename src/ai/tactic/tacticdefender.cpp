#include "tacticdefender.h"

TacticDefender::TacticDefender(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticDefender", worldmodel, parent)
{

}

RobotCommand TacticDefender::getCommand()
{
}
