#ifndef AC_SIMD_DDS_TYPES_HPP
#define AC_SIMD_DDS_TYPES_HPP

#include <dds/config.hpp>

namespace dds {
  const std::string& retcode2string(::DDS::ReturnCode_t rc);
  typedef ::DDS::SampleInfo SampleInfo;
  typedef ::DDS::SampleInfoSeq SampleInfoSeq;
  typedef ::DDS::Duration_t Duration_t;
  typedef ::DDS::Time_t Time_t;
  typedef DDS::ReturnCode_t ReturnCode_t; 

  typedef DDS::SampleStateKind SampleStateKind; 
  typedef DDS::SampleStateMask SampleStateMask;

  enum {
    READ_SAMPLE_STATE = DDS::READ_SAMPLE_STATE,
    NOT_READ_SAMPLE_STATE = DDS::NOT_READ_SAMPLE_STATE,
    ANY_SAMPLE_STATE = DDS::ANY_SAMPLE_STATE
  };

  typedef DDS::InstanceStateKind InstanceStateKind;
  typedef DDS::InstanceStateMask InstanceStateMask;
  enum {
    ALIVE_INSTANCE_STATE = DDS::ALIVE_INSTANCE_STATE,
    NOT_ALIVE_DISPOSED_INSTANCE_STATE = DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE,
    NOT_ALIVE_NO_WRITERS_INSTANCE_STATE = DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE
  };

  typedef DDS::ViewStateKind ViewStateKind;
  typedef DDS::ViewStateMask ViewStateMask;
  enum {
    NEW_VIEW_STATE = DDS::NEW_VIEW_STATE,
    NOT_NEW_VIEW_STATE = DDS::NOT_NEW_VIEW_STATE,
    ANY_VIEW_STATE = DDS::ANY_VIEW_STATE
  };
  
  
}

#endif /* AC_SIMD_DDS_TYPES_HPP */
