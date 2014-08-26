#include "sharifvision.h"

SharifVision::SharifVision(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, WorldModel *wm, QObject *parent) :
    SSLReceiver(ip,port,parent),
    _color(color),
    _side(side),
    _camera(camera),
    _fpscam0(parent),
    _fpscam1(parent),
    _wm(wm)
{
    _time.start();

    connect(this, SIGNAL(newReceivedPacket(QByteArray,QString,int)), this, SLOT(readPendingPacket(QByteArray,QString,int)));

    // Log
    qDebug() << "SharifVision Initialization...";
    qDebug() << "IP: " << ip;
    qDebug() << "Port: " << port;
}

int SharifVision::getFPS(int c)
{
    if(c == 0) return _fpscam0.FPS();
    if(c == 1) return _fpscam1.FPS();
    return 0;
}

void SharifVision::readPendingPacket(QByteArray data, QString ip, int port)
{
    qDebug()<<data.size();
    outputPacket message;
    if(!message.ParseFromArray(data.data(),data.size()))
    {
        qDebug()<<"Parse failed";
    }

    if(message.IsInitialized())
    {
        parseMyPacket(message);
    }
    else
    {
        qDebug()<<QString::fromStdString(message.InitializationErrorString());
    }
}

void SharifVision::parseMyPacket(outputPacket packet)
{
    if(packet.type() == 0)
    {
        qDebug()<<"Initial Message Received...";
        _wm->mission = packet.mission();
        _wm->numberOfShapes = packet.numberofshape();

        if(packet.mission() == 1)
        {
            Vector2D tl1(packet.mission1_region1_tl_x(),packet.mission1_region1_tl_y());
            Vector2D br1(packet.mission1_region1_br_x(),packet.mission1_region1_br_y());
            Rect2D region1(tl1,br1);

            Vector2D tl2(packet.mission1_region2_tl_x(),packet.mission1_region2_tl_y());
            Vector2D br2(packet.mission1_region2_br_x(),packet.mission1_region2_br_y());
            Rect2D region2(tl2,br2);

            _wm->region1 = region1;
            _wm->region2 = region2;

            Vector2D end(packet.mission1_end_x(),packet.mission1_end_y());
            _wm->endPoint = end;
        }
        else if(packet.mission() == 2)
        {
            //Adding lines

            Vector2D end(packet.mission2_end_x(),packet.mission2_end_y());
            _wm->endPoint = end;
        }
        else if(packet.mission() == 3)
        {
            _wm->isAttacker = packet.mission3_isattacker();

            Vector2D borderCenter(packet.mission3_circularborde_x(),packet.mission3_circularborde_y());
            Circle2D cirBorder(borderCenter,CIRCULARBORDERRADIUS);
            _wm->circularBorder = cirBorder;

            Vector2D goal1_center(packet.mission3_goal1_x(),packet.mission3_goal1_y());
            Circle2D goal1(goal1_center,GOALRADIUS);
            _wm->goal1 = goal1;

            Vector2D goal2_center(packet.mission3_goal2_x(),packet.mission3_goal2_y());
            Circle2D goal2(goal2_center,GOALRADIUS);
            _wm->goal2 = goal2;
        }

        qDebug()<<"World Model Initialize";
    }
    else if(packet.type() == 1)
    {
        _wm->numberOfShapes = packet.numberofshape();
        _wm->mission = packet.mission();
        Shape temp;
        outputPacket_shape op;
        for(int i=0;i<packet.shapes_size();i++)
        {
            op = packet.shapes(i);
            string color = op.color();
            string type = op.type();
            Vector2D pos(op.position_x(),op.position_y());
            double rad = op.radios();
            temp.set(pos,rad,color,type);
        }
        //_wm->shapes4Region1
    }
}
