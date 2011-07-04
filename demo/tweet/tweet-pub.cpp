#include <iostream>
#include <dds/dds.hpp>
#include "gen/ccpp_tweet.h"

REGISTER_TOPIC_TRAITS(TweetType)

int main(int argc, char* argv[]) {
  
  if (argc < 3) {
    std::cout << "USAGE:\n\t"
	      << "tweet-writer <uid> <partition>"
	      << std::endl;
    exit (-1);
  }

  std::string partition = "tweeter.";
  partition += argv[2];

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

  dds::DataWriterQos dwQos(tQos);
  dwQos.set_auto_dispose(false);
  dds::DataWriter<TweetType> dw(topic, dwQos);

  std::string tweet;
  TweetType tt;
  tt.userId = DDS::string_dup(argv[1]);
  std::cout << "tweet:> ";
  while (std::getline(std::cin, tweet)) {
    tt.tweet = DDS::string_dup(tweet.c_str());
    dw.write(tt);
    std::cout << "tweet:> ";
  }

  return 0;
}
