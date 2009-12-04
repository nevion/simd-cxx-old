#ifndef AC_SIMD_DDS_QOS_HPP_
#define AC_SIMD_DDS_QOS_HPP_

// -- STD C++ Include
#include <string>
#include <vector>

// -- Boost Includes
#include <boost/shared_ptr.hpp>

// -- dds Includes
#include <dds/runtime.hpp>
#include <dds/domain.hpp>

namespace dds {

  //////////////////////////////////////////////////////////////////////////////

  template <typename DDS_QOS, typename INITIALIZER>
  class BaseTopicQos : public DDS_QOS {
  public:
    BaseTopicQos() {
   	 ::dds::DomainParticipant dp =
   			 Runtime::instance()->get_participant();
      INITIALIZER initializer(dp);
      initializer(*this);
    }

    ~BaseTopicQos() { }

  public:
    // -- Reliability Qos
    void set_reliable() {
      this->reliability.kind = DDS::RELIABLE_RELIABILITY_QOS;
    }
    void set_reliable(DDS::Duration_t timeout) {
      this->reliability.kind = DDS::BEST_EFFORT_RELIABILITY_QOS;
      this->reliability.max_bloking_time = timeout;
    }
    void set_best_effort() {
      this->reliability.kind = DDS::BEST_EFFORT_RELIABILITY_QOS;
    }
  
    // -- Durability Qos
    void set_volatile() {
      this->durability.kind = DDS::VOLATILE_DURABILITY_QOS;
    }

    void set_transient_local() {
      // Not a bug, on OpenSplice DDS TRANSIENT_LOCAL gets anyway TRANSIENT behaviour
      this->durability.kind = DDS::TRANSIENT_DURABILITY_QOS;
    }
  
    void set_transient() {
      this->durability.kind = DDS::TRANSIENT_DURABILITY_QOS;
    }


    void set_persistent() {
      this->durability.kind = DDS::PERSISTENT_DURABILITY_QOS;
    }
  
    // -- Latency Budget Qos
    void set_latency_budget(DDS::Duration_t latency_budget) {
      this->latency_budget.duration = latency_budget;
    }

    // -- Deadline Qos 
    void set_deadline(DDS::Duration_t deadline) {
      this->deadline.period = deadline;
    }

    // -- Destination Order Qos
    void set_source_order() {
      this->destination_order.kind = DDS::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
    }
    void set_dest_order() {
      this->destination_order.kind = DDS::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
    }

    // -- History Qos
    void set_keep_all() {
      this->history.kind = DDS::KEEP_ALL_HISTORY_QOS;
    }

    void set_keep_last(int k = 1) {
      this->history.kind = DDS::KEEP_LAST_HISTORY_QOS;
      this->history.depth = k;
    }

    // -- Resource Limits
    void set_resource_limits(long max_samples, long max_instances, long max_sample_per_instances) {
      this->resource_limits.max_samples = max_samples;
      this->resource_limits.max_instances = max_instances;
      this->resource_limits.max_sample_per_instances = max_sample_per_instances;
    }

    // -- Ownership Qos
    void set_shared_ownership() {
      this->ownership.kind = DDS::SHARED_OWNERSHIP_QOS;
    }

    void set_exclusive_owenership() {
      this->ownership.kind = DDS::EXCLUSIVE_OWNERSHIP_QOS;
    }

  };

  //////////////////////////////////////////////////////////////////////////////

  class TopicQosInitializer {
  public:
    TopicQosInitializer(dds::DomainParticipant dp);
    ~TopicQosInitializer();
  public:
    void operator()(DDS::TopicQos& qos);

  private:
    ::dds::DomainParticipant dp_;
  };

  //////////////////////////////////////////////////////////////////////////////

  class TopicQos : public BaseTopicQos<DDS::TopicQos, TopicQosInitializer> {
  public:
    TopicQos();
    ~TopicQos();

  public:
    // Transport Priority Qos
    void set_priority(long prio);

    void set_durability_service(DDS::Duration_t service_cleanup_delay,
				DDS::HistoryQosPolicyKind history_kind,
				DDS::Long history_depth,
				DDS::Long max_samples,
				DDS::Long max_instances,
				DDS::Long max_samples_per_instance);
			      
  
  
  };

  //////////////////////////////////////////////////////////////////////////////


