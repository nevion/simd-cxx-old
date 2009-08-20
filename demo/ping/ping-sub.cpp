// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

// -- BOOST Include
#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>

// -- SIMD Include
#include <simd/simd.hpp>

// -- Hello Include
#include <gen/ccpp_ping.h>

REGISTER_TOPIC_TRAITS(PingType);

typedef simd::Topic<PingType> PingTopic_t;
typedef boost::shared_ptr<PingTopic_t> PingTopicRef_t;


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

class PingDataHandler {
public:
	void operator() (simd::DataReader<PingType>& reader) {
		std::cout << ">> PingDataHandler: Reads Data" << std::endl;
		PingTypeSeq samples;
		DDS::SampleInfoSeq infos;
		reader.read(samples, infos);
		for (unsigned int i = 0; i < samples.length(); ++i) {
			std::cout << samples[i].vendor << " . " << samples[i].counter
			<< std::endl;

		}
		reader.return_loan(samples, infos);
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

	PingTopicRef_t pingTopic(new PingTopic_t(topic, tqos));

	simd::DataReaderQos drqos(tqos);
	drqos.set_keep_last(history);

	simd::DataReader<PingType> reader(pingTopic, drqos);

	boost::shared_ptr<DDS::ReadCondition> rc =
			reader.create_readcondition();

	PingDataHandler handler;


	simd::ExecutableReadCondition<simd::DataReader<PingType>&, PingDataHandler>*
	ecp = new simd::ExecutableReadCondition<simd::DataReader<PingType>&, PingDataHandler>(rc, reader, handler);

	::simd::ExecutableConditionRef ecr(ecp);
	::simd::ExecutableWaitSet ws;
	DDS::ReturnCode_t retc = ws.attach(ecr);
	std::cout << ">> Attach Condition: " << simd::retcode2string(retc) << std::endl;
	ws.attach(ecr);

	DDS::Duration_t timeout = {1, 0};
	while (true) {
		::simd::ExecutableConditionVector conds = ws.wait(timeout);
		for (unsigned int i = 0; i < conds.size(); ++i)
			conds[i]->execute();
	}


	return 0;
}
