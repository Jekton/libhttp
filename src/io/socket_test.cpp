
#include "socket.h"

#include <iostream>

int main() try {
  libhttp::Socket sock{"127.0.1", 9090};
  std::cout << "fd = " << sock.fd() << std::endl;
  {
    libhttp::Socket sock2{"www.china-pub.com", 80};
    std::cout << "fd = " << sock2.fd() << std::endl;
    libhttp::Socket sock3{"www.baidu.com", 80};
    std::cout << "fd = " << sock3.fd() << std::endl;
  }
  libhttp::Socket sock2{"www.china-pub.com", 80};
  std::cout << "fd = " << sock2.fd() << std::endl;
  libhttp::Socket sock3{"www.baidu.com", 80};
  std::cout << "fd = " << sock3.fd() << std::endl;
} catch (const std::exception& e) {
  std::cerr << e.what() << std::endl;
}