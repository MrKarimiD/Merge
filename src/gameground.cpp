#include "gameground.h"

GameGround::GameGround(QObject *parent) :
    QObject(parent)
{
}

void GameGround::setMission(int mission)
{
    this->mission=mission;
}

void GameGround::setEndPoint(Vector2D input)
{
    this->endPoint=input;
}

void GameGround::setFirstRegion(Rect2D input)
{
    this->region[0]=input;
}

void GameGround::setSecondRegion(Rect2D input)
{
    this->region[1]=input;
}
