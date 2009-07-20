#ifndef AC_SIMD_EXCEPTION_HPP_
#define AC_SIMD_EXCEPTION_HPP_

#include <exception>
#include <string>

namespace simd {
  class Exception;
}

class simd::Exception : public virtual std::exception {
public:
  Exception(const std::string& what) throw();
  
  Exception(const std::string& what,
	    const std::string& where) throw();
  
  Exception(const std::string& what, 
	    const std::string& where,
	    int errno) throw();
  
  virtual ~Exception() throw();
  
public:
  virtual const char* what() const throw();
  virtual const char* where() const throw();
  virtual int errno() const throw();
  
private:
  std::string what_;
  std::string where_;
  int errno_;
};

std::ostream& operator<<(std::ostream& os, const simd::Exception& e);

#endif /* AC_SIMD_EXCEPTION_HPP_ */
