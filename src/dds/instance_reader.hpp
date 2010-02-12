#ifndef AC_SIMD_DDS_INSTANCE_READER_HPP
#define AC_SIMD_DDS_INSTANCE_READER_HPP

// -- BOOST Include
#include <boost/shared_ptr.hpp>

// -- SIMD_DDS Include
#include <dds/config.hpp>
#include <dds/peer/reader_impl.hpp>


namespace dds {
  template <typename T>
  class DataInstanceReader;
}

/**
 * The <code>DataInstanceReader</code> provides a simple way of reading
 * a specific DDS instance. Instances of this class are creadeted via a
 * specific factory method available in the class <code>DataReader</code>.
 *
 * @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
 * @version 0.1
 */
template <typename T>
class SIMD_EXPORT dds::DataInstanceReader 
{
public:
  typedef typename dds::peer::DataReaderImpl<T>::DR   DR;
  typedef typename dds::peer::DataReaderImpl<T>::TSeq TSeq;


public:
  DataInstanceReader(dds::peer::DataInstanceReader<T> reader, const T& key) 
    : reader_(reader),
      key_(key) 
  {
    handle_ = reader_->lookup_instance(key_);
  }

  ~DataInstanceReader() {}

public:
  /**
   * Reads all new samples from any view state and alive instances. Notice
   * that this call is intended to loan the <code>samples</code> as
   * well as the <conde>infos</code> containers, thus will require a
   * return_loan.
   */
  DDS::ReturnCode_t read(TSeq& samples, DDS::SampleInfoSeq& infos) {
    int rv = DDS::RETCODE_NO_DATA;
    if (handle_ == DDS::HANDLE_NIL)
      handle_ = reader_->lookup_instance(key_);
    
    if (handle_ != DDS::HANDLE_NIL)
      rv = reader_->read(samples,
			 infos,
			 DDS::LENGTH_UNLIMITED,
			 handle_,
			 DDS::NOT_READ_SAMPLE_STATE,
			 DDS::ANY_VIEW_STATE,
			 DDS::ALIVE_INSTANCE_STATE);
    return rv;
  }

  /**
   * Takes all new samples from any view state and alive instances. Notice
   * that this call is intended to loan the <code>samples</code> as
   * well as the <conde>infos</code> containers, thus will require a
   * return_loan.
   */ 
  DDS::ReturnCode_t take(TSeq& samples, DDS::SampleInfoSeq& infos) {
    int rv = DDS::RETCODE_NO_DATA;;
    if (handle_ == DDS::HANDLE_NIL)
      handle_ = reader_->lookup_instance(key_);

    if (handle_ != DDS::HANDLE_NIL)
      rv = reader_->take_instance(samples,
				  infos,
				  DDS::LENGTH_UNLIMITED,
				  handle_,
				  DDS::NOT_READ_SAMPLE_STATE,
				  DDS::ANY_VIEW_STATE,
				  DDS::ALIVE_INSTANCE_STATE);
    return rv;
  }
  
  /**
   * Reads at most <code>max_samples</code> samples that have not been
   * read yet from all vies and alive instances.
   */ 
  DDS::ReturnCode_t read(TSeq& samples, 
			 long max_samples) {
    int rv = DDS::RETCODE_NO_DATA;;

    if (handle_ == DDS::HANDLE_NIL)
      handle_ = reader_->lookup_instance(key_);
      
    if (handle_ != DDS::HANDLE_NIL) {
      DDS::SampleInfoSeq infos(max_samples);
      rv = reader_->read(samples,
			 infos,
			 max_samples,
			 handle_,
			 DDS::NOT_READ_SAMPLE_STATE,
			 DDS::ANY_VIEW_STATE,
			 DDS::ALIVE_INSTANCE_STATE);
    }
    return rv;
  }
  
  /**
   * Takes at most <code>max_samples</code> samples that have not been
   * read yet from all vies and alive instances.
   */ 
  DDS::ReturnCode_t take(TSeq& samples, 
			 long max_samples) {

    int rv = DDS::RETCODE_NO_DATA;;

    if (handle_ == DDS::HANDLE_NIL)
      handle_ = reader_->lookup_instance(key_);

    if (handle_ != DDS::HANDLE_NIL) {
      DDS::SampleInfoSeq infos(max_samples);
      rv = reader_->take_instance(samples,
				  infos,
				  max_samples,
				  handle_,
				  DDS::NOT_READ_SAMPLE_STATE,
				  DDS::ANY_VIEW_STATE,
				  DDS::ALIVE_INSTANCE_STATE);
    }
    return rv;
  }
  /**
   * Most generic <code>read</code> exposing all the knobs provided by
   * the OMG DDS API.
   */ 
  DDS::ReturnCode_t read(TSeq& samples, 
			 DDS::SampleInfoSeq& infos,
			 long max_samples,
			 DDS::SampleStateMask samples_state,
			 DDS::ViewStateMask   views_state,
			 DDS::InstanceStateMask instances_state) {
    int rv = DDS::RETCODE_NO_DATA;;
    if (handle_ == DDS::HANDLE_NIL)
      handle_ = reader_->lookup_instance(key_);

    if (handle_ != DDS::HANDLE_NIL)
      rv = reader_->read(samples,
			 infos,
			 max_samples,
			 handle_,
			 samples_state,
			 views_state,
			 instances_state);
    return rv;

  }

  /**
   * Most generic <code>take</code> exposing all the knobs provided by
   * the OMG DDS API.
   */ 
  DDS::ReturnCode_t take(TSeq& samples, 
			 DDS::SampleInfoSeq& infos,
			 long max_samples,
			 DDS::SampleStateMask samples_state,
			 DDS::ViewStateMask   views_state,
			 DDS::InstanceStateMask instances_state) {
      
    int rv = DDS::RETCODE_NO_DATA;;

    if (handle_ == DDS::HANDLE_NIL)
      handle_ = reader_->lookup_instance(key_);
      
    if (handle_ != DDS::HANDLE_NIL) {
      rv = reader_->take_instance(samples,
				  infos,
				  max_samples,
				  handle_,
				  samples_state,
				  views_state,
				  instances_state);
    }
    return rv;
  }
  DDS::ReturnCode_t return_loan(TSeq& samples, DDS::SampleInfoSeq& infos) {
    return reader_->return_loan(samples, infos);
  }
  
private:
  boost::shared_ptr<DR> reader_;
  T key_;
  dds::ihandle_t handle_;

};

#endif /* AC_SIMD_DDS_INSTANCE_READER_HPP */
