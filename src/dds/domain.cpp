#include <dds/domain.hpp>
#include <dds/config.hpp>
#include <dds/qos.hpp>
#include <dds/memory.hpp>

dds::DomainParticipant::DomainParticipant() 
{
  DDS::DomainParticipantFactory_var dpf =
    DDS::DomainParticipantFactory::get_instance();
  
  Assert::postcondition((dpf.in() != 0), 
			"Unable to get DomainParticipantFactory",
			__FILE__);
  
  DDS::DomainParticipant* dp = 
    dpf->create_participant(0,
			    PARTICIPANT_QOS_DEFAULT, 
			    0, 
			    DDS::ANY_STATUS);
  
  Assert::postcondition((dp != 0), 
			"Unable to get DomainParticipant", 
			__FILE__);

  SIMD_LOG(SIMD_ALLOC, "Created Participant at: " << std::hex << dp << std::dec);
  this->reset(dp, dds::mem::DPDeleter());
}

dds::DomainParticipant::DomainParticipant(const std::string& domain) 
{
  DDS::DomainParticipantFactory_var dpf =
    DDS::DomainParticipantFactory::get_instance();
  
  Assert::postcondition((dpf.in() != 0), 
			"Unable to get DomainParticipantFactory",
			__FILE__);
  
  DDS::DomainParticipant* dp = 
    dpf->create_participant(domain.c_str(),
			    PARTICIPANT_QOS_DEFAULT, 
			    0, 
			    DDS::ANY_STATUS);
  
  Assert::postcondition((dp != 0), 
			"Unable to get DomainParticipant", 
			__FILE__);

  this->reset(dp, dds::mem::DPDeleter());
}

dds::DomainParticipant::~DomainParticipant() {
  // TODO Auto-generated destructor stub
}
