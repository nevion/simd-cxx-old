#ifndef AC_SIMD_READER_HPP
#define AC_SIMD_READER_HPP

// -- BOOST Includes
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <boost/signals2/signal.hpp>


// -- SIMD Includes
#include <simd/runtime.hpp>
#include <simd/memory.hpp>
#include <simd/traits.hpp>
#include <simd/topic.hpp>


namespace simd {
  template <typename T>
  class DataReader;

  template <typename T>
  class DataInstanceReader;
}

template <typename T>
class simd::DataReader 
{
public:
  typedef typename simd::topic_data_reader<T>::type DR;
  typedef typename simd::topic_data_seq<T>::type TSeq;

public:
  // -- on_data_available signal/slot
  typedef boost::signals2::signal1<void,
				   DataReader<T>&>
  on_data_available_signal_t;

  typedef typename boost::signals2::signal1<void,
					    DataReader<T>&>::slot_type
  on_data_available_slot_t;

  // -- on_requested_incompatible_qos signal/slot
  typedef boost::signals2::signal2<void,
                                   DataReader<T>&,
                                   const DDS::RequestedIncompatibleQosStatus&>
  on_requested_incompatible_qos_signal_t;

typedef typename boost::signals2::signal2<void,
					  DataReader<T>&,
					  const DDS::RequestedIncompatibleQosStatus&>::slot_type
on_requested_incompatible_qos_slot_t;

  // -- on_liveliness_changed singal/slot
  typedef boost::signals2::signal2<void,
				   DataReader<T>&,
				   const DDS::LivelinessChangedStatus&>
  on_liveliness_changed_signal_t;

typedef typename boost::signals2::signal2<void,
					  DataReader<T>&,
					  const DDS::LivelinessChangedStatus&>::slot_type
on_liveliness_changed_slot_t;

  // -- on_deadline_missed_status_signal_t
  typedef  boost::signals2::signal2<void,
				    DataReader<T>&,
				    const DDS::RequestedDeadlineMissedStatus&>
  on_requested_deadline_missed_signal_t;

typedef typename boost::signals2::signal2<void,
					  DataReader<T>&,
					  const DDS::RequestedDeadlineMissedStatus&>::slot_type
on_requested_deadline_missed_slot_t;

  // -- on_sample_rejected_signal_t
  typedef  boost::signals2::signal2<void,
				    DataReader<T>&,
				    const DDS::SampleRejectedStatus&>
  on_sample_rejected_signal_t;

typedef typename boost::signals2::signal2<void,
					  DataReader<T>&,
					  const DDS::SampleRejectedStatus&>::slot_type
on_sample_rejected_slot_t;

  //-- on_subscription_matched_signal_t
  typedef  boost::signals2::signal2<void,
				    DataReader<T>&,
				    const DDS::SubscriptionMatchedStatus&>
  on_subscription_matched_signal_t;

typedef  typename boost::signals2::signal2<void,
					   DataReader<T>&,
					   const DDS::SubscriptionMatchedStatus&>::slot_type
on_subscription_matched_slot_t;

  // on_sample_lost_signal_t
  typedef  boost::signals2::signal2<void,
				    DataReader<T>&,
				    const DDS::SampleLostStatus&>
  on_sample_lost_signal_t;

typedef typename boost::signals2::signal2<void,
					  DataReader<T>&,
					  const DDS::SampleLostStatus&>::slot_type
on_sample_lost_slot_t;

public:

  DataReader(simd::Topic<T>& topic)
  {
    listener_ = new DataReaderListener(*this);
    sub_ =
      simd::Runtime::instance()->get_subscriber();

    simd::TopicQos tqos(topic.get_qos());
    simd::DataReaderQos drqos(tqos);
    DDS::DataReader* r =
      sub_->create_datareader(topic.get_dds_topic(),
			      drqos,
			      listener_,
			      DDS::ANY_STATUS);

    boost::shared_ptr<DR> tmp(DR::_narrow(r),
			      simd::mem::DRDeleter(sub_));
    reader_ = tmp;
  }

  DataReader(simd::Topic<T>& topic, const simd::DataReaderQos& qos)
  {
    listener_ = new DataReaderListener(*this);
    sub_ =
      simd::Runtime::instance()->get_subscriber();

    DDS::DataReader* w =
      sub_->create_datareader(topic.get_dds_topic(),
			      qos,
			      listener_,
			      DDS::ANY_STATUS);

    boost::shared_ptr<DR> tmp(DR::_narrow(w),
			      simd::mem::DRDeleter(sub_));
    reader_ = tmp;
  }

  ~DataReader() {
  }

public:

  /**
   * Reads all new samples from any view state and alive instances. Notice
   * that this call is intended to loan the <code>samples</code> as
   * well as the <conde>infos</code> containers, thus will require a
   * return_loan.
   */
  DDS::ReturnCode_t read(TSeq& samples, DDS::SampleInfoSeq& infos) {
    return reader_->read(samples,
			 infos,
			 DDS::LENGTH_UNLIMITED,
			 DDS::NOT_READ_SAMPLE_STATE,
			 DDS::ANY_VIEW_STATE,
			 DDS::ANY_INSTANCE_STATE);
  }

