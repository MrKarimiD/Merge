#ifndef TACTICBALLTRACKER_H
#define TACTICBALLTRACKER_H

#include "tactic.h"

class TacticBallTracker : public Tactic
{
    Q_OBJECT
public:
    explicit TacticBallTracker(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

private:

};

#endif // TACTICBALLTRACKER_H
