#include <math.h>
#include <dds/dds.hpp>
#include "util.hpp"


REGISTER_TOPIC_TRAITS(ShapeType);

volatile int read_samples_ = 0;

tssub_options opt = {
  "Circle",        // = Topic
  1000,            // = samples
  "dds_partition"  // = partition
};

class ShapeUpdateHandler {
public:
  ShapeUpdateHandler()  {  }
  ~ShapeUpdateHandler() { }
public:
  void operator()(dds::DataReader<ShapeType>& reader) { 
    ShapeTypeSeq data;
    DDS::SampleInfoSeq status;
    reader.read(data, status);
    read_samples_ += data.length();
    for (int i = 0; i < data.length(); ++i) 
      std::cout << std::dec << ">>[DR]: " << data[i] << std::endl;
    
    reader.return_loan(data, status);
  }
  
private:
  // volatile int read_samples_;
};
  
int
main(int argc, char* argv[]) 
{
  if (!tssub_parse_args(argc, argv, opt))
    exit(-1);
  
  dds::Runtime runtime(opt.partition);
  
  dds::Topic<ShapeType> shape(opt.topic);
  dds::DataReader<ShapeType> dr(shape);

  ShapeUpdateHandler handler;
  dds::ActiveReadCondition arc = 
    dr.create_readcondition(handler);
  ::dds::WaitSet ws;
  DDS::ReturnCode_t retc = ws.attach(arc);

  while (read_samples_ < opt.samples) {
    ws.dispatch();
  }  
  return 0;
}
