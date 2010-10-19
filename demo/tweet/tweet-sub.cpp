#include <iostream>
#include <iostream>
#include <dds/dds.hpp>
#include "gen/ccpp_tweet.h"

REGISTER_TOPIC_TRAITS(TweetType)

int main(int argc, char* argv[]) {
  
  if (argc < 2) {
    std::cout << "USAGE:\n\t"
	      << "tweet-reader <partition>"
	      << std::endl;
    exit (-1);
  }

  std::string partition = "tweeter.";
  partition += argv[1];

  dds::Runtime runtime(partition);
  dds::Duration cleanup_delay = {3600, 0};

  dds::TopicQos tQos;
  tQos.set_persistent();
  tQos.set_reliable();
  tQos.set_keep_last(1024);
  tQos.set_durability_service(cleanup_delay,
			      DDS::KEEP_LAST_HISTORY_QOS,
			      1024,
			      8192,
			      4196,
			      8192);

  dds::Topic<TweetType> topic("TweetTopic", tQos);


  dds::DataReaderQos drQos(tQos);
  dds::DataReader<TweetType> dr(topic, drQos);

  TweetTypeSeq data;
  DDS::SampleInfoSeq info;

  dds::Duration timeout = {60, 0};
  dr.wait_for_historical_data(timeout);

  while (true) {
    dr.take(data, info);
    for (uint32_t i = 0; i < data.length(); ++i) {
      std::cout << ">> " << data[i].userId << " :: " 
		<< data[i].tweet << std::endl;
    }
    dr.return_loan(data, info);
    sleep(1);
  }
  return 0;
}

