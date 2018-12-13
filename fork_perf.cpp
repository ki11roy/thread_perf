#include <thread>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include <unistd.h>

template <class Tp> inline void DoNotOptimize(Tp const &value) {
  asm volatile("" : : "g"(value) : "memory");
}

int main() {
  auto iterations = 100;
  std::chrono::time_point<std::chrono::system_clock> start;
  std::chrono::time_point<std::chrono::system_clock> stop;

  // noop
  start = std::chrono::system_clock::now();
  for (auto i = 0; i < 1000000; ++i) {
    asm volatile("nop" : : :);
  }
  stop = std::chrono::system_clock::now();
  std::cout << std::left << std::setw(50) << "noop" << std::setw(20)
            << 1 / std::chrono::duration<double>(stop - start).count() 
            << "Mhz"
            << std::endl;

  // fork 
  start = std::chrono::system_clock::now();
  for (int i = 0; i < iterations; i++) {
    pid_t pid = fork();
    if(!pid) {
        //std::cout << "fork\n";
        exit(0);
    }
  }
  stop = std::chrono::system_clock::now();
  std::cout << std::left << std::setw(50)
            << "fork()" << std::setw(20)
            << iterations /
                   std::chrono::duration<double>(stop - start).count() 
            << " " << std::chrono::duration<double>(stop - start).count() << "s"
            << std::endl;
}
