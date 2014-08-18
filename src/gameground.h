#ifndef GAMEGROUND_H
#define GAMEGROUND_H

#include <QObject>
#include "cameraoutput.h"

class GameGround : public QObject
{
    Q_OBJECT
public:
    explicit GameGround(QObject *parent = 0);
    void setMission(int mission);
    void setEndPoint(Vector2D input);
    void setFirstRegion(Rect2D input);
    void setSecondRegion(Rect2D input);

    CameraOutput output;
private:
    int mission;
    Rect2D region[2];
    Vector2D endPoint;

signals:

public slots:

};

#endif // GAMEGROUND_H
