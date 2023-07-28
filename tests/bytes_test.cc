// Copyright 2023 PANDA GmbH

#include <drift_bytes/bytes.h>

#include <limits>

#include <catch2/catch_test_macros.hpp>

#include "catch2/generators/catch_generators.hpp"

using drift_bytes::InputBuffer;
using drift_bytes::OutputBuffer;
using drift_bytes::Shape;
using drift_bytes::Type;
using drift_bytes::Variant;

TEST_CASE("Full test") {
  Variant var1({1, 3}, {1, 2, 3});
  Variant var2 =
      GENERATE(Variant({2}, {true, false}), Variant({2}, {1.0, 2.0}),
               Variant({2}, {"Hello", "World"}), Variant({3}, {1l, 2l, 3l}),
               Variant({3}, {1ul, 2ul, 3ul}), Variant({3}, {1.0f, 2.0f, 3.0f}));

  OutputBuffer out;
  out.push_back(var1);
  out.push_back(var2);

  InputBuffer in(out.str());

  REQUIRE(in.pop() == var1);
  REQUIRE_FALSE(in.empty());

  REQUIRE(in.pop() == var2);
  REQUIRE(in.empty());
}

TEST_CASE("Variant: Test scalars") {
  auto value =
      GENERATE(Variant{true}, Variant{uint8_t{9}}, Variant{int8_t{-9}},
               Variant{uint16_t{9}}, Variant{int16_t{-9}}, Variant{uint32_t{9}},
               Variant{int32_t{-9}}, Variant{uint64_t{9}}, Variant{int64_t{-9}},
               Variant{float{9.0}}, Variant{double{9.0}});

  REQUIRE(value.shape() == Shape{1});
}

TEST_CASE("Variant: Test strings") {
  std::string value = "Hello World, ÄÖÜß should be UTF-8";
  Variant var{value};

  REQUIRE(var.shape() == Shape{1});
  REQUIRE(value == static_cast<std::string>(var));
}

TEST_CASE("Variant: test stream") {
  Variant var({1, 3}, {1, 2, 3});
  std::stringstream ss;
  ss << var;

  REQUIRE(ss.str() == "Variant(type:int32, shape:{1,3,}, data:{1,2,3,})");
}
