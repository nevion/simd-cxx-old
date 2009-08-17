// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

// -- BOOST Include
#include <boost/program_options.hpp>

// -- SIMD Include
#include <simd/runtime.hpp>
#include <simd/topic.hpp>
#include <simd/reader.hpp>
#include <simd/traits.hpp>
#include <simd/condition.hpp>

// -- Hello Include
#include <gen/ccpp_ping.h>
namespace po = boost::program_options;


int period = 1;
int history_depth = 10;
int history = 1;
bool set_deadline = false;
DDS::Duration_t deadline = {1, 0};

std::string name("OpenSplice|DDS");
std::string topic("PingTopic");
std::string type("PingType");
bool parse_args(int argc, char* argv[])
{
 po::options_description desc("Available options for <ping-sub> are:");
 desc.add_options()
   ("help", "produce help message")
   ("period", po::value<int>(), "period with which samples will be written")
   ("topic", po::value<std::string>(), "topic name for this ping application")
   ("reader-history", po::value<int>(), "reader history QoS")
   ("deadline", po::value<int>(), "deadline QoS (in sec)")
   ;
 
  po::variables_map vm;        
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    
  
  try {
    
    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      return false;
    }
    
    
    if (vm.count("topic")) 
      topic = vm["topic"].as<std::string>();
    
    if (vm.count("period")) 
      period = vm["period"].as<int>();
    
    if (vm.count("reader-history")) 
      history = vm["reader-history"].as<int>();

    if (vm.count("deadline")) {
      deadline.sec = vm["deadline"].as<int>();
      set_deadline = true;
    }
  } 
  catch (...) {
    std::cout << desc << "\n";
    return false;
  }
  return true;
}  
REGISTER_TOPIC_TRAITS(PingType);

class PingDataHandler {
public:
  void operator() (simd::DataReader<PingType>& reader) {
    std::cout << ">> PingDataHandler: Reads Data" << std::endl;
  }
};

int main(int argc, char* argv[]) {
  
  if (!parse_args(argc, argv))
    return 1;

  // -- init the simd runtime
  simd::Runtime::init("");
  simd::TopicQos tqos;
  tqos.set_best_effort();
  tqos.set_volatile();

  if (set_deadline)
    tqos.set_deadline(deadline);

  boost::shared_ptr<simd::Topic<PingType> > 
    pingTopic(new simd::Topic<PingType>(topic, tqos));

  simd::DataReaderQos drqos(tqos);
  drqos.set_keep_last(history);

  simd::DataReader<PingType> reader(pingTopic, drqos);

  boost::shared_ptr<DDS::ReadCondition> rc = 
    reader.create_readcondition();

  PingDataHandler handler;

  simd::ReadConditionCommand<simd::DataReader<PingType>&, PingDataHandler> 
    rcc(rc, reader, handler);



  PingTypeSeq samples;
  DDS::SampleInfoSeq infos;
  
  while (true) {
    reader.read(samples, infos);
    for (int i = 0; i < samples.length(); ++i) {
      std::cout << samples[i].vendor << " . " << samples[i].counter 
		<< std::endl;
    }
    reader.return_loan(samples, infos);
    usleep(period*1000);
  }


  return 0;
}
