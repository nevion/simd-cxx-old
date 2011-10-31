#include <dds/runtime.hpp>
#include <dds/config.hpp>
#include <dds/peer/runtime_impl.hpp>

dds::Runtime::Runtime(const std::string& partition) {
  ::dds::peer::RuntimeImpl::start(partition);
}

#if (SIMD_OSPL_MAJ_VER >= 6)
dds::Runtime::Runtime(const std::string& partition, int domainId) {
  ::dds::peer::RuntimeImpl::start(partition, domainId);
}

dds::Runtime::Runtime(const std::vector<std::string>& partitions,
		      int domainId) {
  ::dds::peer::RuntimeImpl::start(partitions, domainId);
}

#else 
dds::Runtime::Runtime(const std::string& partition, const std::string& domainId) {
  ::dds::peer::RuntimeImpl::start(partition, domainId);
}

dds::Runtime::Runtime(const std::vector<std::string>& partitions,
		      const std::string& domainId) {
  ::dds::peer::RuntimeImpl::start(partitions, domainId);
}
#endif /* (SIMD_OSPL_MAJ_VER >= 6) */

dds::Runtime::Runtime(const std::vector<std::string>& partitions) {
  ::dds::peer::RuntimeImpl::start(partitions);
}


dds::Runtime::~Runtime() { 
  ::dds::peer::RuntimeImpl::stop();
}

::dds::DomainParticipant 
dds::Runtime::get_participant() {
  return dds::peer::RuntimeImpl::instance().get_participant();
}

::dds::Publisher 
dds::Runtime::get_publisher() {
  return dds::peer::RuntimeImpl::instance().get_publisher();
}
  
::dds::Subscriber get_subscriber() {
  return dds::peer::RuntimeImpl::instance().get_subscriber();
}
