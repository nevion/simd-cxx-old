#ifndef AC_SIMD_DDS_READER_IMPL_HPP_
#define AC_SIMD_DDS_READER_IMPL_HPP_

#include <iostream>

// -- BOOST Includes
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <boost/signals2/signal.hpp>

// -- SIMD_DDS Includes
#include <dds/runtime.hpp>
#include <dds/memory.hpp>
#include <dds/traits.hpp>
#include <dds/topic.hpp>
#include <dds/condition.hpp>


namespace dds {
  namespace peer {
    template<typename T>
    class DataReaderImpl;
  }
}
  
template<typename T>
class dds::peer::DataReaderImpl : public DDS::DataReaderListener 
{
public:
  typedef typename topic_data_reader<T>::type DR;
  typedef typename topic_data_seq<T>::type TSeq;
  
public:
  // -- on_data_available signal/slot
  typedef boost::signals2::signal1<void, 
				   dds::DataReader<T>& >
  on_data_available_signal_t;
  
  typedef typename boost::signals2::signal1<void, 
					    dds::DataReader<T> >::slot_type
  on_data_available_slot_t;
  
  // -- on_requested_incompatible_qos signal/slot
  typedef boost::signals2::signal2<void, 
				   dds::DataReader<T>&,
				   const DDS::RequestedIncompatibleQosStatus&>
  on_requested_incompatible_qos_signal_t;
  
  typedef typename boost::signals2::signal2<void, 
					    dds::DataReader<T>&,
					    const DDS::RequestedIncompatibleQosStatus&>::slot_type
  on_requested_incompatible_qos_slot_t;

  // -- on_liveliness_changed signal/slot
  typedef boost::signals2::signal2<void, 
				   dds::DataReader<T>&,
				   const DDS::LivelinessChangedStatus&> 
  on_liveliness_changed_signal_t;

  typedef typename boost::signals2::signal2<void, 
					    dds::DataReader<T>&,
					    const DDS::LivelinessChangedStatus&>::slot_type
  on_liveliness_changed_slot_t;

  // -- on_deadline_missed_status_signal_t
  typedef boost::signals2::signal2<void, 
				   dds::DataReader<T>&,
				   const DDS::RequestedDeadlineMissedStatus&>
  on_requested_deadline_missed_signal_t;

  typedef typename boost::signals2::signal2<void, 
					    dds::DataReader<T>&,
					    const DDS::RequestedDeadlineMissedStatus&>::slot_type
  on_requested_deadline_missed_slot_t;

  // -- on_sample_rejected_signal_t
  typedef boost::signals2::signal2<void, 
				   dds::DataReader<T>&,
				   const DDS::SampleRejectedStatus&> 
  on_sample_rejected_signal_t;

  typedef typename boost::signals2::signal2<void, 
					    dds::DataReader<T>&,
					    const DDS::SampleRejectedStatus&>::slot_type
  on_sample_rejected_slot_t;
  
  //-- on_subscription_matched_signal_t
  typedef boost::signals2::signal2<void, 
				   dds::DataReader<T>&,
				   const DDS::SubscriptionMatchedStatus&>
  on_subscription_matched_signal_t;
  
  typedef typename boost::signals2::signal2<void, 
					    dds::DataReader<T>&,
					    const DDS::SubscriptionMatchedStatus&>::slot_type
  on_subscription_matched_slot_t;
  
  // on_sample_lost_signal_t
  typedef boost::signals2::signal2<void, 
				   dds::DataReader<T>&,
				   const DDS::SampleLostStatus&> 
  on_sample_lost_signal_t;
  
  typedef typename boost::signals2::signal2<void, 
					    dds::DataReader<T>&,
					    const DDS::SampleLostStatus&>::slot_type 
					    on_sample_lost_slot_t;
  
public:

  DataReaderImpl(const dds::Topic<T>& topic) :
    topic_(topic),
    drqos_(topic_.get_qos())
  {
    sub_ = Runtime::instance()->get_subscriber();
    // @TODO: The Listener should be attached only when a signal is
    // connected to a slot and the mask should be updated likewise.
    DDS::DataReader* r =
      sub_->create_datareader(topic_->get_dds_topic(),
			      drqos_,
			      0,
			      0);
    //			      DDS::ANY_STATUS);
    
    boost::shared_ptr<DR> tmp(DR::_narrow(r), mem::DRDeleter(sub_));
    reader_ = tmp;
  }
  
