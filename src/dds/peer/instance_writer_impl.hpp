#ifndef AC_SIMD_DDS_INSTANCE_WRITER_IMPL_HPP
#define AC_SIMD_DDS_INSTANCE_WRITER_IMPL_HPP

namespace dds { 
  namespace peer {
    
    /**
     * The <code>DataInstanceWriter</code> class takes care of writing a specific
     * Topic instance. The instance is automatically unregistered once the
     * <code>DataInstanceWriter</code> is destroyed.
     *
     * @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
     * @version 1.0
     */
    template <typename T>
    class DataInstanceWriterImpl {
    public:
      typedef typename topic_data_writer<T>::type DW;
    public:

      DataInstanceWriterImpl(boost::shared_ptr<DW> writer, const T& key)
	: writer_(writer),
	  key_(key),
	  status_(ALIVE) {
	handle_ = writer_->register_instance(key_);
      }

      ~DataInstanceWriterImpl() {
	if (status_ == ALIVE)
	  this->unregister();
      }

    public:

      /**
       * Write a sample for the managed instance.
       *
       * @param data the sample.
       */
      DDS::ReturnCode_t write(const T& data) {
	return writer_->write(data, handle_);
      }

      /**
       * Write a sample with a timestamp for the managed instance.
       *
       * @param data the sample.
       * @param timestamp the timestamp
       */
      DDS::ReturnCode_t write(const T& sample, const DDS::Time_t& timestamp) {
	return writer_->write(sample, timestamp, handle_);
      }

      DDS::ReturnCode_t unregister() {
	status_ = UNREGISTERED;
	return writer_->unregister_instance(key_, handle_);
      }

      DDS::ReturnCode_t unregister(const DDS::Time_t& timestamp) {
	status_ = UNREGISTERED;
	return writer_->unregister_instance_w_timestamp(key_, handle_, timestamp);
      }

      DDS::ReturnCode_t dispose() {
	status_ = DISPOSED;
	return writer_->dispose(key_, handle_);
      }

      DDS::ReturnCode_t dispose(const DDS::Time_t& timestamp) {
	status_ = DISPOSED;
	return writer_->dispose_instance_w_timestamp(key_, handle_, timestamp);
      }

      DDS::ReturnCode_t
      wait_for_acks(const DDS::Duration_t& timeout) {
	return writer_->wait_for_acknowlegments(timeout);
      }
    private:

      enum InstanceStatus_ {
	ALIVE, UNREGISTERED, DISPOSED
      };
    private:
      boost::shared_ptr<DW> writer_;
      T key_;
      DDS::InstanceHandle_t handle_;
      InstanceStatus_ status_;
    };

    
  } 
}
#endif /* AC_SIMD_DDS_INSTANCE_WRITER_IMPL_HPP */
