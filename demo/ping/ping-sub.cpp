// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

// -- BOOST Include
#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>

// -- SIMD Include
#include <dds/dds.hpp>

// -- Hello Include
#include <gen/ccpp_ping.h>

REGISTER_TOPIC_TRAITS(PingType);

namespace po = boost::program_options;

int history_depth = 10;
int history = 1;
bool set_deadline = false;
DDS::Duration_t deadline = {1, 0};

std::string name("OpenSplice|DDS");
std::string topic("PingTopic");
std::string type("PingType");

bool parse_args(int argc, char* argv[])
{
  po::options_description desc("Available options for <ping-sub> are");
  desc.add_options()
    ("help", "produce help message")
    ("topic", po::value<std::string>(), "topic name for this ping application")
    ("reader-history", po::value<int>(), "reader history QoS")
    ("deadline", po::value<int>(), "deadline QoS (in sec)")
    ;

  try {
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      return false;
    }

    if (vm.count("topic"))
      topic = vm["topic"].as<std::string>();

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

class PingDataHandler {
public:
  void operator() (dds::DataReader<PingType>& reader) {
    /*
    const uint32_t max_size = 32;
    std::vector<PingType> data(max_size) ;
    std::vector<DDS::SampleInfo> info(max_size);
    
    uint32_t length = reader.read(data.begin(), info.begin(), max_size);
    */
    std::vector<PingType> data;
    /*
    std::back_insert_iterator<std::vector<PingType>> bit(data);
    reader.read(bit);
    */
    reader.read(data);
    std::vector<PingType>::iterator end = data.end();
    for (std::vector<PingType>::iterator index = data.begin(); index < end; ++index) {
      std::cout << index->vendor << " . " << index->counter
		<< std::endl;
    }
    /*
    PingTypeSeq samples;
    DDS::SampleInfoSeq infos;
    reader.read(samples, infos);
    for (unsigned int i = 0; i < samples.length(); ++i) {
      std::cout << samples[i].vendor << " . " << samples[i].counter
		<< std::endl;
    }
    reader.return_loan(samples, infos);
    */
  }
};

int main(int argc, char* argv[]) {

  if (!parse_args(argc, argv))
    return 1;

  // -- start the dds runtime
  dds::Runtime runtime("");

  dds::Topic<PingType> pingTopic(topic);
  dds::DataReader<PingType> reader(pingTopic);

  PingDataHandler handler;
  dds::ReadCondition arc = reader.create_readcondition(handler, 
						       dds::NOT_READ_SAMPLE_STATE, 
						       dds::ANY_VIEW_STATE,
						       dds::ALIVE_INSTANCE_STATE);
  
  ::dds::WaitSet ws;
  DDS::ReturnCode_t retc = ws.attach(arc);
  
  std::cout << ">> Attach Condition: " 
	    << dds::retcode2string(retc) << std::endl;

  DDS::Duration_t timeout = {1, 0};
  bool done = false;
  while (!done) {
    try {
      ws.dispatch(timeout);
    } catch (const dds::InterruptedException& e) {
      exit(0);
    }
  }

  return 0;
}
