/* 
 * File:   ShapesWidget.cpp
 * Author: corsaro
 * 
 * Created on July 12, 2009, 7:23 PM
 */

#include <iostream>
#include <QtGui>
#include <boost/shared_ptr.hpp>
#include "ShapesWidget.hpp"


ShapesWidget::ShapesWidget(QWidget *parent)
: QWidget(parent)
{
    this->setBackgroundRole(QPalette::Base);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

ShapesWidget::~ShapesWidget() {
}

void
ShapesWidget::addShape(boost::shared_ptr<Shape> shape) {
    shapeList_.push_back(shape);
}

void
ShapesWidget::nextAnimationFrame() {
    this->update();

    ShapeList::iterator index = shapeList_.begin();
    while (index != shapeList_.end()) {
        (*index)->update();
        ++index;
    }
}

void
ShapesWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    ShapeList::iterator index = shapeList_.begin();
    while (index != shapeList_.end()) {
        (*index)->paint(painter);
        ++index;
    }
    /*
    int x = 10;
    int y = 10;
    int diameter = 100;

    QPainterPath ellipsePath;
    ellipsePath.addEllipse(x, y, diameter, diameter);
    
    QPoint p1(diameter/2, 0);
    QPoint p2(0, diameter);
    QPoint p3(diameter, diameter);

    QPolygon triangle;
    triangle << p1 << p2 << p3;
    QPainterPath trianglePath;
    trianglePath.addPolygon(triangle);

    QPainter painter(this);
    QBrush brush(Qt::red);
    QPen pen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    // painter.drawRect(diameter, diameter, diameter, diameter);
    // painter.drawPath(ellipsePath);
    painter.drawPath(ellipsePath);
    painter.drawEllipse(100, 100, 200, 200);
    painter.drawRect(10, 10, 50, 60);
    painter.translate(100, 100);
    painter.drawPolygon(triangle);
     */
}