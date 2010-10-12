
/* 
 * File:   iShapesForm.cpp
 * Author: corsaro
 * 
 * Created on July 12, 2009, 6:50 PM
 */

#include <boost/shared_ptr.hpp>

#include <QtGui>
#include "ShapesDialog.hpp"
#include <iostream>
#include <Circle.hpp>
#include <Square.hpp>
#include <Triangle.hpp>
#include <BouncingShapeDynamics.hpp>
#include <DDSShapeDynamics.hpp>
#include <boost/lexical_cast.hpp>

static const float PI = 3.1415926535F;

/* Ugly hack -- fixme */
static QColor  color_[CN];

const char* const colorString_[] = {
  "BLUE",
  "RED",
  "GREEN",
  "ORANGE",
  "YELLOW",
  "MAGENTA",
  "CYAN",
  "GRAY",
  "BLACK"
};

static const std::string circleTopicName("Circle");
static const std::string squareTopicName("Square");
static const std::string triangleTopicName("Triangle");

ShapesDialog::ShapesDialog() 
  :   timer(this),
      circleTopic_(circleTopicName),
      squareTopic_(squareTopicName),
      triangleTopic_(triangleTopicName),
      filterExpression_("(x BETWEEN %0 AND %1) AND (y BETWEEN %2 AND %3)")
{
  mainWidget.setupUi(this);
  shapesWidget = new ShapesWidget(mainWidget.renderFrame);
  shapesWidget->resize(mainWidget.renderFrame->size());
  filterDialog_ = new FilterDialog(shapesWidget);
  connect(&timer, SIGNAL(timeout()),
	  shapesWidget, SLOT(nextAnimationFrame()));

  color_[BLUE] = QColor(0x33, 0x66, 0x99);
  color_[RED] = QColor(0xCC, 0x33, 0x33);
  color_[GREEN] = QColor(0x99, 0xCC, 0x66);
  color_[ORANGE] = QColor(0xFF, 0x99, 0x33);
  color_[YELLOW] = QColor(0xFF, 0xFF, 0x66);
  color_[MAGENTA] = QColor(0xCC, 0x99, 0xCC);
  color_[CYAN] = QColor(0x99, 0xCC, 0xFF);
  color_[GRAY] = QColor(0x99, 0x99, 0x99);
  color_[BLACK] = QColor(0x33, 0x33, 0x33);
  timer.start(40);
}

ShapesDialog::~ShapesDialog() {
}

void
ShapesDialog::onPublishButtonClicked() {
  int d = mainWidget.sizeSlider->value();
  float speed = ((float)mainWidget.speedSlider->value()) / 9;
  QRect rect(0, 0, d, d);
  // TODO: This should be retrieved from the canvas...
  QRect constr(0, 0, 500, 360);
  // QRect constr = this->geometry();
  int x = constr.width() * ((float)rand() / RAND_MAX);
  int y = constr.height() * ((float)rand() / RAND_MAX);
  int cIdx = mainWidget.colorList->currentIndex();
  int sIdx = mainWidget.wShapeList->currentIndex();
  
  QBrush brush(color_[cIdx], Qt::SolidPattern);
  //  QPen pen(color_[(cIdx+1)%(CN-1)], 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  QPen pen(color_[cIdx], 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

  switch (sIdx) {
  case CIRCLE: {
    ShapeType shape;
    shape.color = DDS::string_dup(colorString_[cIdx]);
    shape.shapesize = rect.width();
    shape.x = x;
    shape.y = y;
    dds::DataWriter<ShapeType> dw(circleTopic_ , writerQos_.get_qos());

    boost::shared_ptr<BouncingShapeDynamics>
      dynamics(new BouncingShapeDynamics(x, y, rect, constr, PI/6, speed,
					 shape, dw));
    boost::shared_ptr<Shape>
      circle(new Circle(rect, dynamics, pen, brush));
    shapesWidget->addShape(circle);
            
    break;
  }
  case SQUARE: {
    ShapeType shape;
    shape.color = DDS::string_dup(colorString_[cIdx]);
    shape.shapesize = rect.width();
    shape.x = x;
    shape.y = y;
    dds::DataWriter<ShapeType> dw(squareTopic_ , writerQos_.get_qos());
    boost::shared_ptr<BouncingShapeDynamics>
      dynamics(new BouncingShapeDynamics(x, y, rect, constr, PI/6, speed,
					 shape, dw));
    boost::shared_ptr<Shape>
      square(new Square(rect, dynamics, pen, brush));
    shapesWidget->addShape(square);
    // std::cout << "CREATE SQUARE" << std::endl;
    break;
  }
  case TRIANGLE: {
    ShapeType shape;
    shape.color = DDS::string_dup(colorString_[cIdx]);
    shape.shapesize = rect.width();
    shape.x = x;
    shape.y = y;
    dds::DataWriter<ShapeType> dw(triangleTopic_ , writerQos_.get_qos());
    boost::shared_ptr<BouncingShapeDynamics>
      dynamics(new BouncingShapeDynamics(x, y, rect, constr, PI/6, speed,
					 shape, dw));
    boost::shared_ptr<Shape>
      triangle(new Triangle(rect, dynamics, pen, brush));
    shapesWidget->addShape(triangle);
    // std::cout << "CREATE TRIANGLE" << std::endl;
    break;
  }
  default:
    break;
  };
    
}

