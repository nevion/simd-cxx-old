#include <simd/publisher.hpp>
#include <simd/memory.hpp>
#include <simd/runtime.hpp>


simd::Publisher::Publisher() : dp_(Runtime::instance()->get_participant())
{
	::simd::PublisherQos pubQos;
	pubQos.set_partition(simd::Runtime::DEFAULT_PARTITION);

	DDS::Publisher* p = dp_->create_publisher(pubQos, 0, DDS::ANY_STATUS);

	Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);

	this->reset(p, simd::mem::PubDeleter(dp_));

}

simd::Publisher::Publisher(const std::string& partition) : dp_(Runtime::instance()->get_participant())
{
	::simd::PublisherQos pubQos;
	pubQos.set_partition(partition);

	DDS::Publisher* p = dp_->create_publisher(pubQos, 0, DDS::ANY_STATUS);

	Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);

	this->reset(p, simd::mem::PubDeleter(dp_));
}

simd::Publisher::Publisher(const std::string& partition, simd::DomainParticipant dp) : dp_(dp)
{
	::simd::PublisherQos pubQos;
	pubQos.set_partition(partition);

	DDS::Publisher* p = dp->create_publisher(pubQos, 0, DDS::ANY_STATUS);

	Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);

	this->reset(p, simd::mem::PubDeleter(dp_));
}

simd::Publisher::Publisher(const simd::PublisherQos& pubQos, simd::DomainParticipant dp) : dp_(dp)
{

	DDS::Publisher* p = dp->create_publisher(pubQos, 0, DDS::ANY_STATUS);
	Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);
	this->reset(p, simd::mem::PubDeleter(dp_));
}

simd::Publisher::~Publisher()
{
// -- Nothing to do. The shared_ptr deleter will
//    take care of everything

}

