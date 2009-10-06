#include "gapi.h"
#include "gapi_loanRegistry.h"
#include "ishapeSplDcps.h"
#include "ishapeDcps_impl.h"
#include "ccpp_DataReader_impl.h"


extern c_bool
__ShapeType__copyIn(
    c_base base,
    struct ShapeType *from,
    struct _ShapeType *to);

extern void
__ShapeType__copyOut(
    void *_from,
    void *_to);

// DDS ShapeType TypeSupportFactory Object Body

 DDS::DataWriter_ptr 
ShapeTypeTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new ShapeTypeDataWriter_impl(handle);
}

 DDS::DataReader_ptr 
ShapeTypeTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new ShapeTypeDataReader_impl (handle);
}

// DDS ShapeType TypeSupport Object Body

 ShapeTypeTypeSupport::ShapeTypeTypeSupport(void) :
    TypeSupport_impl(
        __ShapeType__name(),
        __ShapeType__keys(),
        ShapeTypeTypeSupport::metaDescriptor,
        (gapi_copyIn) __ShapeType__copyIn,
        (gapi_copyOut) __ShapeType__copyOut,
        (gapi_readerCopy) DDS::ccpp_DataReaderCopy<ShapeTypeSeq, ShapeType>,
        new  ShapeTypeTypeSupportFactory())
{
    // Parent constructor takes care of everything.
}

 ShapeTypeTypeSupport::~ShapeTypeTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

 DDS::ReturnCode_t
ShapeTypeTypeSupport::register_type(
    DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

 char *
ShapeTypeTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS ShapeType DataWriter_impl Object Body

 ShapeTypeDataWriter_impl::ShapeTypeDataWriter_impl (
    gapi_dataWriter handle
) : DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

 ShapeTypeDataWriter_impl::~ShapeTypeDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

 DDS::InstanceHandle_t
ShapeTypeDataWriter_impl::register_instance(
    const ShapeType & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

 DDS::InstanceHandle_t 
ShapeTypeDataWriter_impl::register_instance_w_timestamp(
    const ShapeType & instance_data,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

 DDS::ReturnCode_t
ShapeTypeDataWriter_impl::unregister_instance(
    const ShapeType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

 DDS::ReturnCode_t 
ShapeTypeDataWriter_impl::unregister_instance_w_timestamp(
    const ShapeType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
ShapeTypeDataWriter_impl::write(
    const ShapeType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

 DDS::ReturnCode_t
ShapeTypeDataWriter_impl::write_w_timestamp(
    const ShapeType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
ShapeTypeDataWriter_impl::dispose(
    const ShapeType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

 DDS::ReturnCode_t 
ShapeTypeDataWriter_impl::dispose_w_timestamp(
    const ShapeType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
ShapeTypeDataWriter_impl::writedispose(
    const ShapeType & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

 DDS::ReturnCode_t
ShapeTypeDataWriter_impl::writedispose_w_timestamp(
    const ShapeType & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t 
ShapeTypeDataWriter_impl::get_key_value(
    ShapeType & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
ShapeTypeDataWriter_impl::lookup_instance(
	const ShapeType & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS ShapeType DataReader_impl Object Body

 ShapeTypeDataReader_impl::ShapeTypeDataReader_impl (
    gapi_dataReader handle
) : DDS::DataReader_impl(handle)
{
    // Parent constructor takes care of everything.
}

 ShapeTypeDataReader_impl::~ShapeTypeDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


 DDS::ReturnCode_t
ShapeTypeDataReader_impl::read(
    ShapeTypeSeq & received_data,
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
ShapeTypeDataReader_impl::take(
    ShapeTypeSeq & received_data,
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
ShapeTypeDataReader_impl::read_w_condition(
    ShapeTypeSeq & received_data,
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
ShapeTypeDataReader_impl::take_w_condition(
    ShapeTypeSeq & received_data,
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
ShapeTypeDataReader_impl::read_next_sample(
    ShapeType & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t 
ShapeTypeDataReader_impl::take_next_sample(
    ShapeType & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t
ShapeTypeDataReader_impl::read_instance(
    ShapeTypeSeq & received_data,
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
ShapeTypeDataReader_impl::take_instance(
    ShapeTypeSeq & received_data,
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
ShapeTypeDataReader_impl::read_next_instance(
    ShapeTypeSeq & received_data,
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
ShapeTypeDataReader_impl::take_next_instance(
    ShapeTypeSeq & received_data,
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
ShapeTypeDataReader_impl::read_next_instance_w_condition(
    ShapeTypeSeq & received_data,
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
ShapeTypeDataReader_impl::take_next_instance_w_condition(
    ShapeTypeSeq & received_data,
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
ShapeTypeDataReader_impl::return_loan(
    ShapeTypeSeq & received_data,
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
                        ShapeTypeSeq::freebuf( received_data.get_buffer(false) );
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
ShapeTypeDataReader_impl::get_key_value(
    ShapeType & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
ShapeTypeDataReader_impl::lookup_instance(
    const ShapeType & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

 DDS::ReturnCode_t 
ShapeTypeDataReader_impl::check_preconditions(
    ShapeTypeSeq & received_data,
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
const char * ShapeTypeTypeSupport::metaDescriptor = "<MetaData version=\"1.0.0\"><Struct name=\"ShapeType\"><Member name=\"x\"><Long/></Member><Member name=\"y\"><Long/></Member><Member name=\"shapesize\"><Long/></Member><Member name=\"color\"><String/></Member></Struct></MetaData>";
