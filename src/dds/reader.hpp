#ifndef AC_SIMD_DDS_READER_HPP
#define AC_SIMD_DDS_READER_HPP


namespace dds {

  template<typename T>
  class DataInstanceReader;

  template<typename T>
  class DataReader;

}
#include <dds/peer/reader_impl.hpp>

template <typename T>
class dds::DataReader {
public:
public:            
  typedef typename dds::peer::DataReaderImpl<T>::DR   DR;
  typedef typename dds::peer::DataReaderImpl<T>::TSeq TSeq;
public:
  typedef typename dds::peer::DataReaderImpl<T>::on_data_available_signal_t 
  on_data_available_signal_t;
  
  typedef typename dds::peer::DataReaderImpl<T>::on_data_available_slot_t 
  on_data_available_slot_t; 

  typedef typename dds::peer::DataReaderImpl<T>::on_requested_incompatible_qos_signal_t 
  on_requested_incompatible_qos_signal_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_requested_incompatible_qos_slot_t
  on_requested_incompatible_qos_slot_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_liveliness_changed_signal_t
  on_liveliness_changed_signal_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_liveliness_changed_slot_t
  on_liveliness_changed_slot_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_requested_deadline_missed_signal_t
  on_requested_deadline_missed_signal_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_requested_deadline_missed_slot_t
  on_requested_deadline_missed_slot_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_sample_rejected_signal_t
  on_sample_rejected_signal_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_sample_rejected_slot_t
  on_sample_rejected_slot_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_subscription_matched_signal_t
  on_subscription_matched_signal_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_subscription_matched_slot_t
  on_subscription_matched_slot_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_sample_lost_signal_t
  on_sample_lost_signal_t;

  typedef typename dds::peer::DataReaderImpl<T>::on_sample_lost_slot_t
  on_sample_lost_slot_t;

public:
  DataReader() { }

  DataReader(const Topic<T>& topic) 
  {
    pimpl_.reset(new dds::peer::DataReaderImpl<T>(topic));
    pimpl_->set_datareader(this);
  }

  DataReader(const Topic<T>& topic, 
	     const DataReaderQos& qos) 
  {
    pimpl_.reset(new dds::peer::DataReaderImpl<T>(topic, qos));
    pimpl_->set_datareader(this);
  }

  virtual ~DataReader() { }

public:

  /**
   * Reads all new samples from any view state and alive instances. Notice
   * that this call is intended to loan the <code>samples</code> as
   * well as the <conde>infos</code> containers, thus will require a
   * return_loan.
   */
  DDS::ReturnCode_t 
  read(TSeq& samples, 
       DDS::SampleInfoSeq& infos) 
  {
    return pimpl_->read(samples, infos);
  }

  /**
   * Takes all new samples from any view state and alive instances. Notice
   * that this call is intended to loan the <code>samples</code> as
   * well as the <conde>infos</code> containers, thus will require a
   * return_loan.
   */
  DDS::ReturnCode_t 
  take(TSeq& samples, 
       DDS::SampleInfoSeq& infos) 
  {
    return pimpl_->take(samples, infos);
  }

  /**
   * Reads at most <code>max_samples</code> samples that have not been
   * read yet from all vies and alive instances.
   */
  DDS::ReturnCode_t 
  read(TSeq& samples, 
       long max_samples) 
  {
    return pimpl_->read(samples, max_samples);
  }

  /**
   * Takes at most <code>max_samples</code> samples that have not been
   * read yet from all vies and alive instances.
   */
  DDS::ReturnCode_t 
  take(TSeq& samples, 
       long max_samples) 
  {
    return pimpl_->take(samples, max_samples);
  }

  /**
   * Most generic <code>read</code> exposing all the knobs provided by
   * the OMG DDS API.
   */
  DDS::ReturnCode_t 
  read(TSeq& samples, 
       DDS::SampleInfoSeq& infos,
       long max_samples, 
       DDS::SampleStateMask samples_state,
       DDS::ViewStateMask views_state,
       DDS::InstanceStateMask instances_state) 
  {
    return pimpl_->read(samples, 
			infos, 
			max_samples, 
			samples_state, 
			views_state, 
			instances_state);
  }

  /**
   * Most generic <code>take</code> exposing all the knobs provided by
   * the OMG DDS API.
   */
  DDS::ReturnCode_t 
  take(TSeq& samples, 
       DDS::SampleInfoSeq& infos,
       long max_samples, 
       DDS::SampleStateMask samples_state,
       DDS::ViewStateMask views_state,
       DDS::InstanceStateMask instances_state) 
  {
    return pimpl_->take(samples, 
			infos, 
			max_samples, 
			samples_state, 
			views_state, 
			instances_state);
  }

  DDS::ReturnCode_t 
  return_loan(TSeq& samples, 
	      DDS::SampleInfoSeq& infos) 
  {
    return pimpl_->return_loan(samples, infos);
  }

public:
  // -- Qos Getter/Setter
  DataReaderQos 
  get_qos() 
  {
    return pimpl_->get_qos();
  }

  DDS::ReturnCode_t 
  set_qos(const DataReaderQos& qos) 
  {
    return pimpl_->set_qos(qos);
  }

  Topic<T> 
  get_topic() 
  {
    return pimpl_->get_topic();
  }

  DDS::ReturnCode_t 
  wait_for_historical_data(const DDS::Duration_t& timeout) 
  {
    return pimpl_->wait_for_historical_data(timeout);
  }

  // -- Condition API
  /**
   * Creates an <code>ActiveReadCondition</code> that waits for new samples to
   * be arriving in order to notify.
   */
  template <typename F>
  ::dds::ActiveReadCondition
  create_readcondition(const F& f)
  {
    return pimpl_->create_readcondition(f);
  }

public:
  // Signal/Slot API

  dds::sigcon_t
  on_data_available_signal_connect(on_data_available_slot_t slot) 
  {
    return pimpl_->on_data_available_signal_connect(slot);
  }

  dds::sigcon_t
  on_requested_incompatible_qos_signal_connect(on_requested_incompatible_qos_slot_t slot) 
  {
    return pimpl_->on_requested_incompatible_qos_signal_connect(slot);
  }

  dds::sigcon_t 
  on_liveliness_changed_signal_connect(on_liveliness_changed_slot_t slot) 
  {
    return pimpl_->on_liveliness_changed_signal_connect(slot);
  }
  
  dds::sigcon_t 
  on_requested_deadline_missed_signal_connect(on_requested_deadline_missed_slot_t slot) 
  {
    return pimpl_->on_requested_deadline_missed_signal_connect(slot);
  }

  dds::sigcon_t 
  on_sample_rejected_signal_connect(on_sample_rejected_slot_t slot) 
  {
    return pimpl_->on_sample_rejected_signal_connect(slot);
  }

  dds::sigcon_t 
  on_subscription_matched_signal_connect(on_subscription_matched_slot_t slot) 
  {
    return pimpl_->on_subscription_matched_signal_connect(slot);
  }

  dds::sigcon_t 
  on_sample_lost_signal_connect(on_sample_lost_slot_t slot) 
  {
    return pimpl_->on_sample_lost_signal_connect(slot);
  }

protected:
  boost::shared_ptr<dds::peer::DataReaderImpl<T> > pimpl_;
};

#endif /* AC_SIMD_DDS_READER_HPP */
