#include <iostream>

#include <unistd.h>
#include <traits.hpp>
#include <Ship.hpp>

long simulationPeriod = 1000 * 1000; // usec 

int main(int argc, char* argv[]) {
  std::string shipName;
  int site;
  int application;
  std::cout << "Please, enter the following simulation parameters:\n";
  std::cout << "Ship Name: ";
  std::cin >> shipName;
  std::cout << "Site Id: ";
  std::cin >> site;
  std::cout << "Application Id: ";
  std::cin >> application;
  dds::Runtime runtime("");

  dds::Topic<lsa::dis::EntityState> entityStateTopic("EntityStateTopic");
  dds::DataWriter<lsa::dis::EntityState> dw(entityStateTopic);
  

  lsa::dis::EntityState shipES;
  // EntityID
  shipES.id.site = site;
  shipES.id.application = application;
  shipES.id.entity = 0;

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
    std::cout << "." << std::endl;
    usleep(simulationPeriod);
  }
  return 0;
}

