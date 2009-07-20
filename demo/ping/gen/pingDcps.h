#ifndef _PINGDCPS_H_
#define _PINGDCPS_H_


#include "sacpp_mapping.h"
#include "dds_dcps.h"
#include "ping.h"

struct PingType;

class  PingTypeTypeSupportInterface;

typedef PingTypeTypeSupportInterface * PingTypeTypeSupportInterface_ptr;
typedef DDS_DCPSInterface_var <PingTypeTypeSupportInterface> PingTypeTypeSupportInterface_var;
typedef DDS_DCPSInterface_out <PingTypeTypeSupportInterface> PingTypeTypeSupportInterface_out;

class  PingTypeDataWriter;

typedef PingTypeDataWriter * PingTypeDataWriter_ptr;
typedef DDS_DCPSInterface_var <PingTypeDataWriter> PingTypeDataWriter_var;
typedef DDS_DCPSInterface_out <PingTypeDataWriter> PingTypeDataWriter_out;

class  PingTypeDataReader;

typedef PingTypeDataReader * PingTypeDataReader_ptr;
typedef DDS_DCPSInterface_var <PingTypeDataReader> PingTypeDataReader_var;
typedef DDS_DCPSInterface_out <PingTypeDataReader> PingTypeDataReader_out;

typedef DDS_DCPSUFLSeq <PingType> PingTypeSeq;
typedef DDS_DCPSSequence_var <PingTypeSeq> PingTypeSeq_var;
typedef DDS_DCPSSequence_out <PingTypeSeq> PingTypeSeq_out;
class  PingTypeTypeSupportInterface
:
  virtual public DDS::TypeSupport
{ 
public:
   typedef PingTypeTypeSupportInterface_ptr _ptr_type;
   typedef PingTypeTypeSupportInterface_var _var_type;

   static PingTypeTypeSupportInterface_ptr _duplicate (PingTypeTypeSupportInterface_ptr obj);
   DDS::Boolean _local_is_a (const char * id);

   static PingTypeTypeSupportInterface_ptr _narrow (DDS::Object_ptr obj);
   static PingTypeTypeSupportInterface_ptr _unchecked_narrow (DDS::Object_ptr obj);
   static PingTypeTypeSupportInterface_ptr _nil () { return NULL; }
   static const char * _local_id;
   PingTypeTypeSupportInterface_ptr _this () { return this; }


protected:
   PingTypeTypeSupportInterface () {};
   ~PingTypeTypeSupportInterface () {};
private:
   PingTypeTypeSupportInterface (const PingTypeTypeSupportInterface &) {};
   PingTypeTypeSupportInterface & operator = (const PingTypeTypeSupportInterface &);
};


