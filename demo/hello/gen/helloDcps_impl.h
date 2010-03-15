#ifndef HELLODCPS_IMPL_H_
#define HELLODCPS_IMPL_H_

#include "ccpp.h"
#include "ccpp_hello.h"
#include "ccpp_TypeSupport_impl.h"
#include "ccpp_DataWriter_impl.h"
#include "ccpp_DataReader_impl.h"


namespace swatch {

    class  helloTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
    {
    public:
        helloTypeSupportFactory() {}
        virtual ~helloTypeSupportFactory() {}
    private:
        ::DDS::DataWriter_ptr 
        create_datawriter (gapi_dataWriter handle);
    
        ::DDS::DataReader_ptr 
        create_datareader (gapi_dataReader handle);
    };
    
    class  helloTypeSupport : public virtual helloTypeSupportInterface,
                                   public ::DDS::TypeSupport_impl
    {
    public:
        virtual ::DDS::ReturnCode_t register_type(
            ::DDS::DomainParticipant_ptr participant,
            const char * type_name) THROW_ORB_EXCEPTIONS;
    
        virtual char * get_type_name() THROW_ORB_EXCEPTIONS;    
    
        helloTypeSupport (void);
        virtual ~helloTypeSupport (void);
    
    private:
        helloTypeSupport (const helloTypeSupport &);
        void operator= (const helloTypeSupport &);
    
        static const char *metaDescriptor;
    };
    
    typedef helloTypeSupportInterface_var helloTypeSupport_var;
    typedef helloTypeSupportInterface_ptr helloTypeSupport_ptr;
    
    class  helloDataWriter_impl : public virtual helloDataWriter,
                                        public ::DDS::DataWriter_impl
    {
    public:
    
        virtual ::DDS::InstanceHandle_t register_instance(
            const hello & instance_data) THROW_ORB_EXCEPTIONS;
            
        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
            const hello & instance_data,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
            
        virtual ::DDS::ReturnCode_t unregister_instance(
            const hello & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
            const hello & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write(
            const hello & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write_w_timestamp(
            const hello & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose(
            const hello & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose_w_timestamp(
            const hello & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose(
            const hello & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
            const hello & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            hello & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const hello & instance_data) THROW_ORB_EXCEPTIONS;
    
    
        helloDataWriter_impl (
            gapi_dataWriter handle
        );
    
        virtual ~helloDataWriter_impl (void);
    
    private:
        helloDataWriter_impl(const helloDataWriter_impl &);
        void operator= (const helloDataWriter &);
    };
    
    class  helloDataReader_impl : public virtual helloDataReader,
                                        public ::DDS::DataReader_impl
    {
    public:
        virtual ::DDS::ReturnCode_t read(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_w_condition(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_w_condition(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            hello & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            hello & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_instance(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_instance(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_next_instance(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t get_key_value(
            hello & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const hello & instance) THROW_ORB_EXCEPTIONS;
    
        helloDataReader_impl (
            gapi_dataReader handle
        );
    
        virtual ~helloDataReader_impl(void);
    
    private:
        helloDataReader_impl(const helloDataReader &);
        void operator= (const helloDataReader &);
    
        ::DDS::ReturnCode_t check_preconditions(
            helloSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            DDS::Long max_samples
        );
    };
    
}

#endif
