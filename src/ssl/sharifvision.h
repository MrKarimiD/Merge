#ifndef SHARIFVISION_H
#define SHARIFVISION_H

#include <QObject>
#include <QTime>

#include "messages_robocup_ssl_wrapper.pb.h"
#include "base.h"
#include "constants.h"
#include "sslreceiver.h"
#include "geom.h"
#include "util.h"
#include "worldmodel.h"
#include <Prototype_Messages/GameGround.pb.h>
#include "shape.h"

class SharifVision : public SSLReceiver
{
    Q_OBJECT

public:
    explicit SharifVision(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, WorldModel *wm, QObject *parent = 0);
    int getFPS(int c);

private:
    QTime _time;
    TeamColorType _color;
    TeamSideType _side;
    CameraConfigType _camera;
    FPSCounter _fpscam0;
    FPSCounter _fpscam1;
    WorldModel *_wm;

    void parseMyPacket(outputPacket packet);

private slots:
    void readPendingPacket(QByteArray data, QString ip, int port);
};

#endif // SHARIFVISION_H
