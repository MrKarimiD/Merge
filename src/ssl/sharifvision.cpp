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
    if(msg.type() == 0)
    {
        _wm->mission = msg.mission();
        _wm->numberOfShapes = msg.numberofshape();

        if(msg.mission() == 1)
        {
            Vector2D tl1(msg.mission1_region1_tl_x(),msg.mission1_region1_tl_y());
            Vector2D br1(msg.mission1_region1_br_x(),msg.mission1_region1_br_y());
            Rect2D region1(tl1,br1);

            Vector2D tl2(msg.mission1_region2_tl_x(),msg.mission1_region2_tl_y());
            Vector2D br2(msg.mission1_region2_br_x(),msg.mission1_region2_br_y());
            Rect2D region2(tl2,br2);

            _wm->region1 = region1;
            _wm->region2 = region2;

            Vector2D end(msg.mission1_end_x(),msg.mission1_end_y());
            _wm->endPoint = end;
        }
        else if(msg.mission() == 2)
        {
            //Adding lines

            Vector2D end(msg.mission2_end_x(),msg.mission2_end_y());
            _wm->endPoint = end;
        }
        else if(msg.mission() == 3)
        {
            _wm->isAttacker = msg.mission3_isattacker();

            Vector2D borderCenter(msg.mission3_circularborde_x(),msg.mission3_circularborde_y());
            Circle2D cirBorder(borderCenter,1750);
            _wm->circularBorder = cirBorder;

            Vector2D goal1_center(msg.mission3_goal1_x(),msg.mission3_goal1_y());
            Circle2D goal1(goal1_center,250);
            _wm->goal1 = goal1;

            Vector2D goal2_center(msg.mission3_goal2_x(),msg.mission3_goal2_y());
            Circle2D goal2(goal2_center,250);
            _wm->goal2 = goal2;
        }

        qDebug()<<"World Model Initialize";
    }
    else if(msg.type() == 1)
    {
        shapes.clear();
       _wm->clean();
        qDebug()<<"Data Message Received...";

        _wm->numberOfShapes = msg.numberofshape();
        _wm->mission = msg.mission();
        Shape temp;
        outputPacket_shape op;

        for(int i=0;i<msg.shapes_size();i++)
        {
            op = msg.shapes(i);
            string color = op.color();
            string type = op.type();
            Vector2D pos(op.position_x(),op.position_y());
            double rad = op.radios();
            temp.set(pos,rad,color,type);
            shapes.push_back(temp);
        }

        if(msg.mission() == 1)
        {
            for(int i=0;i<shapes.size();i++)
            {
                addToRegion1(shapes.at(i));
            }
        qDebug()<<"sharif vis:"<<_wm->shapes4Region1.size();
        }
        else if(msg.mission() == 2)
        {

        }
        else if(msg.mission() == 3)
        {

        }

        qDebug()<<"World Model Updated";
    }

}

void SharifVision::addToRegion1(Shape input)
{
    if(true/**/)
    {
        _wm->shapes4Region1.push_back(input);
    }

}

void SharifVision::addToRegion2(Shape input)
{
    if(true/**/)
    {
        _wm->shapes4Region2.push_back(input);
    }
}

void SharifVision::readPendingPacket(QByteArray data, QString ip, int port)
{
    outputPacket message;
    if(!message.ParseFromArray(data.data(),data.size()))
    {
        qDebug()<<"Parse failed";
    }

    if(message.IsInitialized())
    {
        parse(message);
    }
    else
    {
        qDebug()<<QString::fromStdString(message.InitializationErrorString());
    }
}
