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
: QWidget(parent),
  showCurrentFilter_(false)
{
    this->setBackgroundRole(QPalette::Base);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    logo_.load("logo.jpg");
    simd_.load("simd.jpg");
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
    painter.drawPixmap(15, 300, logo_);
    painter.drawPixmap(200, 10, simd_);
    if (showCurrentFilter_) {
      QBrush brush(QColor(0x99,0x99,0x99,0x99), Qt::SolidPattern);
      painter.setBrush(brush);
      painter.drawRect(currentFilter_);
    }
    ShapeList::iterator index = shapeList_.begin();
    while (index != shapeList_.end()) {
        (*index)->paint(painter);
        ++index;
    }
}

void
ShapesWidget::addFilter(const QRect& filter) {
  filterList_.push_back(filter);
}

void ShapesWidget::displayFilter(const QRect& currentFilter) {
  currentFilter_ = currentFilter;
  showCurrentFilter_ = true;
  this->update();
}
