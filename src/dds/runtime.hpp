#ifndef AC_DDS_RUNTIME_HPP_
#define AC_DDS_RUNTIME_HPP_

#include <string>
#include <dds/config.hpp>
#include <dds/domain.hpp>
#include <dds/publisher.hpp>
#include <dds/subscriber.hpp>

namespace dds {
  class Runtime;
  namespace peer {
    class RuntimeImpl;
  }
}

class SIMD_API dds::Runtime {
public:
  Runtime(const std::string& partition = "");

  Runtime(const std::vector<std::string>& partitions);

#if (SIMD_OSPL_MAJ_VER >= 6)
  Runtime(const std::string& partition, int domainID);

  Runtime(const std::vector<std::string>& partitions, 
	  int domainID);

#else
  Runtime(const std::string& partition, const std::string& domain);

  Runtime(const std::vector<std::string>& partitions, 
	  const std::string& domain);
#endif /* (SIMD_OSPL_MAJ_VER >= 6) */

  ~Runtime();

public:
  ::dds::DomainParticipant get_participant();
  
  ::dds::Publisher get_publisher();
  
  ::dds::Subscriber get_subscriber();
};

#endif /* AC_DDS_DDS_HPP_ */
