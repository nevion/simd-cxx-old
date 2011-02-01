#ifndef AC_SIMD_DDS_READER_IMPL_HPP_
#define AC_SIMD_DDS_READER_IMPL_HPP_

#include <iostream>
// -- Boost Includes
#include <boost/tuple/tuple.hpp>

// -- SIMD_DDS Includes
#include <dds/dds.hpp>
#include <dds/runtime.hpp>
#include <dds/memory.hpp>
#include <dds/traits.hpp>
#include <dds/topic.hpp>
#include <dds/peer/condition_impl.hpp>
#include <dds/condition.hpp>
#include <dds/subscriber.hpp>
#include <dds/content_filtered_topic.hpp>
#include <dds/signals.hpp>

namespace dds {
namespace peer {

template<typename T>
class DataReaderImpl: public DDS::DataReaderListener {
public:
	typedef typename topic_data_reader<T>::type DR;
	typedef typename topic_data_seq<T>::type TSeq;

public:

	DataReaderImpl(const dds::Topic<T>& topic) :
		topic_(topic), drqos_(topic_.get_qos()) {
		sub_ = ::dds::peer::RuntimeImpl::instance().get_subscriber();
		DDS::DataReader* r = sub_->create_datareader(topic_->get_dds_topic(),
				drqos_, 0, 0);

		dds::Assert::precondition(r != 0, "Unable to create DataReader",
				__FILE__);
		boost::shared_ptr<DR> tmp(DR::_narrow(r), mem::DRDeleter(sub_));
		reader_ = tmp;
	}

	DataReaderImpl(const dds::Topic<T>& topic, const dds::DataReaderQos& qos) :
		topic_(topic), drqos_(qos) {
		sub_ = ::dds::peer::RuntimeImpl::instance().get_subscriber();
		DDS::DataReader* r = sub_->create_datareader(topic_->get_dds_topic(),
				drqos_, 0, 0);

		boost::shared_ptr<DR> tmp(DR::_narrow(r), mem::DRDeleter(sub_));
		reader_ = tmp;
	}

	DataReaderImpl(const dds::Topic<T>& topic, const dds::DataReaderQos& qos,
			const dds::Subscriber& sub) :
		topic_(topic), drqos_(qos), sub_(sub) {
		DDS::DataReader* r = sub_->create_datareader(topic_->get_dds_topic(),
				drqos_, 0, 0);

		boost::shared_ptr<DR> tmp(DR::_narrow(r), mem::DRDeleter(sub_));
		reader_ = tmp;
	}

	DataReaderImpl(const ContentFilteredTopic<T>& cftopic) :
		topic_(cftopic.get_related_topic()), cftopic_(cftopic), drqos_(
				topic_.get_qos()) {
		sub_ = ::dds::peer::RuntimeImpl::instance().get_subscriber();
		DDS::DataReader* r = sub_->create_datareader(cftopic_->get_dds_topic(),
				drqos_, 0, 0);

		boost::shared_ptr<DR> tmp(DR::_narrow(r), mem::DRDeleter(sub_));
		reader_ = tmp;
	}

	DataReaderImpl(const dds::ContentFilteredTopic<T>& cftopic,
			const dds::DataReaderQos& qos) :
		topic_(cftopic.get_related_topic()), cftopic_(cftopic), drqos_(qos) {
		sub_ = ::dds::peer::RuntimeImpl::instance().get_subscriber();
		DDS::DataReader* r = sub_->create_datareader(cftopic_->get_dds_topic(),
				drqos_, 0, 0);

		boost::shared_ptr<DR> tmp(DR::_narrow(r), mem::DRDeleter(sub_));
		reader_ = tmp;
	}

	DataReaderImpl(const dds::ContentFilteredTopic<T>& cftopic,
			const dds::DataReaderQos& qos, const dds::Subscriber& sub) :
		topic_(cftopic.get_related_topic()), cftopic_(cftopic), drqos_(qos),
				sub_(sub) {
		DDS::DataReader* r = sub_->create_datareader(cftopic_->get_dds_topic(),
				drqos_, 0, 0);

		boost::shared_ptr<DR> tmp(DR::_narrow(r), mem::DRDeleter(sub_));
		reader_ = tmp;
	}

	~DataReaderImpl() {
		reader_->set_listener(0, 0);
	}

public:

	void set_datareader(dds::DataReader<T>* dr) {
		dds_reader_ = dr;
		reader_->set_listener(this, DDS::ANY_STATUS);
	}

