#ifndef LSA_DEMO_SHIP_HPP_
#define LSA_DEMO_SHIP_HPP_

#include <gen/ccpp_DIS.h>

namespace lsa {
  namespace demo {

    class Ship {
    public:
      Ship(const ::lsa::dis::EntityState es);
      
      const ::lsa::dis::EntityState& tick();

      const ::lsa::dis::EntityState& entityState();

    private:
      ::lsa::dis::EntityState es_;
    };
  }
}

#endif /* LSA_DEMO_SHIP_HPP_ */