class  PingTypeDataWriter
:
   virtual public DDS::DataWriter
{ 
public:
   typedef PingTypeDataWriter_ptr _ptr_type;
   typedef PingTypeDataWriter_var _var_type;

   static PingTypeDataWriter_ptr _duplicate (PingTypeDataWriter_ptr obj);
   DDS::Boolean _local_is_a (const char * id);

   static PingTypeDataWriter_ptr _narrow (DDS::Object_ptr obj);
   static PingTypeDataWriter_ptr _unchecked_narrow (DDS::Object_ptr obj);
   static PingTypeDataWriter_ptr _nil () { return NULL; }
   static const char * _local_id;
   PingTypeDataWriter_ptr _this () { return this; }

   virtual DDS::InstanceHandle_t register_instance (const PingType& instance_data) = 0;
   virtual DDS::InstanceHandle_t register_instance_w_timestamp (const PingType& instance_data, const DDS::Time_t& source_timestamp) = 0;
   virtual DDS::ReturnCode_t unregister_instance (const PingType& instance_data, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::ReturnCode_t unregister_instance_w_timestamp (const PingType& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
   virtual DDS::ReturnCode_t write (const PingType& instance_data, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::ReturnCode_t write_w_timestamp (const PingType& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
   virtual DDS::ReturnCode_t dispose (const PingType& instance_data, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::ReturnCode_t dispose_w_timestamp (const PingType& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
   virtual DDS::ReturnCode_t writedispose (const PingType& instance_data, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::ReturnCode_t writedispose_w_timestamp (const PingType& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
   virtual DDS::ReturnCode_t get_key_value (PingType& key_holder, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::InstanceHandle_t lookup_instance (const PingType& instance_data) = 0;

protected:
   PingTypeDataWriter () {};
   ~PingTypeDataWriter () {};
private:
   PingTypeDataWriter (const PingTypeDataWriter &) {};
   PingTypeDataWriter & operator = (const PingTypeDataWriter &);
};


class  PingTypeDataReader
:
   virtual public DDS::DataReader
{ 
public:
   typedef PingTypeDataReader_ptr _ptr_type;
   typedef PingTypeDataReader_var _var_type;

   static PingTypeDataReader_ptr _duplicate (PingTypeDataReader_ptr obj);
   DDS::Boolean _local_is_a (const char * id);

   static PingTypeDataReader_ptr _narrow (DDS::Object_ptr obj);
   static PingTypeDataReader_ptr _unchecked_narrow (DDS::Object_ptr obj);
   static PingTypeDataReader_ptr _nil () { return NULL; }
   static const char * _local_id;
   PingTypeDataReader_ptr _this () { return this; }

   virtual DDS::ReturnCode_t read (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t take (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t read_w_condition (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
   virtual DDS::ReturnCode_t take_w_condition (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
   virtual DDS::ReturnCode_t read_next_sample (PingType& received_data, DDS::SampleInfo& sample_info) = 0;
   virtual DDS::ReturnCode_t take_next_sample (PingType& received_data, DDS::SampleInfo& sample_info) = 0;
   virtual DDS::ReturnCode_t read_instance (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t take_instance (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t read_next_instance (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t take_next_instance (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t read_next_instance_w_condition (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
   virtual DDS::ReturnCode_t take_next_instance_w_condition (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
   virtual DDS::ReturnCode_t return_loan (PingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
   virtual DDS::ReturnCode_t get_key_value (PingType& key_holder, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::InstanceHandle_t lookup_instance (const PingType& instance) = 0;

protected:
   PingTypeDataReader () {};
   ~PingTypeDataReader () {};
private:
   PingTypeDataReader (const PingTypeDataReader &) {};
   PingTypeDataReader & operator = (const PingTypeDataReader &);
};

struct KeyedPingType;

class  KeyedPingTypeTypeSupportInterface;

typedef KeyedPingTypeTypeSupportInterface * KeyedPingTypeTypeSupportInterface_ptr;
typedef DDS_DCPSInterface_var <KeyedPingTypeTypeSupportInterface> KeyedPingTypeTypeSupportInterface_var;
typedef DDS_DCPSInterface_out <KeyedPingTypeTypeSupportInterface> KeyedPingTypeTypeSupportInterface_out;

class  KeyedPingTypeDataWriter;

typedef KeyedPingTypeDataWriter * KeyedPingTypeDataWriter_ptr;
typedef DDS_DCPSInterface_var <KeyedPingTypeDataWriter> KeyedPingTypeDataWriter_var;
typedef DDS_DCPSInterface_out <KeyedPingTypeDataWriter> KeyedPingTypeDataWriter_out;

class  KeyedPingTypeDataReader;

typedef KeyedPingTypeDataReader * KeyedPingTypeDataReader_ptr;
typedef DDS_DCPSInterface_var <KeyedPingTypeDataReader> KeyedPingTypeDataReader_var;
typedef DDS_DCPSInterface_out <KeyedPingTypeDataReader> KeyedPingTypeDataReader_out;

typedef DDS_DCPSUFLSeq <KeyedPingType> KeyedPingTypeSeq;
typedef DDS_DCPSSequence_var <KeyedPingTypeSeq> KeyedPingTypeSeq_var;
typedef DDS_DCPSSequence_out <KeyedPingTypeSeq> KeyedPingTypeSeq_out;
class  KeyedPingTypeTypeSupportInterface
:
  virtual public DDS::TypeSupport
{ 
public:
   typedef KeyedPingTypeTypeSupportInterface_ptr _ptr_type;
   typedef KeyedPingTypeTypeSupportInterface_var _var_type;

   static KeyedPingTypeTypeSupportInterface_ptr _duplicate (KeyedPingTypeTypeSupportInterface_ptr obj);
   DDS::Boolean _local_is_a (const char * id);

   static KeyedPingTypeTypeSupportInterface_ptr _narrow (DDS::Object_ptr obj);
   static KeyedPingTypeTypeSupportInterface_ptr _unchecked_narrow (DDS::Object_ptr obj);
   static KeyedPingTypeTypeSupportInterface_ptr _nil () { return NULL; }
   static const char * _local_id;
   KeyedPingTypeTypeSupportInterface_ptr _this () { return this; }


protected:
   KeyedPingTypeTypeSupportInterface () {};
   ~KeyedPingTypeTypeSupportInterface () {};
private:
   KeyedPingTypeTypeSupportInterface (const KeyedPingTypeTypeSupportInterface &) {};
   KeyedPingTypeTypeSupportInterface & operator = (const KeyedPingTypeTypeSupportInterface &);
};


class  KeyedPingTypeDataWriter
:
   virtual public DDS::DataWriter
{ 
public:
   typedef KeyedPingTypeDataWriter_ptr _ptr_type;
   typedef KeyedPingTypeDataWriter_var _var_type;

   static KeyedPingTypeDataWriter_ptr _duplicate (KeyedPingTypeDataWriter_ptr obj);
   DDS::Boolean _local_is_a (const char * id);

   static KeyedPingTypeDataWriter_ptr _narrow (DDS::Object_ptr obj);
   static KeyedPingTypeDataWriter_ptr _unchecked_narrow (DDS::Object_ptr obj);
   static KeyedPingTypeDataWriter_ptr _nil () { return NULL; }
   static const char * _local_id;
   KeyedPingTypeDataWriter_ptr _this () { return this; }

   virtual DDS::InstanceHandle_t register_instance (const KeyedPingType& instance_data) = 0;
   virtual DDS::InstanceHandle_t register_instance_w_timestamp (const KeyedPingType& instance_data, const DDS::Time_t& source_timestamp) = 0;
   virtual DDS::ReturnCode_t unregister_instance (const KeyedPingType& instance_data, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::ReturnCode_t unregister_instance_w_timestamp (const KeyedPingType& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
   virtual DDS::ReturnCode_t write (const KeyedPingType& instance_data, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::ReturnCode_t write_w_timestamp (const KeyedPingType& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
   virtual DDS::ReturnCode_t dispose (const KeyedPingType& instance_data, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::ReturnCode_t dispose_w_timestamp (const KeyedPingType& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
   virtual DDS::ReturnCode_t writedispose (const KeyedPingType& instance_data, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::ReturnCode_t writedispose_w_timestamp (const KeyedPingType& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
   virtual DDS::ReturnCode_t get_key_value (KeyedPingType& key_holder, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::InstanceHandle_t lookup_instance (const KeyedPingType& instance_data) = 0;

protected:
   KeyedPingTypeDataWriter () {};
   ~KeyedPingTypeDataWriter () {};
private:
   KeyedPingTypeDataWriter (const KeyedPingTypeDataWriter &) {};
   KeyedPingTypeDataWriter & operator = (const KeyedPingTypeDataWriter &);
};


class  KeyedPingTypeDataReader
:
   virtual public DDS::DataReader
{ 
public:
   typedef KeyedPingTypeDataReader_ptr _ptr_type;
   typedef KeyedPingTypeDataReader_var _var_type;

   static KeyedPingTypeDataReader_ptr _duplicate (KeyedPingTypeDataReader_ptr obj);
   DDS::Boolean _local_is_a (const char * id);

   static KeyedPingTypeDataReader_ptr _narrow (DDS::Object_ptr obj);
   static KeyedPingTypeDataReader_ptr _unchecked_narrow (DDS::Object_ptr obj);
   static KeyedPingTypeDataReader_ptr _nil () { return NULL; }
   static const char * _local_id;
   KeyedPingTypeDataReader_ptr _this () { return this; }

   virtual DDS::ReturnCode_t read (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t take (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t read_w_condition (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
   virtual DDS::ReturnCode_t take_w_condition (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
   virtual DDS::ReturnCode_t read_next_sample (KeyedPingType& received_data, DDS::SampleInfo& sample_info) = 0;
   virtual DDS::ReturnCode_t take_next_sample (KeyedPingType& received_data, DDS::SampleInfo& sample_info) = 0;
   virtual DDS::ReturnCode_t read_instance (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t take_instance (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t read_next_instance (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t take_next_instance (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
   virtual DDS::ReturnCode_t read_next_instance_w_condition (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
   virtual DDS::ReturnCode_t take_next_instance_w_condition (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
   virtual DDS::ReturnCode_t return_loan (KeyedPingTypeSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
   virtual DDS::ReturnCode_t get_key_value (KeyedPingType& key_holder, DDS::InstanceHandle_t handle) = 0;
   virtual DDS::InstanceHandle_t lookup_instance (const KeyedPingType& instance) = 0;

protected:
   KeyedPingTypeDataReader () {};
   ~KeyedPingTypeDataReader () {};
private:
   KeyedPingTypeDataReader (const KeyedPingTypeDataReader &) {};
   KeyedPingTypeDataReader & operator = (const KeyedPingTypeDataReader &);
};

#endif
