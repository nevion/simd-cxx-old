#ifndef AC_SIMD_DDS_TYPES_HPP
#define AC_SIMD_DDS_TYPES_HPP


namespace dds {
  const std::string& retcode2string(::DDS::ReturnCode_t rc);
  typedef ::DDS::SampleInfo SampleInfo;
  typedef ::DDS::SampleInfoSeq SampleInfoSeq;
  typedef ::DDS::Duration_t Duration_t;
  typedef ::DDS::Time_t Time_t;
  typedef DDS::ReturnCode_t ReturnCode_t; 
  typedef DDS::SampleStateMask SampleStateMask;
  typedef DDS::ViewStateMask ViewStateMask;
  typedef DDS::InstanceStateMask InstanceStateMask;
}

#endif /* AC_SIMD_DDS_TYPES_HPP */
