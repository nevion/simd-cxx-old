/* 
 * File:   Circle.cpp
 * Author: corsaro
 * 
 * Created on July 12, 2009, 10:55 PM
 */

#include <qt4/QtGui/qpainter.h>

#include "Circle.hpp"


Circle::Circle(const QRect& bounds,
               boost::shared_ptr<ShapeDynamics> dynamics,
               const QPen& pen,
               const QBrush& brush)
    :   Shape(bounds, pen, brush),
        dynamics_(dynamics)
{ }

void
Circle::update() {
    dynamics_->simulate();
}

void
Circle::paint(QPainter& painter) {
    painter.setBrush(brush_);
    painter.setPen(pen_);
    painter.drawEllipse(dynamics_->getPosition().x(),
                        dynamics_->getPosition().y(),
                        bounds_.width(),
                        bounds_.height());
}

Circle::~Circle() {
}

