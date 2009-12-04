#include <dds/config.hpp>
#include <dds/runtime.hpp>
#include <dds/qos.hpp>
#include <dds/memory.hpp>

const std::string dds::Runtime::DEFAULT_DOMAIN = "dds_domain";
const std::string dds::Runtime::DEFAULT_PARTITION = "dds_partition";
dds::Runtime* dds::Runtime::this_;

dds::Runtime::Runtime(const std::string& domain) :
	dp_(domain) {
}
dds::Runtime::Runtime() {
}

dds::Runtime::~Runtime() {
}

void dds::Runtime::start() {
	this_ = new Runtime();
	this_->init(DEFAULT_PARTITION);
}

void dds::Runtime::start(const std::string& partition) {
	this_ = new Runtime();
	this_->init(partition);
}

void dds::Runtime::start(const std::string& domain,
			  const std::string& partition)
{
  this_ = new Runtime(domain);
  this_->init(partition);
}

void dds::Runtime::init(const std::string& partition) {
	dds::PublisherQos pubQos;
	pubQos.set_partition(partition);

	DDS::Publisher* p = this_->dp_->create_publisher(pubQos, 0, DDS::ANY_STATUS);

	Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);

	this_->pub_.reset(p, dds::mem::PubDeleter(this_->dp_));

	dds::SubscriberQos subQos;
	subQos.set_partition(partition);

	DDS::Subscriber* s = this_->dp_->create_subscriber(subQos, 0,
			DDS::ANY_STATUS);

	Assert::postcondition((s != 0), "Unable to create Subscriber", __FILE__);
	this_->sub_.reset(s, dds::mem::SubDeleter(this_->dp_));
}
/*
void dds::Runtime::init(const std::string& domain,
		const DDS::DomainParticipantQos& qos) {
	Assert::precondition(false, "Method Not Implemented Yet", __FILE__);
}

void dds::Runtime::init(std::ifstream& is) {
	Assert::precondition(false, "Method Not Implemented Yet", __FILE__);
}
*/
dds::DomainParticipant dds::Runtime::get_participant()  throw () {
	return dp_;
}

boost::shared_ptr<DDS::Publisher> dds::Runtime::get_publisher()  throw () {
	return pub_;
}

boost::shared_ptr<DDS::Subscriber> dds::Runtime::get_subscriber()  throw () {
	return sub_;
}

dds::Runtime* dds::Runtime::instance() throw () {
	return this_;
}

void
dds::Runtime::stop() {
	delete this_;
}
