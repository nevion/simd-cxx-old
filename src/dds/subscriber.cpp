#include <dds/subscriber.hpp>
#include <dds/memory.hpp>
#include <dds/peer/runtime_impl.hpp>


dds::Subscriber::Subscriber() : dp_(dds::peer::RuntimeImpl::instance()->get_participant())
{
  ::dds::SubscriberQos pubQos;
  pubQos.set_partition(::dds::peer::RuntimeImpl::DEFAULT_PARTITION);

  DDS::Subscriber* p = dp_->create_subscriber(pubQos, 0, DDS::ANY_STATUS);

  Assert::postcondition((p != 0), "Unable to create Subscriber", __FILE__);

  this->reset(p, dds::mem::SubDeleter(dp_));

}

dds::Subscriber::Subscriber(const std::string& partition) 
  : dp_(dds::peer::RuntimeImpl::instance()->get_participant())
{
  ::dds::SubscriberQos pubQos;
  pubQos.set_partition(partition);

  DDS::Subscriber* p = dp_->create_subscriber(pubQos, 0, DDS::ANY_STATUS);

  Assert::postcondition((p != 0), "Unable to create Subscriber", __FILE__);

  this->reset(p, dds::mem::SubDeleter(dp_));
}

dds::Subscriber::Subscriber(const std::string& partition, dds::DomainParticipant dp) : dp_(dp)
{
  ::dds::SubscriberQos pubQos;
  pubQos.set_partition(partition);

  DDS::Subscriber* p = dp->create_subscriber(pubQos, 0, DDS::ANY_STATUS);

  Assert::postcondition((p != 0), "Unable to create Subscriber", __FILE__);

  this->reset(p, dds::mem::SubDeleter(dp_));
}
/*
dds::Subscriber::Subscriber(const dds::SubscriberQos& pubQos, dds::DomainParticipant dp) : dp_(dp)
{

  DDS::Subscriber* p = dp->create_subscriber(pubQos, 0, DDS::ANY_STATUS);
  Assert::postcondition((p != 0), "Unable to create Subscriber", __FILE__);
  this->reset(p, dds::mem::SubDeleter(dp_));
}
*/

dds::Subscriber::~Subscriber()
{
  // -- Nothing to do. The shared_ptr deleter will
  //    take care of everything

}

