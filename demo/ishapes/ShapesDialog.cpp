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
        circleReader_(circleTopic_),
        squareReader_(squareTopic_),
        triangleReader_(triangleTopic_), 
        circleWriter_(circleTopic_),
        squareWriter_(squareTopic_),
        triangleWriter_(triangleTopic_)
{
    mainWidget.setupUi(this);
    shapesWidget = new ShapesWidget(mainWidget.renderFrame);
    shapesWidget->resize(mainWidget.renderFrame->size());
    connect(&timer, SIGNAL(timeout()),
                    shapesWidget, SLOT(nextAnimationFrame()));

    color_[BLUE] = QColor(0x33, 0x66, 0x99);
    color_[RED] = QColor(0xCC, 0x33, 0x33);
    color_[GREEN] = QColor(0x99, 0xCC, 0x66);
    color_[ORANGE] = QColor(0xFF, 0x99, 0x33);
    color_[YELLOW] = QColor(0xFF, 0xFF, 0x66);
    color_[MAGENTA] = QColor(0xCC, 0x99, 0xCC);
    color_[CYAN] = QColor(0x99, 0xCC, 0xFF);
    color_[BLACK] = QColor(0x33, 0x33, 0x33);

    timer.start(50);
}

ShapesDialog::~ShapesDialog() {
}

void
ShapesDialog::onPublishButtonClicked() {
    // QRect constr(0, 0, mainWidget.renderFrame->size().width(), mainWidget.renderFrame->size().height());
    int d = mainWidget.sizeSlider->value();
    float speed = ((float)mainWidget.speedSlider->value()) / 9;
    QRect rect(0, 0, d, d);
    QRect constr(0, 0, 500, 600);
    // QRect constr = this->geometry();
    int x = constr.width() * ((float)rand() / RAND_MAX);
    int y = constr.height() * ((float)rand() / RAND_MAX);
    int cIdx = mainWidget.colorList->currentIndex();
    int sIdx = mainWidget.wShapeList->currentIndex();

    QBrush brush(color_[cIdx], Qt::SolidPattern);
    QPen pen(color_[(cIdx+1)%(CN-1)], 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    switch (sIdx) {
        case CIRCLE: {
            ShapeType shape;
            shape.color = DDS::string_dup(colorString_[cIdx]);
            shape.shapesize = rect.width();
            shape.x = x;
            shape.y = y;
            boost::shared_ptr<BouncingShapeDynamics>
            dynamics(new BouncingShapeDynamics(x, y, rect, constr, PI/6, speed,
                                               shape, circleWriter_));
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
            boost::shared_ptr<BouncingShapeDynamics>
            dynamics(new BouncingShapeDynamics(x, y, rect, constr, PI/6, speed,
                                               shape, squareWriter_));
            boost::shared_ptr<Shape>
            square(new Square(rect, dynamics, pen, brush));
            shapesWidget->addShape(square);
            std::cout << "CREATE SQUARE" << std::endl;
            break;
        }
        case TRIANGLE: {
            ShapeType shape;
            shape.color = DDS::string_dup(colorString_[cIdx]);
            shape.shapesize = rect.width();
            shape.x = x;
            shape.y = y;
            boost::shared_ptr<BouncingShapeDynamics>
            dynamics(new BouncingShapeDynamics(x, y, rect, constr, PI/6, speed,
                                               shape, triangleWriter_));
            boost::shared_ptr<Shape>
            triangle(new Triangle(rect, dynamics, pen, brush));
            shapesWidget->addShape(triangle);
            std::cout << "CREATE TRIANGLE" << std::endl;
            break;
        }
        default:
            break;
    };
    
    std::cout << "Publish Button Clicked" << std::endl;
}

void
ShapesDialog::onSubscribeButtonClicked() {
   
    int d = mainWidget.sizeSlider->value();
    QRect rect(0, 0, d, d);
    QRect constr(0, 0, 500, 600);
    // QRect constr = this->geometry();
    int x = static_cast<int>(constr.width() * ((float)rand() / RAND_MAX)*0.9F);
    int y = static_cast<int>(constr.height() * ((float)rand() / RAND_MAX)*0.9F);
    int sIdx = mainWidget.rShapeList->currentIndex();

    QBrush brush(color_[BLACK], Qt::FDiagPattern);
    QPen pen(color_[BLACK], 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    switch (sIdx) {
        case CIRCLE: {
            for (int i = 0; i < CN; ++i) {
                std::string colorStr(colorString_[i]);

                boost::shared_ptr<DDSShapeDynamics>
                dynamics(new DDSShapeDynamics(x, y, circleReader_, colorStr, i));
                boost::shared_ptr<Shape>
                circle(new Circle(rect, dynamics, pen, brush));
                dynamics->setShape(circle);
                shapesWidget->addShape(circle);
            }
            break;
        }
        
        case SQUARE: {
            for (int i = 0; i < CN; ++i) {
                std::string colorStr(colorString_[i]);

                boost::shared_ptr<DDSShapeDynamics>
                dynamics(new DDSShapeDynamics(x, y, squareReader_, colorStr, i));
                boost::shared_ptr<Shape>
                square(new Square(rect, dynamics, pen, brush));
                dynamics->setShape(square);
                shapesWidget->addShape(square);
            }
            break;
        }
        case TRIANGLE: {
            for (int i = 0; i < CN; ++i) {
                std::string colorStr(colorString_[i]);

                boost::shared_ptr<DDSShapeDynamics>
                dynamics(new DDSShapeDynamics(x, y, triangleReader_, colorStr, i));
                boost::shared_ptr<Shape>
                triangle(new Triangle(rect, dynamics, pen, brush));
                dynamics->setShape(triangle);
                shapesWidget->addShape(triangle);
            }
            break;
        }

        default:
            break;
    }
 
    std::cout << "Subscribe Button Clicked" << std::endl;
}
