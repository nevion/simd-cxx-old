#include "gapi.h"
#include "gapi_loanRegistry.h"
#include "helloSplDcps.h"
#include "helloDcps_impl.h"
#include "ccpp_DataReader_impl.h"


extern c_bool
__swatch_hello__copyIn(
    c_base base,
    struct swatch::hello *from,
    struct _swatch_hello *to);

extern void
__swatch_hello__copyOut(
    void *_from,
    void *_to);

// DDS swatch::hello TypeSupportFactory Object Body

 DDS::DataWriter_ptr 
swatch::helloTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new swatch::helloDataWriter_impl(handle);
}

 DDS::DataReader_ptr 
swatch::helloTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new swatch::helloDataReader_impl (handle);
}

// DDS swatch::hello TypeSupport Object Body

 swatch::helloTypeSupport::helloTypeSupport(void) :
    TypeSupport_impl(
        __swatch_hello__name(),
        __swatch_hello__keys(),
        swatch::helloTypeSupport::metaDescriptor,
        (gapi_copyIn) __swatch_hello__copyIn,
        (gapi_copyOut) __swatch_hello__copyOut,
        (gapi_readerCopy) DDS::ccpp_DataReaderCopy<swatch::helloSeq, swatch::hello>,
        new  swatch::helloTypeSupportFactory())
{
    // Parent constructor takes care of everything.
}

 swatch::helloTypeSupport::~helloTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

 DDS::ReturnCode_t
swatch::helloTypeSupport::register_type(
    DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

 char *
swatch::helloTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS swatch::hello DataWriter_impl Object Body

 swatch::helloDataWriter_impl::helloDataWriter_impl (
    gapi_dataWriter handle
) : DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

 swatch::helloDataWriter_impl::~helloDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

 DDS::InstanceHandle_t
swatch::helloDataWriter_impl::register_instance(
    const swatch::hello & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

 DDS::InstanceHandle_t 
swatch::helloDataWriter_impl::register_instance_w_timestamp(
    const hello & instance_data,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

 DDS::ReturnCode_t
swatch::helloDataWriter_impl::unregister_instance(
    const swatch::hello & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

 DDS::ReturnCode_t 
swatch::helloDataWriter_impl::unregister_instance_w_timestamp(
    const hello & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
swatch::helloDataWriter_impl::write(
    const swatch::hello & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

 DDS::ReturnCode_t
swatch::helloDataWriter_impl::write_w_timestamp(
    const hello & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
swatch::helloDataWriter_impl::dispose(
    const swatch::hello & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

 DDS::ReturnCode_t 
swatch::helloDataWriter_impl::dispose_w_timestamp(
    const hello & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
swatch::helloDataWriter_impl::writedispose(
    const swatch::hello & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

 DDS::ReturnCode_t
swatch::helloDataWriter_impl::writedispose_w_timestamp(
    const hello & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t 
swatch::helloDataWriter_impl::get_key_value(
    hello & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
swatch::helloDataWriter_impl::lookup_instance(
	const swatch::hello & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS swatch::hello DataReader_impl Object Body

 swatch::helloDataReader_impl::helloDataReader_impl (
    gapi_dataReader handle
) : DDS::DataReader_impl(handle)
{
    // Parent constructor takes care of everything.
}

 swatch::helloDataReader_impl::~helloDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


 DDS::ReturnCode_t
swatch::helloDataReader_impl::read(
    swatch::helloSeq & received_data,
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
swatch::helloDataReader_impl::take(
    swatch::helloSeq & received_data,
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
swatch::helloDataReader_impl::read_w_condition(
    swatch::helloSeq & received_data,
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
swatch::helloDataReader_impl::take_w_condition(
    swatch::helloSeq & received_data,
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
swatch::helloDataReader_impl::read_next_sample(
    swatch::hello & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t 
swatch::helloDataReader_impl::take_next_sample(
    swatch::hello & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t
swatch::helloDataReader_impl::read_instance(
    swatch::helloSeq & received_data,
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
swatch::helloDataReader_impl::take_instance(
    swatch::helloSeq & received_data,
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
swatch::helloDataReader_impl::read_next_instance(
    swatch::helloSeq & received_data,
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
swatch::helloDataReader_impl::take_next_instance(
    swatch::helloSeq & received_data,
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
swatch::helloDataReader_impl::read_next_instance_w_condition(
    swatch::helloSeq & received_data,
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
swatch::helloDataReader_impl::take_next_instance_w_condition(
    swatch::helloSeq & received_data,
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
swatch::helloDataReader_impl::return_loan(
    swatch::helloSeq & received_data,
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
                        swatch::helloSeq::freebuf( received_data.get_buffer(false) );
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
swatch::helloDataReader_impl::get_key_value(
    swatch::hello & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
swatch::helloDataReader_impl::lookup_instance(
    const swatch::hello & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

 DDS::ReturnCode_t 
swatch::helloDataReader_impl::check_preconditions(
    swatch::helloSeq & received_data,
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
const char * ::swatch::helloTypeSupport::metaDescriptor = "<MetaData version=\"1.0.0\"><Module name=\"swatch\"><Struct name=\"hello\"><Member name=\"name\"><String length=\"256\"/></Member></Struct></Module></MetaData>";
