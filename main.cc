#include "scope_exit.hpp"
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {

  auto fd = open("./text.txt", O_CREAT | O_RDWR);
  if (fd < 0) {
    perror("open error");
    return 0;
  }

  scope_exit on_exit([&fd] {
    std::cout << "close file on exit\n";
    close(fd);
  });

  unlink("./text.txt");

  return 0;
}
