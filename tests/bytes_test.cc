// Copyright 2023 PANDA GmbH

#include <drift_bytes/bytes.h>

#include <limits>

#include <catch2/catch_test_macros.hpp>

#include "catch2/generators/catch_generators.hpp"

using drift_bytes::Bytes;
using drift_bytes::Variable;

TEST_CASE("Scalars") {
  auto val = GENERATE(
      bool(1), std::numeric_limits<uint8_t>::max(),
      std::numeric_limits<uint16_t>::max(),
      std::numeric_limits<uint32_t>::max(),
      std::numeric_limits<uint64_t>::max(), std::numeric_limits<int8_t>::max(),
      std::numeric_limits<int16_t>::max(), std::numeric_limits<int32_t>::max(),
      std::numeric_limits<int64_t>::max(), std::numeric_limits<float>::max(),
      std::numeric_limits<double>::max());

  CAPTURE(val);

  auto bytes = drift_bytes::Bytes();
  bytes << Variable(val);

  Variable<decltype(val)> res;
  bytes >> res;

  REQUIRE(res.shape().size() == 1);
  REQUIRE(res.shape()[0] == 1);
  REQUIRE(res.data().size() == 1);
  REQUIRE(res.data()[0] == val);
}

TEST_CASE("Strings") {
  std::string val =
      GENERATE("Hello", "World", "Hello World", "Hello World!", "äöü");

  CAPTURE(val);

  auto bytes = drift_bytes::Bytes();
  bytes << Variable(val);

  Variable<decltype(val)> res;
  bytes >> res;

  REQUIRE(res.shape().size() == 1);
  REQUIRE(res.shape()[0] == 1);
  REQUIRE(res.data().size() == 1);
  REQUIRE(res.data()[0] == val);
}

TEST_CASE("Vectors") {
  std::vector<int> val = GENERATE(std::vector<int>{1, 2, 3, 4, 5},
                                  std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

  CAPTURE(val);

  auto bytes = drift_bytes::Bytes();
  bytes << Variable(val);

  Variable<int> res;
  bytes >> res;

  REQUIRE(res.shape() == std::vector{val.size()});
  REQUIRE(res.data().size() == val.size());
  REQUIRE(res.data() == val);
}

TEST_CASE("Matrices") {
  std::vector<std::vector<int>> val = GENERATE(
      std::vector<std::vector<int>>{{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}},
      std::vector<std::vector<int>>{{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}});

  CAPTURE(val);

  auto bytes = drift_bytes::Bytes();
  bytes << Variable(val);

  Variable<int> res;
  bytes >> res;

  REQUIRE(res.shape() == std::vector{val.size(), val[0].size()});
  REQUIRE(res.data().size() == val.size() * val[0].size());
  REQUIRE(res.data() == std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
}