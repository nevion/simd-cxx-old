#ifndef AC_SIMD_DDS_TOPIC_HPP
#define AC_SIMD_DDS_TOPIC_HPP

#include <string>

// -- Boost Include
#include <boost/shared_ptr.hpp>
#include <dds/peer/topic_impl.hpp>
#include <dds/topic_description.hpp>

namespace dds {
  template <typename T>
  class Topic;

  namespace peer {
    template <typename T>
    class TopicImpl;
  }
}


template<typename T>
class SIMD_EXPORT dds::Topic : public dds::TopicDescription {
public:
  Topic() { }

  Topic(const std::string& name, 
	const std::string type_name) 
  {
    pimpl_.reset(new dds::peer::TopicImpl<T>(name, type_name));
  }

  Topic(const std::string& name) 
  {
    pimpl_.reset(new  dds::peer::TopicImpl<T>(name));
  }

  Topic(const std::string& name, 
	const TopicQos& qos) 
  {
    pimpl_.reset(new dds::peer::TopicImpl<T>(name, qos));
  }

  Topic(const std::string& name, 
	const std::string& type_name,
	const TopicQos& qos) 
  {
    pimpl_.reset(new dds::peer::TopicImpl<T>(name, type_name, qos));
  }
  
  virtual ~Topic() { }

public:
  
  TopicQos 
  get_qos() const 
  {
    return pimpl_->get_qos();
  }


  DDS::ReturnCode_t 
  set_qos(const TopicQos& qos) 
  {
    return pimpl_->set_qos(qos);
  }

  virtual std::string 
  get_name() const
  {
    return pimpl_->get_name();
  }

  virtual std::string 
  get_type_name() const
  {
    return pimpl_->get_type_name();
  }

  virtual dds::DomainParticipant 
  get_participant() const
  {
    return pimpl_->get_participant();
  }
  
  boost::shared_ptr<dds::peer::TopicImpl<T> >
  operator->() {
    return pimpl_;
  }
protected:
  boost::shared_ptr<dds::peer::TopicImpl<T> > pimpl_;
  
};


#endif /* AC_SIMD_DDS_TOPIC_HPP */
