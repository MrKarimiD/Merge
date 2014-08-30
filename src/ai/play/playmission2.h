#ifndef PLAYMISSION2_H
#define PLAYMISSION2_H

#include "play.h"

class PlayMission2 : public Play
{
    Q_OBJECT
public:
    explicit PlayMission2(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    TacticConfront* tConfront;

};

#endif // PLAYMISSION2_H
