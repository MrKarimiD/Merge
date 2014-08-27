#ifndef SHARIFVISION_H
#define SHARIFVISION_H

#include "sslreceiver.h"
#include "worldmodel.h"
#include <Prototype_Messages/GameGround.pb.h>

class SharifVision : public SSLReceiver
{
    Q_OBJECT

public:
    explicit SharifVision(QString ip, int port, WorldModel *wm, QObject *parent = 0);
    int getFPS(int c);

private:
    QTime _time;
    FPSCounter _fpscam0;
    FPSCounter _fpscam1;
    WorldModel *_wm;

    void parse(outputPacket &msg);

private slots:
    void readPendingPacket(QByteArray data, QString ip, int port);


};

#endif // SHARIFVISION_H
