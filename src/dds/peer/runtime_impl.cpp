#include <dds/config.hpp>
#include <dds/runtime.hpp>
#include <dds/qos.hpp>
#include <dds/memory.hpp>
#include <dds/publisher.hpp>
#include <dds/subscriber.hpp>
#include <string>
#include <vector>

const std::string dds::peer::RuntimeImpl::DEFAULT_PARTITION = "";
dds::peer::RuntimeImpl* dds::peer::RuntimeImpl::this_;

#if (SIMD_OSPL_MAJ_VER >= 6)
dds::peer::RuntimeImpl::RuntimeImpl(int domainId) 
 : dp_(domainId) 
{ }

void dds::peer::RuntimeImpl::start(const std::string& partition,
				   int domainId)
{
  this_ = new RuntimeImpl(domainId);
  std::vector<std::string> partitions;
  partitions.push_back(partition);
  this_->init(partitions);
}

void dds::peer::RuntimeImpl::start(const std::vector<std::string>& partitions,
				   int domainId)
{
  this_ = new RuntimeImpl(domainId);
  this_->init(partitions);
}


#else 
dds::peer::RuntimeImpl::RuntimeImpl(const std::string& domain) 
 : dp_(domain) 
{ }

void dds::peer::RuntimeImpl::start(const std::string& partition,
				   const std::string& domain)
{
  this_ = new RuntimeImpl(domain);
  std::vector<std::string> partitions;
  partitions.push_back(partition);
  this_->init(partitions);
}

void dds::peer::RuntimeImpl::start(const std::vector<std::string>& partitions,
				   const std::string& domain)
{
  this_ = new RuntimeImpl(domain);
  this_->init(partitions);
}

#endif /* (SIMD_OSPL_MAJ_VER >= 6) */


dds::peer::RuntimeImpl::RuntimeImpl() { }

dds::peer::RuntimeImpl::~RuntimeImpl() {
  delete pub_;
  delete sub_;
  SIMD_LOG(SIMD_ALLOC, "Deleted RuntimeImpl at: " << std::hex << this << std::dec);
}

void dds::peer::RuntimeImpl::start(const std::string& partition) {
  this_ = new RuntimeImpl();
  std::vector<std::string> partitions;
  partitions.push_back(partition);
  this_->init(partitions);
}

void dds::peer::RuntimeImpl::start(const std::vector<std::string>& partitions) {
  this_ = new RuntimeImpl();
  this_->init(partitions);
}



void dds::peer::RuntimeImpl::init(const std::vector<std::string>& partitions) {
  pub_ = new dds::Publisher(partitions);
  sub_ = new dds::Subscriber(partitions);
}

/*
  void dds::peer::RuntimeImpl::init(const std::string& domain,
  const DDS::DomainParticipantQos& qos) {
  Assert::precondition(false, "Method Not Implemented Yet", __FILE__);
  }

  void dds::peer::RuntimeImpl::init(std::ifstream& is) {
  Assert::precondition(false, "Method Not Implemented Yet", __FILE__);
  }
*/
dds::DomainParticipant dds::peer::RuntimeImpl::get_participant() {
  return dp_;
}

dds::Publisher 
dds::peer::RuntimeImpl::get_publisher() {
  return *pub_;
}

dds::Subscriber 
dds::peer::RuntimeImpl::get_subscriber() {
  return *sub_;
}

dds::peer::RuntimeImpl& 
dds::peer::RuntimeImpl::instance() {
  return *this_;
}

void
dds::peer::RuntimeImpl::stop() {
  delete this_;
}
