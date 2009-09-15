#ifndef AC_SIMD_PUBLISHER_H_
#define AC_SIMD_PUBLISHER_H_

// -- BOOST Include
#include <boost/shared_ptr.hpp>

#include <string>

// -- SIMD Include
#include <simd/config.hpp>
#include <simd/qos.hpp>
#include <simd/domain.hpp>

namespace simd {

class Publisher: public boost::shared_ptr<DDS::Publisher> {
public:
	/**
	 * Creates a <code>Publisher</code> on the default <code>DomainParticipant</code>
	 * and connected to the default partition
	 */
	Publisher();

	/**
	 * Creates a <code>Publisher</code> on the default <code>DomainParticipant</code>
	 * and connected to the partition specified by the argument.
	 *
	 * @param partition the partition to which the <code>Publisher</code> will be connected.
	 */
	Publisher(const std::string& partition);

	/**
	 * Creates a <code>Publisher</code> on the given <code>Participant</code>
	 * and attached to the specified partition.
	 * @param partition the partition to which the <code>Publisher</code> will
	 * 		 be attached
	 * @param dp the <code>DomainParticipant</code> to which the publisher
	 * 		 will be attached
	 */
	Publisher(const std::string& partition, ::simd::DomainParticipant dp);


	Publisher(const ::simd::PublisherQos& qos, ::simd::DomainParticipant dp);

	virtual ~Publisher();

private:
	::simd::DomainParticipant dp_;
};

}

#endif /* AC_SIMD_PUBLISHER_H_ */
