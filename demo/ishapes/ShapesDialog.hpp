/* 
 * File:   iShapesForm.hpp
 * Author: corsaro
 *
 * Created on July 12, 2009, 6:50 PM
 */

#ifndef _ISHAPESFORM_HPP
#define	_ISHAPESFORM_HPP

#include <dds/reader.hpp>
#include <dds/runtime.hpp>
#include <dds/topic.hpp>
#include <dds/reader.hpp>
#include <dds/writer.hpp>
#include <dds/traits.hpp>

#include <QtGui>

#include <ui_iShapesForm.h>
#include <WriterQosDialog.hpp>
#include <ReaderQosDialog.hpp>
#include <FilterDialog.hpp>

#include <ShapesWidget.hpp>
#include <Circle.hpp>

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
  virtual void onFilterButtonClicked();
    
private:
  ShapesDialog(const ShapesDialog& orig);

private:
  Ui::ShapesDialog  mainWidget;
  ShapesWidget*     shapesWidget;
  ReaderQosDialog    readerQos_;
  WriterQosDialog    writerQos_;
  FilterDialog*       filterDialog_;

  QTimer                     timer;
  dds::Topic<ShapeType>      circleTopic_;
  dds::Topic<ShapeType>      squareTopic_;
  dds::Topic<ShapeType>      triangleTopic_;
  std::string 		     filterExpression_;
  std::vector<std::string>   filterParams_;
};

#endif	/* _ISHAPESFORM_HPP */

