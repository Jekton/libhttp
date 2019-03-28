
#ifndef LIBHTTP_IO_IO_EXCEPTION_H_
#define LIBHTTP_IO_IO_EXCEPTION_H_

#include <exception>
#include <string>

namespace libhttp {

class IOException : public std::exception {
 public:
  IOException(const std::string& msg) : msg_{msg} {}
  IOException(std::string&& msg) : msg_{msg} {}

  const char* what() const noexcept override {
    return msg_.c_str();
  }

 private:
  const std::string msg_;
};

}


#endif // LIBHTTP_IO_IO_EXCEPTION_H_