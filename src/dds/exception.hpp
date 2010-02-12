#ifndef AC_SIMD_DDS_EXCEPTION_HPP_
#define AC_SIMD_DDS_EXCEPTION_HPP_

#include <exception>
#include <string>
#include <dds/osmacros.hpp>

namespace dds {

  class SIMD_EXPORT Exception : public virtual std::exception {
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

std::ostream& operator<<(std::ostream& os, const dds::Exception& e);

#endif /* AC_SIMD_DDS_EXCEPTION_HPP_ */
