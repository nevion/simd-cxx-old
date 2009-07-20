#include <simd/exception.hpp>
#include <ostream>

simd::Exception::Exception(const std::string& what) throw()
  : what_(what), 
    where_("NA"),
    errno_(0) 

{}

simd::Exception::Exception(const std::string& what,
			   const std::string& where) throw()
  : what_(what),
    where_(where),
    errno_(0)
{}

simd::Exception::Exception(const std::string& what,
			   const std::string& where,
			   int errno) throw()
  : what_(what),
    where_(where),
    errno_(errno)
{}

simd::Exception::~Exception() throw() { }

const char*
simd::Exception::what() const throw() 
{
  return what_.c_str();
}


const char*
simd::Exception::where() const throw() 
{
  return where_.c_str();
}

int
simd::Exception::errno() const throw() 
{
  return errno_;
}

std::ostream&
operator<<(std::ostream& os, const simd::Exception& e) 
{
  os << "What: " << e.what()
     << "Where: " << e.where()
     << "Errno:" << e.errno()
     << std::endl;

  return os;
}

