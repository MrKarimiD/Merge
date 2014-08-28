#include "sharifvision.h"

SharifVision::SharifVision(QString ip, int port, WorldModel *wm, QObject *parent) :
   SharifReceiver(ip,port,parent),
   _wm(wm)
{
   _time.start();
   connect(this, SIGNAL(newSharifPacket(QByteArray,QString,int)), this, SLOT(readPendingPacket(QByteArray,QString,int)));

   // Log
   qDebug() << "SharifVision Initialization...";
   qDebug() << "IP: " << ip;
   qDebug() << "Port: " << port;
}

void SharifVision::parse(outputPacket &msg)
{

}

void SharifVision::readPendingPacket(QByteArray data, QString ip, int port)
{
    qDebug() << "sharif size:"<<data.size();
}
