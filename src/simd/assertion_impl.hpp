#ifndef AC_SIMD_NULL_ASSERTION_IMPL_HPP_
#define AC_SIMD_NULL_ASSERTION_IMPL_HPP_

#include <simd/assertion.hpp>

namespace simd {
  class NullAssertImpl;
  class SimpleAssertImpl;
}

class simd::NullAssertImpl {
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


class simd::SimpleAssertImpl {
public:
  inline static void precondition(bool condition) {
    if (!condition)
      throw simd::PreconditionViolation("Precondition Violated");
  }
  
  inline static void precondition(bool condition, 
				   const std::string& what) {
    if (!condition)
      throw simd::PreconditionViolation(what);
  }

  inline static void precondition(bool condition, 
				  const std::string& what, 
				  const std::string& where) {
    if (!condition)
      throw simd::PreconditionViolation(what, where);
  }
  
  inline static void postcondition(bool condition) {
    if (!condition)
      throw simd::PostconditionViolation("Postcondition Violated");
  }

  inline static void postcondition(bool condition, 
				   const std::string& what) {
    if (!condition)
      throw simd::PostconditionViolation(what);
  }

  inline static void postcondition(bool condition, 
				   const std::string& what, 
				   const std::string& where) {
    if (!condition)
      throw simd::PostconditionViolation(what, where);
  }
  

  inline static void invariant(bool condition) {
    if (!condition)
      throw simd::StateInvariantViolation("State Invariant Violated");
  }

  inline static void invariant(bool condition, 
			       const std::string& what) {
    if (!condition)
      throw simd::StateInvariantViolation(what);
  }
  
  inline static void invariant(bool condition, 
			       const std::string& what, 
			       const std::string& where) {
    if (!condition)
      throw simd::StateInvariantViolation(what, where);

  }
};


#endif /* AC_SIMD_NULL_ASSERTION_IMPL_HPP_ */