  DataReaderImpl(const dds::Topic<T>& topic,
		 const dds::DataReaderQos& qos) :
    topic_(topic),
    drqos_(qos)
  {
    sub_ = Runtime::instance()->get_subscriber();
    // @TODO: The Listener should be attached only when a signal is
    // connected to a slot and the mask should be updated likewise.
    DDS::DataReader* r =
      sub_->create_datareader(topic_->get_dds_topic(),
			      drqos_,
			      0, 
			      0);

    boost::shared_ptr<DR> tmp(DR::_narrow(r), mem::DRDeleter(sub_));
    reader_ = tmp;
  }

  virtual ~DataReaderImpl() {
    reader_->set_listener(0, 0);
  }

public:
  
  void set_datareader(dds::DataReader<T>* dr) 
  {
    dds_reader_ = dr;
    reader_->set_listener(this, DDS::ANY_STATUS);
  }

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
    return reader_->read(samples, 
			 infos, 
			 DDS::LENGTH_UNLIMITED,
			 DDS::NOT_READ_SAMPLE_STATE, 
			 DDS::ANY_VIEW_STATE,
			 DDS::ALIVE_INSTANCE_STATE);
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
    return reader_->take(samples, 
			 infos, 
			 DDS::LENGTH_UNLIMITED,
			 DDS::ANY_SAMPLE_STATE, 
			 DDS::ANY_VIEW_STATE,
			 DDS::ALIVE_INSTANCE_STATE);
  }

  /**
   * Reads at most <code>max_samples</code> samples that have not been
   * read yet from all vies and alive instances.
   */
  DDS::ReturnCode_t 
  read(TSeq& samples, 
       long max_samples) 
  {
    DDS::SampleInfoSeq infos(max_samples);
    return reader_->read(samples, 
			 infos, 
			 max_samples,
			 DDS::NOT_READ_SAMPLE_STATE, 
			 DDS::ANY_VIEW_STATE,
			 DDS::ALIVE_INSTANCE_STATE);
  }

  /**
   * Takes at most <code>max_samples</code> samples that have not been
   * read yet from all vies and alive instances.
   */
  DDS::ReturnCode_t 
  take(TSeq& samples, 
       long max_samples) 
  {
    DDS::SampleInfoSeq infos(max_samples);
    return reader_->take(samples, 
			 infos, 
			 max_samples,
			 DDS::NOT_READ_SAMPLE_STATE, 
			 DDS::ANY_VIEW_STATE,
			 DDS::ALIVE_INSTANCE_STATE);
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
    return reader_->read(samples, 
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
    return reader_->read(samples, 
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
    return reader_->return_loan(samples, infos);
  }

  boost::shared_ptr<DataInstanceReader<T> > 
  get_instance_reader(const T& key) 
  {
    boost::shared_ptr<DataInstanceReader<T> > ireader(new DataInstanceReader<T> (reader_, key));
    return ireader;
  }

  // -- Qos Getter/Setter

  dds::DataReaderQos 
  get_qos() 
  {
    return drqos_;
  }

  DDS::ReturnCode_t 
  set_qos(const dds::DataReaderQos& qos) 
  {
    DDS::ReturnCode_t rc = reader_->set_qos(qos);
    if (rc == DDS::RETCODE_OK)
      drqos_ = qos;
    return rc;
  }

  boost::shared_ptr<DDS::Subscriber> 
  get_subscriber() {
    return sub_;
  }

  dds::Topic<T> 
  get_topic() 
  {
    return topic_;
  }

  DDS::ReturnCode_t 
  wait_for_historical_data(const DDS::Duration_t timeout) 
  {
    return reader_->wait_for_historical_data(timeout);
  }

  // -- Condition API
  /**
   * Creates an <code>ActiveReadCondition</code> that waits for new samples to
   * be arriving in order to notify.
   */
  // ::dds::ActiveReadCondition
  template <typename F>
  ::dds::ActiveReadCondition
  create_readcondition(const F& f)
  {
    DDS::ReadCondition* rc =
      reader_->create_readcondition(DDS::NOT_READ_SAMPLE_STATE,
				    DDS::ANY_VIEW_STATE,
				    DDS::ALIVE_INSTANCE_STATE);
		
    ::dds::mem::RCondDeleter<DR> deleter(reader_);
    ::boost::shared_ptr <DDS::ReadCondition> rrc(rc, deleter);
    ::dds::iActiveReadCondition < dds::DataReader<T>, F> ardc(rrc, 
							      *dds_reader_, 
							      f);
    return ardc;
  }

public:
  
  
  void on_requested_deadline_missed(DDS::DataReader*,
				    const DDS::RequestedDeadlineMissedStatus& status) 
  {
    on_requested_deadline_missed_signal_(*dds_reader_, status);
  }

  void on_requested_incompatible_qos(DDS::DataReader*,
				     const DDS::RequestedIncompatibleQosStatus& status) 
  {
    on_requested_incompatible_qos_signal_(*dds_reader_, status);
  }

  void on_sample_rejected(DDS::DataReader*,
			  const DDS::SampleRejectedStatus& status) 
  {
    on_sample_rejected_signal_(*dds_reader_, status);
  }

  void on_liveliness_changed(DDS::DataReader*,
			     const DDS::LivelinessChangedStatus& status) 
  {
    on_liveliness_changed_signal_(*dds_reader_, status);
  }

  void on_data_available(DDS::DataReader*) {
    on_data_available_signal_(*dds_reader_);
  }

  void on_subscription_matched(DDS::DataReader*,
			       const DDS::SubscriptionMatchedStatus& status) 
  {
    on_subscription_matched_signal_(*dds_reader_, status);
  }

    void on_sample_lost(DDS::DataReader*,
			const DDS::SampleLostStatus& status) 
  {
    on_sample_lost_signal_(*dds_reader_, status);
  }

public:

  dds::sigcon_t
  on_data_available_signal_connect(on_data_available_slot_t slot) 
  {
    return on_data_available_signal_.connect(slot);
  }

  dds::sigcon_t
  on_requested_incompatible_qos_signal_connect(on_requested_incompatible_qos_slot_t slot) 
  {
    return on_requested_incompatible_qos_signal_.connect(slot);
  }

  dds::sigcon_t 
  on_liveliness_changed_signal_connect(on_liveliness_changed_slot_t slot) 
  {
    return on_liveliness_changed_signal_.connect(slot);
  }
  
  dds::sigcon_t 
  on_requested_deadline_missed_signal_connect(on_requested_deadline_missed_slot_t slot) 
  {
    return on_requested_deadline_missed_signal_.connect(slot);
  }

  dds::sigcon_t 
  on_sample_rejected_signal_connect(on_sample_rejected_slot_t slot) 
  {
    return on_sample_rejected_signal_.connect(slot);
  }

  dds::sigcon_t 
  on_subscription_matched_signal_connect(on_subscription_matched_slot_t slot) 
  {
    return on_subscription_matched_signal_.connect(slot);
  }

  dds::sigcon_t 
  on_sample_lost_signal_connect(on_sample_lost_slot_t slot) 
  {
    return on_sample_lost_signal_.connect(slot);
  }

protected:
  // -- Signals
  on_data_available_signal_t             on_data_available_signal_;
  on_requested_incompatible_qos_signal_t on_requested_incompatible_qos_signal_;
  on_liveliness_changed_signal_t         on_liveliness_changed_signal_;
  on_requested_deadline_missed_signal_t  on_requested_deadline_missed_signal_;
  on_sample_rejected_signal_t            on_sample_rejected_signal_;
  on_subscription_matched_signal_t       on_subscription_matched_signal_;
  on_sample_lost_signal_t                on_sample_lost_signal_;

protected:
  dds::Topic<T>                               topic_;
  boost::shared_ptr<DDS::Subscriber>          sub_;
  boost::shared_ptr<DR>                       reader_;
  dds::DataReaderQos                          drqos_;
  boost::shared_ptr<DDS::DataReaderListener>  listener_;
  dds::DataReader<T>*                         dds_reader_;
};

#endif /* AC_SIMD_DDS_READER_IMPL_HPP_ */
