#ifndef AC_SIMD_DDS_SUBSCRIBER_H_
#define AC_SIMD_DDS_SUBSCRIBER_H_

// -- BOOST Include
#include <boost/shared_ptr.hpp>

#include <string>

// -- SIMD_DDS Include
#include <dds/config.hpp>
#include <dds/qos.hpp>
#include <dds/domain.hpp>

namespace dds {

  class SIMD_API Subscriber: public boost::shared_ptr<DDS::Subscriber> {
  public:
    /**
     * Creates a <code>Subscriber</code> on the default
     * <code>DomainParticipant</code> and connected to the default
     * partition
     */
    Subscriber();

    /**
     * Creates a <code>Subscriber</code> on the default
     * <code>DomainParticipant</code> and connected to the partition
     * specified by the argument.
     *
     * @param partition the partition to which the
     * <code>Subscriber</code> will be connected.
     */
    Subscriber(const std::string& partition);

    /**
     * Creates a <code>Subscriber</code> on the default
     * <code>DomainParticipant</code> and connected to the partitions
     * specified by the argument.
     *
     * @param partitions the partitions to which the
     * <code>Subscriber</code> will be connected.
     */
    Subscriber(const std::vector<std::string>& partitions);


    /**
     * Creates a <code>Subscriber</code> on the given <code>Participant</code>
     * and attached to the specified partition.
     *
     * @param partition the partition to which the
     * 		 <code>Subscriber</code> will be attached
     *
     * @param dp the <code>DomainParticipant</code> to which the
     * 		 publisher will be attached
     */
    Subscriber(const std::string& partition, DomainParticipant dp);

    /**
     * Creates a <code>Subscriber</code> on the given <code>Participant</code>
     * and attached to the specified partitions.
     *
     * @param partitions the partitions to which the
     * 		 <code>Subscriber</code> will be attached
     *
     * @param dp the <code>DomainParticipant</code> to which the
     * 		 publisher will be attached
     */
    Subscriber(const std::vector<std::string>& partition, DomainParticipant dp);


    //  Subscriber(const SubscriberQos& qos, DomainParticipant dp);

    virtual ~Subscriber();

  private:
    ::dds::DomainParticipant dp_;
  };

}

#endif /* AC_SIMD_DDS_SUBSCRIBER_H_ */
