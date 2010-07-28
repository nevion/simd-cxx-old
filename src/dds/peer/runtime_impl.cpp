#include <dds/config.hpp>
#include <dds/runtime.hpp>
#include <dds/qos.hpp>
#include <dds/memory.hpp>
#include <dds/publisher.hpp>
#include <dds/subscriber.hpp>
#include <boost/process.hpp>
#include <string>
#include <vector>

const std::string dds::peer::RuntimeImpl::DEFAULT_PARTITION = "";
dds::peer::RuntimeImpl* dds::peer::RuntimeImpl::this_;

namespace bp = boost::process;

int startOpenSplice() {
  std::string exec(bp::find_executable_in_path("ospl"));
  std::vector<std::string> args;
  args.push_back(exec);
  args.push_back("start");

  bp::context ctx;
  ctx.environment = bp::self::get_environment(); 
  ctx.stdout_behavior = bp::silence_stream();
  bp::child c = bp::launch(exec, args, ctx); 
  bp::status s = c.wait();
  return s.exited() ? s.exit_status() : 1;
}


dds::peer::RuntimeImpl::RuntimeImpl(const std::string& domain) 
 : dp_(domain) 
{ }

dds::peer::RuntimeImpl::RuntimeImpl() { }

dds::peer::RuntimeImpl::~RuntimeImpl() {
  delete pub_;
  delete sub_;
  SIMD_LOG(SIMD_ALLOC, "Deleted RuntimeImpl at: " << std::hex << this << std::dec);
}

void dds::peer::RuntimeImpl::start() {
  startOpenSplice();
  this_ = new RuntimeImpl();
  std::vector<std::string> partitions;
  partitions.push_back(DEFAULT_PARTITION);
  this_->init(partitions);
}

void dds::peer::RuntimeImpl::start(const std::string& partition) {
  startOpenSplice();
  this_ = new RuntimeImpl();
  std::vector<std::string> partitions;
  partitions.push_back(partition);
  this_->init(partitions);
}

void dds::peer::RuntimeImpl::start(const std::vector<std::string>& partitions) {
  startOpenSplice();
  this_ = new RuntimeImpl();
  this_->init(partitions);
}


void dds::peer::RuntimeImpl::start(const std::string& partition,
				   const std::string& domain)
{
  startOpenSplice();
  this_ = new RuntimeImpl(domain);
  std::vector<std::string> partitions;
  partitions.push_back(partition);
  this_->init(partitions);
}

void dds::peer::RuntimeImpl::start(const std::vector<std::string>& partitions,
				   const std::string& domain)
{
  startOpenSplice();
  this_ = new RuntimeImpl(domain);
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
