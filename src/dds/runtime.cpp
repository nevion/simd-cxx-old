#include <dds/runtime.hpp>
#include <dds/config.hpp>
#include <dds/peer/runtime_impl.hpp>

dds::Runtime::Runtime() {
  ::dds::peer::RuntimeImpl::start();
}

dds::Runtime::Runtime(const std::string& partition) {
  ::dds::peer::RuntimeImpl::start(partition);
}

dds::Runtime::Runtime(const std::string& partition, const std::string& domain) {
  ::dds::peer::RuntimeImpl::start(partition, domain);
}

dds::Runtime::~Runtime() { 
  ::dds::peer::RuntimeImpl::stop();
}
