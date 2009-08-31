#ifndef AC_SIMD_READER_HPP
#define AC_SIMD_READER_HPP

#include <iostream>

// -- BOOST Includes
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <boost/signals2/signal.hpp>

// -- SIMD Includes
#include <simd/runtime.hpp>
#include <simd/memory.hpp>
#include <simd/traits.hpp>
#include <simd/topic.hpp>
#include <simd/condition.hpp>

namespace simd {

template<typename T>
class DataInstanceReader;

template<typename T>
class DataReader;

template<typename T>
class DataReaderImpl {
public:
	typedef typename topic_data_reader<T>::type DR;
	typedef typename topic_data_seq<T>::type TSeq;

public:
	// -- on_data_available signal/slot
	typedef boost::signals2::signal1< void, DataReader<T> >
	on_data_available_signal_t;

	typedef typename boost::signals2::signal1<void, DataReader<T> >::slot_type
	on_data_available_slot_t;

	// -- on_requested_incompatible_qos signal/slot
	typedef boost::signals2::signal2<void, DataReader<T>,
	const DDS::RequestedIncompatibleQosStatus&>
	on_requested_incompatible_qos_signal_t;

	typedef typename boost::signals2::signal2<void, DataReader<T>,
	const DDS::RequestedIncompatibleQosStatus&>::slot_type
	on_requested_incompatible_qos_slot_t;

	// -- on_liveliness_changed signal/slot
	typedef boost::signals2::signal2<void, DataReader<T>,
	const DDS::LivelinessChangedStatus&> on_liveliness_changed_signal_t;

	typedef typename boost::signals2::signal2<void, DataReader<T>,
	const DDS::LivelinessChangedStatus&>::slot_type
	on_liveliness_changed_slot_t;

	// -- on_deadline_missed_status_signal_t
	typedef boost::signals2::signal2<void, DataReader<T>,
	const DDS::RequestedDeadlineMissedStatus&>
	on_requested_deadline_missed_signal_t;

	typedef typename boost::signals2::signal2<void, DataReader<T>,
	const DDS::RequestedDeadlineMissedStatus&>::slot_type
	on_requested_deadline_missed_slot_t;

	// -- on_sample_rejected_signal_t
	typedef boost::signals2::signal2<void, DataReader<T>,
	const DDS::SampleRejectedStatus&> on_sample_rejected_signal_t;

	typedef typename boost::signals2::signal2<void, DataReader<T>,
	const DDS::SampleRejectedStatus&>::slot_type
	on_sample_rejected_slot_t;

	//-- on_subscription_matched_signal_t
	typedef boost::signals2::signal2<void, DataReader<T>,
	const DDS::SubscriptionMatchedStatus&>
	on_subscription_matched_signal_t;

	typedef typename boost::signals2::signal2<void, DataReader<T>,
	const DDS::SubscriptionMatchedStatus&>::slot_type
	on_subscription_matched_slot_t;

	// on_sample_lost_signal_t
	typedef boost::signals2::signal2<void, DataReader<T>,
	const DDS::SampleLostStatus&> on_sample_lost_signal_t;

	typedef typename boost::signals2::signal2<void, DataReader<T>,
	const DDS::SampleLostStatus&>::slot_type on_sample_lost_slot_t;

public:

	DataReaderImpl(Topic<T> topic, DataReader<T>& simd_reader) :
		topic_(topic),
		drqos_(topic->get_qos()),
		simd_reader_(simd_reader)
		{
		listener_.reset(new DataReaderListener(*this));
		sub_ = Runtime::instance()->get_subscriber();
		// @TODO: The Listener should be attached only when a signal is
		// connected to a slot and the mask should be updated likewise.
		DDS::DataReader* r =
				sub_->create_datareader(topic->get_dds_topic(),
						drqos_,
						listener_.get(),
						DDS::ANY_STATUS);

		boost::shared_ptr<DR> tmp(DR::_narrow(r), mem::DRDeleter(sub_));
		reader_ = tmp;
		}

	DataReaderImpl(Topic<T> topic,
			const DataReaderQos& qos,
			DataReader<T>& simd_reader) :
				topic_(topic),
				drqos_(qos),
				simd_reader_(simd_reader)
				{
		listener_.reset(new DataReaderListener(*this));
		sub_ = Runtime::instance()->get_subscriber();
		// @TODO: The Listener should be attached only when a signal is
		// connected to a slot and the mask should be updated likewise.
		DDS::DataReader* r =
				sub_->create_datareader(topic->get_dds_topic(),
						drqos_,
						listener_.get(),
						DDS::ANY_STATUS);

		boost::shared_ptr<DR> tmp(DR::_narrow(r), mem::DRDeleter(sub_));
		reader_ = tmp;
				}

