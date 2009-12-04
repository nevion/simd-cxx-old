#include <dds/memory.hpp>
#include <iostream>

void
dds::mem::DPDeleter::operator()(DDS::DomainParticipant* dp) 
{
  DDS::DomainParticipantFactory::get_instance()->delete_participant(dp);

}

dds::mem::PubDeleter::PubDeleter(boost::shared_ptr<DDS::DomainParticipant> dp) : dp_(dp) { }

dds::mem::PubDeleter::~PubDeleter()  { }

void
dds::mem::PubDeleter::operator()(DDS::Publisher* p)
{
  dp_->delete_publisher(p);
}


dds::mem::SubDeleter::SubDeleter(boost::shared_ptr<DDS::DomainParticipant> dp) : dp_(dp) { }

dds::mem::SubDeleter::~SubDeleter() { }

void
dds::mem::SubDeleter::operator()(DDS::Subscriber* s)
{
  dp_->delete_subscriber(s);
}


dds::mem::DWDeleter::DWDeleter(boost::shared_ptr<DDS::Publisher> pub) : pub_(pub) { }
dds::mem::DWDeleter::~DWDeleter() { }
void  
dds::mem::DWDeleter::operator()(DDS::DataWriter* w)
{
  std::cout << "dds::mem::DWDeleter::operator() : " 
	    << "w = " << std::hex << w << std::endl;
  pub_->delete_datawriter(w);
}

dds::mem::DRDeleter::DRDeleter(boost::shared_ptr<DDS::Subscriber> sub) : sub_(sub) { }
dds::mem::DRDeleter::~DRDeleter() { }
void  
dds::mem::DRDeleter::operator()(DDS::DataReader* r)
{
  std::cout << "dds::mem::DRDeleter::operator() : " 
	    << "r = " << std::hex << r << std::endl;
  sub_->delete_datareader(r);
}
