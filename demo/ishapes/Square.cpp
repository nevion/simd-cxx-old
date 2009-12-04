/* 
 * File:   Square.cpp
 * Author: corsaro
 * 
 * Created on July 13, 2009, 1:40 AM
 */

#include "Square.hpp"
#include <iostream>

Square::Square(const QRect& bounds,
               boost::shared_ptr<ShapeDynamics> dynamics,
               const QPen& pen,
               const QBrush& brush)
    :   Shape(bounds, pen, brush),
        dynamics_(dynamics)
{ }

void
Square::update() {
    // std::cout << ">>SQUARE::simulate" << std::endl;
    dynamics_->simulate();
}

void
Square::paint(QPainter& painter) {

    painter.setBrush(brush_);
    painter.setPen(pen_);
    /*
    painter.drawRect(dynamics_->getPosition().x(),
                     dynamics_->getPosition().y(),
                     bounds_.width(),
                     bounds_.height());
    */
   // std::cout << "SQUARE::paint" << std::endl;
    std::vector<QPoint> plist = dynamics_->getPositionList();
    std::vector<QPoint>::iterator idx = plist.begin();
    while (idx != plist.end()) {
      painter.drawRect(idx->x(),
		       idx->y(),
		       bounds_.width(),
		       bounds_.height());
      ++idx;
    }
}

Square::~Square() {
}