	virtual ~DataReaderImpl() {
		reader_->set_listener(0, 0);
	}

public:

	/**
	* Reads all new samples from any view state and alive instances. Notice
	* that this call is intended to loan the <code>samples</code> as
	* well as the <conde>infos</code> containers, thus will require a
	* return_loan.
	*/
	DDS::ReturnCode_t read(TSeq& samples, DDS::SampleInfoSeq& infos) {
		return reader_->read(samples, infos, DDS::LENGTH_UNLIMITED,
				DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
				DDS::ALIVE_INSTANCE_STATE);
	}

	/**
	* Takes all new samples from any view state and alive instances. Notice
	* that this call is intended to loan the <code>samples</code> as
	* well as the <conde>infos</code> containers, thus will require a
	* return_loan.
	*/
	DDS::ReturnCode_t take(TSeq& samples, DDS::SampleInfoSeq& infos) {
		return reader_->take(samples, infos, DDS::LENGTH_UNLIMITED,
				DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
				DDS::ALIVE_INSTANCE_STATE);
	}

	/**
	* Reads at most <code>max_samples</code> samples that have not been
	* read yet from all vies and alive instances.
	*/
	DDS::ReturnCode_t read(TSeq& samples, long max_samples) {
		DDS::SampleInfoSeq infos(max_samples);
		return reader_->read(samples, infos, max_samples,
				DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
				DDS::ALIVE_INSTANCE_STATE);
	}

	/**
	* Takes at most <code>max_samples</code> samples that have not been
	* read yet from all vies and alive instances.
	*/
	DDS::ReturnCode_t take(TSeq& samples, long max_samples) {
		DDS::SampleInfoSeq infos(max_samples);
		return reader_->take(samples, infos, max_samples,
				DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
				DDS::ALIVE_INSTANCE_STATE);
	}

	/**
	* Most generic <code>read</code> exposing all the knobs provided by
	* the OMG DDS API.
	*/
	DDS::ReturnCode_t read(TSeq& samples, DDS::SampleInfoSeq& infos,
			long max_samples, DDS::SampleStateMask samples_state,
			DDS::ViewStateMask views_state,
			DDS::InstanceStateMask instances_state) {
		return reader_->read(samples, infos, max_samples, samples_state,
				views_state, instances_state);
	}

	/**
	* Most generic <code>take</code> exposing all the knobs provided by
	* the OMG DDS API.
	*/
	DDS::ReturnCode_t take(TSeq& samples, DDS::SampleInfoSeq& infos,
			long max_samples, DDS::SampleStateMask samples_state,
			DDS::ViewStateMask views_state,
			DDS::InstanceStateMask instances_state) {
		return reader_->read(samples, infos, max_samples, samples_state,
				views_state, instances_state);
	}

	DDS::ReturnCode_t return_loan(TSeq& samples, DDS::SampleInfoSeq& infos) {
		return reader_->return_loan(samples, infos);
	}

	boost::shared_ptr<DataInstanceReader<T> > get_instance_reader(const T& key) {
		boost::shared_ptr<DataInstanceReader<T> > ireader(
				new DataInstanceReader<T> (reader_, key));
		return ireader;
	}

	// -- Qos Getter/Setter

	DataReaderQos get_qos() {
		return drqos_;
	}

	DDS::ReturnCode_t set_qos(const DataReaderQos& qos) {
		DDS::ReturnCode_t rc = reader_->set_qos(qos);
		if (rc == DDS::RETCODE_OK)
			drqos_ = qos;
		return rc;
	}

	boost::shared_ptr<DDS::Subscriber> get_subscriber() {
		return sub_;
	}

	Topic<T> get_topic() {
		return topic_;
	}

	DDS::ReturnCode_t wait_for_historical_data(const DDS::Duration_t timeout) {
		return reader_->wait_for_historical_data(timeout);
	}

	// -- Condition API
	/**
	* Creates a <code>ReadCondition</code> that waits for new samples to
	* be arriving in order to notify.
	*/
	::simd::RDCondition create_readcondition() {
		DDS::ReadCondition* rc =
				reader_->create_readcondition(DDS::NOT_READ_SAMPLE_STATE,
						DDS::ANY_VIEW_STATE,
						DDS::ALIVE_INSTANCE_STATE);

		simd::mem::RCondDeleter<DR> deleter(reader_);

		::simd::RDCondition src(rc, deleter);
		return src;
	}

protected:

	void on_data_available_notify() {
		DataReader<T> dr(simd_reader_);
		on_data_available_signal_(dr);
	}

