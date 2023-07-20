from typing import List

import drift_bytes._drift_bytes as impl


class Bytes(impl.Bytes):
    def __init__(self):
        super(Bytes, self).__init__()

    def get_bool(self) -> bool:
        return super(Bytes, self).get_bool()

    def set_bool(self, value: bool) -> None:
        super(Bytes, self).set_bool(value)

    def get_int8(self) -> int:
        return super(Bytes, self).get_int8()

    def set_int8(self, value: int) -> None:
        super(Bytes, self).set_int8(value)

    def get_int16(self) -> int:
        return super(Bytes, self).get_int16()

    def set_int16(self, value: int) -> None:
        super(Bytes, self).set_int16(value)

    def get_int32(self) -> int:
        return super(Bytes, self).get_int32()

    def set_int32(self, value: int) -> None:
        super(Bytes, self).set_int32(value)

    def get_int64(self) -> int:
        return super(Bytes, self).get_int64()

    def set_int64(self, value: int) -> None:
        super(Bytes, self).set_int64(value)

    def get_uint8(self) -> int:
        return super(Bytes, self).get_uint8()

    def set_uint8(self, value: int) -> None:
        super(Bytes, self).set_uint8(value)

    def get_uint16(self) -> int:
        return super(Bytes, self).get_uint16()

    def set_uint16(self, value: int) -> None:
        super(Bytes, self).set_uint16(value)

    def get_uint32(self) -> int:
        return super(Bytes, self).get_uint32()

    def set_uint32(self, value: int) -> None:
        super(Bytes, self).set_uint32(value)

    def get_uint64(self) -> int:
        return super(Bytes, self).get_uint64()

    def set_uint64(self, value: int) -> None:
        super(Bytes, self).set_uint64(value)

    def get_float32(self) -> float:
        return super(Bytes, self).get_float32()

    def set_float32(self, value: float) -> None:
        super(Bytes, self).set_float32(value)

    def get_float64(self) -> float:
        return super(Bytes, self).get_float64()

    def set_float64(self, value: float) -> None:
        super(Bytes, self).set_float64(value)

    def set_string(self, value: str) -> None:
        super(Bytes, self).set_string(value)

    def get_string(self) -> str:
        return super(Bytes, self).get_string()

    def get_bool_vec(self) -> List[bool]:
        return super(Bytes, self).get_bool_vec()

    def set_bool_vec(self, value: List[bool]) -> None:
        super(Bytes, self).set_bool_vec(value)

    def get_int8_vec(self) -> List[int]:
        return super(Bytes, self).get_int8_vec()

    def set_int8_vec(self, value: List[int]) -> None:
        super(Bytes, self).set_int8_vec(value)

    def get_int16_vec(self) -> List[int]:
        return super(Bytes, self).get_int16_vec()

    def set_int16_vec(self, value: List[int]) -> None:
        super(Bytes, self).set_int16_vec(value)

    def get_int32_vec(self) -> List[int]:
        return super(Bytes, self).get_int32_vec()

    def set_int32_vec(self, value: List[int]) -> None:
        super(Bytes, self).set_int32_vec(value)

    def get_int64_vec(self) -> List[int]:
        return super(Bytes, self).get_int64_vec()

    def set_int64_vec(self, value: List[int]) -> None:
        super(Bytes, self).set_int64_vec(value)

    def get_uint8_vec(self) -> List[int]:
        return super(Bytes, self).get_uint8_vec()

    def set_uint8_vec(self, value: List[int]) -> None:
        super(Bytes, self).set_uint8_vec(value)

    def get_uint16_vec(self) -> List[int]:
        return super(Bytes, self).get_uint16_vec()

    def set_uint16_vec(self, value: List[int]) -> None:
        super(Bytes, self).set_uint16_vec(value)

    def get_uint32_vec(self) -> List[int]:
        return super(Bytes, self).get_uint32_vec()

    def set_uint32_vec(self, value: List[int]) -> None:
        super(Bytes, self).set_uint32_vec(value)

    def get_uint64_vec(self) -> List[int]:
        return super(Bytes, self).get_uint64_vec()

    def set_uint64_vec(self, value: List[int]) -> None:
        super(Bytes, self).set_uint64_vec(value)

    def get_float32_vec(self) -> List[float]:
        return super(Bytes, self).get_float32_vec()

    def set_float32_vec(self, value: List[float]) -> None:
        super(Bytes, self).set_float32_vec(value)

    def get_float64_vec(self) -> List[float]:
        return super(Bytes, self).get_float64_vec()

    def set_float64_vec(self, value: List[float]) -> None:
        super(Bytes, self).set_float64_vec(value)

    def get_string_vec(self) -> List[str]:
        return super(Bytes, self).get_string_vec()

    def set_string_vec(self, value: List[str]) -> None:
        super(Bytes, self).set_string_vec(value)
