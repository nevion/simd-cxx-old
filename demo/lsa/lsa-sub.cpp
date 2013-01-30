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


class EntityStateHander {
public:
  void operator() (dds::DataReader<lsa::dis::EntityState>& dr) {
    std::vector<lsa::dis::EntityState> data;
    dr.read(data);
    std::for_each(data.begin(), data.end(), logEntityState);
  }
};

int main(int argc, char* argv[]) {
  dds::Runtime runtime("");
  dds::Topic<lsa::dis::EntityState> entityStateTopic("EntityStateTopic");
  dds::DataReader<lsa::dis::EntityState> dr(entityStateTopic);

  EntityStateHander handler; 
  dds::ReadCondition rc = dr.create_readcondition(handler, 
						  dds::NOT_READ_SAMPLE_STATE, 
						  dds::ANY_VIEW_STATE,
						  dds::ALIVE_INSTANCE_STATE);
  dds::WaitSet ws;
  ws.attach(rc);
 
  while(true) {
    ws.dispatch();
  }

  return 0;
}
