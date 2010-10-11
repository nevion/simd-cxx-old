#ifndef AC_SIMD_DDS_ASSERTION_HPP
#define AC_SIMD_DDS_ASSERTION_HPP

#include <dds/osmacros.hpp>
#include <dds/exception.hpp>

namespace dds {

  DECLARE_EXCEPTION(PreconditionViolation)
  DECLARE_EXCEPTION(PostconditionViolation)
  DECLARE_EXCEPTION(StateInvariantViolation)


  template <typename AssertImpl>  
  class SIMD_API AssertBase : public AssertImpl {
  public:
    inline static void precondition(bool condition) {
      AssertImpl::precondition(condition);
    }
  
    inline static void precondition(bool condition, 
				    const std::string& what) {
      AssertImpl::precondition(condition, what);
    }

    inline static void precondition(bool condition, 
				    const std::string& what, 
				    const std::string& where) {
      AssertImpl::precondition(condition,
			       what,
			       where);
    }
  
    inline static void postcondition(bool condition) {
      AssertImpl::postcondition(condition);
    }

    inline static void postcondition(bool condition, 
				     const std::string& what) {
      AssertImpl::postcondition(condition,
				what);
    }

    inline static void postcondition(bool condition, 
				     const std::string& what, 
				     const std::string& where) {
      AssertImpl::postcondition(condition,
				what,
				where);
    }
  

    inline static void invariant(bool condition) {
      AssertImpl::invariant(condition);
    }

    inline static void invariant(bool condition, 
				 const std::string& what) {
      AssertImpl::invariant(condition, what);
    }

    inline static void invariant(bool condition, 
				 const std::string& what, 
				 const std::string& where) {
      AssertImpl::invariant(condition,
			    what,
			    where);
    }
  };
}
#endif /* AC_SIMD_DDS_ASSERTION_HPP */
