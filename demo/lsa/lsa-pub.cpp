#include <iostream>

#include <unistd.h>
#include <traits.hpp>
#include <Ship.hpp>

std::string shipName = "Nautilus";
long simulationPeriod = 1000 * 1000; // usec 

int main(int argc, char* argv[]) {
  dds::Runtime runtime("");
  dds::Topic<lsa::dis::EntityState> entityStateTopic("EntityStateTopic");
  dds::DataWriter<lsa::dis::EntityState> dw(entityStateTopic);

  // TODO: Fix me by using arg-line params
  lsa::dis::EntityState shipES;
  // EntityID
  shipES.id.site = 0;
  shipES.id.application = 1;
  shipES.id.entity = 2;

  // Force ID
  shipES.forceId = lsa::dis::FRIENDLY;

  // EntityType
  shipES.type.kind = lsa::dis::PLATFORM;
  shipES.type.domain = 0;
  shipES.type.country = 0;
  shipES.type.category = 0;
  shipES.type.subcategory = 0;
  shipES.type.specific = 0;
  shipES.type.extra = 0;

  // Location
  shipES.location.x = 375799.0;
  shipES.location.y = -3118378.0;
  shipES.location.z = 4089143.0;

  // Velocity
  shipES.velocity.x = 1;
  shipES.velocity.y = 2;
  shipES.velocity.z = 3;
  
  // Orientation
  shipES.orientation.psi = 0;
  shipES.orientation.theta = 0;
  shipES.orientation.phi = 0;

  // Marking
  shipES.marking = shipName.c_str();

  lsa::demo::Ship ship(shipES);
  while (true) {
    dw.write(ship.tick());
    usleep(simulationPeriod);
  }
  return 0;
}

