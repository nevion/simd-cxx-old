#ifndef PINGDCPS_H
#define PINGDCPS_H

#include <sacpp_mapping.h>


struct PingType {
    DDS::Long number;
    DDS::Long counter;
    DDS::String_mgr vendor;
};
typedef DDS_DCPSStruct_var<PingType> PingType_var;
typedef DDS_DCPSStruct_out<PingType> PingType_out;

struct KeyedPingType {
    DDS::Long number;
    DDS::Long counter;
    DDS::String_mgr vendor;
};
typedef DDS_DCPSStruct_var<KeyedPingType> KeyedPingType_var;
typedef DDS_DCPSStruct_out<KeyedPingType> KeyedPingType_out;

#endif
