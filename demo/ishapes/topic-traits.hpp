/* 
 * File:   topic-traits.hpp
 * Author: corsaro
 *
 * Created on July 13, 2009, 8:32 AM
 */

#ifndef _TOPIC_TRAITS_HPP
#define	_TOPIC_TRAITS_HPP

#include "config.hpp"

#if (ISHAPES_B2_DEMO == 1)
// -- Shaped Include
#include <gen/ccpp_ishape.h>

  REGISTER_TOPIC_TRAITS(org::opensplice::demo::ShapeType);
  using namespace org::opensplice::demo;
#else
#include <gen/ccpp_ishapeiop.h>
  REGISTER_TOPIC_TRAITS(ShapeType);
#endif
#endif	/* _TOPIC_TRAITS_HPP */

