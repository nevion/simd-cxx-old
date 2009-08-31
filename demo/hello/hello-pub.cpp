// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

// -- BOOST Include
#include <boost/program_options.hpp>

// -- SIMD Include
#include <simd/runtime.hpp>
#include <simd/topic.hpp>
#include <simd/writer.hpp>
#include <simd/traits.hpp>

// -- Hello Include
#include "gen/ccpp_hello.h"
#include "hello-traits.hpp"

namespace po = boost::program_options;

int period = 1;
int history_depth = 10;
int N = 50;
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

  // -- init the simd runtime
  simd::Runtime::init();
  
  simd::TopicQos tqos;
  tqos.set_reliable();
  tqos.set_transient();
  
  // -- create the DDS Topic
  simd::Topic<swatch::hello> helloTopic("helloTopic", tqos);

  
  simd::DataWriterQos dwqos(tqos);
  dwqos.set_keep_last(history_depth);
  dwqos.set_auto_dispose(false);
  
  // -- create the DDS DataWriter
  simd::DataWriter<swatch::hello> writer(helloTopic, dwqos);

  
  swatch::hello sample;
  std::stringstream ss;
  
  for (int i = 0; i < N; ++i) {
    ss << i;
    std::string tmp = ss.str() + "." + message;
    ss.str("");
    sample.name = DDS::string_dup(tmp.c_str());
    std::cout << "<<= " <<  sample.name << std::endl;
    writer->write(sample);
    usleep(period*1000);
  }
  std::cout << "[done]" << std::endl;
  return 0;
}
