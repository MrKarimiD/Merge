#ifndef TACTICCIRCLE_H
#define TACTICCIRCLE_H

#include "tactic.h"

class TacticCircle : public Tactic
{
    Q_OBJECT
public:
    explicit TacticCircle(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

private:

};

#endif // TACTICCIRCLE_H
