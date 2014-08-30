#ifndef PLAYMISSION1_H
#define PLAYMISSION1_H

#include "play.h"

class PlayMission1 : public Play
{
    Q_OBJECT
public:
    explicit PlayMission1(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    TacticTransferObject* tTransfer;

};

#endif // PLAYMISSION1_H
