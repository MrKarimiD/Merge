#include "sharifreceiver.h"

SharifReceiver::SharifReceiver(QString ip, int port, QObject *parent) :
    _udpsocket(this),
    _isStarted(false)
{
    // udp socket setup
    bool result;
    result=_udpsocket.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ReuseAddressHint);
    if(!result) qDebug() << _udpsocket.errorString();
    result=_udpsocket.joinMulticastGroup(QHostAddress(ip));
    if(!result) qDebug() << _udpsocket.errorString();
}

void SharifReceiver::Start()
{
    if(_isStarted) return;
    connect(&_udpsocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    _isStarted=true;
}

void SharifReceiver::Stop()
{
    if(!_isStarted) return;
    disconnect(&_udpsocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    _isStarted=false;
}

void SharifReceiver::readPendingDatagrams()
{
    while (_udpsocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udpsocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        _udpsocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        newSharifPacket(datagram,sender.toString(),senderPort);
    }
}

