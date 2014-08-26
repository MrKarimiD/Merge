#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include "geom.h"
#include "opencv2/imgproc/imgproc.hpp"

class Shape : public QObject
{
    Q_OBJECT
public:
    explicit Shape(QObject *parent = 0);
    void set(Vector2D position,double roundedRadios,std::string color,std::string type);
private:
    Vector2D position;
    double roundedRadios;
    std::string color;
    std::string type;

signals:

public slots:

};

#endif // SHAPE_H
