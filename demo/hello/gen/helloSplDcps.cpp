#include "helloSplDcps.h"
#include "ccpp_hello.h"

char *
__swatch_hello__name(void)
{
    return CORBA::string_dup("swatch::hello");
}

char *
__swatch_hello__keys(void)
{
    return CORBA::string_dup("");
}

#include <v_kernel.h>
#include <v_topic.h>
#include <string.h>

c_bool
__swatch_hello__copyIn(
    c_base base,
    struct swatch::hello *from,
    struct _swatch_hello *to)
{
    c_bool result = TRUE;

#ifdef OSPL_BOUNDS_CHECK
    if(from->name){
        if(((unsigned int)strlen(from->name)) <= 256){
            to->name = c_stringNew(base, from->name);
        } else {
            result = FALSE;
        }
    } else {
        result = FALSE;
    }
#else
    to->name = c_stringNew(base, from->name);
#endif
    return result;
}

void
__swatch_hello__copyOut(
    void *_from,
    void *_to)
{
    struct _swatch_hello *from = (struct _swatch_hello *)_from;
    struct swatch::hello *to = (struct swatch::hello *)_to;
    to->name = CORBA::string_dup(from->name);
}

