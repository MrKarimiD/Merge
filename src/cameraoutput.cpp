#include "cameraoutput.h"

CameraOutput::CameraOutput(QObject *parent) :
    QObject(parent)
{
}

void CameraOutput::addShape(Vector2D pos, double r, QString color, QString type)
{
    qDebug()<<"1";
    Shape *temp=new Shape();
    qDebug()<<"2";
    temp->set(pos,r,color,type);
    qDebug()<<"3";
    shapes.insert(nummberOfShapes,temp);
    qDebug()<<"4";
    nummberOfShapes++;
}

void CameraOutput::clearShapeList()
{
    shapes.clear();
    nummberOfShapes=0;
}
