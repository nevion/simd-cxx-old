#include <dds/runtime.hpp>
#include <dds/config.hpp>
#include <dds/peer/runtime_impl.hpp>

dds::Runtime::Runtime(const std::string& partition) {
  ::dds::peer::RuntimeImpl::start(partition);
}

dds::Runtime::Runtime(const std::vector<std::string>& partitions) {
  ::dds::peer::RuntimeImpl::start(partitions);
}

dds::Runtime::Runtime(const std::string& partition, const std::string& domain) {
  ::dds::peer::RuntimeImpl::start(partition, domain);
}

dds::Runtime::Runtime(const std::vector<std::string>& partitions,
		      const std::string& domain) {
  ::dds::peer::RuntimeImpl::start(partitions, domain);
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
