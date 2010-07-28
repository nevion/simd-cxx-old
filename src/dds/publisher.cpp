#include <dds/publisher.hpp>
#include <dds/memory.hpp>
#include <dds/peer/runtime_impl.hpp>


dds::Publisher::Publisher() 
  : dp_(dds::peer::RuntimeImpl::instance().get_participant())
{
  ::dds::PublisherQos pubQos;
  pubQos.set_partition(::dds::peer::RuntimeImpl::DEFAULT_PARTITION);
  
  DDS::Publisher* p = 
    dp_->create_publisher(pubQos, 0, DDS::ANY_STATUS);

  Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);

  this->reset(p, dds::mem::PubDeleter(dp_));
}

dds::Publisher::Publisher(const std::string& partition) 
  : dp_(dds::peer::RuntimeImpl::instance().get_participant())
{
  ::dds::PublisherQos pubQos;
  pubQos.set_partition(partition);

  DDS::Publisher* p = 
    dp_->create_publisher(pubQos, 0, DDS::ANY_STATUS);

  Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);

  this->reset(p, dds::mem::PubDeleter(dp_));
}

dds::Publisher::Publisher(const std::vector<std::string>& partitions) 
  : dp_(dds::peer::RuntimeImpl::instance().get_participant())
{
  ::dds::PublisherQos pubQos;
  pubQos.set_partition(partitions);

  DDS::Publisher* p = 
    dp_->create_publisher(pubQos, 0, DDS::ANY_STATUS);

  Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);

  this->reset(p, dds::mem::PubDeleter(dp_));
}

dds::Publisher::Publisher(const std::string& partition, dds::DomainParticipant dp) 
  : dp_(dp)
{
  ::dds::PublisherQos pubQos;
  pubQos.set_partition(partition);

  DDS::Publisher* p = dp->create_publisher(pubQos, 0, DDS::ANY_STATUS);

  Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);

  this->reset(p, dds::mem::PubDeleter(dp_));
}

dds::Publisher::Publisher(const std::vector<std::string>& partitions, 
			  dds::DomainParticipant dp) 
  : dp_(dp)
{
  ::dds::PublisherQos pubQos;
  pubQos.set_partition(partitions);

  DDS::Publisher* p = dp->create_publisher(pubQos, 0, DDS::ANY_STATUS);

  Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);

  this->reset(p, dds::mem::PubDeleter(dp_));
}
/*
dds::Publisher::Publisher(const dds::PublisherQos& pubQos, dds::DomainParticipant dp) : dp_(dp)
{

  DDS::Publisher* p = dp->create_publisher(pubQos, 0, DDS::ANY_STATUS);
  Assert::postcondition((p != 0), "Unable to create Publisher", __FILE__);
  this->reset(p, dds::mem::PubDeleter(dp_));
}
*/
dds::Publisher::~Publisher()
{
  // -- Nothing to do. The shared_ptr deleter will
  //    take care of everything

}

