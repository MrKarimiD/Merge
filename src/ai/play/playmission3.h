#ifndef PLAYMISSION3_H
#define PLAYMISSION3_H

#include "play.h"

class PlayMission3 : public Play
{
    Q_OBJECT
public:
    explicit PlayMission3(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    TacticPush2Goal* tAttacker;
    TacticSharifDefence* tDefender;

};
#endif // PLAYMISSION3_H
