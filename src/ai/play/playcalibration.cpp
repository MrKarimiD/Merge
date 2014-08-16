#include "playcalibration.h"

PlayCalibration::PlayCalibration(WorldModel *worldmodel, QObject *parent) :
    Play("PlayCalibration", worldmodel, parent)
{
}

int PlayCalibration::enterCondition()
{
    return 0;
}

void PlayCalibration::execute()
{

}
