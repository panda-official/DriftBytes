# pylint: disable=missing-docstring, too-many-public-methods, useless-super-delegation
"""Bindings for the C++ implementation of the Bytes class."""
from typing import List, Union, Optional

import drift_bytes._drift_bytes as impl  # pylint: disable=import-error, no-name-in-module


class Variant:
    TYPES = impl.supported_types()  # pylint: disable=c-extension-no-member
    SUPPORTED_TYPES = Union[
        bool,
        int,
        float,
        str,
        List[bool],
        List[int],
        List[float],
        List[str],
    ]

    def __init__(
        self,
        value: SUPPORTED_TYPES,
        kind: Optional[str] = None,
    ):
        """Create Variant object from value

        Args:
            kind (str): Type of value can be: bool, uint8, int8,
            uint16, int16, uint32, int32, uint64, int64, float32, float64, string
            value (Union[bool, int, float, str, List[bool], List[int], List[float],
            List[str]]): Value to be stored in Variant object
        """

        if isinstance(value, impl.Variant):
            # for internal use only to pop from InputBuffer
            self._variant = value
            self._type = value.type()
            self._shape = value.shape()
            return

        type_error = TypeError(
            f"Unsupported type: {kind}. Must be one of: {self.TYPES}"
        )

        self._type = self._find_type(kind, type_error, value)

        if not isinstance(value, list):
            value = [value]

        self._shape = [len(value)]
        self._make_variant(self._type, self._shape, value)

    def _find_type(self, kind, type_error, value):  # pylint: disable=too-many-branches
        if kind is None:
            if isinstance(value, bool):
                kind = "bool"
            elif isinstance(value, int):
                kind = "int64"
            elif isinstance(value, float):
                kind = "float64"
            elif isinstance(value, str):
                kind = "string"
            elif isinstance(value, list):
                if len(value) == 0:
                    raise ValueError("Empty list cannot be converted to Variant")
                if isinstance(value[0], bool):
                    kind = "bool"
                elif isinstance(value[0], int):
                    kind = "int64"
                elif isinstance(value[0], float):
                    kind = "float64"
                elif isinstance(value[0], str):
                    kind = "string"
                else:
                    raise type_error
            elif isinstance(value, Variant):
                kind = value.type
            else:
                raise type_error
        if kind not in self.TYPES:
            raise type_error
        return kind

    def _make_variant(self, kind, shape, value):
        if kind == "bool":
            self._variant = impl.Variant.from_bools(shape, value)
        elif kind == "uint8":
            self._variant = impl.Variant.from_int8s(shape, value)
        elif kind == "int8":
            self._variant = impl.Variant.from_int8s(shape, value)
        elif kind == "uint16":
            self._variant = impl.Variant.from_uint16s(shape, value)
        elif kind == "int16":
            self._variant = impl.Variant.from_int16s(shape, value)
        elif kind == "uint32":
            self._variant = impl.Variant.from_uint32s(shape, value)
        elif kind == "int32":
            self._variant = impl.Variant.from_int32s(shape, value)
        elif kind == "uint64":
            self._variant = impl.Variant.from_uint64s(shape, value)
        elif kind == "int64":
            self._variant = impl.Variant.from_int64s(shape, value)
        elif kind == "float32":
            self._variant = impl.Variant.from_float32s(shape, value)
        elif kind == "float64":
            self._variant = impl.Variant.from_float64s(shape, value)
        elif kind == "string":
            self._variant = impl.Variant.from_strings(shape, value)

    @property
    def type(self) -> str:
        """Get type"""
        return self._type

    @property
    def shape(self) -> List[int]:
        """Get shape"""
        return self._variant.shape()

    @property
    def value(self) -> SUPPORTED_TYPES:  # pylint: disable=too-many-branches
        """Get value"""
        if self._type == "bool":
            ary = self._variant.to_bools()
        elif self._type == "uint8":
            ary = self._variant.to_uint8s()
        elif self._type == "int8":
            ary = self._variant.to_int8s()
        elif self._type == "uint16":
            ary = self._variant.to_uint16s()
        elif self._type == "int16":
            ary = self._variant.to_int16s()
        elif self._type == "uint32":
            ary = self._variant.to_uint32s()
        elif self._type == "int32":
            ary = self._variant.to_int32s()
        elif self._type == "uint64":
            ary = self._variant.to_uint64s()
        elif self._type == "int64":
            ary = self._variant.to_int64s()
        elif self._type == "float32":
            ary = self._variant.to_float32s()
        elif self._type == "float64":
            ary = self._variant.to_float64s()
        elif self._type == "string":
            ary = self._variant.to_strings()
        else:
            raise TypeError(f"Unsupported type: {self._type}")

        if self.shape == [1]:
            return ary[0]

        return ary


class InputBuffer:
    def __init__(self, buffer: bytes):
        self._buffer = impl.InputBuffer.from_bytes(buffer)

    def pop(self) -> Variant:
        return Variant(self._buffer.pop())

    def empty(self) -> bool:
        return self._buffer.empty()


class OutputBuffer:
    def __init__(self):
        self._buffer = impl.OutputBuffer()

    def push(self, value: Variant):
        self._buffer.push(value._variant)  # pylint: disable=protected-access

    def bytes(self):
        return self._buffer.bytes()
