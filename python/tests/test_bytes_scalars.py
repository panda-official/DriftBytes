from drift_bytes import Bytes


def test__bool():
    b = Bytes()
    b.set_bool(True)
    assert b.get_bool()

    b.set_bool(False)
    assert not b.get_bool()


def test__int8():
    b = Bytes()
    b.set_int8(0)
    assert b.get_int8() == 0

    b.set_int8(127)
    assert b.get_int8() == 127

    b.set_int8(-128)
    assert b.get_int8() == -128


def test__int16():
    b = Bytes()
    b.set_int16(0)
    assert b.get_int16() == 0

    b.set_int16(32767)
    assert b.get_int16() == 32767

    b.set_int16(-32768)
    assert b.get_int16() == -32768


def test__int32():
    b = Bytes()
    b.set_int32(0)
    assert b.get_int32() == 0

    b.set_int32(2147483647)
    assert b.get_int32() == 2147483647

    b.set_int32(-2147483648)
    assert b.get_int32() == -2147483648


def test__int64():
    b = Bytes()
    b.set_int64(0)
    assert b.get_int64() == 0

    b.set_int64(9223372036854775807)
    assert b.get_int64() == 9223372036854775807

    b.set_int64(-9223372036854775808)
    assert b.get_int64() == -9223372036854775808


def test__uint8():
    b = Bytes()
    b.set_uint8(0)
    assert b.get_uint8() == 0

    b.set_uint8(255)
    assert b.get_uint8() == 255


def test__uint16():
    b = Bytes()
    b.set_uint16(0)
    assert b.get_uint16() == 0

    b.set_uint16(65535)
    assert b.get_uint16() == 65535


def test__uint32():
    b = Bytes()
    b.set_uint32(0)
    assert b.get_uint32() == 0

    b.set_uint32(4294967295)
    assert b.get_uint32() == 4294967295


def test__uint64():
    b = Bytes()
    b.set_uint64(0)
    assert b.get_uint64() == 0

    b.set_uint64(18446744073709551615)
    assert b.get_uint64() == 18446744073709551615


def test__float32():
    b = Bytes()
    b.set_float32(1.125)

    assert b.get_float32() == 1.125


def test__float64():
    b = Bytes()
    b.set_float64(1.123456)

    assert b.get_float64() == 1.123456


def test__string():
    b = Bytes()
    b.set_string("Hello World, ÄÖÜäöüß")

    assert b.get_string() == "Hello World, ÄÖÜäöüß"
