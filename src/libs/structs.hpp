// src/libs/structs.hpp

#ifndef STRUCTS_H
#define STRUCTS_H

#include <cstdint>
#include <string>

struct Customer {
  int64_t uid;
  std::string name, dob;
};

#endif
