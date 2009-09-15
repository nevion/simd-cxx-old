#include <simd/config.hpp>
#include <simd/runtime.hpp>
#include <simd/qos.hpp>
#include <simd/memory.hpp>

const std::string simd::Runtime::DEFAULT_DOMAIN = "simd_domain";
const std::string simd::Runtime::DEFAULT_PARTITION = "simd_partition";
simd::Runtime* simd::Runtime::this_;

simd::Runtime::Runtime(const std::string& domain) :
	dp_(domain) {
}
simd::Runtime::Runtime() {
}

simd::Runtime::~Runtime() {
}

void simd::Runtime::start() {
	this_ = new Runtime();
	this_->init(DEFAULT_PARTITION);
}

void simd::Runtime::start(const std::string& partition) {
	this_ = new Runtime();
	this_->init(partition);
}

void simd::Runtime::start(const std::string& domain,
			  const std::string& partition)
{
  this_ = new Runtime(domain);
  this_->init(partition);
}

void simd::Runtime::init(const std::string& partition) {
	simd::PublisherQos pubQos;
	pubQos.set_partition(partition);

	DDS::Publisher* p = this_->dp_->create_publisher(pubQos, 0, DDS::ANY_STATUS);

	Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);

	this_->pub_.reset(p, simd::mem::PubDeleter(this_->dp_));

	simd::SubscriberQos subQos;
	subQos.set_partition(partition);

	DDS::Subscriber* s = this_->dp_->create_subscriber(subQos, 0,
			DDS::ANY_STATUS);

	Assert::postcondition((s != 0), "Unable to create Subscriber", __FILE__);
	this_->sub_.reset(s, simd::mem::SubDeleter(this_->dp_));
}
/*
void simd::Runtime::init(const std::string& domain,
		const DDS::DomainParticipantQos& qos) {
	Assert::precondition(false, "Method Not Implemented Yet", __FILE__);
}

void simd::Runtime::init(std::ifstream& is) {
	Assert::precondition(false, "Method Not Implemented Yet", __FILE__);
}
*/
simd::DomainParticipant simd::Runtime::get_participant()  throw () {
	return dp_;
}

boost::shared_ptr<DDS::Publisher> simd::Runtime::get_publisher()  throw () {
	return pub_;
}

boost::shared_ptr<DDS::Subscriber> simd::Runtime::get_subscriber()  throw () {
	return sub_;
}

simd::Runtime* simd::Runtime::instance() throw () {
	return this_;
}

void
simd::Runtime::stop() {
	delete this_;
}
