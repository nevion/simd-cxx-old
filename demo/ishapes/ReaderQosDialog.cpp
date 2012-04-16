#include <ReaderQosDialog.hpp>
#include <iostream>

ReaderQosDialog::ReaderQosDialog() 
{ 
  qosForm_.setupUi(this);
  this->setVisible(false);
}

ReaderQosDialog::~ReaderQosDialog() { }

void
ReaderQosDialog::accept() 
{
  this->setVisible(false);
}

void
ReaderQosDialog::reject() 
{
  this->setVisible(false);
}

dds::DataReaderQos
ReaderQosDialog::get_qos() 
{
  dds::DataReaderQos tmpQos;
  
  qos_ = tmpQos;

  if (qosForm_.reliableRButt->isChecked()) {
    qos_.set_reliable();
    //    std::cout << "ReaderQos = RELIABLE" << std::endl;
  }
  switch (qosForm_.durabilityComboBox->currentIndex()) {
  case 0:
    qos_.set_volatile();
    break;
  case 1:
    qos_.set_transient_local();
    break;
  case 2: 
    qos_.set_transient();
    break;
  case 3: 
    qos_.set_persistent();
    break;
  };

  if (qosForm_.exclusiveRButt->isChecked())
    qos_.set_exclusive();

  if (qosForm_.keepLastRButton->isChecked())
    qos_.set_keep_last(qosForm_.depthSpinBox->value());
  else
    qos_.set_keep_all();
  
  if (qosForm_.timeBasedFilterActive->isChecked()) {
    int period = 
      qosForm_.timeBasedFilterValue->text().toInt();
    int sec = period / 1000;
    uint32_t nsec = (period - (sec*1000))*1000000;
    DDS::Duration_t d = {sec, nsec};
    qos_.set_time_filter(d);
  }
  
  return qos_;
}
