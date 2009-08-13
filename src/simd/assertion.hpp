#ifndef AC_SIMD_ASSERTION_HPP
#define AC_SIMD_ASSERTION_HPP

#include <simd/exception.hpp>


#define DECLARE_EXCEPTION( ExceptionName)		\
  class ExceptionName : public virtual Exception {	\
  public:						\
  ExceptionName(const std::string& what) throw();	\
  ExceptionName(const std::string& what,		\
		const std::string& where) throw();	\
  ExceptionName(const std::string& what,		\
		const std::string& where,		\
		int errno) throw();			\
  virtual ~ExceptionName() throw();			\
  }; 


#define DEFINE_EXCEPTION(ExceptionName)					\
  ExceptionName::ExceptionName(const std::string& what) throw()		\
    : Exception(what) { }						\
  ExceptionName::ExceptionName(const std::string& what,			\
			       const std::string& where) throw()	\
    : Exception(what, where) { }					\
  ExceptionName::ExceptionName(const std::string& what,			\
			       const std::string& where,		\
			       int errno) throw()			\
    : Exception(what, where, errno) { }					\
  ExceptionName::~ExceptionName() throw() { }	


namespace simd {

  DECLARE_EXCEPTION(PreconditionViolation)
  DECLARE_EXCEPTION(PostconditionViolation)
  DECLARE_EXCEPTION(StateInvariantViolation)



  template <typename AssertImpl>  
  class AssertBase : public AssertImpl {
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
}
#endif /* AC_SIMD_ASSERTION_HPP */
