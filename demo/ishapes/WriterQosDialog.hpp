#ifndef DDS_DEMO_ISHAPES_WRITER_QOS_HPP_
#define DDS_DEMO_ISHAPES_WRITER_QOS_HPP_

#include <QtGui>
#include <ui_writerQosForm.h>
#include <dds/dds.hpp>

class WriterQosDialog : public QDialog 
{
  Q_OBJECT;
public:
  WriterQosDialog();
  virtual ~WriterQosDialog();

public:
  dds::DataWriterQos get_qos();

public slots:
  virtual void accept();
  virtual void reject();
private:
  Ui::WriterQoS qosForm_;
  dds::DataWriterQos qos_;
};
  
#endif /* DDS_DEMO_ISHAPES_WRITER_QOS_HPP_ */
