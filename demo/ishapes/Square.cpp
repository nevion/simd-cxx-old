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
               const QBrush& brush,
               bool targeted)
    :   Shape(bounds, pen, brush, targeted),
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
    QBrush brush( QColor(0x33, 0x33, 0x33), Qt::SolidPattern);
    while (idx != plist.end()) {
      painter.drawRect(idx->x(),
		       idx->y(),
		       bounds_.width(),
		       bounds_.height());
      if (targeted_) {
        painter.setBrush(brush);
        int X0 = idx->x() + (bounds_.width()/2);
        int Y0 = idx->y() + (bounds_.height()/2);
        int W = bounds_.width()/3;
        int H = bounds_.height()/3;
        painter.setBrush(brush);
        painter.drawRect(X0 - W/2,
                            Y0 - H/2,
                            W,
                            H);
        painter.setBrush(brush_);
      }
      ++idx;
    }
}

Square::~Square() {
}

