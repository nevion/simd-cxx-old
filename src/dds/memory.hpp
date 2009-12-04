#ifndef AC_SIMD_DDS_DELETER_HPP_
#define AC_SIMD_DDS_DELETER_HPP_

// -- Boost Includes
#include <boost/shared_ptr.hpp>

// -- SIMD_DDS Includes
#include <dds/config.hpp>

namespace dds {

  namespace mem {

    class DPDeleter {
    public:
      void  operator()(DDS::DomainParticipant* dp);
    };

    // The following class should be written using boost::bind

    class PubDeleter {
    public:
      PubDeleter(boost::shared_ptr<DDS::DomainParticipant> dp);

      ~PubDeleter();

      void operator()(DDS::Publisher* p);

    private:
      boost::shared_ptr<DDS::DomainParticipant> dp_;
    };


    class SubDeleter {
    public:
      SubDeleter(boost::shared_ptr<DDS::DomainParticipant> dp);

      ~SubDeleter();

      void operator()(DDS::Subscriber* s);

    private:
      boost::shared_ptr<DDS::DomainParticipant> dp_;
    };

    class DWDeleter {
    public:
      DWDeleter(boost::shared_ptr<DDS::Publisher> pub);
      ~DWDeleter();
      void  operator()(DDS::DataWriter* w);

    private:
      boost::shared_ptr<DDS::Publisher> pub_;  
    };

    class DRDeleter {
    public:
      DRDeleter(boost::shared_ptr<DDS::Subscriber> sub);
      ~DRDeleter();
      void  operator()(DDS::DataReader* r);

    private:
      boost::shared_ptr<DDS::Subscriber> sub_;  
    };

    template <typename DR>
    class RCondDeleter {
    public:
       RCondDeleter(boost::shared_ptr<DR> reader) : reader_(reader) { }
       ~RCondDeleter() { }
    public:
       void operator()(DDS::ReadCondition* rcond) {
          reader_->delete_readcondition(rcond);
       }

    private:
       boost::shared_ptr<DR> reader_;
    };
  }
}
#endif /* AC_SIMD_DDS_DELETER_HPP_ */
