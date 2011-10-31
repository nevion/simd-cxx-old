#include <dds/domain.hpp>
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

#if (SIMD_OSPL_MAJ_VER == 6)

dds::DomainParticipant::DomainParticipant(int domainId) 
{
  DDS::DomainParticipantFactory_var dpf =
    DDS::DomainParticipantFactory::get_instance();
  
  Assert::postcondition((dpf.in() != 0), 
			"Unable to get DomainParticipantFactory",
			__FILE__);
  
  DDS::DomainParticipant* dp = 
    dpf->create_participant(domainId,
			    PARTICIPANT_QOS_DEFAULT, 
			    0, 
			    DDS::ANY_STATUS);
  
  Assert::postcondition((dp != 0), 
			"Unable to get DomainParticipant", 
			__FILE__);

  this->reset(dp, dds::mem::DPDeleter());
}

#else
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
#endif 
dds::DomainParticipant::~DomainParticipant() {
  // TODO Auto-generated destructor stub
}
