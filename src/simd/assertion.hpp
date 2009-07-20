#ifndef AC_SIMD_ASSERTION_HPP
#define AC_SIMD_ASSERTION_HPP

#include <simd/exception.hpp>


namespace simd {
  template <typename AssertImpl>  
  class AssertBase;
  class PreconditionViolation;
  class PostconditionViolation;
  class StateInvariantViolation;
}


#define DECLARE_EXCEPTION(NS, ExceptionName)	\
class NS::ExceptionName : public virtual simd::Exception {\
public:\
ExceptionName(const std::string& what) throw();\
ExceptionName(const std::string& what,\
	      const std::string& where) throw();\
ExceptionName(const std::string& what, \
	    const std::string& where, \
	    int errno) throw(); \
virtual ~ExceptionName() throw(); \
}; 


#define DEFINE_EXCEPTION(NS, ExceptionName)				\
  NS::ExceptionName::ExceptionName(const std::string& what) throw()	\
  : NS::Exception(what) { }						\
  NS::ExceptionName::ExceptionName(const std::string& what,		\
				   const std::string& where) throw()	\
    : NS::Exception(what, where) { }					\
  NS::ExceptionName::ExceptionName(const std::string& what,		\
				   const std::string& where,		\
				   int errno) throw()			\
    : NS::Exception(what, where, errno) { }				\
  NS::ExceptionName::~ExceptionName() throw() { }	


DECLARE_EXCEPTION(simd, PreconditionViolation)
DECLARE_EXCEPTION(simd, PostconditionViolation)
DECLARE_EXCEPTION(simd, StateInvariantViolation)



template <typename AssertImpl>  
class simd::AssertBase : public AssertImpl {
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
    AssertImpl::poscondition(condition,
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

#endif /* AC_SIMD_ASSERTION_HPP */
