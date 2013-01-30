#ifndef LSA_DEMO_TRAITS_HPP_
#define LSA_DEMO_TRAITS_HPP_

#include "gen/ccpp_DIS.h"
#include <dds/runtime.hpp>
#include <dds/topic.hpp>
#include <dds/writer.hpp>
#include <dds/reader.hpp>
#include <dds/traits.hpp>


REGISTER_TOPIC_TRAITS(lsa::dis::EntityState);

#endif /* LSA_DEMO_TRAITS_HPP_ */
