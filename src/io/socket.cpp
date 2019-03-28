
#include "socket.h"

#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "io_exception.h"
#include "log/log.h"

namespace libhttp {

const char* kTag = "Socket";

Socket::Socket(const std::string host, int port) : fd_{-1} {
  struct addrinfo hint{};
  hint.ai_family = AF_UNSPEC;
  hint.ai_socktype = SOCK_STREAM;
  hint.ai_flags = AI_NUMERICSERV;
  std::string port_ = std::to_string(port);
  struct addrinfo* res;
  int error = getaddrinfo(host.c_str(), port_.c_str(), &hint, &res);
  if (error != 0) {
    throw IOException(gai_strerror(error));
  }

  int sockfd = -1;
  error = 0;
  for (struct addrinfo* addr = res; addr; addr = addr->ai_next) {
    sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (sockfd < 0) {
      error = errno;
      LOGI(kTag, "socket: %s", strerror(error));
      continue;
    }
    if (connect(sockfd, addr->ai_addr, addr->ai_addrlen) == -1) {
      error = errno;
      LOGI(kTag, "connect: %s", strerror(error));
      continue;
    }
    break;
  }
  if (sockfd < 0) {
    if (error == 0) {
      auto msg = std::string{"No address got of host "};
      msg += host;
      msg += port_;
      throw IOException{msg};
    } else {
      auto msg = std::string{"Fail to create socket: "};
      msg += strerror(errno);
      throw IOException{msg};
    }
  }

  fd_ = sockfd;
}

Socket::~Socket() {
  if (fd_ >= 0 && close(fd_) == -1) {
    LOGE(kTag, "socket close fail: %s", strerror(errno));
  }
}


int Socket::Read(void* buf, size_t len) {
  auto err = read(fd_, buf, len);
  if (err < 0) {
    throw IOException(strerror(errno));
  }
  return err;
}

int Socket::Write(const void* buf, size_t len) {
  auto err = write(fd_, buf, len);
  if (err < 0) {
    throw IOException(strerror(errno));
  }
  return err;
}

int Socket::ReadN(void* buf, size_t n) {
  auto left = n;
  auto buffer = static_cast<char*>(buf);
  while (left > 0) {
    auto nbyte = Read(buffer, left);
    if (n < 0) {
      if (errno == SIGINT) continue;
      else                 break;
    } else if (n == 0) {
      break;
    }
    left -= nbyte;
    buffer += nbyte;
  }
  return n - left;
}

int Socket::WriteN(const void* buf, size_t n) {
  auto left = n;
  auto buffer = static_cast<const char*>(buf);
  while (left > 0) {
    auto nbyte = Write(buffer, left);
    if (n < 0) {
      if (errno == SIGINT) continue;
      else                 break;
    } else if (n == 0) {
      break;
    }
    left -= nbyte;
    buffer += nbyte;
  }
  return n - left;
}

}