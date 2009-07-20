#ifndef HELLODCPS_H
#define HELLODCPS_H

#include <sacpp_mapping.h>


namespace swatch {
    struct hello {
        DDS::String_mgr name;
    };
    typedef DDS_DCPSStruct_var<hello> hello_var;
    typedef hello &hello_out;

}
#endif
