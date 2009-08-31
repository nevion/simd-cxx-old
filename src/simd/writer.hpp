#ifndef AC_SIMD_WRITER_HPP
#define AC_SIMD_WRITER_HPP

#include <simd/runtime.hpp>
#include <simd/memory.hpp>
#include <simd/traits.hpp>
#include <simd/topic.hpp>

namespace simd {

template <typename T>
class DataInstanceWriter;

/**
* The <code>DataWriter</code> class provides a generic API for
* writing instances samples for a specific Topic.
*
* @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
*/
template <typename T>
class DataWriterImpl {
public:
	typedef typename topic_data_writer<T>::type DW;

public:

	DataWriterImpl(Topic<T> topic)
	: topic_(topic),
	dwqos_(topic_->get_qos())
	{
		pub_ =
				Runtime::instance()->get_publisher();

		DDS::DataWriter* w = pub_->create_datawriter(topic_->get_dds_topic(),
				dwqos_,
				0,
				DDS::ANY_STATUS);

		boost::shared_ptr<DW> tmp(DW::_narrow(w), mem::DWDeleter(pub_));
		writer_ = tmp;
	}

	DataWriterImpl(Topic<T> topic, const DataWriterQos& qos)
	: topic_(topic), dwqos_(qos)
	{
		pub_ = Runtime::instance()->get_publisher();
		DDS::DataWriter* w =
				pub_->create_datawriter(topic_->get_dds_topic(),
						dwqos_,
						0,
						DDS::ANY_STATUS);

		boost::shared_ptr<DW> tmp(DW::_narrow(w),
				mem::DWDeleter(pub_));
		writer_ = tmp;
	}

	DataWriterImpl(Topic<T> topic, const DataWriterQos& qos, boost::shared_ptr<DDS::Publisher> pub)
	:	topic_(topic), pub_(pub), dwqos_(qos)
	{
		DDS::DataWriter* w =
				pub_->create_datawriter(topic_->get_dds_topic(),
						dwqos_,
						0,
						DDS::ANY_STATUS);

		boost::shared_ptr<DW> tmp(DW::_narrow(w),
				mem::DWDeleter(pub_));
		writer_ = tmp;
	}

	virtual ~DataWriterImpl() { }

public:

	DDS::ReturnCode_t write(const T& sample) {
		return writer_->write(sample, DDS::HANDLE_NIL);
	}

	DDS::ReturnCode_t write(const T& sample, const DDS::Time_t& timestamp) {
		return writer_->write(sample, timestamp, DDS::HANDLE_NIL);
	}


	::boost::shared_ptr<DataInstanceWriter<T> >
	register_instance(const T& key) {
		boost::shared_ptr<DataInstanceWriter<T> >
		iwriter(new DataInstanceWriter<T > (writer_, key));
		return iwriter;
	}

	// -- QoS Getter/Setter

	DataWriterQos
	get_qos() {
		return dwqos_;
	}

	DDS::ReturnCode_t
	set_qos(const DataWriterQos &qos)  {
		DDS::ReturnCode_t rc = writer_->set_qos(qos);
		if (rc == DDS::RETCODE_OK)
			dwqos_ = qos;
		return rc;
	}

	boost::shared_ptr<Topic<T> >
	get_topic() {
		return topic_;
	}

	boost::shared_ptr<DDS::Publisher>
	get_publisher() {
		return pub_;
	}

	DDS::ReturnCode_t
	wait_for_acks(const DDS::Duration_t& timeout) {
		return writer_->wait_for_acknowlegments(timeout);
	}

protected:
	Topic<T>  topic_;
	::boost::shared_ptr<DDS::Publisher> pub_;
	::boost::shared_ptr<DW> writer_;
	DataWriterQos dwqos_;
};

template <typename T>
class DataWriter : public ::boost::shared_ptr< DataWriterImpl<T> > {
public:
	DataWriter(Topic<T> topic) {
		this->reset(new DataWriterImpl<T>(topic));
	}

	DataWriter(Topic<T> topic, const DataWriterQos& qos) {
		this->reset(new DataWriterImpl<T>(topic, qos));
	}

	DataWriter(Topic<T> topic, const DataWriterQos& qos, boost::shared_ptr<DDS::Publisher> pub) {
		this->reset(new DataWriterImpl<T>(topic, qos, pub));
	}

	virtual ~DataWriter() { }

};
}
#endif /* AC_SIMD_WRITER_HPP */
