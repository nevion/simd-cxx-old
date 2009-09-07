#ifndef AC_SIMD_RUNTIME_HPP_
#define AC_SIMD_RUNTIME_HPP_

// -- STD C++ Include
#include <string>

// -- Boost Includes
#include <boost/shared_ptr.hpp>

#include <simd/config.hpp>

namespace simd {

class Runtime {
private:
  Runtime();
  
public:
  static const std::string DEFAULT_DOMAIN;
  static const std::string DEFAULT_PARTITION;

public:
  ~Runtime();

public:
  static void init();

  static void init(std::ifstream& is);
  
  static void init(const std::string& partition);
  
  static void init(const std::string& domain, 
		   const std::string& partition);

  static void init(const std::string& domain, 
		   const DDS::DomainParticipantQos& qos);
  
  static boost::shared_ptr<Runtime> instance() throw();
  
  // TODO: Implement this method1
  //  void set_listener(shared_ptr<DDS::DomainParticipantListener> listener);

  //@TODO: Provide SIMD facades to the DomainParticipant, Publisher, Subscriber, etc.
  /**
   * Get the default participant.
   */
  boost::shared_ptr<DDS::DomainParticipant> get_participant() const throw();
  
  /**
   * Get the default publisher.
   */
  boost::shared_ptr<DDS::Publisher> get_publisher() const throw();
  
  /**
   * Get the default subscriber.
   */
  boost::shared_ptr<DDS::Subscriber> get_subscriber() const throw();
  
private:  
  static boost::shared_ptr<Runtime> this_;
  
  boost::shared_ptr<DDS::DomainParticipant> dp_;  
  boost::shared_ptr<DDS::Publisher> pub_;
  boost::shared_ptr<DDS::Subscriber> sub_;
  
};
}
#endif /* AC_SIMD_RUNTIME_HPP_ */
