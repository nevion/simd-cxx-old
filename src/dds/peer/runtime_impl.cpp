#include <dds/config.hpp>
#include <dds/runtime.hpp>
#include <dds/qos.hpp>
#include <dds/memory.hpp>
#include <dds/publisher.hpp>
#include <dds/subscriber.hpp>
const std::string dds::peer::RuntimeImpl::DEFAULT_DOMAIN = "dds_domain";
const std::string dds::peer::RuntimeImpl::DEFAULT_PARTITION = "dds_partition";
dds::peer::RuntimeImpl* dds::peer::RuntimeImpl::this_;

dds::peer::RuntimeImpl::RuntimeImpl(const std::string& domain) :
  dp_(domain) {
}
dds::peer::RuntimeImpl::RuntimeImpl() {
}

dds::peer::RuntimeImpl::~RuntimeImpl() {
  delete pub_;
  delete sub_;
  SIMD_LOG(SIMD_ALLOC, "Deleted RuntimeImpl at: " << std::hex << this << std::dec);
}

void dds::peer::RuntimeImpl::start() {
  this_ = new RuntimeImpl();
  this_->init(DEFAULT_PARTITION);
}

void dds::peer::RuntimeImpl::start(const std::string& partition) {
  this_ = new RuntimeImpl();
  this_->init(partition);
}

void dds::peer::RuntimeImpl::start(const std::string& domain,
			 const std::string& partition)
{
  this_ = new RuntimeImpl(domain);
  this_->init(partition);
}

void dds::peer::RuntimeImpl::init(const std::string& partition) {
  dds::PublisherQos pubQos;
  pubQos.set_partition(partition);
  
  pub_ = new dds::Publisher(partition);
  sub_ = new dds::Subscriber(partition);
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
dds::DomainParticipant dds::peer::RuntimeImpl::get_participant()  throw () {
  return dp_;
}

dds::Publisher 
dds::peer::RuntimeImpl::get_publisher()  throw () {
  return *pub_;
}

dds::Subscriber 
dds::peer::RuntimeImpl::get_subscriber()  throw () {
  return *sub_;
}

dds::peer::RuntimeImpl* 
dds::peer::RuntimeImpl::instance() throw () {
  return this_;
}

void
dds::peer::RuntimeImpl::stop() {
  delete this_;
}
