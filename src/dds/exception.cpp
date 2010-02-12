#include <dds/exception.hpp>
#include <ostream>

dds::Exception::Exception(const std::string& what) throw()
  : what_(what), 
    where_("NA"),
    error_code_(0)

{}

dds::Exception::Exception(const std::string& what,
			   const std::string& where) throw()
  : what_(what),
    where_(where),
    error_code_(0)
{}

dds::Exception::Exception(const std::string& what,
                          const std::string& where,
                          int error_code) throw()
  : what_(what),
    where_(where),
    error_code_(error_code)
{}

dds::Exception::~Exception() throw() { }

const char*
dds::Exception::what() const throw() 
{
  return what_.c_str();
}


const char*
dds::Exception::where() const throw() 
{
  return where_.c_str();
}

int
dds::Exception::error_code() const throw()
{
  return error_code_;
}

std::ostream&
operator<<(std::ostream& os, const dds::Exception& e) 
{
  os << "What: " << e.what()
     << "Where: " << e.where()
     << "Errno:" << e.error_code()
     << std::endl;

  return os;
}

