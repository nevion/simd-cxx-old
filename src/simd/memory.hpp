#ifndef AC_SIMD_DELETER_HPP_
#define AC_SIMD_DELETER_HPP_

// -- Boost Includes
#include <boost/shared_ptr.hpp>

// -- OpenSplice DDS Includes
#include <dds_dcps.h>
#include <ccpp_dds_dcps.h>

namespace simd {
  namespace mem {
    class DPDeleter;
    class PubDeleter;
    class SubDeleter;
    class TopicDeleter;
    class DWDeleter;
    class DRDeleter;
  }
}

class simd::mem::DPDeleter {
public:
  void  operator()(DDS::DomainParticipant* dp);
};

// The following class should be written using boost::bind

class simd::mem::PubDeleter {
public:
  PubDeleter(boost::shared_ptr<DDS::DomainParticipant> dp);

  ~PubDeleter();

  void operator()(DDS::Publisher* p);

private:
  boost::shared_ptr<DDS::DomainParticipant> dp_;
};


class simd::mem::SubDeleter {
public:
  SubDeleter(boost::shared_ptr<DDS::DomainParticipant> dp);

  ~SubDeleter();

  void operator()(DDS::Subscriber* s);

private:
  boost::shared_ptr<DDS::DomainParticipant> dp_;
};

class simd::mem::DWDeleter {
public:
  DWDeleter(boost::shared_ptr<DDS::Publisher> pub);
  ~DWDeleter();
  void  operator()(DDS::DataWriter* w);

private:
  boost::shared_ptr<DDS::Publisher> pub_;  
};

class simd::mem::DRDeleter {
public:
  DRDeleter(boost::shared_ptr<DDS::Subscriber> sub);
  ~DRDeleter();
  void  operator()(DDS::DataReader* r);

private:
  boost::shared_ptr<DDS::Subscriber> sub_;  
};

#endif /* AC_SIMD_DELETER_HPP_ */
