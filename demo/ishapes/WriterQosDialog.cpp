#include <WriterQosDialog.hpp>
#include <iostream>

WriterQosDialog::WriterQosDialog() 
{ 
  qosForm_.setupUi(this);
  this->setVisible(false);
}

WriterQosDialog::~WriterQosDialog() { }

void
WriterQosDialog::accept() 
{
  this->setVisible(false);
}

void
WriterQosDialog::reject() 
{
  this->setVisible(false);
}

dds::DataWriterQos
WriterQosDialog::get_qos() 
{
  dds::DataWriterQos tmpQos;
  
  qos_ = tmpQos;

  if (qosForm_.reliableRButt->isChecked()) {
    qos_.set_reliable();
    // std::cout << "WriterQos = RELIABLE" << std::endl;
  }
  switch (qosForm_.durabilityComboBox->currentIndex()) {
  case 1:
    qos_.set_transient();
    break;
  case 2: 
    qos_.set_persistent();
    break;
  };

  qos_.set_priority(qosForm_.prioritySpinBox->value());
  
  if (qosForm_.ownershipExclusiveRButt->isChecked())
    qos_.set_strength(qosForm_.strengthSpinBox->value());

  return qos_;
}
