// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

// -- BOOST Include
#include <boost/program_options.hpp>

// -- SIMD Include
#include <dds/runtime.hpp>
#include <dds/topic.hpp>
#include <dds/writer.hpp>
#include <dds/traits.hpp>

// -- Hello Include
#include "gen/ccpp_hello.h"
#include "hello-traits.hpp"

#ifdef WIN32
#include "Windows.h"
#define msecSleep(msec) Sleep(msec)
#else
#define msecSleep(msec) usleep(1000*(msec))
#endif


namespace po = boost::program_options;

int period = 1;
int history_depth = 10;
int N = 50;
std::string partition = "HelloPartition";
std::string message("Hello OpenSplice DDS!");

bool parse_args(int argc, char* argv[])
{
 po::options_description desc("hello-pub program options are:");
  desc.add_options()
    ("help", "produce help message")
    ("message", po::value<std::string>(), "message sent-across")
    ("samples", po::value<int>(), "number of samples published")
    ("writer-history-depth", po::value<int>(), "sets the writer history depth")
    ("period", po::value<int>(), "read polling period in milli-seconcs")
    ("partition", po::value<std::string>(), "DDS Partition")
    ;

  po::variables_map vm;        
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    
  
  try {
    
    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      return false;
    }
    
    if (vm.count("message")) 
      message = vm["message"].as<std::string>();
    
    if (vm.count("samples")) 
      N = vm["samples"].as<int>();
    
    if (vm.count("writer-history-depth")) 
      history_depth = vm["writer-history-depth"].as<int>();
    
    if (vm.count("period")) 
      period = vm["period"].as<int>();
    
    if (vm.count("partition")) 
      partition = vm["partition"].as<std::string>();

  } 
  catch (...) {
    std::cout << desc << "\n";
    return false;
  }
  return true;
}  

int main(int argc, char* argv[]) {
  
  if (!parse_args(argc, argv))
    return 1;

  // -- start the dds runtime
  dds::Runtime runtime;
  
  dds::TopicQos tqos;
  tqos.set_reliable();
  tqos.set_transient();
  
  // -- create the DDS Topic
  dds::Topic<swatch::hello> helloTopic("helloTopic", tqos);

  dds::DataWriterQos dwqos(tqos);
  dwqos.set_keep_last(history_depth);
  dwqos.set_auto_dispose(false);
  
  // Create a Publisher
  dds::Publisher pub(partition);
  std::cout << "Created Pub" << std::endl;
  // -- create the DDS DataWriter
  dds::DataWriter<swatch::hello> writer(helloTopic, dwqos, pub);
  std::cout << "Created DW" << std::endl;

  
  swatch::hello sample;
  std::stringstream ss;
  
  for (int i = 0; i < N; ++i) {
    ss << i;
    std::string tmp = ss.str() + "." + message;
    ss.str("");
    sample.name = DDS::string_dup(tmp.c_str());
    std::cout << "<<= " <<  sample.name << std::endl;
    writer.write(sample);
    DDS::Time_t ts = {0, 0};
    writer.write(sample, ts);
    msecSleep(period);
  }
  std::cout << "[done]" << std::endl;
  return 0;
}
