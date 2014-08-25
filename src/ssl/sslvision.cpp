#include "sslvision.h"

SSLVision::SSLVision(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, WorldModel *wm, QObject *parent) :
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
    connect(this, SIGNAL(newReceivedPacket2(QByteArray,QString,int)), this, SLOT(readPendingPacket2(QByteArray,QString,int)));

    // Log
    qDebug() << "SSLVision Initialization...";
    qDebug() << "IP: " << ip;
    qDebug() << "Port: " << port;
    qDebug() << "Color: " << (color==COLOR_BLUE?"Blue":"Yellow");
    qDebug() << "Side: " << (side==SIDE_RIGHT?"Right":"Left");
    qDebug() << "Camera: " << ((int)camera);
}

int SSLVision::getFPS(int c)
{
    if(c == 0) return _fpscam0.FPS();
    if(c == 1) return _fpscam1.FPS();
    return 0;
}

void SSLVision::readPendingPacket(QByteArray data, QString ip, int port)
{
   // check for server ip (& port)
    if(ip=="" && port==0) return;

    // unpack sslvision packet
    SSL_WrapperPacket packet;
    bool ans=packet.ParseFromArray(data.data(), data.size());
    if(!ans) return;
    if(packet.has_detection()==false) return;
    SSL_DetectionFrame pck = packet.detection();

    // parse detection frame
    parse(pck);
}

void SSLVision::readPendingPacket2(QByteArray data, QString ip, int port)
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

void SSLVision::parse(SSL_DetectionFrame &pck)
{

    // update camera fps
    int cid = pck.camera_id();
    if(cid == 0) _fpscam0.Pulse();
    if(cid == 1) _fpscam1.Pulse();

    switch(_camera)
    {
    case CAMERA_BOTH:
        break;
    case CAMERA_0:
        if (cid==1) return;
        break;
    case CAMERA_1:
        if (cid==0) return;
        break;
    case CAMERA_NONE:
    default:
        return;
    }

    // update vision frame
    //_vframe[cid].frame_number =  pck.frame_number();

    vector<Position> pt;

    // Team side Coefficient
    float ourSide = (_side == SIDE_RIGHT)? -1.0f : 1.0f;
    double time = _time.elapsed(); //pck.t_capture();

    // insert balls
    int max_balls=min(VOBJ_MAX_NUM, pck.balls_size());
    for(int i=0; i<max_balls; ++i)
    {
        auto b = pck.balls(i);
        if(b.has_confidence() && b.has_x() && b.has_y())
            if(b.confidence() > MIN_CONF && fabs(b.x()) < FIELD_MAX_X && fabs(b.y()) < FIELD_MAX_Y)
            {
                Position tp;
                tp.loc = Vector2D(b.x()*ourSide, b.y()*ourSide);
                pt.push_back(tp);
            }
    }
    _wm->ball.seenAt(pt, time, cid);

    if(_color == COLOR_BLUE)
    {
        APPEND_ROBOTS(blue, our);
        APPEND_ROBOTS(yellow, opp);
    }
    else // _color == COLOR_YELLOW
    {
        APPEND_ROBOTS(yellow, our);
        APPEND_ROBOTS(blue, opp);
    }

}

void SSLVision::parseMyPacket(outputPacket packet)
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
}
