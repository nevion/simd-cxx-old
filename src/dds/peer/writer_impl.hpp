#ifndef AC_SIMD_DDS_WRITER_IMPL_HPP
#define AC_SIMD_DDS_WRITER_IMPL_HPP

#include <dds/runtime.hpp>
#include <dds/memory.hpp>
#include <dds/traits.hpp>
#include <dds/topic.hpp>

namespace dds {
  namespace peer {
    template <typename T>
    class DataWriterImpl;
  }
}

template <typename T>
class dds::peer::DataWriterImpl 
{
public:
  typedef typename topic_data_writer<T>::type DW;
  
public:

  DataWriterImpl(const dds::Topic<T>& topic)
    : topic_(topic),
      dwqos_(topic_->get_qos())
  {
    pub_ =
      Runtime::instance()->get_publisher();
    
    DDS::DataWriter* w = 
      pub_->create_datawriter(topic_->get_dds_topic(),
			      dwqos_,
			      0,
			      DDS::ANY_STATUS);
    
    boost::shared_ptr<DW> tmp(DW::_narrow(w), mem::DWDeleter(pub_));
    writer_ = tmp;
  }
    
  DataWriterImpl(const dds::Topic<T>& topic, const dds::DataWriterQos& qos)
    : topic_(topic), dwqos_(qos)
  {
    pub_ = Runtime::instance()->get_publisher();
    DDS::DataWriter* w =
      pub_->create_datawriter(topic_->get_dds_topic(),
			      dwqos_,
			      0,
			      DDS::ANY_STATUS);
    
    
    Assert::postcondition((w != 0), "Unable to create DataWriter", __FILE__);
    Assert::postcondition((DW::_narrow(w) != 0), "Unable to Narrow DataWriter", __FILE__);
    
    boost::shared_ptr<DW> tmp(DW::_narrow(w),
			      mem::DWDeleter(pub_));
    writer_ = tmp;
  }
    
  DataWriterImpl(const dds::Topic<T>& topic, 
		 const dds::DataWriterQos& qos, 
		 const boost::shared_ptr<DDS::Publisher>& pub)
    :	topic_(topic), pub_(pub), dwqos_(qos)
  {
    DDS::DataWriter* w =
      pub_->create_datawriter(topic_->get_dds_topic(),
			      dwqos_,
			      0,
			      DDS::ANY_STATUS);
      
    boost::shared_ptr<DW> tmp(DW::_narrow(w),
			      mem::DWDeleter(pub_));
    writer_ = tmp;
  }
    
  virtual ~DataWriterImpl() { }

public:

  DDS::ReturnCode_t 
  write(const T& sample) 
  {
    return writer_->write(sample, DDS::HANDLE_NIL);
  }
    
  DDS::ReturnCode_t 
  write(const T& sample, 
	const DDS::Time_t& timestamp) 
  {
    return writer_->write_w_timestamp(sample, DDS::HANDLE_NIL, timestamp);
  }
    

  DataInstanceWriter<T>
  register_instance(const T& key) 
  {
    DataInstanceWriter<T> iwriter(writer_, key);
    return iwriter;
  }
    
  // -- QoS Getter/Setter
    
  DataWriterQos
  get_qos() 
  {
    return dwqos_;
  }

  DDS::ReturnCode_t
  set_qos(const DataWriterQos &qos)  
  {
    DDS::ReturnCode_t rc = writer_->set_qos(qos);
    if (rc == DDS::RETCODE_OK)
      dwqos_ = qos;
    return rc;
  }

  boost::shared_ptr<dds::Topic<T> >
  get_topic() 
  {
    return topic_;
  }
    
  boost::shared_ptr<DDS::Publisher>
  get_publisher() 
  {
    return pub_;
  }

  DDS::ReturnCode_t
  wait_for_acks(const DDS::Duration_t& timeout) 
  {
    return writer_->wait_for_acknowlegments(timeout);
  }

protected:
  dds::Topic<T>                       topic_;
  ::boost::shared_ptr<DDS::Publisher> pub_;
  ::boost::shared_ptr<DW>             writer_;
  dds::DataWriterQos                  dwqos_;
};

#endif /* AC_SIMD_DDS_WRITER_IMPL_HPP */
