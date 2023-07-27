// Copyright 2023 PANDA GmbH

#ifndef DRIFT_BYTES_BYTES_H_
#define DRIFT_BYTES_BYTES_H_

#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/variant.hpp>
#include <cereal/types/vector.hpp>

namespace drift_bytes {

const uint8_t kVersion = 0;

enum Type : uint8_t {
  kBool = 0,
  kInt8 = 1,
  kUInt8 = 2,
  kInt16 = 3,
  kUInt16 = 4,
  kInt32 = 5,
  kUInt32 = 6,
  kInt64 = 7,
  kUInt64 = 8,
  kFloat32 = 9,
  kFloat64 = 10,
  kString = 11,
};

static const std::vector<std::string> kSupportedType = {
    "bool",   "int8",  "uint8",  "int16",   "uint16",  "int32",
    "uint32", "int64", "uint64", "float32", "float64", "string"};

using Shape = std::vector<uint32_t>;

using VarArray = std::vector<
    std::variant<bool, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
                 int64_t, uint64_t, float, double, std::string>>;

class Variant {
 public:
  Variant(Shape shape, VarArray data)
      : type_(), shape_(std::move(shape)), data_(std::move(data)) {
    if (data_.empty()) {
      throw std::out_of_range("Data is empty");
    }

    if (!shape_.empty()) {
      bool match =
          (std::accumulate(shape_.begin(), shape_.end(), 1,
                           std::multiplies<uint32_t>()) == data_.size());
      if (!match) {
        throw std::out_of_range("Shape and data size do not match");
      }
    } else {
      throw std::out_of_range("Shape is empty");
    }

    type_ = static_cast<Type>(data_[0].index());
  }

  template <typename T>
  explicit Variant(T value) : type_(), shape_(), data_() {
    type_ = static_cast<Type>(std::variant<T>(value).index());
    shape_ = {1};
    data_ = {value};
  }

  template <class T>
  operator T() const {
    if (type_ != static_cast<Type>(std::variant<T>().index())) {
      throw std::runtime_error("Type mismatch");
    }

    if (shape_ != Shape{1}) {
      throw std::runtime_error("Looks like it is a vector");
    }

    return std::get<T>(data_[0]);
  }

  [[nodiscard]] Type type() const { return type_; }
  [[nodiscard]] const Shape &shape() const { return shape_; }
  [[nodiscard]] const VarArray &data() const { return data_; }

  bool operator==(const Variant &rhs) const {
    return type_ == rhs.type_ && shape_ == rhs.shape_ && data_ == rhs.data_;
  }

  bool operator!=(const Variant &rhs) const { return !(rhs == *this); }

  friend std::ostream &operator<<(std::ostream &os, const Variant &variant) {
    os << "Variant(type:" << kSupportedType[variant.type_] << ", shape:{";
    for (auto &dim : variant.shape_) {
      os << dim << ",";
    }
    os << "}, data:{";

    for (auto &value : variant.data_) {
      switch (variant.type_) {
        case kBool: {
          os << std::get<bool>(value) << ", ";
          break;
        }
        case kInt8: {
          os << std::get<int8_t>(value) << ",";
          break;
        }
        case kUInt8: {
          os << std::get<uint8_t>(value) << ",";
          break;
        }
        case kInt16: {
          os << std::get<int16_t>(value) << ",";
          break;
        }
        case kUInt16: {
          os << std::get<uint16_t>(value) << ",";
          break;
        }
        case kInt32: {
          os << std::get<int32_t>(value) << ",";
          break;
        }
        case kUInt32: {
          os << std::get<uint32_t>(value) << ",";
          break;
        }
        case kInt64: {
          os << std::get<int64_t>(value) << ",";
          break;
        }
        case kUInt64: {
          os << std::get<uint64_t>(value) << ",";
          break;
        }
        case kFloat32: {
          os << std::get<float>(value) << ",";
          break;
        }
        case kFloat64: {
          os << std::get<double>(value) << ",";
          break;
        }
        case kString: {
          os << std::get<std::string>(value) << ",";
          break;
        }
      }
    }

    os << "})";
    return os;
  }

