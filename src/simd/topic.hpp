#ifndef AC_SIMD_TOPIC_HPP
#define AC_SIMD_TOPIC_HPP

#include <string>

// -- Boost Include
#include <boost/shared_ptr.hpp>

#include <simd/traits.hpp>
#include <simd/runtime.hpp>
#include <simd/qos.hpp>

namespace simd {

class TopicDescription {
public:
	virtual ~TopicDescription();

public:
	virtual std::string get_name() = 0;
	virtual std::string get_type_name() = 0;
	virtual simd::DomainParticipant get_participant() = 0;
};

template<typename T>
class TopicImpl: public TopicDescription {
public:

	TopicImpl(const std::string& name, const std::string type_name) :
		name_(name), dp_(::simd::Runtime::instance()->get_participant()) {
		TopicQos qos;
		this->init(name, type_name, qos);
	}

	TopicImpl(const std::string& name) :
		name_(name), dp_(::simd::Runtime::instance()->get_participant()) {
		TopicQos qos;
		std::string type_name(ts_.get_type_name());
		this->init(name, type_name, qos);
	}

	TopicImpl(const std::string& name, const TopicQos& qos) :
		name_(name), qos_(qos), dp_(
				::simd::Runtime::instance()->get_participant()) {
		std::string type_name(ts_.get_type_name());
		this->init(name, type_name, qos);
	}

	TopicImpl(const std::string& name, const std::string& type_name,
			const TopicQos& qos) :
		name_(name), qos_(qos), dp_(
				::simd::Runtime::instance()->get_participant()) {
		this->init(name, type_name, qos);
	}

	virtual ~TopicImpl() {
		dp_->delete_topic(t_);
	}

private:

	void init(const std::string& name, const std::string type_name,
			const TopicQos& qos) {

		ts_.register_type(dp_.get(), type_name.c_str());

		t_ = dp_->create_topic(name.c_str(), type_name.c_str(), qos, 0,
				DDS::ANY_STATUS);
	}

public:

	TopicQos get_qos() const {
		return qos_;
	}

	DDS::ReturnCode_t set_qos(const TopicQos& qos) {
		DDS::ReturnCode_t rc = t_->set_qos(qos);
		if (rc == DDS::RETCODE_OK)
			qos_ = qos;
		return rc;
	}

	// TODO: Add other methods
	// void set_listener();

	//private:
	//  friend template <typename W, typename D> class ::Datawriter;
public:

	DDS::Topic*
	get_dds_topic() const {
		return t_;
	}

public:
	// -- Methods inherited from TopicDescription
	virtual std::string get_name() {
		return name_;
	}

	virtual std::string get_type_name() {
		return std::string(ts_.get_type_name());
	}

	virtual simd::DomainParticipant get_participant() {
		return dp_;
	}
private:
	std::string name_;
	TopicQos qos_;
	typename topic_type_support<T>::type ts_;
	DDS::Topic* t_;
	simd::DomainParticipant dp_;

};

template<typename T>
class Topic: public ::boost::shared_ptr<TopicImpl<T> > {
public:
	Topic(const std::string& name, const std::string type_name) {
		this->reset(new TopicImpl<T> (name, type_name));
	}

	Topic(const std::string& name) {
		this->reset(new TopicImpl<T> (name));
	}

	Topic(const std::string& name, const TopicQos& qos) {
		this->reset(new TopicImpl<T> (name, qos));
	}

	Topic(const std::string& name, const std::string& type_name,
			const TopicQos& qos) {
		this->reset(new TopicImpl<T> (name, type_name, qos));
	}
};
}

#endif /* AC_SIMD_TOPIC_HPP */