	/**
	 * Reads all new samples from any view state and alive instances. Notice
	 * that this call is intended to loan the <code>samples</code> as
	 * well as the <conde>infos</code> containers, thus will require a
	 * return_loan.
	 */
	inline DDS::ReturnCode_t read(TSeq& samples, DDS::SampleInfoSeq& infos) {
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
	inline DDS::ReturnCode_t take(TSeq& samples, DDS::SampleInfoSeq& infos) {
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
		return reader_->take(samples, infos, max_samples, samples_state,
				views_state, instances_state);
	}

	////////////////////////////////////////////////////////////////////////
	DDS::ReturnCode_t return_loan(TSeq& samples, DDS::SampleInfoSeq& infos) {
		return reader_->return_loan(samples, infos);
	}

	////////////////////////////////////////////////////////////////////////
	// -- ForwardIterator read/take
	template<typename DataForwardIterator, typename InfoForwardIterator>
	uint32_t read(DataForwardIterator data_begin,
			InfoForwardIterator info_begin, uint32_t max_samples,
			DDS::SampleStateMask samples_state, DDS::ViewStateMask views_state,
			DDS::InstanceStateMask instances_state) {
		//@TODO: Static assert on iterator tag
		TSeq data;
		DDS::SampleInfoSeq info;
		uint32_t size;
		reader_->read(data, info, max_samples, samples_state, views_state,
				instances_state);

		size = data.length();
		for (uint32_t i = 0; i < size; ++i) {
			*data_begin = data[i];
			*info_begin = info[i];
			++data_begin;
			++info_begin;
		}
		return_loan(data, info);
		return size;
	}

	template<typename DataForwardIterator, typename InfoForwardIterator>
	uint32_t read(DataForwardIterator data_begin,
			InfoForwardIterator info_begin, uint32_t max_samples) {
		return read(data_begin, info_begin, max_samples,
				DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
				DDS::ALIVE_INSTANCE_STATE);
	}

	template<typename DataForwardIterator>
	uint32_t read(DataForwardIterator data_begin, uint32_t max_samples) {
		TSeq data;
		DDS::SampleInfoSeq info;
		uint32_t size;
		reader_->read(data, info, max_samples, DDS::NOT_READ_SAMPLE_STATE,
				DDS::ANY_VIEW_STATE, DDS::ALIVE_INSTANCE_STATE);

		size = data.length();
		for (uint32_t i = 0; i < size; ++i) {
			*data_begin = data[i];
			++data_begin;
		}
		return_loan(data, info);
		return size;
	}

	template<typename DataForwardIterator, typename InfoForwardIterator>
	uint32_t take(DataForwardIterator data_begin,
			InfoForwardIterator info_begin, uint32_t max_samples,
			DDS::SampleStateMask samples_state, DDS::ViewStateMask views_state,
			DDS::InstanceStateMask instances_state) {
		//@TODO: Static assert on iterator tag
		TSeq data;
		DDS::SampleInfoSeq info;
		uint32_t size;
		reader_->take(data, info, max_samples, samples_state, views_state,
				instances_state);

		size = data.length();
		for (uint32_t i = 0; i < size; ++i) {
			*data_begin = data[i];
			*info_begin = info[i];
			++data_begin;
			++info_begin;
		}
		return_loan(data, info);
		return size;
	}

	template<typename DataForwardIterator, typename InfoForwardIterator>
	uint32_t take(DataForwardIterator data_begin,
			InfoForwardIterator info_begin, uint32_t max_samples) {
		return read(data_begin, info_begin, max_samples,
				DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
				DDS::ALIVE_INSTANCE_STATE);
	}

	template<typename DataForwardIterator>
	uint32_t take(DataForwardIterator data_begin, uint32_t max_samples) {
		TSeq data;
		DDS::SampleInfoSeq info;
		uint32_t size;
		reader_->take(data, info, max_samples, DDS::ANY_VIEW_STATE,
				DDS::ALIVE_INSTANCE_STATE);

		size = data.length();
		for (uint32_t i = 0; i < size; ++i) {
			*data_begin = data[i];
			++data_begin;
		}
		return_loan(data, info);
		return size;
	}
	////////////////////////////////////////////////////////////////////////
	// -- OutputIterator read/take
	template<typename DataOutputIterator, typename InfoOutputIterator>
	uint32_t read(DataOutputIterator data_begin, InfoOutputIterator info_begin,
			DDS::SampleStateMask samples_state, DDS::ViewStateMask views_state,
			DDS::InstanceStateMask instances_state) {
		//@TODO: Static assert on iterator tag
		TSeq data;
		DDS::SampleInfoSeq info;
		uint32_t size;
		reader_->read(data, info, DDS::LENGTH_UNLIMITED, samples_state,
				views_state, instances_state);

		size = data.length();
		for (uint32_t i = 0; i < size; ++i) {
			*data_begin = data[i];
			*info_begin = info[i];
			++data_begin;
			++info_begin;
		}
		return_loan(data, info);
		return size;
	}

	template<typename DataOutputIterator>
	uint32_t read(DataOutputIterator data_begin) {
		//@TODO: Static assert on iterator tag
		TSeq data;
		DDS::SampleInfoSeq info;
		uint32_t size;
		reader_->read(data, info, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
				DDS::ANY_VIEW_STATE, DDS::ALIVE_INSTANCE_STATE);

		size = data.length();
		for (uint32_t i = 0; i < size; ++i) {
			*data_begin = data[i];
			++data_begin;
		}
		return_loan(data, info);
		return size;
	}
	//----------------------------------------------------------------------
	template<typename DataOutputIterator, typename InfoOutputIterator>
	uint32_t take(DataOutputIterator data_begin, InfoOutputIterator info_begin,
			DDS::SampleStateMask samples_state, DDS::ViewStateMask views_state,
			DDS::InstanceStateMask instances_state) {
		//@TODO: Static assert on iterator tag
		TSeq data;
		DDS::SampleInfoSeq info;
		uint32_t size;
		reader_->take(data, info, DDS::LENGTH_UNLIMITED, samples_state,
				views_state, instances_state);

		size = data.length();
		for (uint32_t i = 0; i < size; ++i) {
			*data_begin = data[i];
			*info_begin = info[i];
			++data_begin;
			++info_begin;
		}
		return_loan(data, info);
		return size;
	}

	template<typename DataOutputIterator>
	uint32_t take(DataOutputIterator data_begin) {
		//@TODO: Static assert on iterator tag
		TSeq data;
		DDS::SampleInfoSeq info;
		uint32_t size;
		reader_->take(data, info, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
				DDS::ANY_VIEW_STATE, DDS::ALIVE_INSTANCE_STATE);

		size = data.length();
		for (uint32_t i = 0; i < size; ++i) {
			*data_begin = data[i];
			++data_begin;
		}
		return_loan(data, info);
		return size;
	}
	//
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	// -- Vector read/take
	void read(std::vector<T>& data, std::vector<DDS::SampleInfo>& info,
			DDS::SampleStateMask samples_state, DDS::ViewStateMask views_state,
			DDS::InstanceStateMask instances_state) {
		TSeq dat;
		DDS::SampleInfoSeq inf;
		reader_->read(dat, inf, DDS::LENGTH_UNLIMITED, samples_state,
				views_state, instances_state);

		for (int i = 0; i < dat.length(); ++i) {
			data.push_back(dat[i]);
			info.push_back(inf[i]);
		}
		return_loan(dat, inf);
	}

	void read(std::vector<T>& data, std::vector<DDS::SampleInfo>& info) {
		TSeq dat;
		DDS::SampleInfoSeq inf;
		reader_->read(dat, inf, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
				DDS::ANY_VIEW_STATE, DDS::ALIVE_INSTANCE_STATE);

		for (uint32_t i = 0; i < dat.length(); ++i) {
			data.push_back(dat[i]);
			info.push_back(inf[i]);
		}
		return_loan(dat, inf);
	}

	void read(std::vector<T>& data) {
		TSeq dat;
		DDS::SampleInfoSeq inf;
		reader_->read(dat, inf, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
				DDS::ANY_VIEW_STATE, DDS::ALIVE_INSTANCE_STATE);

		for (uint32_t i = 0; i < dat.length(); ++i) {
			data.push_back(dat[i]);
		}
		return_loan(dat, inf);
	}

	void take(std::vector<T>& data, std::vector<DDS::SampleInfo>& info,
			DDS::SampleStateMask samples_state, DDS::ViewStateMask views_state,
			DDS::InstanceStateMask instances_state) {
		TSeq dat;
		DDS::SampleInfoSeq inf;
		reader_->take(dat, inf, DDS::LENGTH_UNLIMITED, samples_state,
				views_state, instances_state);

		for (int i = 0; i < dat.length(); ++i) {
			data.push_back(dat[i]);
			info.push_back(inf[i]);
		}
		return_loan(dat, inf);
	}

	void take(std::vector<T>& data, std::vector<DDS::SampleInfo>& info) {
		this->take(data, info, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
				DDS::ANY_VIEW_STATE, DDS::ALIVE_INSTANCE_STATE);
	}

	void take(std::vector<T>& data) {
		TSeq dat;
		DDS::SampleInfoSeq inf;
		reader_->take(dat, inf, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
				DDS::ANY_VIEW_STATE, DDS::ALIVE_INSTANCE_STATE);

		for (int i = 0; i < dat.length(); ++i) {
			data.push_back(dat[i]);
		}
		return_loan(dat, inf);
	}
	//
	////////////////////////////////////////////////////////////////////////////
	boost::shared_ptr<DataInstanceReader<T> > get_instance_reader(const T& key) {
		boost::shared_ptr<DataInstanceReader<T> > ireader(
				new DataInstanceReader<T> (reader_, key));
		return ireader;
	}

	// -- Qos Getter/Setter

	dds::DataReaderQos get_qos() const {
		return drqos_;
	}

	DDS::ReturnCode_t set_qos(const dds::DataReaderQos& qos) {
		DDS::ReturnCode_t rc = reader_->set_qos(qos);
		if (rc == DDS::RETCODE_OK)
			drqos_ = qos;
		return rc;
	}

	boost::shared_ptr<DDS::Subscriber> get_subscriber() const {
		return sub_;
	}

	dds::Topic<T> get_topic() const {
		return topic_;
	}

	DDS::ReturnCode_t wait_for_historical_data(const DDS::Duration_t timeout) {
		return reader_->wait_for_historical_data(timeout);
	}

	// -- Condition API
	/**
	 * Creates an <code>ReadCondition</code> that waits for new samples to
	 * be arriving in order to notify.
	 */
	template<typename F>
	::dds::ReadCondition create_readcondition(const F& f,
			dds::SampleStateMask sample_state, dds::ViewStateMask view_state,
			dds::InstanceStateMask instance_state) {
		DDS::ReadCondition* rc = reader_->create_readcondition(sample_state,
				view_state, instance_state);

		::dds::mem::RCondDeleter<DR> deleter(reader_);
		::boost::shared_ptr<DDS::ReadCondition> rrc(rc, deleter);
		::dds::TReadCondition<dds::DataReader<T>, F> ardc(rrc, *dds_reader_, f);
		return ardc;
	}

	/*
	 ::dds::QueryCondition
	 create_querycondition(const dds::SampleStateMask&     ssm,
	 const dds::ViewStateMask&       vsm,
	 const dds::InstanceStateMask&   ism,
	 const std::string&              query_expr,
	 const std::vector<std::string>& params)  {

	 DDS::QueryCondition* qc =
	 reader_->create_querycondition(ssm,
	 vsm,
	 ism,
	 query_expr,
	 params);

	 }
	 */
public:

	void on_requested_deadline_missed(DDS::DataReader*,
			const DDS::RequestedDeadlineMissedStatus& status) {
		(boost::get<on_requested_deadline_missed::value>(signals_))(
				*dds_reader_, status);
	}

	void on_requested_incompatible_qos(DDS::DataReader*,
			const DDS::RequestedIncompatibleQosStatus& status) {
		(boost::get<on_requested_incompatible_qos::value>(signals_))(
				*dds_reader_, status);
	}

	void on_sample_rejected(DDS::DataReader*,
			const DDS::SampleRejectedStatus& status) {
		(boost::get<on_sample_rejected::value>(signals_))(*dds_reader_, status);
	}

	void on_liveliness_changed(DDS::DataReader*,
			const DDS::LivelinessChangedStatus& status) {
		(boost::get<on_liveliness_changed::value>(signals_))(*dds_reader_,
				status);
	}

	void on_data_available(DDS::DataReader*) {
		(boost::get<on_data_available::value>(signals_))(*dds_reader_);
	}

	void on_subscription_matched(DDS::DataReader*,
			const DDS::SubscriptionMatchedStatus& status) {
		(boost::get<on_subscription_matched::value>(signals_))(*dds_reader_,
				status);
	}

	void on_sample_lost(DDS::DataReader*, const DDS::SampleLostStatus& status) {
		(boost::get<on_sample_lost::value>(signals_))(*dds_reader_, status);
	}

public:

	template<typename Signal> dds::sigcon_t connect(
			typename Signal::template traits<T>::slot_type slot) {
		return boost::get<Signal::value>(signals_).connect(slot);
	}

protected:
	// -- Signals
	boost::tuple<
			typename dds::on_data_available::traits<T>::signal_type,
			typename dds::on_requested_incompatible_qos::traits<T>::signal_type,
			typename dds::on_liveliness_changed::traits<T>::signal_type,
			typename dds::on_requested_deadline_missed::traits<T>::signal_type,
			typename dds::on_sample_rejected::traits<T>::signal_type,
			typename dds::on_subscription_matched::traits<T>::signal_type,
			typename dds::on_sample_lost::traits<T>::signal_type> signals_;

protected:
	dds::Topic<T> topic_;
	dds::ContentFilteredTopic<T> cftopic_;
	boost::shared_ptr<DR> reader_;
	dds::DataReaderQos drqos_;
	dds::Subscriber sub_;
	boost::shared_ptr<DDS::DataReaderListener> listener_;
	dds::DataReader<T>* dds_reader_;
};
}
}
#endif /* AC_SIMD_DDS_READER_IMPL_HPP_ */
