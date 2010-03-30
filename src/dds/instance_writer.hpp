#ifndef AC_SIMD_DDS_INSTANCE_WRITER_HPP
#define AC_SIMD_DDS_INSTANCE_WRITER_HPP

// -- BOOST Include
#include <boost/shared_ptr.hpp>

// -- SIMD_DDS Include
#include <dds/traits.hpp>
#include <dds/peer/instance_writer_impl.hpp>

namespace dds {

template <typename T>
class DataInstanceWriter {
public:
	typedef typename topic_data_writer<T>::type DW;

public:
  DataInstanceWriter(boost::shared_ptr<DW> writer, const T& key) {
    pimpl_.reset(new ::dds::peer::DataInstanceWriterImpl<T>(writer, key));
  }
  DataInstanceWriter() { }

  virtual ~DataInstanceWriter() { }
public:
      /**
       * Write a sample for the managed instance.
       *
       * @param data the sample.
       */
      DDS::ReturnCode_t write(const T& data) {
	return pimpl_->write(data);
      }

      /**
       * Write a sample with a timestamp for the managed instance.
       *
       * @param data the sample.
       * @param timestamp the timestamp
       */
      DDS::ReturnCode_t write(const T& sample, const DDS::Time_t& timestamp) {
	return pimpl_->write(sample, timestamp);
      }

      DDS::ReturnCode_t unregister() {
	return pimpl_->unregister();
      }

      DDS::ReturnCode_t unregister(const DDS::Time_t& timestamp) {
	return pimpl_->unregister(timestamp);
      }

      DDS::ReturnCode_t dispose() {
	return pimpl_->dispose();
      }

      DDS::ReturnCode_t dispose(const DDS::Time_t& timestamp) {
	return pimpl_->dispose(timestamp);
      }

      DDS::ReturnCode_t
      wait_for_acks(const DDS::Duration_t& timeout) {
	return pimpl_->wait_for_acks(timeout);
      }

private:
  ::boost::shared_ptr<dds::peer::DataInstanceWriterImpl<T> > pimpl_;
};

}
#endif /* AC_SIMD_DDS_INSTANCE_WRITER_HPP */
