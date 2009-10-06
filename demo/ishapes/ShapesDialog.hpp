/* 
 * File:   iShapesForm.hpp
 * Author: corsaro
 *
 * Created on July 12, 2009, 6:50 PM
 */

#ifndef _ISHAPESFORM_HPP
#define	_ISHAPESFORM_HPP


#include <QtGui>

#include <ui_iShapesForm.h>
#include <ShapesWidget.hpp>
#include <Circle.hpp>

#include <simd/reader.hpp>
#include <simd/runtime.hpp>
#include <simd/topic.hpp>
#include <simd/reader.hpp>
#include <simd/writer.hpp>
#include <simd/traits.hpp>

// -- Shaped Include
#include <gen/ccpp_ishape.h>

#define CN 8


#include <topic-traits.hpp>
class ShapesDialog : public QDialog {
    Q_OBJECT
public:
    enum { CIRCLE = 0, SQUARE = 1, TRIANGLE = 2 };

    enum {
        BLUE    = 0,
        RED     = 1,
        GREEN   = 2,
        ORANGE  = 3,
        YELLOW  = 4,
        MAGENTA = 5,
        CYAN    = 6,
        BLACK   = 7
    };

public:
    ShapesDialog();
    virtual ~ShapesDialog();

public slots:
    virtual void onPublishButtonClicked();
    virtual void onSubscribeButtonClicked();
    
private:
    ShapesDialog(const ShapesDialog& orig);

private:
    Ui::ShapesDialog  mainWidget;
    ShapesWidget*     shapesWidget;
    QTimer            timer;
    simd::Topic<ShapeType>      circleTopic_;
    simd::Topic<ShapeType>      squareTopic_;
    simd::Topic<ShapeType>      triangleTopic_;

    simd::DataReader<ShapeType>    circleReader_;
    simd::DataReader<ShapeType>    squareReader_;
    simd::DataReader<ShapeType>   triangleReader_;

    simd::DataWriter<ShapeType>    circleWriter_;
    simd::DataWriter<ShapeType>    squareWriter_;
    simd::DataWriter<ShapeType>    triangleWriter_;
};

#endif	/* _ISHAPESFORM_HPP */