void
ShapesDialog::onSubscribeButtonClicked() {
   
  int d = mainWidget.sizeSlider->value();
  QRect rect(0, 0, d, d);
  QRect constr(0, 0, 500, 340);
  // QRect constr = this->geometry();
  int x = static_cast<int>(constr.width() * ((float)rand() / RAND_MAX)*0.9F);
  int y = static_cast<int>(constr.height() * ((float)rand() / RAND_MAX)*0.9F);
  int sIdx = mainWidget.rShapeList->currentIndex();

  QColor gray = QColor(0x99, 0x99, 0x99);
  //  QBrush brush(color_[BLACK], Qt::FDiagPattern);
  QBrush brush(gray, Qt::SolidPattern);

  QPen pen(Qt::white, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

  std::vector<std::string> empty;
  filterParams_ = empty;
  if (filterDialog_->isEnabled()) {
    QRect rect =  filterDialog_->getFilterBounds();	
    std::string x0 = 
      boost::lexical_cast<std::string>(rect.x());
    std::string x1 = 
      boost::lexical_cast<std::string>(rect.x() + rect.width() -d);
    
    std::string y0 = 
      boost::lexical_cast<std::string>(rect.y());
    std::string y1 = 
      boost::lexical_cast<std::string>(rect.x() + rect.height()-d);
    filterParams_.push_back(x0);
    filterParams_.push_back(x1);
    filterParams_.push_back(y0);
    filterParams_.push_back(y1);
  }

  switch (sIdx) {
  case CIRCLE: {
    for (int i = 0; i < CN; ++i) {
      std::string colorStr(colorString_[i]);
      dds::DataReader<ShapeType> dr;
      if (filterDialog_->isEnabled()) {
	std::string tname = "CFCircle" + boost::lexical_cast<std::string>(i);
	std::string filter = filterExpression_;
	if (filterDialog_->filterOutside() == false) 
	  filter = "(x < %0) OR (x > %1) OR (y < %2) OR (y > %3)" ;
	
	dds::ContentFilteredTopic<ShapeType> cfTopic(tname, 
						     circleTopic_, 
						     filter,
						     filterParams_);
	dds::DataReader<ShapeType> cfdr(cfTopic , readerQos_.get_qos());
	dr = cfdr;	    
      }
      else {
	dds::DataReader<ShapeType> rdr(circleTopic_, readerQos_.get_qos());
	dr = rdr;
      }
      boost::shared_ptr<DDSShapeDynamics>
	dynamics(new DDSShapeDynamics(x, y, dr, colorStr, i));
      boost::shared_ptr<Shape>
	circle(new Circle(rect, dynamics, pen, brush, true));
      dynamics->setShape(circle);
      shapesWidget->addShape(circle);
    }
    break;
  }
        
  case SQUARE: {
    for (int i = 0; i < CN; ++i) {
      dds::DataReader<ShapeType> dr;
      std::string colorStr(colorString_[i]);
      if (filterDialog_->isEnabled()) {
	std::string tname = "CFSquare" + boost::lexical_cast<std::string>(i);
	std::string filter = filterExpression_;
	if (filterDialog_->filterOutside() == false) 
	  filter = "(x < %0) OR (x > %1) OR (y < %2) OR (y > %3)" ;
	
	dds::ContentFilteredTopic<ShapeType> cfTopic(tname, 
						     squareTopic_, 
						     filter,
						     filterParams_);
	dds::DataReader<ShapeType> cfdr(cfTopic , readerQos_.get_qos());
	dr = cfdr;	    
      }
      else {
	dds::DataReader<ShapeType> rdr(squareTopic_, readerQos_.get_qos());
	dr = rdr;
      }

      boost::shared_ptr<DDSShapeDynamics>
	dynamics(new DDSShapeDynamics(x, y, dr, colorStr, i));
      boost::shared_ptr<Shape>
	square(new Square(rect, dynamics, pen, brush, true));
      dynamics->setShape(square);
      shapesWidget->addShape(square);
    }
    break;
  }
  case TRIANGLE: {
    for (int i = 0; i < CN; ++i) {
      dds::DataReader<ShapeType> dr;
      if (filterDialog_->isEnabled()) {
	std::string tname = "CFTriangle" + boost::lexical_cast<std::string>(i);
	std::string filter = filterExpression_;
	if (filterDialog_->filterOutside() == false) 
	  filter = "(x < %0) OR (x > %1) OR (y < %2) OR (y > %3)" ;
	
	dds::ContentFilteredTopic<ShapeType> cfTopic(tname, 
						     triangleTopic_, 
						     filter,
						     filterParams_);
	dds::DataReader<ShapeType> cfdr(cfTopic , readerQos_.get_qos());
	dr = cfdr;	    
      }
      else {
	dds::DataReader<ShapeType> rdr(triangleTopic_, readerQos_.get_qos());
	dr = rdr;
      }

      std::string colorStr(colorString_[i]);
      boost::shared_ptr<DDSShapeDynamics>
	dynamics(new DDSShapeDynamics(x, y, dr, colorStr, i));
      boost::shared_ptr<Shape>
	triangle(new Triangle(rect, dynamics, pen, brush,true));
      dynamics->setShape(triangle);
      shapesWidget->addShape(triangle);
    }
    break;
  }

  default:
    break;
  }
 
}

void 
ShapesDialog::onReaderQosButtonClicked()
{
  readerQos_.setVisible(true);
}
void 
ShapesDialog::onWriterQosButtonClicked()
{
  writerQos_.setVisible(true);
}

void
ShapesDialog::onFilterButtonClicked()
{
  // std::cout << "FilterButton Clicked" << std::endl;
  filterDialog_->setVisible(true);
}
