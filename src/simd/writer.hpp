#ifndef AC_SIMD_WRITER_HPP
#define AC_SIMD_WRITER_HPP

#include <simd/runtime.hpp>
#include <simd/memory.hpp>
#include <simd/traits.hpp>
#include <simd/topic.hpp>

namespace simd {

  // -- Forward declaration
  template <typename T>
  class DataInstanceWriter;

  /**
   * The <code>DataWriter</code> class provides a generic API for
   * writing instances samples for a specific Topic.
   */
  template <typename T>
  class DataWriter {
  public:
    typedef typename topic_data_writer<T>::type DW;
  
  public:
    DataWriter(Topic<T>& topic) {
      pub_ = 
	Runtime::instance()->get_publisher();
    
      TopicQos tqos(topic.get_qos());
      DataWriterQos dwqos(tqos);
      DDS::DataWriter* w = pub_->create_datawriter(topic.get_dds_topic(),
						   dwqos,
						   0,
						   DDS::ANY_STATUS);
    
      boost::shared_ptr<DW> tmp(DW::_narrow(w), mem::DWDeleter(pub_));
      writer_ = tmp;
    }
  
    DataWriter(Topic<T>& topic, const DataWriterQos& qos) {
      pub_ = 
	Runtime::instance()->get_publisher();
      DDS::DataWriter* w = pub_->create_datawriter(topic.get_dds_topic(),
						   qos,
						   0,
						   DDS::ANY_STATUS);
    
      boost::shared_ptr<DW> tmp(DW::_narrow(w), 
				mem::DWDeleter(pub_));
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

    boost::shared_ptr<DataInstanceWriter<T> >
    register_instance(const T& key) {
      boost::shared_ptr<DataInstanceWriter<T> > 
	iwriter(new DataInstanceWriter<T> (writer_, key));
      return iwriter;
    }
  
  protected:
    boost::shared_ptr<DDS::Publisher> pub_;
    boost::shared_ptr<DW> writer_;
  };
}
#endif /* AC_SIMD_WRITER_HPP */
