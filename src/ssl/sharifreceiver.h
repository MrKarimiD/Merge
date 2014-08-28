#ifndef SHARIFRECEIVER_H
#define SHARIFRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class SharifReceiver : public QObject
{
    Q_OBJECT
public:
    explicit SharifReceiver(QString ip, int port, QObject *parent = 0);

private:
    QUdpSocket _udpsocket;
    bool _isStarted;

signals:
    void newSharifPacket(QByteArray data, QString ip, int port);

public slots:
    void Start();
    void Stop();

private slots:
    void readPendingDatagrams();


};

#endif // SHARIFRECEIVER_H
