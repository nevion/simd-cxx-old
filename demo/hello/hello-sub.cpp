// -- STD C++ Include
#include <iostream>
#include <iterator>
#include <sstream>

// -- BOOST Include
#include <boost/program_options.hpp>

// -- DDS Include
#include <dds/runtime.hpp>
#include <dds/topic.hpp>
#include <dds/reader.hpp>
#include <dds/traits.hpp>

// -- Hello Include
#include "gen/ccpp_hello.h"
#include "hello-traits.hpp"


namespace po = boost::program_options;

int period = 5;
int history_depth = 10;

bool parse_args(int argc, char* argv[]) 
{
  po::options_description desc("hello-sub program options are:");
  desc.add_options()
    ("help", "produce help message")
    ("reader-history-depth", po::value<int>(), "sets the reader history depth")
    ("period", po::value<int>(), "read polling period in milli-seconcs")
    ;
  
  po::variables_map vm;        
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    
  
  try {
    if (vm.count("help") || argc == 1) {
      std::cout << desc << std::endl;
      return false;
    }
    
    if (vm.count("reader-history-depth")) 
      history_depth = vm["reader-history-depth"].as<int>();
    
    if (vm.count("period")) 
      period = vm["period"].as<int>();
  } 
  catch (...) {
    std::cout << desc << std::endl;
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  
  if (!parse_args(argc, argv)) 
    return 1;
  
  // -- Start DDS
  dds::Runtime::start();
  
  // -- Create a Topic
  dds::TopicQos tqos;
  tqos.set_reliable();
  tqos.set_transient();
  dds::Topic<swatch::hello> helloTopic("helloTopic", tqos);

  // Create a DataReader
  dds::DataReaderQos drqos(tqos);  
  drqos.set_keep_last(history_depth);
  dds::DataReader<swatch::hello> reader(helloTopic, drqos);

  swatch::helloSeq samples;
  DDS::SampleInfoSeq infos;
  
  // Read the data
  while (true) {
    reader.read(samples, infos);
    
    for (int i = 0; i < samples.length(); ++i) {
      std::cout << "=>> " <<  samples[i].name << std::endl;
    }
    if (samples.length() > 0)
      std::cout << "-------------<Batch>---------------" << std::endl;

    // Notice that since the container had initially a lengh of 0
    // (zero) we are loaning the memory and thus need to return it
    // back to the middleware.
    reader.return_loan(samples, infos);
    usleep(period*1000);
  }
  
  dds::Runtime::stop();
  return 0;
}
