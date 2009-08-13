#ifndef AC_SIMD_INSTANCE_WRITER_HPP
#define AC_SIMD_INSTANCE_WRITER_HPP

// -- BOOST Include
#include <boost/shared_ptr.hpp>

// -- SIMD Include
#include <traits.hpp>

namespace simd {

  template <typename T>
  class DataInstanceWriter {
  public:
    typedef typename topic_data_writer<T>::type DW;
  public:
    DataInstanceWriter(boost::shared_ptr<DW> writer, const T& key) 
      : writer_(writer),
	key_(key) 
    {
      handle_ = writer_->register_instance(key_);
    }

    ~DataInstanceWriter() {
      writer_->unregister_handle(handle_, key_);
    }

  public:
  
    DDS::ReturnCode_t write(const T& data) {
      writer_->write(data, handle_);
    }
  
    DDS::ReturnCode_t write(const T& sample, const DDS::Time_t& timestamp) {
      writer_->write(sample, timestamp, handle_);
    }
  
  private:
    boost::shared_ptr<DW> writer_;
    T key_;
    DDS::InstanceHandle_t handle_;

  };
}
#endif /* AC_SIMD_INSTANCE_WRITER_HPP */
