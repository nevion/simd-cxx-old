#ifndef AC_SIMD_WRITER_HPP
#define AC_SIMD_WRITER_HPP

#include <simd/runtime.hpp>
#include <simd/memory.hpp>
#include <simd/traits.hpp>
#include <simd/topic.hpp>

namespace simd {
  template <typename T> 
  class DataWriter;

  template <typename T>
  class DataInstanceWriter;
}

template <typename T>
class simd::DataWriter {
public:
  typedef typename simd::topic_data_writer<T>::type DW;
  
public:
  DataWriter(simd::Topic<T>& topic) {
    pub_ = 
      simd::Runtime::instance()->get_publisher();
    
    simd::TopicQos tqos(topic.get_qos());
    simd::DataWriterQos dwqos(tqos);
    DDS::DataWriter* w = pub_->create_datawriter(topic.get_dds_topic(),
						 dwqos,
						 0,
						 DDS::ANY_STATUS);
    
    boost::shared_ptr<DW> tmp(DW::_narrow(w), simd::mem::DWDeleter(pub_));
    writer_ = tmp;
  }
  
  DataWriter(simd::Topic<T>& topic, const simd::DataWriterQos& qos) {
    pub_ = 
      simd::Runtime::instance()->get_publisher();
    DDS::DataWriter* w = pub_->create_datawriter(topic.get_dds_topic(),
						 qos,
						 0,
						 DDS::ANY_STATUS);
    
    boost::shared_ptr<DW> tmp(DW::_narrow(w), 
			      simd::mem::DWDeleter(pub_));
    writer_ = tmp;
  }
  
  ~DataWriter() { }
  
public:
  DDS::ReturnCode_t write(const T& sample) {
    return writer_->write(sample, DDS::HANDLE_NIL);
  }
  
  DDS::ReturnCode_t write(const T& sample, const DDS::Time_t& timestamp) {
    return writer_->write(sample, timestamp, DDS::HANDLE_NIL);
  }

  boost::shared_ptr<simd::DataInstanceWriter<T> >
  register_instance(const T& key) {
    boost::shared_ptr<simd::DataInstanceWriter<T> > 
      iwriter(new simd::DataInstanceWriter<T> (writer_, key));
    return iwriter;
  }
  
protected:
  boost::shared_ptr<DDS::Publisher> pub_;
  boost::shared_ptr<DW> writer_;
};

#endif /* AC_SIMD_WRITER_HPP */
