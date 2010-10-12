#ifndef PINGSPLTYPES_H
#define PINGSPLTYPES_H

#include "ccpp_ping.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __PingType__load (c_base base);
extern char * __PingType__keys (void);
extern char * __PingType__name (void);
struct _PingType ;
extern  c_bool __PingType__copyIn(c_base base, struct PingType *from, struct _PingType *to);
extern  void __PingType__copyOut(void *_from, void *_to);
struct _PingType {
    c_long number;
    c_long counter;
    c_string vendor;
};

#endif
