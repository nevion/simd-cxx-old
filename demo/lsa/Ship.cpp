#include "Ship.hpp"

lsa::demo::Ship::Ship(const lsa::dis::EntityState es) : es_(es) { }
      
const lsa::dis::EntityState& 
lsa::demo::Ship::tick() {
  
  lsa::dis::Location ol = es_.location;
  lsa::dis::LinearVelocity v = es_.velocity;

  lsa::dis::Location nl;
  nl.x = ol.x + v.x;
  nl.y = ol.y + v.y;
  nl.z = ol.z + v.z;

  es_.location = nl;
  return es_;
}

const lsa::dis::EntityState& 
lsa::demo::Ship::entityState() {
  return es_;
}
