#ifndef ISHAPESPLTYPES_H
#define ISHAPESPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include "ccpp_ishape.h"


extern c_metaObject __ShapeType__load (c_base base);
extern char * __ShapeType__keys (void);
extern char * __ShapeType__name (void);
struct _ShapeType ;
extern  c_bool __ShapeType__copyIn(c_base base, struct ShapeType *from, struct _ShapeType *to);
extern  void __ShapeType__copyOut(void *_from, void *_to);
struct _ShapeType {
    c_long x;
    c_long y;
    c_long shapesize;
    c_string color;
};

#endif
