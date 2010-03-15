#ifndef HELLOSPLTYPES_H
#define HELLOSPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include "ccpp_hello.h"


extern c_metaObject __hello_swatch__load (c_base base);

extern c_metaObject __swatch_hello__load (c_base base);
extern char * __swatch_hello__keys (void);
extern char * __swatch_hello__name (void);
struct _swatch_hello ;
extern  c_bool __swatch_hello__copyIn(c_base base, struct swatch::hello *from, struct _swatch_hello *to);
extern  void __swatch_hello__copyOut(void *_from, void *_to);
struct _swatch_hello {
    c_string name;
};

#endif
