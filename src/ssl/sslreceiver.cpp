#include "sslreceiver.h"

SSLReceiver::SSLReceiver(QString ip, int port, QObject *parent) :
    FPSCounter(parent),
    _udpsocket(this),
    _isStarted(false)
{
    // udp socket setup
    bool result;
    result=_udpsocket.bind(QHostAddress::Any, port, QUdpSocket::ReuseAddressHint);
    if(!result) qDebug() << _udpsocket.errorString();
    result=_udpsocket.joinMulticastGroup(QHostAddress(ip));
    if(!result) qDebug() << _udpsocket.errorString();

    result=_udpsocket2.bind(QHostAddress::Any, 45454, QUdpSocket::ShareAddress);
    if(!result) qDebug() << _udpsocket2.errorString();
    result=_udpsocket2.joinMulticastGroup(QHostAddress("239.255.43.21"));
    if(!result) qDebug() << _udpsocket2.errorString();
}

void SSLReceiver::Start()
{
    if(_isStarted) return;
    connect(&_udpsocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    connect(&_udpsocket2, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams2()));
    _isStarted=true;
}

void SSLReceiver::Stop()
{
    if(!_isStarted) return;
    disconnect(&_udpsocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    disconnect(&_udpsocket2, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams2()));
    _isStarted=false;
}

void SSLReceiver::readPendingDatagrams()
{
    while (_udpsocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udpsocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        _udpsocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        newReceivedPacket(datagram,sender.toString(),senderPort);
        Pulse();
    }
}

void SSLReceiver::readPendingDatagrams2()
{
    while (_udpsocket2.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udpsocket2.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        _udpsocket2.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        newReceivedPacket2(datagram,sender.toString(),senderPort);
        //Pulse();
    }
}

