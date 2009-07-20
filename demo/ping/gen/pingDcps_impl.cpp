#include "gapi.h"
#include "gapi_loanRegistry.h"
#include "pingSplDcps.h"
#include "pingDcps_impl.h"
#include "ccpp_DataReader_impl.h"


extern c_bool
__PingType__copyIn(
    c_base base,
    struct PingType *from,
    struct _PingType *to);

extern void
__PingType__copyOut(
    void *_from,
    void *_to);

// DDS PingType TypeSupportFactory Object Body

 DDS::DataWriter_ptr 
PingTypeTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new PingTypeDataWriter_impl(handle);
}

 DDS::DataReader_ptr 
PingTypeTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new PingTypeDataReader_impl (handle);
}

// DDS PingType TypeSupport Object Body

 PingTypeTypeSupport::PingTypeTypeSupport(void) :
    TypeSupport_impl(
        __PingType__name(),
        __PingType__keys(),
        PingTypeTypeSupport::metaDescriptor,
        (gapi_copyIn) __PingType__copyIn,
        (gapi_copyOut) __PingType__copyOut,
        (gapi_readerCopy) DDS::ccpp_DataReaderCopy<PingTypeSeq, PingType>,
        new  PingTypeTypeSupportFactory())
{
    // Parent constructor takes care of everything.
}

 PingTypeTypeSupport::~PingTypeTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

 DDS::ReturnCode_t
