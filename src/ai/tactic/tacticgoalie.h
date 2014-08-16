#ifndef TACTICGOALIE_H
#define TACTICGOALIE_H

#include "tactic.h"

class TacticGoalie : public Tactic
{
    Q_OBJECT
public:
    explicit TacticGoalie(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

};

#endif // TACTICGOALIE_H
