/* 
 * File:   Triangle.cpp
 * Author: corsaro
 * 
 * Created on July 13, 2009, 1:57 AM
 */

#include <qt4/QtGui/qpainter.h>

#include "Triangle.hpp"

Triangle::Triangle(const QRect& bounds,
               boost::shared_ptr<ShapeDynamics> dynamics,
               const QPen& pen,
               const QBrush& brush)
    :   Shape(bounds, pen, brush),
        dynamics_(dynamics)
{
    QPoint p1(bounds.width()/2, 0);
    QPoint p2(0, bounds.width());
    QPoint p3(bounds.width(), bounds.width());

    triangle_ << p1 << p2 << p3;
}

Triangle::~Triangle() {
}

void
Triangle::update() {
    dynamics_->simulate();
}

void
Triangle::paint(QPainter& painter) {
    painter.setBrush(brush_);
    painter.setPen(pen_);
   painter.translate(dynamics_->getPosition());
    painter.drawPolygon(triangle_);
    painter.translate(-(dynamics_->getPosition().x()),
                      -(dynamics_->getPosition().y()));


}

