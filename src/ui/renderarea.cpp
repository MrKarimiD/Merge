#include "renderarea.h"

RenderArea::RenderArea(Soccer* sc) :
    QWidget()
{
    _sc = sc;
    brush_field = new QBrush(QPixmap(":/resources/images/Field.jpg"));
    brush_ball = new QBrush(QColor::fromRgb(255,200,0),Qt::SolidPattern);
    brush_yrobot = new QBrush(QColor::fromRgb(255,255,0),Qt::SolidPattern);
    brush_brobot = new QBrush(QColor::fromRgb(50,50,255),Qt::SolidPattern);
    brush_region1 = new QBrush(QColor::fromRgb(204,0,0),Qt::SolidPattern);
    brush_region2 = new QBrush(QColor::fromRgb(204,255,255),Qt::SolidPattern);
    brush_holes = new QBrush(QColor::fromRgb(204,204,204),Qt::SolidPattern);
    brush_shape = new QBrush(QColor::fromRgb(0,255,0),Qt::SolidPattern);
    _timer.start(40);
    connect(&_timer,SIGNAL(timeout()), this, SLOT(refresh()));
}

void RenderArea::refresh()
{
    update();
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Settings
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Draw Field
    painter.setBrush(*brush_field);
    painter.drawRect(0,0,740,540);

    //      // //    Draw circle FOR MISION III

    painter.setBrush(*brush_field);
    painter.drawRect(CENTER_X-25,CENTER_Y-175,350,350);


    painter.setPen(QColor::fromRgb(0,0,0));
    painter.drawEllipse(QPoint(150+CENTER_X,0+CENTER_Y),175,175);//200/2,200/2);
    painter.setPen(QColor::fromRgb(204,51,0));
    painter.drawEllipse(QPoint(150+CENTER_X,0+CENTER_Y),175/2,175/2);
    // //               H O L E S
    painter.setBrush(*brush_holes);
    //painter.setPen(QColor::fromRgb(0,0,0));
    painter.drawEllipse(QPoint(150+CENTER_X,0+CENTER_Y+170/4),25/2,25/2);

    //painter.setBrush(*brush_holes);
    //painter.setPen(QColor::fromRgb(0,0,0));
    painter.drawEllipse(QPoint(150+CENTER_X,0+CENTER_Y-170/4),25/2,25/2);


    // FPS
    painter.drawText(20,20,QString::number(_fps.FPS()));

    painter.translate(CENTER_X,CENTER_Y);

    // -------------------- Sharif Cup 2014 ---------------------\\
//       // //   Draw Regions FOR MISION I

    painter.setBrush(*brush_region1);
    painter.drawRect(-100,150,100,50);//270,70,100,50);
    painter.setPen(QColor::fromRgb(0,0,0));
    painter.drawText(-65,180,"Reg 1");

    painter.setBrush(*brush_region2);
    painter.drawRect(-100,-200,100,50);
    painter.setPen(QColor::fromRgb(0,0,0));
    painter.drawText(-65,-170,"Reg 2");

//      // //    Draw Line FOR MISION II

//    painter.drawLine(-50, 200,0,0);
//    painter.drawLine(-50,-200,0,0);


//      // //    Draw Line FOR MISION III




    // CENTERofField = (0,0)
    // Y_TOP_EDGE  =       Y_DOWN_EDGE = 470
    // X_LEFT_EDGE = 70      X_RIGHT_EDGE =670

    //-------------------- End Sharif Cup 2014 -------------------//

    // Draw Robots
    painter.setPen(QColor::fromRgb(0,0,0));

    painter.setBrush(*brush_yrobot);
    for(int i=0;i<12;i++)
        if(_sc->wm->oppRobot[i].isValid)
        {
            painter.drawChord(_sc->wm->oppRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->oppRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(_sc->wm->oppRobot[i].pos.dir));
            painter.drawText(_sc->wm->oppRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->oppRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,QString::number(i));
        }

    painter.setBrush(*brush_brobot);
    for(int i=0;i<12;i++)
        if(_sc->wm->ourRobot[i].isValid)
        {
            painter.drawChord(_sc->wm->ourRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->ourRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(_sc->wm->ourRobot[i].pos.dir));
            painter.drawText(_sc->wm->ourRobot[i].pos.loc.x/WORLD_SCALE-ROBOT_R,-_sc->wm->ourRobot[i].pos.loc.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,QString::number(i));
        }

    // Draw Ball
    if(_sc->wm->ball.isValid)
    {
        painter.setPen(QColor::fromRgb(200,100,0));
        painter.setBrush(*brush_ball);
        painter.drawEllipse(QPoint(_sc->wm->ball.pos.loc.x/WORLD_SCALE,-_sc->wm->ball.pos.loc.y/WORLD_SCALE),BALL_R,BALL_R);
    }

    qDebug()<<"NUMBER:"<<_sc->wm->shapes4Region1.size();
    for(int i=0;i<_sc->wm->shapes4Region1.size();i++)
    {
        painter.setPen(QColor::fromRgb(150,100,0));
        painter.setBrush(*brush_shape);
        //qDebug()<<"robot"<<i<<_sc->wm->shapes4Region1.at(i).position.x/WORLD_SCALE<<","<<_sc->wm->shapes4Region1.at(i).position.y/WORLD_SCALE;
        painter.drawEllipse(QPoint(_sc->wm->shapes4Region1.at(i).position.x/WORLD_SCALE,_sc->wm->shapes4Region1.at(i).position.y/WORLD_SCALE),BALL_R,BALL_R);
    }
    // TEST

    //painter.drawChord(100-ROBOT_R,100-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(0));
    //painter.drawText(100-ROBOT_R,100-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,"8");

    _fps.Pulse();
}
