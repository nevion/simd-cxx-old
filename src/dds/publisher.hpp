#ifndef AC_SIMD_DDS_PUBLISHER_H_
#define AC_SIMD_DDS_PUBLISHER_H_

// -- BOOST Include
#include <boost/shared_ptr.hpp>

#include <string>

// -- SIMD_DDS Include
#include <dds/config.hpp>
#include <dds/qos.hpp>
#include <dds/domain.hpp>

namespace dds {

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
	Publisher(const std::string& partition, ::dds::DomainParticipant dp);


	Publisher(const ::dds::PublisherQos& qos, ::dds::DomainParticipant dp);

	virtual ~Publisher();

private:
	::dds::DomainParticipant dp_;
};

}

#endif /* AC_SIMD_DDS_PUBLISHER_H_ */
