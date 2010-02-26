#ifndef AC_DDS_RUNTIME_HPP_
#define AC_DDS_RUNTIME_HPP_

#include <string>
#include <dds/domain.hpp>

namespace dds {
  class Runtime;
  namespace peer {
    class RuntimeImpl;
  }
}

class SIMD_API dds::Runtime {
public:
  Runtime();
  Runtime(const std::string& partition);
  Runtime(const std::string& partition, const std::string& domain);

  ~Runtime();

public:
  ::dds::DomainParticipant get_participant() throw ();
  
  boost::shared_ptr<DDS::Publisher> get_publisher()  throw ();
  
  boost::shared_ptr<DDS::Subscriber> get_subscriber()  throw ();
};

#endif /* AC_DDS_DDS_HPP_ */
