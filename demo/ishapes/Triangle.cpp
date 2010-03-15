/* 
 * File:   Triangle.cpp
 * Author: corsaro
 * 
 * Created on July 13, 2009, 1:57 AM
 */

#include <QtGui/qpainter.h>

#include "Triangle.hpp"

Triangle::Triangle(const QRect& bounds,
               boost::shared_ptr<ShapeDynamics> dynamics,
               const QPen& pen,
               const QBrush& brush)
    :   Shape(bounds, pen, brush),
        dynamics_(dynamics)
{
    QPoint p1(bounds_.width()/2, 0);
    QPoint p2(0, bounds_.width());
    QPoint p3(bounds_.width(), bounds_.width());

    triangle_ << p1 << p2 << p3;
}

Triangle::~Triangle() {
}

void 
Triangle::setBounds(const QRect& bounds)
{
  bounds_ = bounds;
  QPoint p1(bounds_.width()/2, 0);
  QPoint p2(0, bounds_.width());
  QPoint p3(bounds_.width(), bounds_.width());
  
  QPolygon triangle;
  triangle << p1 << p2 << p3;
  triangle_ = triangle;
}
void
Triangle::update() {
    dynamics_->simulate();
}

void
Triangle::paint(QPainter& painter) {
    painter.setBrush(brush_);
    painter.setPen(pen_);
    /*
    painter.translate(dynamics_->getPosition());
    painter.drawPolygon(triangle_);
    painter.translate(-(dynamics_->getPosition().x()),
                      -(dynamics_->getPosition().y()));

    */

    std::vector<QPoint> plist = dynamics_->getPositionList();
    std::vector<QPoint>::iterator idx = plist.begin();
    while (idx != plist.end()) {
      painter.translate(*idx);
      painter.drawPolygon(triangle_);
      painter.translate(-(idx->x()),
			-(idx->y()));
      
      ++idx;
    }
}