PingTypeTypeSupport::register_type(
    DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

 char *
PingTypeTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS PingType DataWriter_impl Object Body

 PingTypeDataWriter_impl::PingTypeDataWriter_impl (
    gapi_dataWriter handle
) : DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

 PingTypeDataWriter_impl::~PingTypeDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

 DDS::InstanceHandle_t
PingTypeDataWriter_impl::register_instance(
    const PingType & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

 DDS::InstanceHandle_t 
PingTypeDataWriter_impl::register_instance_w_timestamp(
    const PingType & instance_data,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

 DDS::ReturnCode_t
PingTypeDataWriter_impl::unregister_instance(
    const PingType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

 DDS::ReturnCode_t 
PingTypeDataWriter_impl::unregister_instance_w_timestamp(
    const PingType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
PingTypeDataWriter_impl::write(
    const PingType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

 DDS::ReturnCode_t
PingTypeDataWriter_impl::write_w_timestamp(
    const PingType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
PingTypeDataWriter_impl::dispose(
    const PingType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

 DDS::ReturnCode_t 
PingTypeDataWriter_impl::dispose_w_timestamp(
    const PingType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
PingTypeDataWriter_impl::writedispose(
    const PingType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

 DDS::ReturnCode_t
PingTypeDataWriter_impl::writedispose_w_timestamp(
    const PingType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t 
PingTypeDataWriter_impl::get_key_value(
    PingType & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
PingTypeDataWriter_impl::lookup_instance(
	const PingType & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS PingType DataReader_impl Object Body

 PingTypeDataReader_impl::PingTypeDataReader_impl (
    gapi_dataReader handle
) : DDS::DataReader_impl(handle)
{
    // Parent constructor takes care of everything.
}

 PingTypeDataReader_impl::~PingTypeDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


 DDS::ReturnCode_t
PingTypeDataReader_impl::read(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
PingTypeDataReader_impl::take(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
PingTypeDataReader_impl::read_w_condition(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

 DDS::ReturnCode_t
PingTypeDataReader_impl::take_w_condition(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
PingTypeDataReader_impl::read_next_sample(
    PingType & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t 
PingTypeDataReader_impl::take_next_sample(
    PingType & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t
PingTypeDataReader_impl::read_instance(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
PingTypeDataReader_impl::take_instance(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
PingTypeDataReader_impl::read_next_instance(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
PingTypeDataReader_impl::take_next_instance(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


 DDS::ReturnCode_t 
PingTypeDataReader_impl::read_next_instance_w_condition(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
PingTypeDataReader_impl::take_next_instance_w_condition(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t
PingTypeDataReader_impl::return_loan(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status = DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() && 
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReader_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        PingTypeSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = DDS::RETCODE_OK;
                    } else {
                        status = DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


 DDS::ReturnCode_t 
PingTypeDataReader_impl::get_key_value(
    PingType & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
PingTypeDataReader_impl::lookup_instance(
    const PingType & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

 DDS::ReturnCode_t 
PingTypeDataReader_impl::check_preconditions(
    PingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples)
{
    DDS::ReturnCode_t status = DDS::RETCODE_PRECONDITION_NOT_MET;
    
    if ( received_data.length() == info_seq.length() &&
         received_data.maximum() == info_seq.maximum() &&
         received_data.release() == info_seq.release() ) {
        if ( received_data.maximum() == 0 || received_data.release() ) {
            if (received_data.maximum() == 0 ||
		max_samples <= static_cast<DDS::Long>(received_data.maximum()) ||
		max_samples == DDS::LENGTH_UNLIMITED ) {
                status = DDS::RETCODE_OK;
            }
        }
    }
    return status;
}
extern c_bool
__KeyedPingType__copyIn(
    c_base base,
    struct KeyedPingType *from,
    struct _KeyedPingType *to);

extern void
__KeyedPingType__copyOut(
    void *_from,
    void *_to);

// DDS KeyedPingType TypeSupportFactory Object Body

 DDS::DataWriter_ptr 
KeyedPingTypeTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new KeyedPingTypeDataWriter_impl(handle);
}

 DDS::DataReader_ptr 
KeyedPingTypeTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new KeyedPingTypeDataReader_impl (handle);
}

// DDS KeyedPingType TypeSupport Object Body

 KeyedPingTypeTypeSupport::KeyedPingTypeTypeSupport(void) :
    TypeSupport_impl(
        __KeyedPingType__name(),
        __KeyedPingType__keys(),
        KeyedPingTypeTypeSupport::metaDescriptor,
        (gapi_copyIn) __KeyedPingType__copyIn,
        (gapi_copyOut) __KeyedPingType__copyOut,
        (gapi_readerCopy) DDS::ccpp_DataReaderCopy<KeyedPingTypeSeq, KeyedPingType>,
        new  KeyedPingTypeTypeSupportFactory())
{
    // Parent constructor takes care of everything.
}

 KeyedPingTypeTypeSupport::~KeyedPingTypeTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

 DDS::ReturnCode_t
KeyedPingTypeTypeSupport::register_type(
    DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

 char *
KeyedPingTypeTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS KeyedPingType DataWriter_impl Object Body

 KeyedPingTypeDataWriter_impl::KeyedPingTypeDataWriter_impl (
    gapi_dataWriter handle
) : DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

 KeyedPingTypeDataWriter_impl::~KeyedPingTypeDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

 DDS::InstanceHandle_t
KeyedPingTypeDataWriter_impl::register_instance(
    const KeyedPingType & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

 DDS::InstanceHandle_t 
KeyedPingTypeDataWriter_impl::register_instance_w_timestamp(
    const KeyedPingType & instance_data,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

 DDS::ReturnCode_t
KeyedPingTypeDataWriter_impl::unregister_instance(
    const KeyedPingType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

 DDS::ReturnCode_t 
KeyedPingTypeDataWriter_impl::unregister_instance_w_timestamp(
    const KeyedPingType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
KeyedPingTypeDataWriter_impl::write(
    const KeyedPingType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

 DDS::ReturnCode_t
KeyedPingTypeDataWriter_impl::write_w_timestamp(
    const KeyedPingType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
KeyedPingTypeDataWriter_impl::dispose(
    const KeyedPingType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

 DDS::ReturnCode_t 
KeyedPingTypeDataWriter_impl::dispose_w_timestamp(
    const KeyedPingType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
KeyedPingTypeDataWriter_impl::writedispose(
    const KeyedPingType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

 DDS::ReturnCode_t
KeyedPingTypeDataWriter_impl::writedispose_w_timestamp(
    const KeyedPingType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t 
KeyedPingTypeDataWriter_impl::get_key_value(
    KeyedPingType & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
KeyedPingTypeDataWriter_impl::lookup_instance(
	const KeyedPingType & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS KeyedPingType DataReader_impl Object Body

 KeyedPingTypeDataReader_impl::KeyedPingTypeDataReader_impl (
    gapi_dataReader handle
) : DDS::DataReader_impl(handle)
{
    // Parent constructor takes care of everything.
}

 KeyedPingTypeDataReader_impl::~KeyedPingTypeDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


 DDS::ReturnCode_t
KeyedPingTypeDataReader_impl::read(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
KeyedPingTypeDataReader_impl::take(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
KeyedPingTypeDataReader_impl::read_w_condition(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

 DDS::ReturnCode_t
KeyedPingTypeDataReader_impl::take_w_condition(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
KeyedPingTypeDataReader_impl::read_next_sample(
    KeyedPingType & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t 
KeyedPingTypeDataReader_impl::take_next_sample(
    KeyedPingType & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t
KeyedPingTypeDataReader_impl::read_instance(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
KeyedPingTypeDataReader_impl::take_instance(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
KeyedPingTypeDataReader_impl::read_next_instance(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
KeyedPingTypeDataReader_impl::take_next_instance(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


 DDS::ReturnCode_t 
KeyedPingTypeDataReader_impl::read_next_instance_w_condition(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
KeyedPingTypeDataReader_impl::take_next_instance_w_condition(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t
KeyedPingTypeDataReader_impl::return_loan(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status = DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() && 
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReader_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        KeyedPingTypeSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = DDS::RETCODE_OK;
                    } else {
                        status = DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


 DDS::ReturnCode_t 
KeyedPingTypeDataReader_impl::get_key_value(
    KeyedPingType & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
KeyedPingTypeDataReader_impl::lookup_instance(
    const KeyedPingType & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

 DDS::ReturnCode_t 
KeyedPingTypeDataReader_impl::check_preconditions(
    KeyedPingTypeSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    DDS::Long max_samples)
{
    DDS::ReturnCode_t status = DDS::RETCODE_PRECONDITION_NOT_MET;
    
    if ( received_data.length() == info_seq.length() &&
         received_data.maximum() == info_seq.maximum() &&
         received_data.release() == info_seq.release() ) {
        if ( received_data.maximum() == 0 || received_data.release() ) {
            if (received_data.maximum() == 0 ||
		max_samples <= static_cast<DDS::Long>(received_data.maximum()) ||
		max_samples == DDS::LENGTH_UNLIMITED ) {
                status = DDS::RETCODE_OK;
            }
        }
    }
    return status;
}
const char * PingTypeTypeSupport::metaDescriptor = "<MetaData version=\"1.0.0\"><Struct name=\"PingType\"><Member name=\"number\"><Long/></Member><Member name=\"counter\"><Long/></Member><Member name=\"vendor\"><String length=\"32\"/></Member></Struct></MetaData>";
const char * KeyedPingTypeTypeSupport::metaDescriptor = "<MetaData version=\"1.0.0\"><Struct name=\"KeyedPingType\"><Member name=\"number\"><Long/></Member><Member name=\"counter\"><Long/></Member><Member name=\"vendor\"><String length=\"32\"/></Member></Struct></MetaData>";
