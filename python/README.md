# Python DriftBytes

Python bindings for [DriftBytes](https://github.com/panda-official/DriftBytes).

## Requirements

* Python >= 3.8
* CMake >= 3.16 (for building)
* C++17 compiler (for building)
* conan >= 1.56, < 2.0 (for building)

## Installation

```bash
pip install drift-bytes
```

## Usage Example

```python
from drift_bytes import Variant, InputBuffer, OutputBuffer

out_buf = OutputBuffer()
out_buf.push(Variant([1, 2, 3, 4, 5, 6]))

in_buf = InputBuffer(out_buf.bytes())

var = in_buf.pop()

print(var.value)
```
