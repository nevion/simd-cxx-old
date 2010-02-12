#ifndef AC_SIMD_DDS_NULL_ASSERTION_IMPL_HPP_
#define AC_SIMD_DDS_NULL_ASSERTION_IMPL_HPP_

#include <dds/assertion.hpp>

namespace dds {

  class SIMD_EXPORT NullAssertImpl {
  public:
    inline static void precondition(bool) {  }
  
    inline static void precondition(bool, 
				    const std::string&) { }

    inline static void precondition(bool, 
				    const std::string&, 
				    const std::string&) { }
  
    inline static void postcondition(bool) { }

    inline static void postcondition(bool, 
				     const std::string&) { }

    inline static void pre_condition(bool, 
				     const std::string&, 
				     const std::string&) { }
  

    inline static void invariant(bool) { }

    inline static void invariant(bool, 
				 const std::string&) { }

    inline static void invariant(bool, 
				 const std::string&, 
				 const std::string&) { }
  };


  class SIMD_EXPORT SimpleAssertImpl {
  public:
    inline static void precondition(bool condition) {
      if (!condition)
	throw PreconditionViolation("Precondition Violated");
    }
  
    inline static void precondition(bool condition, 
				    const std::string& what) {
      if (!condition)
	throw PreconditionViolation(what);
    }

    inline static void precondition(bool condition, 
				    const std::string& what, 
				    const std::string& where) {
      if (!condition)
	throw PreconditionViolation(what, where);
    }
  
    inline static void postcondition(bool condition) {
      if (!condition)
	throw PostconditionViolation("Postcondition Violated");
    }

    inline static void postcondition(bool condition, 
				     const std::string& what) {
      if (!condition)
	throw PostconditionViolation(what);
    }

    inline static void postcondition(bool condition, 
				     const std::string& what, 
				     const std::string& where) {
      if (!condition)
	throw PostconditionViolation(what, where);
    }
  

    inline static void invariant(bool condition) {
      if (!condition)
	throw StateInvariantViolation("State Invariant Violated");
    }

    inline static void invariant(bool condition, 
				 const std::string& what) {
      if (!condition)
	throw StateInvariantViolation(what);
    }
  
    inline static void invariant(bool condition, 
				 const std::string& what, 
				 const std::string& where) {
      if (!condition)
	throw StateInvariantViolation(what, where);

    }
  };
}

#endif /* AC_SIMD_DDS_NULL_ASSERTION_IMPL_HPP_ */
