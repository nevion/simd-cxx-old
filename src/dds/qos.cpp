#include <dds/qos.hpp>
#include <dds/assertion.hpp>

#include "config.hpp"

dds::TopicQosInitializer::TopicQosInitializer(dds::DomainParticipant dp)
  : dp_(dp) { }

dds::TopicQosInitializer::~TopicQosInitializer() { }

void
dds::TopicQosInitializer::operator()(DDS::TopicQos& qos)
{
  dp_->get_default_topic_qos(qos);
}

//////////////////////////////////////////////////////////////////////////////

dds::TopicQos::TopicQos() : 
  BaseTopicQos<DDS::TopicQos, TopicQosInitializer>::BaseTopicQos()  { }

dds::TopicQos::~TopicQos() { }

void 
dds::TopicQos::set_priority(long prio) {
  this->transport_priority.value = prio;
}
 
void 
dds::TopicQos::set_durability_service(DDS::Duration_t service_cleanup_delay,
				       DDS::HistoryQosPolicyKind history_kind,
				       DDS::Long history_depth,
				       DDS::Long max_samples,
				       DDS::Long max_instances,
				       DDS::Long max_samples_per_instance)
{
  dds::Assert::precondition(false, "<TopicQoS::set_durability_service>: not implemented yet", __FILE__);
}

//////////////////////////////////////////////////////////////////////////////

dds::DataWriterQos::DataWriterQos() :  
  BaseTopicQos<DDS::DataWriterQos, NullInitializer>::BaseTopicQos()  
{ 
  *((DDS::DataWriterQos*)this) =
    *(DDS::DomainParticipantFactory::datawriter_qos_default());
}

dds::DataWriterQos::DataWriterQos(const TopicQos& tqos) :  
  BaseTopicQos<DDS::DataWriterQos, NullInitializer>::BaseTopicQos()  
{ 
  *((DDS::DataWriterQos*)this) =
    *(DDS::DomainParticipantFactory::datawriter_qos_default());
  this->copy_topic_qos(tqos);
}

dds::DataWriterQos::~DataWriterQos() { }
void 
dds::DataWriterQos::copy_topic_qos(const TopicQos & tqos) 
{
  this->durability = tqos.durability;
  this->deadline = tqos.deadline;
  this->latency_budget = tqos.latency_budget;
  this->liveliness = tqos.liveliness;
  this->reliability = tqos.reliability;
  this->destination_order = tqos.destination_order;
  this->history = tqos.history;
  this->resource_limits = tqos.resource_limits;
}

// Transport Priority Qos
void 
dds::DataWriterQos::set_priority(long prio)
{
  this->transport_priority.value = prio;
}
  
// Ownership Strenght Qos
void 
dds::DataWriterQos::set_strength(long value) 
{
  this->ownership.kind = DDS::EXCLUSIVE_OWNERSHIP_QOS;
  this->ownership_strength.value = value;
}


void
dds::DataWriterQos::set_exclusive() 
{
  this->ownership.kind = DDS::EXCLUSIVE_OWNERSHIP_QOS;
}

void
dds::DataWriterQos::set_shared() 
{
  this->ownership.kind = DDS::SHARED_OWNERSHIP_QOS;
}


// Writer Data Lifecycle Qos
void 
dds::DataWriterQos::set_auto_dispose(bool on) 
{
  this->writer_data_lifecycle.autodispose_unregistered_instances = on;
}

// Lifespan Qos
void 
dds::DataWriterQos::set_lifespan(DDS::Duration_t duration)
{
  this->lifespan.duration = duration;
}

//////////////////////////////////////////////////////////////////////////////

dds::DataReaderQos::DataReaderQos() :  
  BaseTopicQos<DDS::DataReaderQos, NullInitializer>::BaseTopicQos()  
{ 
  *((DDS::DataReaderQos*)this) = 
    *(DDS::DomainParticipantFactory::datareader_qos_default());  
}

dds::DataReaderQos::DataReaderQos(const TopicQos& tqos) :  
  BaseTopicQos<DDS::DataReaderQos, NullInitializer>::BaseTopicQos()  
{ 
  *((DDS::DataReaderQos*)this) = 
    *(DDS::DomainParticipantFactory::datareader_qos_default());  
  this->copy_topic_qos(tqos);
}

dds::DataReaderQos::~DataReaderQos() { }
void 
dds::DataReaderQos::copy_topic_qos(const TopicQos & tqos) 
{
  this->durability = tqos.durability;
  this->deadline = tqos.deadline;
  this->latency_budget = tqos.latency_budget;
  this->liveliness = tqos.liveliness;
  this->reliability = tqos.reliability;
  this->destination_order = tqos.destination_order;
  this->history = tqos.history;
  this->resource_limits = tqos.resource_limits;
}

void 

dds::DataReaderQos::set_lifespan(DDS::Duration_t duration)
{
  this->reader_lifespan.use_lifespan = true;
  this->reader_lifespan.duration = duration;
}

void 
dds::DataReaderQos::set_data_lifecycle(DDS::Duration_t purge_no_writer, 
		   DDS::Duration_t purge_disposed,
		   bool enable_invalid_samples)
{
  this->reader_data_lifecycle.autopurge_nowriter_samples_delay = purge_no_writer;
  this->reader_data_lifecycle.autopurge_disposed_samples_delay = purge_disposed;
  this->reader_data_lifecycle.enable_invalid_samples = enable_invalid_samples;
}

void 
dds::DataReaderQos::set_time_filter(DDS::Duration_t min_separation)
{
  this->time_based_filter.minimum_separation = min_separation;
}

void
dds::DataReaderQos::set_exclusive() 
{
  this->ownership.kind = DDS::EXCLUSIVE_OWNERSHIP_QOS;
}

void
dds::DataReaderQos::set_shared() 
{
  this->ownership.kind = DDS::SHARED_OWNERSHIP_QOS;
}


//////////////////////////////////////////////////////////////////////////////

dds::PubQosInitializer::PubQosInitializer(dds::DomainParticipant dp) :
  dp_(dp) { }

dds::PubQosInitializer::~PubQosInitializer() { }

void 
dds::PubQosInitializer::operator()(DDS::PublisherQos& qos) 
{
  dp_->get_default_publisher_qos(qos);
}

//////////////////////////////////////////////////////////////////////////////

dds::SubQosInitializer::SubQosInitializer(dds::DomainParticipant dp) :
  dp_(dp) { }

dds::SubQosInitializer::~SubQosInitializer() { }

void 
dds::SubQosInitializer::operator()(DDS::SubscriberQos& qos) 
{
  dp_->get_default_subscriber_qos(qos);
}
//////////////////////////////////////////////////////////////////////////////

dds::PublisherQos::PublisherQos() : 
  BasePubSubQos<DDS::PublisherQos, PubQosInitializer>::BasePubSubQos()  { }

dds::PublisherQos::~PublisherQos() { }

//////////////////////////////////////////////////////////////////////////////

dds::SubscriberQos::SubscriberQos() : 
  BasePubSubQos<DDS::SubscriberQos, SubQosInitializer>::BasePubSubQos()  { }

dds::SubscriberQos::~SubscriberQos() { }
