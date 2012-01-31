/* 
 * File:   ShapesWidget.cpp
 * Author: corsaro
 * 
 * Created on July 12, 2009, 7:23 PM
 */

#include <iostream>
#include <QtGui>
#include <boost/shared_ptr.hpp>
#include "config.hpp"
#include "ShapesWidget.hpp"


ShapesWidget::ShapesWidget(QWidget *parent)
: QWidget(parent),
  showCurrentFilter_(false),
  logo_(":/images/logo.png"),
  simd_(":/images/simd.png")
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
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(BRAND_LOGO_X, BRAND_LOGO_Y, logo_);
    painter.drawPixmap(SIMD_LOGO_X, SIMD_LOGO_Y, simd_);
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
