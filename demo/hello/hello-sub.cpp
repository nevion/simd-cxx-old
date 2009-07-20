// -- STD C++ Include
#include <iostream>
#include <iterator>
#include <sstream>

// -- BOOST Include
#include <boost/program_options.hpp>

// -- SIMD Include
#include <simd/runtime.hpp>
#include <simd/topic.hpp>
#include <simd/reader.hpp>
#include <simd/traits.hpp>

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
  
  simd::Runtime::init();
  
  simd::TopicQos tqos;
  tqos.set_reliable();
  tqos.set_transient();
  simd::Topic<swatch::hello> helloTopic("helloTopic", tqos);

  simd::DataReaderQos drqos(tqos);  
  drqos.set_keep_last(history_depth);
  simd::DataReader<swatch::hello> reader(helloTopic, drqos);

  swatch::helloSeq samples;
  DDS::SampleInfoSeq infos;
  
  while (true) {
    reader.read(samples, infos);
    
    for (int i = 0; i < samples.length(); ++i) {
      std::cout << "=>> " <<  samples[i].name << std::endl;
    }
    if (samples.length() > 0)
      std::cout << "--" << std::endl;
    reader.return_loan(samples, infos);
    usleep(period*1000);

  }
  
  return 0;
}
