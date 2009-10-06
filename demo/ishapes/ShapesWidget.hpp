/* 
 * File:   ShapesWidget.hpp
 * Author: corsaro
 *
 * Created on July 12, 2009, 7:23 PM
 */

#ifndef _SHAPESWIDGET_HPP
#define	_SHAPESWIDGET_HPP

#include <QWidget>

#include <vector>
#include <boost/shared_ptr.hpp>

#include <Shape.hpp>

class ShapesWidget  : public QWidget
{
    Q_OBJECT
public:
    typedef std::vector<boost::shared_ptr<Shape> > ShapeList;
    
public:

    ShapesWidget(QWidget *parent = 0);
    virtual ~ShapesWidget();

public slots:
    void nextAnimationFrame();
    void addShape(boost::shared_ptr<Shape> shape);
    
protected:
    void paintEvent(QPaintEvent *event);

private:
    ShapesWidget(const ShapesWidget& orig);

private:
    ShapeList shapeList_;
};

#endif	/* _SHAPESWIDGET_HPP */

