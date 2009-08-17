// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

// -- BOOST Include
#include <boost/program_options.hpp>
#include <boost/bind.hpp>
#include <boost/signals/signal1.hpp>
#include <boost/thread/barrier.hpp>

// -- SIMD Include
#include <simd/runtime.hpp>
#include <simd/topic.hpp>
#include <simd/reader.hpp>
#include <simd/traits.hpp>

// -- Hello Include
#include <gen/ccpp_ping.h>

REGISTER_TOPIC_TRAITS(PingType);

namespace po = boost::program_options;


int period = 1;
int history = 1;
int samples_to_read = 50;

boost::barrier completion_barrier(2);

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
   ("samples", po::value<int>(), "number of samples reade by the reader")
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

    if (vm.count("samples")) {
      samples_to_read = vm["samples"].as<int>();
    }
  } 
  catch (...) {
    std::cout << desc << "\n";
    return false;
  }
  return true;
}  

struct DataHandler {
  void handle_data(simd::DataReader<PingType>& reader) {
    PingTypeSeq samples;
    DDS::SampleInfoSeq infos;
    
    reader.read(samples, infos);
    for (int i = 0; i < samples.length(); ++i) {
      std::cout << samples[i].vendor << " . " << samples[i].counter 
		<< std::endl;
      samples_to_read--;
    }
    reader.return_loan(samples, infos);
    if (samples_to_read <= 0)
      completion_barrier.wait();
  }

  void handle_liveliness_change(simd::DataReader<PingType>& reader, 
				const DDS::LivelinessChangedStatus& status)
  {
    std::cout << "Liveliness Status Change" << std::endl;
  }
};


int main(int argc, char* argv[]) {
  
  DataHandler dh;
  if (!parse_args(argc, argv))
    return 1;

  // -- init the simd runtime
  simd::Runtime::init("");
  simd::TopicQos tqos;
  tqos.set_best_effort();
  tqos.set_volatile();

  boost::shared_ptr<simd::Topic<PingType> > 
    pingTopic(new simd::Topic<PingType>(topic, tqos));

  
  simd::DataReaderQos drqos(tqos);
  drqos.set_keep_last(history);
  simd::DataReader<PingType> reader(pingTopic, drqos);
  
  boost::signals2::connection con_data = 
    reader.on_data_available_signal_connect(boost::bind(&DataHandler::handle_data, &dh, _1));

  boost::signals2::connection con_liv = 
    reader.on_liveliness_changed_signal_connect(boost::bind(&DataHandler::handle_liveliness_change, 
						    &dh, 
						    _1, 
						    _2));
  

  completion_barrier.wait();
  con_data.disconnect();
  con_liv.disconnect();
  return 0;
}
