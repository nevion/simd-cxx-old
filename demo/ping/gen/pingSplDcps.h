#ifndef PINGSPLTYPES_H
#define PINGSPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __PingType__load (c_base base);
extern char * __PingType__keys (void);
extern char * __PingType__name (void);
struct _PingType {
    c_long number;
    c_long counter;
    c_string vendor;
};

extern c_metaObject __KeyedPingType__load (c_base base);
extern char * __KeyedPingType__keys (void);
extern char * __KeyedPingType__name (void);
struct _KeyedPingType {
    c_long number;
    c_long counter;
    c_string vendor;
};

#endif
