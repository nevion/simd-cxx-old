#ifndef PINGDCPS_IMPL_H_
#define PINGDCPS_IMPL_H_

#include "ccpp.h"
#include "ccpp_ping.h"
#include "ccpp_TypeSupport_impl.h"
#include "ccpp_DataWriter_impl.h"
#include "ccpp_DataReader_impl.h"


class  PingTypeTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
{
public:
    PingTypeTypeSupportFactory() {}
    virtual ~PingTypeTypeSupportFactory() {}
private:
    ::DDS::DataWriter_ptr 
    create_datawriter (gapi_dataWriter handle);

    ::DDS::DataReader_ptr 
    create_datareader (gapi_dataReader handle);
};

class  PingTypeTypeSupport : public virtual PingTypeTypeSupportInterface,
                               public ::DDS::TypeSupport_impl
{
public:
    virtual ::DDS::ReturnCode_t register_type(
        ::DDS::DomainParticipant_ptr participant,
        const char * type_name) THROW_ORB_EXCEPTIONS;

    virtual char * get_type_name() THROW_ORB_EXCEPTIONS;    

    PingTypeTypeSupport (void);
    virtual ~PingTypeTypeSupport (void);

private:
    PingTypeTypeSupport (const PingTypeTypeSupport &);
    void operator= (const PingTypeTypeSupport &);

    static const char *metaDescriptor;
};

typedef PingTypeTypeSupportInterface_var PingTypeTypeSupport_var;
typedef PingTypeTypeSupportInterface_ptr PingTypeTypeSupport_ptr;

class  PingTypeDataWriter_impl : public virtual PingTypeDataWriter,
                                    public ::DDS::DataWriter_impl
{
public:

    virtual ::DDS::InstanceHandle_t register_instance(
        const PingType & instance_data) THROW_ORB_EXCEPTIONS;
        
    virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
        const PingType & instance_data,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
        
    virtual ::DDS::ReturnCode_t unregister_instance(
        const PingType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
        const PingType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t write(
        const PingType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t write_w_timestamp(
        const PingType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t dispose(
        const PingType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t dispose_w_timestamp(
        const PingType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t writedispose(
        const PingType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
        const PingType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t get_key_value(
        PingType & key_holder,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::InstanceHandle_t lookup_instance(
        const PingType & instance_data) THROW_ORB_EXCEPTIONS;


    PingTypeDataWriter_impl (
        gapi_dataWriter handle
    );

    virtual ~PingTypeDataWriter_impl (void);

private:
    PingTypeDataWriter_impl(const PingTypeDataWriter_impl &);
    void operator= (const PingTypeDataWriter &);
};

class  PingTypeDataReader_impl : public virtual PingTypeDataReader,
                                    public ::DDS::DataReader_impl
{
public:
    virtual ::DDS::ReturnCode_t read(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_w_condition(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_w_condition(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t read_next_sample(
        PingType & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_sample(
        PingType & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_instance(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_instance(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_next_instance(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t return_loan(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t get_key_value(
        PingType & key_holder,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::InstanceHandle_t lookup_instance(
        const PingType & instance) THROW_ORB_EXCEPTIONS;

    PingTypeDataReader_impl (
        gapi_dataReader handle
    );

    virtual ~PingTypeDataReader_impl(void);

private:
    PingTypeDataReader_impl(const PingTypeDataReader &);
    void operator= (const PingTypeDataReader &);

    ::DDS::ReturnCode_t check_preconditions(
        PingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples
    );
};

class  KeyedPingTypeTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
{
public:
    KeyedPingTypeTypeSupportFactory() {}
    virtual ~KeyedPingTypeTypeSupportFactory() {}
private:
    ::DDS::DataWriter_ptr 
    create_datawriter (gapi_dataWriter handle);

    ::DDS::DataReader_ptr 
    create_datareader (gapi_dataReader handle);
};

class  KeyedPingTypeTypeSupport : public virtual KeyedPingTypeTypeSupportInterface,
                               public ::DDS::TypeSupport_impl
{
public:
    virtual ::DDS::ReturnCode_t register_type(
        ::DDS::DomainParticipant_ptr participant,
        const char * type_name) THROW_ORB_EXCEPTIONS;

    virtual char * get_type_name() THROW_ORB_EXCEPTIONS;    

    KeyedPingTypeTypeSupport (void);
    virtual ~KeyedPingTypeTypeSupport (void);

private:
    KeyedPingTypeTypeSupport (const KeyedPingTypeTypeSupport &);
    void operator= (const KeyedPingTypeTypeSupport &);

    static const char *metaDescriptor;
};

typedef KeyedPingTypeTypeSupportInterface_var KeyedPingTypeTypeSupport_var;
typedef KeyedPingTypeTypeSupportInterface_ptr KeyedPingTypeTypeSupport_ptr;

class  KeyedPingTypeDataWriter_impl : public virtual KeyedPingTypeDataWriter,
                                    public ::DDS::DataWriter_impl
{
public:

    virtual ::DDS::InstanceHandle_t register_instance(
        const KeyedPingType & instance_data) THROW_ORB_EXCEPTIONS;
        
    virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
        const KeyedPingType & instance_data,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
        
    virtual ::DDS::ReturnCode_t unregister_instance(
        const KeyedPingType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
        const KeyedPingType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t write(
        const KeyedPingType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t write_w_timestamp(
        const KeyedPingType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t dispose(
        const KeyedPingType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t dispose_w_timestamp(
        const KeyedPingType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t writedispose(
        const KeyedPingType & instance_data,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
        const KeyedPingType & instance_data,
        ::DDS::InstanceHandle_t handle,
        const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t get_key_value(
        KeyedPingType & key_holder,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::InstanceHandle_t lookup_instance(
        const KeyedPingType & instance_data) THROW_ORB_EXCEPTIONS;


    KeyedPingTypeDataWriter_impl (
        gapi_dataWriter handle
    );

    virtual ~KeyedPingTypeDataWriter_impl (void);

private:
    KeyedPingTypeDataWriter_impl(const KeyedPingTypeDataWriter_impl &);
    void operator= (const KeyedPingTypeDataWriter &);
};

class  KeyedPingTypeDataReader_impl : public virtual KeyedPingTypeDataReader,
                                    public ::DDS::DataReader_impl
{
public:
    virtual ::DDS::ReturnCode_t read(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_w_condition(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_w_condition(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t read_next_sample(
        KeyedPingType & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_sample(
        KeyedPingType & received_data,
        ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_instance(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_instance(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t take_next_instance(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::SampleStateMask sample_states,
        ::DDS::ViewStateMask view_states,
        ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples,
        ::DDS::InstanceHandle_t a_handle,
        ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;

    virtual ::DDS::ReturnCode_t return_loan(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::ReturnCode_t get_key_value(
        KeyedPingType & key_holder,
        ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
    virtual ::DDS::InstanceHandle_t lookup_instance(
        const KeyedPingType & instance) THROW_ORB_EXCEPTIONS;

    KeyedPingTypeDataReader_impl (
        gapi_dataReader handle
    );

    virtual ~KeyedPingTypeDataReader_impl(void);

private:
    KeyedPingTypeDataReader_impl(const KeyedPingTypeDataReader &);
    void operator= (const KeyedPingTypeDataReader &);

    ::DDS::ReturnCode_t check_preconditions(
        KeyedPingTypeSeq & received_data,
        ::DDS::SampleInfoSeq & info_seq,
        DDS::Long max_samples
    );
};

#endif
