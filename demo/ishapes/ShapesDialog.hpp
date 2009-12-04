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
#include <WriterQosDialog.hpp>
#include <ReaderQosDialog.hpp>

#include <ShapesWidget.hpp>
#include <Circle.hpp>

#include <dds/reader.hpp>
#include <dds/runtime.hpp>
#include <dds/topic.hpp>
#include <dds/reader.hpp>
#include <dds/writer.hpp>
#include <dds/traits.hpp>

// -- Shaped Include
#include <gen/ccpp_ishape.h>

#define CN 9


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
    GRAY    = 7,
    BLACK   = 8
  };

public:
  ShapesDialog();
  virtual ~ShapesDialog();

public slots:
  virtual void onPublishButtonClicked();
  virtual void onSubscribeButtonClicked();
  virtual void onReaderQosButtonClicked();
  virtual void onWriterQosButtonClicked();
    
private:
  ShapesDialog(const ShapesDialog& orig);

private:
  Ui::ShapesDialog  mainWidget;
  ShapesWidget*     shapesWidget;
  ReaderQosDialog    readerQos_;
  WriterQosDialog    writerQos_;

  QTimer                     timer;
  dds::Topic<ShapeType>      circleTopic_;
  dds::Topic<ShapeType>      squareTopic_;
  dds::Topic<ShapeType>      triangleTopic_;

  /*
  dds::DataReader<ShapeType>    circleReader_;
  dds::DataReader<ShapeType>    squareReader_;
  dds::DataReader<ShapeType>   triangleReader_;

  dds::DataWriter<ShapeType>    circleWriter_;
  dds::DataWriter<ShapeType>    squareWriter_;
  dds::DataWriter<ShapeType>    triangleWriter_;
  */
};

#endif	/* _ISHAPESFORM_HPP */

