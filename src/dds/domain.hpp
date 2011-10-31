#ifndef AC_SIMD_DDS_DOMAINPARTICIPANT_H_
#define AC_SIMD_DDS_DOMAINPARTICIPANT_H_

// -- BOOST Include
#include <boost/shared_ptr.hpp>

// -- SIMD_DDS Include
#include <dds/config.hpp>

namespace dds {

  /**
   * The <code>DomainParticipant</code> provide access to
   * a DDS domain and thus allowing to communicate within it.
   * <br>
   * <b>Note</b>Since OpenSplice DDS only supports a single
   * domain participant per application, this class is a singleton.
   * In general, it is a good approach to have a single domain per
   * application and leverage DDS Partitions in order to organize
   * information
   *
   * @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
   * @version 1.0
   */
  class SIMD_API DomainParticipant : public boost::shared_ptr<DDS::DomainParticipant> {
  public:
    DomainParticipant();
#if (SIMD_OSPL_MAJ_VER == 6)
    DomainParticipant(int domainId);
#else
    DomainParticipant(const std::string& domain);
#endif
    /*
      DomainParticipant(const std::string& domain,
      const DDS::DomainParticipantQos& qos);
    */
    virtual ~DomainParticipant();

  public:
    /**
     * Get the default publisher.
     */
    // Publisher get_publisher() const throw();
  
    /**
     * Get the default subscriber.
     */
    // Subscriber get_subscriber() const throw();
  };

}
#endif /* DOMAINPARTICIPANT_H_ */
