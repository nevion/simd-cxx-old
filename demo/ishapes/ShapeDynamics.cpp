/* 
 * File:   ShapeDynamics.cpp
 * Author: corsaro
 * 
 * Created on July 12, 2009, 9:54 PM
 */

#include "ShapeDynamics.hpp"

ShapeDynamics::ShapeDynamics(int x0, int y0)
    : pos_(x0, y0)
{ }

ShapeDynamics::ShapeDynamics(int x0, int y0, const QRect& constraint)
    :   pos_(x0, y0),
        constraint_(constraint)
{ }

ShapeDynamics::~ShapeDynamics() {
}

QPoint
ShapeDynamics::getPosition() {
    return pos_;
}

void
ShapeDynamics::setConstraint(const QRect& rect) {
    constraint_ = rect;
}
