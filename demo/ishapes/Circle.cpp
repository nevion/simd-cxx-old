/* 
 * File:   Circle.cpp
 * Author: corsaro
 * 
 * Created on July 12, 2009, 10:55 PM
 */

#include <QtGui/qpainter.h>
#include <vector>
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
    std::vector<QPoint> plist = dynamics_->getPositionList();
    std::vector<QPoint>::iterator idx = plist.begin();
    while (idx != plist.end()) {
      painter.drawEllipse(idx->x(),
			  idx->y(),
			  bounds_.width(),
			  bounds_.height());
      ++idx;
    }
    /*
     painter.drawEllipse(dynamics_->getPosition().x(),
                        dynamics_->getPosition().y(),
                        bounds_.width(),
                        bounds_.height());
    */
}

Circle::~Circle() {
}

