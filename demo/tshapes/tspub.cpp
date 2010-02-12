#include <math.h>
#include <dds/dds.hpp>
#include "util.hpp"


REGISTER_TOPIC_TRAITS(ShapeType);


tspub_options opt = {
  "Circle",        // = Topic
  "BLUE",          // = Color
  80,              // = Size
  200,             // = X0
  120,             // = Y0
  120,             // = radius
  500,               // = period (ms)
  1000,            // = samples
  "dds_partition"  // = partition
};

const long long ONE_SECOND = 1E9;
int
main(int argc, char* argv[]) 
{
  if (!tspub_parse_args(argc, argv, opt))
    exit(-1);
  
  dds::Runtime runtime(opt.partition);
  
  dds::Topic<ShapeType> shape(opt.topic);
  dds::DataWriter<ShapeType> dw(shape);
  
  float delta = 0.1F;
  int x;
  int y;
  ShapeType st;
  st.color = DDS::string_dup(opt.color.c_str());
  st.shapesize = opt.size;
  
  
  long long sec = 0;
  long long nsec = opt.period;

  // nsec has to be <= 999999999
  if (nsec >= ONE_SECOND) {
    sec = nsec / ONE_SECOND;
    nsec = opt.period - (sec * ONE_SECOND);
  } 

  timespec period = {
    sec, 
    nsec
  };
  
  float theta = 0;
  timespec leftover;
  for (int i = 0; i < opt.samples; ++i) {
    x = opt.X0 + static_cast<int>(opt.radius * cos(theta));
    y = opt.Y0 + static_cast<int>(opt.radius * sin(theta));
    theta += delta;
    st.x = x;
    st.y = y;
    dw.write(st);
    nanosleep(&period, &leftover);
    std::cout << "DW << " << st << std::endl;
  }
  
  return 0;
}
