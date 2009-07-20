#include "pingSplDcps.h"
#include "ccpp_ping.h"

char *
__PingType__name(void)
{
    return CORBA::string_dup("PingType");
}

char *
__PingType__keys(void)
{
    return CORBA::string_dup("");
}

char *
__KeyedPingType__name(void)
{
    return CORBA::string_dup("KeyedPingType");
}

char *
__KeyedPingType__keys(void)
{
    return CORBA::string_dup("vendor");
}

#include <v_kernel.h>
#include <v_topic.h>
#include <string.h>

c_bool
__PingType__copyIn(
    c_base base,
    struct PingType *from,
    struct _PingType *to)
{
    c_bool result = TRUE;

    to->number = (c_long)from->number;
    to->counter = (c_long)from->counter;
#ifdef OSPL_BOUNDS_CHECK
    if(from->vendor){
        if(((unsigned int)strlen(from->vendor)) <= 32){
            to->vendor = c_stringNew(base, from->vendor);
        } else {
            result = FALSE;
        }
    } else {
        result = FALSE;
    }
#else
    to->vendor = c_stringNew(base, from->vendor);
#endif
    return result;
}

c_bool
__KeyedPingType__copyIn(
    c_base base,
    struct KeyedPingType *from,
    struct _KeyedPingType *to)
{
    c_bool result = TRUE;

    to->number = (c_long)from->number;
    to->counter = (c_long)from->counter;
#ifdef OSPL_BOUNDS_CHECK
    if(from->vendor){
        if(((unsigned int)strlen(from->vendor)) <= 32){
            to->vendor = c_stringNew(base, from->vendor);
        } else {
            result = FALSE;
        }
    } else {
        result = FALSE;
    }
#else
    to->vendor = c_stringNew(base, from->vendor);
#endif
    return result;
}

void
__PingType__copyOut(
    void *_from,
    void *_to)
{
    struct _PingType *from = (struct _PingType *)_from;
    struct PingType *to = (struct PingType *)_to;
    to->number = (DDS::Long)from->number;
    to->counter = (DDS::Long)from->counter;
    to->vendor = CORBA::string_dup(from->vendor);
}

void
__KeyedPingType__copyOut(
    void *_from,
    void *_to)
{
    struct _KeyedPingType *from = (struct _KeyedPingType *)_from;
    struct KeyedPingType *to = (struct KeyedPingType *)_to;
    to->number = (DDS::Long)from->number;
    to->counter = (DDS::Long)from->counter;
    to->vendor = CORBA::string_dup(from->vendor);
}

