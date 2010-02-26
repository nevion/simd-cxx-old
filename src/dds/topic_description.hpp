#ifndef AC_SIMD_DDS_TOPIC_DESCRIPTION_HPP_
#define AC_SIMD_DDS_TOPIC_DESCRIPTION_HPP_

#include <string>
#include <dds/config.hpp>
#include <dds/domain.hpp>

namespace dds {
  class TopicDescription;
}

class SIMD_API dds::TopicDescription {
public:
  virtual ~TopicDescription();
  
public:
  virtual std::string get_name() const = 0;
  virtual std::string get_type_name() const = 0;
  virtual dds::DomainParticipant get_participant() const = 0;
};

#endif /* AC_SIMD_DDS_TOPIC_DESCRIPTION_HPP_*/
