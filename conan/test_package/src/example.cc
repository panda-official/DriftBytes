#include <drift_bytes/bytes.h>

#include <iostream>

using drift_bytes::InputBuffer;
using drift_bytes::OutputBuffer;
using drift_bytes::Variant;

int main() {
  Variant some_value{42};

  OutputBuffer buffer;
  buffer.push_back(some_value);

  InputBuffer input(buffer.str());
  Variant new_val = input.pop();

  std::cout << new_val << std::endl;
}
