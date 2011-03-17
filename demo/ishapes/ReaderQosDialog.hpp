#ifndef DDS_DEMO_ISHAPES_READER_QOS_HPP_
#define DDS_DEMO_ISHAPES_READER_QOS_HPP_

#include <dds/dds.hpp>
#include <QtGui>
#include <ui_readerQosForm.h>

class ReaderQosDialog : public QDialog 
{
  Q_OBJECT;
public:
  ReaderQosDialog();
  virtual ~ReaderQosDialog();

public:
  dds::DataReaderQos get_qos();

public slots:
  virtual void accept();
  virtual void reject();

private:
  Ui::ReaderQos qosForm_;
  dds::DataReaderQos qos_;
};
  
#endif /* DDS_DEMO_ISHAPES_READER_QOS_HPP_ */