 private:
  Type type_;
  Shape shape_;
  VarArray data_;
};

class InputBuffer {
 public:
  explicit InputBuffer(std::string &&bytes) {
    buffer_ << bytes;
    cereal::PortableBinaryInputArchive archive(buffer_);
    uint8_t version;
    archive(version);

    if (version != kVersion) {
      throw std::runtime_error("Version mismatch");
    }
  }

  std::string str() const { return buffer_.str(); }

  Variant pop() {
    cereal::PortableBinaryInputArchive archive(buffer_);
    Type type;
    Shape shape;
    archive(type, shape);

    auto size = std::accumulate(shape.begin(), shape.end(), 1,
                                std::multiplies<uint32_t>());
    VarArray data(size);
    for (auto &value : data) {
      switch (type) {
        case kBool: {
          bool bool_value;
          archive(bool_value);
          value = bool_value;
          break;
        }
        case kInt8: {
          int8_t int8_value;
          archive(int8_value);
          value = int8_value;
          break;
        }
        case kUInt8: {
          uint8_t uint8_value;
          archive(uint8_value);
          value = uint8_value;
          break;
        }

        case kInt16: {
          int16_t int16_value;
          archive(int16_value);
          value = int16_value;
          break;
        }
        case kUInt16: {
          uint16_t uint16_value;
          archive(uint16_value);
          value = uint16_value;
          break;
        }
        case kInt32: {
          int32_t int32_value;
          archive(int32_value);
          value = int32_value;
          break;
        }
        case kUInt32: {
          uint32_t uint32_value;
          archive(uint32_value);
          value = uint32_value;
          break;
        }
        case kInt64: {
          int64_t int64_value;
          archive(int64_value);
          value = int64_value;
          break;
        }
        case kUInt64: {
          uint64_t uint64_value;
          archive(uint64_value);
          value = uint64_value;
          break;
        }
        case kFloat32: {
          float float_value;
          archive(float_value);
          value = float_value;
          break;
        }
        case kFloat64: {
          double double_value;
          archive(double_value);
          value = double_value;
          break;
        }
        case kString: {
          std::string string_value;
          archive(string_value);
          value = string_value;
          break;
        }
        default:
          throw std::runtime_error("Unknown type");
      }
    }

    return {shape, data};
  }

  bool empty() const { return buffer_.rdbuf()->in_avail() == 0; }

 private:
  std::stringstream buffer_;
};

class OutputBuffer {
 public:
  OutputBuffer() : buffer_() {
    cereal::PortableBinaryOutputArchive archive(buffer_);
    archive(kVersion);
  }

  std::string str() const { return buffer_.str(); }

  void push_back(const Variant &variant) {
    cereal::PortableBinaryOutputArchive archive(buffer_);
    archive(variant.type(), variant.shape());
    for (const auto &value : variant.data()) {
      switch (variant.type()) {
        case kBool:
          archive(std::get<bool>(value));
          break;
        case kInt8:
          archive(std::get<int8_t>(value));
          break;
        case kUInt8:
          archive(std::get<uint8_t>(value));
          break;
        case kInt16:
          archive(std::get<int16_t>(value));
          break;
        case kUInt16:
          archive(std::get<uint16_t>(value));
          break;
        case kInt32:
          archive(std::get<int32_t>(value));
          break;
        case kUInt32:
          archive(std::get<uint32_t>(value));
          break;
        case kInt64:
          archive(std::get<int64_t>(value));
          break;
        case kUInt64:
          archive(std::get<uint64_t>(value));
          break;
        case kFloat32:
          archive(std::get<float>(value));
          break;
        case kFloat64:
          archive(std::get<double>(value));
          break;
        case kString:
          archive(std::get<std::string>(value));
          break;
        default:
          throw std::runtime_error("Unknown type");
      }
    }
  }

 private:
  std::stringstream buffer_;
};

}  // namespace drift_bytes
#endif  // DRIFT_BYTES_BYTES_H_
