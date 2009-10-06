/* 
 * File:   ShapeDynamics.hpp
 * Author: corsaro
 *
 * Created on July 12, 2009, 9:54 PM
 */

#ifndef _SHAPEDYNAMICS_HPP
#define	_SHAPEDYNAMICS_HPP

#include <QRect>
#include <QPoint>

class ShapeDynamics {
public:
    ShapeDynamics(int x0, int y0);
    ShapeDynamics(int x0, int y0, const QRect& constraint);
    virtual ~ShapeDynamics();
public:
    virtual QPoint getPosition();

    virtual void setConstraint(const QRect& rect);

    virtual void simulate() = 0;
    
private:
    ShapeDynamics(const ShapeDynamics& orig);

protected:
    QPoint pos_;
    QRect  constraint_;
};

#endif	/* _SHAPEDYNAMICS_HPP */