  /**
   * Takes all new samples from any view state and alive instances. Notice
   * that this call is intended to loan the <code>samples</code> as
   * well as the <conde>infos</code> containers, thus will require a
   * return_loan.
   */
  DDS::ReturnCode_t take(TSeq& samples, DDS::SampleInfoSeq& infos) {
    return reader_->take(samples,
			 infos,
			 DDS::LENGTH_UNLIMITED,
			 DDS::NOT_READ_SAMPLE_STATE,
			 DDS::ANY_VIEW_STATE,
			 DDS::ANY_INSTANCE_STATE);
  }

  /**
   * Reads at most <code>max_samples</code> samples that have not been
   * read yet from all vies and alive instances.
   */
  DDS::ReturnCode_t read(TSeq& samples,
			 long max_samples) {
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
  DDS::ReturnCode_t take(TSeq& samples,
			 long max_samples) {
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
  DDS::ReturnCode_t read(TSeq& samples,
			 DDS::SampleInfoSeq& infos,
			 long max_samples,
			 DDS::SampleStateMask samples_state,
			 DDS::ViewStateMask views_state,
			 DDS::InstanceStateMask instances_state) {
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
  DDS::ReturnCode_t take(TSeq& samples,
			 DDS::SampleInfoSeq& infos,
			 long max_samples,
			 DDS::SampleStateMask samples_state,
			 DDS::ViewStateMask views_state,
			 DDS::InstanceStateMask instances_state) {
    return reader_->read(samples,
			 infos,
			 max_samples,
			 samples_state,
			 views_state,
			 instances_state);
  }

  DDS::ReturnCode_t return_loan(TSeq& samples, DDS::SampleInfoSeq& infos) {
    return reader_->return_loan(samples, infos);
  }

  boost::shared_ptr<simd::DataInstanceReader<T> >
  get_instance_reader(const T& key) {
    boost::shared_ptr<simd::DataInstanceReader<T> >
      ireader(new simd::DataInstanceReader<T > (reader_, key));
    return ireader;
  }

protected:

  void on_data_available_notify() {
    on_data_available_signal_(*this);
  }

  void on_requested_incompatible_qos_notify(const DDS::RequestedIncompatibleQosStatus& status) {
    on_requested_incompatible_qos_signal_(*this, status);
  }

  void on_liveliness_changed_notify(const DDS::LivelinessChangedStatus& status) {
    on_liveliness_changed_signal_(*this, status);
  }
protected:

  class DataReaderListener : public virtual DDS::DataReaderListener {
  public:

    DataReaderListener(DataReader<T>& reader)
      : reader_(reader) {
    }

    virtual ~DataReaderListener() {
    }

  public:

    void
    on_requested_deadline_missed(DDS::DataReader* reader,
				 const DDS::RequestedDeadlineMissedStatus& status) {
    }

    void
    on_requested_incompatible_qos(DDS::DataReader* reader,
				  const DDS::RequestedIncompatibleQosStatus& status) {
    }

    void
    on_sample_rejected(DDS::DataReader* reader,
		       const DDS::SampleRejectedStatus& status) {
    }

    void
    on_liveliness_changed(DDS::DataReader* reader,
			  const DDS::LivelinessChangedStatus& status) {
    }

    void
    on_data_available(DDS::DataReader* reader) {
      reader_.on_data_available_notify();
    }

    void
    on_subscription_matched(DDS::DataReader* reader,
			    const DDS::SubscriptionMatchedStatus& status) {
    }

    void
    on_sample_lost(DDS::DataReader* reader,
		   const DDS::SampleLostStatus& status) {
    }
  private:
    DataReader<T>& reader_;
  };
public:
  boost::signals2::connection
  on_data_available_signal_connect(on_data_available_slot_t slot) {
    return on_data_available_signal_.connect(slot);
  }
    
  boost::signals2::connection
  on_requested_incompatible_qos_signal_connect(on_requested_incompatible_qos_slot_t slot) {
    return on_requested_incompatible_qos_signal_.connect(slot);
  }
    
  boost::signals2::connection
  on_liveliness_changed_signal_connect(on_liveliness_changed_slot_t slot) {
    return on_liveliness_changed_signal_.connect(slot);
  }

  boost::signals2::connection
  on_requested_deadline_missed_signal_connect(on_requested_deadline_missed_slot_t slot) {
    return on_requested_deadline_missed_signal_.connect(slot);
  }

  boost::signals2::connection
  on_sample_rejected_signal_connect(on_sample_rejected_slot_t slot) {
    return on_sample_rejected_signal_.connect(slot);
  }

  boost::signals2::connection
  on_subscription_matched_signal_connect(on_subscription_matched_slot_t slot) {
    return on_subscription_matched_signal_.connect(slot);
  }
    
  boost::signals2::connection
  on_sample_lost_signal_connect(on_sample_lost_slot_t slot) {
    return on_sample_lost_signal_.connect(slot);
  }

protected:
  on_data_available_signal_t on_data_available_signal_;
  on_requested_incompatible_qos_signal_t on_requested_incompatible_qos_signal_;
  on_liveliness_changed_signal_t on_liveliness_changed_signal_;
  on_requested_deadline_missed_signal_t on_requested_deadline_missed_signal_;
  on_sample_rejected_signal_t on_sample_rejected_signal_;
  on_subscription_matched_signal_t on_subscription_matched_signal_;
  on_sample_lost_signal_t on_sample_lost_signal_;

protected:
  boost::shared_ptr<DDS::Subscriber> sub_;
  boost::shared_ptr<DR> reader_;

  DataReaderListener* listener_;
};


#endif /* AC_SIMD_READER_HPP */
