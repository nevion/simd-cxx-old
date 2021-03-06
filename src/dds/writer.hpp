#ifndef AC_SIMD_DDS_WRITER_HPP
#define AC_SIMD_DDS_WRITER_HPP

namespace dds {
template<typename T>
class DataInstanceWriter;

template<typename T>
class DataWriter;
}

#include <dds/peer/writer_impl.hpp>

/**
 * The <code>DataWriter</code> class provides a generic API for
 * writing instances samples for a specific Topic.
 *
 * @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
 */

template<typename T>
class dds::DataWriter {
public:
	typedef typename dds::peer::DataWriterImpl<T>::DW DW;

public:
	DataWriter() {
	}

	DataWriter(const dds::Topic<T>& topic) {
		pimpl_.reset(new dds::peer::DataWriterImpl<T>(topic));
	}

	DataWriter(const dds::Topic<T>& topic, const DataWriterQos& qos) {
		pimpl_.reset(new dds::peer::DataWriterImpl<T>(topic, qos));
	}

	DataWriter(const dds::Topic<T>& topic, const DataWriterQos& qos,
			dds::Publisher pub) {
		pimpl_.reset(new dds::peer::DataWriterImpl<T>(topic, qos, pub));
	}

	~DataWriter() {
	}

public:
	inline dds::ReturnCode_t write(const T& sample) {
		return pimpl_->write(sample);
	}

	inline dds::ReturnCode_t write(const T& sample,
			const dds::Time_t& timestamp) {
		return pimpl_->write(sample, timestamp);
	}


	void write(const std::vector<T>& samples) {
		for (uint32_t i = 0; i < samples.size(); ++i)
			this->write(samples[i]);
	}

	DataInstanceWriter<T> register_instance(const T& key) {
		return pimpl_->register_instance(key);
	}

	// -- QoS Getter/Setter

	DataWriterQos get_qos() {
		return pimpl_->get_qos();
	}

	dds::ReturnCode_t set_qos(const DataWriterQos &qos) {
		return pimpl_->set_qos(qos);
	}

	boost::shared_ptr<dds::Topic<T> > get_topic() {
		return pimpl_->get_topic();
	}

	dds::Publisher get_publisher() {
		return pimpl_->get_publisher();
	}

	dds::ReturnCode_t wait_for_acks(const dds::Duration_t& timeout) {
		return pimpl_->wait_for_acks(timeout);
	}
public:

	DataWriter<T>& operator <<(const T& sample) {
		this->write(sample);
		return *this;
	}

	DataWriter<T>& operator <<(const std::vector<T>& samples) {
		this->write(samples);
		return *this;
	}

	DataWriter<T>& operator <<(const DataWriterQos& qos) {
		this->set_qos(qos);
		return *this;
	}

protected:
	::boost::shared_ptr<dds::peer::DataWriterImpl<T> > pimpl_;
};

#endif /* AC_SIMD_DDS_WRITER_HPP */
