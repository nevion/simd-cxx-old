#ifndef AC_SIMD_DDS_EXCEPTION_HPP_
#define AC_SIMD_DDS_EXCEPTION_HPP_

#include <exception>
#include <string>
#include <dds/osmacros.hpp>

#define DECLARE_EXCEPTION(ExceptionName)		\
  class SIMD_API ExceptionName : public virtual Exception {	\
  public:						\
  ExceptionName(const std::string& what) throw();	\
  ExceptionName(const std::string& what,		\
		const std::string& where) throw();	\
  ExceptionName(const std::string& what,		\
		const std::string& where,		\
		int ecode) throw();			\
  virtual ~ExceptionName() throw();			\
  }; 


#define DEFINE_EXCEPTION(NP, ExceptionName)					\
  NP::ExceptionName::ExceptionName(const std::string& what) throw()		\
    : Exception(what) { }						\
  NP::ExceptionName::ExceptionName(const std::string& what,			\
			       const std::string& where) throw()	\
    : Exception(what, where) { }					\
  NP::ExceptionName::ExceptionName(const std::string& what,			\
			       const std::string& where,		\
			       int ecode) throw()			\
    : Exception(what, where, ecode) { }					\
  NP::ExceptionName::~ExceptionName() throw() { }


namespace dds {

  class SIMD_API Exception : public virtual std::exception {
  public:
    Exception(const std::string& what) throw();
  
    Exception(const std::string& what,
	      const std::string& where) throw();
  
    Exception(const std::string& what, 
	      const std::string& where,
	      int error_code) throw();
  
    virtual ~Exception() throw();
  
  public:
    virtual const char* what() const throw();
    virtual const char* where() const throw();
    virtual int error_code() const throw();
  
  private:
    std::string what_;
    std::string where_;
    int error_code_;
  };
}

SIMD_API std::ostream& operator<<(std::ostream& os, const dds::Exception& e);

#endif /* AC_SIMD_DDS_EXCEPTION_HPP_ */
