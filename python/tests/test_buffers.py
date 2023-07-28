"""Test the InputBuffer and OutputBuffer classes."""
from drift_bytes import Variant, InputBuffer, OutputBuffer


def test_input_output():
    """Should push and pop"""
    out_buf = OutputBuffer()
    out_buf.push(Variant([1, 2, 3, 4, 5, 6]))

    in_buf = InputBuffer(out_buf.bytes())

    var = in_buf.pop()
    assert var.type == "int64"
    assert var.shape == [6]
    assert var.value == [1, 2, 3, 4, 5, 6]

    assert in_buf.empty()
