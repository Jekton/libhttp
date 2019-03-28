
#ifndef LIBHTTP_IO_SOCKET_H_
#define LIBHTTP_IO_SOCKET_H_

#include <unistd.h>

#include <string>

namespace libhttp {

class Socket {

 public:
  Socket(std::string host, int port);
  ~Socket();

  Socket(const Socket&) = delete;
  Socket(Socket&&) = delete;
  Socket operator=(const Socket&) = delete;
  Socket operator=(Socket&&) = delete;

  /*
   * return bytes read
   */
  int Read(void* buf, size_t len);
  /*
   * return bytes written
   */
  int Write(const void* buf, size_t len);

  /*
   * return bytes read
   */
  int ReadN(void* buf, size_t n);
  /*
   * return bytes written
   */
  int WriteN(const void* buf, size_t n);

  int fd() const { return fd_; }

 private:
  int fd_;
};

}

#endif //LIBHTTP_IO_SOCKET_H_
