#ifndef PLAYKICKOFFOUR_H
#define PLAYKICKOFFOUR_H

#include "play.h"

class PlayKickoffOur : public Play
{
    Q_OBJECT
public:
    explicit PlayKickoffOur(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

protected:

};
#endif // PLAYKICKOFFOUR_H
