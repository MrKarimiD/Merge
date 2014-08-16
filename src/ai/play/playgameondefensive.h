#ifndef PLAYGAMEONDEFENSIVE_H
#define PLAYGAMEONDEFENSIVE_H

#include "play.h"

class PlayGameOnDefensive : public Play
{
    Q_OBJECT
public:
    explicit PlayGameOnDefensive(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:

};

#endif // PLAYGAMEONDEFENSIVE_H
