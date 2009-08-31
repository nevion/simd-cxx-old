#include <simd/memory.hpp>

void
simd::mem::DPDeleter::operator()(DDS::DomainParticipant* dp) 
{
  DDS::DomainParticipantFactory::get_instance()->delete_participant(dp);

}

simd::mem::PubDeleter::PubDeleter(boost::shared_ptr<DDS::DomainParticipant> dp) : dp_(dp) { }

simd::mem::PubDeleter::~PubDeleter()  { }

void
simd::mem::PubDeleter::operator()(DDS::Publisher* p)
{
  dp_->delete_publisher(p);
}


simd::mem::SubDeleter::SubDeleter(boost::shared_ptr<DDS::DomainParticipant> dp) : dp_(dp) { }

simd::mem::SubDeleter::~SubDeleter() { }

void
simd::mem::SubDeleter::operator()(DDS::Subscriber* s)
{
  dp_->delete_subscriber(s);
}


simd::mem::DWDeleter::DWDeleter(boost::shared_ptr<DDS::Publisher> pub) : pub_(pub) { }
simd::mem::DWDeleter::~DWDeleter() { }
void  
simd::mem::DWDeleter::operator()(DDS::DataWriter* w)
{
  pub_->delete_datawriter(w);
}

simd::mem::DRDeleter::DRDeleter(boost::shared_ptr<DDS::Subscriber> sub) : sub_(sub) { }
simd::mem::DRDeleter::~DRDeleter() { }
void  
simd::mem::DRDeleter::operator()(DDS::DataReader* r)
{
  sub_->delete_datareader(r);
}
