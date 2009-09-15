#include <simd/domain.hpp>
#include <simd/config.hpp>
#include <simd/qos.hpp>
#include <simd/memory.hpp>

simd::DomainParticipant::DomainParticipant() {
	DDS::DomainParticipantFactory_ptr dpf =
			DDS::DomainParticipantFactory::get_instance();

	Assert::postcondition((dpf != 0), "Unable to get DomainParticipantFactory",
			__FILE__);

	DDS::DomainParticipant* dp = dpf->create_participant(0,
			PARTICIPANT_QOS_DEFAULT, 0, DDS::ANY_STATUS);

	Assert::postcondition((dp != 0), "Unable to get DomainParticipant", __FILE__);
	this->reset(dp, simd::mem::DPDeleter());
}

simd::DomainParticipant::DomainParticipant(const std::string& domain) {
	DDS::DomainParticipantFactory_ptr dpf =
			DDS::DomainParticipantFactory::get_instance();

	Assert::postcondition((dpf != 0), "Unable to get DomainParticipantFactory",
			__FILE__);

	DDS::DomainParticipant* dp = dpf->create_participant(domain.c_str(),
			PARTICIPANT_QOS_DEFAULT, 0, DDS::ANY_STATUS);

	Assert::postcondition((dp != 0), "Unable to get DomainParticipant", __FILE__);
	this->reset(dp, simd::mem::DPDeleter());
}

simd::DomainParticipant::~DomainParticipant() {
	// TODO Auto-generated destructor stub
}
