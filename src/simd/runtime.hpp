#ifndef AC_SIMD_RUNTIME_HPP_
#define AC_SIMD_RUNTIME_HPP_

// -- STD C++ Include
#include <string>

// -- Boost Includes
#include <boost/shared_ptr.hpp>

#include <simd/config.hpp>
#include <simd/domain.hpp>

namespace simd {

class Runtime {

public:
	static const std::string DEFAULT_DOMAIN;
	static const std::string DEFAULT_PARTITION;

public:
	static void start();
	static void start(const std::string& partition);
	static void start(const std::string& partition, const std::string& domain);
	/*
	static void start(std::ifstream& is);

	 static void start(const std::string& domain,
	 const DDS::DomainParticipantQos& qos);
	 */
	static void stop();

protected:
	Runtime();
	Runtime(const std::string& domain);
	void init(const std::string& partition);
public:
	~Runtime();

public:

	static Runtime* instance() throw ();

	// TODO: Implement this method1
	//  void set_listener(shared_ptr<DDS::DomainParticipantListener> listener);

	//@TODO: Provide SIMD facades to the DomainParticipant, Publisher, Subscriber, etc.
	/**
	 * Get the default participant.
	 */
	::simd::DomainParticipant get_participant() throw ();

	/**
	 * Get the default publisher.
	 */
	boost::shared_ptr<DDS::Publisher> get_publisher()  throw ();

	/**
	 * Get the default subscriber.
	 */
	boost::shared_ptr<DDS::Subscriber> get_subscriber()  throw ();

private:
	static Runtime* this_;

	::simd::DomainParticipant dp_;

	boost::shared_ptr<DDS::Publisher> pub_;
	boost::shared_ptr<DDS::Subscriber> sub_;

};



}
#endif /* AC_SIMD_RUNTIME_HPP_ */
