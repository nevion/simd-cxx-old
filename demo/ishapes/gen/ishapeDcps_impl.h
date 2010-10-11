#ifndef ISHAPEDCPS_IMPL_H_
#define ISHAPEDCPS_IMPL_H_

#include "ccpp.h"
#include "ccpp_ishape.h"
#include "ccpp_TypeSupport_impl.h"
#include "ccpp_DataWriter_impl.h"
#include "ccpp_DataReader_impl.h"
#include "ccpp_DataReaderView_impl.h"


class  ShapeTypeTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
{
public:
    ShapeTypeTypeSupportFactory() {}
    virtual ~ShapeTypeTypeSupportFactory() {}
private:
    ::DDS::DataWriter_ptr 
    create_datawriter (gapi_dataWriter handle);

    ::DDS::DataReader_ptr 
    create_datareader (gapi_dataReader handle);

    ::DDS::DataReaderView_ptr 
    create_view (gapi_dataReaderView handle);
};

class  ShapeTypeTypeSupport : public virtual ShapeTypeTypeSupportInterface,
                               public ::DDS::TypeSupport_impl
{
public:
    virtual ::DDS::ReturnCode_t register_type(
        ::DDS::DomainParticipant_ptr participant,
        const char * type_name) THROW_ORB_EXCEPTIONS;

    virtual char * get_type_name() THROW_ORB_EXCEPTIONS;    

    ShapeTypeTypeSupport (void);
    virtual ~ShapeTypeTypeSupport (void);

private:
    ShapeTypeTypeSupport (const ShapeTypeTypeSupport &);
    void operator= (const ShapeTypeTypeSupport &);

    static const char *metaDescriptor;
};

typedef ShapeTypeTypeSupportInterface_var ShapeTypeTypeSupport_var;
typedef ShapeTypeTypeSupportInterface_ptr ShapeTypeTypeSupport_ptr;

class  ShapeTypeDataWriter_impl : public virtual ShapeTypeDataWriter,
                                    public ::DDS::DataWriter_impl
{
public:

    virtual ::DDS::InstanceHandle_t register_instance(
        const ShapeType & instance_data) THROW_ORB_EXCEPTIONS;
        
    virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
        const ShapeType & instance_data,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
        
    virtual ::DDS::ReturnCode_t unregister_instance(
        const ShapeType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
        const ShapeType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t write(
        const ShapeType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t write_w_timestamp(
        const ShapeType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t dispose(
        const ShapeType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t dispose_w_timestamp(
        const ShapeType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t writedispose(
        const ShapeType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
        const ShapeType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t get_key_value(
        ShapeType & key_holder,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::InstanceHandle_t lookup_instance(
        const ShapeType & instance_data) THROW_ORB_EXCEPTIONS;


    ShapeTypeDataWriter_impl (
        gapi_dataWriter handle
    );

    virtual ~ShapeTypeDataWriter_impl (void);

private:
    ShapeTypeDataWriter_impl(const ShapeTypeDataWriter_impl &);
    void operator= (const ShapeTypeDataWriter &);
};

class  ShapeTypeDataReader_impl : public virtual ShapeTypeDataReader,
                                    public ::DDS::DataReader_impl
{
    friend class ShapeTypeDataReaderView_impl;
public:
    virtual ::DDS::ReturnCode_t read(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_w_condition(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_w_condition(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t read_next_sample(
        ShapeType & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_sample(
        ShapeType & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_instance(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_instance(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_next_instance(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t return_loan(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t get_key_value(
        ShapeType & key_holder,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::InstanceHandle_t lookup_instance(
        const ShapeType & instance) THROW_ORB_EXCEPTIONS;

    ShapeTypeDataReader_impl (
        gapi_dataReader handle
    );

    virtual ~ShapeTypeDataReader_impl(void);

private:
    ShapeTypeDataReader_impl(const ShapeTypeDataReader &);
    void operator= (const ShapeTypeDataReader &);

    static ::DDS::ReturnCode_t check_preconditions(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples
    );
};

class  ShapeTypeDataReaderView_impl : public virtual ShapeTypeDataReaderView,
                                    public ::DDS::DataReaderView_impl
{
public:
    virtual ::DDS::ReturnCode_t read(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_w_condition(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_w_condition(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t read_next_sample(
        ShapeType & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_sample(
        ShapeType & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_instance(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_instance(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_next_instance(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        CORBA::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t return_loan(
        ShapeTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t get_key_value(
        ShapeType & key_holder,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::InstanceHandle_t lookup_instance(
        const ShapeType & instance) THROW_ORB_EXCEPTIONS;

    ShapeTypeDataReaderView_impl (
        gapi_dataReader handle
    );

    virtual ~ShapeTypeDataReaderView_impl(void);

private:
    ShapeTypeDataReaderView_impl(const ShapeTypeDataReaderView &);
    void operator= (const ShapeTypeDataReaderView &);
};

#endif