	void on_requested_incompatible_qos_notify(const DDS::RequestedIncompatibleQosStatus& status) {
		DataReader<T> dr(simd_reader_);
		on_requested_incompatible_qos_signal_(dr, status);
	}

	void on_liveliness_changed_notify(const DDS::LivelinessChangedStatus& status) {
		DataReader<T> dr(simd_reader_);
		on_liveliness_changed_signal_(dr, status);
	}

	void on_requested_deadline_missed_notify(const DDS::RequestedDeadlineMissedStatus& status) {
		DataReader<T> dr(simd_reader_);
		on_requested_deadline_missed_signal_(dr, status);
	}

	void on_sample_rejected_notify(const DDS::SampleRejectedStatus& status) {
		DataReader<T> dr(simd_reader_);
		on_sample_rejected_signal_(dr, status);
	}

	void on_subscription_matched_notify(const DDS::SubscriptionMatchedStatus& status) {
		DataReader<T> dr(simd_reader_);
		on_subscription_matched_signal_(dr, status);
	}

	void on_sample_lost_notify(const DDS::SampleLostStatus& status) {
		DataReader<T> dr(simd_reader_);
		on_sample_lost_signal_(dr, status);
	}

protected:

	class DataReaderListener: public virtual DDS::DataReaderListener {
	public:

		DataReaderListener(DataReaderImpl<T>& reader) :
			reader_(reader) {
		}

		virtual ~DataReaderListener() {
		}

	public:

		void on_requested_deadline_missed(DDS::DataReader* reader,
				const DDS::RequestedDeadlineMissedStatus& status) {
			reader_.on_requested_deadline_missed_notify(status);
		}

		void on_requested_incompatible_qos(DDS::DataReader* reader,
				const DDS::RequestedIncompatibleQosStatus& status) {
			reader_.on_requested_incompatible_qos_notify(status);
		}

		void on_sample_rejected(DDS::DataReader* reader,
				const DDS::SampleRejectedStatus& status) {
			reader_.on_sample_rejected_notify(status);
		}

		void on_liveliness_changed(DDS::DataReader* reader,
				const DDS::LivelinessChangedStatus& status) {
			reader_.on_liveliness_changed_notify(status);
		}

		void on_data_available(DDS::DataReader* reader) {
			reader_.on_data_available_notify();
		}

		void on_subscription_matched(DDS::DataReader* reader,
				const DDS::SubscriptionMatchedStatus& status) {
			reader_.on_subscription_matched_notify(status);
		}

		void on_sample_lost(DDS::DataReader* reader,
				const DDS::SampleLostStatus& status) {
			reader_.on_sample_lost_notify(status);
		}
	private:
		DataReaderImpl<T>& reader_;
	};
	public:

	boost::signals2::connection on_data_available_signal_connect(
			on_data_available_slot_t slot) {
		return on_data_available_signal_.connect(slot);
	}

	boost::signals2::connection on_requested_incompatible_qos_signal_connect(
			on_requested_incompatible_qos_slot_t slot) {
		return on_requested_incompatible_qos_signal_.connect(slot);
	}

	boost::signals2::connection on_liveliness_changed_signal_connect(
			on_liveliness_changed_slot_t slot) {
		return on_liveliness_changed_signal_.connect(slot);
	}

	boost::signals2::connection on_requested_deadline_missed_signal_connect(
			on_requested_deadline_missed_slot_t slot) {
		return on_requested_deadline_missed_signal_.connect(slot);
	}

	boost::signals2::connection on_sample_rejected_signal_connect(
			on_sample_rejected_slot_t slot) {
		return on_sample_rejected_signal_.connect(slot);
	}

	boost::signals2::connection on_subscription_matched_signal_connect(
			on_subscription_matched_slot_t slot) {
		return on_subscription_matched_signal_.connect(slot);
	}

	boost::signals2::connection on_sample_lost_signal_connect(
			on_sample_lost_slot_t slot) {
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
	Topic<T>									   topic_;
	boost::shared_ptr<DDS::Subscriber> 	sub_;
	boost::shared_ptr<DR> 				   reader_;
	DataReaderQos 							   drqos_;
	boost::shared_ptr<DDS::DataReaderListener> listener_;
	DataReader<T>&                      simd_reader_;
};

template <typename T>
class DataReader : public ::boost::shared_ptr< DataReaderImpl<T> > {
public:
	DataReader(Topic<T> topic) {
		this->reset(new DataReaderImpl<T>(topic, *this));
	}

	DataReader(Topic<T> topic, const DataReaderQos& qos) {
		this->reset(new DataReaderImpl<T>(topic, qos, *this));
	}

	virtual ~DataReader() {	}
};
}
#endif /* AC_SIMD_READER_HPP */
