/* 
 * File:   Square.hpp
 * Author: corsaro
 *
 * Created on July 13, 2009, 1:40 AM
 */

#ifndef _SQUARE_HPP
#define	_SQUARE_HPP

#include <QtGui>
#include <boost/shared_ptr.hpp>
#include <Shape.hpp>
#include <ShapeDynamics.hpp>

class Square : public Shape {
public:
    Square(const QRect& bounds,
           boost::shared_ptr<ShapeDynamics> dynamics,
           const QPen& pen,
           const QBrush& brush,
           bool targeted = false);
    
    virtual ~Square();

public:
    virtual void update();
    virtual void paint(QPainter& painter);
private:
    Square(const Square& orig);
    Square& operator=(const Square&);

private:
    boost::shared_ptr<ShapeDynamics> dynamics_;
    
};

#endif	/* _SQUARE_HPP */

