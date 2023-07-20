#include <drift_bytes/bytes.h>

#include <iostream>

using drift_bytes::Bytes;
using drift_bytes::Variable;

int main() {
  uint32_t val = 42;

  auto bytes = Bytes();
  bytes << Variable(val);

  Variable<uint32_t> res;
  bytes >> res;

  std::cout << res.data()[0] << std::endl;
}
