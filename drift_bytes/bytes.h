// Copyright 2023 PANDA GmbH

#ifndef DRIFT_BYTES_BYTES_H
#define DRIFT_BYTES_BYTES_H

#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

namespace drift_bytes {

/**
 * @brief A multidimensional variable is a container for data and shape_.
 * @tparam T
 */
template <typename T>
class Variable {
 public:
  Variable() = default;

  Variable(std::vector<T> &&data, std::vector<size_t> &&shape)
      : data_(data), shape_(shape) {
    if (std::accumulate(shape.begin(), shape.end(), 1,
                        std::multiplies<size_t>{}) == data.size()) {
      throw std::runtime_error("Shape and data size mismatch");
    }
  }

  explicit Variable(T scalar) : data_({scalar}), shape_({1}) {}

  explicit Variable(std::vector<T> vec) : data_(vec), shape_({vec.size()}) {}

  explicit Variable(std::vector<std::vector<T>> matrix)
      : shape_({matrix.size(), matrix[0].size()}) {
    for (const auto &row : matrix) {
      if (row.size() != matrix[0].size()) {
        throw std::runtime_error("Matrix is not rectangular");
      }

      data_.insert(data_.end(), row.begin(), row.end());
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Variable &variable) {
    os << "data: " << variable.data_ << " shape_: " << variable.shape_;
    return os;
  }

  const std::vector<T> &data() const { return data_; }

  [[nodiscard]] const std::vector<size_t> &shape() const { return shape_; }

 private:
  template <class Archive>
  void save(Archive &ar) const {
    ar(shape_, data_);
  }

  template <class Archive>
  void load(Archive &ar) {
    ar(shape_, data_);
  }

  friend class cereal::access;

  std::vector<T> data_;
  std::vector<size_t> shape_;
};


/**
 * Serializes and deserializes variables.
 */
class Bytes {
 public:
  Bytes() = default;
  explicit Bytes(std::string &&bytes);

  std::string str() const { return buffer_.str(); }

  template <typename T>
  Bytes &operator<<(const Variable<T> &var) {
    cereal::PortableBinaryOutputArchive archive(
        buffer_);  // Create an output archive
    archive(var);  // Write the data to the archive
    return *this;
  }

  template <typename T>
  Bytes &operator>>(Variable<T> &var) {
    cereal::PortableBinaryInputArchive archive(
        buffer_);  // Create an input archive
    archive(var);  // Read the data from the archive

    return *this;
  }

 private:
  std::stringstream buffer_;
};

}  // namespace drift_bytes
#endif  // DRIFT_BYTES_BYTES_H