  class NullInitializer {
  public:
    NullInitializer(::dds::DomainParticipant) { }
    ~NullInitializer() { }
  public:
    template <typename QOS> void operator()(QOS& qos) { }

  };

  //////////////////////////////////////////////////////////////////////////////
  class DataWriterQos : public BaseTopicQos<DDS::DataWriterQos, NullInitializer> {
  public:
    DataWriterQos();
    DataWriterQos(const TopicQos& tqos);
    ~DataWriterQos();
  public:
    // Transport Priority Qos
    void set_priority(long prio);
  
    // Ownership Strenght Qos
    void set_strength(long value);
    void set_shared();
    void set_exclusive();

    // Writer Data Lifecycle Qos
    void set_auto_dispose(bool autod);

    // Lifespan Qos
    void set_lifespan(DDS::Duration_t duration);


  protected:
    void copy_topic_qos(const TopicQos & tqos);
  };

  //////////////////////////////////////////////////////////////////////////////

  class DataReaderQos : public BaseTopicQos<DDS::DataReaderQos, NullInitializer> {
  public:
    DataReaderQos();
    DataReaderQos(const TopicQos& tqos);
    ~DataReaderQos();
  public:
    void set_lifespan(DDS::Duration_t duration);

    void set_data_lifecycle(DDS::Duration_t purge_no_writer, 
			    DDS::Duration_t purge_disposed,
			    bool enable_invalid_samples);

    void set_exclusive();

    void set_shared();

    void set_time_filter(DDS::Duration_t min_separation);

  protected:
    void copy_topic_qos(const TopicQos & tqos);


  };

  //////////////////////////////////////////////////////////////////////////////

  template <typename DDS_QOS, typename INITIALIZER>
  class BasePubSubQos : public DDS_QOS {
  public:
    BasePubSubQos() {
      ::dds::DomainParticipant dp =
      		Runtime::instance()->get_participant();
      INITIALIZER initializer(dp);
      initializer(*this);
    }

    ~BasePubSubQos() { }

  public:
    void set_instance_presentation(bool coherent, bool ordered) {
      this->presentation.access_scope = DDS::INSTANCE_PRESENTATION_QOS;
      this->coherent_access = coherent;
      this->ordered_access = ordered;
    }

    void set_topic_presentation(bool coherent, bool ordered) {
      this->presentation.access_scope = DDS::TOPIC_PRESENTATION_QOS;
      this->coherent_access = coherent;
      this->ordered_access = ordered;
    }
  
    void set_group_presentation(bool coherent, bool ordered) {
      this->presentation.access_scope = DDS::GROUP_PRESENTATION_QOS;
      this->coherent_access = coherent;
      this->ordered_access = ordered;
    }

  
    void set_partition(const std::string& partition) {
      this->partition.name.length (1);
      this->partition.name[0] = DDS::string_dup(partition.c_str());
    }

  
    void set_partition(const std::vector<std::string>& partitions) {
      this->partition.name.length (partitions.size());
      for (int i = 0; i < partitions.size(); ++i) 
	this->partition.name[i] = DDS::string_dup(partitions[i].c_str());
    }
  };

  //////////////////////////////////////////////////////////////////////////////


  class PubQosInitializer {
  public:
    PubQosInitializer(dds::DomainParticipant dp);
    ~PubQosInitializer();
  public:
    void operator()(DDS::PublisherQos& qos);
  
  private:
   ::dds::DomainParticipant dp_;
  };

  //////////////////////////////////////////////////////////////////////////////

  class PublisherQos : public BasePubSubQos<DDS::PublisherQos, PubQosInitializer> {
  public:
    PublisherQos();
    ~PublisherQos();
  };

  //////////////////////////////////////////////////////////////////////////////

  class SubQosInitializer {
  public:
    SubQosInitializer(dds::DomainParticipant dp);
    ~SubQosInitializer();
  public:
    void operator()(DDS::SubscriberQos& qos);

  private:
    ::dds::DomainParticipant dp_;
  };

  //////////////////////////////////////////////////////////////////////////////
  class SubscriberQos : public BasePubSubQos<DDS::SubscriberQos, SubQosInitializer> {
  public:
    SubscriberQos();
    ~SubscriberQos();
  };
}

#endif /* AC_SIMD_DDS_QOS_HPP_ */
