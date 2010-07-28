#ifndef AC_SIMD_DDS_PUBLISHER_H_
#define AC_SIMD_DDS_PUBLISHER_H_

// -- BOOST Include
#include <boost/shared_ptr.hpp>

#include <string>

// -- SIMD_DDS Include
#include <dds/config.hpp>
#include <dds/qos.hpp>


namespace dds {

  class SIMD_API Publisher: public boost::shared_ptr<DDS::Publisher> {
  public:
    /**
     * Creates a <code>Publisher</code> on the default
     * <code>DomainParticipant</code> and connected to the default
     * partition
     */
    Publisher();
    
    /**
     * Creates a <code>Publisher</code> on the default
     * <code>DomainParticipant</code> and connected to the partition
     * specified by the argument.
     *
     * @param partition the partition to which the
     * <code>Publisher</code> will be connected.
     */
    Publisher(const std::string& partition);

    /**
     * Creates a <code>Publisher</code> on the default
     * <code>DomainParticipant</code> and connected to the partitions
     * specified by the argument.
     *
     * @param partitions the partitions to which the
     * <code>Publisher</code> will be connected.
     */
    Publisher(const std::vector<std::string>& partitions);

    /**
     * Creates a <code>Publisher</code> on the given <code>Participant</code>
     * and attached to the specified partition.
     * @param partition the partition to which the <code>Publisher</code> will
     * 		 be attached
     * @param dp the <code>DomainParticipant</code> to which the publisher
     * 		 will be attached
     */
    Publisher(const std::string& partition, DomainParticipant dp);


    /**
     * Creates a <code>Publisher</code> on the given <code>Participant</code>
     * and attached to the specified partitions.
     * @param partitions the partitions to which the <code>Publisher</code> will
     * 		 be attached
     * @param dp the <code>DomainParticipant</code> to which the publisher
     * 		 will be attached
     */
    Publisher(const std::vector<std::string>& partitions, DomainParticipant dp);

    // Publisher(const PublisherQos& qos, DomainParticipant dp);

    virtual ~Publisher();

  private:
    DomainParticipant dp_;
  };

}

#endif /* AC_SIMD_DDS_PUBLISHER_H_ */
