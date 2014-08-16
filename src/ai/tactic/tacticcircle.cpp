#include "tacticcircle.h"

TacticCircle::TacticCircle(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticCircle", worldmodel, parent)
{
}

RobotCommand TacticCircle::getCommand()
{

}
