#ifndef TACTICTECHNICAL_H
#define TACTICTECHNICAL_H

#include "tactic.h"

class TacticTechnical : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTechnical(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

private:

};

#endif // TACTICTECHNICAL_H
