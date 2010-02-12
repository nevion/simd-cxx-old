#ifndef DEMO_TS_UTIL_HPP_
#define DEMO_TS_UTIL_HPP_

#include "gen/ccpp_ishape.h"
#include <string>

struct tspub_options {
  std::string topic;
  std::string color;
  int X0;
  int Y0;
  int size;
  int radius;
  long long period;
  int samples;
  std::string partition;
};

struct tssub_options {
  std::string topic;
  int samples;
  std::string partition;
};

std::ostream&
operator<<(std::ostream& os, const ShapeType& t);

std::ostream&
operator<<(std::ostream& os, const DDS::LivelinessChangedStatus& s); 

bool tspub_parse_args(int argc, char* argv[], tspub_options& options);

bool tssub_parse_args(int argc, char* argv[], tssub_options& options);


#endif // DEMO_TS_UTIL_HPP_
