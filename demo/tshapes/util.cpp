#include "util.hpp"

// -- Boost Include
#include <boost/program_options.hpp>

#include <iostream>

std::ostream&
operator<<(std::ostream& os, const DDS::LivelinessChangedStatus& s) 
{
  os << "LivelinessChangedStatus = {"
     <<"\n\talive_count = " << s.alive_count 
     << "\n\tnot_alive_count = " << s.not_alive_count 
     << "\n\talive_count_change = " << s.alive_count_change
     << "\n\tlast_instance_handle = " << s.last_publication_handle
     <<"\n}";
  return os;
}
std::ostream&
operator<<(std::ostream& os, const ShapeType& t) 
{
  os << "ShapeType = (color = " << t.color 
     << ", x = " << t.x 
     << ", y = " << t.y 
     << ", size = " << t.shapesize 
     << ")";

  return os;
}

namespace po = boost::program_options;
bool
tspub_parse_args(int argc, char* argv[], tspub_options& o) 
{
  bool isok = true;
  po::options_description desc("Available options for <tspub> are:");
  desc.add_options()
    ("help", "produce help message")
    ("topic", po::value<std::string>(), "[Circle|Square|Triangle]")
    ("color", po::value<std::string>(), "[BLUE|RED|ORANGE|YELLOW|CYAN|MAGENTA]")
    ("size", po::value<int>(), "the shape size")
    ("X0", po::value<int>(), "the X0 for the shape orbit [0-400]")
    ("Y0", po::value<int>(), "the Y0 for the shape orbit [0-240]")
    ("radius", po::value<int>(), "the radius of the orbit the shape will follow")
    ("period",  po::value<int>(), "the write perio (msec >= 0) at which the shape will be refreshed")
    ("samples", po::value<int>(), "the number of samples that will be written")
    ("partition", po::value<std::string>(), "the partition in which data will be read/written")

    ;

  try {  
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    
    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      exit(-1);
    }
    if (vm.count("topic")) {
      o.topic = vm["topic"].as<std::string>();
    }
    if (vm.count("color")) {
      o.color = vm["color"].as<std::string>();
    }
    if (vm.count("size")) {
      o.size = vm["size"].as<int>();
    }
    if (vm.count("radius")) {
      o.radius = vm["radius"].as<int>();
    }
    if (vm.count("X0")) {
      o.X0 = vm["X0"].as<int>();
    }
    if (vm.count("Y0")) {
      o.Y0 = vm["Y0"].as<int>();
    }
    if (vm.count("samples")) {
      o.samples = vm["samples"].as<int>();
    }
    if (vm.count("period")) {
      o.period = vm["period"].as<int>(); // ms as nsec
      if (o.period < 0)
	throw "period has to be >= 0";
      o.period = o.period  * 1000000L;
      std::cout << "o.period = " << o.period << std::endl;
    }

    if (vm.count("partition")) {
      o.partition = vm["partition"].as<std::string>();
    }
    
  }
  catch(...) {
    std::cout << desc << "\n";
    isok = false;
  }
  return isok;
}

bool
tssub_parse_args(int argc, char* argv[], tssub_options& o) 
{
  bool isok = true;
  po::options_description desc("Available options for <tssub> are:");
  desc.add_options()
    ("help", "produce help message")
    ("topic", po::value<std::string>(), "[Circle|Square|Triangle]")
    ("samples", po::value<int>(), "the number of samples that will be written")
    ("partition", po::value<std::string>(), "the partition in which data will be read/written")
    ;

  try {  
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    
    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      exit(-1);
    }
    if (vm.count("topic")) {
      o.topic = vm["topic"].as<std::string>();
    }

    if (vm.count("samples")) {
      o.samples = vm["samples"].as<int>();
    }
    
    if (vm.count("partition")) {
      o.partition = vm["partition"].as<std::string>();
    }
    
  }
  catch(...) {
    std::cout << desc << "\n";
    isok = false;
  }
  return isok;
}
//////////////////////////////////////////////////////////////////////////////
