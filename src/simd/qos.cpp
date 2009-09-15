#include <simd/qos.hpp>
#include <simd/assertion.hpp>

#include "config.hpp"

simd::TopicQosInitializer::TopicQosInitializer(simd::DomainParticipant dp)
  : dp_(dp) { }

simd::TopicQosInitializer::~TopicQosInitializer() { }

void
simd::TopicQosInitializer::operator()(DDS::TopicQos& qos)
{
  dp_->get_default_topic_qos(qos);
}

//////////////////////////////////////////////////////////////////////////////

simd::TopicQos::TopicQos() : 
  BaseTopicQos<DDS::TopicQos, TopicQosInitializer>::BaseTopicQos()  { }

simd::TopicQos::~TopicQos() { }

void 
simd::TopicQos::set_priority(long prio) {
  this->transport_priority.value = prio;
}
 
void 
simd::TopicQos::set_durability_service(DDS::Duration_t service_cleanup_delay,
				       DDS::HistoryQosPolicyKind history_kind,
				       DDS::Long history_depth,
				       DDS::Long max_samples,
				       DDS::Long max_instances,
				       DDS::Long max_samples_per_instance)
{
  simd::Assert::precondition(false, "<TopicQoS::set_durability_service>: not implemented yet", __FILE__);
}

//////////////////////////////////////////////////////////////////////////////

simd::DataWriterQos::DataWriterQos() :  
  BaseTopicQos<DDS::DataWriterQos, NullInitializer>::BaseTopicQos()  
{ 
  *((DDS::DataWriterQos*)this) =
    *(DDS::DomainParticipantFactory::datawriter_qos_default());
}

simd::DataWriterQos::DataWriterQos(const TopicQos& tqos) :  
  BaseTopicQos<DDS::DataWriterQos, NullInitializer>::BaseTopicQos()  
{ 
  *((DDS::DataWriterQos*)this) =
    *(DDS::DomainParticipantFactory::datawriter_qos_default());
  this->copy_topic_qos(tqos);
}

simd::DataWriterQos::~DataWriterQos() { }
void 
simd::DataWriterQos::copy_topic_qos(const TopicQos & tqos) 
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
simd::DataWriterQos::set_priority(long prio)
{
  this->transport_priority.value = prio;
}
  
// Ownership Strenght Qos
void 
simd::DataWriterQos::set_strength(long value) 
{
  this->ownership_strength.value = value;
}

// Writer Data Lifecycle Qos
void 
simd::DataWriterQos::set_auto_dispose(bool on) 
{
  this->writer_data_lifecycle.autodispose_unregistered_instances = on;
}

// Lifespan Qos
void 
simd::DataWriterQos::set_lifespan(DDS::Duration_t duration)
{
  this->lifespan.duration = duration;
}

//////////////////////////////////////////////////////////////////////////////

simd::DataReaderQos::DataReaderQos() :  
  BaseTopicQos<DDS::DataReaderQos, NullInitializer>::BaseTopicQos()  
{ 
  *((DDS::DataReaderQos*)this) = 
    *(DDS::DomainParticipantFactory::datareader_qos_default());  
}

simd::DataReaderQos::DataReaderQos(const TopicQos& tqos) :  
  BaseTopicQos<DDS::DataReaderQos, NullInitializer>::BaseTopicQos()  
{ 
  *((DDS::DataReaderQos*)this) = 
    *(DDS::DomainParticipantFactory::datareader_qos_default());  
  this->copy_topic_qos(tqos);
}

simd::DataReaderQos::~DataReaderQos() { }
void 
simd::DataReaderQos::copy_topic_qos(const TopicQos & tqos) 
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

simd::DataReaderQos::set_lifespan(DDS::Duration_t duration)
{
  this->reader_lifespan.use_lifespan = true;
  this->reader_lifespan.duration = duration;
}

void 
simd::DataReaderQos::set_data_lifecycle(DDS::Duration_t purge_no_writer, 
		   DDS::Duration_t purge_disposed,
		   bool enable_invalid_samples)
{
  this->reader_data_lifecycle.autopurge_nowriter_samples_delay = purge_no_writer;
  this->reader_data_lifecycle.autopurge_disposed_samples_delay = purge_disposed;
  this->reader_data_lifecycle.enable_invalid_samples = enable_invalid_samples;
}

void 
simd::DataReaderQos::set_time_filter(DDS::Duration_t min_separation)
{
  this->time_based_filter.minimum_separation = min_separation;
}

//////////////////////////////////////////////////////////////////////////////

simd::PubQosInitializer::PubQosInitializer(simd::DomainParticipant dp) :
  dp_(dp) { }

simd::PubQosInitializer::~PubQosInitializer() { }

void 
simd::PubQosInitializer::operator()(DDS::PublisherQos& qos) 
{
  dp_->get_default_publisher_qos(qos);
}

//////////////////////////////////////////////////////////////////////////////

simd::SubQosInitializer::SubQosInitializer(simd::DomainParticipant dp) :
  dp_(dp) { }

simd::SubQosInitializer::~SubQosInitializer() { }

void 
simd::SubQosInitializer::operator()(DDS::SubscriberQos& qos) 
{
  dp_->get_default_subscriber_qos(qos);
}
//////////////////////////////////////////////////////////////////////////////

simd::PublisherQos::PublisherQos() : 
  BasePubSubQos<DDS::PublisherQos, PubQosInitializer>::BasePubSubQos()  { }

simd::PublisherQos::~PublisherQos() { }

//////////////////////////////////////////////////////////////////////////////

simd::SubscriberQos::SubscriberQos() : 
  BasePubSubQos<DDS::SubscriberQos, SubQosInitializer>::BasePubSubQos()  { }

simd::SubscriberQos::~SubscriberQos() { }
