#include <math.h>
#include <dds/dds.hpp>
#include "util.hpp"
#include <boost/thread/barrier.hpp>

REGISTER_TOPIC_TRAITS(ShapeType);

tssub_options opt = {
  "Circle",        // = Topic
  1000,            // = samples
  "dds_partition"  // = partition
};

class ShapeUpdateHandler {
public:
  ShapeUpdateHandler(int samples, boost::barrier& barrier) 
    : samples_(samples),
      barrier_(barrier)
  {  }

  ~ShapeUpdateHandler() { }

public:
  void handle_data(dds::DataReader<ShapeType>& reader) 
  { 
    ShapeTypeSeq data;
    DDS::SampleInfoSeq status;
    reader.read(data, status);
    samples_ -= data.length();
    for (int i = 0; i < data.length(); ++i) 
      std::cout << std::dec << "DR >> " << data[i] << std::endl;
    
    // Notice it is OK to call the barrier_.wait() here since it is
    // not really going to wait but simply reach the barrier count and
    // exit the program.
    if (samples_ <= 0)
      barrier_.wait();
  }
  
  void handle_liveliness_change(dds::DataReader<ShapeType>& reader, 
				const DDS::LivelinessChangedStatus& status)
  {
    std::cout << status << std::endl;
  }

private:
  int samples_;
  boost::barrier& barrier_;
};
  
int
main(int argc, char* argv[]) 
{
  if (!tssub_parse_args(argc, argv, opt))
    exit(-1);

  dds::Runtime runtime(opt.partition);
  
  dds::Topic<ShapeType> shape(opt.topic);
  dds::DataReader<ShapeType> dr(shape);

  boost::barrier completion_barrier(2);
  ShapeUpdateHandler handler(opt.samples, completion_barrier);

  dds::sigcon_t con_data = 
    dr.on_data_available_signal_connect(boost::bind(&ShapeUpdateHandler::handle_data,
						    &handler, 
						    _1));


  dds::sigcon_t con_liv = 
    dr.on_liveliness_changed_signal_connect(boost::bind(&ShapeUpdateHandler::handle_liveliness_change, 
							&handler, 
							_1, 
							_2));
  
  
  completion_barrier.wait();
  con_data.disconnect();
  con_liv.disconnect();

  return 0;
}
