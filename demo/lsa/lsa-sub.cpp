#include <iostream>

#include <unistd.h>
#include <traits.hpp>
#include <Ship.hpp>

long simulationPeriod = 1000 * 1000; // usec 

void logEntityState(const lsa::dis::EntityState& es) {
  std::cout << "Entity: "
	    << "\n\t marking:  " << es.marking
	    << "\n\t site: " << es.id.site
	    << "\n\t application: " << es.id.application
	    << std::endl;
}

int main(int argc, char* argv[]) {
  dds::Runtime runtime("");
  dds::Topic<lsa::dis::EntityState> entityStateTopic("EntityStateTopic");
  dds::DataReader<lsa::dis::EntityState> dr(entityStateTopic);

  while(true) {
    std::vector<lsa::dis::EntityState> data;
    dr.read(data);
    std::for_each(data.begin(), data.end(), logEntityState);
    usleep(simulationPeriod);
  }

  return 0;
}
