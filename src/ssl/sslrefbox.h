#ifndef SSLREFBOX_H
#define SSLREFBOX_H

#include "commands.h"   //from sslrefbox
#include "game_state.h" //from sslrefbox client
#include "ref_protocol.h"   //referee:protocol

#include "sslreceiver.h"
#include "base.h"
#include "worldmodel.h"

class SSLRefBox : public SSLReceiver
{
    Q_OBJECT

public:
    explicit SSLRefBox(QString ip, int port, TeamColorType color, float ball_min, WorldModel* wm, QObject *parent = 0);
    bool paused;
    GameStatePacket refgs;

protected:
    int _cmdcounter;
    TeamColorType _color;
    unsigned char _lastCMDCounter;
    float _ball_min;
    WorldModel* _wm;
    Position _lastBallpos;
    void parse(GameStatePacket pck);
    void updategs(char cmd, bool ball_moved);

signals:
    void newRefreeCommand();

public slots:


protected slots:
    virtual void readPendingPacket(QByteArray data, QString ip, int port);

};

#endif // SSLREFBOX_H
