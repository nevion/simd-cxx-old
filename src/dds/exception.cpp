#include <dds/exception.hpp>
#include <ostream>

dds::Exception::Exception(const std::string& what) throw()
  : what_(what), 
    where_("NA"),
    errno_(0) 

{}

dds::Exception::Exception(const std::string& what,
			   const std::string& where) throw()
  : what_(what),
    where_(where),
    errno_(0)
{}

dds::Exception::Exception(const std::string& what,
			   const std::string& where,
			   int errno) throw()
  : what_(what),
    where_(where),
    errno_(errno)
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
dds::Exception::errno() const throw() 
{
  return errno_;
}

std::ostream&
operator<<(std::ostream& os, const dds::Exception& e) 
{
  os << "What: " << e.what()
     << "Where: " << e.where()
     << "Errno:" << e.errno()
     << std::endl;

  return os;
}

