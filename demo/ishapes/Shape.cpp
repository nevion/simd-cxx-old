/* 
 * File:   Shape.cpp
 * Author: corsaro
 * 
 * Created on July 12, 2009, 9:50 PM
 */

#include "Shape.hpp"
#include <iostream>

Shape::Shape(const QRect& bounds, const QPen& pen, const QBrush& brush)
    :   bounds_(bounds),
        pen_(pen),
        brush_(brush)
{}

Shape::~Shape() {
}

void
Shape::setPen(const QPen& pen) {
    pen_ = pen;
}

void
Shape::setBrush(const QBrush& brush) {
    brush_ = brush;
}

void
Shape::setBounds(const QRect& bounds) {
    bounds_ = bounds;
}