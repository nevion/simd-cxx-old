#include <dds/memory.hpp>
#include <iostream>

void
dds::mem::DPDeleter::operator()(DDS::DomainParticipant* dp) 
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::get_instance();
  dpf->delete_participant(dp);
  DDS::release(dp);

  SIMD_LOG(SIMD_ALLOC, "Deleted Participant at: " << std::hex << dp << std::dec);

}

dds::mem::PubDeleter::PubDeleter(boost::shared_ptr<DDS::DomainParticipant> dp) : dp_(dp) { }

dds::mem::PubDeleter::~PubDeleter()  { }

void
dds::mem::PubDeleter::operator()(DDS::Publisher* p)
{
  dp_->delete_publisher(p);
  DDS::release(p);
  SIMD_LOG(SIMD_ALLOC, "Deleted Publisher at: " << std::hex << p << std::dec);
}


dds::mem::SubDeleter::SubDeleter(boost::shared_ptr<DDS::DomainParticipant> dp) : dp_(dp) { }

dds::mem::SubDeleter::~SubDeleter() { }

void
dds::mem::SubDeleter::operator()(DDS::Subscriber* s)
{
  dp_->delete_subscriber(s);
  DDS::release(s);
  SIMD_LOG(SIMD_ALLOC, "Deleted Subscriber at: " << std::hex << s << std::dec);
}


dds::mem::DWDeleter::DWDeleter(boost::shared_ptr<DDS::Publisher> pub) : pub_(pub) { }
dds::mem::DWDeleter::~DWDeleter() { }
void  
dds::mem::DWDeleter::operator()(DDS::DataWriter* w)
{
  pub_->delete_datawriter(w);
  DDS::release(w);
  SIMD_LOG(SIMD_ALLOC, "Deleted DataWriter at: " << std::hex << w << std::dec);
}

dds::mem::DRDeleter::DRDeleter(boost::shared_ptr<DDS::Subscriber> sub) : sub_(sub) { }
dds::mem::DRDeleter::~DRDeleter() { }
void  
dds::mem::DRDeleter::operator()(DDS::DataReader* r)
{
  sub_->delete_datareader(r);
  DDS::release(r);
  SIMD_LOG(SIMD_ALLOC, "Deleted DataReader at: " << std::hex << r << std::dec);
}
