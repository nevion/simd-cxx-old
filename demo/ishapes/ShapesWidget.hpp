/* 
 * File:   ShapesWidget.hpp
 * Author: corsaro
 *
 * Created on July 12, 2009, 7:23 PM
 */

#ifndef _SHAPESWIDGET_HPP
#define	_SHAPESWIDGET_HPP

#include <QWidget>
#include <QRect>
#include <QPixmap>
#include <vector>
#include <boost/shared_ptr.hpp>

#include <Shape.hpp>

class ShapesWidget  : public QWidget
{
  Q_OBJECT
  public:
  typedef std::vector<boost::shared_ptr<Shape> > ShapeList;
  typedef std::vector<QRect> FilterList;
public:

  ShapesWidget(QWidget *parent = 0);
  virtual ~ShapesWidget();

public:
  void addFilter(const QRect& filter);
  void displayFilter(const QRect& currentFilter);
  
public slots:
  void nextAnimationFrame();
  void addShape(boost::shared_ptr<Shape> shape);
    
protected:
  void paintEvent(QPaintEvent *event);

private:
  ShapesWidget(const ShapesWidget& orig);

private:
  ShapeList shapeList_;
  FilterList filterList_;
  QRect currentFilter_;
  bool showCurrentFilter_;
  QPixmap logo_;
  QPixmap simd_;
};

#endif	/* _SHAPESWIDGET_HPP */

