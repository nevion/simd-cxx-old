#include <dds/dds.hpp>

const std::string&
dds::retcode2string(::DDS::ReturnCode_t rc) 
{
  static const short RETCODES_N = 13;
  static std::string retcodeStrings[RETCODES_N] = {
    "DDS_RETCODE_OK",
    "DDS_RETCODE_ERROR",
    "DDS_RETCODE_UNSUPPORTED",
    "DDS_RETCODE_BAD_PARAMETER",
    "DDS_RETCODE_PRECONDITION_NOT_MET",
    "DDS_RETCODE_OUT_OF_RESOURCES",
    "DDS_RETCODE_NOT_ENABLED",
    "DDS_RETCODE_IMMUTABLE_POLICY",
    "DDS_RETCODE_INCONSISTENT_POLICY",
    "DDS_RETCODE_ALREADY_DELETED",
    "DDS_RETCODE_TIMEOUT",
    "DDS_RETCODE_NO_DATA",
    "DDS_RETCODE_ILLEGAL_OPERATION"
  };
  
  ::dds::Assert::precondition(rc < RETCODES_N , "Bad ReturnCode_t");
  return retcodeStrings[rc];
}
