#include "ishapeSplDcps.h"
#include "ccpp_ishape.h"

char *
__ShapeType__name(void)
{
    return CORBA::string_dup("ShapeType");
}

char *
__ShapeType__keys(void)
{
    return CORBA::string_dup("color");
}

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>

c_bool
__ShapeType__copyIn(
    c_base base,
    struct ShapeType *from,
    struct _ShapeType *to)
{
    c_bool result = TRUE;

    to->x = (c_long)from->x;
    to->y = (c_long)from->y;
    to->shapesize = (c_long)from->shapesize;
#ifdef OSPL_BOUNDS_CHECK
    if(from->color){
        to->color = c_stringNew(base, from->color);
    } else {
        result = FALSE;
    }
#else
    to->color = c_stringNew(base, from->color);
#endif
    return result;
}

void
__ShapeType__copyOut(
    void *_from,
    void *_to)
{
    struct _ShapeType *from = (struct _ShapeType *)_from;
    struct ShapeType *to = (struct ShapeType *)_to;
    to->x = (::DDS::Long)from->x;
    to->y = (::DDS::Long)from->y;
    to->shapesize = (::DDS::Long)from->shapesize;
    to->color = CORBA::string_dup(from->color);
}

