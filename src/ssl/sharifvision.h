#ifndef SHARIFVISION_H
#define SHARIFVISION_H

#include "sharifreceiver.h"
#include "worldmodel.h"
#include <Prototype_Messages/GameGround.pb.h>

class SharifVision : public SharifReceiver
{
    Q_OBJECT
public:
    SharifVision(QString ip, int port, WorldModel *wm, QObject *parent = 0);

private:
    QTime _time;
    WorldModel *_wm;

    void parse(outputPacket &msg);

private slots:
    void readPendingPacket(QByteArray data, QString ip, int port);
};

#endif // SHARIFVISION_H
