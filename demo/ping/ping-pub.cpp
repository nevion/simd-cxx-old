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
#include <gen/ccpp_ping.h>
namespace po = boost::program_options;

int period = 1;
int history_depth = 10;
int N = 50;
std::string name("OpenSplice|DDS");
std::string topic("PingTopic");
std::string URI;

bool parse_args(int argc, char* argv[])
{
 po::options_description desc("Available options for <ping> are:");
 desc.add_options()
   ("help", "produce help message")
   ("name", po::value<std::string>(), "name for this ping application")
   ("samples", po::value<int>(), "number of samples published")
   ("period", po::value<int>(), "period with which samples will be written")
   ("topic", po::value<std::string>(), "topic name for this ping application")
   ("URI", po::value<std::string>(), "OpenSplice DDS configuration URI")
   ;
 
  po::variables_map vm;        
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    
  
  try {
    
    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      return false;
    }
    
    
    if (vm.count("name")) 
      name = vm["name"].as<std::string>();

    if (vm.count("topic")) 
      topic = vm["topic"].as<std::string>();

    if (vm.count("URI")) 
      URI = vm["URI"].as<std::string>();
    
    if (vm.count("samples")) 
      N = vm["samples"].as<int>();
    
    if (vm.count("period")) 
      period = vm["period"].as<int>();
  } 
  catch (...) {
    std::cout << desc << "\n";
    return false;
  }
  return true;
}  
REGISTER_TOPIC_TRAITS(PingType);

int main(int argc, char* argv[]) {
  
  if (!parse_args(argc, argv))
    return 1;

  // -- start the dds runtime to use the default DDS partition, which
  // -- as per the DDS standard is ""
  dds::Runtime::start("");
  
  dds::Topic<PingType> pingTopic(topic);
  dds::DataWriter<PingType> writer(pingTopic);

  PingType d;
  d.number = 0;
  d.counter = 1;
  d.vendor = name.c_str();
  for (int i = 0; i < N; ++i) {
    
    writer.write(d);
    std::cout << ".";
    std::cout.flush();
    d.counter++;
    usleep(period*1000);
  }
  std::cout << std::endl;
  dds::Runtime::stop();
  return 0;
}
